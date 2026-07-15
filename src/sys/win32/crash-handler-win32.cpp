// -----------------------------------------------
// crash-handler-win32.cpp
//
// Install an unhandled exception filter on Windows that prints
// a C++ stack trace to stderr before the process exits.
// This makes native crashes (e.g. in test suite) debuggable.
//
// -----------------------------------------------

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dbghelp.h>
#include <cstdio>
#include <cstdarg>
#include <cstring>

#pragma comment(lib, "dbghelp.lib")

extern "C" void pdg_win32_crash_dump_js_stack(FILE* log);

namespace {

const int kMaxFrames = 64;
const int kSymBufSize = 256;

static void pdg_crash_log(FILE* log, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    if (log) {
        va_list ap2;
        va_copy(ap2, ap);
        vfprintf(log, fmt, ap2);
        va_end(ap2);
        fflush(log);
    }
    va_end(ap);
}

static LONG WINAPI pdg_unhandled_exception_filter(EXCEPTION_POINTERS* ex) {
    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();
    DWORD64 offset = 0;
    DWORD disp = 0;
    IMAGEHLP_LINE64 line = {};
    line.SizeOfStruct = sizeof(line);

    FILE* log = fopen("pdg_crash.log", "w");
    if (log) pdg_crash_log(log, "PDG C++ crash log - also check stderr\n\n");

    pdg_crash_log(log, "\n");
    pdg_crash_log(log, "=== PDG C++ CRASH (Unhandled Exception) ===\n");
    pdg_crash_log(log, "ExceptionCode: 0x%08lX", (unsigned long)ex->ExceptionRecord->ExceptionCode);
    switch (ex->ExceptionRecord->ExceptionCode) {
        case EXCEPTION_ACCESS_VIOLATION:
            pdg_crash_log(log, " (ACCESS_VIOLATION)");
            if (ex->ExceptionRecord->NumberParameters >= 2) {
                pdg_crash_log(log, " at 0x%p %s",
                    (void*)ex->ExceptionRecord->ExceptionInformation[1],
                    ex->ExceptionRecord->ExceptionInformation[0] ? "write" : "read");
            }
            break;
        case EXCEPTION_STACK_OVERFLOW:
            pdg_crash_log(log, " (STACK_OVERFLOW)");
            break;
        case EXCEPTION_ILLEGAL_INSTRUCTION:
            pdg_crash_log(log, " (ILLEGAL_INSTRUCTION)");
            break;
        default:
            break;
    }
    pdg_crash_log(log, "\n");
    pdg_crash_log(log, "ExceptionAddress: 0x%p\n", (void*)ex->ExceptionRecord->ExceptionAddress);
    pdg_crash_log(log, "\nC++ stack trace:\n");

    if (!SymInitialize(process, NULL, TRUE)) {
        pdg_crash_log(log, "  (SymInitialize failed, error %lu)\n", GetLastError());
        pdg_crash_log(log, "  Build with Debug config or ensure .pdb is next to .exe/.node for symbols.\n");
        if (log) fclose(log);
        return EXCEPTION_EXECUTE_HANDLER;
    }

#ifdef _M_X64
    CONTEXT* ctx = ex->ContextRecord;
    STACKFRAME64 frame = {};
    frame.AddrPC.Offset = ctx->Rip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = ctx->Rbp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = ctx->Rsp;
    frame.AddrStack.Mode = AddrModeFlat;

    int frame_num = 0;
    while (frame_num < kMaxFrames) {
        if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, thread,
                &frame, ctx, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL)) {
            break;
        }
        if (frame.AddrPC.Offset == 0) break;

        DWORD64 addr = frame.AddrPC.Offset;
        char sym_buf[sizeof(SYMBOL_INFO) + kSymBufSize] = {};
        SYMBOL_INFO* sym = (SYMBOL_INFO*)sym_buf;
        sym->SizeOfStruct = sizeof(SYMBOL_INFO);
        sym->MaxNameLen = kSymBufSize;

        const char* name = "???";
        if (SymFromAddr(process, addr, &offset, sym)) {
            name = sym->Name;
        }
        if (SymGetLineFromAddr64(process, addr, &disp, &line)) {
            pdg_crash_log(log, "  #%-2d 0x%p  %s (%s:%lu)\n",
                frame_num, (void*)addr, name, line.FileName, (unsigned long)line.LineNumber);
        } else {
            pdg_crash_log(log, "  #%-2d 0x%p  %s\n", frame_num, (void*)addr, name);
        }
        frame_num++;
    }
#elif defined(_M_IX86)
    CONTEXT* ctx = ex->ContextRecord;
    STACKFRAME64 frame = {};
    frame.AddrPC.Offset = ctx->Eip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = ctx->Ebp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = ctx->Esp;
    frame.AddrStack.Mode = AddrModeFlat;

    int frame_num = 0;
    while (frame_num < kMaxFrames) {
        if (!StackWalk64(IMAGE_FILE_MACHINE_I386, process, thread,
                &frame, ctx, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL)) {
            break;
        }
        if (frame.AddrPC.Offset == 0) break;

        DWORD64 addr = frame.AddrPC.Offset;
        char sym_buf[sizeof(SYMBOL_INFO) + kSymBufSize] = {};
        SYMBOL_INFO* sym = (SYMBOL_INFO*)sym_buf;
        sym->SizeOfStruct = sizeof(SYMBOL_INFO);
        sym->MaxNameLen = kSymBufSize;

        const char* name = "???";
        if (SymFromAddr(process, addr, &offset, sym)) {
            name = sym->Name;
        }
        if (SymGetLineFromAddr64(process, addr, &disp, &line)) {
            pdg_crash_log(log, "  #%-2d 0x%p  %s (%s:%lu)\n",
                frame_num, (void*)(uintptr_t)addr, name, line.FileName, (unsigned long)line.LineNumber);
        } else {
            pdg_crash_log(log, "  #%-2d 0x%p  %s\n", frame_num, (void*)(uintptr_t)addr, name);
        }
        frame_num++;
    }
#else
    pdg_crash_log(log, "  (Unsupported architecture for stack walk)\n");
#endif

    SymCleanup(process);
    pdg_crash_log(log, "=== END PDG C++ STACK TRACE ===\n\n");

    pdg_crash_log(log, "=== JavaScript stack trace (if available) ===\n");
    pdg_win32_crash_dump_js_stack(log);
    pdg_crash_log(log, "=== END JavaScript stack trace ===\n\n");

    fflush(stderr);
    if (log) {
        fclose(log);
        pdg_crash_log((FILE*)0, "Crash log also written to pdg_crash.log\n");
    }
    return EXCEPTION_EXECUTE_HANDLER;
}

} // anonymous namespace

extern "C" void pdg_install_win32_crash_handler(void) {
    SetUnhandledExceptionFilter(pdg_unhandled_exception_filter);
}

#else

extern "C" void pdg_install_win32_crash_handler(void) {
    (void)0;
}

#endif // _WIN32
