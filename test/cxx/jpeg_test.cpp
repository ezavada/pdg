// Simple test program to verify JPEG support
#include <iostream>
#include <fstream>
#include <vector>

// Forward declaration of the JPEG function
extern "C" {
    void platform_initJPEGData(unsigned char* imageData, long imageDataLen, unsigned char** outDataPtr, 
        long* outWidth, long* outHeight, long* outBufferWidth, long* outBufferHeight, long* outBufferPitch, 
        int* outFormat);
}

int main() {
    std::cout << "JPEG Support Test" << std::endl;
    std::cout << "=================" << std::endl;
    
    // Test with a simple JPEG file (you would need to provide a real JPEG file)
    std::string testFile = "test.jpg";
    std::ifstream file(testFile, std::ios::binary);
    
    if (!file.is_open()) {
        std::cout << "Could not open test file: " << testFile << std::endl;
        std::cout << "Please provide a JPEG file named 'test.jpg' in the test directory." << std::endl;
        return 1;
    }
    
    // Read the file into memory
    file.seekg(0, std::ios::end);
    long fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<unsigned char> imageData(fileSize);
    file.read(reinterpret_cast<char*>(imageData.data()), fileSize);
    file.close();
    
    // Test JPEG decoding
    unsigned char* outData = nullptr;
    long width, height, bufferWidth, bufferHeight, bufferPitch;
    int format;
    
    platform_initJPEGData(imageData.data(), fileSize, &outData, 
        &width, &height, &bufferWidth, &bufferHeight, &bufferPitch, &format);
    
    if (outData) {
        std::cout << "JPEG decoding successful!" << std::endl;
        std::cout << "Width: " << width << std::endl;
        std::cout << "Height: " << height << std::endl;
        std::cout << "Format: " << (format == 0x1907 ? "GL_RGB" : "GL_RGBA") << std::endl;
        std::cout << "Buffer pitch: " << bufferPitch << std::endl;
        
        // Clean up
        free(outData);
        std::cout << "Test completed successfully!" << std::endl;
        return 0;
    } else {
        std::cout << "JPEG decoding failed!" << std::endl;
        return 1;
    }
} 