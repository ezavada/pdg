// -----------------------------------------------
// main-iphone.m
// 
// iPhone implementation of main application entry point
//
// Written by Ed Zavada, 2010-2012
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


#include "pdg_project.h"

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

#define PDG_DECORATE_GLOBAL_TYPES
#include "pdg/sys/platform.h"
#import "pdg/sys/events.h"

#import "pdg-main.h"
#include "pdg-lib.h"

#import <OpenGLES/ES1/gl.h>
#import "EAGLView.h"
#import "ES1Renderer.h"
#import "PdgAppDelegate.h"
#include "internals.h"

#define kAccelerometerUpdateFrequency    60.0

extern "C" int pow2(int n);

float gLastOrientationAngle = 0.0f;
int gLastScreenPosition = -1;
//UIDeviceOrientation gLastOrientation = UIDeviceOrientationPortrait;

int main(int argc, char *argv[])
{
    pdg_LibSaveArgs(argc, (const char**)argv);
	int result = 0;
	bool noExit = pdg::main_getNoExitFromArgs(argc, (const char**) argv);
	do {
		if (result == 0) {
			result = UIApplicationMain(argc, argv, nil, nil);
			if (noExit && result == 0) {
				result = pdg::main_cleanup(&noExit); // cleanup without exit
			}
		}
	} while(noExit);
    pdg::main_cleanup(&noExit); // cleanup for complete shutdown and exit
	return result;
}

extern "C" int pow2(int n) {
	int x = 1;
	while(x < n) {
		x <<= 1;
	}
	return x;
}

namespace pdg {
    

//CGContextRef graphics_getCurrentCGContextRef() {
//	CGContextRef theContextRef = UIGraphicsGetCurrentContext();
//	return theContextRef;
//}
//
void platform_setHardwareCursorVisible(bool inVisible) {
}

void platform_setHardwareBusyCursor() {
}

void platform_setHardwareNormalCursor() {
}

void platform_startDrawing(void* windRef) {
    [EAGLContext setCurrentContext:gCurrContext];
}

void platform_finishDrawing(void* windRef) {
    [gCurrContext presentRenderbuffer:GL_RENDERBUFFER_OES];
}

void platform_getScreenSize(long* outWidth, long* outHeight, int screenNum) {
	UIScreen* screen = [UIScreen mainScreen];
	CGRect rect = [screen applicationFrame];
	UIDevice* uiDevice = [UIDevice currentDevice];

    if (UIDeviceOrientationIsLandscape([uiDevice orientation]) || !pdg::graphics_allowVerticalOrientation()) {
		// landscape, swap height and width
		*outWidth = rect.size.height;
		*outHeight = rect.size.width;
	} else {
		*outWidth = rect.size.width;
		*outHeight = rect.size.height;		
	}

//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
//	{
//		// The device is an iPad running iPhone 3.2 or later.
//	}
//	else
//	{
//		// The device is an iPhone or iPod touch.
//	}
}

void platform_getMaxWindowSize(long* outWidth, long* outHeight, int screenNum) {
	platform_getScreenSize(outWidth, outHeight, screenNum); // no difference between windowed and full screen on iPhone/iPad
}

int platform_getNumScreens(void) {
    // right now we are ignoring TV out screen
    return 1;
}

int platform_getCurrentScreenDepth(int screenNum) {
    if (screenNum == 0 || screenNum == pdg::screenNum_PrimaryScreen) {
        return 32;
    } else {
        return 0;
    }
}

void platform_switchScreenResolution(int screenNum, long width, long height, int bpp) {
    // meaningless on iPhone/iPad (except perhaps on TV out screen)
}

void* platform_createWindow(long width, long height, long x, long y, int bpp, const char* title) {
    // meaningless on iPhone/iPad (except perhaps on TV out screen)
    return 0;
}

void* platform_createFullscreenWindow(long width, long height, int bpp, int screenNum) {
    // meaningless on iPhone/iPad (except perhaps on TV out screen)
    return 0;
}

bool platform_isFullScreen(void* windRef) {
	// always full screen
	return true;
}

void platform_destroyWindow(void* windRef) {
}

void platform_resizeWindow(void* windRef, long width, long height, bool fullscreen) {
	// always full screen
}

void platform_captureScreen(int screenNum) {
	// always captured
	// TODO: make this actually be what hides the top battery and signal indicators
}

void platform_releaseScreen(int screenNum) {
	// always captured
	// TODO: make this actually be what shows the top battery and signal indicators
}

int platform_closestScreenTo(long width, long height, int bpp) {
	// there is only one screen, it is always the closest
	return 0;
}

int platform_getPrimaryScreen() {
	// there is only one screen, it is always the primary
	return 0;
}

int platform_getWindowScreen(void* windRef) {
	// there is only one screen, the window must be in it
	return 0;
}

bool platform_closestScreenMode(int screenNum, long* ioWidth, long* ioHeight, int* ioBpp) {
	UIScreen* screen = [UIScreen mainScreen];
	CGRect rect = [screen applicationFrame];
	bool landscape = *ioWidth > *ioHeight;
	bool canDo = false;
	if (landscape) {
		// try landscape mode
		canDo = (*ioWidth <= rect.size.height) && (*ioHeight <= rect.size.width);
		*ioWidth = rect.size.height;
		*ioHeight = rect.size.width;
	} else {
		canDo = (*ioWidth <= rect.size.width) && (*ioHeight <= rect.size.height);
		*ioHeight = rect.size.height;
		*ioWidth = rect.size.width;
	}
	*ioBpp = 32;
	return canDo;
}

void platform_getWindowPosition(void* windRef, long* outXPos, long* outYPos) {
	*outXPos = 0;
	*outYPos = 0;
}

int platform_getNumSupportedScreenModes(int screenNum) {
	return 2;  // portrait and landscape
}

void platform_getNthSupportedScreenMode(int screenNum, int n, long* outWidth, long* outHeight, int* outBpp) {
	UIScreen* screen = [UIScreen mainScreen];
	CGRect rect = [screen applicationFrame];
    if (n == 1) {
		// landscape, swap height and width
		*outWidth = rect.size.height;
		*outHeight = rect.size.width;
	} else {
		*outWidth = rect.size.width;
		*outHeight = rect.size.height;		
	}
	*outBpp = 32;
}

void platform_setWindowPosition(void* windRef, long xPos, long yPos) {
	// always fullscreen
}


// ---------------------------------

void platform_initImageData(unsigned char* imageData, long imageDataLen, unsigned char** outDataPtr, long* outWidth, long* outHeight, long* outBufferWidth, long* outBufferHeight, long* outBufferPitch, int* outFormat) {

	UIImage* image = 0;
	void* tmpImageData = 0;
	*outWidth = 0;
	*outHeight = 0;
	*outBufferWidth = 0;
	*outBufferHeight = 0;
	*outBufferPitch = 0; 
	*outDataPtr = 0;
	*outFormat = GL_RGB;
	
	@try {
		
		NSData *data = [NSData dataWithBytesNoCopy:imageData length:imageDataLen];
		image = [[UIImage alloc] initWithData:data];
		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

		int width   = CGImageGetWidth(image.CGImage);
		int height  = CGImageGetHeight(image.CGImage);
		int pitch   = CGImageGetBytesPerRow(image.CGImage);
		int bpp     = CGImageGetBitsPerPixel(image.CGImage);
		
		// see if we have an alpha channel
//		CGImageAlphaInfo alphaInfo = CGImageGetAlphaInfo(image.CGImage);
		bool hasAlpha = true; //((alphaInfo != kCGImageAlphaNone) && (alphaInfo != kCGImageAlphaNoneSkipLast) && (alphaInfo != kCGImageAlphaNoneSkipFirst));

		// now draw the image once into a a CGContext
		// recalc the pitch and for the intermediate bitmap buffer
		int numComponents = hasAlpha ? 4 : 3;
		pitch = ((width * 4 * numComponents) + 3) / 4;
		bpp = numComponents * 8;
		tmpImageData = malloc( height * pitch);
		CGContextRef context = CGBitmapContextCreate( tmpImageData, width, height, 8, pitch, colorSpace, 
					hasAlpha ? (kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big) : (kCGImageAlphaNone | kCGBitmapByteOrder32Big) );
		CGColorSpaceRelease( colorSpace );
		CGContextClearRect( context, CGRectMake( 0, 0, width, height ) );
		CGContextTranslateCTM( context, 0, height - height );
		CGContextDrawImage( context, CGRectMake( 0, 0, width, height ), image.CGImage );
	
		int glBufferWidth = pow2(width);
		int glBufferHeight = pow2(height);
		int glBufferPitch = ((glBufferWidth * bpp/2) + 3) / 4;
		
		*outDataPtr = (unsigned char*) malloc(glBufferPitch * glBufferHeight);
		// copy the image bitmap data line by line into the new malloc'd buffer
		unsigned char* dst = *outDataPtr;
		unsigned char* src = (unsigned char*) tmpImageData;
		for (int i = 0; i<height; i++) {
			memcpy(dst, src, pitch);
			memset(dst + pitch, 0, glBufferPitch - pitch); // clear the remaining part of the buffer
			dst += glBufferPitch;
			src += pitch;
		}
//		memcpy(dst, src, glBufferPitch * glBufferHeight);

		*outWidth = width;
		*outHeight = height;
		*outBufferWidth = glBufferWidth;
		*outBufferHeight = glBufferHeight;
		*outBufferPitch = glBufferPitch; 
		
		if (hasAlpha)  {
			*outFormat = GL_RGBA;
		}
	}
	@catch (NSException *exception) {
		if (outDataPtr) {
			free(*outDataPtr);
			outDataPtr = 0;
		}
	}
	if (tmpImageData) {
		free(tmpImageData);
		tmpImageData = 0;
	}
	if (image) {
		[image retain];
//		[image release];
//		image = 0;
	}
}
    
void platform_getDeviceOrientation(float* outRoll, float* outPitch, float* outYaw, bool absolute) {
    *outPitch = 0.0f;
    *outRoll = 0.0f;
    *outYaw = 0.0f;
}


} // end namespace pdg

// ===================================

@implementation PDGOpenGLView

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	int btnIndex = 0;
	// check against all touches so that we can keep consistent "button" numbers
	// the first finger down represents button 0 (left click), the second button 1 (right click), etc..
    for (UITouch *touch in [event allTouches]) {
        if (touch.phase == UITouchPhaseBegan) {
			CGPoint location = [touch locationInView:touch.view];
            pdg::main_handleMouse(pdg::mouseEventType_MouseDown, location.x, location.y, btnIndex, 0, 0, 0, 0);
        }
		btnIndex++;
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	int btnIndex = 0;
    for (UITouch *touch in [event allTouches]) {
        if (touch.phase == UITouchPhaseMoved) {
			CGPoint location = [touch locationInView:touch.view];
            pdg::main_handleMouse(pdg::mouseEventType_MouseMoved, location.x, location.y, btnIndex, 0, 0, 0, 0);
		}
		btnIndex++;
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	int btnIndex = 0;
    for (UITouch *touch in [event allTouches]) {
        if (touch.phase == UITouchPhaseEnded) {
			CGPoint location = [touch locationInView:touch.view];
            pdg::main_handleMouse(pdg::mouseEventType_MouseUp, location.x, location.y, btnIndex, 0, 0, 0, 0);
		}
		btnIndex++;
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	int btnIndex = 0;
    for (UITouch *touch in [event allTouches]) {
        if (touch.phase == UITouchPhaseCancelled) {
			// when cancelled, we generate a mouseup that is off the screen, so it should be outside any 
			// controls or active items we have
			pdg::main_handleMouse(pdg::mouseEventType_MouseUp, -1, -1, btnIndex, 0, 0, 0, 0);
		}
		btnIndex++;
    }
}

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
	// do something when motion ends. Currently this is only a shake gesture
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
	// do something when accelerometer detects changes
}

- (void)setupAccelerometer
{
	// setup for orientation events
	[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didRotate:) name: UIDeviceOrientationDidChangeNotification object: nil];

	// setup for other accelerometer events
	[[UIAccelerometer sharedAccelerometer] setUpdateInterval:1.0 / kAccelerometerUpdateFrequency];
	[[UIAccelerometer sharedAccelerometer] setDelegate:self];
	
}

-(void) didRotate:(NSNotification *)notification
{ 
	UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
	int screenPos = pdg::screenPos_Normal;
    if (orientation == UIDeviceOrientationPortraitUpsideDown) {
		screenPos = pdg::screenPos_Rotated180;
	} else if (orientation == UIDeviceOrientationLandscapeRight) {
		screenPos = pdg::screenPos_Rotated90Clockwise;
	} else if (orientation == UIDeviceOrientationLandscapeLeft) {
		screenPos = pdg::screenPos_Rotated90CounterClockwise;
	} else if (orientation == UIDeviceOrientationFaceUp) {
		screenPos = pdg::screenPos_FaceUp;
	} else if (orientation == UIDeviceOrientationFaceDown) {
		screenPos = pdg::screenPos_FaceDown;
	}
    if (gLastScreenPosition != screenPos) {
		if (gLastScreenPosition == -1) {
			// this is the initial event we get to setup the screen state
			pdg::main_setInitialScreenState(screenPos, true);
		} else {
			// Let the rest of the framework know that a resize has happened so it can redraw
			pdg::main_handleScreenUpdate(screenPos);
		}
		gLastScreenPosition = screenPos;
	}

/*	if (orientation == UIDeviceOrientationLandscapeLeft)
	{
		CGAffineTransform transform = CGAffineTransformRotate(window.transform, 3.14159/2);
		[UIView beginAnimations:@"rotate" context:nil];
		[UIView setAnimationDuration:0.3];
		[UIView setAnimationDelegate:self];
		window.transform = transform;
		[UIView commitAnimations];
		NSLog([NSString stringWithFormat:@"Frame: %d %d %d %d\n", (int)window.frame.origin.x, (int)window.frame.origin.y, (int)window.frame.size.width, (int)window.frame.size.height]);
		NSLog([NSString stringWithFormat:@"Bounds: %d %d %d %d\n", (int)window.bounds.origin.x, (int)window.bounds.origin.y, (int)window.bounds.size.width, (int)window.bounds.size.height]);
		NSLog([NSString stringWithFormat:@"Center: %d %d\n", (int)window.center.x, (int)window.center.y]);
	} */
}
@end

