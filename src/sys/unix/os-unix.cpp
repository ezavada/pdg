// -----------------------------------------------
// os-unix.cpp
// 
// Implementation of core os specific functionality
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
#include "pdg/sys/log.h"
#include "internals.h"
#include "pdg-main.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstdarg>

#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <fnmatch.h>

#define PosixAPI


namespace pdg {


// return false if illegal characters are found
bool os_path2native(const char *inStdFileName, char* outNativeFileName, int len) {
    if (std::strchr(inStdFileName, '\\')) {
        return false;   // backslash is an illegal character
    }
    if (std::string_view(inStdFileName).find(':', 2) != std::string_view::npos) {
        return false;   // colon is an illegal character after 2nd position
    }
    std::strncpy(outNativeFileName, inStdFileName, len - 1);
    outNativeFileName[len - 1] = '\0';
    MAKE_STRING_BUFFER_SAFE(outNativeFileName, len);
    return true;
}

bool os_matchesFilename(const char* pattern, const char* name) {
    return ::fnmatch(pattern, name, FNM_PATHNAME) == 0;
}

} // end namespace pdg 

#ifdef DEBUG

pdg::log::category category_DOUT("_DOUT");

void pdg::OS::_DEBUGGER(const char* str) {
	// invoke the debugger
    bool debugger_break_for_assert = false;
	// we still want to dump asserts to the console
	std::cerr << str << std::endl;
    assert(debugger_break_for_assert);
}


void pdg::OS::_DOUT( const char * fmt, ...) {
    static const int bufsize = 4068;
	static char buf[bufsize];
	std::va_list lst;
	va_start(lst, fmt);
	/* int n = */ std::vsnprintf(buf, bufsize-1, fmt, lst);
	va_end(lst);
	buf[bufsize-1] = 0;
#ifndef PDG_NO_DEBUG_TO_CONSOLE
	std::cout << buf << std::endl;
#endif

#ifdef PDG_DEBUG_OUT_TO_LOG
    main_getDebugLog() << pdg::log::verbose << category_DOUT << buf << pdg::endlog;
#endif // PDG_DEBUG_OUT_TO_LOG
	
	return;
}
#endif


