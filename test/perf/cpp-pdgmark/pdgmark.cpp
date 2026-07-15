// -----------------------------------------------
// pdgmark.cpp
//
// PDG PDGMark Performance Test (C++ version)
//
// Tests 5 different aspects of 2D rendering:
// 1. Bitmap Rendering - Sprite/image drawing
// 2. Line Drawing - Lines, arcs, curves
// 3. Alpha Blending - Transparency and blend modes
// 4. Polygon Fills - Complex shapes with fills/gradients
// 5. Text Rendering - Text drawing with various styles
//
// Each test progressively adds complexity until 60 FPS
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
const int BASE_OBJECTS = 50;            // Base number of objects to add
const int TARGET_FPS = 60;
const float FRAME_TIME_TARGET_MS = 1000.0f / TARGET_FPS;
const int STATS_UPDATE_INTERVAL = 500;  // Update stats every 500ms
const int MIN_FRAMES_PER_TEST = 60;     // Minimum frames before allowing test completion

// Calculate delay between object additions based on current FPS
int calculateAutoAddDelay(float currentFPS) {
    if (currentFPS < 80) {
        return 2000;  // 2 seconds - near threshold, let it stabilize
    } else {
        return 1000;  // 1 second - add quickly
    }
}

// Calculate how many objects to add based on current FPS
int calculateObjectsToAdd(float currentFPS) {
    if (currentFPS > 500) {
        return 2500;  // Extremely fast, ramp up aggressively
    } else if (currentFPS > 300) {
        return 2000;  // Very fast
    } else if (currentFPS > 200) {
        return 1500;  // Fast
    } else if (currentFPS > 100) {
        return 750;   // Moderate speed
    } else if (currentFPS > 70) {
        return 250;   // Approaching threshold
    } else {
        return 50;    // Near threshold, add carefully
    }
}

// Text rendering: fixed 50 objects every 2 seconds (no ramping needed)
const int TEXT_OBJECTS_PER_BATCH = 50;
const int TEXT_AUTO_ADD_DELAY = 2000;

// Test weights (complexity multipliers for scoring)
const float WEIGHT_BITMAP = 1.0f;
const float WEIGHT_DRAWING = 1.2f;
const float WEIGHT_ALPHA = 1.3f;
const float WEIGHT_POLYGON = 1.5f;
const float WEIGHT_TEXT = 1.4f;

// Window size
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

// ============================================
// BASE TEST OBJECT
// ============================================

class TestObject {
public:
    virtual ~TestObject() {}
    virtual void update() = 0;
    virtual void draw(Port* port) = 0;
};

// ============================================
// TEST 1: BITMAP RENDERING
// ============================================

class BitmapObject : public TestObject {
public:
    float x, y;
    float rotation;
    float rotationSpeed;
    float scale;
    Image* image;
    
    BitmapObject(Image* img, const pdg::Rect& bounds) : image(img) {
        x = (rand() / (float)RAND_MAX) * (bounds.width() - img->getWidth());
        y = (rand() / (float)RAND_MAX) * (bounds.height() - img->getHeight());
        rotation = (rand() / (float)RAND_MAX) * M_PI * 2.0f;
        rotationSpeed = ((rand() / (float)RAND_MAX) - 0.5f) * 0.1f;
        scale = 0.5f + (rand() / (float)RAND_MAX) * 0.5f;
    }
    
    virtual void update() {
        rotation += rotationSpeed;
    }
    
    virtual void draw(Port* port) {
        pdg::Point center(x + image->getWidth() / 2.0f, y + image->getHeight() / 2.0f);
        Attributes attrs;
        attrs.rotation(rotation, center);
        attrs.scale(scale, scale);
        port->drawImage(image, pdg::Point(x, y), attrs);
    }
};

// ============================================
// TEST 2: LINE DRAWING
// ============================================

class DrawingObject : public TestObject {
public:
    int type;  // 0=line, 1=arc, 2=spline, 3=ellipse
    float x, y;
    Color color;
    float thickness;
    float size;
    float angle;
    float angleSpeed;
    
    DrawingObject(const pdg::Rect& bounds) {
        type = rand() % 4;
        x = (rand() / (float)RAND_MAX) * bounds.width();
        y = (rand() / (float)RAND_MAX) * bounds.height();
        color = Color(rand() / (float)RAND_MAX, 
                     rand() / (float)RAND_MAX, 
                     rand() / (float)RAND_MAX, 0.8f);
        thickness = 1.0f + (rand() / (float)RAND_MAX) * 3.0f;
        size = 20.0f + (rand() / (float)RAND_MAX) * 80.0f;
        angle = (rand() / (float)RAND_MAX) * M_PI * 2.0f;
        angleSpeed = ((rand() / (float)RAND_MAX) - 0.5f) * 0.05f;
    }
    
    virtual void update() {
        angle += angleSpeed;
    }
    
    virtual void draw(Port* port) {
        Attributes attrs;
        attrs.lineColor(color);
        attrs.lineThickness(thickness);
        
        float cx = x;
        float cy = y;
        float s = size;
        
        switch(type) {
            case 0: { // Line
                float x1 = cx + std::cos(angle) * s;
                float y1 = cy + std::sin(angle) * s;
                float x2 = cx - std::cos(angle) * s;
                float y2 = cy - std::sin(angle) * s;
                port->drawLine(pdg::Point(x1, y1), pdg::Point(x2, y2), attrs);
                break;
            }
            case 1: { // Arc
                port->drawArc(pdg::Point(cx, cy), s, s, angle, angle + M_PI * 1.5f, attrs);
                break;
            }
            case 2: { // Spline
                pdg::Spline spline;
                spline.addPoint(pdg::Point(cx, cy));
                spline.addPoint(pdg::Point(cx + s * std::cos(angle), cy + s * std::sin(angle)));
                spline.addPoint(pdg::Point(cx + s * std::cos(angle + 1), cy + s * std::sin(angle + 1)));
                spline.addPoint(pdg::Point(cx, cy + s));
                port->drawSpline(spline, attrs);
                break;
            }
            case 3: { // Ellipse
                port->drawEllipse(pdg::Point(cx, cy), s/2, s/2, attrs);
                break;
            }
        }
    }
};

// ============================================
// TEST 3: ALPHA BLENDING
// ============================================

class AlphaObject : public TestObject {
public:
    int type;  // 0=rect, 1=ellipse
    float x, y;
    float width, height;
    Color color;
    float opacity;
    int blendMode;
    float rotation;
    float rotationSpeed;
    
    AlphaObject(const pdg::Rect& bounds) {
        type = rand() % 2;
        x = (rand() / (float)RAND_MAX) * bounds.width();
        y = (rand() / (float)RAND_MAX) * bounds.height();
        width = 40.0f + (rand() / (float)RAND_MAX) * 80.0f;
        height = 40.0f + (rand() / (float)RAND_MAX) * 80.0f;
        color = Color(rand() / (float)RAND_MAX, 
                     rand() / (float)RAND_MAX, 
                     rand() / (float)RAND_MAX, 1.0f);
        opacity = 0.3f + (rand() / (float)RAND_MAX) * 0.5f;
        blendMode = rand() % 6;  // All blend modes
        rotation = (rand() / (float)RAND_MAX) * M_PI * 2.0f;
        rotationSpeed = ((rand() / (float)RAND_MAX) - 0.5f) * 0.02f;
    }
    
    virtual void update() {
        rotation += rotationSpeed;
    }
    
    virtual void draw(Port* port) {
        pdg::Point center(x + width/2, y + height/2);
        Attributes attrs;
        attrs.fillColor(color);
        attrs.fillOpacity(opacity);
        attrs.blendMode((BlendMode)blendMode);
        attrs.rotation(rotation, center);
        
        if (type == 0) {
            pdg::Rect rect(x, y, x + width, y + height);
            port->drawRect(rect, attrs);
        } else {
            port->drawEllipse(pdg::Point(x + width/2, y + height/2), width/2, height/2, attrs);
        }
    }
};

// ============================================
// TEST 4: POLYGON FILLS
// ============================================

class PolygonObject : public TestObject {
public:
    float centerX, centerY;
    int sides;
    float radius;
    float rotation;
    float rotationSpeed;
    bool useGradient;
    Color color;
    Color color1, color2;
    
    PolygonObject(const pdg::Rect& bounds) {
        centerX = (rand() / (float)RAND_MAX) * bounds.width();
        centerY = (rand() / (float)RAND_MAX) * bounds.height();
        sides = 3 + (rand() % 5);  // 3-7 sides
        radius = 20.0f + (rand() / (float)RAND_MAX) * 50.0f;
        rotation = (rand() / (float)RAND_MAX) * M_PI * 2.0f;
        rotationSpeed = ((rand() / (float)RAND_MAX) - 0.5f) * 0.03f;
        useGradient = (rand() / (float)RAND_MAX) > 0.5f;
        
        if (useGradient) {
            color1 = Color(rand() / (float)RAND_MAX, 
                          rand() / (float)RAND_MAX, 
                          rand() / (float)RAND_MAX, 1.0f);
            color2 = Color(rand() / (float)RAND_MAX, 
                          rand() / (float)RAND_MAX, 
                          rand() / (float)RAND_MAX, 1.0f);
        } else {
            color = Color(rand() / (float)RAND_MAX, 
                         rand() / (float)RAND_MAX, 
                         rand() / (float)RAND_MAX, 0.8f);
        }
    }
    
    virtual void update() {
        rotation += rotationSpeed;
    }
    
    virtual void draw(Port* port) {
        pdg::Polygon polygon;
        
        for (int i = 0; i < sides; i++) {
            float angle = rotation + (i / (float)sides) * M_PI * 2.0f;
            float x = centerX + std::cos(angle) * radius;
            float y = centerY + std::sin(angle) * radius;
            polygon.addPoint(pdg::Point(x, y));
        }
        
        Attributes attrs;
        attrs.lineColor(Color(0.0f, 0.0f, 0.0f, 0.5f));
        attrs.lineThickness(1);
        
        if (useGradient) {
            pdg::Point start(centerX - radius, centerY);
            pdg::Point end(centerX + radius, centerY);
            attrs.fillGradient(start, color1, end, color2);
        } else {
            attrs.fillColor(color);
        }
        
        port->drawPolygon(polygon, attrs);
    }
};

// ============================================
// TEST 5: TEXT RENDERING
// ============================================

class TextObject : public TestObject {
public:
    float x, y;
    std::string text;
    int size;
    Color color;
    float rotation;
    float rotationSpeed;
    int style;
    
    TextObject(const pdg::Rect& bounds) {
        x = (rand() / (float)RAND_MAX) * bounds.width();
        y = (rand() / (float)RAND_MAX) * bounds.height();
        
        std::ostringstream oss;
        oss << "PDGMark " << (rand() % 1000);
        text = oss.str();
        
        size = 12 + (rand() % 24);
        color = Color(rand() / (float)RAND_MAX, 
                     rand() / (float)RAND_MAX, 
                     rand() / (float)RAND_MAX, 0.9f);
        rotation = ((rand() / (float)RAND_MAX) - 0.5f) * 0.5f;
        rotationSpeed = ((rand() / (float)RAND_MAX) - 0.5f) * 0.01f;
        
        int styles[] = {textStyle_Plain, textStyle_Bold, textStyle_Italic};
        style = styles[rand() % 3];
    }
    
    virtual void update() {
        rotation += rotationSpeed;
    }
    
    virtual void draw(Port* port) {
        pdg::Point center(x, y);
        Attributes attrs;
        attrs.textSize(size);
        attrs.textStyle(style);
        attrs.fillColor(color);
        attrs.rotation(rotation, center);
        
        port->drawText(text.c_str(), pdg::Point(x, y), attrs);
    }
};

// ============================================
// GLOBAL STATE
// ============================================

struct TestDefinition {
    std::string name;
    std::string title;
    float weight;
    int testIndex;
};

TestDefinition gTests[] = {
    {"bitmap", "Bitmap Rendering", WEIGHT_BITMAP, 0},
    {"drawing", "Line Drawing", WEIGHT_DRAWING, 1},
    {"alpha", "Alpha Blending", WEIGHT_ALPHA, 2},
    {"polygon", "Polygon Fills", WEIGHT_POLYGON, 3},
    {"text", "Text Rendering", WEIGHT_TEXT, 4}
};
const int NUM_TESTS = 5;

Port* gPort = nullptr;
Image* gTestImage = nullptr;
std::vector<TestObject*> gTestObjects;

int gCurrentTestIndex = 0;
ms_time gTestStartTime = 0;
ms_time gLastAutoAddTime = 0;
ms_time gLastStatsUpdate = 0;
int gTestFrameCount = 0;
bool gTestComplete = false;

// Stats tracking
int gFrameCount = 0;
float gTotalFrameTime = 0;
float gMaxFrameTime = 0;
float gMinFrameTime = 999999.0f;
std::vector<float> gFrameTimes;
float gCurrentFPS = 60.0f;
float gCurrentFrameTimeMs = 0;
int gObjectsAt60FPS = 0;

// Test results
struct TestResult {
    std::string testName;
    std::string testTitle;
    float weight;
    int objectsAt60FPS;
    int score;
    float durationSeconds;
    int totalFrames;
    float meanFrameTimeMs;
    float minFrameTimeMs;
    float maxFrameTimeMs;
    float percentile95Ms;
    float percentile99Ms;
    float averageFPS;
};

std::vector<TestResult> gAllTestResults;
ms_time gGlobalStartTime = 0;
std::string gTestStartTimestamp;

// ============================================
// HELPER FUNCTIONS
// ============================================

inline float randomFloat() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float calculatePercentile(std::vector<float>& sortedArray, float percentile) {
    if (sortedArray.empty()) return 0;
    size_t index = static_cast<size_t>(std::ceil((percentile / 100.0f) * sortedArray.size())) - 1;
    index = std::min(index, sortedArray.size() - 1);
    return sortedArray[index];
}

void updateStats(float frameTimeMs) {
    gFrameCount++;
    gTestFrameCount++;
    gTotalFrameTime += frameTimeMs;
    gMaxFrameTime = std::max(gMaxFrameTime, frameTimeMs);
    gMinFrameTime = std::min(gMinFrameTime, frameTimeMs);
    gFrameTimes.push_back(frameTimeMs);
    
    // Track max objects at 60 FPS
    if (frameTimeMs <= FRAME_TIME_TARGET_MS && (int)gTestObjects.size() > gObjectsAt60FPS) {
        gObjectsAt60FPS = gTestObjects.size();
    }
}

void resetTestStats() {
    gFrameCount = 0;
    gTestFrameCount = 0;
    gTotalFrameTime = 0;
    gMaxFrameTime = 0;
    gMinFrameTime = 999999.0f;
    gFrameTimes.clear();
    gCurrentFPS = 60.0f;
    gCurrentFrameTimeMs = 0;
    gObjectsAt60FPS = 0;
    gTestStartTime = OS::getMilliseconds();
    gLastAutoAddTime = gTestStartTime;
    gLastStatsUpdate = gTestStartTime;
    gTestComplete = false;
}

void addTestObjects(int count, const pdg::Rect& bounds) {
    TestDefinition& test = gTests[gCurrentTestIndex];
    
    for (int i = 0; i < count; i++) {
        TestObject* obj = nullptr;
        
        switch(gCurrentTestIndex) {
            case 0: // Bitmap
                obj = new BitmapObject(gTestImage, bounds);
                break;
            case 1: // Drawing
                obj = new DrawingObject(bounds);
                break;
            case 2: // Alpha
                obj = new AlphaObject(bounds);
                break;
            case 3: // Polygon
                obj = new PolygonObject(bounds);
                break;
            case 4: // Text
                obj = new TextObject(bounds);
                break;
        }
        
        if (obj) {
            gTestObjects.push_back(obj);
        }
    }
}

void saveTestResults() {
    float testDuration = (OS::getMilliseconds() - gTestStartTime) / 1000.0f;
    float meanFrameTime = gTotalFrameTime / gFrameCount;
    
    std::sort(gFrameTimes.begin(), gFrameTimes.end());
    float p95 = calculatePercentile(gFrameTimes, 95.0f);
    float p99 = calculatePercentile(gFrameTimes, 99.0f);
    
    TestDefinition& test = gTests[gCurrentTestIndex];
    int score = static_cast<int>(gObjectsAt60FPS * test.weight);
    
    TestResult result;
    result.testName = test.name;
    result.testTitle = test.title;
    result.weight = test.weight;
    result.objectsAt60FPS = gObjectsAt60FPS;
    result.score = score;
    result.durationSeconds = testDuration;
    result.totalFrames = gFrameCount;
    result.meanFrameTimeMs = meanFrameTime;
    result.minFrameTimeMs = gMinFrameTime;
    result.maxFrameTimeMs = gMaxFrameTime;
    result.percentile95Ms = p95;
    result.percentile99Ms = p99;
    result.averageFPS = 1000.0f / meanFrameTime;
    
    gAllTestResults.push_back(result);
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "TEST " << (gCurrentTestIndex + 1) << " COMPLETE: " << test.title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Objects at 60 FPS: " << gObjectsAt60FPS << std::endl;
    std::cout << "Weight: " << test.weight << "x" << std::endl;
    std::cout << "Test Score: " << score << std::endl;
    std::cout << "Duration: " << testDuration << "s" << std::endl;
    std::cout << "Avg FPS: " << result.averageFPS << std::endl;
    std::cout << "Frame Time: " << meanFrameTime << "ms (95th: " << p95 << "ms)" << std::endl;
    std::cout << std::string(60, '=') << "\n" << std::endl;
}

void printFinalResults() {
    float totalDuration = (OS::getMilliseconds() - gGlobalStartTime) / 1000.0f;
    int compositeScore = 0;
    
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "PDGMARK TEST COMPLETE - ALL TESTS FINISHED (C++)" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "\nINDIVIDUAL TEST RESULTS:\n" << std::endl;
    
    for (size_t i = 0; i < gAllTestResults.size(); i++) {
        TestResult& result = gAllTestResults[i];
        compositeScore += result.score;
        std::cout << (i+1) << ". " << result.testTitle << std::endl;
        std::cout << "   Objects @ 60 FPS: " << result.objectsAt60FPS << std::endl;
        std::cout << "   Weight: " << result.weight << "x" << std::endl;
        std::cout << "   Score: " << result.score << std::endl;
        std::cout << "   Avg FPS: " << result.averageFPS << std::endl;
        std::cout << "   Frame Time: " << result.meanFrameTimeMs << "ms" << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "COMPOSITE SCORE: " << compositeScore << std::endl;
    std::cout << "Total Duration: " << totalDuration << " seconds" << std::endl;
    std::cout << std::string(70, '=') << "\n" << std::endl;
}

void saveResultsJSON(const char* filename) {
    float totalDuration = (OS::getMilliseconds() - gGlobalStartTime) / 1000.0f;
    int compositeScore = 0;
    
    for (size_t i = 0; i < gAllTestResults.size(); i++) {
        compositeScore += gAllTestResults[i].score;
    }
    
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Warning: Could not save results to file: " << filename << std::endl;
        return;
    }
    
    outfile << "{\n";
    outfile << "  \"testName\": \"PDG PDGMark (C++)\",\n";
    outfile << "  \"timestamp\": \"" << gTestStartTimestamp << "\",\n";
    outfile << "  \"totalDurationSeconds\": " << totalDuration << ",\n";
    outfile << "  \"compositeScore\": " << compositeScore << ",\n";
    outfile << "  \"tests\": {\n";
    
    for (size_t i = 0; i < gAllTestResults.size(); i++) {
        TestResult& result = gAllTestResults[i];
        outfile << "    \"" << result.testName << "\": {\n";
        outfile << "      \"testName\": \"" << result.testName << "\",\n";
        outfile << "      \"testTitle\": \"" << result.testTitle << "\",\n";
        outfile << "      \"weight\": " << result.weight << ",\n";
        outfile << "      \"objectsAt60FPS\": " << result.objectsAt60FPS << ",\n";
        outfile << "      \"score\": " << result.score << ",\n";
        outfile << "      \"durationSeconds\": " << result.durationSeconds << ",\n";
        outfile << "      \"totalFrames\": " << result.totalFrames << ",\n";
        outfile << "      \"frameTime\": {\n";
        outfile << "        \"meanMs\": " << result.meanFrameTimeMs << ",\n";
        outfile << "        \"minMs\": " << result.minFrameTimeMs << ",\n";
        outfile << "        \"maxMs\": " << result.maxFrameTimeMs << ",\n";
        outfile << "        \"percentile95Ms\": " << result.percentile95Ms << ",\n";
        outfile << "        \"percentile99Ms\": " << result.percentile99Ms << "\n";
        outfile << "      },\n";
        outfile << "      \"averageFPS\": " << result.averageFPS << "\n";
        outfile << "    }";
        if (i < gAllTestResults.size() - 1) {
            outfile << ",";
        }
        outfile << "\n";
    }
    
    outfile << "  }\n";
    outfile << "}\n";
    
    outfile.close();
    std::cout << "Results saved to: " << filename << std::endl;
    std::cout << "\nTo compare with baseline:" << std::endl;
    std::cout << "  node test/perf/pdgmark/compare_results.js\n" << std::endl;
}

void cleanupTestObjects() {
    for (size_t i = 0; i < gTestObjects.size(); i++) {
        delete gTestObjects[i];
    }
    gTestObjects.clear();
}

void startNextTest();

// ============================================
// EVENT HANDLER
// ============================================

class PDGMarkHandler : public IEventHandler {
public:
    virtual bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw() {
        if (inEventType == eventType_PortDraw) {
            PortDrawInfo* drawInfo = static_cast<PortDrawInfo*>(inEventData);
            Port* port = drawInfo->port;
            
            ms_time frameStartTime = OS::getMilliseconds();
            
            // Clear background
            pdg::Rect bounds = port->getDrawingArea();
            Attributes bgAttrs;
            bgAttrs.fillColor(Color(0.05f, 0.05f, 0.08f, 1.0f));
            port->drawRect(bounds, bgAttrs);
            
            // Run current test
            if (gCurrentTestIndex < NUM_TESTS) {
                for (size_t i = 0; i < gTestObjects.size(); i++) {
                    gTestObjects[i]->update();
                    gTestObjects[i]->draw(port);
                }
            }
            
            // Draw stats overlay
            Attributes textAttrs;
            textAttrs.textSize(16);
            textAttrs.textStyle(textStyle_Plain);
            textAttrs.fillColor(Color(0.3f, 1.0f, 0.3f, 1.0f));  // Bright green for contrast
            
            float y = 20;
            float lineHeight = 20;
            
            port->drawText("PDG PDGMARK TEST (C++)", pdg::Point(10, y), textAttrs);
            y += lineHeight * 1.5f;
            
            if (gCurrentTestIndex < NUM_TESTS) {
                TestDefinition& test = gTests[gCurrentTestIndex];
                char buffer[256];
                
                snprintf(buffer, sizeof(buffer), "Test %d/%d: %s", 
                        gCurrentTestIndex + 1, NUM_TESTS, test.title.c_str());
                port->drawText(buffer, pdg::Point(10, y), textAttrs);
                y += lineHeight;
                
                snprintf(buffer, sizeof(buffer), "Objects: %zu", gTestObjects.size());
                port->drawText(buffer, pdg::Point(10, y), textAttrs);
                y += lineHeight;
                
                snprintf(buffer, sizeof(buffer), "FPS: %.1f", gCurrentFPS);
                port->drawText(buffer, pdg::Point(10, y), textAttrs);
                y += lineHeight;
                
                snprintf(buffer, sizeof(buffer), "Frame Time: %.2f ms", gCurrentFrameTimeMs);
                port->drawText(buffer, pdg::Point(10, y), textAttrs);
                y += lineHeight;
                
                snprintf(buffer, sizeof(buffer), "Objects @ 60 FPS: %d", gObjectsAt60FPS);
                port->drawText(buffer, pdg::Point(10, y), textAttrs);
                y += lineHeight * 1.5f;
                
                if (!gTestComplete) {
                    port->drawText("Adding objects...", pdg::Point(10, y), textAttrs);
                } else {
                    port->drawText("Test stabilizing...", pdg::Point(10, y), textAttrs);
                }
                y += lineHeight;
            }
            
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
            
            // Auto-add objects if test not complete and enough time has passed
            bool isTextTest = (gTests[gCurrentTestIndex].name == "text");
            int currentDelay = isTextTest ? TEXT_AUTO_ADD_DELAY : calculateAutoAddDelay(gCurrentFPS);
            
            if (!gTestComplete && (frameEndTime - gLastAutoAddTime) > currentDelay) {
                // Only add more if we're still at target FPS
                if (gCurrentFPS >= TARGET_FPS) {
                    pdg::Rect bounds = port->getDrawingArea();
                    
                    // Text uses fixed batch size, others use adaptive scaling
                    int count = isTextTest ? TEXT_OBJECTS_PER_BATCH : calculateObjectsToAdd(gCurrentFPS);
                    
                    addTestObjects(count, bounds);
                    gLastAutoAddTime = frameEndTime;
                } else if (gTestFrameCount >= MIN_FRAMES_PER_TEST) {
                    // Test complete - save results and move to next test
                    gTestComplete = true;
                    std::cout << "Test threshold reached. Completing test..." << std::endl;
                    
                    // Save and proceed to next test
                    saveTestResults();
                    cleanupTestObjects();
                    gCurrentTestIndex++;
                    
                    if (gCurrentTestIndex < NUM_TESTS) {
                        startNextTest();
                    } else {
                        // All tests complete
                        printFinalResults();
                        saveResultsJSON("test/perf/cpp-pdgmark/pdgmark_results.json");
                        
                        if (gPort) {
                            GraphicsManager::instance().closeGraphicsPort(gPort);
                        }
                        OS::exit(0);
                    }
                }
            }
            
            return true;
        }
        else if (inEventType == eventType_KeyPress) {
            KeyPressInfo* keyInfo = static_cast<KeyPressInfo*>(inEventData);
            if (keyInfo->unicode == key_Escape) {
                std::cout << "\nTest stopped by user." << std::endl;
                if (!gAllTestResults.empty()) {
                    printFinalResults();
                    saveResultsJSON("test/perf/cpp-pdgmark/pdgmark_results.json");
                }
                cleanupTestObjects();
                if (gPort) {
                    GraphicsManager::instance().closeGraphicsPort(gPort);
                }
                OS::exit(0);
                return true;
            }
        }
        else if (inEventType == eventType_Startup) {
            std::cout << "=== PDG PDGMARK PERFORMANCE TEST (C++) ===" << std::endl;
            std::cout << "\nWill run " << NUM_TESTS << " tests:" << std::endl;
            for (int i = 0; i < NUM_TESTS; i++) {
                std::cout << "  " << (i+1) << ". " << gTests[i].title 
                         << " (weight: " << gTests[i].weight << "x)" << std::endl;
            }
            std::cout << "\nPress ESC to quit at any time\n" << std::endl;
            
            // Create window
            pdg::Rect windowRect(WINDOW_WIDTH, WINDOW_HEIGHT);
            gPort = GraphicsManager::instance().createWindowPort(windowRect, "PDG PDGMark Test (C++)");
            
            if (!gPort) {
                std::cerr << "ERROR: Could not create window port" << std::endl;
                OS::exit(1);
                return true;
            }
            
            std::cout << "Window created: " << gPort->getDrawingArea().width() 
                     << "x" << gPort->getDrawingArea().height() << std::endl;
            
            // Load test image - try multiple paths
            const char* imagePaths[] = {
                "test/data/test_image.png",
                "data/test_image.png",
                "../data/test_image.png",
                "../../data/test_image.png",
                "test_image.png"
            };
            
            for (size_t i = 0; i < sizeof(imagePaths) / sizeof(imagePaths[0]); ++i) {
                try {
                    gTestImage = Image::createImageFromFile(imagePaths[i]);
                    if (gTestImage) {
                        std::cout << "Loaded test image from: " << imagePaths[i] << std::endl;
                        break;
                    }
                } catch (...) {
                    // Try next path
                }
            }
            
            if (!gTestImage) {
                std::cerr << "ERROR: Could not load test image from any path" << std::endl;
                OS::exit(1);
                return true;
            }
            
            // Initialize random seed
            srand(static_cast<unsigned int>(time(NULL)));
            
            // Get timestamp
            time_t now = time(0);
            char timestamp[80];
            strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", gmtime(&now));
            gTestStartTimestamp = std::string(timestamp) + "Z";
            
            gGlobalStartTime = OS::getMilliseconds();
            
            // Start first test
            startNextTest();
            
            return true;
        }
        
        return false;
    }
};

void startNextTest() {
    if (gCurrentTestIndex >= NUM_TESTS) {
        return;
    }
    
    resetTestStats();
    
    TestDefinition& test = gTests[gCurrentTestIndex];
    
    std::cout << "Starting Test " << (gCurrentTestIndex + 1) << "/" << NUM_TESTS 
             << ": " << test.title << std::endl;
    std::cout << "Adaptively adding objects (50-500 per batch) until FPS drops below 60..." << std::endl;
    
    // Add initial batch
    pdg::Rect bounds = gPort->getDrawingArea();
    int count = BASE_OBJECTS;
    if (gTests[gCurrentTestIndex].name == "text") {
        count = 10;  // Start very small for text
    }
    addTestObjects(count, bounds);
}

// ============================================
// PDG FRAMEWORK INITIALIZATION
// ============================================

namespace pdg {

bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool haveMainResourceFile) throw() { return "PDG PDGMark (C++)"; }
const char* Initializer::getMainResourceFileName() throw() { return NULL; }

bool Initializer::installGlobalHandlers() throw() {
    PDGMarkHandler* handler = new PDGMarkHandler();
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

