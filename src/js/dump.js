// -----------------------------------------------
// dump.js
//
// java object properties dump for debugging
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
// jsminify this file, js2c: jsmin

// this is one of the few javascript files that are built-in
// to the pdg standalone app but also part of the pure 
// javascript implementation

// debug stuff
function printProperties(obj) {
   var propList = "";
   var functionList = "";
   for (var propName in obj) {
      if (typeof(obj[propName]) == "function") {
         functionList += "  '"+propName+"' -> "+(obj[propName]+"\n");
      } else if (typeof(obj[propName]) != "undefined") {
         propList += "  "+(propName + ": " + obj[propName]);
      }
   }
   if (propList.length == 0 && functionList.length == 0) {
      console.log("DUMP:\n" + obj + ": -Empty- ");
   } else {
     var objStr = "DUMP:\n" + obj + ":";
     if (propList.length > 0) {
	    objStr += "\n"+propList;
     }
     if (functionList.length > 0) {
	    objStr += "\n"+functionList;
     }
     console.log(objStr);
   }
}

// Export for module systems
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        printProperties: printProperties
    };
}
// Also support legacy 'exports' global
if (typeof exports !== 'undefined') {
    exports.printProperties = printProperties;
}
console.dump = printProperties;
