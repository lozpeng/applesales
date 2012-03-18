

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sun Mar 18 00:02:34 2012
 */
/* Compiler settings for .\otMapControl.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_otMapControlLib,0x83832279,0x48EB,0x4E01,0xA8,0x42,0x7A,0x17,0xDA,0xBE,0x20,0xA5);


MIDL_DEFINE_GUID(IID, DIID__DotMapControl,0x1C60EC25,0x8C5A,0x4B28,0xAE,0xF7,0x01,0x7C,0x15,0x8D,0x40,0x17);


MIDL_DEFINE_GUID(IID, DIID__DotMapControlEvents,0x5E23396E,0x8367,0x4E8E,0xA9,0xFF,0xCB,0xA2,0x3B,0x37,0x8F,0xAA);


MIDL_DEFINE_GUID(CLSID, CLSID_otMapControl,0x875F9C3B,0x337B,0x4D2C,0xA3,0x25,0x27,0x7F,0x2E,0x1D,0x20,0x68);


MIDL_DEFINE_GUID(IID, DIID_IotSymbolSelector,0x1E5E4427,0x9C21,0x4DD0,0x86,0x7E,0xBA,0xC5,0x1C,0x6D,0xAD,0x63);


MIDL_DEFINE_GUID(CLSID, CLSID_otSymbolSelector,0x61F0A120,0x2A95,0x442F,0xB5,0x41,0x4B,0x3C,0x30,0x9E,0xCA,0xF0);


MIDL_DEFINE_GUID(IID, DIID_IotLayerProperty,0x63E2AB56,0x8483,0x4405,0xAB,0x79,0x40,0xB8,0x1A,0xEF,0x1C,0xCC);


MIDL_DEFINE_GUID(CLSID, CLSID_otLayerProperty,0x798B7203,0x4A4B,0x48a9,0xB8,0x02,0xFB,0x4C,0x66,0x24,0x60,0x40);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



