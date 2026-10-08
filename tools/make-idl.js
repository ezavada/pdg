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
var format_mvc = pdg.argv.indexOf("--mvc") >= 0;
// Comparison mode for textual references. JSON already includes inherited
// members; Embind keeps registering them through native base classes.
var include_inherited = pdg.argv.indexOf("--include-inherited") >= 0;
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

    } else if (typename == "[]" && name == "argv") {
        typename = "string[]";
    } else if (typename.substring(0, 7) == "object ") {
        typename = typename.substring(7, 1000).trim();
    }
    return typename;
}

function memberReturnType(member, owner) {
    return member.returns === 'this' ? 'object '+owner : member.returns;
}

function doxyReturnType(member, owner) {
    var type = apiContracts.parameterDocumentationType({type: memberReturnType(member, owner), contract: member.returns_contract}, api.schemas || {})
        || doxyType(memberReturnType(member, owner));
    // Null/sentinel alternatives belong in the return comment, not the type token.
    return typeof type === 'string' ? type.split(' or ')[0] : type;
}

// Return contracts can differ between overloads, e.g. single-hit and buffered casts.
function overloadMember(member, params) {
    var byParameter = member.returns_contract && member.returns_contract.by_parameter || {};
    var matches = params.map(function(param) { return byParameter[param.name]; }).filter(Boolean);
    if (matches.length > 1) throw new Error('Ambiguous overload return for ' + member.name);
    return Object.assign({}, member, {params: params}, matches.length ? {
        returns: matches[0].items && matches[0].items.schema ? 'object ' + matches[0].items.schema + '[]' : matches[0].type || member.returns,
        returns_contract: matches[0]
    } : {});
}

function headerResultComment(member) {
    if (member.returns === 'this' || (member.returns_contract && member.returns_contract.type === 'this')) return '';
    return apiContracts.memberResultComment(member);
}

// Consume the binding-owned structured inventory. No discovery executes API code.
var today = new Date();
var api = pdg.getInterfaceMetadata();
api.when = today.getFullYear().toString().rpad("0", 4)+"-"+(today.getMonth()+1).toString().lpad("0", 2)+"-"+today.getDate().toString().lpad("0", 2);
var apiContracts = require('./api-contracts');
api = apiContracts.alphabeticalOrder(api);
if (format_mvc) {
    if (typeof pdg.AnimatedAttributes !== 'function') throw new Error('MVC inventory requires AnimatedAttributes');
    var mvcApi = apiContracts.inventoryModule(require('../src/js/mvc-app'), 'mvc-app');
    mvcApi.lang = api.lang;
    mvcApi.vers = api.vers;
    mvcApi.when = api.when;
    mvcApi.contract_version = api.contract_version;
    mvcApi = apiContracts.alphabeticalOrder(mvcApi);
    if (format_json) {
        write(JSON.stringify(mvcApi, null, "\t"));
    } else if (format_doxyc) {
        write('// this file was automatically generated by "pdg tools/make-idl.js --doxygen-h-format --mvc"\n\n');
        write(apiContracts.moduleDocumentation(mvcApi));
    } else {
        throw new Error('MVC inventory supports --json-format and --doxygen-h-format');
    }
} else if (format_json) {

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
                    var ret = webidlType(memberReturnType(obj[m], root[i].name), "return", obj[m]);
                    var fstr = "\t"+ret.rpad(" ",fnamepad)+" "+obj[m]["name"]+"(";
                    
                    var variants = obj[m]["params"];
                    if (variants.length == 0) {
                        // no params
                        write( fstr + ");\n");
                    } else if (!Array.isArray(variants[0])) {
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
            var ret = doxyReturnType(root[i], api.name);
            if (ret) ret += " "; else ret = "";
            var fstr = "    "+ret+root[i]["name"]+" (";                    
            var plist = [];
            var params = root[i]["params"];
            for (p in params) {
                var par = params[p];
                plist.push((apiContracts.parameterDocumentationType(par, api.schemas || {}) || doxyType(par["type"]))+" "+par["name"] + (par["optional"]? " = "+par["default_value"]:""));
            }
            var pstr = plist.join(", ");
            write(apiContracts.memberDocumentation(root[i]));
            write( fstr + pstr + ");" + headerResultComment(root[i]) + "\n");
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
            // Emit constants, properties, constructors, and methods in section order.
            var previousSection;
            for (m in obj) {
                var section = apiContracts.memberSection(obj[m], 'class');
                if (previousSection !== undefined && section !== previousSection) write("\n");
                previousSection = section;
                const otype = obj[m]["type"];
                if (otype == "function" || otype == "constructor") {
                    if (obj[m]["inherited_from"] && !include_inherited) continue;
                    var ret = (otype == "constructor") ? false : doxyReturnType(obj[m], root[i].name);
                    if (ret) ret += " "; else ret = "";
                    var fstr = "            "+(obj[m]["static"] ? "static " : "")+ret+obj[m]["name"]+" (";
                    var variants = obj[m]["params"];
                    if (variants.length == 0) {
                        // no params
                        write(apiContracts.memberDocumentation(obj[m]));
                        write( fstr + ");" + headerResultComment(obj[m]) + "\n");
                    } else if (!Array.isArray(variants[0])) {
                        // no variants, create array with one variant
                        variants = [ variants ];
                    }
                    for (v in variants) {
                        // write a full function for each variant
                        var params = variants[v];
                        var variant = overloadMember(obj[m], params);
                        var variantRet = (otype == "constructor") ? false : doxyReturnType(variant, root[i].name);
                        var variantPrefix = "            " + (obj[m]["static"] ? "static " : "") +
                            (variantRet ? variantRet + " " : "") + obj[m]["name"] + " (";
                        var plist = [];
                        for (p in params) {
                            var par = params[p];
                            plist.push((apiContracts.parameterDocumentationType(par, api.schemas || {}) || doxyType(par["type"]))+" "+par["name"] + (par["optional"]? " = "+par["default_value"]:""));
                        }
                        var pstr = plist.join(", ");
                        write(apiContracts.memberDocumentation(variant));
                        write( variantPrefix + pstr + ");" + headerResultComment(variant) + "\n");
                    }
                } else if (otype != "undefined") {
                    if (obj[m]["value"] != undefined) {
                        write("            const "+obj[m]["name"]+" = "+obj[m]["value"]+";\n");
                    } else {
                        write(apiContracts.memberDocumentation(obj[m]));
                        if (obj[m]["readonly"] && !obj[m]["static"]) write("            /** Read-only property. */\n");
                        var qualifiers = obj[m]["static"] ? "static " + (obj[m]["readonly"] ? "const " : "") : "";
                        write("            "+qualifiers+doxyType(otype)+" "+obj[m]["name"]+";\n");
                    }

                }
            }
            write( "    };\n\n");
        }
    }
    write(apiContracts.schemaDocumentation(api.schemas));
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
            // Emit constants, properties, constructors, and methods in section order.
            var previousSection;
            for (m in obj) {
                var section = apiContracts.memberSection(obj[m], 'class');
                if (previousSection !== undefined && section !== previousSection) write("\n");
                previousSection = section;
                var otype = obj[m]["type"];
                if (otype == "function" || otype == "constructor") {
                    if (obj[m]["inherited_from"] && !include_inherited) continue;
                    if (obj[m]["brief"] && obj[m]["brief"].length) {
                        brief = obj[m]["brief"].replace(/\\param/g, "\n\\param");
                        brief = brief.replace(/\\return/g, "\n\\return");
                        brief = brief.replace(/; /g, "\n");
                        brief = brief.replace(/[ \t]+(?=\n|$)/g, "");
                        briefLines = brief.replace(/\n/g, "\n        // ");
                        write( "        // "+obj[m]["name"]+": "+briefLines+"\n");
                    }
                    var fstr = "        "+obj[m]["name"]+" : (";
                    var variants = obj[m]["params"];
                    if (variants.length == 0) {
                        variants = [ [ ] ];
                    } else if (!Array.isArray(variants[0])) {
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
                            .replace(/string\[\]/g, "[\"\"] /* array of strings */");
                            write( fstr + pstr + ") => { return "+returnsStr+"; },");
                        } else {
                            write( fstr + pstr + ") => {},");
                        }
                        write("\n");
                    }
                } else if (otype != "undefined") {
                    if (obj[m]["value"] != undefined) {
                        write("        "+obj[m]["name"]+" : "+obj[m]["value"]+",\n");
                    } else {
                        write("        "+obj[m]["name"]+" : null,\n");
                    }

                }
            }
            write( "    }; },\n\n");
        }
    }
    write("};\n"); // close main var

} else if (format_embind) {
    throw new Error("Use node tools/emscripten/generate.js; Emscripten bindings are generated from source metadata without a PDG runtime.");
}
