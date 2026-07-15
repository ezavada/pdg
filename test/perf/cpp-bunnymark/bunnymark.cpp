// -----------------------------------------------
// bunnymark.cpp
//
// PDG Bunnymark Performance Test (C++ version)
//
// Classic sprite rendering benchmark that measures
// how many sprites can be rendered while maintaining
// 60 FPS (16.67ms per frame)
//
// -----------------------------------------------

#include "pdg_project.h"
#include "pdg/framework.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace pdg;

// Configuration
const int BUNNIES_PER_BATCH = 100;
const int TARGET_FPS = 60;
const int MIN_FPS = 30;
const float FRAME_TIME_TARGET_MS = 1000.0f / TARGET_FPS;  // 16.67ms
const float FRAME_TIME_MIN_MS = 1000.0f / MIN_FPS;        // 33.33ms
const int STATS_UPDATE_INTERVAL = 500;  // Update stats every 500ms
const int AUTO_ADD_DELAY = 2000;        // Wait 2 seconds between auto-adds

// Physics constants
const float GRAVITY = 0.5f;
const float BOUNCE_DAMPING = 0.95f;

// Window size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Bunny structure
struct Bunny {
    float x;
    float y;
    float speedX;
    float speedY;
    
    Bunny(float initX, float initY, float spdX, float spdY)
        : x(initX), y(initY), speedX(spdX), speedY(spdY) {}
};

// Global state
Port* gPort = nullptr;
Image* gBunnyImage = nullptr;
std::vector<Bunny> gBunnies;

// Stats tracking
int gFrameCount = 0;
float gTotalFrameTime = 0;
float gMaxFrameTime = 0;
float gMinFrameTime = 999999.0f;
int gDroppedFrames = 0;
ms_time gLastStatsUpdate = 0;
float gCurrentFPS = 60.0f;
float gCurrentFrameTimeMs = 0;
std::vector<float> gFrameTimes;
int gMaxBunniesAt60FPS = 0;
int gMaxBunniesAt30FPS = 0;
ms_time gTestStartTime = 0;
ms_time gLastAutoAddTime = 0;
ms_time gLastFrameTime = 0;
bool gAutoAddBunnies = true;
bool gTestRunning = true;

// Function declarations
void addBunnies(int count);
void updateStats(float frameTimeMs);
void printFinalResults();
void saveResultsJSON(const char* filename);
float calculatePercentile(std::vector<float>& sortedArray, float percentile);

// Random float between 0 and 1
inline float randomFloat() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

// Add bunnies to the scene
void addBunnies(int count) {
    for (int i = 0; i < count; ++i) {
        float x = randomFloat() * WINDOW_WIDTH;
        float y = randomFloat() * WINDOW_HEIGHT;
        float speedX = (randomFloat() - 0.5f) * 10.0f;
        float speedY = (randomFloat() - 0.5f) * 10.0f - 5.0f; // Bias upward
        gBunnies.push_back(Bunny(x, y, speedX, speedY));
    }
    std::cout << "Added " << count << " bunnies. Total: " << gBunnies.size() << std::endl;
}

// Update statistics
void updateStats(float frameTimeMs) {
    gFrameCount++;
    gTotalFrameTime += frameTimeMs;
    gMaxFrameTime = std::max(gMaxFrameTime, frameTimeMs);
    gMinFrameTime = std::min(gMinFrameTime, frameTimeMs);
    
    // Track frame time for percentile calculation
    gFrameTimes.push_back(frameTimeMs);
    
    // Count dropped frames (> 16.67ms = below 60 FPS)
    if (frameTimeMs > FRAME_TIME_TARGET_MS) {
        gDroppedFrames++;
    }
    
    // Track max bunnies at different FPS thresholds
    if (frameTimeMs <= FRAME_TIME_TARGET_MS && (int)gBunnies.size() > gMaxBunniesAt60FPS) {
        gMaxBunniesAt60FPS = gBunnies.size();
    }
    if (frameTimeMs <= FRAME_TIME_MIN_MS && (int)gBunnies.size() > gMaxBunniesAt30FPS) {
        gMaxBunniesAt30FPS = gBunnies.size();
    }
}

// Calculate percentile from sorted array
float calculatePercentile(std::vector<float>& sortedArray, float percentile) {
    if (sortedArray.empty()) return 0;
    size_t index = static_cast<size_t>(std::ceil((percentile / 100.0f) * sortedArray.size())) - 1;
    index = std::min(index, sortedArray.size() - 1);
    return sortedArray[index];
}

// Print final results to console
void printFinalResults() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "BUNNYMARK TEST RESULTS (C++)" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Calculate final metrics
    float testDuration = (OS::getMilliseconds() - gTestStartTime) / 1000.0f;
    float meanFrameTime = gTotalFrameTime / gFrameCount;
    
    // Sort frame times for percentiles
    std::sort(gFrameTimes.begin(), gFrameTimes.end());
    float p95 = calculatePercentile(gFrameTimes, 95.0f);
    float p99 = calculatePercentile(gFrameTimes, 99.0f);
    
    std::cout << "\nTest Duration: " << testDuration << " seconds" << std::endl;
    std::cout << "Total Frames: " << gFrameCount << std::endl;
    std::cout << "\nFRAME TIME STATISTICS:" << std::endl;
    std::cout << "  Mean:        " << meanFrameTime << " ms" << std::endl;
    std::cout << "  Min:         " << gMinFrameTime << " ms" << std::endl;
    std::cout << "  Max:         " << gMaxFrameTime << " ms" << std::endl;
    std::cout << "  95th %ile:   " << p95 << " ms" << std::endl;
    std::cout << "  99th %ile:   " << p99 << " ms" << std::endl;
    std::cout << "\nPERFORMANCE METRICS:" << std::endl;
    std::cout << "  Average FPS:           " << (1000.0f / meanFrameTime) << std::endl;
    std::cout << "  Dropped Frames:        " << gDroppedFrames 
              << " (" << ((float)gDroppedFrames / gFrameCount * 100.0f) << "%)" << std::endl;
    std::cout << "  Max Bunnies @ 60 FPS:  " << gMaxBunniesAt60FPS << std::endl;
    std::cout << "  Max Bunnies @ 30 FPS:  " << gMaxBunniesAt30FPS << std::endl;
    std::cout << "  Final Bunny Count:     " << gBunnies.size() << std::endl;
    
    std::cout << "\nKEY METRIC (Bunnymark Score): " << gMaxBunniesAt60FPS << " sprites @ 60 FPS" << std::endl;
    std::cout << std::string(60, '=') << "\n" << std::endl;
}

// Save results as JSON
void saveResultsJSON(const char* filename) {
    float testDuration = (OS::getMilliseconds() - gTestStartTime) / 1000.0f;
    float meanFrameTime = gTotalFrameTime / gFrameCount;
    
    // Sort frame times for percentiles
    std::sort(gFrameTimes.begin(), gFrameTimes.end());
    float p95 = calculatePercentile(gFrameTimes, 95.0f);
    float p99 = calculatePercentile(gFrameTimes, 99.0f);
    
    // Get current timestamp (simplified)
    time_t now = time(0);
    char timestamp[80];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", gmtime(&now));
    
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Warning: Could not save results to file: " << filename << std::endl;
        return;
    }
    
    outfile << "{\n";
    outfile << "  \"testName\": \"PDG Bunnymark (C++)\",\n";
    outfile << "  \"timestamp\": \"" << timestamp << "Z\",\n";
    outfile << "  \"testDurationSeconds\": " << testDuration << ",\n";
    outfile << "  \"totalFrames\": " << gFrameCount << ",\n";
    outfile << "  \"frameTime\": {\n";
    outfile << "    \"meanMs\": " << meanFrameTime << ",\n";
    outfile << "    \"minMs\": " << gMinFrameTime << ",\n";
    outfile << "    \"maxMs\": " << gMaxFrameTime << ",\n";
    outfile << "    \"percentile95Ms\": " << p95 << ",\n";
    outfile << "    \"percentile99Ms\": " << p99 << "\n";
    outfile << "  },\n";
    outfile << "  \"performance\": {\n";
    outfile << "    \"averageFPS\": " << (1000.0f / meanFrameTime) << ",\n";
    outfile << "    \"droppedFrames\": " << gDroppedFrames << ",\n";
    outfile << "    \"droppedFramePercent\": " << ((float)gDroppedFrames / gFrameCount * 100.0f) << ",\n";
    outfile << "    \"maxBunniesAt60FPS\": " << gMaxBunniesAt60FPS << ",\n";
    outfile << "    \"maxBunniesAt30FPS\": " << gMaxBunniesAt30FPS << ",\n";
    outfile << "    \"finalBunnyCount\": " << gBunnies.size() << "\n";
    outfile << "  },\n";
    outfile << "  \"bunnymarkScore\": " << gMaxBunniesAt60FPS << "\n";
    outfile << "}\n";
    
    outfile.close();
    std::cout << "Results saved to: " << filename << std::endl;
}

// Event handler class
class BunnymarkHandler : public IEventHandler {
public:
    virtual bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw() {
        if (inEventType == eventType_PortDraw) {
            if (!gTestRunning) return false;
            
            PortDrawInfo* drawInfo = static_cast<PortDrawInfo*>(inEventData);
            Port* port = drawInfo->port;
            
            ms_time frameStartTime = OS::getMilliseconds();
            gLastFrameTime = frameStartTime;
            
            // Clear background
            pdg::Rect bounds = port->getDrawingArea();
            pdg::Attributes bgAttrs;
            bgAttrs.fillColor(pdg::Color(0.1f, 0.1f, 0.15f, 1.0f));
            port->drawRect(bounds, bgAttrs);
            
            // Get image dimensions once
            float imgWidth = gBunnyImage->getWidth();
            float imgHeight = gBunnyImage->getHeight();
            
            // Update and draw all bunnies
            for (size_t i = 0; i < gBunnies.size(); ++i) {
                Bunny& bunny = gBunnies[i];
                
                // Apply gravity
                bunny.speedY += GRAVITY;
                
                // Update position
                bunny.x += bunny.speedX;
                bunny.y += bunny.speedY;
                
                // Bounce off walls
                if (bunny.x <= 0) {
                    bunny.x = 0;
                    bunny.speedX = std::abs(bunny.speedX) * BOUNCE_DAMPING;
                } else if (bunny.x + imgWidth >= bounds.width()) {
                    bunny.x = bounds.width() - imgWidth;
                    bunny.speedX = -std::abs(bunny.speedX) * BOUNCE_DAMPING;
                }
                
                if (bunny.y <= 0) {
                    bunny.y = 0;
                    bunny.speedY = std::abs(bunny.speedY) * BOUNCE_DAMPING;
                } else if (bunny.y + imgHeight >= bounds.height()) {
                    bunny.y = bounds.height() - imgHeight;
                    bunny.speedY = -std::abs(bunny.speedY) * BOUNCE_DAMPING;
                }
                
                // Draw bunny
                pdg::Point pos(bunny.x, bunny.y);
                pdg::Attributes attrs;
                port->drawImage(gBunnyImage, pos, attrs);
            }
            
            // Draw stats overlay
            pdg::Attributes textAttrs;
            textAttrs.textSize(16);
            textAttrs.textStyle(pdg::textStyle_Plain);
            textAttrs.fillColor(pdg::Color(1.0f, 1.0f, 1.0f, 1.0f));
            
            float y = 20;
            float lineHeight = 20;
            
            port->drawText("PDG BUNNYMARK TEST (C++)", pdg::Point(10, y), textAttrs);
            y += lineHeight * 1.5f;
            
            char buffer[256];
            
            snprintf(buffer, sizeof(buffer), "Bunnies: %zu", gBunnies.size());
            port->drawText(buffer, pdg::Point(10, y), textAttrs);
            y += lineHeight;
            
            snprintf(buffer, sizeof(buffer), "FPS: %.1f", gCurrentFPS);
            port->drawText(buffer, pdg::Point(10, y), textAttrs);
            y += lineHeight;
            
            snprintf(buffer, sizeof(buffer), "Frame Time: %.2f ms", gCurrentFrameTimeMs);
            port->drawText(buffer, pdg::Point(10, y), textAttrs);
            y += lineHeight;
            
            snprintf(buffer, sizeof(buffer), "Max @ 60 FPS: %d", gMaxBunniesAt60FPS);
            port->drawText(buffer, pdg::Point(10, y), textAttrs);
            y += lineHeight;
            
            snprintf(buffer, sizeof(buffer), "Max @ 30 FPS: %d", gMaxBunniesAt30FPS);
            port->drawText(buffer, pdg::Point(10, y), textAttrs);
            y += lineHeight * 1.5f;
            
            if (gAutoAddBunnies) {
                port->drawText("Auto-adding bunnies...", pdg::Point(10, y), textAttrs);
            } else {
                port->drawText("Press SPACE to add bunnies", pdg::Point(10, y), textAttrs);
            }
            y += lineHeight;
            
            port->drawText("Press ESC to quit", pdg::Point(10, y), textAttrs);
            
            // Calculate frame time
            ms_time frameEndTime = OS::getMilliseconds();
            float frameTimeMs = static_cast<float>(frameEndTime - frameStartTime);
            
            // Update stats
            updateStats(frameTimeMs);
            gCurrentFrameTimeMs = frameTimeMs;
            
            // Update current FPS periodically
            if (frameEndTime - gLastStatsUpdate > STATS_UPDATE_INTERVAL) {
                if (frameTimeMs > 0) {
                    gCurrentFPS = 1000.0f / frameTimeMs;
                }
                gLastStatsUpdate = frameEndTime;
            }
            
            // Auto-add bunnies if enabled and enough time has passed
            if (gAutoAddBunnies && (frameEndTime - gLastAutoAddTime) > AUTO_ADD_DELAY) {
                // Only add more if we're still above minimum FPS
                if (gCurrentFrameTimeMs < FRAME_TIME_MIN_MS) {
                    addBunnies(BUNNIES_PER_BATCH);
                    gLastAutoAddTime = frameEndTime;
                } else {
                    std::cout << "Stopped auto-adding: FPS dropped below " << MIN_FPS << std::endl;
                    std::cout << "Run test for a bit longer, then press ESC to see final results" << std::endl;
                    gAutoAddBunnies = false;  // Stop auto-adding
                }
            }
            
            return true;
        }
        else if (inEventType == eventType_KeyPress) {
            KeyPressInfo* keyInfo = static_cast<KeyPressInfo*>(inEventData);
            if (keyInfo->unicode == key_Escape) {
                std::cout << "\nTest stopped by user." << std::endl;
                printFinalResults();
                saveResultsJSON("test/perf/cpp-bunnymark/bunnymark_results.json");
                gTestRunning = false;
                if (gPort) {
                    GraphicsManager::instance().closeGraphicsPort(gPort);
                }
                OS::exit(0);
                return true;
            } else if (keyInfo->unicode == 32) {  // Space key
                addBunnies(BUNNIES_PER_BATCH);
                gLastAutoAddTime = OS::getMilliseconds();  // Reset auto-add timer
                return true;
            }
        }
        else if (inEventType == eventType_Startup) {
            // Handle startup here
            std::cout << "=== PDG BUNNYMARK PERFORMANCE TEST (C++) ===" << std::endl;
            std::cout << "Measuring sprite rendering throughput...\n" << std::endl;
            std::cout << "Auto mode: Will add " << BUNNIES_PER_BATCH << " bunnies every " 
                      << (AUTO_ADD_DELAY/1000) << " seconds until FPS drops below " << TARGET_FPS << std::endl;
            std::cout << "Press ESC to quit and show final results\n" << std::endl;
            
            // Create window
            pdg::Rect windowRect(WINDOW_WIDTH, WINDOW_HEIGHT);
            gPort = GraphicsManager::instance().createWindowPort(windowRect, "PDG Bunnymark Test (C++)");
            
            if (!gPort) {
                std::cerr << "ERROR: Could not create window port" << std::endl;
                OS::exit(1);
                return true;
            }
            
            std::cout << "Window created: " << gPort->getDrawingArea().width() 
                      << "x" << gPort->getDrawingArea().height() << std::endl;
            
            // Load bunny image - try multiple paths
            const char* imagePaths[] = {
                "test/perf/bunnymark/wabbit.png",
                "perf/bunnymark/wabbit.png",
                "bunnymark/wabbit.png",
                "../bunnymark/wabbit.png",
                "wabbit.png"
            };
            
            for (size_t i = 0; i < sizeof(imagePaths) / sizeof(imagePaths[0]); ++i) {
                try {
                    gBunnyImage = Image::createImageFromFile(imagePaths[i]);
                    if (gBunnyImage) {
                        std::cout << "Loaded bunny image from: " << imagePaths[i] << std::endl;
                        std::cout << "Image size: " << gBunnyImage->getWidth() 
                                  << "x" << gBunnyImage->getHeight() << std::endl;
                        break;
                    }
                } catch (...) {
                    // Try next path
                }
            }
            
            if (!gBunnyImage) {
                std::cerr << "ERROR: Could not load bunny image from any path" << std::endl;
                OS::exit(1);
                return true;
            }
            
            // Initialize random seed
            srand(static_cast<unsigned int>(time(NULL)));
            
            // Start with initial batch of bunnies
            addBunnies(BUNNIES_PER_BATCH);
            
            gTestStartTime = OS::getMilliseconds();
            gLastAutoAddTime = gTestStartTime;
            gLastStatsUpdate = gTestStartTime;
            gLastFrameTime = gTestStartTime;
            
            std::cout << "\nTest started. Watch the window for live stats." << std::endl;
            std::cout << "Starting with " << gBunnies.size() << " bunnies...\n" << std::endl;
            
            return true;
        }
        
        return false;
    }
};

// Initialize PDG framework
namespace pdg {

bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool haveMainResourceFile) throw() { return "PDG Bunnymark (C++)"; }
const char* Initializer::getMainResourceFileName() throw() { return NULL; }

bool Initializer::installGlobalHandlers() throw() {
    BunnymarkHandler* handler = new BunnymarkHandler();
    EventManager::instance().addHandler(handler);
    return true;
}

bool Initializer::getGraphicsEnvironmentDimensions(Rect maxWindowDim, Rect maxFullScreenDim,
    long& ioWidth, long& ioHeight, uint8& ioDepth) throw()
{
    ioWidth = WINDOW_WIDTH;
    ioHeight = WINDOW_HEIGHT;
    ioDepth = 32;
    return false;  // windowed mode
}

} // end namespace pdg

