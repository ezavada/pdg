// -----------------------------------------------
// fs.js
//
// Modified version of Node.js' fs module for use with JavaScriptCore
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// Copyright Joyent, Inc. and other Node contributors.
//
// Modified version of Node.js' console module for use with JavaScriptCore
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

// Maintainers, keep in mind that octal literals are not allowed
// in strict mode. Use the decimal value and add a comment with
// the octal value. Example:
//
//   var mode = 438; /* mode=0666 */

/* Needed for PDG:
    binding.stat(path);
    process.nextTick();
    binding.close(fd)
    binding.open(path, flags, mode)
    binding.read(fd, buffer, offset, length, pos)
    binding.fstat(fd)

	needed for fs module:
    Buffer(size)
    Buffer.slice()
    Buffer.concat(bufarray, len) {
    	Buffer.copy(targetBuffer, targetStart=0, sourceStart=0, sourceEnd=buffer.length)
    }
    Buffer.toString(encoding)
    Buffer.isBuffer(buffer)
    Buffer.isEncoding(encoding)
*/   

//var util = require('util');
var pathModule = require('path');

//var binding = process.binding('fs');
var constants = process.binding('constants');
var fs = exports;
//var EventEmitter = require('events').EventEmitter;

//var Stream = require('stream').Stream;
// var Readable = Stream.Readable;
// var Writable = Stream.Writable;
// 
// var kMinPoolSpace = 128;
// 
var O_APPEND = constants.O_APPEND || 0;
var O_CREAT = constants.O_CREAT || 0;
var O_DIRECTORY = constants.O_DIRECTORY || 0;
var O_EXCL = constants.O_EXCL || 0;
var O_NOCTTY = constants.O_NOCTTY || 0;
var O_NOFOLLOW = constants.O_NOFOLLOW || 0;
var O_RDONLY = constants.O_RDONLY || 0;
var O_RDWR = constants.O_RDWR || 0;
var O_SYMLINK = constants.O_SYMLINK || 0;
var O_SYNC = constants.O_SYNC || 0;
var O_TRUNC = constants.O_TRUNC || 0;
var O_WRONLY = constants.O_WRONLY || 0;

var DEBUG = process.env.NODE_DEBUG && /fs/.test(process.env.NODE_DEBUG);

/*
function rethrow() {
  // Only enable in debug mode. A backtrace uses ~1000 bytes of heap space and
  // is fairly slow to generate.
  var callback;
  if (DEBUG) {
    var backtrace = new Error;
    callback = debugCallback;
  } else
    callback = missingCallback;

  return callback;

  function debugCallback(err) {
    if (err) {
      backtrace.message = err.message;
      err = backtrace;
      missingCallback(err);
    }
  }

  function missingCallback(err) {
    if (err) {
      if (process.throwDeprecation)
        throw err;  // Forgot a callback but don't know where? Use NODE_DEBUG=fs
      else if (!process.noDeprecation) {
        var msg = 'fs: missing callback ' + (err.stack || err.message);
        if (process.traceDeprecation)
          console.trace(msg);
        else
          console.error(msg);
      }
    }
  }
}

function maybeCallback(cb) {
  return typeof cb === 'function' ? cb : rethrow();
}

// Ensure that callbacks run in the global context. Only use this function
// for callbacks that are passed to the binding layer, callbacks that are
// invoked from JS already run in the proper scope.
function makeCallback(cb) {
  if (typeof cb !== 'function') {
    return rethrow();
  }

  return function() {
    return cb.apply(null, arguments);
  };
}

*/

function assertEncoding(encoding) {
//  if (encoding && !Buffer.isEncoding(encoding)) {
//    throw new Error('Unknown encoding: ' + encoding);
//  }
}

function nullCheck(path, callback) {
  if (('' + path).indexOf('\u0000') !== -1) {
    var er = new Error('Path must be a string without null bytes.');
    if (!callback)
      throw er;
    process.nextTick(function() {
      callback(er);
    });
    return false;
  }
  return true;
}

fs.Stats = function() {}; //binding.Stats;

fs.Stats.__proto__._checkModeProperty = function(property) {
  return ((this.mode & constants.S_IFMT) === property);
};

fs.Stats.__proto__.isDirectory = function() {
  return this._checkModeProperty(constants.S_IFDIR);
};

fs.Stats.__proto__.isFile = function() {
  return this._checkModeProperty(constants.S_IFREG);
};

fs.Stats.__proto__.isBlockDevice = function() {
  return this._checkModeProperty(constants.S_IFBLK);
};

fs.Stats.__proto__.isCharacterDevice = function() {
  return this._checkModeProperty(constants.S_IFCHR);
};

fs.Stats.__proto__.isSymbolicLink = function() {
  return this._checkModeProperty(constants.S_IFLNK);
};

fs.Stats.__proto__.isFIFO = function() {
  return this._checkModeProperty(constants.S_IFIFO);
};

fs.Stats.__proto__.isSocket = function() {
  return this._checkModeProperty(constants.S_IFSOCK);
};

fs.exists = function(path, callback) {
	throw "Unimplemented fs.exists";
//   if (!nullCheck(path, cb)) return;
//   binding.stat(path, cb);
//   function cb(err, stats) {
//     if (callback) callback(err ? false : true);
//   }
};

fs.existsSync = function(path) {
  try {
    nullCheck(path);
    var stats = process._jsc_stat(path);
    return true;
  } catch (e) {
    return false;
  }
};

fs.readFile = function(path, options, callback_) {
	throw "Unimplemented fs.readFile";
//   var callback = maybeCallback(arguments[arguments.length - 1]);
// 
//   if (typeof options === 'function' || !options) {
//     options = { encoding: null, flag: 'r' };
//   } else if (typeof options === 'string') {
//     options = { encoding: options, flag: 'r' };
//   } else if (!options) {
//     options = { encoding: null, flag: 'r' };
//   } else if (typeof options !== 'object') {
//     throw new TypeError('Bad arguments');
//   }
// 
//   var encoding = options.encoding;
//   assertEncoding(encoding);
// 
//   // first, stat the file, so we know the size.
//   var size;
//   var buffer; // single buffer with file data
//   var buffers; // list for when size is unknown
//   var pos = 0;
//   var fd;
// 
//   var flag = options.flag || 'r';
//   fs.open(path, flag, 438, function(er, fd_) {  // 438 = 0666
//     if (er) return callback(er);
//     fd = fd_;
// 
//     fs.fstat(fd, function(er, st) {
//       if (er) return callback(er);
//       size = st.size;
//       if (size === 0) {
//         // the kernel lies about many files.
//         // Go ahead and try to read some bytes.
//         buffers = [];
//         return read();
//       }
// 
//       buffer = new Buffer(size);
//       read();
//     });
//   });
// 
//   function read() {
//     if (size === 0) {
//       buffer = new Buffer(8192);
//       fs.read(fd, buffer, 0, 8192, -1, afterRead);
//     } else {
//       fs.read(fd, buffer, pos, size - pos, -1, afterRead);
//     }
//   }
// 
//   function afterRead(er, bytesRead) {
//     if (er) {
//       return fs.close(fd, function(er2) {
//         return callback(er);
//       });
//     }
// 
//     if (bytesRead === 0) {
//       return close();
//     }
// 
//     pos += bytesRead;
//     if (size !== 0) {
//       if (pos === size) close();
//       else read();
//     } else {
//       // unknown size, just read until we don't get bytes.
//       buffers.push(buffer.slice(0, bytesRead));
//       read();
//     }
//   }
// 
//   function close() {
//     fs.close(fd, function(er) {
//       if (size === 0) {
//         // collected the data into the buffers list.
//         buffer = Buffer.concat(buffers, pos);
//       } else if (pos < size) {
//         buffer = buffer.slice(0, pos);
//       }
// 
//       if (encoding) buffer = buffer.toString(encoding);
//       return callback(er, buffer);
//     });
//   }
};


fs.readFileSync = function(path, options) {
	// TODO: maybe just call a single C++ hook to read entire contents of file
  if (!options) {
    options = { encoding: null, flag: 'r' };
  } else if (typeof options === 'string') {
    options = { encoding: options, flag: 'r' };
  } else if (typeof options !== 'object') {
    throw new TypeError('Bad arguments');
  }

  var encoding = options.encoding;
  assertEncoding(encoding);

  var flag = options.flag || 'r';
  var fileContents = process._jsc_readFileContents(path, flag);
  if (typeof fileContents == 'undefined') {
    throw new Error('Read File ['+path+'] Failed.');
  }
  return fileContents;
};


// Used by binding.open and friends
function stringToFlags(flag) {
// Only mess with strings
  if (typeof flag !== 'string') {
    return flag;
  }
// 
// O_EXCL is mandated by POSIX, Windows supports it too.
// Let's add a check anyway, just in case.
  if (!O_EXCL && ~flag.indexOf('x')) {
    throw errnoException('ENOSYS', 'fs.open(O_EXCL)');
  }

  switch (flag) {
    case 'r' : return O_RDONLY;
    case 'rs' : return O_RDONLY | O_SYNC;
    case 'r+' : return O_RDWR;
    case 'rs+' : return O_RDWR | O_SYNC;

    case 'w' : return O_TRUNC | O_CREAT | O_WRONLY;
    case 'wx' : // fall through
    case 'xw' : return O_TRUNC | O_CREAT | O_WRONLY | O_EXCL;

    case 'w+' : return O_TRUNC | O_CREAT | O_RDWR;
    case 'wx+': // fall through
    case 'xw+': return O_TRUNC | O_CREAT | O_RDWR | O_EXCL;

    case 'a' : return O_APPEND | O_CREAT | O_WRONLY;
    case 'ax' : // fall through
    case 'xa' : return O_APPEND | O_CREAT | O_WRONLY | O_EXCL;

    case 'a+' : return O_APPEND | O_CREAT | O_RDWR;
    case 'ax+': // fall through
    case 'xa+': return O_APPEND | O_CREAT | O_RDWR | O_EXCL;
  }

  throw new Error('Unknown file open flag: ' + flag);
}

// exported but hidden, only used by test/simple/test-fs-open-flags.js
// Object.defineProperty(exports, '_stringToFlags', {
//   enumerable: false,
//   value: stringToFlags
// });

// Yes, the follow could be easily DRYed up but I provide the explicit
// list to make the arguments clear.

fs.close = function(fd, callback) {
	throw "Unimplemented fs.close";
//  binding.close(fd, makeCallback(callback));
};


fs.closeSync = function(fd) {
	throw "Unimplemented fs.closeSync";
//   return binding.close(fd);
};


function modeNum(m, def) {
  switch (typeof m) {
    case 'number': return m;
    case 'string': return parseInt(m, 8);
    default:
      if (def) {
        return modeNum(def);
      } else {
        return undefined;
      }
  }
}

fs.open = function(path, flags, mode, callback) {
	throw "Unimplemented fs.open";
//   callback = makeCallback(arguments[arguments.length - 1]);
//   mode = modeNum(mode, 438 );  // 438 = 0666
// 
//   if (!nullCheck(path, callback)) return;
//   binding.open(path,
//                stringToFlags(flags),
//                mode,
//                callback);
};


fs.openSync = function(path, flags, mode) {
  mode = modeNum(mode, 438);
  nullCheck(path);
	throw "Unimplemented fs.openSync";
//   return binding.open(path, stringToFlags(flags), mode);
};

fs.read = function(fd, buffer, offset, length, position, callback) {
	throw "Unimplemented fs.read";
//   if (!Buffer.isBuffer(buffer)) {
//     // legacy string interface (fd, length, position, encoding, callback)
//     var cb = arguments[4],
//         encoding = arguments[3];
// 
//     assertEncoding(encoding);
// 
//     position = arguments[2];
//     length = arguments[1];
//     buffer = new Buffer(length);
//     offset = 0;
// 
//     callback = function(err, bytesRead) {
//       if (!cb) return;
// 
//       var str = (bytesRead > 0) ? buffer.toString(encoding, 0, bytesRead) : '';
// 
//       (cb)(err, str, bytesRead);
//     };
//   }
// 
//   function wrapper(err, bytesRead) {
//     // Retain a reference to buffer so that it can't be GC'ed too soon.
//     callback && callback(err, bytesRead || 0, buffer);
//   }
// 
//   binding.read(fd, buffer, offset, length, position, wrapper);
};


fs.readSync = function(fd, buffer, offset, length, position) {
	throw "Unimplemented fs.readSync";
  var legacy = false;
//   if (!Buffer.isBuffer(buffer)) {
//     // legacy string interface (fd, length, position, encoding, callback)
//     legacy = true;
//     var encoding = arguments[3];
// 
//     assertEncoding(encoding);
// 
//     position = arguments[2];
//     length = arguments[1];
//     buffer = new Buffer(length);
// 
//     offset = 0;
//   }
// 
//   var r = binding.read(fd, buffer, offset, length, position);
//   if (!legacy) {
//     return r;
//   }
// 
//   var str = (r > 0) ? buffer.toString(encoding, 0, r) : '';
//   return [str, r];
};

fs.write = function(fd, buffer, offset, length, position, callback) {
	throw "Unimplemented fs.write";
//   if (!Buffer.isBuffer(buffer)) {
//     // legacy string interface (fd, data, position, encoding, callback)
//     callback = arguments[4];
//     position = arguments[2];
//     assertEncoding(arguments[3]);
// 
//     buffer = new Buffer('' + arguments[1], arguments[3]);
//     offset = 0;
//     length = buffer.length;
//   }
// 
//   if (!length) {
//     if (typeof callback == 'function') {
//       process.nextTick(function() {
//         callback(undefined, 0);
//       });
//     }
//     return;
//   }
// 
//   callback = maybeCallback(callback);
// 
//   function wrapper(err, written) {
//     // Retain a reference to buffer so that it can't be GC'ed too soon.
//     callback(err, written || 0, buffer);
//   }
// 
//   binding.write(fd, buffer, offset, length, position, wrapper);
};

fs.writeSync = function(fd, buffer, offset, length, position) {
	throw "Unimplemented fs.writeSync";
//   if (!Buffer.isBuffer(buffer)) {
//     // legacy string interface (fd, data, position, encoding)
//     position = arguments[2];
//     assertEncoding(arguments[3]);
// 
//     buffer = new Buffer('' + arguments[1], arguments[3]);
//     offset = 0;
//     length = buffer.length;
//   }
//   if (!length) return 0;
// 
//   return binding.write(fd, buffer, offset, length, position);
};

fs.rename = function(oldPath, newPath, callback) {
	throw "Unimplemented fs.rename";
//   callback = makeCallback(callback);
//   if (!nullCheck(oldPath, callback)) return;
//   if (!nullCheck(newPath, callback)) return;
//   binding.rename(oldPath,
//                  newPath,
//                  callback);
};

fs.renameSync = function(oldPath, newPath) {
	throw "Unimplemented fs.renameSync";
//   nullCheck(oldPath);
//   nullCheck(newPath);
//   return binding.rename(oldPath,
//                         newPath);
};

fs.truncate = function(path, len, callback) {
	throw "Unimplemented fs.truncate";
//   if (typeof path === 'number') {
//     // legacy
//     return fs.ftruncate(path, len, callback);
//   }
//   if (typeof len === 'function') {
//     callback = len;
//     len = 0;
//   } else if (typeof len === 'undefined') {
//     len = 0;
//   }
//   callback = maybeCallback(callback);
//   fs.open(path, 'w', function(er, fd) {
//     if (er) return callback(er);
//     binding.ftruncate(fd, len, function(er) {
//       fs.close(fd, function(er2) {
//         callback(er || er2);
//       });
//     });
//   });
};

fs.truncateSync = function(path, len) {
	throw "Unimplemented fs.truncateSync";
//   if (typeof path === 'number') {
//     // legacy
//     return fs.ftruncateSync(path, len);
//   }
//   if (typeof len === 'undefined') {
//     len = 0;
//   }
//   // allow error to be thrown, but still close fd.
//   var fd = fs.openSync(path, 'w');
//   try {
//     var ret = fs.ftruncateSync(fd, len);
//   } finally {
//     fs.closeSync(fd);
//   }
//   return ret;
};

fs.ftruncate = function(fd, len, callback) {
	throw "Unimplemented fs.ftruncate";
//   if (typeof len === 'function') {
//     callback = len;
//     len = 0;
//   } else if (typeof len === 'undefined') {
//     len = 0;
//   }
//   binding.ftruncate(fd, len, makeCallback(callback));
};

fs.ftruncateSync = function(fd, len) {
	throw "Unimplemented fs.ftruncateSync";
//   if (typeof len === 'undefined') {
//     len = 0;
//   }
//   return binding.ftruncate(fd, len);
};

fs.rmdir = function(path, callback) {
	throw "Unimplemented fs.rmdir";
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.rmdir(path, callback);
};

fs.rmdirSync = function(path) {
	throw "Unimplemented fs.rmdirSync";
//   nullCheck(path);
//   return binding.rmdir(path);
};

fs.fdatasync = function(fd, callback) {
	throw "Unimplemented fs.fdatasync";
//   binding.fdatasync(fd, makeCallback(callback));
};

fs.fdatasyncSync = function(fd) {
	throw "Unimplemented fs.fdatasyncSync";
//  return binding.fdatasync(fd);
};

fs.fsync = function(fd, callback) {
	throw "Unimplemented fs.fsync";
//  binding.fsync(fd, makeCallback(callback));
};

fs.fsyncSync = function(fd) {
	throw "Unimplemented fs.fsyncSunc";
//  return binding.fsync(fd);
};

fs.mkdir = function(path, mode, callback) {
	throw "Unimplemented fs.mkdir";
//   if (typeof mode === 'function') callback = mode;
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.mkdir(path,
//                 modeNum(mode, 511), // 511 = 0777
//                 callback);
};

fs.mkdirSync = function(path, mode) {
	throw "Unimplemented fs.mkdirSync";
//   nullCheck(path);
//   return binding.mkdir(path,
//                        modeNum(mode, 511));
};

fs.readdir = function(path, callback) {
	throw "Unimplemented fs.readdir";
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.readdir(path, callback);
};

fs.readdirSync = function(path) {
   nullCheck(path);
   var pdgfs = require('pdg').fs;
   var files = pdgfs.findFiles(path+'/*');
   return files;
//   return binding.readdir(path);
};

fs.fstat = function(fd, callback) {
	throw "Unimplemented fs.fstat";
//  binding.fstat(fd, makeCallback(callback));
};

fs.lstat = function(path, callback) {
	throw "Unimplemented fs.lstat";
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.lstat(path, callback);
};

fs.stat = function(path, callback) {
	throw "Unimplemented fs.stat";
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.stat(path, callback);
};

fs.fstatSync = function(fd) {
	throw "Unimplemented fs.fstatSync";
//  return process._jsc_fstat(fd)
};

fs.lstatSync = function(path) {
  nullCheck(path);
  var stats = process._jsc_lstat(path);
  stats.__proto__ = fs.Stats.__proto__;
  return stats;
};

fs.statSync = function(path) {
  nullCheck(path);
  var stats = process._jsc_stat(path);
  stats.__proto__ = fs.Stats.__proto__;
  return stats;
};

fs.readlink = function(path, callback) {
	throw "Unimplemented fs.readlink";
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.readlink(path, callback);
};

fs.readlinkSync = function(path) {
  nullCheck(path);
  var linkdat = process._jsc_readlink(path);
  return linkdat;
};

function preprocessSymlinkDestination(path, type) {
	// No preprocessing is needed on Unix.
    return path;
}

fs.symlink = function(destination, path, type_, callback) {
	throw "Unimplemented fs.symlink";
//   var type = (typeof type_ === 'string' ? type_ : null);
//   var callback = makeCallback(arguments[arguments.length - 1]);
// 
//   if (!nullCheck(destination, callback)) return;
//   if (!nullCheck(path, callback)) return;
// 
//   binding.symlink(preprocessSymlinkDestination(destination, type),
//                   path,
//                   type,
//                   callback);
};

fs.symlinkSync = function(destination, path, type) {
	throw "Unimplemented fs.symlinkSync";
//   type = (typeof type === 'string' ? type : null);
// 
//   nullCheck(destination);
//   nullCheck(path);
// 
//   return binding.symlink(preprocessSymlinkDestination(destination, type),
//                          path,
//                          type);
};

fs.link = function(srcpath, dstpath, callback) {
	throw "Unimplemented fs.link";
//   callback = makeCallback(callback);
//   if (!nullCheck(srcpath, callback)) return;
//   if (!nullCheck(dstpath, callback)) return;
// 
//   binding.link(srcpath,
//                dstpath,
//                callback);
};

fs.linkSync = function(srcpath, dstpath) {
	throw "Unimplemented fs.linkSync";
//   nullCheck(srcpath);
//   nullCheck(dstpath);
//   return binding.link(srcpath,
//                       dstpath);
};

fs.unlink = function(path, callback) {
	throw "Unimplemented fs.unlink";
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.unlink(path, callback);
};

fs.unlinkSync = function(path) {
  nullCheck(path);
  return process._jsc_unlink(path);
};

fs.fchmod = function(fd, mode, callback) {
	throw "Unimplemented fs.fchmod";
//   binding.fchmod(fd, modeNum(mode), makeCallback(callback));
};

fs.fchmodSync = function(fd, mode) {
	throw "Unimplemented fs.fchmodSync";
//   return binding.fchmod(fd, modeNum(mode));
};

if (constants.hasOwnProperty('O_SYMLINK')) {
  fs.lchmod = function(path, mode, callback) {
	throw "Unimplemented fs.lchmod";
//     callback = maybeCallback(callback);
//     fs.open(path, constants.O_WRONLY | constants.O_SYMLINK, function(err, fd) {
//       if (err) {
//         callback(err);
//         return;
//       }
//       // prefer to return the chmod error, if one occurs,
//       // but still try to close, and report closing errors if they occur.
//       fs.fchmod(fd, mode, function(err) {
//         fs.close(fd, function(err2) {
//           callback(err || err2);
//         });
//       });
//     });
  };

  fs.lchmodSync = function(path, mode) {
	throw "Unimplemented fs.lchmodSync";
//     var fd = fs.openSync(path, constants.O_WRONLY | constants.O_SYMLINK);
// 
//     // prefer to return the chmod error, if one occurs,
//     // but still try to close, and report closing errors if they occur.
//     var err, err2;
//     try {
//       var ret = fs.fchmodSync(fd, mode);
//     } catch (er) {
//       err = er;
//     }
//     try {
//       fs.closeSync(fd);
//     } catch (er) {
//       err2 = er;
//     }
//     if (err || err2) throw (err || err2);
//     return ret;
  };
}


fs.chmod = function(path, mode, callback) {
	throw "Unimplemented fs.chmod";
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.chmod(path,
//                 modeNum(mode),
//                 callback);
};

fs.chmodSync = function(path, mode) {
	throw "Unimplemented fs.chmodSync";
//   nullCheck(path);
//   return binding.chmod(path, modeNum(mode));
};

if (constants.hasOwnProperty('O_SYMLINK')) {
  fs.lchown = function(path, uid, gid, callback) {
	throw "Unimplemented fs.lchown";
//     callback = maybeCallback(callback);
//     fs.open(path, constants.O_WRONLY | constants.O_SYMLINK, function(err, fd) {
//       if (err) {
//         callback(err);
//         return;
//       }
//       fs.fchown(fd, uid, gid, callback);
//     });
  };

  fs.lchownSync = function(path, uid, gid) {
	throw "Unimplemented fs.lchownSync";
//     var fd = fs.openSync(path, constants.O_WRONLY | constants.O_SYMLINK);
//     return fs.fchownSync(fd, uid, gid);
  };
}

fs.fchown = function(fd, uid, gid, callback) {
	throw "Unimplemented fs.fchown";
//  binding.fchown(fd, uid, gid, makeCallback(callback));
};

fs.fchownSync = function(fd, uid, gid) {
	throw "Unimplemented fs.fchownSync";
//  return binding.fchown(fd, uid, gid);
};

fs.chown = function(path, uid, gid, callback) {
	throw "Unimplemented fs.chown";
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.chown(path, uid, gid, callback);
};

fs.chownSync = function(path, uid, gid) {
	throw "Unimplemented fs.chownSync";
//   nullCheck(path);
//   return binding.chown(path, uid, gid);
};

// converts Date or number to a fractional UNIX timestamp
function toUnixTimestamp(time) {
  if (typeof time == 'number') {
    return time;
  }
  if (time instanceof Date) {
    // convert to 123.456 UNIX timestamp
    return time.getTime() / 1000;
  }
  throw new Error('Cannot parse time: ' + time);
}

// exported for unit tests, not for public consumption
fs._toUnixTimestamp = toUnixTimestamp;

fs.utimes = function(path, atime, mtime, callback) {
	throw "Unimplemented fs.utimes";
//   callback = makeCallback(callback);
//   if (!nullCheck(path, callback)) return;
//   binding.utimes(path,
//                  toUnixTimestamp(atime),
//                  toUnixTimestamp(mtime),
//                  callback);
};

fs.utimesSync = function(path, atime, mtime) {
	throw "Unimplemented fs.utimesSync";
//   nullCheck(path);
//   atime = toUnixTimestamp(atime);
//   mtime = toUnixTimestamp(mtime);
//   binding.utimes(path, atime, mtime);
};

fs.futimes = function(fd, atime, mtime, callback) {
	throw "Unimplemented fs.futimes";
//   atime = toUnixTimestamp(atime);
//   mtime = toUnixTimestamp(mtime);
//   binding.futimes(fd, atime, mtime, makeCallback(callback));
};

fs.futimesSync = function(fd, atime, mtime) {
	throw "Unimplemented fs.futimesSync";
//   atime = toUnixTimestamp(atime);
//   mtime = toUnixTimestamp(mtime);
//   binding.futimes(fd, atime, mtime);
};

function writeAll(fd, buffer, offset, length, position, callback) {
  callback = maybeCallback(arguments[arguments.length - 1]);

  // write(fd, buffer, offset, length, position, callback)
  fs.write(fd, buffer, offset, length, position, function(writeErr, written) {
    if (writeErr) {
      fs.close(fd, function() {
        if (callback) callback(writeErr);
      });
    } else {
      if (written === length) {
        fs.close(fd, callback);
      } else {
        offset += written;
        length -= written;
        position += written;
        writeAll(fd, buffer, offset, length, position, callback);
      }
    }
  });
}

fs.writeFile = function(path, data, options, callback) {
	throw "Unimplemented fs.writeFile";
//   var callback = maybeCallback(arguments[arguments.length - 1]);
// 
//   if (typeof options === 'function' || !options) {
//     options = { encoding: 'utf8', mode: 438 , flag: 'w' };
//   } else if (typeof options === 'string') {
//     options = { encoding: options, mode: 438, flag: 'w' };
//   } else if (!options) {
//     options = { encoding: 'utf8', mode: 438 , flag: 'w' };
//   } else if (typeof options !== 'object') {
//     throw new TypeError('Bad arguments');
//   }
// 
//   assertEncoding(options.encoding);
// 
//   var flag = options.flag || 'w';
//   fs.open(path, options.flag || 'w', options.mode, function(openErr, fd) {
//     if (openErr) {
//       if (callback) callback(openErr);
//     } else {
//       var buffer = Buffer.isBuffer(data) ? data : new Buffer('' + data,
//           options.encoding || 'utf8');
//       var position = /a/.test(flag) ? null : 0;
//       writeAll(fd, buffer, 0, buffer.length, position, callback);
//     }
//   });
};

fs.writeFileSync = function(path, data, options) {
  if (!options) {
    options = { encoding: 'utf8', mode: 438, flag: 'w' };
  } else if (typeof options === 'string') {
    options = { encoding: options, mode: 438, flag: 'w' };
  } else if (typeof options !== 'object') {
    throw new TypeError('Bad arguments');
  }

  assertEncoding(options.encoding);
  if (typeof Buffer !== 'undefined' && Buffer.isBuffer(data)) {
    data = data.toString(options.encoding || 'utf8');
  } else {
    data = '' + data;
  }
  return process._jsc_writeFileContents(path, data, options.flag || 'w');
};

fs.appendFile = function(path, data, options, callback_) {
	throw "Unimplemented fs.appendFile";
//   var callback = maybeCallback(arguments[arguments.length - 1]);
// 
//   if (typeof options === 'function' || !options) {
//     options = { encoding: 'utf8', mode: 438 , flag: 'a' };
//   } else if (typeof options === 'string') {
//     options = { encoding: options, mode: 438, flag: 'a' };
//   } else if (!options) {
//     options = { encoding: 'utf8', mode: 438 , flag: 'a' };
//   } else if (typeof options !== 'object') {
//     throw new TypeError('Bad arguments');
//   }
// 
//   if (!options.flag)
//     options = util._extend({ flag: 'a' }, options);
//   fs.writeFile(path, data, options, callback);
};

fs.appendFileSync = function(path, data, options) {
	throw "Unimplemented fs.appendFileSync";
//   if (!options) {
//     options = { encoding: 'utf8', mode: 438 , flag: 'a' };
//   } else if (typeof options === 'string') {
//     options = { encoding: options, mode: 438, flag: 'a' };
//   } else if (typeof options !== 'object') {
//     throw new TypeError('Bad arguments');
//   }
//   if (!options.flag)
//     options = util._extend({ flag: 'a' }, options);
// 
//   fs.writeFileSync(path, data, options);
};

// function errnoException(errorno, syscall) {
//   // TODO make this more compatible with ErrnoException from src/node.cc
//   // Once all of Node is using this function the ErrnoException from
//   // src/node.cc should be removed.
//   var e = new Error(syscall + ' ' + errorno);
//   e.errno = e.code = errorno;
//   e.syscall = syscall;
//   return e;
// }
// 

/*
function FSWatcher() {
  EventEmitter.call(this);

  var self = this;
  var FSEvent = process.binding('fs_event_wrap').FSEvent;
  this._handle = new FSEvent();
  this._handle.owner = this;

  this._handle.onchange = function(status, event, filename) {
    if (status) {
      self._handle.close();
      self.emit('error', errnoException(process._errno, 'watch'));
    } else {
      self.emit('change', event, filename);
    }
  };
}
util.inherits(FSWatcher, EventEmitter);

FSWatcher.prototype.start = function(filename, persistent) {
  nullCheck(filename);
  var r = this._handle.start(filename, persistent);

  if (r) {
    this._handle.close();
    throw errnoException(process._errno, 'watch');
  }
};

FSWatcher.prototype.close = function() {
  this._handle.close();
};
*/

fs.watch = function(filename) {
	throw "Unimplemented fs.watch";
//   nullCheck(filename);
//   var watcher;
//   var options;
//   var listener;
// 
//   if ('object' == typeof arguments[1]) {
//     options = arguments[1];
//     listener = arguments[2];
//   } else {
//     options = {};
//     listener = arguments[1];
//   }
// 
//   if (options.persistent === undefined) options.persistent = true;
// 
//   watcher = new FSWatcher();
//   watcher.start(filename, options.persistent);
// 
//   if (listener) {
//     watcher.addListener('change', listener);
//   }
// 
//   return watcher;
};


// Stat Change Watchers

/*
function StatWatcher() {
  EventEmitter.call(this);

  var self = this;
  this._handle = new binding.StatWatcher();

  // uv_fs_poll is a little more powerful than ev_stat but we curb it for
  // the sake of backwards compatibility
  var oldStatus = -1;

  this._handle.onchange = function(current, previous, newStatus) {
    if (oldStatus === -1 &&
        newStatus === -1 &&
        current.nlink === previous.nlink) return;

    oldStatus = newStatus;
    self.emit('change', current, previous);
  };

  this._handle.onstop = function() {
    self.emit('stop');
  };
}
util.inherits(StatWatcher, EventEmitter);


StatWatcher.prototype.start = function(filename, persistent, interval) {
  nullCheck(filename);
  this._handle.start(filename, persistent, interval);
};


StatWatcher.prototype.stop = function() {
  this._handle.stop();
};


var statWatchers = {};
function inStatWatchers(filename) {
  return Object.prototype.hasOwnProperty.call(statWatchers, filename) &&
      statWatchers[filename];
}

*/

fs.watchFile = function(filename) {
	throw "Unimplemented fs.watchFile";
//   nullCheck(filename);
//   var stat;
//   var listener;
// 
//   var options = {
//     // Poll interval in milliseconds. 5007 is what libev used to use. It's
//     // a little on the slow side but let's stick with it for now to keep
//     // behavioral changes to a minimum.
//     interval: 5007,
//     persistent: true
//   };
// 
//   if ('object' == typeof arguments[1]) {
//     options = util._extend(options, arguments[1]);
//     listener = arguments[2];
//   } else {
//     listener = arguments[1];
//   }
// 
//   if (!listener) {
//     throw new Error('watchFile requires a listener function');
//   }
// 
//   if (inStatWatchers(filename)) {
//     stat = statWatchers[filename];
//   } else {
//     stat = statWatchers[filename] = new StatWatcher();
//     stat.start(filename, options.persistent, options.interval);
//   }
//   stat.addListener('change', listener);
//   return stat;
};

fs.unwatchFile = function(filename, listener) {
	throw "Unimplemented fs.unwatchFile";
//   nullCheck(filename);
//   if (!inStatWatchers(filename)) return;
// 
//   var stat = statWatchers[filename];
// 
//   if (typeof listener === 'function') {
//     stat.removeListener('change', listener);
//   } else {
//     stat.removeAllListeners('change');
//   }
// 
//   if (EventEmitter.listenerCount(stat, 'change') === 0) {
//     stat.stop();
//     statWatchers[filename] = undefined;
//   }
};

// Realpath
// Not using realpath(2) because it's bad.
// See: http://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html

var normalize = pathModule.normalize;

// Regexp that finds the next partion of a (partial) path
// result is [base_with_slash, base], e.g. ['somedir/', 'somedir']
var nextPartRe = /(.*?)(?:[\/]+|$)/g;

// Regex to find the device root, including trailing slash. E.g. 'c:\\'.
var splitRootRe = /^(?:[a-zA-Z]:|[\\\/]{2}[^\\\/]+[\\\/][^\\\/]+)?[\\\/]*/;

fs.realpathSync = function realpathSync(p, cache) {
  // make p is absolute
  p = pathModule.resolve(p);

  if (cache && Object.__proto__.hasOwnProperty.call(cache, p)) {
    return cache[p];
  }

  var original = p,
      seenLinks = {},
      knownHard = {};

  // current character position in p
  var pos;
  // the partial path so far, including a trailing slash if any
  var current;
  // the partial path without a trailing slash (except when pointing at a root)
  var base;
  // the partial path scanned in the previous round, with slash
  var previous;

  start();

  function start() {
    // Skip over roots
    var m = splitRootRe.exec(p);
    pos = m[0].length;
    current = m[0];
    base = m[0];
    previous = '';
  }

  // walk down the path, swapping out linked pathparts for their real
  // values
  // NB: p.length changes.
  while (pos < p.length) {
    // find the next part
    nextPartRe.lastIndex = pos;
    var result = nextPartRe.exec(p);
    previous = current;
    current += result[0];
    base = previous + result[1];
    pos = nextPartRe.lastIndex;

    // continue if not a symlink
    if (knownHard[base] || (cache && cache[base] === base)) {
      continue;
    }

    var resolvedLink;
    if (cache && Object.__proto__.hasOwnProperty.call(cache, base)) {
      // some known symbolic link.  no need to stat again.
      resolvedLink = cache[base];
    } else {
      var stat = fs.lstatSync(base);
      if (!stat.isSymbolicLink()) {
        knownHard[base] = true;
        if (cache) cache[base] = base;
        continue;
      }

      // read the link if it wasn't read before
      // dev/ino always return 0 on windows, so skip the check.
      var linkTarget = null;
	  var id = stat.dev.toString(32) + ':' + stat.ino.toString(32);
	  if (seenLinks.hasOwnProperty(id)) {
		linkTarget = seenLinks[id];
	  }
      if (linkTarget === null) {
        fs.statSync(base);
        linkTarget = fs.readlinkSync(base);
      }
      resolvedLink = pathModule.resolve(previous, linkTarget);
      // track this, if given a cache.
      if (cache) cache[base] = resolvedLink;
      seenLinks[id] = linkTarget;
    }

    // resolve the link, then start over
    p = pathModule.resolve(resolvedLink, p.slice(pos));
    start();
  }

  if (cache) cache[original] = p;

  return p;
};

fs.realpath = function realpath(p, cache, cb) {
	throw "Unimplemented fs.realpath";
//   if (typeof cb !== 'function') {
//     cb = maybeCallback(cache);
//     cache = null;
//   }
// 
//   // make p is absolute
//   p = pathModule.resolve(p);
// 
//   if (cache && Object.prototype.hasOwnProperty.call(cache, p)) {
//     return process.nextTick(cb.bind(null, null, cache[p]));
//   }
// 
//   var original = p,
//       seenLinks = {},
//       knownHard = {};
// 
//   // current character position in p
//   var pos;
//   // the partial path so far, including a trailing slash if any
//   var current;
//   // the partial path without a trailing slash (except when pointing at a root)
//   var base;
//   // the partial path scanned in the previous round, with slash
//   var previous;
// 
//   start();
// 
//   function start() {
//     // Skip over roots
//     var m = splitRootRe.exec(p);
//     pos = m[0].length;
//     current = m[0];
//     base = m[0];
//     previous = '';
// 
//     process.nextTick(LOOP);
//   }
// 
//   // walk down the path, swapping out linked pathparts for their real
//   // values
//   function LOOP() {
//     // stop if scanned past end of path
//     if (pos >= p.length) {
//       if (cache) cache[original] = p;
//       return cb(null, p);
//     }
// 
//     // find the next part
//     nextPartRe.lastIndex = pos;
//     var result = nextPartRe.exec(p);
//     previous = current;
//     current += result[0];
//     base = previous + result[1];
//     pos = nextPartRe.lastIndex;
// 
//     // continue if not a symlink
//     if (knownHard[base] || (cache && cache[base] === base)) {
//       return process.nextTick(LOOP);
//     }
// 
//     if (cache && Object.prototype.hasOwnProperty.call(cache, base)) {
//       // known symbolic link.  no need to stat again.
//       return gotResolvedLink(cache[base]);
//     }
// 
//     return fs.lstat(base, gotStat);
//   }
// 
//   function gotStat(err, stat) {
//     if (err) return cb(err);
// 
//     // if not a symlink, skip to the next path part
//     if (!stat.isSymbolicLink()) {
//       knownHard[base] = true;
//       if (cache) cache[base] = base;
//       return process.nextTick(LOOP);
//     }
// 
//     // stat & read the link if not read before
//     // call gotTarget as soon as the link target is known
//       var id = stat.dev.toString(32) + ':' + stat.ino.toString(32);
//       if (seenLinks.hasOwnProperty(id)) {
//         return gotTarget(null, seenLinks[id], base);
//       }
//     fs.stat(base, function(err) {
//       if (err) return cb(err);
// 
//       fs.readlink(base, function(err, target) {
//         seenLinks[id] = target;
//         gotTarget(err, target);
//       });
//     });
//   }
// 
//   function gotTarget(err, target, base) {
//     if (err) return cb(err);
// 
//     var resolvedLink = pathModule.resolve(previous, target);
//     if (cache) cache[base] = resolvedLink;
//     gotResolvedLink(resolvedLink);
//   }
// 
//   function gotResolvedLink(resolvedLink) {
//     // resolve the link, then start over
//     p = pathModule.resolve(resolvedLink, p.slice(pos));
//     start();
//   }
};


/*
var pool;

function allocNewPool(poolSize) {
  pool = new Buffer(poolSize);
  pool.used = 0;
}
*/
