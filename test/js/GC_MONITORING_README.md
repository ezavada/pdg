# PDG Garbage Collection Monitoring

This directory contains tools to monitor garbage collection performance in PDG applications and correlate GC events with frame rate issues.

## Overview

Garbage collection can cause frame rate drops and inconsistent performance in JavaScript applications. This monitoring system helps you:

1. **Track GC Events** - Monitor when and how long garbage collection takes
2. **Correlate with Frame Rate** - See which GC events cause frame drops
3. **Monitor Memory Usage** - Track memory growth and identify potential leaks
4. **Get Actionable Insights** - Receive recommendations for optimization

## Files

- `gc-monitor.js` - Main GC monitoring module
- `gc-test.js` - Standalone test application
- `run-gc-monitor.sh` - Convenience script for running tests
- `main.js` - Your existing test with GC monitoring integrated

## Quick Start

### 1. Basic GC Monitoring

Run your existing test with GC monitoring:

```bash
./pdg test/js/main.js
```

This will automatically track GC events and print a report when the application exits.

### 2. Enhanced Monitoring with V8 Flags

For more detailed monitoring, use V8 flags:

```bash
# Enable manual GC control
./pdg --expose-gc test/js/main.js

# Enable detailed GC logging
./pdg --trace-gc test/js/main.js

# Enable both (recommended for debugging)
./pdg --trace-gc --expose-gc test/js/main.js
```

### 3. Using the Convenience Script

```bash
./test/js/run-gc-monitor.sh
```

This interactive script lets you choose different monitoring options.

## Understanding the Output

### GC Monitor Report

When you run with GC monitoring, you'll see output like:

```
=== GC Monitor Report ===
Duration: 30.45s
Total GC Events: 15
Total GC Time: 245.67ms
GC Time Percentage: 0.81%
Average GC Duration: 16.38ms
Longest GC: 45.23ms
Memory Growth: 2.34MB
Average FPS: 58.7
Frame Rate Drops: 8

GC Events that caused frame drops:
  GC at 12500.45ms caused 23.4ms frame drop
  GC at 18750.12ms caused 18.7ms frame drop
```

### Key Metrics

- **GC Time Percentage**: Percentage of total time spent in garbage collection
- **Longest GC**: The longest single GC event (causes the biggest frame drops)
- **Frame Rate Drops**: Number of frames that took longer than 16ms (60fps threshold)
- **Memory Growth**: Total memory growth during the session

### V8 GC Types

The monitor tracks different types of garbage collection:

- **Scavenge**: Fast, minor GC (usually < 5ms)
- **MarkSweepCompact**: Slower, major GC (can cause frame drops)
- **IncrementalMarking**: Background marking phase
- **WeakPhantomCallbackProcessing**: Processing weak references

## Interpreting Results

### Good Performance
- GC Time Percentage < 1%
- Longest GC < 16ms
- Average FPS > 55
- Few frame rate drops

### Performance Issues
- GC Time Percentage > 5%
- Longest GC > 50ms
- Average FPS < 50
- Many frame drops correlated with GC events

### Common Issues and Solutions

#### High GC Overhead (>5% of time)
**Symptoms**: Frequent GC events, high GC time percentage
**Solutions**:
- Reduce object allocation frequency
- Use object pooling for frequently created objects
- Avoid creating temporary objects in render loops

#### Long GC Pauses (>50ms)
**Symptoms**: Occasional frame drops, inconsistent frame rate
**Solutions**:
- Reduce memory pressure
- Avoid large object allocations
- Consider using `--max-old-space-size` to increase heap size

#### Memory Growth
**Symptoms**: Steady memory increase over time
**Solutions**:
- Check for memory leaks
- Ensure objects are properly disposed
- Use weak references where appropriate

## Integration with Your Code

### Basic Integration

```javascript
const GCMonitor = require('./gc-monitor');

// Create monitor
const monitor = new GCMonitor({
    logToConsole: true,
    trackMemoryUsage: true,
    trackFrameRate: true,
    gcThreshold: 10 // Log GC events longer than 10ms
});

// Start monitoring
monitor.start();

// In your frame update loop
function updateFrame() {
    monitor.onFrame(); // Track frame rate
    // ... your game logic
}

// When shutting down
monitor.stop();
monitor.printReport();
```

### Advanced Configuration

```javascript
const monitor = new GCMonitor({
    logToConsole: false, // Disable console logging
    trackMemoryUsage: true,
    trackFrameRate: true,
    gcThreshold: 5, // More sensitive logging
    memoryThreshold: 512 * 1024 // 512KB memory growth threshold
});

// Get detailed report
const report = monitor.getReport();
console.log('GC caused frame drops:', report.correlation.gcCausedDrops.length);
```

## V8 Flags Reference

### Essential Flags
- `--expose-gc`: Exposes `gc()` function for manual garbage collection
- `--trace-gc`: Logs detailed GC information to console
- `--trace-gc-verbose`: Even more detailed GC logging

### Performance Tuning
- `--max-old-space-size=4096`: Increase heap size to 4GB
- `--optimize-for-size`: Optimize for memory usage over speed
- `--gc-interval=100`: Force GC every 100 allocations

### Debugging
- `--trace-gc-nvp`: Log GC events in name-value pair format
- `--trace-gc-object-stats`: Log object statistics during GC

## Troubleshooting

### GC Monitoring Not Working
1. Check that `perf_hooks` is available (Node.js 8.5+)
2. Ensure you're running with V8 (not JSC)
3. Verify the GC observer is properly set up

### No GC Events Detected
1. Your application might not be creating enough garbage
2. Try running with `--expose-gc` and manually calling `gc()`
3. Check if GC events are being filtered by threshold

### High Memory Usage
1. Look for memory leaks in your application
2. Check if objects are being properly disposed
3. Consider using object pooling for frequently allocated objects

## Best Practices

1. **Monitor Regularly**: Run GC monitoring during development and testing
2. **Set Realistic Thresholds**: Adjust `gcThreshold` based on your performance requirements
3. **Correlate with User Experience**: Focus on GC events that cause noticeable frame drops
4. **Profile Different Scenarios**: Test with different game states and load levels
5. **Use Multiple Tools**: Combine GC monitoring with other profiling tools

## Example Workflow

1. **Baseline**: Run your application with GC monitoring to establish baseline
2. **Identify Issues**: Look for high GC overhead or long pauses
3. **Optimize**: Apply recommended optimizations
4. **Verify**: Re-run monitoring to confirm improvements
5. **Iterate**: Continue monitoring during development

This monitoring system should help you identify and resolve GC-related frame rate issues in your PDG applications.
