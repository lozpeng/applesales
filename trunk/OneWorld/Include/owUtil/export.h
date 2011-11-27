#pragma once

#if defined(_MSC_VER)
#pragma warning( disable : 4312 )
#pragma warning( disable : 4251 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#  if defined( OWUTIL_LIBRARY_STATIC )
#    define OWUTIL_EXPORT
#  elif defined( OWUTIL_LIBRARY )
#    define OWUTIL_EXPORT   __declspec(dllexport)
#  else
#    define OWUTIL_EXPORT   __declspec(dllimport)
#  endif
#else
#  define OWUTIL_EXPORT
#endif  

