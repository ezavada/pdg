// -----------------------------------------------
// platform-iphone.cpp
// 
// iOS implementation of platform specific functions
// Cocoa implementation
//
// Written by Ed Zavada, 2004-2012
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

#include "pdg/sys/os.h"
#include "internals.h"
#include "internals-macosx.h"

#include <iostream>
#include <string>

#include <limits.h>
#include <stdlib.h>
#include <mach-o/dyld.h> // for _NSGetExecutablePath

namespace pdg {

const char* ios_setupWorkingDirectory(int argc, const char* argv[]);
const char* ios_getExecPath();

const char* platform_setupDirectories(int argc, const char* argv[]) {
		// make sure our working directory is the directory the app was launched from
	static std::string workingDir = ios_setupWorkingDirectory(argc, argv);
	std::string appDir;
	std::string appDataDir;
	std::string resourceDir;

	// for Mac OS X application bundles, we want the application directory to point to the directory that
	// contains the {myapp}.app folder, and the data directory to point into {myapp.app}/Contents/Resources
	appDir = workingDir;
	std::string appName = argv[0];
	appName.replace(0, workingDir.length(), "");
	int pos = appName.find('/');
	if (pos != std::string::npos) {
		appName.replace(pos, std::string::npos, "");
	}
	char buffer[PATH_MAX];
	if ( macosx_getApplicationSupportDirectory(appName.c_str(), buffer, PATH_MAX) ) {
		appDataDir = buffer;
	} else {
		appDataDir = workingDir;
	}
	resourceDir = workingDir + appName + "/Contents/Resources/";

	os_setApplicationDirectory(appDir.c_str());
	os_setApplicationDataDirectory(appDataDir.c_str());
	os_setApplicationResourceDirectory(resourceDir.c_str());

    DEBUG_ONLY(
		std::cout << "Using Application directory [" << OS::getApplicationDirectory() << "]" << std::endl;
		std::cout << "Using Data directory [" << OS::getApplicationDataDirectory() << "]" << std::endl;
		std::cout << "Using Resource directory [" << OS::getApplicationResourceDirectory() << "]" << std::endl;
	)
    return workingDir.c_str();
}

/*
#ifdef PLATFORM_IOS
		// for iOS, we want the application directory to point to the Documents folder
		// and the Application Data Directory to point inside the package where all the resources are found
		// now workingDir is the actual Application directory path
		std::string tmpDir = workingDir;
		tmpDir = workingDir + "../Documents/";
		appDir = os_makeCanonicalPath(tmpDir.c_str());
		appDataDir = workingDir;
		resourceDir = appDataDir;
#else
#endif // ! PLATFORM_IOS
*/		

// NOT THREAD SAFE!!	
const char* ios_getExecPath() {
    char buf[PATH_MAX];
    static char path[PATH_MAX];

    uint32_t size = sizeof(buf);
    _NSGetExecutablePath(buf, &size);
    MAKE_STRING_BUFFER_SAFE(buf, PATH_MAX);
	realpath(buf, path);
    MAKE_STRING_BUFFER_SAFE(path, PATH_MAX);
    return path;
}

const char* ios_setupWorkingDirectory(int argc, const char* argv[]) {
    static char path[PATH_MAX];

	std::strncpy(path, ios_getExecPath(), PATH_MAX);
    MAKE_STRING_BUFFER_SAFE(path, PATH_MAX);
    char* p = strrchr(path, '/');
    if (p) {
        p++;
        *p = 0;
    }
	std::cerr << "Using working directory [" << path << "]" << std::endl;
    chdir(path);	
    return path;
}


} // end namespace pdg

