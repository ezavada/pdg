// -----------------------------------------------
// semaphore.h
//
// Provides platform independent semaphore classes.
//
// This is an auto-reset wakeup event: repeated signals coalesce into
// one pending wakeup, consumed by one waiter. It is not a counting semaphore.
//
// Written by Ed Zavada, 2001-2012
// Copyright (c) 2012, Dream Rock Studios, LLC
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


#ifndef PDG_SEMAPHORE_H_INCLUDED
#define PDG_SEMAPHORE_H_INCLUDED

#include "pdg_project.h"
#include "pdg/sys/global_types.h"

#include <chrono>
#include <condition_variable>
#include <mutex>

namespace pdg {

// Retain the public name and coalescing semantics used by the main event loop.
// A bare std::binary_semaphore cannot safely accept repeated releases while full.
class Semaphore {
public:
    Semaphore() = default;
    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    void awaitSignal() {
        std::unique_lock lock(mMutex);
        mCondition.wait(lock, [this] { return mSignaled; });
        mSignaled = false;
    }
    bool awaitSignal(ms_delta waitMilliseconds) {
        std::unique_lock lock(mMutex);
        if (!mCondition.wait_for(lock, std::chrono::milliseconds(waitMilliseconds),
                                 [this] { return mSignaled; })) {
            return false;
        }
        mSignaled = false;
        return true;
    }
    void signal() {
        // Notify while holding the lock so a consumer cannot destroy the event
        // between publishing the flag and notifying the condition variable.
        std::lock_guard lock(mMutex);
        mSignaled = true;
        mCondition.notify_one();
    }
private:
    std::mutex mMutex;
    std::condition_variable mCondition;
    bool mSignaled = false;
};

} // namespace pdg
#endif // PDG_SEMAPHORE_H_INCLUDED
