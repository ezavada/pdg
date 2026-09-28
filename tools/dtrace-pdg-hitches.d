#!/usr/sbin/dtrace -s

/*
 * PDG Hitch Detection Script
 * 
 * This script specifically monitors for performance hitches in PDG.
 * Run with: sudo dtrace -s tools/dtrace-pdg-hitches.d -p <PDG_PID>
 * 
 * Usage:
 * 1. Start PDG: ./pdg test/js/main.js
 * 2. Get PID: ps aux | grep pdg
 * 3. Run: sudo dtrace -s tools/dtrace-pdg-hitches.d -p <PID>
 */

#pragma D option quiet
#pragma D option switchrate=1000hz

/* Global variables */
BEGIN
{
    printf("PDG Hitch Detection Started\n");
    printf("Monitoring for performance hitches...\n\n");
    
    last_timestamp = timestamp;
    frame_count = 0;
    hitch_count = 0;
}

/* Monitor frame timing by looking for GL swap/flush operations */
pid$target:libGL.dylib:glFlush:entry,
pid$target:libGL.dylib:glFinish:entry,
pid$target:libGL.dylib:glSwapBuffers:entry
{
    frame_count++;
    current_time = timestamp;
    frame_duration = current_time - last_timestamp;
    
    /* Detect frame drops (frames taking longer than 16.67ms for 60fps) */
    if (frame_duration > 16670000) {  /* >16.67ms */
        hitch_count++;
        printf("HITCH #%d: Frame %d took %d ms (expected ~16.67ms)\n", 
               hitch_count, frame_count, frame_duration / 1000000);
    }
    
    last_timestamp = current_time;
}

/* Monitor system calls that could cause hitches */
syscall:::entry
/pid == $target/
{
    self->syscall_start = timestamp;
    self->syscall_name = probefunc;
}

syscall:::return
/pid == $target && self->syscall_start/
{
    duration = timestamp - self->syscall_start;
    
    /* Log system calls that take longer than 5ms */
    if (duration > 5000000) {  /* >5ms */
        printf("SLOW SYSCALL: %s took %d ms\n", self->syscall_name, duration / 1000000);
    }
    
    self->syscall_start = 0;
    self->syscall_name = "";
}

/* Monitor memory allocation that could cause GC */
pid$target:libsystem_malloc.dylib:malloc:entry
{
    self->malloc_start = timestamp;
    self->malloc_size = arg0;
}

pid$target:libsystem_malloc.dylib:malloc:return
/self->malloc_start/
{
    duration = timestamp - self->malloc_start;
    
    /* Log large allocations that could trigger GC */
    if (self->malloc_size > 1024 * 1024) {  /* >1MB */
        printf("LARGE ALLOC: %d bytes took %d ms\n", self->malloc_size, duration / 1000000);
    }
    
    self->malloc_start = 0;
    self->malloc_size = 0;
}

/* Monitor V8/Node.js functions that might indicate GC */
pid$target:node:*:entry
/strstr(probefunc, "GC") != NULL || 
 strstr(probefunc, "gc") != NULL || 
 strstr(probefunc, "Collect") != NULL/
{
    self->gc_start = timestamp;
    self->gc_func = probefunc;
    printf("GC START: %s\n", probefunc);
}

pid$target:node:*:return
/self->gc_start/
{
    duration = timestamp - self->gc_start;
    printf("GC END: %s took %d ms\n", self->gc_func, duration / 1000000);
    self->gc_start = 0;
    self->gc_func = "";
}

/* Monitor file I/O that could cause hitches */
syscall::open:entry,
syscall::read:entry,
syscall::write:entry
/pid == $target/
{
    self->io_start = timestamp;
    self->io_op = probefunc;
}

syscall::open:return,
syscall::read:return,
syscall::write:return
/pid == $target && self->io_start/
{
    duration = timestamp - self->io_start;
    
    if (duration > 1000000) {  /* >1ms */
        printf("SLOW I/O: %s took %d ms\n", self->io_op, duration / 1000000);
    }
    
    self->io_start = 0;
    self->io_op = "";
}

/* Monitor timer/scheduling operations */
syscall::select:entry,
syscall::poll:entry,
syscall::kevent:entry
/pid == $target/
{
    self->timer_start = timestamp;
    self->timer_syscall = probefunc;
}

syscall::select:return,
syscall::poll:return,
syscall::kevent:return
/pid == $target && self->timer_start/
{
    duration = timestamp - self->timer_start;
    
    if (duration > 1000000) {  /* >1ms */
        printf("TIMER WAIT: %s took %d ms\n", self->timer_syscall, duration / 1000000);
    }
    
    self->timer_start = 0;
    self->timer_syscall = "";
}

/* Periodic status report */
profile:::tick-10sec
{
    printf("STATUS: %d frames, %d hitches detected\n", frame_count, hitch_count);
}

/* Print summary when script ends */
END
{
    printf("\n=== PDG Hitch Detection Summary ===\n");
    printf("Total frames monitored: %d\n", frame_count);
    printf("Total hitches detected: %d\n", hitch_count);
    
    if (frame_count > 0) {
        printf("Hitch rate: %d%%\n", (hitch_count * 100) / frame_count);
    }
    
    printf("=== End Summary ===\n");
}
