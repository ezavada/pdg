# PDG DTrace Performance Profiling

This directory contains DTrace scripts to profile PDG performance and identify the root causes of frame rate hitches.

## Files

- `dtrace-pdg-profile.d` - Comprehensive performance profiling
- `dtrace-pdg-hitches.d` - Focused hitch detection
- `run-dtrace-profile.sh` - Convenience script for running profiling

## Quick Start

### 1. Hitch Detection (Recommended)

```bash
# Terminal 1: Start PDG
./pdg test/js/main.js

# Terminal 2: Get PDG PID
ps aux | grep pdg

# Terminal 3: Run hitch detection
sudo tools/run-dtrace-profile.sh
# Choose option 2, then enter the PDG PID
```

### 2. Full Profiling

```bash
# Terminal 1: Run full profiling
sudo tools/run-dtrace-profile.sh
# Choose option 1

# Terminal 2: Start PDG
./pdg test/js/main.js

# Terminal 1: Press Ctrl+C to stop and see results
```

## What DTrace Monitors

### Hitch Detection Script
- **Frame timing** via OpenGL operations
- **System calls** longer than 5ms
- **Memory allocations** larger than 1MB
- **Garbage collection** events
- **File I/O** operations longer than 1ms
- **Timer/scheduling** delays

### Full Profile Script
- All of the above plus:
- **Function call timing** in PDG
- **Detailed system call analysis**
- **Memory allocation patterns**
- **OpenGL operation timing**
- **Periodic sampling** for hitch detection

## Understanding the Output

### Hitch Detection Example
```
HITCH #1: Frame 45 took 23 ms (expected ~16.67ms)
GC START: v8::internal::Heap::CollectGarbage
GC END: v8::internal::Heap::CollectGarbage took 12 ms
SLOW SYSCALL: select took 8 ms
```

### Full Profile Example
```
--- System Call Duration Distribution ---
select
           value  ------------- Distribution ------------- count
               0 |                                         0
               1 |@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 156
               2 |                                         0
               4 |                                         0
               8 |@@@@                                     12
              16 |                                         0
              32 |                                         0
              64 |                                         0
```

## Common Hitch Sources

### 1. Garbage Collection
- **Symptoms**: GC events taking 10-50ms
- **Solutions**: Reduce object allocation, use object pooling

### 2. System Calls
- **Symptoms**: `select`, `poll`, `kevent` taking >5ms
- **Solutions**: Optimize event loop, reduce blocking operations

### 3. Memory Allocation
- **Symptoms**: Large allocations (>1MB) taking time
- **Solutions**: Pre-allocate memory, use memory pools

### 4. File I/O
- **Symptoms**: `open`, `read`, `write` taking >1ms
- **Solutions**: Cache resources, use async I/O

### 5. OpenGL Operations
- **Symptoms**: GL functions taking >5ms
- **Solutions**: Optimize rendering, reduce draw calls

## Troubleshooting

### DTrace Permission Issues
```bash
# Enable DTrace on macOS
sudo /usr/sbin/dtrace -n 'BEGIN { exit(0); }'
```

### No Output
- Make sure PDG is running
- Check that the PID is correct
- Verify DTrace is working: `sudo dtrace -n 'BEGIN { exit(0); }'`

### Too Much Output
- Use the hitch detection script instead of full profiling
- Adjust thresholds in the scripts
- Filter by specific probes

## Advanced Usage

### Custom DTrace Commands

```bash
# Monitor only system calls
sudo dtrace -n 'syscall:::entry /pid == $target/ { @syscalls[probefunc] = count(); } tick-10sec { printa(@syscalls); }' -p <PID>

# Monitor memory allocation
sudo dtrace -n 'pid$target:libsystem_malloc.dylib:malloc:entry { @allocations[arg0] = quantize(arg0); } tick-10sec { printa(@allocations); }' -p <PID>

# Monitor specific functions
sudo dtrace -n 'pid$target:pdg:*:entry { @functions[probefunc] = count(); } tick-10sec { printa(@functions); }' -p <PID>
```

### Integration with GC Monitoring

Combine DTrace with the JavaScript GC monitoring:

1. Start DTrace profiling
2. Start PDG with GC monitoring enabled
3. Correlate DTrace hitches with GC events
4. Identify which GC events cause the biggest hitches

## Performance Optimization Workflow

1. **Baseline**: Run hitch detection to establish baseline
2. **Identify**: Use full profiling to identify bottlenecks
3. **Optimize**: Apply targeted optimizations
4. **Verify**: Re-run profiling to confirm improvements
5. **Iterate**: Continue monitoring during development

This DTrace profiling system will help you identify the exact causes of frame rate hitches in your PDG applications.
