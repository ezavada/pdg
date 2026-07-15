// -----------------------------------------------
// pdg_node.cpp
//
// support and bindings for pdg game engine as a
// node.js add-on
//
// Written by Ed Zavada, 2012
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

//#define PDG_STANDALONE_NODE_APP
//#define WANT_TRACE
//#define WANT_DEBUG_LOG
//#define WANT_VERBOSE_DEBUG_LOG

#ifdef PDG_USE_LIBPNG
#include "png.h"
#endif

// Prevent Windows min/max macros from being defined
#ifdef _WIN32
#define NOMINMAX
#endif

#ifdef PDG_STANDALONE_NODE_APP

#include "cppgc/platform.h"
#define NODE_WANT_INTERNALS 1
#include "node_internals.h"
#include "node_binding.h"
#include "node_errors.h"
#include "env.h"
#include "env-inl.h"
#include "node_realm.h"
#include "node_context_data.h"
#include <memory>
#endif

#include "node.h"
#include "v8.h"
#include "uv.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <signal.h>
#include <cstdio>

// Linux-specific headers
#ifndef _WIN32
#include <execinfo.h>
#include <dlfcn.h>
#include <cxxabi.h>
#endif

// PDG-specific includes
#include "pdg-lib.h"
#include "pdg/version.h"

#ifdef PDG_USE_GLFW
#include <GLFW/glfw3.h>
#endif

// Define missing version strings if not already defined
#ifndef cpVersionString
extern "C" const char* cpVersionString;
#endif
#include "../generated/v8/pdg_script_interface.h"
#ifdef PDG_STANDALONE_NODE_APP
#include "pdg_natives.h"
#include "pdg_script_bindings.h"
#include "../javascript/v8/pdg_script_macros.h"
#include "../javascript/v8/pdg_v8_support.h"
#endif

#ifndef WANT_TRACE
  #define TRACE(msg)
  #define TRACEIN
  #define TRACEOUT
#else
  #define TRACE(msg)   std::cerr << "TRACE: in "<<__func__<<" at "<<__FILE__<<":" << __LINE__ << " " << msg << "\n"
  #define TRACEIN TRACE("ENTER")
  #define TRACEOUT TRACE("EXIT")
#endif

// Stub for missing node::SnapshotBuilder::GetEmbeddedSnapshotData()
// This prevents linker errors when Node.js snapshots are not properly built
namespace node {
    struct SnapshotData;  // Forward declaration
    
    // Define the SnapshotBuilder class with the missing function
    class SnapshotBuilder {
    public:
        static const SnapshotData* GetEmbeddedSnapshotData();
    };
}

// Implementation of the stub function
const node::SnapshotData* node::SnapshotBuilder::GetEmbeddedSnapshotData() {
    std::cerr << "WARNING: node::SnapshotBuilder::GetEmbeddedSnapshotData() called but not implemented. "
              << "Node.js snapshots are disabled in this build." << std::endl;
    return nullptr;
}

// Forward declarations
int RunNodeInstance(node::MultiIsolatePlatform* platform,
                   const std::vector<std::string>& args,
                   const std::vector<std::string>& exec_args);

// PDG namespace functions
namespace pdg {
#ifdef PDG_STANDALONE_NODE_APP
    void addProcessVersions(v8::Local<v8::Object> process);
    void setupCppBindings(v8::Local<v8::Object> process);
    void installIntoNodeApplication(node::Environment* env);
    int Start(int argc, char** argv);
    void CheckForSavedJavaScriptErrors(); // For debugging assertion failures
    void AbortSignalHandler(int signal); // Signal handler for assertion failures
#endif
    void initBindings(v8::Local<v8::Object> target);

#ifdef PDG_STANDALONE_NODE_APP
    // Helper function to handle V8 script errors
    void handleV8ScriptError(v8::Isolate* isolate, v8::Local<v8::Context> context, 
                            v8::TryCatch& try_catch, const std::string& operation) {
        std::cerr << "[PDG] ERROR: " << operation << " failed!" << std::endl;
        if (try_catch.HasCaught()) {
            v8::String::Utf8Value error_msg(isolate, try_catch.Exception());
            std::cerr << "[PDG] JavaScript error: " << *error_msg << std::endl;
            
            // Get detailed error information
            if (try_catch.HasTerminated()) {
                std::cerr << "[PDG] Script execution was terminated" << std::endl;
            }
            
            // Get the error location and context
            if (try_catch.Message().IsEmpty() == false) {
                v8::Local<v8::Message> message = try_catch.Message();
                v8::String::Utf8Value filename(isolate, message->GetScriptResourceName());
                int line_number = message->GetLineNumber(context).FromMaybe(-1);
                int start_column = message->GetStartColumn(context).FromMaybe(-1);
                int end_column = message->GetEndColumn(context).FromMaybe(-1);
                
                std::cerr << "[PDG] Error location: " << *filename << ":" << line_number;
                if (start_column >= 0) {
                    std::cerr << ":" << start_column;
                    if (end_column >= 0 && end_column != start_column) {
                        std::cerr << "-" << end_column;
                    }
                }
                std::cerr << std::endl;
                
                // Get the source line with the error
                v8::MaybeLocal<v8::String> maybe_source_line = message->GetSourceLine(context);
                if (!maybe_source_line.IsEmpty()) {
                    v8::Local<v8::String> source_line = maybe_source_line.ToLocalChecked();
                    v8::String::Utf8Value source_line_utf8(isolate, source_line);
                    if (source_line_utf8.length() > 0) {
                        std::cerr << "[PDG] Source line: " << *source_line_utf8 << std::endl;
                        
                        // Show the problematic token if we have column info
                        if (start_column >= 0 && end_column >= 0 && start_column < source_line_utf8.length()) {
                            std::string line_str(*source_line_utf8);
                            if (start_column < line_str.length()) {
                                int token_length = std::min(end_column - start_column, static_cast<int>(line_str.length()) - start_column);
                                std::string token = line_str.substr(start_column, token_length);
                                std::cerr << "[PDG] Problematic token: '" << token << "'" << std::endl;
                            }
                        }
                    }
                }
            }
            
            // Also try to get the stack trace
            v8::Local<v8::Value> stack_trace = try_catch.StackTrace(context).ToLocalChecked();
            if (!stack_trace.IsEmpty()) {
                v8::String::Utf8Value stack_msg(isolate, stack_trace);
                std::cerr << "[PDG] Stack trace: " << *stack_msg << std::endl;
            }
        }
        // Abort program execution
        std::cerr << "[PDG] Fatal error occurred, aborting program execution" << std::endl;
        std::abort();
    }
#endif // PDG_STANDALONE_NODE_APP
 }

#ifdef PDG_STANDALONE_NODE_APP
// Add PDG version information to process.versions
void pdg::addProcessVersions(v8::Local<v8::Object> process) {
    TRACEIN;
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    // Get the versions object
    v8::Local<v8::String> versions_symbol = v8::String::NewFromUtf8(isolate, "versions").ToLocalChecked();
    v8::Local<v8::Object> versions = process->Get(context, versions_symbol).ToLocalChecked()->ToObject(context).ToLocalChecked();
    
    // Add PDG version
    v8::Local<v8::String> pdg_symbol = v8::String::NewFromUtf8(isolate, "pdg").ToLocalChecked();
    v8::Local<v8::String> pdg_version = v8::String::NewFromUtf8(isolate, PDG_VERSION).ToLocalChecked();
    versions->Set(context, pdg_symbol, pdg_version).Check();
    
    // Add other library versions if available
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    v8::Local<v8::String> chipmunk_symbol = v8::String::NewFromUtf8(isolate, "chipmunk").ToLocalChecked();
    v8::Local<v8::String> chipmunk_version = v8::String::NewFromUtf8(isolate, cpVersionString).ToLocalChecked();
    versions->Set(context, chipmunk_symbol, chipmunk_version).Check();
#endif

#ifdef PDG_USE_GLFW
    v8::Local<v8::String> glfw_symbol = v8::String::NewFromUtf8(isolate, "glfw").ToLocalChecked();
    char glfw_vers_str[256];
    std::snprintf(glfw_vers_str, sizeof(glfw_vers_str), "%d.%d.%d", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
    v8::Local<v8::String> glfw_version = v8::String::NewFromUtf8(isolate, glfw_vers_str).ToLocalChecked();
    versions->Set(context, glfw_symbol, glfw_version).Check();
#endif

#ifdef PDG_USE_LIBPNG
    v8::Local<v8::String> libpng_symbol = v8::String::NewFromUtf8(isolate, "libpng").ToLocalChecked();
#ifdef PNG_LIBPNG_VER_STRING
    v8::Local<v8::String> libpng_version = v8::String::NewFromUtf8(isolate, PNG_LIBPNG_VER_STRING).ToLocalChecked();
#else
    v8::Local<v8::String> libpng_version = v8::String::NewFromUtf8(isolate, "Unknown").ToLocalChecked();
#endif
    versions->Set(context, libpng_symbol, libpng_version).Check();
#endif
    TRACEOUT;
}

void pdg::setupCppBindings(v8::Local<v8::Object> process) {
    TRACEIN;
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

#ifdef WANT_DEBUG_LOG
    std::cerr << "[PDG] C++ setupCppBindings: Setting up process.pdg with C++ bindings" << std::endl;
#endif
    
    // Initialize C++ module
    v8::Local<v8::Object> exports = v8::Object::New(isolate);
    
#ifdef WANT_DEBUG_LOG
    std::cerr << "[PDG] C++ setupCppBindings: Before initBindings - exports has " 
              << exports->GetPropertyNames(isolate->GetCurrentContext()).ToLocalChecked()->Length() << " properties" << std::endl;
#endif
    
    pdg::initBindings(exports); // pdg C++ module init
    
#ifdef WANT_DEBUG_LOG
    v8::Local<v8::Array> prop_names = exports->GetPropertyNames(isolate->GetCurrentContext()).ToLocalChecked();
    std::cerr << "[PDG] C++ setupCppBindings: After initBindings - exports has " << prop_names->Length() << " properties" << std::endl;
    
    // Check for Color and Quad specifically
    v8::Local<v8::Value> color_val = exports->Get(isolate->GetCurrentContext(), 
        v8::String::NewFromUtf8(isolate, "Color").ToLocalChecked()).ToLocalChecked();
    v8::Local<v8::Value> quad_val = exports->Get(isolate->GetCurrentContext(), 
        v8::String::NewFromUtf8(isolate, "Quad").ToLocalChecked()).ToLocalChecked();
    std::cerr << "[PDG] C++ setupCppBindings: Color present: " << (!color_val->IsUndefined() ? "YES" : "NO") << std::endl;
    std::cerr << "[PDG] C++ setupCppBindings: Quad present: " << (!quad_val->IsUndefined() ? "YES" : "NO") << std::endl;
#endif
    
    // Add PDG module to process.pdg
    v8::Local<v8::String> pdg_symbol = v8::String::NewFromUtf8(isolate, "pdg").ToLocalChecked();
    process->Set(isolate->GetCurrentContext(), pdg_symbol, exports).Check();
    
    // Verify that process.pdg was set correctly
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::MaybeLocal<v8::Value> maybe_pdg = process->Get(context, pdg_symbol);
    if (!maybe_pdg.IsEmpty()) {
        v8::Local<v8::Value> pdg_value = maybe_pdg.ToLocalChecked();
        if (pdg_value->IsObject()) {
#ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] C++ setupCppBindings: process.pdg is now set and verified" << std::endl;
#endif
        } else {
            std::cerr << "[PDG] C++ setupCppBindings: ERROR: process.pdg is not an object!" << std::endl;
        }
    } else {
        std::cerr << "[PDG] C++ setupCppBindings: ERROR: process.pdg is empty!" << std::endl;
    }
    
    TRACEOUT;
}

// Install the PDG framework into the Node.js application as linked bindings
void pdg::installIntoNodeApplication(node::Environment* env) {
    TRACEIN;
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
#ifdef WANT_DEBUG_LOG
    std::cerr << "[PDG] C++ installIntoNodeApplication: Installing native modules as linked bindings" << std::endl;
#endif
        
    // Add the main PDG module as a linked binding
    for (int i = 0; pdg::natives[i].name; i++) {
#ifdef WANT_DEBUG_LOG
        std::cerr << "[PDG] C++ installIntoNodeApplication: Adding linked binding: " << pdg::natives[i].name << std::endl;
#endif
        // Create a registration function for this module
        auto register_func = [](v8::Local<v8::Object> exports, 
                               v8::Local<v8::Value> module, 
                               v8::Local<v8::Context> context, 
                               void* priv) {
            v8::Isolate* isolate = context->GetIsolate();
            const char* source = static_cast<const char*>(priv);
            const char* native_name = nullptr;
            size_t source_len = 0;
            for (int j = 0; pdg::natives[j].name; j++) {
                if (pdg::natives[j].source == source) {
                    native_name = pdg::natives[j].name;
                    source_len = pdg::natives[j].source_len;
                    break;
                }
            }
            if (!native_name) native_name = "unknown";
            //std::cerr << "[PDG] register_func: source ptr=" << (void*)source << ", len=" << source_len << std::endl;
            if (!source || source_len == 0) {
                std::cerr << "[PDG] ERROR: Source is null or length is zero!" << std::endl;
                return;
            }
#ifdef WANT_VERBOSE_DEBUG_LOG
            // Print first 32 bytes as hex for debugging
            char hexbuf[256];
            pdg::OS::binaryDump(hexbuf, sizeof(hexbuf), source, std::min<size_t>(32, source_len), 16);
            std::cerr << "[PDG] Source (first 32 bytes):\n" << hexbuf << std::endl;
#endif
            // Create a script origin with the actual native name
            v8::Local<v8::String> filename = v8::String::NewFromUtf8(isolate, native_name).ToLocalChecked();
            v8::ScriptOrigin origin(filename);
            
            // Create the source string
            v8::MaybeLocal<v8::String> maybe_source_str = v8::String::NewFromUtf8(isolate, source, v8::NewStringType::kNormal, static_cast<int>(source_len));
            if (maybe_source_str.IsEmpty()) {
                std::cerr << "[PDG] ERROR: v8::String::NewFromUtf8 returned empty MaybeLocal!" << std::endl;
                return;
            }
            v8::Local<v8::String> source_str = maybe_source_str.ToLocalChecked();
            
            // Compile the script
            v8::TryCatch try_catch(isolate);
            v8::MaybeLocal<v8::Script> maybe_script = v8::Script::Compile(context, source_str, &origin);
            if (maybe_script.IsEmpty()) {
                pdg::handleV8ScriptError(isolate, context, try_catch, "v8::Script::Compile");
                return;
            }
            v8::Local<v8::Script> script = maybe_script.ToLocalChecked();
            
            // Ensure module.exports points to the same object as exports (CommonJS requirement)
            if (module->IsObject()) {
                v8::Local<v8::Object> module_obj = module->ToObject(context).ToLocalChecked();
                module_obj->Set(context, v8::String::NewFromUtf8(isolate, "exports").ToLocalChecked(), exports).Check();
#ifdef WANT_DEBUG_LOG
                std::cerr << "[PDG] C++ register_func(" << native_name << "): Set up module.exports to point to exports object" << std::endl;
#endif
            }
            
            v8::Local<v8::Object> global = context->Global();
            
            // The main 'pdg' module needs full global access for Node.js internals
            // Other JavaScript modules can be wrapped for isolation  
            bool is_main_pdg_module = (std::strcmp(native_name, "pdg") == 0);
            
            if (is_main_pdg_module) {
                // For the main pdg module, set up global state
                global->Set(context, v8::String::NewFromUtf8(isolate, "module").ToLocalChecked(), module).Check();
                global->Set(context, v8::String::NewFromUtf8(isolate, "exports").ToLocalChecked(), exports).Check();
            } else {
                // For all but pdg.js module, use function wrapping to avoid global state corruption
                // Wrap the script in a function to provide module and exports as local variables
                std::string wrapped_source = "(function(module, exports) {\n";
                wrapped_source += std::string(source, source_len);
                wrapped_source += "\n});";
                
                v8::MaybeLocal<v8::String> maybe_wrapped_source = v8::String::NewFromUtf8(
                    isolate, wrapped_source.c_str(), v8::NewStringType::kNormal, static_cast<int>(wrapped_source.length()));
                if (maybe_wrapped_source.IsEmpty()) {
                    std::cerr << "[PDG] ERROR: Failed to create wrapped source string!" << std::endl;
                    return;
                }
                v8::Local<v8::String> wrapped_source_str = maybe_wrapped_source.ToLocalChecked();
                
                // Compile the wrapped script
                v8::TryCatch compile_try_catch(isolate);
                v8::MaybeLocal<v8::Script> maybe_wrapped_script = v8::Script::Compile(context, wrapped_source_str, &origin);
                if (maybe_wrapped_script.IsEmpty()) {
                    pdg::handleV8ScriptError(isolate, context, compile_try_catch, "v8::Script::Compile (wrapped)");
                    return;
                }
                v8::Local<v8::Script> wrapped_script = maybe_wrapped_script.ToLocalChecked();
                
                // Store the wrapped script to use later
                script = wrapped_script;
            }
            
#ifdef WANT_VERBOSE_DEBUG_LOG
            std::cerr << "[PDG] C++ register_func(" << native_name << "): Set global.module (ptr=" << (void*)(*module) << ") and global.exports (ptr=" << (void*)(*exports) << ")" << std::endl;
#endif
            
            // Add a require function that can resolve native modules
            struct RequireContext {
                v8::Global<v8::Object> module;
                v8::Global<v8::Object> exports;
            };
            auto* require_ctx = new RequireContext{
                v8::Global<v8::Object>(isolate, module->ToObject(context).ToLocalChecked()),
                v8::Global<v8::Object>(isolate, exports)
            };
            
            auto require_func = [](const v8::FunctionCallbackInfo<v8::Value>& args) {
                v8::Isolate* isolate = args.GetIsolate();
                v8::Local<v8::Context> context = isolate->GetCurrentContext();
                
                v8::Local<v8::External> data = args.Data().As<v8::External>();
                RequireContext* ctx = static_cast<RequireContext*>(data->Value());
                v8::Local<v8::Object> module_obj = ctx->module.Get(isolate);
                v8::Local<v8::Object> exports = ctx->exports.Get(isolate);
                
                if (args.Length() < 1) {
                    isolate->ThrowException(v8::Exception::TypeError(
                        v8::String::NewFromUtf8(isolate, "require() expects a module name").ToLocalChecked()));
                    return;
                }
                
                v8::String::Utf8Value module_name(isolate, args[0]);
                std::string name(*module_name);
#ifdef WANT_DEBUG_LOG
                std::cerr << "[PDG] C++ require: Attempting to require module: " << name << std::endl;
#endif
                
                // Prevent recursion: if this is the current module, return exports
                v8::Local<v8::Value> id_val = module_obj->Get(context, v8::String::NewFromUtf8(isolate, "id").ToLocalChecked()).ToLocalChecked();
                v8::String::Utf8Value current_module_id(isolate, id_val);
                if (*current_module_id && name == *current_module_id) {
#ifdef WANT_DEBUG_LOG
                    std::cerr << "[PDG] C++ require: Recursion detected for module: " << name << ", returning exports immediately." << std::endl;
#endif
                    args.GetReturnValue().Set(exports);
                    return;
                }
                
                // Special case for 'pdg' module: get it from process.pdg which is our single source of truth
                if (std::strcmp(name.c_str(), "pdg") == 0) {
#ifdef WANT_DEBUG_LOG
                    std::cerr << "[PDG] C++ require: Intercepting require('pdg')" << std::endl;
#endif
                    v8::Local<v8::Object> global = context->Global();
                    v8::Local<v8::Value> process = global->Get(context, v8::String::NewFromUtf8(isolate, "process").ToLocalChecked()).ToLocalChecked();
                    v8::Local<v8::Object> process_obj = process->ToObject(context).ToLocalChecked();
                    v8::Local<v8::Value> process_pdg = process_obj->Get(context, v8::String::NewFromUtf8(isolate, "pdg").ToLocalChecked()).ToLocalChecked();
                    if (!process_pdg.IsEmpty() && !process_pdg->IsUndefined()) {
#ifdef WANT_DEBUG_LOG
                        std::cerr << "[PDG] C++ require: Found process.pdg, returning it" << std::endl;
#endif
                        
                        // Check if if pdg has tm available and how many properties it has
                        if (process_pdg->IsObject()) {
#ifdef WANT_DEBUG_LOG
                            v8::Local<v8::Object> pdg_obj = process_pdg->ToObject(context).ToLocalChecked();
                            v8::Local<v8::Array> prop_names = pdg_obj->GetPropertyNames(context).ToLocalChecked();  
                            std::cerr << "[PDG] C++ require: process.pdg has " << prop_names->Length() << " properties" << std::endl;
                            v8::Local<v8::Value> tm_val = pdg_obj->Get(context, v8::String::NewFromUtf8(isolate, "tm").ToLocalChecked()).ToLocalChecked();
                            std::cerr << "[PDG] C++ require: process.pdg.tm type=" << (tm_val->IsUndefined() ? "undefined" : (tm_val->IsObject() ? "object" : "other")) << std::endl;
#endif
                        } else {
                            std::cerr << "[PDG] C++ require: process.pdg is not an object" << std::endl;
                        }
                        
                        args.GetReturnValue().Set(process_pdg);
                        return;
                    } else {
                        std::cerr << "[PDG] C++ require: process.pdg not found or undefined" << std::endl;
                    }
                }
                
                // Try to find the native module
                for (int i = 0; pdg::natives[i].name; i++) {
                    if (std::strcmp(pdg::natives[i].name, name.c_str()) == 0) {
#ifdef WANT_DEBUG_LOG
                        std::cerr << "[PDG] C++ require: Found native module: " << name << ", loading as linked binding" << std::endl;
#endif
                        // Load the linked binding using process._linkedBinding
                        v8::Local<v8::Object> global = context->Global();
                        v8::Local<v8::Value> process = global->Get(context, v8::String::NewFromUtf8(isolate, "process").ToLocalChecked()).ToLocalChecked();
                        v8::Local<v8::Object> process_obj = process->ToObject(context).ToLocalChecked();
                        
                        v8::Local<v8::Value> linked_binding = process_obj->Get(context, v8::String::NewFromUtf8(isolate, "_linkedBinding").ToLocalChecked()).ToLocalChecked();
                        if (linked_binding->IsFunction()) {
                            v8::Local<v8::Function> linked_binding_func = v8::Local<v8::Function>::Cast(linked_binding);
                            v8::Local<v8::Value> args_array[] = { v8::String::NewFromUtf8(isolate, name.c_str()).ToLocalChecked() };
                            v8::Local<v8::Value> result;
                            if (linked_binding_func->Call(context, process_obj, 1, args_array).ToLocal(&result)) {
#ifdef WANT_DEBUG_LOG
                                std::cerr << "[PDG] C++ require: Successfully loaded linked binding: " << name << std::endl;
#endif
                                args.GetReturnValue().Set(result);
                                return;
                            } else {
                                std::cerr << "[PDG] C++ require: Failed to call _linkedBinding for: " << name << std::endl;
                            }
                        } else {
                            std::cerr << "[PDG] C++ require: _linkedBinding is not a function" << std::endl;
                        }
                        
                        // Fallback: return an empty object
                        v8::Local<v8::Object> native_exports = v8::Object::New(isolate);
                        args.GetReturnValue().Set(native_exports);
                        return;
                    }
                }
                
                // If not found in natives, try to use the public require function
#ifdef WANT_DEBUG_LOG
                std::cerr << "[PDG] C++ require: Module " << name << " not found in natives, trying public require" << std::endl;
#endif
                // Get the public require function from the global scope (has proper module resolution context)
                v8::Local<v8::Object> global = context->Global();
                v8::Local<v8::Value> public_require = global->Get(context, v8::String::NewFromUtf8(isolate, "_publicRequire").ToLocalChecked()).ToLocalChecked();
                
                if (public_require->IsFunction()) {
                    v8::Local<v8::Function> require_func = v8::Local<v8::Function>::Cast(public_require);
                    v8::Local<v8::Value> args_array[] = { args[0] };
                    v8::Local<v8::Value> result;
                    if (require_func->Call(context, global, 1, args_array).ToLocal(&result)) {
#ifdef WANT_DEBUG_LOG
                        std::cerr << "[PDG] C++ require: Successfully loaded via public require: " << name << std::endl;
#endif
                        args.GetReturnValue().Set(result);
                        return;
                    } else {
                        std::cerr << "[PDG] C++ require: Failed to call public require for: " << name << std::endl;
                    }
                } else {
                    // Fallback to original require if public require is not available
                    v8::Local<v8::Value> original_require = global->Get(context, v8::String::NewFromUtf8(isolate, "_originalRequire").ToLocalChecked()).ToLocalChecked();
                    
                    if (original_require->IsFunction()) {
                        v8::Local<v8::Function> require_func = v8::Local<v8::Function>::Cast(original_require);
                        v8::Local<v8::Value> args_array[] = { args[0] };
                        v8::Local<v8::Value> result;
                        if (require_func->Call(context, global, 1, args_array).ToLocal(&result)) {
#ifdef WANT_DEBUG_LOG
                            std::cerr << "[PDG] C++ require: Successfully loaded via original require: " << name << std::endl;
#endif
                            args.GetReturnValue().Set(result);
                            return;
                        } else {
                            std::cerr << "[PDG] C++ require: Failed to call original require for: " << name << std::endl;
                        }
                    } else {
                        std::cerr << "[PDG] C++ require: Neither _publicRequire nor _originalRequire is available" << std::endl;
                    }
                }
                
                // If all else fails, throw an error
                std::string error_msg = "Cannot find module '" + name + "'";
                isolate->ThrowException(v8::Exception::Error(
                    v8::String::NewFromUtf8(isolate, error_msg.c_str()).ToLocalChecked()));
            }; // end of require_func
            
            v8::Local<v8::External> require_data = v8::External::New(isolate, require_ctx);
            v8::Local<v8::Function> require = v8::Function::New(context, require_func, require_data).ToLocalChecked();
            global->Set(context, v8::String::NewFromUtf8(isolate, "require").ToLocalChecked(), require).Check();
            
            // Only initialize C++ bindings for the main PDG module
            // JavaScript modules (coordinates, color, etc.) should only export their JS classes
            if (std::strcmp(native_name, "pdg") == 0) {
#ifdef WANT_VERBOSE_DEBUG_LOG
                v8::Local<v8::Array> prop_names_before = exports->GetPropertyNames(context).ToLocalChecked();
                std::cerr << "[PDG] C++ register_func(" << native_name << "): Before initBindings - exports has " 
                          << prop_names_before->Length() << " properties" << std::endl;
#endif
                pdg::initBindings(exports);
#ifdef WANT_VERBOSE_DEBUG_LOG
                v8::Local<v8::Array> prop_names_after = exports->GetPropertyNames(context).ToLocalChecked();
                std::cerr << "[PDG] C++ register_func(" << native_name << "): After initBindings - exports has " 
                          << prop_names_after->Length() << " properties" << std::endl;
#endif
            }
            
            // Execute all modules immediately, including pdg_main_v24
            {
                // For other modules, execute immediately as before
#ifdef WANT_DEBUG_LOG
                std::cerr << "[PDG] C++ installIntoNodeApplication: executing Module " << native_name << "..." << std::endl;
#endif
                v8::TryCatch run_try_catch(isolate);
                v8::MaybeLocal<v8::Value> run_result;
                
                if (is_main_pdg_module) {
                    // For the main pdg module, execute directly  
                    run_result = script->Run(context);
                } else {
                    // Execute the wrapped script to get the function
                    v8::MaybeLocal<v8::Value> wrapped_result = script->Run(context);
                    if (wrapped_result.IsEmpty()) {
                        std::cerr << "[PDG] ERROR: Wrapped script execution failed!" << std::endl;
                        pdg::handleV8ScriptError(isolate, context, run_try_catch, "wrapped_script->Run");
                        return;
                    }
                    
                    // The result should be a function - call it with module and exports
                    v8::Local<v8::Value> function_val = wrapped_result.ToLocalChecked();
                    if (!function_val->IsFunction()) {
                        std::cerr << "[PDG] ERROR: Wrapped script did not return a function!" << std::endl;
                        return;
                    }
                    
                    v8::Local<v8::Function> module_function = v8::Local<v8::Function>::Cast(function_val);
                    
                    // Call the function with just module and exports
                    v8::Local<v8::Value> args[] = { module, exports };
                    run_result = module_function->Call(context, v8::Undefined(isolate), 2, args);
                }
                if (run_result.IsEmpty()) {
                    std::cerr << "[PDG] ERROR: Script execution failed!" << std::endl;
                    pdg::handleV8ScriptError(isolate, context, run_try_catch, "script->Run");
                    return;
                }
                

                
#ifdef WANT_DEBUG_LOG

                // For 'pdg' module, check number of properties for debugging
                if (std::strcmp(native_name, "pdg") == 0) {
                    v8::Local<v8::Value> process = global->Get(context, v8::String::NewFromUtf8(isolate, "process").ToLocalChecked()).ToLocalChecked();
                    v8::Local<v8::Object> process_obj = process->ToObject(context).ToLocalChecked();
                    v8::Local<v8::Value> process_pdg = process_obj->Get(context, v8::String::NewFromUtf8(isolate, "pdg").ToLocalChecked()).ToLocalChecked();
                    
                    if (!process_pdg.IsEmpty() && process_pdg->IsObject()) {
                        v8::Local<v8::Object> module_exports_obj = process_pdg->ToObject(context).ToLocalChecked();
                        v8::Local<v8::Array> prop_names = module_exports_obj->GetPropertyNames(context).ToLocalChecked();
                        std::cerr << "[PDG] C++ installIntoNodeApplication: process.pdg has " << prop_names->Length() << " properties" << std::endl;
                    }
                }

                std::cerr << "[PDG] C++ installIntoNodeApplication: Module " << native_name << " loaded successfully with C++ bindings" << std::endl;
#endif
            }
        };
        
        // Add as a linked binding
        node::AddLinkedBinding(env, pdg::natives[i].name, register_func, (void*)pdg::natives[i].source);
        
#ifdef WANT_DEBUG_LOG
        std::cerr << "[PDG] C++ installIntoNodeApplication: Successfully added linked binding: " << pdg::natives[i].name << std::endl;
#endif
    }

    TRACEOUT;
}
#endif // PDG_STANDALONE_NODE_APP

#ifdef PDG_STANDALONE_NODE_APP

#ifdef _WIN32
extern "C" void pdg_install_win32_crash_handler(void);
#endif

int main(int argc, char *argv[]) {
#ifdef _WIN32
	// Install first so C++ crashes (e.g. in test suite) print stack trace to stderr and pdg_crash.log
	pdg_install_win32_crash_handler();
#endif
	pdg_LibSaveArgs(argc, (const char**)argv);
	return pdg::Start(argc, argv);
}

int pdg::Start(int argc, char** argv) {
  TRACEIN;

  // Set up command line arguments
  argv = uv_setup_args(argc, argv);
  std::vector<std::string> args(argv, argv + argc);
  
  // Store original arguments before Node.js processes them
  std::string orig_args_str;
  for (size_t i = 0; i < args.size(); i++) {
    if (i > 0) orig_args_str += "\n";
    orig_args_str += args[i];
  }
#ifndef _WIN32
  setenv("PDG_ORIGINAL_ARGS", orig_args_str.c_str(), 1);
#else
  _putenv_s("PDG_ORIGINAL_ARGS", orig_args_str.c_str());
#endif
  
  // Parse Node.js CLI options and print any errors
  std::shared_ptr<node::InitializationResult> result =
      node::InitializeOncePerProcess(args, {
        node::ProcessInitializationFlags::kNoInitializeV8,
        node::ProcessInitializationFlags::kNoInitializeNodeV8Platform,
        node::ProcessInitializationFlags::kNoInitializeCppgc
      });

  for (const std::string& error : result->errors())
    fprintf(stderr, "%s: %s\n", args[0].c_str(), error.c_str());
  if (result->early_return()) {
    return result->exit_code();
  }

  // Create a v8::Platform instance for multi-isolate support
  std::unique_ptr<node::MultiIsolatePlatform> platform =
      node::MultiIsolatePlatform::Create(4);
  v8::V8::InitializePlatform(platform.get());
  cppgc::InitializeProcess(platform->GetPageAllocator());
  v8::V8::Initialize();

  // Register signal handlers after V8 initialization but before Node.js environment setup
  // This ensures our handlers take precedence over Node.js WASM trap handlers
#ifndef _WIN32
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = pdg::AbortSignalHandler;
  sa.sa_flags = 0;
  sigfillset(&sa.sa_mask);
  
  sigaction(SIGABRT, &sa, nullptr);
  sigaction(SIGSEGV, &sa, nullptr); // Also catch segfaults
#endif

  // Run the Node.js instance
  int ret = RunNodeInstance(platform.get(), result->args(), result->exec_args());

  // Clean up
  v8::V8::Dispose();
  v8::V8::DisposePlatform();
  node::TearDownOncePerProcess();
  
  TRACEOUT;
  return ret;
}


int RunNodeInstance(node::MultiIsolatePlatform* platform,
                   const std::vector<std::string>& args,
                   const std::vector<std::string>& exec_args) {
    TRACEIN;
  int exit_code = 0;

  // Keep the full parsed argv for Node's environment setup.
  // PDG-specific dispatch still uses PDG_ORIGINAL_ARGS inside pdg_main_v24.js.
#ifdef WANT_DEBUG_LOG
  std::cerr << "[PDG] RunNodeInstance: Using " << args.size() << " args for Node.js environment setup" << std::endl;
#endif

  // Set up a libuv event loop, v8::Isolate, and Node.js Environment
  std::vector<std::string> errors;
  std::unique_ptr<node::CommonEnvironmentSetup> setup =
      node::CommonEnvironmentSetup::Create(platform, &errors, args, exec_args);
  if (!setup) {
    for (const std::string& err : errors)
      fprintf(stderr, "%s: %s\n", args[0].c_str(), err.c_str());
    return 1;
  }

  v8::Isolate* isolate = setup->isolate();
  node::Environment* env = setup->env();

  {
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);
    // The v8::Context needs to be entered when node::LoadEnvironment() is called
    v8::Context::Scope context_scope(setup->context());

    // Find pdg_bootstrap.js content to pass as the main script
    std::string pdg_bootstrap_script;
    for (int i = 0; pdg::natives[i].name; i++) {
        if (pdg::natives[i].source == pdg::pdg_bootstrap_native) {
            pdg_bootstrap_script = std::string(pdg::natives[i].source, pdg::natives[i].source_len);
            break;
        }
    }
    
    if (pdg_bootstrap_script.empty()) {
        fprintf(stderr, "Error: Could not find pdg_bootstrap.js in natives\n");
        return 1;
    }

    // Set up the Node.js instance for execution using pdg_bootstrap.js as the main script
    v8::MaybeLocal<v8::Value> loadenv_ret = node::LoadEnvironment(
        env,
        pdg_bootstrap_script,
        [](node::Environment* env, v8::Local<v8::Value> process, v8::Local<v8::Value> require) {
            // This is the preload callback that runs before any user code
            // We can use this to set up PDG-specific initialization
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            
            v8::Local<v8::Object> process_obj = process->ToObject(context).ToLocalChecked();
            
            // Add PDG version information to process.versions
            pdg::addProcessVersions(process_obj);

            // Setup C++ bindings
            pdg::setupCppBindings(process_obj);
                       
            // Install PDG natives
            pdg::installIntoNodeApplication(env);

#ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] C++ preload: PDG setup complete, bootstrap script will handle main execution" << std::endl;
#endif
        }
    );

    if (loadenv_ret.IsEmpty()) {
      // There has been a JS exception
      fprintf(stderr, "Error: Failed to setup PDG environment\n");
      return 1;
    }

#ifdef WANT_DEBUG_LOG
    std::cerr << "[PDG] RunNodeInstance: Bootstrap completed, starting event loop" << std::endl;
#endif
    
    // Run the event loop - this will execute our scheduled PDG main code
    exit_code = node::SpinEventLoop(env).FromMaybe(1);
    
#ifdef WANT_DEBUG_LOG
    std::cerr << "[PDG] RunNodeInstance: Event loop completed, performing proper shutdown" << std::endl;
#endif
    
    // Ensure proper environment shutdown to prevent segfaults
    // This follows the Node.js shutdown sequence from NodeMainInstance
    env->set_can_call_into_js(false);
#ifdef WANT_VERBOSE_DEBUG_LOG
    std::cerr << "[PDG] RunNodeInstance: Calling set_stopping(true)" << std::endl;
#endif
    env->set_stopping(true);
    env->stop_sub_worker_contexts();
#ifdef WANT_VERBOSE_DEBUG_LOG
    std::cerr << "[PDG] RunNodeInstance: Calling RunCleanup" << std::endl;
#endif
    env->RunCleanup();
#ifdef WANT_VERBOSE_DEBUG_LOG
    std::cerr << "[PDG] RunNodeInstance: Calling stop" << std::endl;
#endif
    // Stop the environment properly
    node::Stop(env);
  }

    TRACEOUT;
    return exit_code;
}

#endif // PDG_STANDALONE_NODE_APP

namespace pdg {

#ifdef PDG_STANDALONE_NODE_APP
// Check for saved JavaScript errors that haven't been thrown yet
extern bool s_HaveSavedError;
extern v8::Persistent<v8::Value> s_SavedError;

// Helper function to dump current JavaScript stack trace
void DumpCurrentJavaScriptStackTrace();

// Signal handler to catch assertion failures and check for JavaScript errors
void AbortSignalHandler(int signal) {
    std::cerr << "\n=== PROCESS ABORTING (Signal " << signal << ") ===" << std::endl;
    
    // Dump C++ stack trace
#ifndef _WIN32
    void *array[100];
    size_t size = backtrace(array, 100);
    
    std::cerr << "C++ Stack trace:" << std::endl;
    for (size_t i = 0; i < size; i++) {
        Dl_info info;
        if (dladdr(array[i], &info)) {
            int status;
            char *demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
            
            std::cerr << "#" << i << "  " << array[i] << " ";
            if (demangled) {
                std::cerr << demangled;
                free(demangled);
            } else if (info.dli_sname) {
                std::cerr << info.dli_sname;
            } else {
                std::cerr << "???";
            }
            
            if (info.dli_fname) {
                std::cerr << " in " << info.dli_fname;
            }
            std::cerr << std::endl;
        } else {
            std::cerr << "#" << i << "  " << array[i] << " ???" << std::endl;
        }
    }
    std::cerr << "=== END C++ STACK TRACE ===" << std::endl;
#else
    std::cerr << "C++ Stack trace not available on Windows" << std::endl;
#endif
    
    CheckForSavedJavaScriptErrors();
    
    // Also dump the current JavaScript stack trace if available
    std::cerr << "\n=== CURRENT JAVASCRIPT STACK TRACE ===" << std::endl;
    DumpCurrentJavaScriptStackTrace();
    std::cerr << "=== END JAVASCRIPT ERROR INFO ===" << std::endl;
    
    // Restore default handler and re-raise the signal
    ::signal(signal, SIG_DFL);
    ::raise(signal);
}

// Helper function to get current JavaScript stack trace
void DumpCurrentJavaScriptStackTrace() {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    if (!isolate) {
        std::cerr << "No V8 isolate available for JavaScript stack trace" << std::endl;
        return;
    }
    
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    if (context.IsEmpty()) {
        std::cerr << "No V8 context available for JavaScript stack trace" << std::endl;
        return;
    }
    
    try {
        // Create a new Error object to capture the current stack trace
        v8::Local<v8::String> error_name = v8::String::NewFromUtf8(isolate, "Error").ToLocalChecked();
        v8::Local<v8::Function> error_constructor = v8::Local<v8::Function>::Cast(
            context->Global()->Get(context, error_name).ToLocalChecked());
        
        if (!error_constructor.IsEmpty()) {
            v8::Local<v8::Value> error_obj;
            if (error_constructor->NewInstance(context).ToLocal(&error_obj)) {
                // Get the stack property from the Error object
                v8::Local<v8::String> stack_name = v8::String::NewFromUtf8(isolate, "stack").ToLocalChecked();
                v8::Local<v8::Value> stack_val = error_obj->ToObject(context).ToLocalChecked()->Get(context, stack_name).ToLocalChecked();
                
                if (!stack_val.IsEmpty() && stack_val->IsString()) {
                    v8::String::Utf8Value stack(isolate, stack_val);
                    std::cerr << "JavaScript Stack Trace:" << std::endl << *stack << std::endl;
                } else {
                    std::cerr << "Could not retrieve JavaScript stack trace" << std::endl;
                }
            } else {
                std::cerr << "Could not create Error object for stack trace" << std::endl;
            }
        } else {
            std::cerr << "Error constructor not available" << std::endl;
        }
    } catch (...) {
        std::cerr << "Exception occurred while trying to get JavaScript stack trace" << std::endl;
    }
}

void CheckForSavedJavaScriptErrors() {
    if (s_HaveSavedError) {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        if (isolate) {
            std::cerr << "Pending JavaScript Error: ";
            v8::Local<v8::Value> error = v8::Local<v8::Value>::New(isolate, s_SavedError);
            v8::String::Utf8Value error_msg(isolate, error);
            std::cerr << *error_msg << std::endl;
            
            // Try to get stack trace from the error object if it's an Error object
            if (error->IsObject()) {
                v8::Local<v8::Object> error_obj = error->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::Local<v8::Value> stack_val = error_obj->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "stack").ToLocalChecked()).ToLocalChecked();
                if (!stack_val.IsEmpty() && stack_val->IsString()) {
                    v8::String::Utf8Value stack(isolate, stack_val);
                    std::cerr << "JavaScript Stack Trace:" << std::endl << *stack << std::endl;
                }
            }
            std::cerr << std::endl;
        }
        s_HaveSavedError = false;
    }
}
#endif // PDG_STANDALONE_NODE_APP

#ifdef _WIN32
extern "C" void pdg_win32_crash_dump_js_stack(FILE* log) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    auto out = [log](const char* msg) {
        if (msg) {
            fputs(msg, stderr);
            if (log) { fputs(msg, log); fflush(log); }
        }
    };
    if (!isolate) {
        out("No V8 isolate available for JavaScript stack trace\n");
        return;
    }
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    if (context.IsEmpty()) {
        out("No V8 context available for JavaScript stack trace\n");
        return;
    }
    try {
        v8::Local<v8::String> error_name = v8::String::NewFromUtf8(isolate, "Error").ToLocalChecked();
        v8::Local<v8::Value> err_ctor_val = context->Global()->Get(context, error_name).ToLocalChecked();
        if (err_ctor_val.IsEmpty() || !err_ctor_val->IsFunction()) {
            out("Error constructor not available\n");
            return;
        }
        v8::Local<v8::Function> error_constructor = v8::Local<v8::Function>::Cast(err_ctor_val);
        v8::Local<v8::Value> error_obj;
        if (!error_constructor->NewInstance(context).ToLocal(&error_obj)) {
            out("Could not create Error object for stack trace\n");
            return;
        }
        v8::Local<v8::String> stack_name = v8::String::NewFromUtf8(isolate, "stack").ToLocalChecked();
        v8::Local<v8::Value> stack_val = error_obj->ToObject(context).ToLocalChecked()->Get(context, stack_name).ToLocalChecked();
        if (!stack_val.IsEmpty() && stack_val->IsString()) {
            v8::String::Utf8Value stack(isolate, stack_val);
            std::string s("JavaScript Stack Trace:\n");
            s += *stack;
            s += "\n";
            out(s.c_str());
        } else {
            out("Could not retrieve JavaScript stack trace\n");
        }
    } catch (...) {
        out("Exception occurred while trying to get JavaScript stack trace\n");
    }
}
#endif // _WIN32

void FatalException(v8::TryCatch& try_catch) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    
#ifdef PDG_STANDALONE_NODE_APP
    // First check for any saved JavaScript errors that haven't been thrown
    CheckForSavedJavaScriptErrors();
#endif
    
    // Extract the exception value
    v8::Local<v8::Value> exception = try_catch.Exception();
    v8::Local<v8::Message> message = try_catch.Message();
    
    std::cerr << "JavaScript Fatal Exception: ";
    
    // Print the error message
    if (!message.IsEmpty()) {
        v8::String::Utf8Value error_msg(isolate, exception);
        std::cerr << *error_msg << std::endl;
        
        // Print source location if available
        v8::Local<v8::Value> resource_name = message->GetScriptResourceName();
        if (!resource_name.IsEmpty() && !resource_name->IsUndefined()) {
            v8::String::Utf8Value filename(isolate, resource_name);
            std::cerr << "  at " << *filename << ":" << message->GetLineNumber(isolate->GetCurrentContext()).FromMaybe(0) << std::endl;
        }
        
        // Print stack trace if available
        v8::Local<v8::Value> stack_trace = try_catch.StackTrace(isolate->GetCurrentContext()).ToLocalChecked();
        if (!stack_trace.IsEmpty() && !stack_trace->IsUndefined()) {
            v8::String::Utf8Value stack(isolate, stack_trace);
            std::cerr << "Stack trace:" << std::endl << *stack << std::endl;
        }
    } else {
        v8::String::Utf8Value error_msg(isolate, exception);
        std::cerr << *error_msg << std::endl;
    }
    
    // Optionally call Node.js's FatalException if available
    // node::FatalException(isolate, try_catch);
}

// grab all the native class prototypes out of the process object and save them
extern "C" void scriptSetupCompleted() {
    TRACEIN;
  #ifdef WANT_DEBUG_LOG
    std::cerr << "[PDG] scriptSetupCompleted: Starting..." << std::endl;
  #endif
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    if (!isolate) {
        std::cerr << "[PDG] ERROR: scriptSetupCompleted called with null isolate" << std::endl;
        return;
    }

    v8::Local<v8::String> _pdgScriptClasses_symbol = v8::String::NewFromUtf8(isolate, "_pdgScriptClasses").ToLocalChecked();

    // Get the current context
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    if (context.IsEmpty()) {
        std::cerr << "[PDG] ERROR: scriptSetupCompleted called with empty context" << std::endl;
        return;
    }
    
    // Get process object directly from global context instead of through realm
    // This is more robust when Node.js realm isn't fully initialized
    v8::Local<v8::Object> global = context->Global();
    v8::Local<v8::String> process_symbol = v8::String::NewFromUtf8(isolate, "process").ToLocalChecked();
    v8::MaybeLocal<v8::Value> maybe_process = global->Get(context, process_symbol);
    
    if (maybe_process.IsEmpty()) {
        std::cerr << "[PDG] ERROR: process object not found in global context" << std::endl;
        return;
    }
    
    v8::Local<v8::Value> process_value = maybe_process.ToLocalChecked();
    if (!process_value->IsObject()) {
        std::cerr << "[PDG] ERROR: process is not an object" << std::endl;
        return;
    }
    
    v8::Local<v8::Object> process = process_value->ToObject(context).ToLocalChecked();

    // Try to get the _pdgScriptClasses property
  #ifdef WANT_DEBUG_LOG
    std::cerr << "[PDG] scriptSetupCompleted: Looking for _pdgScriptClasses in process object..." << std::endl;
  #endif
    v8::MaybeLocal<v8::Value> maybe_obj = process->Get(context, _pdgScriptClasses_symbol);
    if (maybe_obj.IsEmpty()) {
        std::cerr << "[PDG] WARNING: _pdgScriptClasses property not found in process object" << std::endl;
      #ifdef WANT_VERBOSE_DEBUG_LOG
        std::cerr << "[PDG] scriptSetupCompleted: Available properties in process object:" << std::endl;
        v8::Local<v8::Array> process_props = process->GetPropertyNames(context).ToLocalChecked();
        for (uint32_t i = 0; i < process_props->Length(); i++) {
            v8::Local<v8::Value> prop = process_props->Get(context, i).ToLocalChecked();
            v8::String::Utf8Value prop_str(isolate, prop);
            std::cerr << "[PDG] scriptSetupCompleted:   " << *prop_str << std::endl;
        }
      #endif
        return;
    }
    
    v8::Local<v8::Value> obj_value = maybe_obj.ToLocalChecked();
    if (!obj_value->IsObject()) {
        std::cerr << "[PDG] ERROR: _pdgScriptClasses is not an object" << std::endl;
        return;
    }
    
    v8::Local<v8::Object> obj = obj_value->ToObject(context).ToLocalChecked();
  #ifdef WANT_DEBUG_LOG
    std::cerr << "[PDG] scriptSetupCompleted: Found _pdgScriptClasses object" << std::endl;
#endif
    v8::MaybeLocal<v8::Array> maybe_array = obj->GetPropertyNames(context);
    if (maybe_array.IsEmpty()) {
        std::cerr << "[PDG] ERROR: Failed to get property names from _pdgScriptClasses object" << std::endl;
        return;
    }
    
    v8::Local<v8::Array> array = maybe_array.ToLocalChecked();
    int length = array->Length();
  #ifdef WANT_DEBUG_LOG
    std::cerr << "[PDG] scriptSetupCompleted: _pdgScriptClasses has " << length << " properties" << std::endl;
  #endif
    
    for (int i = 0; i < length; i++) {
        v8::MaybeLocal<v8::Value> maybe_prop = array->Get(context, i);
        if (maybe_prop.IsEmpty()) {
            std::cerr << "[PDG] WARNING: Failed to get property at index " << i << std::endl;
            continue;
        }
        
        v8::Local<v8::Value> prop = maybe_prop.ToLocalChecked();
        v8::MaybeLocal<v8::Value> maybe_proto = obj->Get(context, prop);
        if (maybe_proto.IsEmpty()) {
            std::cerr << "[PDG] WARNING: Failed to get prototype for property at index " << i << std::endl;
            continue;
        }
        
        v8::Local<v8::Value> proto_value = maybe_proto.ToLocalChecked();
        if (!proto_value->IsObject()) {
            std::cerr << "[PDG] WARNING: Prototype is not an object for property at index " << i << std::endl;
            continue;
        }
        
        v8::Local<v8::Object> proto = proto_value->ToObject(context).ToLocalChecked();
        
        // Convert property name to C string safely using the macro
        VALUE_TO_CSTRING(propName, prop);
      #ifdef WANT_VERBOSE_DEBUG_LOG
        std::cerr << "[PDG] scriptSetupCompleted: Processing property: " << propName << std::endl;
      #endif
        
        if (std::strcmp("Color", propName) == 0) {
          #ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] scriptSetupCompleted: Setting Color prototype" << std::endl;
          #endif
            v8_SetColorPrototype(proto);
        } else if (std::strcmp("Offset", propName) == 0) {
          #ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] scriptSetupCompleted: Setting Offset prototype" << std::endl;
          #endif
            v8_SetOffsetPrototype(proto);
        } else if (std::strcmp("Point", propName) == 0) {
          #ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] scriptSetupCompleted: Setting Point prototype" << std::endl;
          #endif
            v8_SetPointPrototype(proto);
        } else if (std::strcmp("Vector", propName) == 0) {
          #ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] scriptSetupCompleted: Setting Vector prototype" << std::endl;
          #endif
            v8_SetVectorPrototype(proto);
        } else if (std::strcmp("Rect", propName) == 0) {
          #ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] scriptSetupCompleted: Setting Rect prototype" << std::endl;
          #endif
            v8_SetRectPrototype(proto);
        } else if (std::strcmp("RotatedRect", propName) == 0) {
          #ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] scriptSetupCompleted: Setting RotatedRect prototype" << std::endl;
          #endif
            v8_SetRotatedRectPrototype(proto);
        } else if (std::strcmp("Quad", propName) == 0) {
          #ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] scriptSetupCompleted: Setting Quad prototype" << std::endl;
          #endif
            v8_SetQuadPrototype(proto);
        } else if (std::strcmp("MemBlock", propName) == 0) {
          #ifdef WANT_DEBUG_LOG
            std::cerr << "[PDG] scriptSetupCompleted: Setting MemBlock prototype" << std::endl;
          #endif
            v8_SetMemBlockPrototype(proto);
        } else {
          #ifdef WANT_VERBOSE_DEBUG_LOG
            std::cerr << "[PDG] scriptSetupCompleted: Ignored property: " << propName << std::endl;
          #endif
        }
    }

    // Try to delete the _pdgScriptClasses property
    process->Delete(context, _pdgScriptClasses_symbol).Check();
    
    TRACEOUT;
}

#ifdef PDG_STANDALONE_NODE_APP
} // namespace pdg
#endif

// Node.js addon initialization (when not building standalone app)
#ifndef PDG_STANDALONE_NODE_APP

// Simple version of addProcessVersions for addon mode
void addProcessVersionsAddon() {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    v8::Local<v8::String> pdg_symbol = v8::String::NewFromUtf8(isolate, "pdg").ToLocalChecked();
    v8::Local<v8::String> versions_symbol = v8::String::NewFromUtf8(isolate, "versions").ToLocalChecked();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    v8::Local<v8::String> chipmunk_symbol = v8::String::NewFromUtf8(isolate, "chipmunk").ToLocalChecked();
#endif
#ifdef PDG_USE_GLFW
    v8::Local<v8::String> glfw_symbol = v8::String::NewFromUtf8(isolate, "glfw").ToLocalChecked();
#endif
#ifdef PDG_USE_LIBPNG
    v8::Local<v8::String> libpng_symbol = v8::String::NewFromUtf8(isolate, "libpng").ToLocalChecked();
#endif

    // Get process object from global context
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Object> global = context->Global();
    v8::Local<v8::String> process_symbol = v8::String::NewFromUtf8(isolate, "process").ToLocalChecked();
    v8::Local<v8::Value> process_val = global->Get(context, process_symbol).ToLocalChecked();
    if (process_val->IsObject()) {
        v8::Local<v8::Object> process = process_val->ToObject(context).ToLocalChecked();
        v8::Local<v8::Object> versions = process->Get(context, versions_symbol).ToLocalChecked()->ToObject(context).ToLocalChecked();

        (void)versions->Set(context, pdg_symbol, v8::String::NewFromUtf8(isolate, PDG_VERSION).ToLocalChecked());
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        (void)versions->Set(context, chipmunk_symbol, v8::String::NewFromUtf8(isolate, cpVersionString).ToLocalChecked());
#endif
#ifdef PDG_USE_GLFW
        char glfw_vers_str[256];
        std::snprintf(glfw_vers_str, sizeof(glfw_vers_str), "%d.%d.%d", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
        (void)versions->Set(context, glfw_symbol, v8::String::NewFromUtf8(isolate, glfw_vers_str).ToLocalChecked());
#endif
#ifdef PDG_USE_LIBPNG
#ifdef PNG_LIBPNG_VER_STRING
        (void)versions->Set(context, libpng_symbol, v8::String::NewFromUtf8(isolate, PNG_LIBPNG_VER_STRING).ToLocalChecked());
#else
        (void)versions->Set(context, libpng_symbol, v8::String::NewFromUtf8(isolate, "Unknown").ToLocalChecked());
#endif
#endif
    }
}

} // namespace pdg

extern "C" void pdg_install_win32_crash_handler(void);

NODE_MODULE_INIT() {
#ifdef _WIN32
    pdg_install_win32_crash_handler();
#endif
    const char* nodestr = "node";
    pdg_LibSaveArgs(1, &nodestr);
    pdg::addProcessVersionsAddon(); // set up the version flags
    pdg_LibInit();
    pdg::initBindings(exports);
    
    // Also set up process.pdg for addon mode compatibility
    v8::Isolate* isolate = context->GetIsolate();
    v8::Local<v8::Object> global = context->Global();
    v8::Local<v8::String> process_symbol = v8::String::NewFromUtf8(isolate, "process").ToLocalChecked();
    v8::Local<v8::Value> process_val = global->Get(context, process_symbol).ToLocalChecked();
    if (process_val->IsObject()) {
        v8::Local<v8::Object> process = process_val->ToObject(context).ToLocalChecked();
        v8::Local<v8::String> pdg_symbol = v8::String::NewFromUtf8(isolate, "pdg").ToLocalChecked();
        process->Set(context, pdg_symbol, exports).Check();
    }
}

#endif
