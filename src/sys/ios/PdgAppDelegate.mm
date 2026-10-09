// -----------------------------------------------
//  PDGAppDelegate.m
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

#include "pdg-lib.h"
#ifdef PDG_COMPILING_FOR_JAVASCRIPT
#include "pdg_ios_network.h"
#endif

#import "PDGAppDelegate.h"
#import "EAGLView.h"

@implementation PDGAppDelegate

@synthesize window;
@synthesize glView;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
	self.glView = [[[PDGOpenGLView alloc] initWithFrame:self.window.bounds] autorelease];
	self.glView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;

	UIViewController *viewController = [[[UIViewController alloc] init] autorelease];
	viewController.view = self.glView;
	self.window.rootViewController = viewController;
	[self.window makeKeyAndVisible];

	[glView setupAccelerometer];
	[glView startAnimation];
	return YES;
}

- (void) applicationWillResignActive:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
#ifdef PDG_COMPILING_FOR_JAVASCRIPT
    JSC_IOS_NetworkSuspend();
#endif
}

- (void) applicationDidBecomeActive:(UIApplication *)application
{
	[glView startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	[glView stopAnimation];
#ifdef PDG_COMPILING_FOR_JAVASCRIPT
    JSC_IOS_NetworkShutdown();
#endif
    pdg_LibQuit();
}

- (void) dealloc
{
	[window release];
	[glView release];
	
	[super dealloc];
}

@end
