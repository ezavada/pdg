// -----------------------------------------------
// audio_cleanup_manager.h
// 
// Manages deferred cleanup of audio resources to prevent blocking
// the main thread during sound disposal
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

#ifndef PDG_AUDIO_CLEANUP_MANAGER_H_INCLUDED
#define PDG_AUDIO_CLEANUP_MANAGER_H_INCLUDED

#include "pdg_project.h"
#include "pdg/sys/global_types.h"
#include <vector>
#include <mutex>
#include <atomic>

// Include Core Audio headers for type definitions
#include <AudioToolbox/AudioToolbox.h>
#include <CoreFoundation/CFURL.h>

namespace pdg {

// -----------------------------------------------------------------------------------
// DeferredAudioCleanup
// Manages deferred cleanup of audio resources to prevent blocking
// -----------------------------------------------------------------------------------

class DeferredAudioCleanup {
public:
    static DeferredAudioCleanup& getInstance();
    
    // Schedule cleanup of audio resources
    void scheduleCleanup(AudioQueueRef queue, AudioFileID file, CFURLRef fileRef);
    
    // Process pending cleanup operations (called from idle loop)
    void processCleanup();
    
    // Force immediate cleanup of all pending resources
    void forceCleanup();
    
    // Get cleanup statistics
    struct CleanupStats {
        uint32_t pendingCleanups;
        uint32_t completedCleanups;
        uint32_t failedCleanups;
        ms_time lastCleanupTime;
    };
    CleanupStats getStats() const;
    
private:
    DeferredAudioCleanup();
    ~DeferredAudioCleanup();
    
    // Prevent copying
    DeferredAudioCleanup(const DeferredAudioCleanup&) = delete;
    DeferredAudioCleanup& operator=(const DeferredAudioCleanup&) = delete;
    
    struct PendingCleanup {
        AudioQueueRef queue;
        AudioFileID file;
        CFURLRef fileRef;
        ms_time scheduledTime;
        int retryCount;
        bool isProcessing;
    };
    
    std::vector<PendingCleanup> mPendingCleanup;
    mutable std::mutex mCleanupMutex;
    std::atomic<uint32_t> mCompletedCleanups;
    std::atomic<uint32_t> mFailedCleanups;
    ms_time mLastCleanupTime;
    
    // Process a single cleanup task
    bool processCleanupTask(PendingCleanup& task);
    
    // Remove completed tasks from the queue
    void cleanupCompletedTasks();
    
    // Constants
    static const int MAX_RETRY_COUNT = 3;
    static const ms_delta CLEANUP_TIMEOUT_MS = 5000; // 5 seconds
};

} // namespace pdg

#endif // PDG_AUDIO_CLEANUP_MANAGER_H_INCLUDED
