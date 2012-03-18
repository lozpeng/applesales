

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sat Mar 17 22:44:16 2012
 */
/* Compiler settings for .\otcGeometry.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */
#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "otcGeometry.h"

#define TYPE_FORMAT_STRING_SIZE   137                               
#define PROC_FORMAT_STRING_SIZE   2023                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotPointCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotPointCollection_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotTransform_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotTransform_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotGeometryCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotGeometryCollection_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotGeometry_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotGeometry_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotEnvelope_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotEnvelope_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotPoint_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotPoint_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSegment_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSegment_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSegmentCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSegmentCollection_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotLineString_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotLineString_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotLineRing_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotLineRing_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotMultiPoint_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotMultiPoint_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotMultiLineString_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotMultiLineString_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotPolygon_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotPolygon_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotMultiPolygon_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotMultiPolygon_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotGeoConvert_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotGeoConvert_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotCircle_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotCircle_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotEllipse_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotEllipse_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotBezierSpline_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotBezierSpline_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotLine_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotLine_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotBezierCurve_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotBezierCurve_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, float, double or hyper in -Oif or -Oicf.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_InteriorRingCount */


	/* Procedure get_SegmentCount */


	/* Procedure get_GeometryCount */


	/* Procedure get_PointNum */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x24 ),	/* 36 */
/* 14 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 16 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 24 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Point */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 38 */	NdrFcShort( 0x8 ),	/* 8 */
/* 40 */	NdrFcShort( 0x8 ),	/* 8 */
/* 42 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 44 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 46 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 48 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 50 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 52 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 54 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 56 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 58 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 60 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddPoint */

/* 62 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 64 */	NdrFcLong( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x5 ),	/* 5 */
/* 70 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 72 */	NdrFcShort( 0x0 ),	/* 0 */
/* 74 */	NdrFcShort( 0x8 ),	/* 8 */
/* 76 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter point */

/* 78 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 80 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 82 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 84 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 86 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 88 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure InsertPoint */

/* 90 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 92 */	NdrFcLong( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x6 ),	/* 6 */
/* 98 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 100 */	NdrFcShort( 0x8 ),	/* 8 */
/* 102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 104 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 106 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 108 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter point */

/* 112 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 114 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 116 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 118 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 120 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 122 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReplacePoint */

/* 124 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 126 */	NdrFcLong( 0x0 ),	/* 0 */
/* 130 */	NdrFcShort( 0x7 ),	/* 7 */
/* 132 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 134 */	NdrFcShort( 0x8 ),	/* 8 */
/* 136 */	NdrFcShort( 0x8 ),	/* 8 */
/* 138 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 140 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 142 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter point */

/* 146 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 148 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 150 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 152 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 154 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 156 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RemovePoint */

/* 158 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 160 */	NdrFcLong( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 166 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 170 */	NdrFcShort( 0x8 ),	/* 8 */
/* 172 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter index */

/* 174 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 176 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 180 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 182 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 184 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Move */

/* 186 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 188 */	NdrFcLong( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x3 ),	/* 3 */
/* 194 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 196 */	NdrFcShort( 0x20 ),	/* 32 */
/* 198 */	NdrFcShort( 0x8 ),	/* 8 */
/* 200 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter dx */

/* 202 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 204 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 206 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter dy */

/* 208 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 210 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 212 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 214 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 216 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 218 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Scale */

/* 220 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 222 */	NdrFcLong( 0x0 ),	/* 0 */
/* 226 */	NdrFcShort( 0x4 ),	/* 4 */
/* 228 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 230 */	NdrFcShort( 0x20 ),	/* 32 */
/* 232 */	NdrFcShort( 0x8 ),	/* 8 */
/* 234 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter Origin */

/* 236 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 238 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 240 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Parameter dx */

/* 242 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 244 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 246 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter dy */

/* 248 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 250 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 252 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 254 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 256 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 258 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Rotate */

/* 260 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 266 */	NdrFcShort( 0x5 ),	/* 5 */
/* 268 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 270 */	NdrFcShort( 0x10 ),	/* 16 */
/* 272 */	NdrFcShort( 0x8 ),	/* 8 */
/* 274 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter Origin */

/* 276 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 278 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 280 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Parameter angle */

/* 282 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 284 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 286 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 288 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 290 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 292 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetGeometry */

/* 294 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 296 */	NdrFcLong( 0x0 ),	/* 0 */
/* 300 */	NdrFcShort( 0x4 ),	/* 4 */
/* 302 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 306 */	NdrFcShort( 0x8 ),	/* 8 */
/* 308 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 310 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 312 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 314 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter retGeometry */

/* 316 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 318 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 320 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 322 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 324 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddGeometry */

/* 328 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 330 */	NdrFcLong( 0x0 ),	/* 0 */
/* 334 */	NdrFcShort( 0x5 ),	/* 5 */
/* 336 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 342 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter geometry */

/* 344 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 346 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 348 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 350 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 352 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 354 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_GeometryType */

/* 356 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 358 */	NdrFcLong( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x3 ),	/* 3 */
/* 364 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 368 */	NdrFcShort( 0x22 ),	/* 34 */
/* 370 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 372 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 374 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 376 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 378 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 380 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 382 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PointCount */

/* 384 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 386 */	NdrFcLong( 0x0 ),	/* 0 */
/* 390 */	NdrFcShort( 0x4 ),	/* 4 */
/* 392 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 396 */	NdrFcShort( 0x24 ),	/* 36 */
/* 398 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 400 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 402 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 404 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 406 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 408 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 410 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetEnvelope */

/* 412 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 414 */	NdrFcLong( 0x0 ),	/* 0 */
/* 418 */	NdrFcShort( 0x5 ),	/* 5 */
/* 420 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 424 */	NdrFcShort( 0x8 ),	/* 8 */
/* 426 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter envelope */

/* 428 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 430 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 432 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Return value */

/* 434 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 436 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 438 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HasZ */

/* 440 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 442 */	NdrFcLong( 0x0 ),	/* 0 */
/* 446 */	NdrFcShort( 0x6 ),	/* 6 */
/* 448 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 452 */	NdrFcShort( 0x22 ),	/* 34 */
/* 454 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 456 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 458 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 460 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 462 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 464 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 466 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_HasZ */

/* 468 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 470 */	NdrFcLong( 0x0 ),	/* 0 */
/* 474 */	NdrFcShort( 0x7 ),	/* 7 */
/* 476 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 478 */	NdrFcShort( 0x6 ),	/* 6 */
/* 480 */	NdrFcShort( 0x8 ),	/* 8 */
/* 482 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 484 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 486 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 488 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 490 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 492 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 494 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HasM */

/* 496 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 498 */	NdrFcLong( 0x0 ),	/* 0 */
/* 502 */	NdrFcShort( 0x8 ),	/* 8 */
/* 504 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 508 */	NdrFcShort( 0x22 ),	/* 34 */
/* 510 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 512 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 514 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 516 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 518 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 520 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_HasM */

/* 524 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 526 */	NdrFcLong( 0x0 ),	/* 0 */
/* 530 */	NdrFcShort( 0x9 ),	/* 9 */
/* 532 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 534 */	NdrFcShort( 0x6 ),	/* 6 */
/* 536 */	NdrFcShort( 0x8 ),	/* 8 */
/* 538 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 540 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 542 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 544 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 546 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 548 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 550 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsEmpty */

/* 552 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 554 */	NdrFcLong( 0x0 ),	/* 0 */
/* 558 */	NdrFcShort( 0xa ),	/* 10 */
/* 560 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x22 ),	/* 34 */
/* 566 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 568 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 570 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 572 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 574 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 576 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 578 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetEmpty */

/* 580 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 582 */	NdrFcLong( 0x0 ),	/* 0 */
/* 586 */	NdrFcShort( 0xb ),	/* 11 */
/* 588 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x8 ),	/* 8 */
/* 594 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 596 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 598 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 600 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */

/* 602 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 604 */	NdrFcLong( 0x0 ),	/* 0 */
/* 608 */	NdrFcShort( 0xc ),	/* 12 */
/* 610 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 614 */	NdrFcShort( 0x8 ),	/* 8 */
/* 616 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter geometry */

/* 618 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 620 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 622 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 624 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 626 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 628 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsValid */

/* 630 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 632 */	NdrFcLong( 0x0 ),	/* 0 */
/* 636 */	NdrFcShort( 0xd ),	/* 13 */
/* 638 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 642 */	NdrFcShort( 0x22 ),	/* 34 */
/* 644 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 646 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 648 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 650 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 652 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 654 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 656 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Disjoint */

/* 658 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 660 */	NdrFcLong( 0x0 ),	/* 0 */
/* 664 */	NdrFcShort( 0xe ),	/* 14 */
/* 666 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x22 ),	/* 34 */
/* 672 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 674 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 676 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 678 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bRet */

/* 680 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 682 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 684 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 686 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 688 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 690 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Touches */

/* 692 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 694 */	NdrFcLong( 0x0 ),	/* 0 */
/* 698 */	NdrFcShort( 0xf ),	/* 15 */
/* 700 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x22 ),	/* 34 */
/* 706 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 708 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 710 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 712 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bRet */

/* 714 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 716 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 718 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 720 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 722 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 724 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Intersects */

/* 726 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 728 */	NdrFcLong( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x10 ),	/* 16 */
/* 734 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 736 */	NdrFcShort( 0x0 ),	/* 0 */
/* 738 */	NdrFcShort( 0x22 ),	/* 34 */
/* 740 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 742 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 744 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 746 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bRet */

/* 748 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 750 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 752 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 754 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 756 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Crosses */

/* 760 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 762 */	NdrFcLong( 0x0 ),	/* 0 */
/* 766 */	NdrFcShort( 0x11 ),	/* 17 */
/* 768 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 772 */	NdrFcShort( 0x22 ),	/* 34 */
/* 774 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 776 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 778 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 780 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bRet */

/* 782 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 784 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 786 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 788 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 790 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 792 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Within */

/* 794 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 796 */	NdrFcLong( 0x0 ),	/* 0 */
/* 800 */	NdrFcShort( 0x12 ),	/* 18 */
/* 802 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 806 */	NdrFcShort( 0x22 ),	/* 34 */
/* 808 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 810 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 812 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 814 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bRet */

/* 816 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 818 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 820 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 822 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 824 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 826 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Overlaps */

/* 828 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 830 */	NdrFcLong( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x13 ),	/* 19 */
/* 836 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x22 ),	/* 34 */
/* 842 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 844 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 846 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 848 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bRet */

/* 850 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 852 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 854 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 856 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 858 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 860 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Equals */

/* 862 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 864 */	NdrFcLong( 0x0 ),	/* 0 */
/* 868 */	NdrFcShort( 0x14 ),	/* 20 */
/* 870 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 874 */	NdrFcShort( 0x22 ),	/* 34 */
/* 876 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 878 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 880 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 882 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bRet */

/* 884 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 886 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 888 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 890 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 892 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 894 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Covers */

/* 896 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 898 */	NdrFcLong( 0x0 ),	/* 0 */
/* 902 */	NdrFcShort( 0x15 ),	/* 21 */
/* 904 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 906 */	NdrFcShort( 0x0 ),	/* 0 */
/* 908 */	NdrFcShort( 0x22 ),	/* 34 */
/* 910 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 912 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 914 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 916 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bRet */

/* 918 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 920 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 922 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 924 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 926 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 928 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ConvexHull */

/* 930 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 932 */	NdrFcLong( 0x0 ),	/* 0 */
/* 936 */	NdrFcShort( 0x16 ),	/* 22 */
/* 938 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 940 */	NdrFcShort( 0x0 ),	/* 0 */
/* 942 */	NdrFcShort( 0x8 ),	/* 8 */
/* 944 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter retGeometry */

/* 946 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 948 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 950 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 952 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 954 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 956 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Buffer */

/* 958 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 960 */	NdrFcLong( 0x0 ),	/* 0 */
/* 964 */	NdrFcShort( 0x17 ),	/* 23 */
/* 966 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 968 */	NdrFcShort( 0x10 ),	/* 16 */
/* 970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 972 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter distance */

/* 974 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 976 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 978 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter retGeometry */

/* 980 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 982 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 984 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 986 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 988 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 990 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Intersection */

/* 992 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 994 */	NdrFcLong( 0x0 ),	/* 0 */
/* 998 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1000 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1006 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 1008 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1010 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1012 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter retGeometry */

/* 1014 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1016 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1018 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 1020 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1022 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1024 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Union */

/* 1026 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1028 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1032 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1034 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1038 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1040 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 1042 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1044 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1046 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter retGeometry */

/* 1048 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1050 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1052 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 1054 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1056 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1058 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Difference */

/* 1060 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1062 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1066 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1068 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1070 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1072 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1074 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 1076 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1078 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1080 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter retGeometry */

/* 1082 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1084 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1086 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 1088 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1090 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1092 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SymDifference */

/* 1094 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1096 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1100 */	NdrFcShort( 0x1b ),	/* 27 */
/* 1102 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1106 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1108 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 1110 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1112 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1114 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter retGeometry */

/* 1116 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1118 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1120 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 1122 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1124 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1126 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Area */


	/* Procedure get_Length */


	/* Procedure get_X */


	/* Procedure get_MinX */

/* 1128 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1130 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1136 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1140 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1142 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 1144 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1146 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1148 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 1150 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1152 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1154 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_X */


	/* Procedure put_MinX */

/* 1156 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1158 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1162 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1164 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1166 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1170 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 1172 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1174 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1176 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1180 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Radius */


	/* Procedure get_Y */


	/* Procedure get_MinY */

/* 1184 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1190 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1192 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1196 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1198 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 1200 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1202 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1204 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1206 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1208 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1210 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Radius */


	/* Procedure put_Y */


	/* Procedure put_MinY */

/* 1212 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1214 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1218 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1220 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1222 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1224 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1226 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */

/* 1228 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1230 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1232 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1234 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1236 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Z */


	/* Procedure get_MaxX */

/* 1240 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1242 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1246 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1248 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1252 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1254 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1256 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1258 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1260 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1262 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1264 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1266 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Z */


	/* Procedure put_MaxX */

/* 1268 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1270 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1274 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1276 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1278 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1282 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 1284 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1286 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1288 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1290 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1292 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_M */


	/* Procedure get_MaxY */

/* 1296 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1298 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1302 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1304 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1308 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1310 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1312 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1314 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1316 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1318 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1320 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1322 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_M */


	/* Procedure put_MaxY */

/* 1324 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1326 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1330 */	NdrFcShort( 0xa ),	/* 10 */
/* 1332 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1334 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1336 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1338 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 1340 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1342 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1344 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1346 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1348 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1350 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CenterPoint */


	/* Procedure get_CenterPoint */


	/* Procedure get_FromPoint */

/* 1352 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1354 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1358 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1360 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1364 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1366 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 1368 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1370 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1372 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1374 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1376 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CenterPoint */


	/* Procedure put_CenterPoint */


	/* Procedure put_FromPoint */

/* 1380 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1382 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1386 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1388 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1394 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */

/* 1396 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1398 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1400 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1402 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1404 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1406 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StartPoint */


	/* Procedure get_ToPoint */

/* 1408 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1410 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1414 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1416 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1420 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1422 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1424 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1426 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1428 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */


	/* Return value */

/* 1430 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1432 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1434 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_StartPoint */


	/* Procedure put_ToPoint */

/* 1436 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1438 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1442 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1444 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1448 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1450 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 1452 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1454 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1456 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */


	/* Return value */

/* 1458 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1460 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1462 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddSegment */

/* 1464 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1466 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1470 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1472 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1476 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1478 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter segment */

/* 1480 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1482 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1484 */	NdrFcShort( 0x54 ),	/* Type Offset=84 */

	/* Return value */

/* 1486 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1488 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1490 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSegment */

/* 1492 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1494 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1498 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1500 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1502 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1504 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1506 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 1508 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1510 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1512 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ret */

/* 1514 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1516 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1518 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Return value */

/* 1520 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1522 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1524 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsClosed */

/* 1526 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1528 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1532 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1534 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1538 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1540 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bRet */

/* 1542 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1544 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1546 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1548 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1550 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1552 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Area */


	/* Procedure get_Length */

/* 1554 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1556 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1560 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1562 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1566 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1568 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1570 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1572 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1574 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1576 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1578 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_FirstCtrlPoint */


	/* Procedure get_EndPoint */

/* 1582 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1588 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1590 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1594 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1596 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1598 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1600 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1602 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */


	/* Return value */

/* 1604 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1606 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1608 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_FirstCtrlPoint */


	/* Procedure put_EndPoint */

/* 1610 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1612 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1616 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1618 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1620 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1622 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1624 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 1626 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1628 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1630 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */


	/* Return value */

/* 1632 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1634 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1636 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ExteriorRing */

/* 1638 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1640 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1644 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1646 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1650 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1652 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1654 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1656 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1658 */	NdrFcShort( 0x6a ),	/* Type Offset=106 */

	/* Return value */

/* 1660 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1662 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1664 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ExteriorRing */

/* 1666 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1668 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1672 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1674 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1678 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1680 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1682 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1684 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1686 */	NdrFcShort( 0x6e ),	/* Type Offset=110 */

	/* Return value */

/* 1688 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1690 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_InteriorRing */

/* 1694 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1700 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1702 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1704 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1706 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1708 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 1710 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1712 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1714 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1716 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1718 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1720 */	NdrFcShort( 0x6a ),	/* Type Offset=106 */

	/* Return value */

/* 1722 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1724 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1726 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_InteriorRing */

/* 1728 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1730 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1734 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1736 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1738 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1740 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1742 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 1744 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter newVal */

/* 1750 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1752 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1754 */	NdrFcShort( 0x6e ),	/* Type Offset=110 */

	/* Return value */

/* 1756 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1758 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1760 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddInteriorRing */

/* 1762 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1764 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1768 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1770 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1772 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1774 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1776 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter ring */

/* 1778 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1780 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1782 */	NdrFcShort( 0x6e ),	/* Type Offset=110 */

	/* Return value */

/* 1784 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1786 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1788 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ConvertGeo */

/* 1790 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1792 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1796 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1798 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1800 */	NdrFcShort( 0xe ),	/* 14 */
/* 1802 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1804 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x4,		/* 4 */

	/* Parameter p */

/* 1806 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1808 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1810 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bown */

/* 1812 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1814 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1816 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter retGeo */

/* 1818 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1820 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1822 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 1824 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1826 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1828 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ConvertIGeo */

/* 1830 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1832 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1836 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1838 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1842 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1844 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter geometry */

/* 1846 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1848 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1850 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter ret */

/* 1852 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1854 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1856 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1858 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1860 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1862 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetAxes */

/* 1864 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1866 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1870 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1872 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1874 */	NdrFcShort( 0x48 ),	/* 72 */
/* 1876 */	NdrFcShort( 0x50 ),	/* 80 */
/* 1878 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter semiMajor */

/* 1880 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 1882 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1884 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter semiMinor */

/* 1886 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 1888 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1890 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1892 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1894 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1896 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetAxes */

/* 1898 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1900 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1904 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1906 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1908 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1910 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1912 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter semiMajor */

/* 1914 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1916 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1918 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter semiMinor */

/* 1920 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1922 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1924 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1926 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1928 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1930 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Create */

/* 1932 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1934 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1938 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1940 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1942 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1944 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1946 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter numPoints */

/* 1948 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1950 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1952 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter points */

/* 1954 */	NdrFcShort( 0x200b ),	/* Flags:  must size, must free, in, srv alloc size=8 */
/* 1956 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1958 */	NdrFcShort( 0x84 ),	/* Type Offset=132 */

	/* Return value */

/* 1960 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1962 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1964 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SecondCtrlPoint */

/* 1966 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1968 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1972 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1974 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1978 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1980 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1982 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1984 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1986 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 1988 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1990 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1992 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SecondCtrlPoint */

/* 1994 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1996 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2000 */	NdrFcShort( 0xa ),	/* 10 */
/* 2002 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2004 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2006 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2008 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 2010 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2012 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2014 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 2016 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2018 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2020 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 12 */	NdrFcLong( 0xe345d296 ),	/* -481963370 */
/* 16 */	NdrFcShort( 0x34c1 ),	/* 13505 */
/* 18 */	NdrFcShort( 0x42ea ),	/* 17130 */
/* 20 */	0x95,		/* 149 */
			0xdc,		/* 220 */
/* 22 */	0x84,		/* 132 */
			0x41,		/* 65 */
/* 24 */	0xfe,		/* 254 */
			0x42,		/* 66 */
/* 26 */	0xf9,		/* 249 */
			0xcb,		/* 203 */
/* 28 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 30 */	NdrFcShort( 0x2 ),	/* Offset= 2 (32) */
/* 32 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 34 */	NdrFcLong( 0x31e731d ),	/* 52327197 */
/* 38 */	NdrFcShort( 0xc0a9 ),	/* -16215 */
/* 40 */	NdrFcShort( 0x44b0 ),	/* 17584 */
/* 42 */	0xad,		/* 173 */
			0xc6,		/* 198 */
/* 44 */	0xa2,		/* 162 */
			0x77,		/* 119 */
/* 46 */	0x9b,		/* 155 */
			0x1d,		/* 29 */
/* 48 */	0x9d,		/* 157 */
			0x60,		/* 96 */
/* 50 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 52 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 54 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 56 */	NdrFcShort( 0x2 ),	/* Offset= 2 (58) */
/* 58 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 60 */	NdrFcLong( 0xd3d17ed8 ),	/* -741245224 */
/* 64 */	NdrFcShort( 0x8141 ),	/* -32447 */
/* 66 */	NdrFcShort( 0x4b37 ),	/* 19255 */
/* 68 */	0x93,		/* 147 */
			0x1b,		/* 27 */
/* 70 */	0xab,		/* 171 */
			0x4d,		/* 77 */
/* 72 */	0x2a,		/* 42 */
			0xa8,		/* 168 */
/* 74 */	0xad,		/* 173 */
			0x8a,		/* 138 */
/* 76 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 78 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 80 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 82 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 84 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 86 */	NdrFcLong( 0x42899086 ),	/* 1116311686 */
/* 90 */	NdrFcShort( 0x1be7 ),	/* 7143 */
/* 92 */	NdrFcShort( 0x4870 ),	/* 18544 */
/* 94 */	0x84,		/* 132 */
			0x85,		/* 133 */
/* 96 */	0x6d,		/* 109 */
			0xdf,		/* 223 */
/* 98 */	0xc1,		/* 193 */
			0x14,		/* 20 */
/* 100 */	0xd6,		/* 214 */
			0xa7,		/* 167 */
/* 102 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 104 */	NdrFcShort( 0xffec ),	/* Offset= -20 (84) */
/* 106 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 108 */	NdrFcShort( 0x2 ),	/* Offset= 2 (110) */
/* 110 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 112 */	NdrFcLong( 0x37aaecc0 ),	/* 933948608 */
/* 116 */	NdrFcShort( 0x6af7 ),	/* 27383 */
/* 118 */	NdrFcShort( 0x45a9 ),	/* 17833 */
/* 120 */	0x82,		/* 130 */
			0x22,		/* 34 */
/* 122 */	0x60,		/* 96 */
			0xe8,		/* 232 */
/* 124 */	0x40,		/* 64 */
			0x4f,		/* 79 */
/* 126 */	0x45,		/* 69 */
			0xd4,		/* 212 */
/* 128 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 130 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 132 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 134 */	NdrFcShort( 0xff84 ),	/* Offset= -124 (10) */

			0x0
        }
    };


/* Standard interface: __MIDL_itf_otcGeometry_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IotPointCollection, ver. 0.0,
   GUID={0x67644AA5,0x0A8D,0x4ff2,{0xB2,0xE4,0x51,0x29,0x0F,0xB1,0x39,0xAA}} */

#pragma code_seg(".orpc")
static const unsigned short IotPointCollection_FormatStringOffsetTable[] =
    {
    0,
    28,
    62,
    90,
    124,
    158
    };

static const MIDL_STUBLESS_PROXY_INFO IotPointCollection_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotPointCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotPointCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotPointCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IotPointCollectionProxyVtbl = 
{
    &IotPointCollection_ProxyInfo,
    &IID_IotPointCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotPointCollection::get_PointNum */ ,
    (void *) (INT_PTR) -1 /* IotPointCollection::get_Point */ ,
    (void *) (INT_PTR) -1 /* IotPointCollection::AddPoint */ ,
    (void *) (INT_PTR) -1 /* IotPointCollection::InsertPoint */ ,
    (void *) (INT_PTR) -1 /* IotPointCollection::ReplacePoint */ ,
    (void *) (INT_PTR) -1 /* IotPointCollection::RemovePoint */
};

const CInterfaceStubVtbl _IotPointCollectionStubVtbl =
{
    &IID_IotPointCollection,
    &IotPointCollection_ServerInfo,
    9,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotTransform, ver. 0.0,
   GUID={0xB227DF87,0x4B92,0x43f9,{0x96,0x6E,0x9A,0x4B,0xD6,0x20,0xDB,0x8C}} */

#pragma code_seg(".orpc")
static const unsigned short IotTransform_FormatStringOffsetTable[] =
    {
    186,
    220,
    260
    };

static const MIDL_STUBLESS_PROXY_INFO IotTransform_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotTransform_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotTransform_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotTransform_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IotTransformProxyVtbl = 
{
    &IotTransform_ProxyInfo,
    &IID_IotTransform,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotTransform::Move */ ,
    (void *) (INT_PTR) -1 /* IotTransform::Scale */ ,
    (void *) (INT_PTR) -1 /* IotTransform::Rotate */
};

const CInterfaceStubVtbl _IotTransformStubVtbl =
{
    &IID_IotTransform,
    &IotTransform_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotGeometryCollection, ver. 0.0,
   GUID={0xF89C4CC5,0x548A,0x478c,{0xB0,0x94,0xBE,0x80,0xFC,0xB1,0xC5,0xCF}} */

#pragma code_seg(".orpc")
static const unsigned short IotGeometryCollection_FormatStringOffsetTable[] =
    {
    0,
    294,
    328
    };

static const MIDL_STUBLESS_PROXY_INFO IotGeometryCollection_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotGeometryCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotGeometryCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotGeometryCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IotGeometryCollectionProxyVtbl = 
{
    &IotGeometryCollection_ProxyInfo,
    &IID_IotGeometryCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotGeometryCollection::get_GeometryCount */ ,
    (void *) (INT_PTR) -1 /* IotGeometryCollection::GetGeometry */ ,
    (void *) (INT_PTR) -1 /* IotGeometryCollection::AddGeometry */
};

const CInterfaceStubVtbl _IotGeometryCollectionStubVtbl =
{
    &IID_IotGeometryCollection,
    &IotGeometryCollection_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotGeometry, ver. 0.0,
   GUID={0x031E731D,0xC0A9,0x44b0,{0xAD,0xC6,0xA2,0x77,0x9B,0x1D,0x9D,0x60}} */

#pragma code_seg(".orpc")
static const unsigned short IotGeometry_FormatStringOffsetTable[] =
    {
    356,
    384,
    412,
    440,
    468,
    496,
    524,
    552,
    580,
    602,
    630,
    658,
    692,
    726,
    760,
    794,
    828,
    862,
    896,
    930,
    958,
    992,
    1026,
    1060,
    1094
    };

static const MIDL_STUBLESS_PROXY_INFO IotGeometry_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotGeometry_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotGeometry_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotGeometry_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(28) _IotGeometryProxyVtbl = 
{
    &IotGeometry_ProxyInfo,
    &IID_IotGeometry,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotGeometry::get_GeometryType */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::get_PointCount */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::GetEnvelope */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::get_HasZ */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::put_HasZ */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::get_HasM */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::put_HasM */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::get_IsValid */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Disjoint */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Touches */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Intersects */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Crosses */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Within */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Overlaps */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Equals */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Covers */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::ConvexHull */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Buffer */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Intersection */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Union */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::Difference */ ,
    (void *) (INT_PTR) -1 /* IotGeometry::SymDifference */
};

const CInterfaceStubVtbl _IotGeometryStubVtbl =
{
    &IID_IotGeometry,
    &IotGeometry_ServerInfo,
    28,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotEnvelope, ver. 0.0,
   GUID={0xD3D17ED8,0x8141,0x4B37,{0x93,0x1B,0xAB,0x4D,0x2A,0xA8,0xAD,0x8A}} */

#pragma code_seg(".orpc")
static const unsigned short IotEnvelope_FormatStringOffsetTable[] =
    {
    1128,
    1156,
    1184,
    1212,
    1240,
    1268,
    1296,
    1324
    };

static const MIDL_STUBLESS_PROXY_INFO IotEnvelope_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotEnvelope_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotEnvelope_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotEnvelope_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IotEnvelopeProxyVtbl = 
{
    &IotEnvelope_ProxyInfo,
    &IID_IotEnvelope,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotEnvelope::get_MinX */ ,
    (void *) (INT_PTR) -1 /* IotEnvelope::put_MinX */ ,
    (void *) (INT_PTR) -1 /* IotEnvelope::get_MinY */ ,
    (void *) (INT_PTR) -1 /* IotEnvelope::put_MinY */ ,
    (void *) (INT_PTR) -1 /* IotEnvelope::get_MaxX */ ,
    (void *) (INT_PTR) -1 /* IotEnvelope::put_MaxX */ ,
    (void *) (INT_PTR) -1 /* IotEnvelope::get_MaxY */ ,
    (void *) (INT_PTR) -1 /* IotEnvelope::put_MaxY */
};

const CInterfaceStubVtbl _IotEnvelopeStubVtbl =
{
    &IID_IotEnvelope,
    &IotEnvelope_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotPoint, ver. 0.0,
   GUID={0xE345D296,0x34C1,0x42EA,{0x95,0xDC,0x84,0x41,0xFE,0x42,0xF9,0xCB}} */

#pragma code_seg(".orpc")
static const unsigned short IotPoint_FormatStringOffsetTable[] =
    {
    1128,
    1156,
    1184,
    1212,
    1240,
    1268,
    1296,
    1324
    };

static const MIDL_STUBLESS_PROXY_INFO IotPoint_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotPoint_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotPoint_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotPoint_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IotPointProxyVtbl = 
{
    &IotPoint_ProxyInfo,
    &IID_IotPoint,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotPoint::get_X */ ,
    (void *) (INT_PTR) -1 /* IotPoint::put_X */ ,
    (void *) (INT_PTR) -1 /* IotPoint::get_Y */ ,
    (void *) (INT_PTR) -1 /* IotPoint::put_Y */ ,
    (void *) (INT_PTR) -1 /* IotPoint::get_Z */ ,
    (void *) (INT_PTR) -1 /* IotPoint::put_Z */ ,
    (void *) (INT_PTR) -1 /* IotPoint::get_M */ ,
    (void *) (INT_PTR) -1 /* IotPoint::put_M */
};

const CInterfaceStubVtbl _IotPointStubVtbl =
{
    &IID_IotPoint,
    &IotPoint_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSegment, ver. 0.0,
   GUID={0x42899086,0x1BE7,0x4870,{0x84,0x85,0x6D,0xDF,0xC1,0x14,0xD6,0xA7}} */

#pragma code_seg(".orpc")
static const unsigned short IotSegment_FormatStringOffsetTable[] =
    {
    1352,
    1380,
    1408,
    1436
    };

static const MIDL_STUBLESS_PROXY_INFO IotSegment_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSegment_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSegment_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSegment_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IotSegmentProxyVtbl = 
{
    &IotSegment_ProxyInfo,
    &IID_IotSegment,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSegment::get_FromPoint */ ,
    (void *) (INT_PTR) -1 /* IotSegment::put_FromPoint */ ,
    (void *) (INT_PTR) -1 /* IotSegment::get_ToPoint */ ,
    (void *) (INT_PTR) -1 /* IotSegment::put_ToPoint */
};

const CInterfaceStubVtbl _IotSegmentStubVtbl =
{
    &IID_IotSegment,
    &IotSegment_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSegmentCollection, ver. 0.0,
   GUID={0xC3DF7859,0x3624,0x4846,{0x86,0x1F,0x01,0x5D,0xBC,0x0B,0x98,0xF9}} */

#pragma code_seg(".orpc")
static const unsigned short IotSegmentCollection_FormatStringOffsetTable[] =
    {
    0,
    1464,
    1492
    };

static const MIDL_STUBLESS_PROXY_INFO IotSegmentCollection_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSegmentCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSegmentCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSegmentCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IotSegmentCollectionProxyVtbl = 
{
    &IotSegmentCollection_ProxyInfo,
    &IID_IotSegmentCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSegmentCollection::get_SegmentCount */ ,
    (void *) (INT_PTR) -1 /* IotSegmentCollection::AddSegment */ ,
    (void *) (INT_PTR) -1 /* IotSegmentCollection::GetSegment */
};

const CInterfaceStubVtbl _IotSegmentCollectionStubVtbl =
{
    &IID_IotSegmentCollection,
    &IotSegmentCollection_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotLineString, ver. 0.0,
   GUID={0xCF2D8ABA,0x5D6A,0x4732,{0xB8,0x1F,0xDB,0xCA,0x0C,0x5D,0x25,0xAC}} */

#pragma code_seg(".orpc")
static const unsigned short IotLineString_FormatStringOffsetTable[] =
    {
    1526,
    1554,
    1408,
    1436,
    1582,
    1610
    };

static const MIDL_STUBLESS_PROXY_INFO IotLineString_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotLineString_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotLineString_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotLineString_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IotLineStringProxyVtbl = 
{
    &IotLineString_ProxyInfo,
    &IID_IotLineString,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotLineString::IsClosed */ ,
    (void *) (INT_PTR) -1 /* IotLineString::get_Length */ ,
    (void *) (INT_PTR) -1 /* IotLineString::get_StartPoint */ ,
    (void *) (INT_PTR) -1 /* IotLineString::put_StartPoint */ ,
    (void *) (INT_PTR) -1 /* IotLineString::get_EndPoint */ ,
    (void *) (INT_PTR) -1 /* IotLineString::put_EndPoint */
};

const CInterfaceStubVtbl _IotLineStringStubVtbl =
{
    &IID_IotLineString,
    &IotLineString_ServerInfo,
    9,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotLineRing, ver. 0.0,
   GUID={0x37AAECC0,0x6AF7,0x45A9,{0x82,0x22,0x60,0xE8,0x40,0x4F,0x45,0xD4}} */

#pragma code_seg(".orpc")
static const unsigned short IotLineRing_FormatStringOffsetTable[] =
    {
    1526,
    1554,
    1408,
    1436,
    1582,
    1610,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotLineRing_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotLineRing_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotLineRing_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotLineRing_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IotLineRingProxyVtbl = 
{
    0,
    &IID_IotLineRing,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotLineString::IsClosed */ ,
    0 /* forced delegation IotLineString::get_Length */ ,
    0 /* forced delegation IotLineString::get_StartPoint */ ,
    0 /* forced delegation IotLineString::put_StartPoint */ ,
    0 /* forced delegation IotLineString::get_EndPoint */ ,
    0 /* forced delegation IotLineString::put_EndPoint */
};


static const PRPC_STUB_FUNCTION IotLineRing_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotLineRingStubVtbl =
{
    &IID_IotLineRing,
    &IotLineRing_ServerInfo,
    9,
    &IotLineRing_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotMultiPoint, ver. 0.0,
   GUID={0x8928D749,0x81A2,0x48A1,{0x80,0x71,0x5D,0x47,0x39,0x98,0x8A,0x1B}} */

#pragma code_seg(".orpc")
static const unsigned short IotMultiPoint_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotMultiPoint_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotMultiPoint_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotMultiPoint_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotMultiPoint_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(3) _IotMultiPointProxyVtbl = 
{
    0,
    &IID_IotMultiPoint,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IotMultiPointStubVtbl =
{
    &IID_IotMultiPoint,
    &IotMultiPoint_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotMultiLineString, ver. 0.0,
   GUID={0x4665385A,0x34D0,0x4E4D,{0x86,0x26,0x1F,0x01,0x8A,0x99,0x54,0x8B}} */

#pragma code_seg(".orpc")
static const unsigned short IotMultiLineString_FormatStringOffsetTable[] =
    {
    1128
    };

static const MIDL_STUBLESS_PROXY_INFO IotMultiLineString_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotMultiLineString_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotMultiLineString_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotMultiLineString_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IotMultiLineStringProxyVtbl = 
{
    &IotMultiLineString_ProxyInfo,
    &IID_IotMultiLineString,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotMultiLineString::get_Length */
};

const CInterfaceStubVtbl _IotMultiLineStringStubVtbl =
{
    &IID_IotMultiLineString,
    &IotMultiLineString_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotPolygon, ver. 0.0,
   GUID={0xD3A18F5B,0x90F8,0x45E4,{0x8E,0xF7,0x2E,0xC9,0x48,0xDC,0xA7,0x4F}} */

#pragma code_seg(".orpc")
static const unsigned short IotPolygon_FormatStringOffsetTable[] =
    {
    0,
    1554,
    1638,
    1666,
    1694,
    1728,
    1762
    };

static const MIDL_STUBLESS_PROXY_INFO IotPolygon_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotPolygon_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotPolygon_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotPolygon_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IotPolygonProxyVtbl = 
{
    &IotPolygon_ProxyInfo,
    &IID_IotPolygon,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotPolygon::get_InteriorRingCount */ ,
    (void *) (INT_PTR) -1 /* IotPolygon::get_Area */ ,
    (void *) (INT_PTR) -1 /* IotPolygon::get_ExteriorRing */ ,
    (void *) (INT_PTR) -1 /* IotPolygon::put_ExteriorRing */ ,
    (void *) (INT_PTR) -1 /* IotPolygon::get_InteriorRing */ ,
    (void *) (INT_PTR) -1 /* IotPolygon::put_InteriorRing */ ,
    (void *) (INT_PTR) -1 /* IotPolygon::AddInteriorRing */
};

const CInterfaceStubVtbl _IotPolygonStubVtbl =
{
    &IID_IotPolygon,
    &IotPolygon_ServerInfo,
    10,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotMultiPolygon, ver. 0.0,
   GUID={0xB57958AB,0xD268,0x44BA,{0x8E,0x9B,0x2B,0xEE,0x1C,0x8C,0x2C,0xD9}} */

#pragma code_seg(".orpc")
static const unsigned short IotMultiPolygon_FormatStringOffsetTable[] =
    {
    1128
    };

static const MIDL_STUBLESS_PROXY_INFO IotMultiPolygon_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotMultiPolygon_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotMultiPolygon_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotMultiPolygon_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IotMultiPolygonProxyVtbl = 
{
    &IotMultiPolygon_ProxyInfo,
    &IID_IotMultiPolygon,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotMultiPolygon::get_Area */
};

const CInterfaceStubVtbl _IotMultiPolygonStubVtbl =
{
    &IID_IotMultiPolygon,
    &IotMultiPolygon_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotGeoConvert, ver. 0.0,
   GUID={0x3FD948E8,0x3CBF,0x448A,{0x85,0xF7,0xA1,0xAF,0xAF,0x20,0x4C,0xB5}} */

#pragma code_seg(".orpc")
static const unsigned short IotGeoConvert_FormatStringOffsetTable[] =
    {
    1790,
    1830
    };

static const MIDL_STUBLESS_PROXY_INFO IotGeoConvert_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotGeoConvert_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotGeoConvert_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotGeoConvert_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IotGeoConvertProxyVtbl = 
{
    &IotGeoConvert_ProxyInfo,
    &IID_IotGeoConvert,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotGeoConvert::ConvertGeo */ ,
    (void *) (INT_PTR) -1 /* IotGeoConvert::ConvertIGeo */
};

const CInterfaceStubVtbl _IotGeoConvertStubVtbl =
{
    &IID_IotGeoConvert,
    &IotGeoConvert_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotCircle, ver. 0.0,
   GUID={0x216DAD59,0x1C93,0x45B9,{0x8E,0x37,0x4F,0x0B,0x04,0x9A,0xD3,0xAB}} */

#pragma code_seg(".orpc")
static const unsigned short IotCircle_FormatStringOffsetTable[] =
    {
    1352,
    1380,
    1184,
    1212
    };

static const MIDL_STUBLESS_PROXY_INFO IotCircle_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotCircle_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotCircle_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotCircle_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IotCircleProxyVtbl = 
{
    &IotCircle_ProxyInfo,
    &IID_IotCircle,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotCircle::get_CenterPoint */ ,
    (void *) (INT_PTR) -1 /* IotCircle::put_CenterPoint */ ,
    (void *) (INT_PTR) -1 /* IotCircle::get_Radius */ ,
    (void *) (INT_PTR) -1 /* IotCircle::put_Radius */
};

const CInterfaceStubVtbl _IotCircleStubVtbl =
{
    &IID_IotCircle,
    &IotCircle_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotEllipse, ver. 0.0,
   GUID={0x8F0790DE,0x9A26,0x4196,{0x8B,0x2C,0x2D,0x8A,0x9D,0x20,0x68,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IotEllipse_FormatStringOffsetTable[] =
    {
    1352,
    1380,
    1864,
    1898
    };

static const MIDL_STUBLESS_PROXY_INFO IotEllipse_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotEllipse_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotEllipse_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotEllipse_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IotEllipseProxyVtbl = 
{
    &IotEllipse_ProxyInfo,
    &IID_IotEllipse,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotEllipse::get_CenterPoint */ ,
    (void *) (INT_PTR) -1 /* IotEllipse::put_CenterPoint */ ,
    (void *) (INT_PTR) -1 /* IotEllipse::GetAxes */ ,
    (void *) (INT_PTR) -1 /* IotEllipse::SetAxes */
};

const CInterfaceStubVtbl _IotEllipseStubVtbl =
{
    &IID_IotEllipse,
    &IotEllipse_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotBezierSpline, ver. 0.0,
   GUID={0xFD6436F2,0xD47E,0x4DDB,{0xB2,0x4C,0xF7,0xF3,0x7D,0x08,0x65,0xD2}} */

#pragma code_seg(".orpc")
static const unsigned short IotBezierSpline_FormatStringOffsetTable[] =
    {
    1932
    };

static const MIDL_STUBLESS_PROXY_INFO IotBezierSpline_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotBezierSpline_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotBezierSpline_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotBezierSpline_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IotBezierSplineProxyVtbl = 
{
    &IotBezierSpline_ProxyInfo,
    &IID_IotBezierSpline,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotBezierSpline::Create */
};

const CInterfaceStubVtbl _IotBezierSplineStubVtbl =
{
    &IID_IotBezierSpline,
    &IotBezierSpline_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotLine, ver. 0.0,
   GUID={0x716150DE,0x5EC3,0x454C,{0xB6,0xFB,0xDC,0x01,0x91,0x05,0xE7,0xDE}} */

#pragma code_seg(".orpc")
static const unsigned short IotLine_FormatStringOffsetTable[] =
    {
    1352,
    1380,
    1408,
    1436,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotLine_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotLine_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotLine_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotLine_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IotLineProxyVtbl = 
{
    0,
    &IID_IotLine,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotSegment::get_FromPoint */ ,
    0 /* forced delegation IotSegment::put_FromPoint */ ,
    0 /* forced delegation IotSegment::get_ToPoint */ ,
    0 /* forced delegation IotSegment::put_ToPoint */
};


static const PRPC_STUB_FUNCTION IotLine_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotLineStubVtbl =
{
    &IID_IotLine,
    &IotLine_ServerInfo,
    7,
    &IotLine_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotBezierCurve, ver. 0.0,
   GUID={0x719A5E2E,0x1432,0x427C,{0x9D,0xC9,0x93,0x79,0xBD,0xB8,0x85,0x76}} */

#pragma code_seg(".orpc")
static const unsigned short IotBezierCurve_FormatStringOffsetTable[] =
    {
    1352,
    1380,
    1408,
    1436,
    1582,
    1610,
    1966,
    1994
    };

static const MIDL_STUBLESS_PROXY_INFO IotBezierCurve_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotBezierCurve_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotBezierCurve_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotBezierCurve_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IotBezierCurveProxyVtbl = 
{
    &IotBezierCurve_ProxyInfo,
    &IID_IotBezierCurve,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSegment::get_FromPoint */ ,
    (void *) (INT_PTR) -1 /* IotSegment::put_FromPoint */ ,
    (void *) (INT_PTR) -1 /* IotSegment::get_ToPoint */ ,
    (void *) (INT_PTR) -1 /* IotSegment::put_ToPoint */ ,
    (void *) (INT_PTR) -1 /* IotBezierCurve::get_FirstCtrlPoint */ ,
    (void *) (INT_PTR) -1 /* IotBezierCurve::put_FirstCtrlPoint */ ,
    (void *) (INT_PTR) -1 /* IotBezierCurve::get_SecondCtrlPoint */ ,
    (void *) (INT_PTR) -1 /* IotBezierCurve::put_SecondCtrlPoint */
};

const CInterfaceStubVtbl _IotBezierCurveStubVtbl =
{
    &IID_IotBezierCurve,
    &IotBezierCurve_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x600016e, /* MIDL Version 6.0.366 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _otcGeometry_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IotGeometryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotBezierCurveProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotMultiPointProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSegmentCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotCircleProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotMultiLineStringProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotPolygonProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSegmentProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotTransformProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotPointProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotPointCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotMultiPolygonProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotLineStringProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotLineRingProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotGeometryCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotEnvelopeProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotLineProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotEllipseProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotGeoConvertProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotBezierSplineProxyVtbl,
    0
};

const CInterfaceStubVtbl * _otcGeometry_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IotGeometryStubVtbl,
    ( CInterfaceStubVtbl *) &_IotBezierCurveStubVtbl,
    ( CInterfaceStubVtbl *) &_IotMultiPointStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSegmentCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IotCircleStubVtbl,
    ( CInterfaceStubVtbl *) &_IotMultiLineStringStubVtbl,
    ( CInterfaceStubVtbl *) &_IotPolygonStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSegmentStubVtbl,
    ( CInterfaceStubVtbl *) &_IotTransformStubVtbl,
    ( CInterfaceStubVtbl *) &_IotPointStubVtbl,
    ( CInterfaceStubVtbl *) &_IotPointCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IotMultiPolygonStubVtbl,
    ( CInterfaceStubVtbl *) &_IotLineStringStubVtbl,
    ( CInterfaceStubVtbl *) &_IotLineRingStubVtbl,
    ( CInterfaceStubVtbl *) &_IotGeometryCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IotEnvelopeStubVtbl,
    ( CInterfaceStubVtbl *) &_IotLineStubVtbl,
    ( CInterfaceStubVtbl *) &_IotEllipseStubVtbl,
    ( CInterfaceStubVtbl *) &_IotGeoConvertStubVtbl,
    ( CInterfaceStubVtbl *) &_IotBezierSplineStubVtbl,
    0
};

PCInterfaceName const _otcGeometry_InterfaceNamesList[] = 
{
    "IotGeometry",
    "IotBezierCurve",
    "IotMultiPoint",
    "IotSegmentCollection",
    "IotCircle",
    "IotMultiLineString",
    "IotPolygon",
    "IotSegment",
    "IotTransform",
    "IotPoint",
    "IotPointCollection",
    "IotMultiPolygon",
    "IotLineString",
    "IotLineRing",
    "IotGeometryCollection",
    "IotEnvelope",
    "IotLine",
    "IotEllipse",
    "IotGeoConvert",
    "IotBezierSpline",
    0
};

const IID *  _otcGeometry_BaseIIDList[] = 
{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    &IID_IotLineString,   /* forced */
    0,
    0,
    &IID_IotSegment,   /* forced */
    0,
    0,
    0,
    0
};


#define _otcGeometry_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _otcGeometry, pIID, n)

int __stdcall _otcGeometry_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _otcGeometry, 20, 16 )
    IID_BS_LOOKUP_NEXT_TEST( _otcGeometry, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _otcGeometry, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _otcGeometry, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _otcGeometry, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _otcGeometry, 20, *pIndex )
    
}

const ExtendedProxyFileInfo otcGeometry_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _otcGeometry_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _otcGeometry_StubVtblList,
    (const PCInterfaceName * ) & _otcGeometry_InterfaceNamesList,
    (const IID ** ) & _otcGeometry_BaseIIDList,
    & _otcGeometry_IID_Lookup, 
    20,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

