#!/usr/sbin/dtrace -s

/*
 * Basic PDG Performance Monitoring Script
 * 
 * This script monitors PDG performance without relying on specific OpenGL functions.
 * Run with: sudo dtrace -s tools/dtrace-pdg-basic.d -p <PDG_PID>
 */

#pragma D option quiet
#pragma D option switchrate=1000hz

/* Global variables */
BEGIN
{
    printf("PDG Basic Performance Monitoring Started\n");
    printf("Monitoring for performance issues...\n\n");
    
    syscall_count = 0;
    slow_syscall_count = 0;
    gc_count = 0;
}

/* Monitor system calls that could cause hitches */
syscall:::entry
/pid == $target/
{
    self->syscall_start = timestamp;
    self->syscall_name = probefunc;
    syscall_count++;
}

syscall:::return
/pid == $target && self->syscall_start/
{
    duration = timestamp - self->syscall_start;
    
    /* Log system calls that take longer than 5ms */
    if (duration > 5000000) {  /* >5ms */
        slow_syscall_count++;
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
    gc_count++;
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

/* Monitor any OpenGL operations that exist */
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
    
    self->gl_start = 0;
    self->gl_func = "";
}

/* Periodic status report */
profile:::tick-10sec
{
    printf("STATUS: %d syscalls, %d slow, %d GC events\n", 
           syscall_count, slow_syscall_count, gc_count);
}

/* Print summary when script ends */
END
{
    printf("\n=== PDG Basic Performance Summary ===\n");
    printf("Total system calls: %d\n", syscall_count);
    printf("Slow system calls (>5ms): %d\n", slow_syscall_count);
    printf("Garbage collection events: %d\n", gc_count);
    
    if (syscall_count > 0) {
        printf("Slow syscall rate: %d%%\n", (slow_syscall_count * 100) / syscall_count);
    }
    
    printf("=== End Summary ===\n");
}
