// -----------------------------------------------
//
//  EAGLView.m
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

//

#import "pdg_project.h"
#include "pdg-lib.h"

#import "EAGLView.h"

#import "ES1Renderer.h"
//#import "ES2Renderer.h"

@implementation EAGLView

@synthesize animating;
@dynamic animationFrameInterval;

// You must implement this method
+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (BOOL)setupRenderer
{
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];

// we don't need this since we aren't doing any shaders
//		renderer = [[ES2Renderer alloc] init];
		
		if (!renderer)
		{
			renderer = [[ES1Renderer alloc] init];
			
			if (!renderer)
			{
				return NO;
			}
		}
        
		// Get the bounds of the main screen
		screenBounds = [[UIScreen mainScreen] bounds];

		animating = FALSE;
		displayLinkSupported = FALSE;
		animationFrameInterval = 2;  // Max 30 FPS
		displayLink = nil;
		animationTimer = nil;
		engineTimer = nil;
		
		displayLinkSupported = TRUE;
		return YES;
}

- (id)initWithFrame:(CGRect)frame
{
	if ((self = [super initWithFrame:frame]) && ![self setupRenderer]) {
		[self release];
		return nil;
	}
	return self;
}

- (id)initWithCoder:(NSCoder *)coder
{
	if ((self = [super initWithCoder:coder]) && ![self setupRenderer]) {
		[self release];
		return nil;
	}
	return self;
}

- (void) drawView:(id)sender
{
    if (sender == engineTimer) {
        engineTimer = nil;
    }
    [renderer render];
    [self scheduleEngineTimer];
}

- (void) scheduleEngineTimer
{
    [engineTimer invalidate];
    engineTimer = nil;

    long delayMs = pdg_LibGetNextTimerDelay();
    if (delayMs < 0) {
        return;
    }

    // A zero-delay callback must return to the UIKit run loop rather than
    // recursively entering the engine from inside a timer handler.
    NSTimeInterval delay = MAX(delayMs, 1L) / 1000.0;
    engineTimer = [NSTimer timerWithTimeInterval:delay
                                          target:self
                                        selector:@selector(drawView:)
                                        userInfo:nil
                                         repeats:NO];
    [[NSRunLoop mainRunLoop] addTimer:engineTimer forMode:NSRunLoopCommonModes];
}

- (void) layoutSubviews
{
	[renderer resizeFromLayer:(CAEAGLLayer*)self.layer];
    [self drawView:nil];
}

- (NSInteger) animationFrameInterval
{
	return animationFrameInterval;
}

- (void) setAnimationFrameInterval:(NSInteger)frameInterval
{
	// Frame interval defines how many display frames must pass between each time the
	// display link fires. The display link will only fire 30 times a second when the
	// frame internal is two on a display that refreshes 60 times a second. The default
	// frame interval setting of one will fire 60 times a second when the display refreshes
	// at 60 times a second. A frame interval setting of less than one results in undefined
	// behavior.
	if (frameInterval >= 1)
	{
		animationFrameInterval = frameInterval;
		
		if (animating)
		{
			[self stopAnimation];
			[self startAnimation];
		}
	}
}

- (void) startAnimation
{
	if (!animating)
	{
		if (displayLinkSupported)
		{
			displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
			[displayLink setPreferredFramesPerSecond:60 / animationFrameInterval];
			[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		}
		else
			animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 30.0) * animationFrameInterval) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];
		
		animating = TRUE;
	}
}

- (void)stopAnimation
{
	if (animating)
	{
		if (displayLinkSupported)
		{
			[displayLink invalidate];
			displayLink = nil;
		}
		else
		{
			[animationTimer invalidate];
			animationTimer = nil;
		}
		[engineTimer invalidate];
		engineTimer = nil;
		
		animating = FALSE;
	}
}

- (void) dealloc
{
	[engineTimer invalidate];
    [renderer release];
	
    [super dealloc];
}

@end
