#pragma once

#if defined(_MSC_VER)
#pragma warning( disable : 4312 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#  if defined( OWNAVI_LIBRARY_STATIC )
#    define OWNAVI_EXPORT
#  elif defined( OWNAVI_LIBRARY )
#    define OWNAVI_EXPORT   __declspec(dllexport)
#  else
#    define OWNAVI_EXPORT   __declspec(dllimport)
#  endif
#else
#  define OWNAVI_EXPORT
#endif  

#include <owUtil/Log.h>