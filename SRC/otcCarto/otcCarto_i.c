

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sun Mar 18 10:46:40 2012
 */
/* Compiler settings for .\otcCarto.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
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

MIDL_DEFINE_GUID(IID, IID_IotGeoPageLayout,0x20352E96,0xA989,0x4153,0xA4,0xA0,0x9C,0xA7,0xF9,0x1D,0xB5,0x2E);


MIDL_DEFINE_GUID(IID, LIBID_otcCarto,0x6894B3CB,0xB38F,0x4EA0,0x8B,0x01,0x30,0x41,0x47,0x9E,0x9E,0xE9);


MIDL_DEFINE_GUID(IID, IID_IotFeatureRender,0x98C98A24,0xFF62,0x4599,0xA0,0x03,0xA6,0xEC,0xE7,0xF7,0x8F,0xB8);


MIDL_DEFINE_GUID(IID, IID_IotSimpleRender,0x3BB94E62,0xA5FA,0x4D55,0x98,0xC1,0x23,0xFA,0x39,0xDA,0x23,0xCD);


MIDL_DEFINE_GUID(IID, IID_IElement,0xAEAB375F,0x2E75,0x4c81,0xA0,0xD5,0xE6,0x5E,0xDA,0xD3,0x7C,0xD4);


MIDL_DEFINE_GUID(IID, IID_IotFrameElementBase,0xD940E6E3,0x39C2,0x497f,0x89,0xA3,0x3C,0x8E,0x50,0xAF,0x3A,0x05);


MIDL_DEFINE_GUID(IID, IID_IotMarkerElement,0x93ABBC20,0x5FAB,0x4240,0x84,0x1D,0x64,0xA7,0x18,0xF4,0x0B,0xE1);


MIDL_DEFINE_GUID(IID, IID_IotPolylineElement,0xA22AA436,0xD71B,0x415D,0x8B,0xB1,0x02,0x17,0xDB,0x45,0xB7,0xE0);


MIDL_DEFINE_GUID(IID, IID_IotPolygonElement,0xCE4E1D46,0x6EDE,0x431A,0xA7,0x27,0x7B,0x67,0xAD,0x39,0x02,0x2B);


MIDL_DEFINE_GUID(IID, IID_IotRectElement,0x3E34B214,0x22B7,0x4EA8,0xA1,0xCA,0xB7,0xBF,0xF5,0x37,0x1C,0x04);


MIDL_DEFINE_GUID(IID, IID_IotCircleElement,0xD44BFFDF,0x7ECC,0x4E13,0xB0,0x44,0xDC,0x57,0xF8,0xD9,0x77,0x8E);


MIDL_DEFINE_GUID(IID, IID_IotEllipseElement,0xB7ADC815,0x48C8,0x458F,0xBA,0x23,0x6C,0xD1,0x4C,0xF4,0x8C,0x19);


MIDL_DEFINE_GUID(IID, IID_IotBezierCurveElement,0x146D442A,0x808A,0x4C9F,0xB4,0x74,0xE3,0x71,0xE3,0x9A,0x97,0x94);


MIDL_DEFINE_GUID(IID, IID_IotPictureElement,0x828574AA,0xE196,0x47B6,0xA3,0xAC,0xE4,0x26,0xD0,0xA9,0x7D,0x15);


MIDL_DEFINE_GUID(IID, IID_IotTextElement,0xED8B01AF,0x78F3,0x41FC,0x89,0xA3,0xBB,0xDA,0x30,0x8F,0x9D,0x5D);


MIDL_DEFINE_GUID(IID, IID_IotCalloutTextElement,0xB4E8FA64,0xADFD,0x498E,0x81,0xD0,0xF9,0xA5,0x21,0x59,0xB6,0x0E);


MIDL_DEFINE_GUID(IID, IID_IotPage,0x6FC775A1,0x7F40,0x4B81,0x92,0xF8,0xC2,0xB3,0xC3,0xCF,0x3D,0xAC);


MIDL_DEFINE_GUID(IID, IID_IotMapFrame,0x3175177D,0xCFA9,0x4C82,0xB7,0x89,0x5E,0xEA,0xF9,0x24,0x89,0x31);


MIDL_DEFINE_GUID(IID, IID_IotLayer,0x2B7F6D8E,0x1318,0x4f33,0xBB,0xA4,0xD3,0x95,0xAE,0x52,0xD1,0xD0);


MIDL_DEFINE_GUID(IID, IID_IotRasterLayer,0xD8E6C255,0x17AE,0x40C6,0xAE,0x56,0x04,0xEF,0x94,0x04,0x62,0xDA);


MIDL_DEFINE_GUID(IID, IID_IotFeatureLayer,0x6B2D9CBB,0xC4E9,0x42BF,0x93,0x31,0x49,0x19,0xD9,0x75,0x86,0x14);


MIDL_DEFINE_GUID(IID, IID_IotGraphicLayer,0x892F223F,0xD887,0x4263,0x9C,0xCA,0x26,0x88,0xF2,0x98,0x72,0x9B);


MIDL_DEFINE_GUID(IID, IID_IGeoMap,0x7BC33468,0xC328,0x41E6,0x8D,0x61,0x24,0xE4,0x6F,0x8B,0xBD,0x7B);


MIDL_DEFINE_GUID(IID, DIID__IGeoMapEvents,0xA56763EB,0xDE04,0x4561,0x8D,0x4E,0x1C,0xF5,0xF1,0x58,0xFA,0xEA);


MIDL_DEFINE_GUID(CLSID, CLSID_GeoMap,0x91EAA7A2,0x5758,0x4B92,0xA0,0x8F,0x87,0x7F,0x1A,0xD4,0x69,0xEF);


MIDL_DEFINE_GUID(CLSID, CLSID_otFeatureLayer,0x29FFCCDA,0x2132,0x4232,0x89,0x01,0x5D,0x4C,0x42,0xDB,0xC0,0xA7);


MIDL_DEFINE_GUID(CLSID, CLSID_otGraphicLayer,0x07C08A06,0x1859,0x4E9B,0xBA,0xA1,0x90,0xFB,0xD1,0x53,0xAD,0x4C);


MIDL_DEFINE_GUID(CLSID, CLSID_otMarkerElement,0x09ADAB83,0x8667,0x4764,0xBA,0xF1,0xEF,0x1C,0x57,0x92,0x7C,0x01);


MIDL_DEFINE_GUID(CLSID, CLSID_otPolylineElement,0x7CD1FB96,0xC0E7,0x48BF,0xAF,0xB5,0xE5,0xB4,0x68,0xA8,0xCF,0xC3);


MIDL_DEFINE_GUID(CLSID, CLSID_otPolygonElement,0x5B1C2866,0xBD99,0x4C6B,0xAB,0xE1,0xDA,0xF2,0x1B,0x8F,0xBA,0xDD);


MIDL_DEFINE_GUID(CLSID, CLSID_otRectElement,0x3892BCF3,0xEF3C,0x488D,0xB0,0x27,0x53,0xBA,0xFC,0x08,0x4C,0xF3);


MIDL_DEFINE_GUID(CLSID, CLSID_otTextElement,0x4E50DECD,0xBA9E,0x4EB0,0xB3,0x92,0x81,0x76,0x79,0xCE,0xFB,0xD4);


MIDL_DEFINE_GUID(CLSID, CLSID_otRasterLayer,0xA1B2ED9C,0x1A68,0x45FE,0xA3,0x46,0xF9,0xDF,0xF9,0xDF,0xB5,0xE2);


MIDL_DEFINE_GUID(CLSID, CLSID_otCircleElement,0x5FD0038C,0xDFC2,0x4BBF,0x8B,0x2F,0x62,0x80,0xD5,0xDB,0xAA,0xB2);


MIDL_DEFINE_GUID(CLSID, CLSID_otGeoPageLayout,0x58D5B697,0x2EA1,0x461A,0xB6,0xF3,0x2A,0x0A,0x05,0x9D,0xDB,0xFB);


MIDL_DEFINE_GUID(CLSID, CLSID_otBezierCurveElement,0xBAEFF30B,0x7A9C,0x41FC,0xBE,0x1D,0x8F,0xE2,0x08,0xFD,0xBC,0x44);


MIDL_DEFINE_GUID(CLSID, CLSID_otEllipseElement,0x7D3AD466,0x57C8,0x4991,0xB5,0x7B,0xFB,0x63,0x59,0xEB,0x1F,0xAD);


MIDL_DEFINE_GUID(CLSID, CLSID_otPictureElement,0x90D04AB6,0xFB73,0x409D,0xB3,0x8F,0x53,0x71,0xDF,0x10,0xA3,0xB7);


MIDL_DEFINE_GUID(CLSID, CLSID_otCalloutTextElement,0xBD5390E6,0xD1B4,0x4863,0x90,0x55,0xFC,0x57,0x34,0x44,0x1B,0xC3);


MIDL_DEFINE_GUID(CLSID, CLSID_otSimpleRender,0x57138786,0xBC15,0x4C16,0xAF,0xB1,0xC3,0x87,0x0A,0xE9,0xF9,0xD3);


MIDL_DEFINE_GUID(CLSID, CLSID_otPage,0x6409EB5F,0xAA78,0x4846,0x8E,0xA2,0xF8,0xC5,0x86,0x3D,0x29,0xD4);


MIDL_DEFINE_GUID(CLSID, CLSID_otMapFrame,0x2925AA1E,0xE428,0x4B3D,0xB8,0x88,0x04,0xFF,0x17,0x32,0xC3,0x42);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



