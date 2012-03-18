

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sun Mar 18 02:08:57 2012
 */
/* Compiler settings for .\otMapTreeControl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_otMapTreeControlLib,0xB9D879EE,0xBBA9,0x4150,0x9A,0xB9,0xBF,0x62,0x0A,0x2B,0x09,0xC8);


MIDL_DEFINE_GUID(IID, DIID__DotMapTreeControl,0xF8C383A6,0xBC41,0x43ED,0x8D,0xEA,0x6B,0xFE,0xD5,0x91,0xB1,0x92);


MIDL_DEFINE_GUID(IID, DIID__DotMapTreeControlEvents,0xA9D71CB3,0x7908,0x4C84,0xB5,0x47,0x1F,0x6B,0xA6,0xDF,0xEF,0xBC);


MIDL_DEFINE_GUID(CLSID, CLSID_otMapTreeControl,0x87A8EF82,0x3CED,0x4CDA,0xAF,0xC2,0x7E,0x6A,0x36,0xFD,0xE4,0x90);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



