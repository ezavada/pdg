#!/usr/sbin/dtrace -s

/*
 * PDG Performance Profiling Script
 * 
 * This script monitors PDG performance to identify hitches and bottlenecks.
 * Run with: sudo dtrace -s tools/dtrace-pdg-profile.d
 * 
 * Usage:
 * 1. Start this script in one terminal
 * 2. Run your PDG application in another terminal
 * 3. Press Ctrl+C to stop profiling and see results
 */

#pragma D option quiet
#pragma D option switchrate=10hz

/* Global variables to track timing */
BEGIN
{
    printf("PDG Performance Profiling Started\n");
    printf("Run your PDG application now...\n");
    printf("Press Ctrl+C to stop and see results\n\n");
    
    /* Initialize timing variables */
    last_timestamp = timestamp;
    long_syscalls = 0;
    long_functions = 0;
    total_samples = 0;
}

/* Monitor system calls that take a long time */
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
    
    /* Track system calls longer than 1ms */
    @syscall_duration[probefunc] = quantize(duration / 1000000);
    
    /* Log very long system calls (>10ms) */
    @long_syscalls[probefunc] = lquantize(duration / 1000000, 0, 50, 1);
    
    if (duration > 10000000) {  /* >10ms */
        printf("LONG SYSCALL: %s took %d ms\n", probefunc, duration / 1000000);
    }
    
    self->syscall_start = 0;
    self->syscall_name = "";
}

/* Monitor function entry/exit for performance analysis */
pid$target:pdg:*:entry
{
    self->func_start = timestamp;
    self->func_name = probefunc;
}

pid$target:pdg:*:return
/self->func_start/
{
    duration = timestamp - self->func_start;
    
    /* Track function durations */
    @func_duration[probefunc] = quantize(duration / 1000000);
    
    /* Log very long functions (>5ms) */
    if (duration > 5000000) {  /* >5ms */
        printf("LONG FUNCTION: %s took %d ms\n", probefunc, duration / 1000000);
    }
    
    self->func_start = 0;
    self->func_name = "";
}

/* Monitor V8 garbage collection */
pid$target:node:*:entry
/strstr(probefunc, "GC") != NULL || strstr(probefunc, "gc") != NULL/
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
    @gc_duration[self->gc_func] = quantize(duration / 1000000);
    self->gc_start = 0;
    self->gc_func = "";
}

/* Monitor memory allocation patterns */
pid$target:libsystem_malloc.dylib:malloc:entry
{
    self->malloc_start = timestamp;
    self->malloc_size = arg0;
}

pid$target:libsystem_malloc.dylib:malloc:return
/self->malloc_start/
{
    duration = timestamp - self->malloc_start;
    
    /* Track large allocations */
    if (self->malloc_size > 1024 * 1024) {  /* >1MB */
        printf("LARGE ALLOC: %d bytes took %d ms\n", self->malloc_size, duration / 1000000);
    }
    
    @malloc_duration = quantize(duration / 1000000);
    self->malloc_start = 0;
    self->malloc_size = 0;
}

/* Monitor file I/O operations */
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
    
    @io_duration[self->io_op] = quantize(duration / 1000000);
    self->io_start = 0;
    self->io_op = "";
}

/* Monitor OpenGL/Graphics operations */
pid$target:libGL.dylib:*:entry
{
    self->gl_start = timestamp;
    self->gl_func = probefunc;
}

pid$target:libGL.dylib:*:return
/self->gl_start/
{
    duration = timestamp - self->gl_start;
    
    if (duration > 5000000) {  /* >5ms */
        printf("SLOW GL: %s took %d ms\n", self->gl_func, duration / 1000000);
    }
    
    @gl_duration[self->gl_func] = quantize(duration / 1000000);
    self->gl_start = 0;
    self->gl_func = "";
}

/* Monitor timer events and scheduling */
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
    
    @timer_duration[self->timer_syscall] = quantize(duration / 1000000);
    self->timer_start = 0;
    self->timer_syscall = "";
}

/* Periodic sampling to detect hitches */
profile:::tick-1sec
{
    total_samples++;
    
    /* Check for long periods of inactivity */
    if (timestamp - last_timestamp > 100000000) {  /* >100ms */
        printf("HITCH DETECTED: %d ms gap at sample %d\n", 
               (timestamp - last_timestamp) / 1000000, total_samples);
    }
    
    last_timestamp = timestamp;
}

/* Print summary when script ends */
END
{
    printf("\n=== PDG Performance Profile Summary ===\n");
    printf("Total samples collected: %d\n", total_samples);
    
    printf("\n--- System Call Duration Distribution ---\n");
    printa(@syscall_duration);
    
    printf("\n--- Function Duration Distribution ---\n");
    printa(@func_duration);
    
    printf("\n--- Garbage Collection Duration Distribution ---\n");
    printa(@gc_duration);
    
    printf("\n--- Memory Allocation Duration Distribution ---\n");
    printa(@malloc_duration);
    
    printf("\n--- I/O Operation Duration Distribution ---\n");
    printa(@io_duration);
    
    printf("\n--- OpenGL Operation Duration Distribution ---\n");
    printa(@gl_duration);
    
    printf("\n--- Timer/Scheduling Duration Distribution ---\n");
    printa(@timer_duration);
    
    printf("\n--- Long System Calls (>10ms) ---\n");
    printa(@long_syscalls);
    
    printf("\n=== End Profile Summary ===\n");
}
