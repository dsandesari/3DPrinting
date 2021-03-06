/*=========================================================================

  Program:   KWSys - Kitware System Library
  Module:    $RCSfile: kwsys_stl_string.hxx.in,v $

  Copyright (c) Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

// This header is extra code for <vtksys/stl/string>.
#if !defined(vtksys_stl_string_including_hxx)
# error "The header <vtksys/stl/string.hxx> may be included only by <vtksys/stl/string>."
#endif

// Provide the istream operator for the stl string if it is not
// provided by the system or another copy of kwsys.  Allow user code
// to block this definition by defining the macro
// vtksys_STL_STRING_NO_ISTREAM
// to avoid conflicts with other libraries.  User code can test for
// this definition by checking the macro
// vtksys_STL_STRING_ISTREAM_DEFINED
#if !vtksys_STL_STRING_HAVE_ISTREAM && !defined(vtksys_STL_STRING_NO_ISTREAM) && !defined(KWSYS_STL_STRING_ISTREAM_DEFINED)
# define KWSYS_STL_STRING_ISTREAM_DEFINED
# define vtksys_STL_STRING_ISTREAM_DEFINED
# include <ctype.h> // isspace
# include <vtksys/ios/iostream>
# if defined(__WATCOMC__)
namespace vtksys
{
struct ios_istream_hack: public kwsys_ios::istream
{ void eatwhite() { this->vtksys_ios::istream::eatwhite(); } };
}
# endif
inline vtksys_ios::istream&
operator>>(vtksys_ios::istream& is,
           vtksys_stl::string& s)
{
  // Keep track of the resulting state.
  int state = vtksys_ios::ios::goodbit;

  // Save the width setting and set it back to zero.
  size_t n = static_cast<size_t>(is.width(0));

  // Clear any old contents of the output string.
  s.erase();

  // Skip leading whitespace.
#if defined(__WATCOMC__)
  static_cast<vtksys::ios_istream_hack&>(is).eatwhite();
#else
  is.eatwhite();
#endif
  vtksys_ios::istream& okay = is;

  if(okay)
    {
    // Select a maximum possible length.
    if(n == 0 || n >= s.max_size())
      {
      n = s.max_size();
      }

    // Read until a space is found or the maximum length is reached.
    bool success = false;
    for(int c = is.peek(); (--n > 0 && c != EOF && !isspace(c)); c = is.peek())
      {
      s += static_cast<char>(c);
      success = true;
      is.ignore();
      }

    // Set flags for resulting state.
    if(is.peek() == EOF) { state |= vtksys_ios::ios::eofbit; }
    if(!success) { state |= vtksys_ios::ios::failbit; }
    }

  // Set the final result state.
  is.clear(state);
  return is;
}
#endif

// Provide the ostream operator for the stl string if it is not
// provided by the system or another copy of kwsys.  Allow user code
// to block this definition by defining the macro
// vtksys_STL_STRING_NO_OSTREAM
// to avoid conflicts with other libraries.  User code can test for
// this definition by checking the macro
// vtksys_STL_STRING_OSTREAM_DEFINED
#if !vtksys_STL_STRING_HAVE_OSTREAM && !defined(vtksys_STL_STRING_NO_OSTREAM) && !defined(KWSYS_STL_STRING_OSTREAM_DEFINED)
# define KWSYS_STL_STRING_OSTREAM_DEFINED
# define vtksys_STL_STRING_OSTREAM_DEFINED
# include <vtksys/ios/iostream>
inline vtksys_ios::ostream&
operator<<(vtksys_ios::ostream& os,
           vtksys_stl::string const& s)
{
  return os << s.c_str();
}
#endif

// Provide the operator!= for the stl string and char* if it is not
// provided by the system or another copy of kwsys.  Allow user code
// to block this definition by defining the macro
// vtksys_STL_STRING_NO_NEQ_CHAR
// to avoid conflicts with other libraries.  User code can test for
// this definition by checking the macro
// vtksys_STL_STRING_NEQ_CHAR_DEFINED
#if !vtksys_STL_STRING_HAVE_NEQ_CHAR && !defined(vtksys_STL_STRING_NO_NEQ_CHAR) && !defined(KWSYS_STL_STRING_NEQ_CHAR_DEFINED)
# define KWSYS_STL_STRING_NEQ_CHAR_DEFINED
# define vtksys_STL_STRING_NEQ_CHAR_DEFINED
inline bool operator!=(vtksys_stl::string const& s, const char* c)
{
  return !(s == c);
}
inline bool operator!=(const char* c, vtksys_stl::string const& s)
{
  return !(s == c);
}
#endif
