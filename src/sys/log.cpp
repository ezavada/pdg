// -----------------------------------------------
// log.cpp
// 
// logging support
//
// Written by Ed Zavada, 2001-2012
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

#include "pdg/msvcfix.h"

#include "pdg/sys/os.h"
#include "log-impl.h"

#include <ctime>

#define MAX_LOG_FILENAME_LEN 256

// get the build info
#include "buildinfo.i"

namespace pdg {

static std::string getLogDirectoryPrefix() {
    std::string logDir = OS::getApplicationDirectory();
    if (!logDir.empty() && logDir[logDir.length() - 1] != '/' &&
        logDir[logDir.length() - 1] != '\\') {
        logDir += '/';
    }
    return logDir;
}

static std::string trimLogBaseName(const char* inLogNameBase, const std::string& logDir, size_t suffixLen) {
    std::string logBase = inLogNameBase ? inLogNameBase : "";
    const size_t maxFilenameLen = MAX_LOG_FILENAME_LEN - 1;
    if (logDir.length() + suffixLen >= maxFilenameLen) {
        logBase.clear();
        return logBase;
    }
    const size_t maxBaseLen = maxFilenameLen - logDir.length() - suffixLen;
    if (logBase.length() > maxBaseLen) {
        logBase.resize(maxBaseLen);
    }
    return logBase;
}

static std::string buildLogFilename(const std::string& logDir, const char* inLogNameBase, const char* suffix, size_t suffixLen) {
    return logDir + trimLogBaseName(inLogNameBase, logDir, suffixLen) + suffix;
}

// LogManagerImpl methods
void 
LogManagerImpl::initialize(const char* inLogNameBase, int initMode) {
    try {
        if (mFile.is_open()) {
            mFile.close();
        }
		mBaseLogName = inLogNameBase;
		mInitMode = initMode;
		if (mLevel > 0) { // only create the file if log level is something higher than none
            std::string logDir = getLogDirectoryPrefix();
    		std::time_t lclTime;
    		struct std::tm *now;
    		lclTime = std::time(NULL);
    		now = std::localtime(&lclTime);
			if (initMode == init_CreateUniqueNewFile) {
				const size_t uniqueSuffixLen = sizeof("_YYMMDD_HHMMSS.log") - 1;
				const std::string uniqueBaseName = trimLogBaseName(inLogNameBase, logDir, uniqueSuffixLen);
				char timestamp[32];
				bool exists = false;
				do {
        			std::strftime(timestamp, sizeof(timestamp), "%y%m%d_%H%M%S", now);
          			MAKE_STRING_BUFFER_SAFE(timestamp, sizeof(timestamp));
                    std::string logname = logDir + uniqueBaseName + "_" + timestamp + ".log";
					// keep trying new filenames until there is no existing one
					++now->tm_sec;
					FindDataT fd;
					exists = OS::findFirst(logname.c_str(), fd);
					OS::findClose(fd);
                    if (!exists) {
        				mFile.open(logname.c_str());
        				mLogFilename = logname;
        				mStream = &mFile;
                    }
				} while (exists);
			} else if (initMode == init_OverwriteExisting) {
                std::string logname = buildLogFilename(logDir, inLogNameBase, ".log", sizeof(".log") - 1);
				mFile.open(logname.c_str());
				mLogFilename = logname;
				mStream = &mFile;
			} else if (initMode == init_AppendToExisting) {
                std::string logname = buildLogFilename(logDir, inLogNameBase, ".log", sizeof(".log") - 1);
				mFile.open(logname.c_str(), std::ios::app);
				mLogFilename = logname;
				mStream = &mFile;
			} else if (initMode == init_StdOut) {
			    mStream = &std::cout;
				mLogFilename = "";
			} else if (initMode == init_StdErr) {
				mStream = &std::cerr;
				mLogFilename = "";
			}
			char formatstr[1024];
      		std::snprintf(formatstr, 1024, "log initialized %%Y/%%m/%%d %%H:%%M:%%S for %s", inLogNameBase);
      		MAKE_STRING_BUFFER_SAFE(formatstr, 1024);
      		// get the date time info that will make this filename unique
    		// use the format string to add in the data time info
    		char loglinestr[1024];
    		std::strftime(loglinestr, 1024, formatstr, now);
      		MAKE_STRING_BUFFER_SAFE(loglinestr, 1024);
			writeLogEntry(4, "@LOGINIT", loglinestr);
			writeLogEntry(4, "@BLDINFO", BUILDINFO_STR);
		}
		mInited = true;
    }
    catch(...) {
        mInited = false;
    }
}

#define LEVEL_STR_LEN 3
//static const char sLevelStrings[37] = "E0\0E1\0E2\0E3\0I4\0I5\0I6\0I7\0V8\0V9\0TRACE\0";

void 
LogManagerImpl::writeLogEntry(int8 level, const char* category, const char* message) {
    if ( mInited && (level < mLevel) ) {
        try {
            const char theLevelStrings[37] = "E0\0E1\0E2\0E3\0I4\0I5\0I6\0I7\0V8\0V9\0TRACE\0";
            char dateTimeStr[40];
        	time_t lclTime;
        	struct tm *now;
        	lclTime = time(NULL);
        	now = gmtime(&lclTime);
        	strftime(dateTimeStr, 40, "%y%m%d %H:%M:%S ", now);
        	if (level > log::trace) {
        	    level = log::trace;
        	}
            ms_time msTime = OS::getMilliseconds();
        	char msStr[40];
        	std::snprintf(msStr, 40, "%.10lu\t", msTime);
            MAKE_STRING_BUFFER_SAFE(msStr, 40);
        	// following section is mutexed so we don't have multiple threads
        	// attempting to alter the file at once
        	AutoMutex mutex(&mWriteMutex);
        	CHECK_PTR(&theLevelStrings[level*LEVEL_STR_LEN], theLevelStrings, 37);
            *mStream << dateTimeStr << msStr << &theLevelStrings[level*LEVEL_STR_LEN] 
                    << '\t' << category << '\t' << message << '\n';
        	mStream->flush();
        }
        catch(...) {
            try {
                mFile.close();
            }
            catch(...) {
            }
            mInited = false;
        }
    }
}

void  
LogManagerImpl::setLogLevel(int8 level) {
	if (level > log::trace) {
		level = log::trace;
	}
	if ((mLevel <= 0) && (level > log::none)) {
		// we are turning on logging where before it was set to none
		mLevel = level + 1;
		initialize(mBaseLogName.c_str(), mInitMode);	// create the file by calling initialize again
	} else if (level == log::none) {
        mLevel = 5; // make sure this is written
        writeLogEntry(4, "@LOGLVL", "setting log level to none, nothing more will be written till level is set higher");
        mLevel = 0; // we don't want any logging whatsoever
		try {
			mFile.close();  // close the file, now that we aren't using it so Windows can do things with it
		}
		catch(...) {
		}
        mInited = false;
	} else {
        if (level < log::none) {
            level = log::fatal;
        }
        // log the change to the log level so it is obvious
        char loglinestr[1024];
    	std::snprintf(loglinestr, 1024, "setting log level to [%d]", level);
      	MAKE_STRING_BUFFER_SAFE(loglinestr, 1024);
      	mLevel = 5; // to make sure this is written
        writeLogEntry(4, "@LOGLVL", loglinestr);
        mLevel = level + 1;  // so that when we set a level, we get everything at that level and below
    }
}

int8 
LogManagerImpl::getLogLevel() const {
    if (mLevel == 0) {
        return log::none;
    } else {
        return mLevel - 1;
    }
}

LogManager* LogManager::createSingletonInstance() {
	return new LogManagerImpl();
}



} // close namespace pdg

