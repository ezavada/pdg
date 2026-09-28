// -----------------------------------------------
// os-win32.cpp
//
// Windows implementation of common system functions
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

#include "pdg/msvcfix.h"  // fix non-standard MSVC

#include "pdg/sys/os.h"
#include "pdg/sys/log.h"

//#define PDG_DEBUG_OUT_TO_LOG

#include "ConvertUTF.h"
#include "internals.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <regex>
#include <format>
#include <string_view>
#include <time.h>
#include <assert.h>
#include <io.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef LEAK_AND_EXCEPTION_CHECKS
#include "..\LeakCheck\LeakCheck.h"
#define DEBUG_NEW new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#define THIS_FILE __FILE__
#endif

#define WinAPI


namespace pdg {


bool native2path(const char *inNativeFileName, char* outStdFileName, int len);

const char* os_getPlatformErrorMessage(long err) {
	static char sHresultMsgBuf[1024];
	LPVOID a_pvMsgBuf;
	LPCSTR a_pszMsg = NULL;
	std::snprintf(sHresultMsgBuf, sizeof(sHresultMsgBuf), "Windows Error: 0X%.8X", err);
	if (WinAPI::FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, (DWORD)err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPSTR) &a_pvMsgBuf, 0, NULL )) {
	   a_pszMsg = (LPSTR)a_pvMsgBuf;
	   // Do something with the error message.
	   std::strncat(sHresultMsgBuf, a_pszMsg, sizeof(sHresultMsgBuf) - strlen(sHresultMsgBuf) - 1);
	   LocalFree(a_pvMsgBuf);
	}
	return sHresultMsgBuf;
}

// return false if illegal characters are found
bool os_path2native(const char *inStdFileName, char* outNativeFileName, int len) {
    DEBUG_ASSERT(len > 0, "PRECONDITION: length must not be zero or negative");
    outNativeFileName[0] = 0;
    
    // Check for illegal characters: colon after 2nd position
    if (std::string_view(inStdFileName).find(':', 2) != std::string_view::npos) {
        return false;   // colon is an illegal character after 2nd position
    }
    
    char tempname[MAX_PATH];
    std::strncpy(tempname, inStdFileName, MAX_PATH - 1);
    tempname[MAX_PATH - 1] = '\0';
    MAKE_STRING_BUFFER_SAFE(tempname, MAX_PATH); // make string buffer safe also alerts us to when inStdFileName is too long and gets truncated
    
    // Convert forward slashes to backslashes for Windows
    // Always do this conversion regardless of whether backslashes are already present
    char * p;
    p = std::strchr(tempname,'/');
    while (p) {
        *p = '\\';
        p = std::strchr(p,'/');
    }
    std::strncpy(outNativeFileName, tempname, len - 1);
    outNativeFileName[len - 1] = '\0';
    MAKE_STRING_BUFFER_SAFE(outNativeFileName, len);
    return true;
}

// return false if illegal characters are found
bool native2path(const char *inNativeFileName, char* outStdFileName, int len) {
    DEBUG_ASSERT(len > 0, "PRECONDITION: length must not be zero or negative");
    if (std::strchr(inNativeFileName, '/')) {
        return false;   // forward slash is an illegal character
    }
    char tempname[1024];
    std::strncpy(tempname, inNativeFileName, 1023);
    tempname[1023] = '\0';
    MAKE_STRING_BUFFER_SAFE(tempname, 1024); // make string buffer safe also alerts us to when inStdFileName is too long and gets truncated
	// now that we got the drive spec, there is no other place were colon is legal
	if (std::strchr(tempname+2, ':')) {
        return false;   // colon is an illegal character
    }
	char * p;
    p = std::strchr(tempname,'\\');
    while (p) {
        *p = '/';
        p = std::strchr(p+1,'\\');
    }
    std::strncpy(outStdFileName, tempname, len - 1);
    outStdFileName[len - 1] = '\0';
    MAKE_STRING_BUFFER_SAFE(outStdFileName, len);
    return true;
}

bool os_matchesFilename(const char* pattern, const char* name) {
    // Match the documented * and ? wildcards, preserving Windows case folding.
    std::string expression;
    std::string_view wildcard(pattern);
    if (wildcard == "*.*") wildcard = "*";
    for (char c : wildcard) {
        if (c == '*') expression += ".*";
        else if (c == '?') expression += '.';
        else {
            if (std::string_view(R"(\.^$|()[]{}+)").find(c) != std::string_view::npos)
                expression += '\\';
            expression += c;
        }
    }
    return std::regex_match(name, std::regex(expression, std::regex::icase));
}

#ifdef DEBUG

#ifdef PDG_DEBUG_OUT_TO_LOG
extern pdg::log gDebugLog;

pdg::log::category category_DOUT("_DOUT");

#endif // PDG_DEBUG_OUT_TO_LOG

void OS::_DEBUGGER(const char* str) {
/*	if(str)
	{
		::MessageBoxA(NULL, str, "ASSERT FAILED!", MB_OK | MB_ICONEXCLAMATION);
	}

	// invoke the debugger
    bool debugger_break_for_assert = false;
    assert(debugger_break_for_assert);
*/
}

#ifndef STADIUM_SERVER
void OS::_DOUT( const char * fmt, ...) {
	char buf[1256];
	va_list lst;
	va_start(lst, fmt);
	int n = std::vsnprintf(buf, 1255, fmt, lst);
	buf[1255] = 0;
	va_end(lst);
#ifdef PDG_DEBUG_OUT_TO_LOG

    gDebugLog << pdg::log::verbose << category_DOUT << buf << pdg::endlog;

#endif // PDG_DEBUG_OUT_TO_LOG

#ifdef UNICODE
    std::string src(buf);
    utf16string dst;
    utf8to16(dst, src);
	OutputDebugString( (WCHAR*)dst.c_str() );
#else
	OutputDebugString( buf );
#endif // UNICODE
    OutputDebugStringA("\n");
	// make the date time string
    char dateTimeStr[40];
	time_t lclTime;
	struct tm *now;
	lclTime = time(NULL);
	now = gmtime(&lclTime);
	strftime(dateTimeStr, 40, "%y%m%d %H:%M:%S ", now);
    const auto msStr = std::format("{:010}\t", OS::getMilliseconds());
	std::cout << dateTimeStr << msStr << '\t' << buf << std::endl;

}
#endif // !STADIUM_SERVER

//End of File
#endif // DEBUG

} // end namespace pdg

