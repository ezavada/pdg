// -----------------------------------------------
// audio_cleanup_manager.cpp
// 
// Implementation of deferred audio cleanup management
//
// Written by Ed Zavada, 2024
// Copyright (c) 2024, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------

#include "audio_cleanup_manager.h"
#include "pdg/sys/core.h"
#include "pdg/sys/os.h"
#include <AudioToolbox/AudioToolbox.h>
#include <CoreFoundation/CFURL.h>

//#define PDG_DEBUG_AUDIO_CLEANUP
#ifndef PDG_DEBUG_AUDIO_CLEANUP
  #define AUDIO_CLEANUP_DEBUG_ONLY(_expression)
#else
  #define AUDIO_CLEANUP_DEBUG_ONLY DEBUG_ONLY
#endif

namespace pdg {

DeferredAudioCleanup& DeferredAudioCleanup::getInstance() {
    static DeferredAudioCleanup instance;
    return instance;
}

DeferredAudioCleanup::DeferredAudioCleanup() 
    : mCompletedCleanups(0)
    , mFailedCleanups(0)
    , mLastCleanupTime(0) {
    AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Created cleanup manager"));
}

DeferredAudioCleanup::~DeferredAudioCleanup() {
    AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Destroying cleanup manager"));
    forceCleanup();
}

void DeferredAudioCleanup::scheduleCleanup(AudioQueueRef queue, AudioFileID file, CFURLRef fileRef) {
    if (!queue && !file && !fileRef) {
        return; // Nothing to clean up
    }
    
    std::lock_guard<std::mutex> lock(mCleanupMutex);
    
    PendingCleanup cleanup;
    cleanup.queue = queue;
    cleanup.file = file;
    cleanup.fileRef = fileRef;
    cleanup.scheduledTime = OS::getMilliseconds();
    cleanup.retryCount = 0;
    cleanup.isProcessing = false;
    
    mPendingCleanup.push_back(cleanup);
    
    AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Scheduled cleanup for queue %p, file %p, fileRef %p", 
                                       queue, file, fileRef));
}

void DeferredAudioCleanup::processCleanup() {
    std::lock_guard<std::mutex> lock(mCleanupMutex);
    
    if (mPendingCleanup.empty()) {
        return;
    }
    
    ms_time currentTime = OS::getMilliseconds();
    mLastCleanupTime = currentTime;
    
    AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Processing %zu pending cleanups", mPendingCleanup.size()));
    
    // Process each pending cleanup task
    for (auto& task : mPendingCleanup) {
        if (task.isProcessing) {
            continue; // Skip tasks already being processed
        }
        
        // Check if task has timed out
        if (currentTime - task.scheduledTime > CLEANUP_TIMEOUT_MS) {
            AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Task timed out, forcing cleanup"));
            task.retryCount = MAX_RETRY_COUNT; // Force cleanup
        }
        
        if (processCleanupTask(task)) {
            task.isProcessing = true; // Mark as processing
        }
    }
    
    // Remove completed tasks
    cleanupCompletedTasks();
}

bool DeferredAudioCleanup::processCleanupTask(PendingCleanup& task) {
    bool success = true;
    
    try {
        // Clean up AudioQueue if present
        if (task.queue) {
            OSStatus result = AudioQueueDispose(task.queue, false); // Non-blocking
            if (result != noErr) {
                AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: AudioQueueDispose failed with error %d", result));
                success = false;
            } else {
                AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Successfully disposed AudioQueue %p", task.queue));
                task.queue = nullptr;
            }
        }
        
        // Clean up AudioFile if present
        if (task.file) {
            OSStatus result = AudioFileClose(task.file);
            if (result != noErr) {
                AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: AudioFileClose failed with error %d", result));
                success = false;
            } else {
                AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Successfully closed AudioFile %p", task.file));
                task.file = nullptr;
            }
        }
        
        // Clean up CFURL if present
        if (task.fileRef) {
            CFRelease(task.fileRef);
            AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Successfully released CFURL %p", task.fileRef));
            task.fileRef = nullptr;
        }
        
    } catch (...) {
        AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Exception during cleanup task"));
        success = false;
    }
    
    if (success) {
        mCompletedCleanups++;
        AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Task completed successfully"));
    } else {
        task.retryCount++;
        if (task.retryCount >= MAX_RETRY_COUNT) {
            mFailedCleanups++;
            AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Task failed after %d retries", task.retryCount));
        } else {
            AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Task failed, will retry (%d/%d)", 
                                               task.retryCount, MAX_RETRY_COUNT));
        }
    }
    
    return success;
}

void DeferredAudioCleanup::cleanupCompletedTasks() {
    // Remove tasks that are completed (all resources cleaned up) or failed too many times
    auto it = mPendingCleanup.begin();
    while (it != mPendingCleanup.end()) {
        if ((it->queue == nullptr && it->file == nullptr && it->fileRef == nullptr) || 
            it->retryCount >= MAX_RETRY_COUNT) {
            it = mPendingCleanup.erase(it);
        } else {
            ++it;
        }
    }
}

void DeferredAudioCleanup::forceCleanup() {
    std::lock_guard<std::mutex> lock(mCleanupMutex);
    
    AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Forcing cleanup of %zu pending tasks", mPendingCleanup.size()));
    
    // Process all pending tasks with maximum retries
    for (auto& task : mPendingCleanup) {
        task.retryCount = MAX_RETRY_COUNT;
        processCleanupTask(task);
    }
    
    // Remove all tasks
    mPendingCleanup.clear();
    
    AUDIO_CLEANUP_DEBUG_ONLY(OS::_DOUT("DeferredAudioCleanup: Force cleanup completed"));
}

DeferredAudioCleanup::CleanupStats DeferredAudioCleanup::getStats() const {
    std::lock_guard<std::mutex> lock(mCleanupMutex);
    
    CleanupStats stats;
    stats.pendingCleanups = static_cast<uint32_t>(mPendingCleanup.size());
    stats.completedCleanups = mCompletedCleanups.load();
    stats.failedCleanups = mFailedCleanups.load();
    stats.lastCleanupTime = mLastCleanupTime;
    
    return stats;
}

} // namespace pdg
