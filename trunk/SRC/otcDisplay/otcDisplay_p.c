

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sat Mar 17 22:48:43 2012
 */
/* Compiler settings for .\otcDisplay.idl:
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


#include "otcDisplay.h"

#define TYPE_FORMAT_STRING_SIZE   207                               
#define PROC_FORMAT_STRING_SIZE   2097                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

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


extern const MIDL_SERVER_INFO IotSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotMarkerSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotMarkerSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotLineSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotLineSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotFillSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotFillSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotColor_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotColor_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSimpleMarkerSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSimpleMarkerSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotCharMarkerSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotCharMarkerSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotArrowMarkerSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotArrowMarkerSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotPicMarkerSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotPicMarkerSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSimpleLineSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSimpleLineSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotAdvLineSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotAdvLineSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotHashLineSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotHashLineSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotMarkerLineSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotMarkerLineSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSimpleFillSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSimpleFillSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotLineFillSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotLineFillSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotMarkerFillSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotMarkerFillSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotPicFillSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotPicFillSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotGradientFillSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotGradientFillSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotComplexMarkerSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotComplexMarkerSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotComplexLineSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotComplexLineSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotComplexFillSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotComplexFillSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotCanvas_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotCanvas_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSymbolConvert_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSymbolConvert_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotTextSymbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotTextSymbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSymbolLibLoader_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSymbolLibLoader_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, float, double or hyper in -Oif or -Oicf.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_Type */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x22 ),	/* 34 */
/* 14 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 16 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 24 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Unit */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x22 ),	/* 34 */
/* 42 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 44 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 46 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 48 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 52 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Unit */

/* 56 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 58 */	NdrFcLong( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x5 ),	/* 5 */
/* 64 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 66 */	NdrFcShort( 0x6 ),	/* 6 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 72 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 74 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 76 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 80 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Color */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x6 ),	/* 6 */
/* 92 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x8 ),	/* 8 */
/* 98 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 100 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 102 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 104 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 106 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 108 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Color */

/* 112 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 114 */	NdrFcLong( 0x0 ),	/* 0 */
/* 118 */	NdrFcShort( 0x7 ),	/* 7 */
/* 120 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 124 */	NdrFcShort( 0x8 ),	/* 8 */
/* 126 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 128 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 130 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 132 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 134 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 136 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Angle */


	/* Procedure get_OffsetX */

/* 140 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 142 */	NdrFcLong( 0x0 ),	/* 0 */
/* 146 */	NdrFcShort( 0x8 ),	/* 8 */
/* 148 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x2c ),	/* 44 */
/* 154 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 156 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 158 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 160 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 162 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 164 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Angle */


	/* Procedure put_OffsetX */

/* 168 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 170 */	NdrFcLong( 0x0 ),	/* 0 */
/* 174 */	NdrFcShort( 0x9 ),	/* 9 */
/* 176 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 178 */	NdrFcShort( 0x10 ),	/* 16 */
/* 180 */	NdrFcShort( 0x8 ),	/* 8 */
/* 182 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 184 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 186 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 188 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 190 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 192 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_OffsetY */

/* 196 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 198 */	NdrFcLong( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0xa ),	/* 10 */
/* 204 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0x2c ),	/* 44 */
/* 210 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 212 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 214 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 216 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 218 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 220 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_OffsetY */

/* 224 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 226 */	NdrFcLong( 0x0 ),	/* 0 */
/* 230 */	NdrFcShort( 0xb ),	/* 11 */
/* 232 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 234 */	NdrFcShort( 0x10 ),	/* 16 */
/* 236 */	NdrFcShort( 0x8 ),	/* 8 */
/* 238 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 240 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 242 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 244 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 246 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 248 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_OffsetX */


	/* Procedure get_Angle */


	/* Procedure get_Angle */

/* 252 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 254 */	NdrFcLong( 0x0 ),	/* 0 */
/* 258 */	NdrFcShort( 0xc ),	/* 12 */
/* 260 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 262 */	NdrFcShort( 0x0 ),	/* 0 */
/* 264 */	NdrFcShort( 0x2c ),	/* 44 */
/* 266 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 268 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 270 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 272 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 274 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 276 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 278 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_OffsetX */


	/* Procedure put_Angle */


	/* Procedure put_Angle */

/* 280 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 282 */	NdrFcLong( 0x0 ),	/* 0 */
/* 286 */	NdrFcShort( 0xd ),	/* 13 */
/* 288 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 290 */	NdrFcShort( 0x10 ),	/* 16 */
/* 292 */	NdrFcShort( 0x8 ),	/* 8 */
/* 294 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */

/* 296 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 298 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 300 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 302 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 304 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 306 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_OffsetY */


	/* Procedure get_separation */


	/* Procedure get_Size */

/* 308 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 310 */	NdrFcLong( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0xe ),	/* 14 */
/* 316 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 320 */	NdrFcShort( 0x2c ),	/* 44 */
/* 322 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 324 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 326 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 328 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 330 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 332 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 334 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_OffsetY */


	/* Procedure put_separation */


	/* Procedure put_Size */

/* 336 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 338 */	NdrFcLong( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0xf ),	/* 15 */
/* 344 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 346 */	NdrFcShort( 0x10 ),	/* 16 */
/* 348 */	NdrFcShort( 0x8 ),	/* 8 */
/* 350 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */

/* 352 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 354 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 356 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 358 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 360 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 362 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Size */


	/* Procedure get_LineWidth */

/* 364 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 366 */	NdrFcLong( 0x0 ),	/* 0 */
/* 370 */	NdrFcShort( 0x6 ),	/* 6 */
/* 372 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 376 */	NdrFcShort( 0x2c ),	/* 44 */
/* 378 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 380 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 382 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 384 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 386 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 388 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 390 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Size */


	/* Procedure put_LineWidth */

/* 392 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 394 */	NdrFcLong( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x7 ),	/* 7 */
/* 400 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 402 */	NdrFcShort( 0x10 ),	/* 16 */
/* 404 */	NdrFcShort( 0x8 ),	/* 8 */
/* 406 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 408 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 412 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 416 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Color */

/* 420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 426 */	NdrFcShort( 0x8 ),	/* 8 */
/* 428 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 434 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 436 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 438 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 440 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 442 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 444 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 446 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Color */

/* 448 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 450 */	NdrFcLong( 0x0 ),	/* 0 */
/* 454 */	NdrFcShort( 0x9 ),	/* 9 */
/* 456 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 458 */	NdrFcShort( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x8 ),	/* 8 */
/* 462 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 464 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 466 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 468 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 470 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 472 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DrawOutLine */

/* 476 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 478 */	NdrFcLong( 0x0 ),	/* 0 */
/* 482 */	NdrFcShort( 0x6 ),	/* 6 */
/* 484 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 488 */	NdrFcShort( 0x22 ),	/* 34 */
/* 490 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 492 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 494 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 496 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 498 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 500 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 502 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DrawOutLine */

/* 504 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 506 */	NdrFcLong( 0x0 ),	/* 0 */
/* 510 */	NdrFcShort( 0x7 ),	/* 7 */
/* 512 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 514 */	NdrFcShort( 0x6 ),	/* 6 */
/* 516 */	NdrFcShort( 0x8 ),	/* 8 */
/* 518 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 520 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 522 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 524 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 528 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_OutLine */

/* 532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x8 ),	/* 8 */
/* 540 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 546 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 548 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 550 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 552 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 554 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 556 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 558 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_OutLine */

/* 560 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 562 */	NdrFcLong( 0x0 ),	/* 0 */
/* 566 */	NdrFcShort( 0x9 ),	/* 9 */
/* 568 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 572 */	NdrFcShort( 0x8 ),	/* 8 */
/* 574 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 576 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 578 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 580 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */

	/* Return value */

/* 582 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 584 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 586 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TextColor */


	/* Procedure get_FillColor */

/* 588 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 590 */	NdrFcLong( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0xa ),	/* 10 */
/* 596 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 600 */	NdrFcShort( 0x8 ),	/* 8 */
/* 602 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 604 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 606 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 608 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */


	/* Return value */

/* 610 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 612 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 614 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TextColor */


	/* Procedure put_FillColor */

/* 616 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 618 */	NdrFcLong( 0x0 ),	/* 0 */
/* 622 */	NdrFcShort( 0xb ),	/* 11 */
/* 624 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 628 */	NdrFcShort( 0x8 ),	/* 8 */
/* 630 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 632 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 634 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 636 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */


	/* Return value */

/* 638 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 640 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 642 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Red */

/* 644 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 646 */	NdrFcLong( 0x0 ),	/* 0 */
/* 650 */	NdrFcShort( 0x3 ),	/* 3 */
/* 652 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	NdrFcShort( 0x24 ),	/* 36 */
/* 658 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 660 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 662 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 664 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 666 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 668 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 670 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Red */

/* 672 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 674 */	NdrFcLong( 0x0 ),	/* 0 */
/* 678 */	NdrFcShort( 0x4 ),	/* 4 */
/* 680 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 682 */	NdrFcShort( 0x8 ),	/* 8 */
/* 684 */	NdrFcShort( 0x8 ),	/* 8 */
/* 686 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 688 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 690 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 694 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 696 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 698 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Green */

/* 700 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 702 */	NdrFcLong( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x5 ),	/* 5 */
/* 708 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 712 */	NdrFcShort( 0x24 ),	/* 36 */
/* 714 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 716 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 718 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 720 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 722 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 724 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 726 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Green */

/* 728 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 730 */	NdrFcLong( 0x0 ),	/* 0 */
/* 734 */	NdrFcShort( 0x6 ),	/* 6 */
/* 736 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 738 */	NdrFcShort( 0x8 ),	/* 8 */
/* 740 */	NdrFcShort( 0x8 ),	/* 8 */
/* 742 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 744 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 752 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Blue */

/* 756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x7 ),	/* 7 */
/* 764 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x24 ),	/* 36 */
/* 770 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 772 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 774 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 776 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 778 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 780 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 782 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Blue */

/* 784 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 786 */	NdrFcLong( 0x0 ),	/* 0 */
/* 790 */	NdrFcShort( 0x8 ),	/* 8 */
/* 792 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 794 */	NdrFcShort( 0x8 ),	/* 8 */
/* 796 */	NdrFcShort( 0x8 ),	/* 8 */
/* 798 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 800 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 802 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 804 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 806 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 808 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 810 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DrawOutLine */

/* 812 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 814 */	NdrFcLong( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0x10 ),	/* 16 */
/* 820 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 824 */	NdrFcShort( 0x22 ),	/* 34 */
/* 826 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 828 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 830 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 832 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 834 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 836 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 838 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DrawOutLine */

/* 840 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 842 */	NdrFcLong( 0x0 ),	/* 0 */
/* 846 */	NdrFcShort( 0x11 ),	/* 17 */
/* 848 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 850 */	NdrFcShort( 0x6 ),	/* 6 */
/* 852 */	NdrFcShort( 0x8 ),	/* 8 */
/* 854 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 856 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 858 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 860 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 862 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 864 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 866 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SeparationY */


	/* Procedure get_OutLineWidth */

/* 868 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 870 */	NdrFcLong( 0x0 ),	/* 0 */
/* 874 */	NdrFcShort( 0x12 ),	/* 18 */
/* 876 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 880 */	NdrFcShort( 0x2c ),	/* 44 */
/* 882 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 884 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 886 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 888 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 890 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 892 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 894 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SeparationY */


	/* Procedure put_OutLineWidth */

/* 896 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 898 */	NdrFcLong( 0x0 ),	/* 0 */
/* 902 */	NdrFcShort( 0x13 ),	/* 19 */
/* 904 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 906 */	NdrFcShort( 0x10 ),	/* 16 */
/* 908 */	NdrFcShort( 0x8 ),	/* 8 */
/* 910 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 912 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 914 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 916 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 918 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 920 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 922 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_MarkerStyle */

/* 924 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 926 */	NdrFcLong( 0x0 ),	/* 0 */
/* 930 */	NdrFcShort( 0x14 ),	/* 20 */
/* 932 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 934 */	NdrFcShort( 0x0 ),	/* 0 */
/* 936 */	NdrFcShort( 0x22 ),	/* 34 */
/* 938 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 940 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 942 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 944 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 946 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 948 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 950 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_MarkerStyle */

/* 952 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 954 */	NdrFcLong( 0x0 ),	/* 0 */
/* 958 */	NdrFcShort( 0x15 ),	/* 21 */
/* 960 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 962 */	NdrFcShort( 0x6 ),	/* 6 */
/* 964 */	NdrFcShort( 0x8 ),	/* 8 */
/* 966 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 968 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 970 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 972 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 974 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 976 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 978 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_OutLineColor */

/* 980 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 982 */	NdrFcLong( 0x0 ),	/* 0 */
/* 986 */	NdrFcShort( 0x16 ),	/* 22 */
/* 988 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 990 */	NdrFcShort( 0x0 ),	/* 0 */
/* 992 */	NdrFcShort( 0x8 ),	/* 8 */
/* 994 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 996 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 998 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1000 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 1002 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1004 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1006 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_OutLineColor */

/* 1008 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1010 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1014 */	NdrFcShort( 0x17 ),	/* 23 */
/* 1016 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1020 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1022 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1024 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1026 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1028 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 1030 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1032 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1034 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PictureFile */

/* 1036 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1038 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1042 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1044 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1048 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1050 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1052 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1054 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1056 */	NdrFcShort( 0x5a ),	/* Type Offset=90 */

	/* Return value */

/* 1058 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1060 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1062 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PictureFile */

/* 1064 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1066 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1070 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1072 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1076 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1078 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1080 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1082 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1084 */	NdrFcShort( 0x68 ),	/* Type Offset=104 */

	/* Return value */

/* 1086 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1088 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1090 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TransparentColor */

/* 1092 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1094 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1098 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1100 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1104 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1106 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1108 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1110 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1112 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 1114 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1116 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TransparentColor */

/* 1120 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1122 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1126 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1128 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1132 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1134 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1136 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1138 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1140 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 1142 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1144 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1146 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BackgroundColor */

/* 1148 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1150 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1154 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1156 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1160 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1162 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1164 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1166 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1168 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 1170 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1172 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1174 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_BackgroundColor */

/* 1176 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1178 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1182 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1184 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1188 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1190 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1192 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1194 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1196 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 1198 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1200 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LineStyle */

/* 1204 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1206 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1210 */	NdrFcShort( 0xa ),	/* 10 */
/* 1212 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1216 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1218 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1220 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 1222 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1224 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 1226 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1228 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1230 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LineStyle */

/* 1232 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1234 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1238 */	NdrFcShort( 0xb ),	/* 11 */
/* 1240 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1242 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1244 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1246 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1248 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1250 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1252 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 1254 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1256 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1258 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_MarkerSymbol */

/* 1260 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1266 */	NdrFcShort( 0xa ),	/* 10 */
/* 1268 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1272 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1274 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1276 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1278 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1280 */	NdrFcShort( 0x72 ),	/* Type Offset=114 */

	/* Return value */

/* 1282 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1284 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1286 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_MarkerSymbol */

/* 1288 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1290 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1294 */	NdrFcShort( 0xb ),	/* 11 */
/* 1296 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1298 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1300 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1302 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1304 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1306 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1308 */	NdrFcShort( 0x76 ),	/* Type Offset=118 */

	/* Return value */

/* 1310 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1312 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1314 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SeparationX */


	/* Procedure get_Offset */

/* 1316 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1318 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1322 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1324 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1328 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1330 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1332 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1334 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1336 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1338 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1340 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1342 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SeparationX */


	/* Procedure put_Offset */

/* 1344 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1346 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1350 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1352 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1354 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1356 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1358 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 1360 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1362 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1364 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1366 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1368 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1370 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LineSymbol */

/* 1372 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1374 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1378 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1380 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1382 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1384 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1386 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1388 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1390 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1392 */	NdrFcShort( 0x88 ),	/* Type Offset=136 */

	/* Return value */

/* 1394 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1396 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1398 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LineSymbol */

/* 1400 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1402 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1406 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1408 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1410 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1412 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1414 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1416 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1418 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1420 */	NdrFcShort( 0x8c ),	/* Type Offset=140 */

	/* Return value */

/* 1422 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1424 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1426 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_MarkSymbol */

/* 1428 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1430 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1434 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1436 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1440 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1442 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1444 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1446 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1448 */	NdrFcShort( 0x72 ),	/* Type Offset=114 */

	/* Return value */

/* 1450 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1452 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1454 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_MarkSymbol */

/* 1456 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1458 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1462 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1464 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1468 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1470 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1472 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1474 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1476 */	NdrFcShort( 0x76 ),	/* Type Offset=118 */

	/* Return value */

/* 1478 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1480 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1482 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PictureFile */

/* 1484 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1486 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1490 */	NdrFcShort( 0xc ),	/* 12 */
/* 1492 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1494 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1496 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1498 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1500 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1502 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1504 */	NdrFcShort( 0x5a ),	/* Type Offset=90 */

	/* Return value */

/* 1506 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1508 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1510 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PictureFile */

/* 1512 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1514 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1518 */	NdrFcShort( 0xd ),	/* 13 */
/* 1520 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1524 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1526 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1528 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1530 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1532 */	NdrFcShort( 0x68 ),	/* Type Offset=104 */

	/* Return value */

/* 1534 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1536 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1538 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndColor */


	/* Procedure get_BackgroundColor */

/* 1540 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1542 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1546 */	NdrFcShort( 0xe ),	/* 14 */
/* 1548 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1552 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1554 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1556 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1558 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1560 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */


	/* Return value */

/* 1562 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1564 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1566 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndColor */


	/* Procedure put_BackgroundColor */

/* 1568 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1570 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1574 */	NdrFcShort( 0xf ),	/* 15 */
/* 1576 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1580 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1582 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 1584 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1586 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1588 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */


	/* Return value */

/* 1590 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1592 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1594 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TransparentColor */

/* 1596 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1598 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1602 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1604 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1608 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1610 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1612 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1614 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1616 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 1618 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1620 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1622 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TransparentColor */

/* 1624 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1626 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1630 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1632 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1636 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1638 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1640 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1642 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1644 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 1646 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1648 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1650 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BeginColor */

/* 1652 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1654 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1658 */	NdrFcShort( 0xc ),	/* 12 */
/* 1660 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1664 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1666 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1668 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1670 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1672 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 1674 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1676 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1678 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_BeginColor */

/* 1680 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1682 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1686 */	NdrFcShort( 0xd ),	/* 13 */
/* 1688 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1690 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1692 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1694 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1696 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1698 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1700 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 1702 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1704 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1706 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_GradientFillType */

/* 1708 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1710 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1714 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1716 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1718 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1720 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1722 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1724 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 1726 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1728 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 1730 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1732 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1734 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_GradientFillType */

/* 1736 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1738 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1742 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1744 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1746 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1748 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1750 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1752 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1754 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1756 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 1758 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1760 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1762 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SegmentCounts */

/* 1764 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1766 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1770 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1772 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1776 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1778 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1780 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1782 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1784 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1786 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1788 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SegmentCounts */

/* 1792 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1794 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1798 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1800 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1802 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1804 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1806 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1808 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1810 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1812 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1814 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1816 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1818 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Percent */

/* 1820 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1822 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1826 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1828 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1832 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1834 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1836 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1838 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1840 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1842 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1844 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1846 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Percent */

/* 1848 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1850 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1854 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1856 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1858 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1860 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1862 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1864 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1866 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1870 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1872 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1874 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Angle */

/* 1876 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1878 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1882 */	NdrFcShort( 0x16 ),	/* 22 */
/* 1884 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1888 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1890 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1892 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1894 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1896 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 1898 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1900 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1902 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Angle */

/* 1904 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1906 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1910 */	NdrFcShort( 0x17 ),	/* 23 */
/* 1912 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1914 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1916 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1918 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1920 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1922 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1924 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 1926 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1928 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1930 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ConvertSymbol */

/* 1932 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1934 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1938 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1940 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1942 */	NdrFcShort( 0xe ),	/* 14 */
/* 1944 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1946 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x4,		/* 4 */

	/* Parameter ldata */

/* 1948 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1950 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1952 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bown */

/* 1954 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1956 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1958 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter retSymbol */

/* 1960 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1962 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1964 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1966 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1968 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Font */

/* 1972 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1974 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1978 */	NdrFcShort( 0xc ),	/* 12 */
/* 1980 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1984 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1986 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1988 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1990 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1992 */	NdrFcShort( 0xa2 ),	/* Type Offset=162 */

	/* Return value */

/* 1994 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1996 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1998 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Font */

/* 2000 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2002 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2006 */	NdrFcShort( 0xd ),	/* 13 */
/* 2008 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2010 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2012 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2014 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 2016 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2018 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2020 */	NdrFcShort( 0xa6 ),	/* Type Offset=166 */

	/* Return value */

/* 2022 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2024 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2026 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Open */

/* 2028 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2030 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2034 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2036 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2040 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2042 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter libName */

/* 2044 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2046 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2048 */	NdrFcShort( 0x68 ),	/* Type Offset=104 */

	/* Parameter ret */

/* 2050 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2052 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2054 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2056 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2058 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2060 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSymbol */

/* 2062 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2064 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2068 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2070 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2072 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2074 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2076 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 2078 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2080 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2082 */	NdrFcShort( 0x68 ),	/* Type Offset=104 */

	/* Parameter retSymbol */

/* 2084 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2086 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2088 */	NdrFcShort( 0xb8 ),	/* Type Offset=184 */

	/* Return value */

/* 2090 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2092 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2094 */	0x8,		/* FC_LONG */
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
/*  4 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 12 */	NdrFcLong( 0xa3abfab4 ),	/* -1549010252 */
/* 16 */	NdrFcShort( 0x3d14 ),	/* 15636 */
/* 18 */	NdrFcShort( 0x4f02 ),	/* 20226 */
/* 20 */	0xad,		/* 173 */
			0xaf,		/* 175 */
/* 22 */	0x37,		/* 55 */
			0xac,		/* 172 */
/* 24 */	0x9c,		/* 156 */
			0xd2,		/* 210 */
/* 26 */	0xd6,		/* 214 */
			0xb,		/* 11 */
/* 28 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 30 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 32 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 34 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 36 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 38 */	NdrFcShort( 0x2 ),	/* Offset= 2 (40) */
/* 40 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 42 */	NdrFcLong( 0x3719d63b ),	/* 924440123 */
/* 46 */	NdrFcShort( 0x9a15 ),	/* -26091 */
/* 48 */	NdrFcShort( 0x4bc3 ),	/* 19395 */
/* 50 */	0xac,		/* 172 */
			0x8a,		/* 138 */
/* 52 */	0x33,		/* 51 */
			0x54,		/* 84 */
/* 54 */	0x3e,		/* 62 */
			0x70,		/* 112 */
/* 56 */	0x92,		/* 146 */
			0xbc,		/* 188 */
/* 58 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 60 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 62 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 64 */	NdrFcShort( 0x1a ),	/* Offset= 26 (90) */
/* 66 */	
			0x13, 0x0,	/* FC_OP */
/* 68 */	NdrFcShort( 0xc ),	/* Offset= 12 (80) */
/* 70 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 72 */	NdrFcShort( 0x2 ),	/* 2 */
/* 74 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 76 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 78 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 80 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 82 */	NdrFcShort( 0x8 ),	/* 8 */
/* 84 */	NdrFcShort( 0xfff2 ),	/* Offset= -14 (70) */
/* 86 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 88 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 90 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x4 ),	/* 4 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (66) */
/* 100 */	
			0x12, 0x0,	/* FC_UP */
/* 102 */	NdrFcShort( 0xffea ),	/* Offset= -22 (80) */
/* 104 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 108 */	NdrFcShort( 0x4 ),	/* 4 */
/* 110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (100) */
/* 114 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 116 */	NdrFcShort( 0x2 ),	/* Offset= 2 (118) */
/* 118 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 120 */	NdrFcLong( 0xb1797a2e ),	/* -1317438930 */
/* 124 */	NdrFcShort( 0x3b2c ),	/* 15148 */
/* 126 */	NdrFcShort( 0x434a ),	/* 17226 */
/* 128 */	0x98,		/* 152 */
			0xe,		/* 14 */
/* 130 */	0x36,		/* 54 */
			0x27,		/* 39 */
/* 132 */	0x8b,		/* 139 */
			0x98,		/* 152 */
/* 134 */	0x31,		/* 49 */
			0x2c,		/* 44 */
/* 136 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 138 */	NdrFcShort( 0x2 ),	/* Offset= 2 (140) */
/* 140 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 142 */	NdrFcLong( 0x8a5b2356 ),	/* -1973738666 */
/* 146 */	NdrFcShort( 0x8ff7 ),	/* -28681 */
/* 148 */	NdrFcShort( 0x4027 ),	/* 16423 */
/* 150 */	0xa4,		/* 164 */
			0xf8,		/* 248 */
/* 152 */	0x2,		/* 2 */
			0xab,		/* 171 */
/* 154 */	0xe1,		/* 225 */
			0x3c,		/* 60 */
/* 156 */	0x8c,		/* 140 */
			0x7e,		/* 126 */
/* 158 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 160 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 162 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 164 */	NdrFcShort( 0x2 ),	/* Offset= 2 (166) */
/* 166 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 168 */	NdrFcLong( 0xbef6e003 ),	/* -1091117053 */
/* 172 */	NdrFcShort( 0xa874 ),	/* -22412 */
/* 174 */	NdrFcShort( 0x101a ),	/* 4122 */
/* 176 */	0x8b,		/* 139 */
			0xba,		/* 186 */
/* 178 */	0x0,		/* 0 */
			0xaa,		/* 170 */
/* 180 */	0x0,		/* 0 */
			0x30,		/* 48 */
/* 182 */	0xc,		/* 12 */
			0xab,		/* 171 */
/* 184 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 186 */	NdrFcShort( 0x2 ),	/* Offset= 2 (188) */
/* 188 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 190 */	NdrFcLong( 0x3719d63b ),	/* 924440123 */
/* 194 */	NdrFcShort( 0x9a15 ),	/* -26091 */
/* 196 */	NdrFcShort( 0x4bc3 ),	/* 19395 */
/* 198 */	0xac,		/* 172 */
			0x8a,		/* 138 */
/* 200 */	0x33,		/* 51 */
			0x54,		/* 84 */
/* 202 */	0x3e,		/* 62 */
			0x70,		/* 112 */
/* 204 */	0x92,		/* 146 */
			0xbc,		/* 188 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Standard interface: __MIDL_itf_otcDisplay_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IotSymbol, ver. 0.0,
   GUID={0x3719D63B,0x9A15,0x4bc3,{0xAC,0x8A,0x33,0x54,0x3E,0x70,0x92,0xBC}} */

#pragma code_seg(".orpc")
static const unsigned short IotSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56
    };

static const MIDL_STUBLESS_PROXY_INFO IotSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IotSymbolProxyVtbl = 
{
    &IotSymbol_ProxyInfo,
    &IID_IotSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */
};

const CInterfaceStubVtbl _IotSymbolStubVtbl =
{
    &IID_IotSymbol,
    &IotSymbol_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotMarkerSymbol, ver. 0.0,
   GUID={0xB1797A2E,0x3B2C,0x434a,{0x98,0x0E,0x36,0x27,0x8B,0x98,0x31,0x2C}} */

#pragma code_seg(".orpc")
static const unsigned short IotMarkerSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    84,
    112,
    140,
    168,
    196,
    224,
    252,
    280,
    308,
    336
    };

static const MIDL_STUBLESS_PROXY_INFO IotMarkerSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotMarkerSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IotMarkerSymbolProxyVtbl = 
{
    &IotMarkerSymbol_ProxyInfo,
    &IID_IotMarkerSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_Color */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_Color */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_OffsetX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_OffsetX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_OffsetY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_OffsetY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_Angle */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_Angle */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_Size */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_Size */
};

const CInterfaceStubVtbl _IotMarkerSymbolStubVtbl =
{
    &IID_IotMarkerSymbol,
    &IotMarkerSymbol_ServerInfo,
    16,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotLineSymbol, ver. 0.0,
   GUID={0x8A5B2356,0x8FF7,0x4027,{0xA4,0xF8,0x02,0xAB,0xE1,0x3C,0x8C,0x7E}} */

#pragma code_seg(".orpc")
static const unsigned short IotLineSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    364,
    392,
    420,
    448
    };

static const MIDL_STUBLESS_PROXY_INFO IotLineSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotLineSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IotLineSymbolProxyVtbl = 
{
    &IotLineSymbol_ProxyInfo,
    &IID_IotLineSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::get_LineWidth */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::put_LineWidth */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::get_Color */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::put_Color */
};

const CInterfaceStubVtbl _IotLineSymbolStubVtbl =
{
    &IID_IotLineSymbol,
    &IotLineSymbol_ServerInfo,
    10,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotFillSymbol, ver. 0.0,
   GUID={0x107F6E58,0xF6E7,0x44cd,{0xB4,0xDF,0xA6,0x1B,0x3D,0x5F,0x97,0xD2}} */

#pragma code_seg(".orpc")
static const unsigned short IotFillSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    476,
    504,
    532,
    560,
    588,
    616
    };

static const MIDL_STUBLESS_PROXY_INFO IotFillSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotFillSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IotFillSymbolProxyVtbl = 
{
    &IotFillSymbol_ProxyInfo,
    &IID_IotFillSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_FillColor */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_FillColor */
};

const CInterfaceStubVtbl _IotFillSymbolStubVtbl =
{
    &IID_IotFillSymbol,
    &IotFillSymbol_ServerInfo,
    12,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotColor, ver. 0.0,
   GUID={0xA3ABFAB4,0x3D14,0x4F02,{0xAD,0xAF,0x37,0xAC,0x9C,0xD2,0xD6,0x0B}} */

#pragma code_seg(".orpc")
static const unsigned short IotColor_FormatStringOffsetTable[] =
    {
    644,
    672,
    700,
    728,
    756,
    784
    };

static const MIDL_STUBLESS_PROXY_INFO IotColor_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotColor_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotColor_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotColor_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IotColorProxyVtbl = 
{
    &IotColor_ProxyInfo,
    &IID_IotColor,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotColor::get_Red */ ,
    (void *) (INT_PTR) -1 /* IotColor::put_Red */ ,
    (void *) (INT_PTR) -1 /* IotColor::get_Green */ ,
    (void *) (INT_PTR) -1 /* IotColor::put_Green */ ,
    (void *) (INT_PTR) -1 /* IotColor::get_Blue */ ,
    (void *) (INT_PTR) -1 /* IotColor::put_Blue */
};

const CInterfaceStubVtbl _IotColorStubVtbl =
{
    &IID_IotColor,
    &IotColor_ServerInfo,
    9,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSimpleMarkerSymbol, ver. 0.0,
   GUID={0x27409DBF,0x730B,0x4756,{0x9D,0x09,0x5E,0xBF,0x25,0x88,0x5E,0x7B}} */

#pragma code_seg(".orpc")
static const unsigned short IotSimpleMarkerSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    84,
    112,
    140,
    168,
    196,
    224,
    252,
    280,
    308,
    336,
    812,
    840,
    868,
    896,
    924,
    952,
    980,
    1008
    };

static const MIDL_STUBLESS_PROXY_INFO IotSimpleMarkerSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSimpleMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSimpleMarkerSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSimpleMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(24) _IotSimpleMarkerSymbolProxyVtbl = 
{
    &IotSimpleMarkerSymbol_ProxyInfo,
    &IID_IotSimpleMarkerSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_Color */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_Color */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_OffsetX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_OffsetX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_OffsetY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_OffsetY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_Angle */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_Angle */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_Size */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_Size */ ,
    (void *) (INT_PTR) -1 /* IotSimpleMarkerSymbol::get_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotSimpleMarkerSymbol::put_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotSimpleMarkerSymbol::get_OutLineWidth */ ,
    (void *) (INT_PTR) -1 /* IotSimpleMarkerSymbol::put_OutLineWidth */ ,
    (void *) (INT_PTR) -1 /* IotSimpleMarkerSymbol::get_MarkerStyle */ ,
    (void *) (INT_PTR) -1 /* IotSimpleMarkerSymbol::put_MarkerStyle */ ,
    (void *) (INT_PTR) -1 /* IotSimpleMarkerSymbol::get_OutLineColor */ ,
    (void *) (INT_PTR) -1 /* IotSimpleMarkerSymbol::put_OutLineColor */
};

const CInterfaceStubVtbl _IotSimpleMarkerSymbolStubVtbl =
{
    &IID_IotSimpleMarkerSymbol,
    &IotSimpleMarkerSymbol_ServerInfo,
    24,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotCharMarkerSymbol, ver. 0.0,
   GUID={0x39F5D04E,0x3135,0x45CA,{0xA0,0x04,0xFE,0x0A,0xCA,0x6A,0xE8,0x83}} */

#pragma code_seg(".orpc")
static const unsigned short IotCharMarkerSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    84,
    112,
    140,
    168,
    196,
    224,
    252,
    280,
    308,
    336,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotCharMarkerSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotCharMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotCharMarkerSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotCharMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IotCharMarkerSymbolProxyVtbl = 
{
    0,
    &IID_IotCharMarkerSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotSymbol::get_Type */ ,
    0 /* forced delegation IotSymbol::get_Unit */ ,
    0 /* forced delegation IotSymbol::put_Unit */ ,
    0 /* forced delegation IotMarkerSymbol::get_Color */ ,
    0 /* forced delegation IotMarkerSymbol::put_Color */ ,
    0 /* forced delegation IotMarkerSymbol::get_OffsetX */ ,
    0 /* forced delegation IotMarkerSymbol::put_OffsetX */ ,
    0 /* forced delegation IotMarkerSymbol::get_OffsetY */ ,
    0 /* forced delegation IotMarkerSymbol::put_OffsetY */ ,
    0 /* forced delegation IotMarkerSymbol::get_Angle */ ,
    0 /* forced delegation IotMarkerSymbol::put_Angle */ ,
    0 /* forced delegation IotMarkerSymbol::get_Size */ ,
    0 /* forced delegation IotMarkerSymbol::put_Size */
};


static const PRPC_STUB_FUNCTION IotCharMarkerSymbol_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotCharMarkerSymbolStubVtbl =
{
    &IID_IotCharMarkerSymbol,
    &IotCharMarkerSymbol_ServerInfo,
    16,
    &IotCharMarkerSymbol_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotArrowMarkerSymbol, ver. 0.0,
   GUID={0xC43B9169,0x5882,0x4704,{0xA0,0x2D,0x40,0xE6,0xFA,0x9F,0x09,0x5F}} */

#pragma code_seg(".orpc")
static const unsigned short IotArrowMarkerSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    84,
    112,
    140,
    168,
    196,
    224,
    252,
    280,
    308,
    336,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotArrowMarkerSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotArrowMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotArrowMarkerSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotArrowMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IotArrowMarkerSymbolProxyVtbl = 
{
    0,
    &IID_IotArrowMarkerSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotSymbol::get_Type */ ,
    0 /* forced delegation IotSymbol::get_Unit */ ,
    0 /* forced delegation IotSymbol::put_Unit */ ,
    0 /* forced delegation IotMarkerSymbol::get_Color */ ,
    0 /* forced delegation IotMarkerSymbol::put_Color */ ,
    0 /* forced delegation IotMarkerSymbol::get_OffsetX */ ,
    0 /* forced delegation IotMarkerSymbol::put_OffsetX */ ,
    0 /* forced delegation IotMarkerSymbol::get_OffsetY */ ,
    0 /* forced delegation IotMarkerSymbol::put_OffsetY */ ,
    0 /* forced delegation IotMarkerSymbol::get_Angle */ ,
    0 /* forced delegation IotMarkerSymbol::put_Angle */ ,
    0 /* forced delegation IotMarkerSymbol::get_Size */ ,
    0 /* forced delegation IotMarkerSymbol::put_Size */
};


static const PRPC_STUB_FUNCTION IotArrowMarkerSymbol_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotArrowMarkerSymbolStubVtbl =
{
    &IID_IotArrowMarkerSymbol,
    &IotArrowMarkerSymbol_ServerInfo,
    16,
    &IotArrowMarkerSymbol_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotPicMarkerSymbol, ver. 0.0,
   GUID={0x59480D48,0xBA1B,0x4684,{0xB9,0x32,0x05,0xF1,0x77,0x69,0x9F,0x2E}} */

#pragma code_seg(".orpc")
static const unsigned short IotPicMarkerSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    84,
    112,
    140,
    168,
    196,
    224,
    252,
    280,
    308,
    336,
    1036,
    1064,
    1092,
    1120,
    1148,
    1176
    };

static const MIDL_STUBLESS_PROXY_INFO IotPicMarkerSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotPicMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotPicMarkerSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotPicMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(22) _IotPicMarkerSymbolProxyVtbl = 
{
    &IotPicMarkerSymbol_ProxyInfo,
    &IID_IotPicMarkerSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_Color */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_Color */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_OffsetX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_OffsetX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_OffsetY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_OffsetY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_Angle */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_Angle */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::get_Size */ ,
    (void *) (INT_PTR) -1 /* IotMarkerSymbol::put_Size */ ,
    (void *) (INT_PTR) -1 /* IotPicMarkerSymbol::get_PictureFile */ ,
    (void *) (INT_PTR) -1 /* IotPicMarkerSymbol::put_PictureFile */ ,
    (void *) (INT_PTR) -1 /* IotPicMarkerSymbol::get_TransparentColor */ ,
    (void *) (INT_PTR) -1 /* IotPicMarkerSymbol::put_TransparentColor */ ,
    (void *) (INT_PTR) -1 /* IotPicMarkerSymbol::get_BackgroundColor */ ,
    (void *) (INT_PTR) -1 /* IotPicMarkerSymbol::put_BackgroundColor */
};

const CInterfaceStubVtbl _IotPicMarkerSymbolStubVtbl =
{
    &IID_IotPicMarkerSymbol,
    &IotPicMarkerSymbol_ServerInfo,
    22,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSimpleLineSymbol, ver. 0.0,
   GUID={0xEDA46204,0xCF12,0x4BF3,{0x88,0x11,0x2D,0xAF,0xB5,0x4E,0x8B,0xB9}} */

#pragma code_seg(".orpc")
static const unsigned short IotSimpleLineSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    364,
    392,
    420,
    448,
    1204,
    1232
    };

static const MIDL_STUBLESS_PROXY_INFO IotSimpleLineSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSimpleLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSimpleLineSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSimpleLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IotSimpleLineSymbolProxyVtbl = 
{
    &IotSimpleLineSymbol_ProxyInfo,
    &IID_IotSimpleLineSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::get_LineWidth */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::put_LineWidth */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::get_Color */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::put_Color */ ,
    (void *) (INT_PTR) -1 /* IotSimpleLineSymbol::get_LineStyle */ ,
    (void *) (INT_PTR) -1 /* IotSimpleLineSymbol::put_LineStyle */
};

const CInterfaceStubVtbl _IotSimpleLineSymbolStubVtbl =
{
    &IID_IotSimpleLineSymbol,
    &IotSimpleLineSymbol_ServerInfo,
    12,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotAdvLineSymbol, ver. 0.0,
   GUID={0xFDDD408D,0x5B2A,0x4232,{0xBB,0xF2,0xFF,0x2D,0x4B,0xE4,0x6A,0x12}} */

#pragma code_seg(".orpc")
static const unsigned short IotAdvLineSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    364,
    392,
    420,
    448,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotAdvLineSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotAdvLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotAdvLineSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotAdvLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IotAdvLineSymbolProxyVtbl = 
{
    0,
    &IID_IotAdvLineSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotSymbol::get_Type */ ,
    0 /* forced delegation IotSymbol::get_Unit */ ,
    0 /* forced delegation IotSymbol::put_Unit */ ,
    0 /* forced delegation IotLineSymbol::get_LineWidth */ ,
    0 /* forced delegation IotLineSymbol::put_LineWidth */ ,
    0 /* forced delegation IotLineSymbol::get_Color */ ,
    0 /* forced delegation IotLineSymbol::put_Color */
};


static const PRPC_STUB_FUNCTION IotAdvLineSymbol_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotAdvLineSymbolStubVtbl =
{
    &IID_IotAdvLineSymbol,
    &IotAdvLineSymbol_ServerInfo,
    10,
    &IotAdvLineSymbol_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotHashLineSymbol, ver. 0.0,
   GUID={0x6C75C746,0x7EBC,0x40A1,{0x84,0xD0,0x3F,0x2B,0x41,0x65,0x41,0x3D}} */

#pragma code_seg(".orpc")
static const unsigned short IotHashLineSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    364,
    392,
    420,
    448,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotHashLineSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotHashLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotHashLineSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotHashLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IotHashLineSymbolProxyVtbl = 
{
    0,
    &IID_IotHashLineSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotSymbol::get_Type */ ,
    0 /* forced delegation IotSymbol::get_Unit */ ,
    0 /* forced delegation IotSymbol::put_Unit */ ,
    0 /* forced delegation IotLineSymbol::get_LineWidth */ ,
    0 /* forced delegation IotLineSymbol::put_LineWidth */ ,
    0 /* forced delegation IotLineSymbol::get_Color */ ,
    0 /* forced delegation IotLineSymbol::put_Color */
};


static const PRPC_STUB_FUNCTION IotHashLineSymbol_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotHashLineSymbolStubVtbl =
{
    &IID_IotHashLineSymbol,
    &IotHashLineSymbol_ServerInfo,
    10,
    &IotHashLineSymbol_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotMarkerLineSymbol, ver. 0.0,
   GUID={0x21D5AFE5,0xE6C8,0x4048,{0xBB,0x4B,0x34,0xB0,0x38,0xE0,0xD3,0x82}} */

#pragma code_seg(".orpc")
static const unsigned short IotMarkerLineSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    364,
    392,
    420,
    448,
    1260,
    1288
    };

static const MIDL_STUBLESS_PROXY_INFO IotMarkerLineSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotMarkerLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotMarkerLineSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotMarkerLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IotMarkerLineSymbolProxyVtbl = 
{
    &IotMarkerLineSymbol_ProxyInfo,
    &IID_IotMarkerLineSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::get_LineWidth */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::put_LineWidth */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::get_Color */ ,
    (void *) (INT_PTR) -1 /* IotLineSymbol::put_Color */ ,
    (void *) (INT_PTR) -1 /* IotMarkerLineSymbol::get_MarkerSymbol */ ,
    (void *) (INT_PTR) -1 /* IotMarkerLineSymbol::put_MarkerSymbol */
};

const CInterfaceStubVtbl _IotMarkerLineSymbolStubVtbl =
{
    &IID_IotMarkerLineSymbol,
    &IotMarkerLineSymbol_ServerInfo,
    12,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSimpleFillSymbol, ver. 0.0,
   GUID={0x7E000018,0x2A71,0x46F6,{0xAD,0x2F,0xBF,0x89,0xB6,0x6B,0x4C,0xED}} */

#pragma code_seg(".orpc")
static const unsigned short IotSimpleFillSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    476,
    504,
    532,
    560,
    588,
    616,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotSimpleFillSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSimpleFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSimpleFillSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSimpleFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IotSimpleFillSymbolProxyVtbl = 
{
    0,
    &IID_IotSimpleFillSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotSymbol::get_Type */ ,
    0 /* forced delegation IotSymbol::get_Unit */ ,
    0 /* forced delegation IotSymbol::put_Unit */ ,
    0 /* forced delegation IotFillSymbol::get_DrawOutLine */ ,
    0 /* forced delegation IotFillSymbol::put_DrawOutLine */ ,
    0 /* forced delegation IotFillSymbol::get_OutLine */ ,
    0 /* forced delegation IotFillSymbol::put_OutLine */ ,
    0 /* forced delegation IotFillSymbol::get_FillColor */ ,
    0 /* forced delegation IotFillSymbol::put_FillColor */
};


static const PRPC_STUB_FUNCTION IotSimpleFillSymbol_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotSimpleFillSymbolStubVtbl =
{
    &IID_IotSimpleFillSymbol,
    &IotSimpleFillSymbol_ServerInfo,
    12,
    &IotSimpleFillSymbol_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotLineFillSymbol, ver. 0.0,
   GUID={0x398832F1,0x2E6D,0x45DB,{0x9C,0x8D,0xAE,0x15,0x4F,0x85,0xE6,0x13}} */

#pragma code_seg(".orpc")
static const unsigned short IotLineFillSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    476,
    504,
    532,
    560,
    588,
    616,
    252,
    280,
    308,
    336,
    1316,
    1344,
    1372,
    1400
    };

static const MIDL_STUBLESS_PROXY_INFO IotLineFillSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotLineFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotLineFillSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotLineFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(20) _IotLineFillSymbolProxyVtbl = 
{
    &IotLineFillSymbol_ProxyInfo,
    &IID_IotLineFillSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_FillColor */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_FillColor */ ,
    (void *) (INT_PTR) -1 /* IotLineFillSymbol::get_Angle */ ,
    (void *) (INT_PTR) -1 /* IotLineFillSymbol::put_Angle */ ,
    (void *) (INT_PTR) -1 /* IotLineFillSymbol::get_separation */ ,
    (void *) (INT_PTR) -1 /* IotLineFillSymbol::put_separation */ ,
    (void *) (INT_PTR) -1 /* IotLineFillSymbol::get_Offset */ ,
    (void *) (INT_PTR) -1 /* IotLineFillSymbol::put_Offset */ ,
    (void *) (INT_PTR) -1 /* IotLineFillSymbol::get_LineSymbol */ ,
    (void *) (INT_PTR) -1 /* IotLineFillSymbol::put_LineSymbol */
};

const CInterfaceStubVtbl _IotLineFillSymbolStubVtbl =
{
    &IID_IotLineFillSymbol,
    &IotLineFillSymbol_ServerInfo,
    20,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotMarkerFillSymbol, ver. 0.0,
   GUID={0xB26681BD,0x81F8,0x43BF,{0xA2,0x29,0xAC,0xAA,0x36,0x23,0xB4,0x8F}} */

#pragma code_seg(".orpc")
static const unsigned short IotMarkerFillSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    476,
    504,
    532,
    560,
    588,
    616,
    252,
    280,
    308,
    336,
    1316,
    1344,
    868,
    896,
    1428,
    1456
    };

static const MIDL_STUBLESS_PROXY_INFO IotMarkerFillSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotMarkerFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotMarkerFillSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotMarkerFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(22) _IotMarkerFillSymbolProxyVtbl = 
{
    &IotMarkerFillSymbol_ProxyInfo,
    &IID_IotMarkerFillSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_FillColor */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_FillColor */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::get_OffsetX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::put_OffsetX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::get_OffsetY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::put_OffsetY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::get_SeparationX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::put_SeparationX */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::get_SeparationY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::put_SeparationY */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::get_MarkSymbol */ ,
    (void *) (INT_PTR) -1 /* IotMarkerFillSymbol::put_MarkSymbol */
};

const CInterfaceStubVtbl _IotMarkerFillSymbolStubVtbl =
{
    &IID_IotMarkerFillSymbol,
    &IotMarkerFillSymbol_ServerInfo,
    22,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotPicFillSymbol, ver. 0.0,
   GUID={0x4E814FCE,0x21F8,0x4C1F,{0xA7,0xA7,0xF5,0xBA,0x00,0xFF,0x33,0xF7}} */

#pragma code_seg(".orpc")
static const unsigned short IotPicFillSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    476,
    504,
    532,
    560,
    588,
    616,
    1484,
    1512,
    1540,
    1568,
    1596,
    1624
    };

static const MIDL_STUBLESS_PROXY_INFO IotPicFillSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotPicFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotPicFillSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotPicFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(18) _IotPicFillSymbolProxyVtbl = 
{
    &IotPicFillSymbol_ProxyInfo,
    &IID_IotPicFillSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_FillColor */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_FillColor */ ,
    (void *) (INT_PTR) -1 /* IotPicFillSymbol::get_PictureFile */ ,
    (void *) (INT_PTR) -1 /* IotPicFillSymbol::put_PictureFile */ ,
    (void *) (INT_PTR) -1 /* IotPicFillSymbol::get_BackgroundColor */ ,
    (void *) (INT_PTR) -1 /* IotPicFillSymbol::put_BackgroundColor */ ,
    (void *) (INT_PTR) -1 /* IotPicFillSymbol::get_TransparentColor */ ,
    (void *) (INT_PTR) -1 /* IotPicFillSymbol::put_TransparentColor */
};

const CInterfaceStubVtbl _IotPicFillSymbolStubVtbl =
{
    &IID_IotPicFillSymbol,
    &IotPicFillSymbol_ServerInfo,
    18,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotGradientFillSymbol, ver. 0.0,
   GUID={0x4E914FCE,0x21F8,0x4C1F,{0xA7,0x47,0xF5,0xBA,0x00,0xEF,0x33,0xA7}} */

#pragma code_seg(".orpc")
static const unsigned short IotGradientFillSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    476,
    504,
    532,
    560,
    588,
    616,
    1652,
    1680,
    1540,
    1568,
    1708,
    1736,
    1764,
    1792,
    1820,
    1848,
    1876,
    1904
    };

static const MIDL_STUBLESS_PROXY_INFO IotGradientFillSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotGradientFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotGradientFillSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotGradientFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(24) _IotGradientFillSymbolProxyVtbl = 
{
    &IotGradientFillSymbol_ProxyInfo,
    &IID_IotGradientFillSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_DrawOutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_OutLine */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::get_FillColor */ ,
    (void *) (INT_PTR) -1 /* IotFillSymbol::put_FillColor */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::get_BeginColor */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::put_BeginColor */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::get_EndColor */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::put_EndColor */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::get_GradientFillType */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::put_GradientFillType */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::get_SegmentCounts */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::put_SegmentCounts */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::get_Percent */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::put_Percent */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::get_Angle */ ,
    (void *) (INT_PTR) -1 /* IotGradientFillSymbol::put_Angle */
};

const CInterfaceStubVtbl _IotGradientFillSymbolStubVtbl =
{
    &IID_IotGradientFillSymbol,
    &IotGradientFillSymbol_ServerInfo,
    24,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotComplexMarkerSymbol, ver. 0.0,
   GUID={0x16F3B5D1,0x4723,0x4645,{0xA2,0xA8,0x36,0x9F,0x6D,0xFC,0xC9,0xE9}} */

#pragma code_seg(".orpc")
static const unsigned short IotComplexMarkerSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    84,
    112,
    140,
    168,
    196,
    224,
    252,
    280,
    308,
    336,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotComplexMarkerSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotComplexMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotComplexMarkerSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotComplexMarkerSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IotComplexMarkerSymbolProxyVtbl = 
{
    0,
    &IID_IotComplexMarkerSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotSymbol::get_Type */ ,
    0 /* forced delegation IotSymbol::get_Unit */ ,
    0 /* forced delegation IotSymbol::put_Unit */ ,
    0 /* forced delegation IotMarkerSymbol::get_Color */ ,
    0 /* forced delegation IotMarkerSymbol::put_Color */ ,
    0 /* forced delegation IotMarkerSymbol::get_OffsetX */ ,
    0 /* forced delegation IotMarkerSymbol::put_OffsetX */ ,
    0 /* forced delegation IotMarkerSymbol::get_OffsetY */ ,
    0 /* forced delegation IotMarkerSymbol::put_OffsetY */ ,
    0 /* forced delegation IotMarkerSymbol::get_Angle */ ,
    0 /* forced delegation IotMarkerSymbol::put_Angle */ ,
    0 /* forced delegation IotMarkerSymbol::get_Size */ ,
    0 /* forced delegation IotMarkerSymbol::put_Size */
};


static const PRPC_STUB_FUNCTION IotComplexMarkerSymbol_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotComplexMarkerSymbolStubVtbl =
{
    &IID_IotComplexMarkerSymbol,
    &IotComplexMarkerSymbol_ServerInfo,
    16,
    &IotComplexMarkerSymbol_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotComplexLineSymbol, ver. 0.0,
   GUID={0x8B0226DB,0x2624,0x45EF,{0xA1,0x13,0xA8,0xBC,0x1F,0x2E,0x7D,0x23}} */

#pragma code_seg(".orpc")
static const unsigned short IotComplexLineSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    364,
    392,
    420,
    448,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotComplexLineSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotComplexLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotComplexLineSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotComplexLineSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IotComplexLineSymbolProxyVtbl = 
{
    0,
    &IID_IotComplexLineSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotSymbol::get_Type */ ,
    0 /* forced delegation IotSymbol::get_Unit */ ,
    0 /* forced delegation IotSymbol::put_Unit */ ,
    0 /* forced delegation IotLineSymbol::get_LineWidth */ ,
    0 /* forced delegation IotLineSymbol::put_LineWidth */ ,
    0 /* forced delegation IotLineSymbol::get_Color */ ,
    0 /* forced delegation IotLineSymbol::put_Color */
};


static const PRPC_STUB_FUNCTION IotComplexLineSymbol_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotComplexLineSymbolStubVtbl =
{
    &IID_IotComplexLineSymbol,
    &IotComplexLineSymbol_ServerInfo,
    10,
    &IotComplexLineSymbol_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotComplexFillSymbol, ver. 0.0,
   GUID={0xD9CBB941,0x385C,0x4AF3,{0x8D,0xD8,0x50,0x3D,0xF6,0x71,0x03,0xE4}} */

#pragma code_seg(".orpc")
static const unsigned short IotComplexFillSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    476,
    504,
    532,
    560,
    588,
    616,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotComplexFillSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotComplexFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotComplexFillSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotComplexFillSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IotComplexFillSymbolProxyVtbl = 
{
    0,
    &IID_IotComplexFillSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotSymbol::get_Type */ ,
    0 /* forced delegation IotSymbol::get_Unit */ ,
    0 /* forced delegation IotSymbol::put_Unit */ ,
    0 /* forced delegation IotFillSymbol::get_DrawOutLine */ ,
    0 /* forced delegation IotFillSymbol::put_DrawOutLine */ ,
    0 /* forced delegation IotFillSymbol::get_OutLine */ ,
    0 /* forced delegation IotFillSymbol::put_OutLine */ ,
    0 /* forced delegation IotFillSymbol::get_FillColor */ ,
    0 /* forced delegation IotFillSymbol::put_FillColor */
};


static const PRPC_STUB_FUNCTION IotComplexFillSymbol_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotComplexFillSymbolStubVtbl =
{
    &IID_IotComplexFillSymbol,
    &IotComplexFillSymbol_ServerInfo,
    12,
    &IotComplexFillSymbol_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotCanvas, ver. 0.0,
   GUID={0x4E269D07,0x6C04,0x443B,{0xB5,0x60,0x6C,0xF8,0x41,0x92,0x62,0x08}} */

#pragma code_seg(".orpc")
static const unsigned short IotCanvas_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotCanvas_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotCanvas_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotCanvas_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotCanvas_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(3) _IotCanvasProxyVtbl = 
{
    0,
    &IID_IotCanvas,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IotCanvasStubVtbl =
{
    &IID_IotCanvas,
    &IotCanvas_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSymbolConvert, ver. 0.0,
   GUID={0x751B8D1B,0x9231,0x48F0,{0x8D,0xEA,0xCD,0x8B,0x82,0xF7,0xA7,0xE2}} */

#pragma code_seg(".orpc")
static const unsigned short IotSymbolConvert_FormatStringOffsetTable[] =
    {
    1932
    };

static const MIDL_STUBLESS_PROXY_INFO IotSymbolConvert_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSymbolConvert_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSymbolConvert_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSymbolConvert_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IotSymbolConvertProxyVtbl = 
{
    &IotSymbolConvert_ProxyInfo,
    &IID_IotSymbolConvert,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbolConvert::ConvertSymbol */
};

const CInterfaceStubVtbl _IotSymbolConvertStubVtbl =
{
    &IID_IotSymbolConvert,
    &IotSymbolConvert_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotTextSymbol, ver. 0.0,
   GUID={0x3D75BBF9,0x65B4,0x419C,{0x9E,0x02,0xA0,0xB1,0xD7,0x8D,0xDC,0xCF}} */

#pragma code_seg(".orpc")
static const unsigned short IotTextSymbol_FormatStringOffsetTable[] =
    {
    0,
    28,
    56,
    364,
    392,
    140,
    168,
    588,
    616,
    1972,
    2000
    };

static const MIDL_STUBLESS_PROXY_INFO IotTextSymbol_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotTextSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotTextSymbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotTextSymbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _IotTextSymbolProxyVtbl = 
{
    &IotTextSymbol_ProxyInfo,
    &IID_IotTextSymbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::get_Unit */ ,
    (void *) (INT_PTR) -1 /* IotSymbol::put_Unit */ ,
    (void *) (INT_PTR) -1 /* IotTextSymbol::get_Size */ ,
    (void *) (INT_PTR) -1 /* IotTextSymbol::put_Size */ ,
    (void *) (INT_PTR) -1 /* IotTextSymbol::get_Angle */ ,
    (void *) (INT_PTR) -1 /* IotTextSymbol::put_Angle */ ,
    (void *) (INT_PTR) -1 /* IotTextSymbol::get_TextColor */ ,
    (void *) (INT_PTR) -1 /* IotTextSymbol::put_TextColor */ ,
    (void *) (INT_PTR) -1 /* IotTextSymbol::get_Font */ ,
    (void *) (INT_PTR) -1 /* IotTextSymbol::put_Font */
};

const CInterfaceStubVtbl _IotTextSymbolStubVtbl =
{
    &IID_IotTextSymbol,
    &IotTextSymbol_ServerInfo,
    14,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSymbolLibLoader, ver. 0.0,
   GUID={0x8D3709D7,0x6DD5,0x4728,{0x8D,0xCC,0x8B,0x3A,0x5D,0x6A,0x7A,0x52}} */

#pragma code_seg(".orpc")
static const unsigned short IotSymbolLibLoader_FormatStringOffsetTable[] =
    {
    2028,
    2062
    };

static const MIDL_STUBLESS_PROXY_INFO IotSymbolLibLoader_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSymbolLibLoader_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSymbolLibLoader_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSymbolLibLoader_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IotSymbolLibLoaderProxyVtbl = 
{
    &IotSymbolLibLoader_ProxyInfo,
    &IID_IotSymbolLibLoader,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSymbolLibLoader::Open */ ,
    (void *) (INT_PTR) -1 /* IotSymbolLibLoader::GetSymbol */
};

const CInterfaceStubVtbl _IotSymbolLibLoaderStubVtbl =
{
    &IID_IotSymbolLibLoader,
    &IotSymbolLibLoader_ServerInfo,
    5,
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
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _otcDisplay_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IotSimpleLineSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotCanvasProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSimpleFillSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSymbolConvertProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotMarkerSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotComplexFillSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotHashLineSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotPicMarkerSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotCharMarkerSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotLineSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotFillSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotArrowMarkerSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotAdvLineSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotColorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotMarkerFillSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSimpleMarkerSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotPicFillSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotGradientFillSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotComplexMarkerSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSymbolLibLoaderProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotComplexLineSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotMarkerLineSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotLineFillSymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotTextSymbolProxyVtbl,
    0
};

const CInterfaceStubVtbl * _otcDisplay_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IotSimpleLineSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotCanvasStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSimpleFillSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSymbolConvertStubVtbl,
    ( CInterfaceStubVtbl *) &_IotMarkerSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotComplexFillSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotHashLineSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotPicMarkerSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotCharMarkerSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotLineSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotFillSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotArrowMarkerSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotAdvLineSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotColorStubVtbl,
    ( CInterfaceStubVtbl *) &_IotMarkerFillSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSimpleMarkerSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotPicFillSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotGradientFillSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotComplexMarkerSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSymbolLibLoaderStubVtbl,
    ( CInterfaceStubVtbl *) &_IotComplexLineSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotMarkerLineSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotLineFillSymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IotTextSymbolStubVtbl,
    0
};

PCInterfaceName const _otcDisplay_InterfaceNamesList[] = 
{
    "IotSimpleLineSymbol",
    "IotCanvas",
    "IotSimpleFillSymbol",
    "IotSymbolConvert",
    "IotMarkerSymbol",
    "IotSymbol",
    "IotComplexFillSymbol",
    "IotHashLineSymbol",
    "IotPicMarkerSymbol",
    "IotCharMarkerSymbol",
    "IotLineSymbol",
    "IotFillSymbol",
    "IotArrowMarkerSymbol",
    "IotAdvLineSymbol",
    "IotColor",
    "IotMarkerFillSymbol",
    "IotSimpleMarkerSymbol",
    "IotPicFillSymbol",
    "IotGradientFillSymbol",
    "IotComplexMarkerSymbol",
    "IotSymbolLibLoader",
    "IotComplexLineSymbol",
    "IotMarkerLineSymbol",
    "IotLineFillSymbol",
    "IotTextSymbol",
    0
};

const IID *  _otcDisplay_BaseIIDList[] = 
{
    0,
    0,
    &IID_IotFillSymbol,   /* forced */
    0,
    0,
    0,
    &IID_IotFillSymbol,   /* forced */
    &IID_IotLineSymbol,   /* forced */
    0,
    &IID_IotMarkerSymbol,   /* forced */
    0,
    0,
    &IID_IotMarkerSymbol,   /* forced */
    &IID_IotLineSymbol,   /* forced */
    0,
    0,
    0,
    0,
    0,
    &IID_IotMarkerSymbol,   /* forced */
    0,
    &IID_IotLineSymbol,   /* forced */
    0,
    0,
    0,
    0
};


#define _otcDisplay_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _otcDisplay, pIID, n)

int __stdcall _otcDisplay_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _otcDisplay, 25, 16 )
    IID_BS_LOOKUP_NEXT_TEST( _otcDisplay, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _otcDisplay, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _otcDisplay, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _otcDisplay, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _otcDisplay, 25, *pIndex )
    
}

const ExtendedProxyFileInfo otcDisplay_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _otcDisplay_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _otcDisplay_StubVtblList,
    (const PCInterfaceName * ) & _otcDisplay_InterfaceNamesList,
    (const IID ** ) & _otcDisplay_BaseIIDList,
    & _otcDisplay_IID_Lookup, 
    25,
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

