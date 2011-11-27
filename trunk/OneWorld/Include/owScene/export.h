#pragma once

#if defined(_MSC_VER)
#pragma warning( disable : 4312 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#  if defined( OWSCENE_LIBRARY_STATIC )
#    define OWSCENE_EXPORT
#  elif defined( OWSCENE_LIBRARY )
#    define OWSCENE_EXPORT   __declspec(dllexport)
#  else
#    define OWSCENE_EXPORT   __declspec(dllimport)
#  endif
#else
#  define OWSCENE_EXPORT
#endif  

#include <owUtil/Log.h>