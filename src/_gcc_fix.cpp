// -----------------------------------------------
// _gcc_fix.cpp
//
// this file is present to fix linker errors caused by some gcc versions not having template specializations
// for unsigned short in their libraries
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

#include "pdg/sys/platform.h"

#ifdef COMPILER_GCC

#include <cwchar>
#include <bits/char_traits.h>


namespace std {

  typedef fpos<mbstate_t> 		wstreampos;

  /// char_traits specializations
  template<>
    struct char_traits<unsigned short>
    {
      typedef unsigned short 	char_type;
      typedef unsigned int 	    int_type;
      typedef streamoff 	off_type;
      typedef wstreampos 	pos_type;
      typedef mbstate_t 	state_type;
      
      static void 
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static bool 
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static bool 
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }

      static int 
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemcmp((wchar_t*)__s1, (wchar_t*)__s2, __n); }

      static size_t
      length(const char_type* __s)
      { return wcslen((wchar_t*)__s); }

      static const char_type* 
      find(const char_type* __s, size_t __n, const char_type& __a)
      { return (char_type*)wmemchr((wchar_t*)__s, __a, __n); }

      static char_type* 
      move(char_type* __s1, const char_type* __s2, unsigned int __n)
      { return (char_type*)wmemmove((wchar_t*)__s1, (wchar_t*)__s2, __n); }

      static char_type* 
      move(char_type* __s1, const char_type* __s2, unsigned long __n)
      { return (char_type*)wmemmove((wchar_t*)__s1, (wchar_t*)__s2, __n); }

      static char_type* 
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      { return (char_type*)wmemcpy((wchar_t*)__s1, (wchar_t*)__s2, __n); }

      static char_type* 
      assign(char_type* __s, size_t __n, char_type __a)
      { return (char_type*)wmemset((wchar_t*)__s, __a, __n); }

      static char_type 
      to_char_type(const int_type& __c) { return char_type(__c); }

      static int_type 
      to_int_type(const char_type& __c) { return int_type(__c); }

      static bool 
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static int_type 
      eof() { return static_cast<int_type>(WEOF); }

      static int_type 
      not_eof(const int_type& __c)
      { return eq_int_type(__c, eof()) ? 0 : __c; }
  };
  
}

#endif // COMPILER_GCC


