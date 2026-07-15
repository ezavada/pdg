// -----------------------------------------------
// GC Monitor for PDG
//
// This module provides comprehensive garbage collection monitoring
// to help identify GC-related frame rate issues.
//
// Usage:
//   const GCMonitor = require('./gc-monitor');
//   const monitor = new GCMonitor();
//   monitor.start();
//   // ... your game code ...
//   monitor.stop();
//   monitor.getReport();
//
// -----------------------------------------------

const { PerformanceObserver, performance } = require('perf_hooks');

class GCMonitor {
    constructor(options = {}) {
        this.options = {
            logToConsole: true,
            trackMemoryUsage: true,
            trackFrameRate: true,
            gcThreshold: 16, // ms - GC events longer than this are logged
            memoryThreshold: 1024 * 1024, // 1MB - memory growth above this is logged
            ...options
        };
        
        this.isRunning = false;
        this.gcEvents = [];
        this.memorySnapshots = [];
        this.frameRateSamples = [];
        this.startTime = 0;
        this.lastMemoryCheck = 0;
        this.lastFrameRateCheck = 0;
        this.frameCount = 0;
        this.lastFrameTime = 0;
		this.pdg = options.pdg;
        
        // GC observer
        this.gcObserver = null;
        
        // Memory tracking interval
        this.memoryInterval = null;
        
        // Frame rate tracking
        this.frameRateInterval = null;
    }
    
    start() {
        if (this.isRunning) return;
        
        this.isRunning = true;
        this.startTime = performance.now();
        this.gcEvents = [];
        this.memorySnapshots = [];
        this.frameRateSamples = [];
        this.frameCount = 0;
        this.lastFrameTime = performance.now();
        
        // Set up GC monitoring
        this._setupGCMonitoring();
        
        // Set up memory monitoring
        if (this.options.trackMemoryUsage) {
            this._setupMemoryMonitoring();
        }
        
        // Set up frame rate monitoring
        if (this.options.trackFrameRate) {
            this._setupFrameRateMonitoring();
        }
        
        if (this.options.logToConsole) {
            console.log('GC Monitor started');
        }
    }
    
    stop() {
        if (!this.isRunning) return;
        
        this.isRunning = false;
        
        // Clean up observers
        if (this.gcObserver) {
            this.gcObserver.disconnect();
            this.gcObserver = null;
        }
        
        if (this.memoryInterval) {
            clearInterval(this.memoryInterval);
            this.memoryInterval = null;
        }
        
        if (this.frameRateInterval) {
            clearInterval(this.frameRateInterval);
            this.frameRateInterval = null;
        }
        
        if (this.options.logToConsole) {
            console.log('GC Monitor stopped');
        }
    }
    
    // Call this from your frame update loop to track frame rate
    onFrame() {
        if (!this.isRunning || !this.options.trackFrameRate) return;
        
        const now = performance.now();
        this.frameCount++;
        
        if (this.lastFrameTime > 0) {
            const frameTime = now - this.lastFrameTime;
            this.frameRateSamples.push({
                timestamp: now - this.startTime,
                pdgTimestampMs: this.pdg.tm.getMilliseconds(),
                frameTime: frameTime,
                fps: 1000 / frameTime
            });
        }
        
        this.lastFrameTime = now;
    }
    
    // Get a comprehensive report
    getReport() {
        const endTime = performance.now();
        const duration = endTime - this.startTime;
        
        // Analyze GC events
        const gcAnalysis = this._analyzeGCEvents();
        
        // Analyze memory usage
        const memoryAnalysis = this._analyzeMemoryUsage();
        
        // Analyze frame rate
        const frameRateAnalysis = this._analyzeFrameRate();
        
        // Correlate GC with frame rate drops
        const correlation = this._correlateGCWithFrameRate();
        
        return {
            duration: duration,
            gcEvents: this.gcEvents,
            gcAnalysis: gcAnalysis,
            memoryAnalysis: memoryAnalysis,
            frameRateAnalysis: frameRateAnalysis,
            correlation: correlation,
            summary: this._generateSummary(gcAnalysis, memoryAnalysis, frameRateAnalysis, correlation)
        };
    }
    
    // Print a formatted report to console
    printReport() {
        const report = this.getReport();
        
        console.log('\n=== GC Monitor Report ===');
        console.log(`Duration: ${(report.duration / 1000).toFixed(2)}s`);
        console.log(`Total GC Events: ${report.gcEvents.length}`);
        console.log(`Total GC Time: ${report.gcAnalysis.totalGCTime.toFixed(2)}ms`);
        console.log(`GC Time Percentage: ${(report.gcAnalysis.gcTimePercentage * 100).toFixed(2)}%`);
        console.log(`Average GC Duration: ${report.gcAnalysis.averageGCDuration.toFixed(2)}ms`);
        console.log(`Longest GC: ${report.gcAnalysis.longestGC.toFixed(2)}ms`);
        console.log(`Memory Growth: ${(report.memoryAnalysis.totalGrowth / 1024 / 1024).toFixed(2)}MB`);
        console.log(`Average FPS: ${report.frameRateAnalysis.averageFPS.toFixed(2)}`);
        console.log(`Frame Rate Drops: ${report.frameRateAnalysis.drops.length}`);
        
        if (report.correlation.gcCausedDrops.length > 0) {
            console.log(`\nGC Events that caused frame drops:`);
            report.correlation.gcCausedDrops.forEach(drop => {
                console.log(`  GC at ${drop.gcTime.toFixed(2)}ms (pdg ${drop.pdgTimestampMs}) caused ${drop.frameDrop}ms frame drop`);
            });
        }
        
        console.log('\n=== End Report ===\n');
    }
    
    _setupGCMonitoring() {
        try {
            this.gcObserver = new PerformanceObserver((list) => {
                const entries = list.getEntries();
                entries.forEach(entry => {
                    const gcEvent = {
                        timestamp: entry.startTime,
                        duration: entry.duration,
                        kind: entry.detail ? entry.detail.kind : entry.kind,
                        flags: entry.detail ? entry.detail.flags : entry.flags,
                        detail: entry.detail,
                        pdgTimestampMs: this.pdg ? this.pdg.tm.getMilliseconds() : Date.now()
                    };
                    
                    this.gcEvents.push(gcEvent);
                    
                    if (this.options.logToConsole && entry.duration > this.options.gcThreshold) {
                        console.log(`GC Event: ${entry.duration.toFixed(2)}ms (${this._getGCTypeName(entry.kind)})`);
                    }
                });
            });
            
            this.gcObserver.observe({ entryTypes: ['gc'] });
        } catch (error) {
            console.warn('GC monitoring not available:', error.message);
        }
    }
    
    _setupMemoryMonitoring() {
        this.memoryInterval = setInterval(() => {
            const memUsage = process.memoryUsage();
            const now = performance.now();
            
            this.memorySnapshots.push({
                timestamp: now - this.startTime,
                rss: memUsage.rss,
                heapUsed: memUsage.heapUsed,
                heapTotal: memUsage.heapTotal,
                external: memUsage.external
            });
            
            this.lastMemoryCheck = now;
        }, 1000); // Check every second
    }
    
    _setupFrameRateMonitoring() {
        this.frameRateInterval = setInterval(() => {
            // This will be populated by onFrame() calls
        }, 100); // Sample every 100ms
    }
    
    _analyzeGCEvents() {
        if (this.gcEvents.length === 0) {
            return {
                totalGCTime: 0,
                gcTimePercentage: 0,
                averageGCDuration: 0,
                longestGC: 0,
                gcCountByType: {}
            };
        }
        
        const totalGCTime = this.gcEvents.reduce((sum, event) => sum + event.duration, 0);
        const gcTimePercentage = totalGCTime / (performance.now() - this.startTime);
        const averageGCDuration = totalGCTime / this.gcEvents.length;
        const longestGC = Math.max(...this.gcEvents.map(e => e.duration));
        
        const gcCountByType = {};
        this.gcEvents.forEach(event => {
            const type = this._getGCTypeName(event.kind);
            gcCountByType[type] = (gcCountByType[type] || 0) + 1;
        });
        
        return {
            totalGCTime,
            gcTimePercentage,
            averageGCDuration,
            longestGC,
            gcCountByType
        };
    }
    
    _analyzeMemoryUsage() {
        if (this.memorySnapshots.length < 2) {
            return {
                totalGrowth: 0,
                peakUsage: 0,
                averageUsage: 0
            };
        }
        
        const first = this.memorySnapshots[0];
        const last = this.memorySnapshots[this.memorySnapshots.length - 1];
        const totalGrowth = last.heapUsed - first.heapUsed;
        const peakUsage = Math.max(...this.memorySnapshots.map(s => s.heapUsed));
        const averageUsage = this.memorySnapshots.reduce((sum, s) => sum + s.heapUsed, 0) / this.memorySnapshots.length;
        
        return {
            totalGrowth,
            peakUsage,
            averageUsage
        };
    }
    
    _analyzeFrameRate() {
        if (this.frameRateSamples.length === 0) {
            return {
                averageFPS: 0,
                drops: [],
                minFPS: 0,
                maxFPS: 0
            };
        }
        
        const fpsValues = this.frameRateSamples.map(s => s.fps);
        const averageFPS = fpsValues.reduce((sum, fps) => sum + fps, 0) / fpsValues.length;
        const minFPS = Math.min(...fpsValues);
        const maxFPS = Math.max(...fpsValues);
        
        // Find frame rate drops (frames that took longer than 16ms = 60fps threshold)
        const drops = this.frameRateSamples
            .filter(sample => sample.frameTime > 16)
            .map(sample => ({
                timestamp: sample.timestamp,
                pdgTimestampMs: sample.pdgTimestampMs,
                frameTime: sample.frameTime,
                fps: sample.fps
            }));
        
        return {
            averageFPS,
            drops,
            minFPS,
            maxFPS
        };
    }
    
    _correlateGCWithFrameRate() {
        const gcCausedDrops = [];
        
        // For each GC event, check if there were frame drops around that time
        this.gcEvents.forEach(gcEvent => {
            const gcTime = gcEvent.timestamp;
            const gcEndTime = gcTime + gcEvent.duration;
            
            // Look for frame drops that occurred during or immediately after GC
            const relatedDrops = this.frameRateSamples.filter(sample => {
                const sampleTime = sample.timestamp;
                return sampleTime >= gcTime - 50 && sampleTime <= gcEndTime + 100;
            });
            
            if (relatedDrops.length > 0) {
                const worstDrop = relatedDrops.reduce((worst, drop) => 
                    drop.frameTime > worst.frameTime ? drop : worst
                );
                
                gcCausedDrops.push({
                    gcTime: gcTime,
                    pdgTimestampMs: gcEvent.pdgTimestampMs,
                    gcDuration: gcEvent.duration,
                    frameDrop: worstDrop.frameTime,
                    frameDropFPS: worstDrop.fps
                });
            }
        });
        
        return {
            gcCausedDrops
        };
    }
    
    _generateSummary(gcAnalysis, memoryAnalysis, frameRateAnalysis, correlation) {
        const issues = [];
        
        if (gcAnalysis.gcTimePercentage > 0.1) {
            issues.push(`High GC overhead: ${(gcAnalysis.gcTimePercentage * 100).toFixed(1)}% of time spent in GC`);
        }
        
        if (gcAnalysis.longestGC > 50) {
            issues.push(`Long GC pauses: longest GC was ${gcAnalysis.longestGC.toFixed(1)}ms`);
        }
        
        if (memoryAnalysis.totalGrowth > 10 * 1024 * 1024) {
            issues.push(`Memory growth: ${(memoryAnalysis.totalGrowth / 1024 / 1024).toFixed(1)}MB growth detected`);
        }
        
        if (frameRateAnalysis.averageFPS < 50) {
            issues.push(`Low frame rate: average ${frameRateAnalysis.averageFPS.toFixed(1)} FPS`);
        }
        
        if (correlation.gcCausedDrops.length > 0) {
            issues.push(`${correlation.gcCausedDrops.length} frame drops correlated with GC events`);
        }
        
        return {
            issues,
            recommendations: this._generateRecommendations(issues)
        };
    }
    
    _generateRecommendations(issues) {
        const recommendations = [];
        
        if (issues.some(i => i.includes('High GC overhead'))) {
            recommendations.push('Consider reducing object allocation frequency');
            recommendations.push('Use object pooling for frequently created objects');
            recommendations.push('Avoid creating temporary objects in render loops');
        }
        
        if (issues.some(i => i.includes('Memory growth'))) {
            recommendations.push('Check for memory leaks in your application');
            recommendations.push('Ensure objects are properly disposed when no longer needed');
            recommendations.push('Use weak references where appropriate');
        }
        
        if (issues.some(i => i.includes('frame drops'))) {
            recommendations.push('Move heavy computations outside the render loop');
            recommendations.push('Consider using Web Workers for background processing');
            recommendations.push('Optimize rendering to reduce per-frame work');
        }
        
        return recommendations;
    }
    
    _getGCTypeName(kind) {
        const types = {
            1: 'Scavenge',
            2: 'MarkSweepCompact',
            4: 'IncrementalMarking',
            8: 'WeakPhantomCallbackProcessing',
            15: 'All'
        };
        return types[kind] || `Unknown(${kind})`;
    }
}

module.exports = GCMonitor;
