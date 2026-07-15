// -----------------------------------------------
// main.js
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

var pdg = require('pdg');

var pdg_dir = process.env['PDG_ROOT'];
if (pdg_dir == undefined) {
    pdg_dir = "."
}
var verbose = (parseInt(process.env['VERBOSE']) == 1);
var superverbose = (parseInt(process.env['VERBOSE']) == 2);
if (superverbose) verbose = true;

var format_webidl = (pdg.argv[2] == "--web-idl-format");
var format_json = (pdg.argv[2] == "--json-format");
var format_pdgidl = (pdg.argv[2] == "--pdg-i-format");
var format_js = (pdg.argv[2] == "--js-format");
var format_doxyc = (pdg.argv[2] == "--doxygen-h-format");
var format_embind = (pdg.argv[2] == "--embind-format");
if (!format_webidl && !format_pdgidl && !format_json && !format_js && !format_doxyc && !format_embind) {
    // no format set, use default
    format_json = true;
}

var write = function(what) { 
    process.stdout.write(what);
};

var log = function(what) {
    process.stderr.write(what + "\n");
}

var ext = (format_webidl) ? ".idl" : 
    (format_pdgidl) ? ".i" :
    (format_js) ? ".js" :
    (format_doxyc) ? ".h" :
    (format_embind) ? ".embind" :
    ".json";


var depth = 0;
function indent() {
    return "".lpad(" ", depth*2);
}

// ElementRef is a factory-only class, so we need to fake a create function for IDL generation
pdg._fakeCreateElementRef = function() {
    drawing = pdg.createDrawing();
    element = drawing.addLine(new pdg.Point(0,0), new pdg.Point(100,100), new pdg.Attributes());
    return element;
}

// garbage collecting some object (pdg singletons) can cause problems.
// keep references here so we don't do that.

var _objects_to_not_garbage_collect = [];

function inspect(obj, objname, skip, objclassinfo) {
    var STRIP_COMMENTS = /((\/\/.*$)|(\/\*[\s\S]*?\*\/))/mg;

    if (typeof(skip)=="undefined") {
        skip = [];
    }

    if (verbose) log( indent() + "Inspecting "+objname+": "+obj.toString());

    // this just takes the argument name
    function _get_script_param_info(arg) {
        return {    "name": arg, 
                    "type": _guess_type_from_param_name(arg), 
                    "optional": false, 
                    "default_value": undefined 
                };
    }

    // this takes a single section of a method signature, something like:
    // "[number uint] style = textStyle_Plain"
    function _get_native_param_info(arg) {
        arg = arg.trim();
        var endblk = arg.indexOf(']');
        var optblk = arg.indexOf("=");
        var tname = "", pname = "";
        var opt = (optblk > 0);
        var default_val = undefined;
        if (endblk > 0) {
            tname = arg.slice(1, endblk).trim();
        } else {
            endblk = arg.indexOf(' ');
            tname = arg.slice(0, endblk).trim();
        }
        pname = arg.slice(endblk+1, opt ? optblk : arg.length).trim();
        if (opt) {
            default_val = arg.slice(optblk+1, arg.length).trim();
            default_val = default_val.replace(';', ',');  // put back any commas we changed
        } else {
            opt = undefined;
        }
        return {    "name": pname, 
                    "type": tname.replace("_ARRAY_", "[]"), 
                    "optional": opt, 
                    "default_value": default_val 
                };
    }

 
    function _get_supers(inst) {
        if (Object.getPrototypeOf(inst.constructor).name != "") {
            // for javascript classes, we need to return the single constructorprototype name
            return [Object.getPrototypeOf(inst.constructor).name];
        }
        var supers = [].concat(inst.constructor.superclass);  // make sure we have an array
        var slist = [];
        for (i in supers) {
            if (typeof(supers[i]) === "function") {
                var sname = supers[i].toString();
                sname = sname.replace("function ", "");
                sname = sname.replace("() { [native code] }", "");
                slist.push(sname);
            }
        }
        return slist;
    }
    
    function _get_function_inherited_from(name) {
        var supers;
        if (Object.getPrototypeOf(obj.constructor).name != "") {
            supers = [Object.getPrototypeOf(obj.constructor).name];
        } else {
            supers = [].concat(obj.constructor.superclass);  // force an array
        }
        for (i in supers) {
            if ((typeof(supers[i]) === "function") && (typeof(supers[i].prototype[name]) == "function")) {
                var sname = supers[i].toString();
                sname = sname.replace("function ", "");
                sname = sname.replace("() { [native code] }", "");
                return sname;
            }
        }
        return undefined;
    }

    function _is_native(func) {
        var fnStr = func.toString().replace(STRIP_COMMENTS, '');
        fnStr = fnStr.split('\n')[0];
        return (fnStr.indexOf("[native code]") >= 0) ? true : undefined;
    }
    
    function _is_read_only(pname) {
        var props = Object.getOwnPropertyDescriptor(obj, pname);
        if (typeof props == "undefined") return undefined;
        return props["writable"] ? undefined : true;
    }

    function _get_const_value(pname) {
        var props = Object.getOwnPropertyDescriptor(obj, pname);
        if (typeof props == "undefined" || props["writable"]) return undefined;
        return props["value"];
    }

    function _get_method_signature(fname) {
        let sig = "";
        try {
            sig = obj[fname](null);
        }
        catch(e) {
            if (e.message.indexOf("cannot be invoked without 'new'") >= 0) {  
                sig = new Function("{ return pdg._get"+fname+"ConstructorSignature() }")();
            } else if (fname == obj.constructor.name && e.message.indexOf("obj[fname] is not a function") >= 0) {  
                sig = new Function("{ return pdg._get"+fname+"ConstructorSignature() }")();
            } else {
                throw e; // rethrow the exception
            }
        }
        return sig;
    }

    function _get_brief(func, fname) {
        // Check if this function has documentation override
        var fullName = objname + "." + fname;
        if (excludedFunctionDocs && excludedFunctionDocs[fullName]) {
            return excludedFunctionDocs[fullName].brief || "";
        }
        
        try {
            var sig = _get_method_signature(fname);
            var fparts = sig.split(' - ');
            return (fparts.length > 1) ? fparts[1] : "";
        }
        catch(e) {
            if (verbose) {
                log("**** (1) " + objname + "."+fname + " threw an exception when called with (null) to get method signature: "+e.message);
            }
            return "";
        }
    }
    
    function _get_return_type(func, fname) {
        // Check if this function has documentation override
        var fullName = objname + "." + fname;
        if (excludedFunctionDocs && excludedFunctionDocs[fullName]) {
            return excludedFunctionDocs[fullName].returns;
        }
        
        try {
            let sig = _get_method_signature(fname);
            var tname = sig.split(' function')[0].replace("[]", "_ARRAY_").replace("[", "").replace("]", "").replace("CR ","").replace("_ARRAY_", "[]").trim();
            if (tname == "undefined") {
                return;
            }
            // these things have been a constant pain in my butt because
            // of the case differences from C to JavaScript. >sigh<
            if (tname == "object cpSpace") {
                return "object CpSpace";
            } else if (tname == "object cpConstraint") {
                return "object CpConstraint";
            } else if (tname == "object cpArbiter") {
                return "object CpArbiter";
            }

            return tname;
        }
        catch(e) {
            if (verbose) {
                log("**** (2) " + objname + "."+fname + " threw an exception when called with (null) to get method signature: "+e.message);
            }
            return "undefined"
        }
    }
    
    function _guess_type_from_param_name(pname) {
        if (pname == "func") {
            return "function";
        } else if (pname == "callback") {
            return "function";
        } else if (pname == "point") {
            return "Point";
        } else if (pname == "color") {
            return "Color";
        } else if (pname == "offset") {
            return "number";
        } else if (pname == "delta") {
            return "number";
        } else if (pname == "r") {
            return "Rect";
        } else if (pname == "r2") {
            return "Rect";
        }
        return "value";
    }

    function _get_function_params(func, fname) {
        
        var params = [];

        // Check if this function has documentation override
        var fullName = objname + "." + fname;
        if (excludedFunctionDocs && excludedFunctionDocs[fullName]) {
            return excludedFunctionDocs[fullName].params;
        }

        if (true) { //_is_native(func)) {
            // for native code, we have a calling convention in pdg
            // where calling the function with a single param of null
            // will return the method signature
            
            if (!_is_private_or_internal(fname)) {
                try {
                    let sig = _get_method_signature(fname);
                    sig = sig.split(' - ')[0];
                    var args = sig.slice(sig.indexOf('(')+1, sig.lastIndexOf(')')).replace("[]","_ARRAY_").trim();
                    if (args.length > 0) {
                    
                        // replace all commas inside ( ) blocks with semicolons 
                        // this handles cases where a default value for an optional param
                        // is something like Point(0,0)
                        var inside = 0;
                        for (i = 0; i < args.length; i++) {
                            var c = args.charAt(i);
                            if (c == ',' && (inside > 0)) {
                                args = args.replaceAt(i, ';');
                            } else if (c == '(') {
                                inside++;
                            } else if (c == ')') {
                                inside--;
                            }
                        }
                        var VARIENTS = /[|{][^|}]*/g;
                        var vlist = args.match(VARIENTS);
                        if (vlist && vlist.length < 2) {
                            vlist = null;
                        } else {
                            args = args.replace(/\{.*\}/, "_VLIST_");
                        }
                        var ARGUMENTS = /(_VLIST_(?=,)|\[\w+\s+\w+\]\s+[^,]+|\w+\s+[^,]+)/g;
                        var plist = args.match(ARGUMENTS);
                        
                        if (vlist) {
                         
                            var all_params = (plist) ? plist.join(",") : "_VLIST_";  // whole thing might be variable

                            // there are argument variants, so we must create multiple parameter sets
                            for (variantIdx in vlist) {
                                vparam = [];
                                // need to reparse the arguments list since a VLIST
                                // might contain multiple arguments
                                var newargs = vlist[variantIdx];
                                var nparams = all_params.replace("_VLIST_", newargs.substring(1, 10000));
                                var nplist = nparams.match(ARGUMENTS);
                                for (idx in nplist) {
                                    var pinfo = _get_native_param_info(nplist[idx]);
                                    vparam.push(pinfo)
                                }
                                
                                params.push(vparam);
                            }

                        } else {
                        
                            // there are no argument list variants, so just go through and add all the names and types   
                            for (idx in plist) {
                                var pinfo = _get_native_param_info(plist[idx]);
                                params.push(pinfo)
                            }     

                        }   
                    }
                }
                catch(e) {
                    if (verbose) {
                        log("**** (3) " + fname + " threw an exception when called with (null) to get method signature: "+e.message);
                    }
                    return null;
                }
            }
            
        } else {

            var ARGUMENT_NAMES = /(\w+)/g;
            var fnStr = func.toString().replace(STRIP_COMMENTS, '');
            fnStr = fnStr.split('\n')[0];
            var plist = fnStr.slice(fnStr.indexOf('(')+1, fnStr.indexOf(')')).match(ARGUMENT_NAMES);
            if (plist) {
                for (idx in plist) {
                    var pinfo = _get_script_param_info(plist[idx]);
                    params.push(pinfo);
                }
            }
        }
        
        return params;

    }

    function _class_info(name) {
        // Check if there's a singleton instance we should use instead of creating a new one
        var singletonInst = _get_singleton_instance(name, obj);
        var inst;
        
        if (singletonInst) {
            // Use the singleton instance for method inspection - this is the primary interface
            inst = singletonInst;
            if (verbose) {
                log(indent() + "Using singleton instance for " + name + " instead of creating new instance");
            }
        } else if (_is_factory_only_class(name)) {
            // Use factory function for factory-only classes
            var factoryFunc = _get_factory_function(name, obj);
            if (factoryFunc) {
                try {
                    inst = factoryFunc();
                    if (verbose) {
                        log(indent() + "Using factory function for " + name + " instead of constructor");
                    }
                } catch (e) {
                    if (verbose) {
                        log(indent() + "Factory function for " + name + " failed: " + e.message);
                    }
                    // If factory function fails, we can't inspect this class
                    return {
                        "name": name,
                        "type": "class",
                        "native": true,
                        "implements": [],
                        "interface": [],
                        "note": "Factory-only class - cannot be instantiated for inspection"
                    };
                }
            } else {
                if (verbose) {
                    log(indent() + "No factory function found for " + name);
                }
                // If no factory function found, we can't inspect this class
                return {
                    "name": name,
                    "type": "class",
                    "native": true,
                    "implements": [],
                    "interface": [],
                    "note": "Factory-only class - no factory function available"
                };
            }
        } else {
            // Fallback to creating a new instance if no singleton exists and not factory-only
            inst = new obj[name](null);
        }
        _objects_to_not_garbage_collect.push(inst);
        
        var classInfo = { 
            "name": name,
            "type": "class",
            "native": _is_native(inst.constructor),
            "implements": _get_supers(inst),
        };
        
        // If this class has a singleton instance, document that as the primary access method
        if (singletonInst) {
            var singletonName = null;
            // Find the singleton name by reverse lookup
            for (var key in obj) {
                if (obj[key] === singletonInst) {
                    singletonName = key;
                    break;
                }
            }
            if (singletonName) {
                classInfo.singleton = singletonName;
                classInfo.note = "Primary access via singleton instance: " + objname + "." + singletonName;
            }
        } else if (_is_factory_only_class(name)) {
            // Document that this is a factory-only class
            var factoryMap = {
                'SpriteLayer': 'createSpriteLayer',
                'TileLayer': 'createTileLayer',
                'Drawing': 'createDrawing',
                'ElementRef': 'Drawing.addLine'
            };
            var factoryName = factoryMap[name];
            if (factoryName) {
                classInfo.factory = factoryName;
                classInfo.note = "Factory-only class - use factory function: " + objname + "." + factoryName + "()";
            }
        }
        classInfo.interface = inspect(inst, name, skip, classInfo);   // recursively inspect object
        
        return classInfo;
    }

    function _constructor_info(obj) {
        const func = obj.constructor;
        const funcParams = _get_function_params(func, func.name);
        if (funcParams == null) {
            return undefined;
        }
        return {
            "name": func.name,
            "type": "constructor",
            "native": _is_native(func),
            "brief": _get_brief(func, func.name),
            "returns": "object "+objname,
            "params": funcParams
        };
    }

    function _function_info(name) { 
        const func = obj[name];
        const funcParams = _get_function_params(func, name);
        if (funcParams == null) {
            return undefined;
        }
        return { 
            "name": name,
            "type": "function",
            "native": _is_native(func),
            "inherited_from": _get_function_inherited_from(name),
            "brief": _get_brief(func, name),
            "returns": _get_return_type(func, name),
            "params": funcParams
        };
    }

    function _member_info(name) {
        var tname = typeof(obj[name]);
        if (tname == 'object') {
            // Check for both actual Arrays and array-like objects (with length property)
            var isArrayLike = (obj[name] instanceof Array) || 
                             (obj[name] && typeof(obj[name].length) === 'number' && obj[name].length >= 0);
            
            if (isArrayLike) {
                var item = obj[name][0];
                var itype = typeof(item);
                if (itype=="string") {
                    tname = "string[]";
                } else if (itype == "object") {
                    if (item && item.toString().substring(0,5) == "Point") {
                        tname = "object Point[]"
                    } else {
                        tname = "object[]";
                    }
                } else if (itype == "undefined" && obj[name].length >= 0) {
                    // Empty array - try to infer type from property name or default to generic array
                    if (name == "connections") {
                        tname = "object NetConnection[]";
                    } else if (name == "points") {
                        tname = "object Point[]";
                    } else {
                        tname = "[]";
                    }
                } else {
                    tname = "[]";
                }
            } else {
                tname = obj[name].toString();
                if (tname.charAt(0) == '[') {
                    tname = tname.slice(1, tname.indexOf(']')).trim();
                } else if (tname.indexOf('(')>0) {
                    tname = "object "+tname.slice(0, tname.indexOf('(')).trim();
                } else {
                    tname = "object";
                }
            }
        }
        var ro = _is_read_only(name);
        var value = _get_const_value(name);
        return {
            "name": name,
            "type": tname,
            "readonly": ro,
            "value": value
        };
    }

  
    function _is_constructor(name) {
        if (name == "constructor") {  // except these get filtered out by _is_private()
            return true;
        } else {
            return (name == objname);
        }
    }

    function _is_private_or_internal(name) {
        return ((name.charAt(0) == '_') ||   // private if it starts with an underscore
           // these are methods on the Object prototype, so exclude them
            (name == "toString") || 
            (name == "constructor") ||
            (name == "hasOwnProperty") ||
            (name == "isPrototypeOf") ||
            (name == "propertyIsEnumerable") ||
            (name == "toLocaleString") ||
            (name == "valueOf"));
    }

    function _is_class(name) {
        if (name.charAt(0).match(/[A-Z]/)) {
            return obj[name] && obj[name].constructor;
        } else {
            return false;
        }
    }

    function _all_properties_of(obj) {
        let props = {};
        for (var key in obj) {
            if (props[key]) continue;
            var item = obj[key];
            props[key] = item;
        }
        const propDescs = Object.getOwnPropertyDescriptors(obj.constructor.prototype);
        for (var key in propDescs) {
            var item = propDescs[key];
            props[key] = item.value;
        }
        return props;
    }

    function _all_members_of(obj) {
        let props = _all_properties_of(obj);
        let members = {}
        for (var key in props) {
            if (typeof(props[key]) !== "function" && !_is_class(key)) {
               members[key] = props[key];
            }
        }
        return members;
    }

    function _all_methods_of(obj) {
        let props = _all_properties_of(obj);
        let methods = {}
        for (var key in props) {
            if (typeof(props[key]) === "function" && !_is_class(key)) {
                methods[key] = props[key];
            }
        }
        return methods;
    }

    function _all_classes_of(obj) {
        let props = _all_properties_of(obj);
        let classes = {}
        for (var key in props) {
            if (typeof(props[key]) === "function" && _is_class(key)) {
                classes[key] = props[key];
            }
        }
        return classes;
    }

    var _api = [];
    
    depth++;
    for (var name in _all_members_of(obj)) {
        var fullname = objname+"."+name;
        if (skip.indexOf(fullname) < 0 && !_is_private_or_internal(name)) {
            if (superverbose) {
                log(indent() + "- "+fullname);
            }
            try {
                _api.push( _member_info(name) );
            } catch (e) {
                log(indent() + "Error: "+fullname+" threw an exception: "+e.message);
            }
        } else {
            if (verbose) { 
                log(indent() + "- "+fullname+" -- skipped");
            }
        }
    }
    if (objname != "pdg" &&
        !_is_factory_only_class(objname) && 
        !_get_singleton_instance(objname, pdg)) {
        const constructorInfo = _constructor_info(obj); // this can return undefined
        if (constructorInfo) {
            _api.push( constructorInfo );
        }
    }
    for (var name in _all_methods_of(obj)) {
        var fullname = objname+"."+name;
        //superverbose = fullname == "pdg.Point" || fullname == "pdg.xOffset" || fullname.startsWith("Point.") || fullname.startsWith("xOffset.");
        //superverbose = obj === pdg;
        if (skip.indexOf(fullname) < 0 && !_is_private_or_internal(name)) {
            if (superverbose) {
                log(indent() + "- "+fullname);
            }
            if (superverbose) {
                log(indent() + "("+fullname+" appears to be a function)");
            }
            _api.push( _function_info(name) );
        } else {
            if (verbose) { 
                log(indent() + "- "+fullname+" -- skipped");
            }
        }
    }
    for (var name in _all_classes_of(obj)) {
        var fullname = objname+"."+name;
        //superverbose = fullname == "pdg.Point" || fullname == "pdg.xOffset" || fullname.startsWith("Point.") || fullname.startsWith("xOffset.");
        //superverbose = obj === pdg;
        if (skip.indexOf(fullname) < 0 && !_is_private_or_internal(name)) {
            if (superverbose) {
                log(indent() + "- "+fullname);
            }
            if (superverbose) {
                log(indent() + "("+fullname+" appears to be a class)");
            }
            _api.push( _class_info(name) );
        } else {
            if (verbose) { 
                log(indent() + "- "+fullname+" -- skipped");
            }
        }
    }
    depth--;
    return _api;
}

// Map constructor function names to their corresponding singleton instances in PDG
function _get_singleton_instance(className, parentObj) {
    var singletonMap = {
        'TimerManager': 'tm',
        'FileManager': 'fs', 
        'EventManager': 'evt',
        'ResourceManager': 'res',
        'ConfigManager': 'cfg',
        'LogManager': 'lm',
        'GraphicsManager': 'gfx',
        'SoundManager': 'snd',
        'NetManager': 'net'
    };
    
    var singletonName = singletonMap[className];
    if (singletonName && parentObj[singletonName]) {
        return parentObj[singletonName];
    }
    return null;
}

// Map factory-only classes to their corresponding factory functions
function _get_factory_function(className, parentObj) {
    var factoryMap = {
        'SpriteLayer': 'createSpriteLayer',
        'TileLayer': 'createTileLayer',
        'Drawing': 'createDrawing',
        'ElementRef': '_fakeCreateElementRef',
        // Add other factory-only classes as needed
    };
    
    var factoryName = factoryMap[className];
    if (factoryName && parentObj[factoryName]) {
        return parentObj[factoryName];
    }
    return null;
}

// Check if a class is factory-only (cannot be instantiated with 'new')
function _is_factory_only_class(className) {
    var factoryOnlyClasses = [
        'SpriteLayer',
        'TileLayer',
        'Drawing',
        'ElementRef',
        // Add other factory-only classes as needed
    ];
    
    return factoryOnlyClasses.indexOf(className) >= 0;
}


String.prototype.lpad = function(padString, length) {
	var str = this;
    while (str.length < length)
        str = padString + str;
    return str;
}
String.prototype.rpad = function(padString, length) {
	var str = this;
    while (str.length < length)
        str = str + padString;
    return str;
}
String.prototype.replaceAt = function(index, char) {
    var a = this.split("");
    a[index] = char;
    return a.join("");
}


function embindAllowPtr(obj, v) {
    var needAllow = false;
    if (obj["returns"] && obj["returns"].indexOf("object ") == 0) {
        needAllow = true;
    } else if (obj["params"] && obj["params"].length > 0) {
        var variants = obj["params"];
        if (!(variants[0] instanceof Array)) {
            variants = [ variants ];
        }
        // check this variant to see if the params include an object
        var params = variants[v];
        for (p in params) {
            if (params[p]["type"].indexOf("object ") == 0) {
                needAllow = true;
                break;
            }
        }
    }
    return (needAllow) ? ", emscripten::allow_raw_pointers()" : "";
}


function webidlType(typename, mode, context) {
    var prefix = "";
    if (typename == undefined) {
        typename = "void"
    } else if (typename == "undefined") {
        typename = "void";
    } else if (typename == "number") {
        typename = "float";
    } else if (typename == "string") {
        typename = "DOMString";
    } else if (typename == "string Binary") {
        typename = "DOMString";
    } else if (typename == "string[]") {
        typename = "DOMString[]";
    } else if (typename == "number int") {
        typename = "long";
    } else if (typename == "number uint") {
        typename = "unsigned long";
    } else if (typename == "value") {
        typename = "any";
    } else if (typename == "constructor") {
        typename = "class";
    } else if (typename == "object") {
        typename = "object";

//     } else if (typename == "object Color") {
//         typename = "object";
    } else if (typename == "object Point") {
        typename = "Point";
        if (mode != "return") {
            prefix = "[Ref] ";
        }
//     } else if (typename == "object Offset") {
//         typename = = "object";
//     } else if (typename == "object Vector") {
//         typename = "object";
     } else if (typename == "object Rect") {
         typename = "Rect";
         if (mode != "return") {
            prefix = "[Ref] ";
         }
//     } else if (typename == "object RotatedRect") {
//         typename = "object";
//     } else if (typename == "object Quad") {
//         typename = "object";

    } else if (typename.substring(0, 7) == "object ") {
        typename = typename.substring(7, 1000).trim();
    }
    if (mode=="return") {
        mode = "";
    } else if (mode=="optional") {
        mode = "optional "
    }
    return prefix+mode+typename;
}

function doxyType(typename, name) {
    if (typename == undefined) {
        typename = false;
    } else if (typename == "undefined") {
        typename = "void";
    } else if (typename == "object") {
        typename = "object";
    } else if (typename == "number int") {
        typename = "int";
    } else if (typename == "number uint") {
        typename = "uint";
    } else if (typename == "string Binary") {
        typename = "BinaryString";
    } else if (typename == "[]" && name == "argv") {
        typename = "string[]";
    } else if (typename.substring(0, 7) == "object ") {
        typename = typename.substring(7, 1000).trim();
    }
    return typename;
}

// gather all the info, except for these particular problem things
var exclude = [];
var today = new Date();

// Load documentation overrides for excluded functions
var excludedFunctionDocs = {};
try {
    excludedFunctionDocs = require('../docs/javascript/excluded-function-docs.js');
} catch (e) {
    // If the file doesn't exist, continue without it
    log("Warning: Could not load excluded-function-docs.js: " + e.message);
}

var api = inspect(pdg, "pdg", exclude, null);
api = {
    "name": "pdg", 
    "type": "module",
    "lang": "javascript",
    "vers": require("fs").readFileSync(pdg_dir+"/VERSION", "utf8").replace("\n", ""),
    "when": today.getFullYear().toString().rpad("0", 4)+"-"+(today.getMonth()+1).toString().lpad("0", 2)+"-"+today.getDate().toString().lpad("0", 2),
    "interface": api
};


if (format_json) {

    write(JSON.stringify(api, null, "\t"));

} else if (format_webidl) {

    var fnamepad = 10;

    write("// this file was automatically generated by \"pdg tools/make-idl.js --web-idl-format\"\n\n");
    write("// this isn't likely to be very useful for pdg since WebIDL doesn't support multiple inheritance\n\n");

    var root = api["interface"];
    for (i in root) {
        if (root[i]["type"] == "class") {
            write( "[Prefix=\""+api["name"]+"::\"");
            if (!root[i]["native"] || (root[i]["name"].charAt(0) == "I")) {
                // WebIDL won't generate bindings for these
                write( ", NoInterfaceObject, NoDelete");
            }
            write( "]\n");
            write( "interface "+root[i]["name"]+" {\n");
            var obj = root[i]["interface"];
            var haveConstructor = false;
            // first go through and find the constructor(s), if any
            for (m in obj) {
                if (obj[m]["type"] == "constructor") {
                    haveConstructor = true;
                }
            }
            if (!haveConstructor && (root[i]["name"].charAt(0) != "I")) {
                // we didn't have a constructor, so write one now
                // we don't create constructors for pure virtual classes (start with I)
                write( "\t"+"void".rpad(" ",fnamepad)+" "+root[i]["name"]+"();\n");
            }
            for (m in obj) {
                if (obj[m]["type"] == "function" && obj[m]["native"]) {
                    var ret = webidlType(obj[m]["returns"], "return", obj[m]);
                    var fstr = "\t"+ret.rpad(" ",fnamepad)+" "+obj[m]["name"]+"(";
                    
                    var variants = obj[m]["params"];
                    if (variants.length == 0) {
                        // no params
                        write( fstr + ");\n");
                    } else if (!(variants[0] instanceof Array)) {
                        // no variants, create array with one variant
                        variants = [ variants ];
                    }
                    var varParCounts = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
                    for (v in variants) {
                        // write a full function for each variant
                        var params = variants[v];
                        var plist = [];
                        var paramCount = params.length;
                        for (p in params) {
                            var par = params[p];
                            if (par["optional"] && (p < paramCount)) {
                                paramCount = p; // probably have to count all possible variants of optional params too
                            }
                            plist.push(webidlType(par["type"], par["optional"]?"optional":"", obj[m])+" "+par["name"]);
                        }
                        varParCounts[paramCount]++;
                        var pstr = plist.join(", ");
                        if (varParCounts[paramCount] == 1) { // we can only have a single variant with the same number of params
                            write( fstr + pstr + ");\n");
                        } else {
                            write( "/* "+ fstr + pstr + "); */\n");
                        }
                        break; // only do one
                    }
                }
            }
            write( "};\n\n");
        }
    }

} else if (format_doxyc) {

    write("// this file was automatically generated by \"pdg tools/make-idl.js --doxygen-h-format\"\n\n\n");

    write("namespace "+api["name"]+"\n{\n\n");
    var root = api["interface"];
    // first get all our constants and variables
    for (i in root) {
        if ((root[i]["type"] != "class") && (root[i]["type"] != "function")) {
            if (root[i]["value"] != undefined) {
                write("    const "+root[i]["name"]+" = "+root[i]["value"]+";\n");
            } else {
                write("    "+doxyType(root[i]["type"])+" "+root[i]["name"]+";\n");
            }
        }
    }
    // get all the top level functions
    // simpler because there are no variant param lists in top level functions
    for (i in root) {
        if (root[i]["type"] == "function") {
            var ret = doxyType(root[i]["returns"]);
            if (ret) ret += " "; else ret = "";
            var fstr = "    "+ret+root[i]["name"]+" (";                    
            var plist = [];
            var params = root[i]["params"];
            for (p in params) {
                var par = params[p];
                plist.push(doxyType(par["type"])+" "+par["name"] + (par["optional"]? " = "+par["default_value"]:""));
            }
            var pstr = plist.join(", ");
            write( fstr + pstr + ");\n");
        }
    }
    // now dump all the classes
    write("\n");
    for (i in root) {
        if (root[i]["type"] == "class") {
            write("    class "+root[i]["name"]);
            if (root[i]["implements"].length > 0) {
                var ilist = [];
                for (j in root[i]["implements"]) {
                    ilist.push("public "+root[i]["implements"][j]);
                }
                var istr = ilist.join(", ");
                write(" : "+istr);
            }
            write( "\n    {\n        public:\n");
            var obj = root[i]["interface"];
            var haveConstructor = false;
            // go through three times: 
            // 1. member vars and consts  2. constructors  3. member functions
            var find="_VARSANDCONSTS_";
            while (find) {
                for (m in obj) {
                    const otype = obj[m]["type"];
                    if (otype == find) {
                        if (obj[m]["inherited_from"]) continue;  // skip inherited functions
                        var ret = (otype == "constructor") ? false : doxyType(obj[m]["returns"]);
                        if (ret) ret += " "; else ret = "";
                        var fstr = "            "+ret+obj[m]["name"]+" (";
                        var variants = obj[m]["params"];
                        if (variants.length == 0) {
                            // no params
                            write( fstr + ");\n");
                        } else if (!(variants[0] instanceof Array)) {
                            // no variants, create array with one variant
                            variants = [ variants ];
                        }
                        for (v in variants) {
                            // write a full function for each variant
                            var params = variants[v];
                            var plist = [];
                            for (p in params) {
                                var par = params[p];
                                plist.push(doxyType(par["type"])+" "+par["name"] + (par["optional"]? " = "+par["default_value"]:""));
                            }
                            var pstr = plist.join(", ");
                            write( fstr + pstr + ");\n");
                        }
                    } else if ((find == "_VARSANDCONSTS_") && (otype != "undefined") && (otype != "function") && (otype != "constructor")) {
                        if (obj[m]["value"] != undefined) {
                            write("            const "+obj[m]["name"]+" = "+obj[m]["value"]+";\n");
                        } else {
                            write("            "+doxyType(otype)+" "+obj[m]["name"]+";\n");
                        }
                
                    }
                }
                if (find=="_VARSANDCONSTS_") {
                    find = "constructor";
                } else if (find=="constructor") {
                    find = "function";
    //             if (!haveConstructor && (root[i]["name"].charAt(0) != "I")) {
    //                 // we didn't have a constructor, so write one now
    //                 // we don't create constructors for pure virtual classes (start with I)
    //                 write( "\t"+"void".rpad(" ",fnamepad)+" "+root[i]["name"]+"();\n");
    //             }
                } else {
                    find=false;
                }
            }
            write( "    };\n\n");
        }
    }
    write("}\n"); // close namespace

} else if (format_js) {

    write("// this file was automatically generated by \"pdg tools/make-idl.js --js-format\"\n\n\n");

    write("var "+api["name"]+" = {\n\n");
    var root = api["interface"];
    // first get all our constants and variables
    for (i in root) {
        if ((root[i]["type"] != "class") && (root[i]["type"] != "function")) {
            if (root[i]["value"] != undefined) {
                write("    "+root[i]["name"]+" : "+root[i]["value"]+",\n");
            } else {
                write("    "+root[i]["name"]+" : null,   // "+doxyType(root[i]["type"])+"\n");
            }
        }
    }
    // get all the top level functions
    // simpler because there are no variant param lists in top level functions
    for (i in root) {
        if (root[i]["type"] == "function") {
            if (root[i]["brief"].length) {
                write( "    // "+root[i]["name"]+": "+root[i]["brief"]+"\n");
            }
            var fstr = "    "+root[i]["name"]+" : (";                    
            var plist = [];
            var params = root[i]["params"];
            for (p in params) {
                var par = params[p];
                plist.push(par["name"]);
            }
            var pstr = plist.join(", ");
            write(fstr + pstr + ") => {},");
            write("\n");
        }
    }
    // now dump all the classes
    write("\n");
    for (i in root) {
        if (root[i]["type"] == "class") {
            if (root[i]["brief"] && root[i]["brief"].length) {
                write( "    // "+root[i]["name"]+": "+root[i]["brief"]+"\n");
            }
            if (root[i]["note"] && root[i]["note"].length) {
                write( "    // NOTE: "+root[i]["note"]+"\n");
            }
            write("    "+root[i]["name"]+" : () => { return {\n");
            if (root[i]["implements"].length > 0) {
                var ilist = [];
                for (j in root[i]["implements"]) {
                    ilist.push(root[i]["implements"][j]);
                }
                var istr = ilist.join(", ");
                write("   //  TODO: derive from "+istr+"\n");
            }
            var obj = root[i]["interface"];
            var haveConstructor = false;
            // go through three times: 
            // 1. member vars and consts  2. constructors  3. member functions
            var find="_VARSANDCONSTS_";
            while (find) {
                for (m in obj) {
                    var otype = obj[m]["type"];
                    if (otype == find) {
                        if (obj[m]["inherited_from"]) continue;  // skip inherited functions
                        if (obj[m]["brief"] && obj[m]["brief"].length) {
                            brief = obj[m]["brief"].replace(/\\param/g, "\n\\param");
                            brief = brief.replace(/\\return/g, "\n\\return");
                            brief = brief.replace(/; /g, "\n");
                            briefLines = brief.replace(/\n/g, "\n        // ");
                            write( "        // "+obj[m]["name"]+": "+briefLines+"\n");
                        }
                        var fstr = "        "+obj[m]["name"]+" : (";
                        var variants = obj[m]["params"];
                        if (variants.length == 0) {
                            variants = [ [ ] ];
                        } else if (!(variants[0] instanceof Array)) {
                            // no variants, create array with one variant
                            variants = [ variants ];
                        }
                        for (v in variants) {
                            // write a full function for each variant
                            var params = variants[v];
                            var plist = [];
                            for (p in params) {
                                var par = params[p];
                                plist.push(par["name"]);
                            }
                            var pstr = plist.join(", ");
                            if (obj[m]["returns"]) {
                                returnsStr = obj[m]["returns"].replace(/object /g, "")
                                .replace(/ uint/g, " /* uint */")
                                .replace(/ int/g, " /* int */")
                                .replace(/ Binary/g, " /* Binary */")
                                .replace(/string\[\]/g, "[\"\"] /* array of strings */");
                                write( fstr + pstr + ") => { return "+returnsStr+"; }, ");
                            } else {
                                write( fstr + pstr + ") => {},");
                            }
                            write("\n");
                        }
                    } else if ((find == "_VARSANDCONSTS_") && (otype != "undefined") && (otype != "function") && (otype != "constructor")) {
                        if (obj[m]["value"] != undefined) {
                            write("        "+obj[m]["name"]+" : "+obj[m]["value"]+",\n");
                        } else {
                            write("        "+obj[m]["name"]+" : null,\n");
                        }
                
                    }
                }
                if (find=="_VARSANDCONSTS_") {
                    find = "constructor";
                } else if (find=="constructor") {
                    find = "function";
    //             if (!haveConstructor && (root[i]["name"].charAt(0) != "I")) {
    //                 // we didn't have a constructor, so write one now
    //                 // we don't create constructors for pure virtual classes (start with I)
    //                 write( "\t"+"void".rpad(" ",fnamepad)+" "+root[i]["name"]+"();\n");
    //             }
                } else {
                    find=false;
                }
            }
            write( "    }; },\n\n");
        }
    }
    write("};\n"); // close main var

} else if (format_embind) {

    var root = api["interface"];
    

    var excludeNames = [
            "FileManager.findFirst",
            "FileManager.findNext",
            "FileManager.findClose",
            
 			"ConfigManager",  // completely broken
 			
			"ResourceManager.getLanguage",
			"ResourceManager.getString",
			"ResourceManager.getResource",
			"ResourceManager.getResourceSize",
			"ResourceManager.openResourceFile",
			
			// many of these are failing because they are inline
			"Serializer.serialize_8",
			"Serializer.serialize_8u",
			"Serializer.serialize_mem",
			"Serializer.sizeof_mem",
			"Serializer.sizeof_8",
			"Serializer.sizeof_8u",
			"Serializer.serialize_d",
			"Serializer.serialize_f",
			"Serializer.serialize_4",
			"Serializer.serialize_2",
			"Serializer.serialize_1",
			"Serializer.serialize_point",
			"Serializer.serialize_vector",
			"Serializer.serialize_offset",
			"Serializer.serialize_rect",
			"Serializer.serialize_rotr",
			"Serializer.serialize_quad",
			"Serializer.serialize_str",
			"Serializer.serialize_ref",
			"Serializer.sizeof_d",
			"Serializer.sizeof_f",
			"Serializer.sizeof_4",
			"Serializer.sizeof_4u",
			"Serializer.sizeof_3u",
			"Serializer.sizeof_2",
			"Serializer.sizeof_2u",
			"Serializer.sizeof_1",
			"Serializer.sizeof_1u",
			"Serializer.sizeof_point",
			"Serializer.sizeof_vector",
			"Serializer.sizeof_offset",
			"Serializer.sizeof_rect",
			"Serializer.sizeof_rotr",
			"Serializer.sizeof_quad",
			"Serializer.sizeof_str",
			"Serializer.sizeof_ref",
			"Serializer.sizeof_",
			
			"Deserializer.setDataPtr",
			"Deserializer.deserialize_8",
			"Deserializer.deserialize_d",
			"Deserializer.deserialize_4",
			"Deserializer.deserialize_2",
			"Deserializer.deserialize_1",
			"Deserializer.deserialize_f",
			"Deserializer.deserialize_point",
			"Deserializer.deserialize_vector",
			"Deserializer.deserialize_offset",
			"Deserializer.deserialize_rect",
			"Deserializer.deserialize_rotr",
			"Deserializer.deserialize_quad",
			"Deserializer.deserialize_str",
			"Deserializer.deserialize_ref",

//			"ISerializable",
//			"IEventHandler",
// 			"EventEmitter",

            // these are all failing because they call static OS::methods
			"EventManager.isKeyDown",
			"EventManager.isRawKeyDown",
			"EventManager.isButtonDown",
			"EventManager.getDeviceOrientation",

			"TimerManager.getMilliseconds",
			"TimerManager.startTimer",

//			"IAnimationHelper",
			"Animated.setVelocity",
			"Animated.move",
			"Animated.moveTo",
			"Animated.accelerate",
			"Animated.accelerateTo",
			"Animated.",
			"Animated.",
			"Animated.",
			"Animated.",
			"Animated.",
			"Animated.",
			"Animated.",
			"Animated.",
			"Animated",

			"LogManager",
			"CpArbiter",
			"CpConstraint",
			"CpSpace",
  			"ISpriteDrawHelper",
			"ISpriteCollideHelper",
			"Sprite",
			"SpriteLayer",
			"TileLayer",
			"Image",
			"ImageStrip",
  			"Font",
  			"Port",
  			"GraphicsManager",
  			"Sound",
  			"SoundManager"
    ];
    
    var guiOnlyNames = [
            "getSoundManager", 
            "getGraphicsManager",
            "SoundManager", 
            "GraphicsManager",
            "Sound",
            "Port",
            "Font",
            "ISpriteDrawHelper",
        ];

    write("// this file was automatically generated by \"pdg tools/make-idl.js --embind-format\"\n\n\n");

    write("#include <emscripten/bind.h>\n\n");
    
    write("EMSCRIPTEN_BINDINGS("+api["name"]+") {\n\n");

    var ns = api["name"]+"::"; // we are going to use the namespace a lot

    // get all the top level constants
    for (i in root) {
        if (root[i]["readonly"]) {
            var name = root[i]["name"];

            var guiOnly = (guiOnlyNames.indexOf(fname) >= 0);

            if (guiOnly) {
                write("\n#ifndef PDG_NO_GUI\n  ");
            }
            var pdgName = name;
            if (name.match(/linear\w+|ease(In|Out)\w+|customEasing[0-9]/)) {
                pdgName = "EasingFuncIds::"+name;
            }
// not writing constants, they don't seem to show up in the interface properly
//            write("emscripten::constant(\""+name+"\", "+ns+pdgName+");\n");
            if (guiOnly) {
                write("#endif\n\n");
            }
        }
    }
    write("\n\n");
    // get all the top level functions
    // simpler because there are no variant param lists in top level functions
    for (i in root) {
        if (root[i]["type"] == "function" && root[i]["native"]) {
            var fname = root[i]["name"];

            var guiOnly = (guiOnlyNames.indexOf(fname) >= 0);
            // these functions don't work for yet various reasons, skip them
            if (fname == "registerEasingFunction") continue;
            if (fname == "registerSerializableClass") continue;

            if (guiOnly) {
                write("\n#ifndef PDG_NO_GUI\n  ");
            }
            write("emscripten::function(\""+fname+"\", &"+ns+fname +
                ", emscripten::allow_raw_pointers());\n");
            if (guiOnly) {
                write("#endif\n\n");
            }
        }
    }
    // now dump all the classes
    write("\n");
    for (i in root) {
        if (root[i]["type"] == "class" && root[i]["native"]) {
            var oname = root[i]["name"];
            
            var guiOnly = (guiOnlyNames.indexOf(oname) >= 0);

            if (guiOnly) {
                write("\n#ifndef PDG_NO_GUI\n  ");
            }
            write("emscripten::class_<"+ns+oname+">(\""+oname+"\")\n    "+oname+"_Extra\n");
            var obj = root[i]["interface"];
            var haveConstructor = false;
            // go through three times: 
            // 1. member vars and consts  2. constructors  3. member functions
            var find="_VARSANDCONSTS_";
            while (find && (excludeNames.indexOf(oname) < 0)) {
                for (m in obj) {
                    var otype = obj[m]["type"];
                    if (otype == find) {
                        if (obj[m]["native"] != true) continue;  // skip JavaScript add-ins from pdg.js
                        if (obj[m]["inherited_from"]) continue;  // skip inherited functions
                        var fname = oname+"."+obj[m]["name"];
                        if (excludeNames.indexOf(fname) >= 0) continue;   // skip any excluded functions
                        var fstr = "    ."+otype;
                        if (otype == "constructor") {
                            fstr += "<";
                        } else {
                            fstr += "(\""+obj[m]["name"];
                        }
                        var variants = obj[m]["params"];
                        if (variants.length == 0) {
                            // no params
                            write(fstr+"\", &"+ns+oname+"::"+obj[m]["name"]+embindAllowPtr(obj[m], 0)+")\n");
                        } else if (!(variants[0] instanceof Array)) {
                            // no variants, create array with one variant
                            write(fstr+"\", &"+ns+oname+"::"+obj[m]["name"]+embindAllowPtr(obj[m], 0)+")\n");
                        } else {
                            for (v in variants) {
                                // variants, write one with a different number for each variant
                                write(fstr+v+"\", &"+ns+oname+"::"+obj[m]["name"]+v+embindAllowPtr(obj[m], v)+")\n");
                            }
                        }
                    } else if ((find == "_VARSANDCONSTS_") && (otype != "undefined") && (otype != "function") && (otype != "constructor")) {
//                         if (obj[m]["value"] != undefined) {
//                             write("            const "+obj[m]["name"]+" = "+obj[m]["value"]+";\n");
//                         } else {
//                             write("            "+doxyType(otype)+" "+obj[m]["name"]+";\n");
//                         }
//                 
                    }
                }
                if (find=="_VARSANDCONSTS_") {
                    find = "constructor";
                } else if (find=="constructor") {
                    find = "function";
    //             if (!haveConstructor && (root[i]["name"].charAt(0) != "I")) {
    //                 // we didn't have a constructor, so write one now
    //                 // we don't create constructors for pure virtual classes (start with I)
    //                 write( "\t"+"void".rpad(" ",fnamepad)+" "+root[i]["name"]+"();\n");
    //             }
                } else {
                    find=false;
                }
            }
            write("    ;\n");
            if (guiOnly) {
                write("#endif\n");
            }
            write("\n");
        }
    }

    write("\n}\n"); // close EMSCRIPTEN_BINDINGS

}
