

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sun Mar 18 10:44:39 2012
 */
/* Compiler settings for .\otcGeodataModel.idl:
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


#include "otcGeodataModel.h"

#define TYPE_FORMAT_STRING_SIZE   1289                              
#define PROC_FORMAT_STRING_SIZE   1445                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   3            

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


extern const MIDL_SERVER_INFO IotWorkspaceFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotWorkspaceFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotRow_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotRow_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITmsWF_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITmsWF_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotField_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotField_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSimpleQuery_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSimpleQuery_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotCursor_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotCursor_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotFeatureCursor_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotFeatureCursor_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotShpWF_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotShpWF_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotIfeWF_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotIfeWF_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotRasterBlock_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotRasterBlock_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSelectionSet_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSelectionSet_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotSpatialReference_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotSpatialReference_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IotProjTransform_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IotProjTransform_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure OpenFromFile */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter filename */

/* 16 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter workspace */

/* 22 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 24 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 26 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 28 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 30 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 32 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OpenFolder */

/* 34 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 36 */	NdrFcLong( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x4 ),	/* 4 */
/* 42 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 44 */	NdrFcShort( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x8 ),	/* 8 */
/* 48 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 50 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 52 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 54 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter retWorkspace */

/* 56 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 58 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 60 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 62 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 64 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 66 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Table */

/* 68 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 70 */	NdrFcLong( 0x0 ),	/* 0 */
/* 74 */	NdrFcShort( 0x3 ),	/* 3 */
/* 76 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 78 */	NdrFcShort( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x8 ),	/* 8 */
/* 82 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 84 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 86 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 88 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */

	/* Return value */

/* 90 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 92 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 94 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_FieldCount */

/* 96 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 98 */	NdrFcLong( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0x4 ),	/* 4 */
/* 104 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 108 */	NdrFcShort( 0x24 ),	/* 36 */
/* 110 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 112 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 114 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 116 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 118 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 120 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 122 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Width */


	/* Procedure get_Length */


	/* Procedure get_ID */

/* 124 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 126 */	NdrFcLong( 0x0 ),	/* 0 */
/* 130 */	NdrFcShort( 0x5 ),	/* 5 */
/* 132 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x24 ),	/* 36 */
/* 138 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 140 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 142 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 148 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Field */

/* 152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x6 ),	/* 6 */
/* 160 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 162 */	NdrFcShort( 0x8 ),	/* 8 */
/* 164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 166 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 168 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 170 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 174 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 176 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 178 */	NdrFcShort( 0x54 ),	/* Type Offset=84 */

	/* Return value */

/* 180 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 182 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 184 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Value */

/* 186 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 188 */	NdrFcLong( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x7 ),	/* 7 */
/* 194 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 196 */	NdrFcShort( 0x8 ),	/* 8 */
/* 198 */	NdrFcShort( 0x8 ),	/* 8 */
/* 200 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 202 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 204 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 206 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 208 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 210 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 212 */	NdrFcShort( 0x45e ),	/* Type Offset=1118 */

	/* Return value */

/* 214 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 216 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 218 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Value */

/* 220 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 222 */	NdrFcLong( 0x0 ),	/* 0 */
/* 226 */	NdrFcShort( 0x8 ),	/* 8 */
/* 228 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 230 */	NdrFcShort( 0x8 ),	/* 8 */
/* 232 */	NdrFcShort( 0x8 ),	/* 8 */
/* 234 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 236 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 238 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 240 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter newVal */

/* 242 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 244 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 246 */	NdrFcShort( 0x46c ),	/* Type Offset=1132 */

	/* Return value */

/* 248 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 250 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 252 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Update */

/* 254 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 256 */	NdrFcLong( 0x0 ),	/* 0 */
/* 260 */	NdrFcShort( 0x9 ),	/* 9 */
/* 262 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 264 */	NdrFcShort( 0x0 ),	/* 0 */
/* 266 */	NdrFcShort( 0x8 ),	/* 8 */
/* 268 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 270 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 272 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 274 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Delete */

/* 276 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 278 */	NdrFcLong( 0x0 ),	/* 0 */
/* 282 */	NdrFcShort( 0xa ),	/* 10 */
/* 284 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 288 */	NdrFcShort( 0x8 ),	/* 8 */
/* 290 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 292 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 294 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 296 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Fields */


	/* Procedure get_Name */

/* 298 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 300 */	NdrFcLong( 0x0 ),	/* 0 */
/* 304 */	NdrFcShort( 0x3 ),	/* 3 */
/* 306 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 308 */	NdrFcShort( 0x0 ),	/* 0 */
/* 310 */	NdrFcShort( 0x8 ),	/* 8 */
/* 312 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 314 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 316 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 318 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */


	/* Return value */

/* 320 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 322 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 324 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Fields */


	/* Procedure put_Name */

/* 326 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 328 */	NdrFcLong( 0x0 ),	/* 0 */
/* 332 */	NdrFcShort( 0x4 ),	/* 4 */
/* 334 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 336 */	NdrFcShort( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0x8 ),	/* 8 */
/* 340 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 342 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 344 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 346 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */


	/* Return value */

/* 348 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 350 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 352 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Width */


	/* Procedure put_Length */

/* 354 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 356 */	NdrFcLong( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0x6 ),	/* 6 */
/* 362 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 364 */	NdrFcShort( 0x8 ),	/* 8 */
/* 366 */	NdrFcShort( 0x8 ),	/* 8 */
/* 368 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 370 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 372 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 376 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 378 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 380 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Type */

/* 382 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 384 */	NdrFcLong( 0x0 ),	/* 0 */
/* 388 */	NdrFcShort( 0x7 ),	/* 7 */
/* 390 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 394 */	NdrFcShort( 0x22 ),	/* 34 */
/* 396 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 398 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 400 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 402 */	NdrFcShort( 0x484 ),	/* Type Offset=1156 */

	/* Return value */

/* 404 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 406 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 408 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Type */

/* 410 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 412 */	NdrFcLong( 0x0 ),	/* 0 */
/* 416 */	NdrFcShort( 0x8 ),	/* 8 */
/* 418 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 420 */	NdrFcShort( 0x6 ),	/* 6 */
/* 422 */	NdrFcShort( 0x8 ),	/* 8 */
/* 424 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 426 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 428 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 430 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 432 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 434 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Precision */

/* 438 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 440 */	NdrFcLong( 0x0 ),	/* 0 */
/* 444 */	NdrFcShort( 0x9 ),	/* 9 */
/* 446 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x24 ),	/* 36 */
/* 452 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 454 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 456 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 458 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 460 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 462 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 464 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Precision */

/* 466 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 468 */	NdrFcLong( 0x0 ),	/* 0 */
/* 472 */	NdrFcShort( 0xa ),	/* 10 */
/* 474 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 476 */	NdrFcShort( 0x8 ),	/* 8 */
/* 478 */	NdrFcShort( 0x8 ),	/* 8 */
/* 480 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 482 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 484 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 486 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 488 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 490 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 492 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_WhereString */

/* 494 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 496 */	NdrFcLong( 0x0 ),	/* 0 */
/* 500 */	NdrFcShort( 0x5 ),	/* 5 */
/* 502 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x8 ),	/* 8 */
/* 508 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 510 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 512 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 514 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */

/* 516 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 518 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 520 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_WhereString */

/* 522 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 524 */	NdrFcLong( 0x0 ),	/* 0 */
/* 528 */	NdrFcShort( 0x6 ),	/* 6 */
/* 530 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 534 */	NdrFcShort( 0x8 ),	/* 8 */
/* 536 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 538 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 540 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 542 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 544 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 546 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 548 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddField */

/* 550 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 552 */	NdrFcLong( 0x0 ),	/* 0 */
/* 556 */	NdrFcShort( 0x7 ),	/* 7 */
/* 558 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 562 */	NdrFcShort( 0x8 ),	/* 8 */
/* 564 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter fieldname */

/* 566 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 568 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 570 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 572 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 574 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 576 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Table */

/* 578 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 580 */	NdrFcLong( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0x3 ),	/* 3 */
/* 586 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 590 */	NdrFcShort( 0x8 ),	/* 8 */
/* 592 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 594 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 596 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 598 */	NdrFcShort( 0x488 ),	/* Type Offset=1160 */

	/* Return value */

/* 600 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 602 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 604 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NextRow */

/* 606 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 608 */	NdrFcLong( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x4 ),	/* 4 */
/* 614 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 618 */	NdrFcShort( 0x8 ),	/* 8 */
/* 620 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter row */

/* 622 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 624 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 626 */	NdrFcShort( 0x49e ),	/* Type Offset=1182 */

	/* Return value */

/* 628 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 630 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 632 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsEOF */

/* 634 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 636 */	NdrFcLong( 0x0 ),	/* 0 */
/* 640 */	NdrFcShort( 0x5 ),	/* 5 */
/* 642 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 646 */	NdrFcShort( 0x22 ),	/* 34 */
/* 648 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter ret */

/* 650 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 652 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 654 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 656 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 658 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 660 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NextFeature */

/* 662 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 664 */	NdrFcLong( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x6 ),	/* 6 */
/* 670 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0x8 ),	/* 8 */
/* 676 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter retFeature */

/* 678 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 680 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 682 */	NdrFcShort( 0x4b8 ),	/* Type Offset=1208 */

	/* Return value */

/* 684 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 686 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 688 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DataType */

/* 690 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 696 */	NdrFcShort( 0x3 ),	/* 3 */
/* 698 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 702 */	NdrFcShort( 0x22 ),	/* 34 */
/* 704 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 706 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 708 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 710 */	NdrFcShort( 0x484 ),	/* Type Offset=1156 */

	/* Return value */

/* 712 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 714 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 716 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DataType */

/* 718 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 720 */	NdrFcLong( 0x0 ),	/* 0 */
/* 724 */	NdrFcShort( 0x4 ),	/* 4 */
/* 726 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 728 */	NdrFcShort( 0x6 ),	/* 6 */
/* 730 */	NdrFcShort( 0x8 ),	/* 8 */
/* 732 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 734 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 736 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 738 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 740 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 742 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 744 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Height */

/* 746 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 748 */	NdrFcLong( 0x0 ),	/* 0 */
/* 752 */	NdrFcShort( 0x7 ),	/* 7 */
/* 754 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 758 */	NdrFcShort( 0x24 ),	/* 36 */
/* 760 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 762 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 764 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 766 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 768 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 770 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 772 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Height */

/* 774 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 776 */	NdrFcLong( 0x0 ),	/* 0 */
/* 780 */	NdrFcShort( 0x8 ),	/* 8 */
/* 782 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 784 */	NdrFcShort( 0x8 ),	/* 8 */
/* 786 */	NdrFcShort( 0x8 ),	/* 8 */
/* 788 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 790 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 792 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 794 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 796 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 798 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 800 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetValue */

/* 802 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 804 */	NdrFcLong( 0x0 ),	/* 0 */
/* 808 */	NdrFcShort( 0x9 ),	/* 9 */
/* 810 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 812 */	NdrFcShort( 0x10 ),	/* 16 */
/* 814 */	NdrFcShort( 0x8 ),	/* 8 */
/* 816 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x4,		/* 4 */

	/* Parameter X */

/* 818 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 820 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 822 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 824 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 826 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 828 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter value */

/* 830 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 832 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 834 */	NdrFcShort( 0x45e ),	/* Type Offset=1118 */

	/* Return value */

/* 836 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 838 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 840 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SafeArray */

/* 842 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 844 */	NdrFcLong( 0x0 ),	/* 0 */
/* 848 */	NdrFcShort( 0xa ),	/* 10 */
/* 850 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 854 */	NdrFcShort( 0x8 ),	/* 8 */
/* 856 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 858 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 860 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 862 */	NdrFcShort( 0x45e ),	/* Type Offset=1118 */

	/* Return value */

/* 864 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 866 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SafeArray */

/* 870 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 872 */	NdrFcLong( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0xb ),	/* 11 */
/* 878 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x8 ),	/* 8 */
/* 884 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 886 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 888 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 890 */	NdrFcShort( 0x46c ),	/* Type Offset=1132 */

	/* Return value */

/* 892 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 894 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 896 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Count */

/* 898 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 900 */	NdrFcLong( 0x0 ),	/* 0 */
/* 904 */	NdrFcShort( 0x3 ),	/* 3 */
/* 906 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 910 */	NdrFcShort( 0x24 ),	/* 36 */
/* 912 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 914 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 916 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 920 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 922 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 924 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsEOF */

/* 926 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 928 */	NdrFcLong( 0x0 ),	/* 0 */
/* 932 */	NdrFcShort( 0x4 ),	/* 4 */
/* 934 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 938 */	NdrFcShort( 0x22 ),	/* 34 */
/* 940 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter ret */

/* 942 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 944 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 946 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 948 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 950 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 952 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ResetIndex */

/* 954 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 956 */	NdrFcLong( 0x0 ),	/* 0 */
/* 960 */	NdrFcShort( 0x5 ),	/* 5 */
/* 962 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 964 */	NdrFcShort( 0x0 ),	/* 0 */
/* 966 */	NdrFcShort( 0x8 ),	/* 8 */
/* 968 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 970 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 972 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 974 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NextID */

/* 976 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 978 */	NdrFcLong( 0x0 ),	/* 0 */
/* 982 */	NdrFcShort( 0x6 ),	/* 6 */
/* 984 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 988 */	NdrFcShort( 0x24 ),	/* 36 */
/* 990 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter id */

/* 992 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 994 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 996 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 998 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1000 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1002 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Add */

/* 1004 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1006 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1010 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1012 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1014 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1016 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1018 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter id */

/* 1020 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1022 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1024 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1026 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1028 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1030 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Table */

/* 1032 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1034 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1038 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1040 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1046 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1048 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1050 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1052 */	NdrFcShort( 0x488 ),	/* Type Offset=1160 */

	/* Return value */

/* 1054 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1056 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1058 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_FromSpatialReference */


	/* Procedure Clone */

/* 1060 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1062 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1066 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1068 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1070 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1072 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1074 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter spatialReference */

/* 1076 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1078 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1080 */	NdrFcShort( 0x4ce ),	/* Type Offset=1230 */

	/* Return value */


	/* Return value */

/* 1082 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1084 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1086 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ImportFromWkt */

/* 1088 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1090 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1094 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1096 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1098 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1100 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1102 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter wkt */

/* 1104 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1106 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1108 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter bSuccess */

/* 1110 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1112 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1114 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1116 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1118 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1120 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ImportFromESRI */

/* 1122 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1124 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1128 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1130 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1136 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter wkt */

/* 1138 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1140 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1142 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter bSuccess */

/* 1144 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1146 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1148 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1150 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1152 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1154 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExportToWkt */

/* 1156 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1158 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1162 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1170 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter wkt */

/* 1172 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1174 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1176 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */

/* 1178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1180 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsGeographic */

/* 1184 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1190 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1192 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1196 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1198 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bRet */

/* 1200 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1202 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1204 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1206 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1208 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1210 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsProjected */

/* 1212 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1214 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1218 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1220 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1224 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1226 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bRet */

/* 1228 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1230 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1232 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1234 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1236 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsSame */

/* 1240 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1242 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1246 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1248 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1252 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1254 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter other */

/* 1256 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1258 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1260 */	NdrFcShort( 0x4d2 ),	/* Type Offset=1234 */

	/* Parameter bSame */

/* 1262 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1264 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1266 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1268 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1270 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1272 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetGeogName */

/* 1274 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1276 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1280 */	NdrFcShort( 0xa ),	/* 10 */
/* 1282 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1286 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1288 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter name */

/* 1290 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1292 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1294 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */

/* 1296 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1298 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1300 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetProjName */

/* 1302 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1304 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1308 */	NdrFcShort( 0xb ),	/* 11 */
/* 1310 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1314 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1316 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter name */

/* 1318 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1320 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1322 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */

/* 1324 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1326 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ToSpatialReference */

/* 1330 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1336 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1338 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1342 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1344 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1346 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1348 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1350 */	NdrFcShort( 0x4ce ),	/* Type Offset=1230 */

	/* Return value */

/* 1352 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1354 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1356 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetSpatialReference */

/* 1358 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1360 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1364 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1366 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1370 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1372 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter from */

/* 1374 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1376 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1378 */	NdrFcShort( 0x4d2 ),	/* Type Offset=1234 */

	/* Parameter to */

/* 1380 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1382 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1384 */	NdrFcShort( 0x4d2 ),	/* Type Offset=1234 */

	/* Return value */

/* 1386 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1388 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1390 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Transform */

/* 1392 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1394 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1398 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1400 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1402 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1404 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1406 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x6,		/* 6 */

	/* Parameter count */

/* 1408 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1412 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter inX */

/* 1414 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1416 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1418 */	NdrFcShort( 0x4f0 ),	/* Type Offset=1264 */

	/* Parameter inY */

/* 1420 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1422 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1424 */	NdrFcShort( 0x4f0 ),	/* Type Offset=1264 */

	/* Parameter outX */

/* 1426 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 1428 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1430 */	NdrFcShort( 0x4fe ),	/* Type Offset=1278 */

	/* Parameter outY */

/* 1432 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 1434 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1436 */	NdrFcShort( 0x4fe ),	/* Type Offset=1278 */

	/* Return value */

/* 1438 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1440 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1442 */	0x8,		/* FC_LONG */
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
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0xc ),	/* Offset= 12 (16) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  8 */	NdrFcShort( 0x2 ),	/* 2 */
/* 10 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 14 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 16 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 18 */	NdrFcShort( 0x8 ),	/* 8 */
/* 20 */	NdrFcShort( 0xfff2 ),	/* Offset= -14 (6) */
/* 22 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 24 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 26 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */
/* 30 */	NdrFcShort( 0x4 ),	/* 4 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (2) */
/* 36 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 38 */	NdrFcShort( 0x2 ),	/* Offset= 2 (40) */
/* 40 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 42 */	NdrFcLong( 0xdc845e45 ),	/* -595304891 */
/* 46 */	NdrFcShort( 0x7e27 ),	/* 32295 */
/* 48 */	NdrFcShort( 0x40cd ),	/* 16589 */
/* 50 */	0xaf,		/* 175 */
			0xfe,		/* 254 */
/* 52 */	0xa,		/* 10 */
			0x19,		/* 25 */
/* 54 */	0x24,		/* 36 */
			0x6d,		/* 109 */
/* 56 */	0x4c,		/* 76 */
			0x84,		/* 132 */
/* 58 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 60 */	NdrFcShort( 0x2 ),	/* Offset= 2 (62) */
/* 62 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 64 */	NdrFcLong( 0x90993c2c ),	/* -1869005780 */
/* 68 */	NdrFcShort( 0x8725 ),	/* -30939 */
/* 70 */	NdrFcShort( 0x4c0b ),	/* 19467 */
/* 72 */	0x82,		/* 130 */
			0x2c,		/* 44 */
/* 74 */	0x8c,		/* 140 */
			0x8f,		/* 143 */
/* 76 */	0xe3,		/* 227 */
			0xe,		/* 14 */
/* 78 */	0x2f,		/* 47 */
			0x71,		/* 113 */
/* 80 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 82 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 84 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 86 */	NdrFcShort( 0x2 ),	/* Offset= 2 (88) */
/* 88 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 90 */	NdrFcLong( 0x5dc04615 ),	/* 1572881941 */
/* 94 */	NdrFcShort( 0xeb7d ),	/* -5251 */
/* 96 */	NdrFcShort( 0x45a2 ),	/* 17826 */
/* 98 */	0xa4,		/* 164 */
			0x5,		/* 5 */
/* 100 */	0x2d,		/* 45 */
			0x79,		/* 121 */
/* 102 */	0xbb,		/* 187 */
			0xa4,		/* 164 */
/* 104 */	0xd2,		/* 210 */
			0xf7,		/* 247 */
/* 106 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 108 */	NdrFcShort( 0x3f2 ),	/* Offset= 1010 (1118) */
/* 110 */	
			0x13, 0x0,	/* FC_OP */
/* 112 */	NdrFcShort( 0x3da ),	/* Offset= 986 (1098) */
/* 114 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 116 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 118 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 120 */	NdrFcShort( 0x2 ),	/* Offset= 2 (122) */
/* 122 */	NdrFcShort( 0x10 ),	/* 16 */
/* 124 */	NdrFcShort( 0x2f ),	/* 47 */
/* 126 */	NdrFcLong( 0x14 ),	/* 20 */
/* 130 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 132 */	NdrFcLong( 0x3 ),	/* 3 */
/* 136 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 138 */	NdrFcLong( 0x11 ),	/* 17 */
/* 142 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 144 */	NdrFcLong( 0x2 ),	/* 2 */
/* 148 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 150 */	NdrFcLong( 0x4 ),	/* 4 */
/* 154 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 156 */	NdrFcLong( 0x5 ),	/* 5 */
/* 160 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 162 */	NdrFcLong( 0xb ),	/* 11 */
/* 166 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 168 */	NdrFcLong( 0xa ),	/* 10 */
/* 172 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 174 */	NdrFcLong( 0x6 ),	/* 6 */
/* 178 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (410) */
/* 180 */	NdrFcLong( 0x7 ),	/* 7 */
/* 184 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 186 */	NdrFcLong( 0x8 ),	/* 8 */
/* 190 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (416) */
/* 192 */	NdrFcLong( 0xd ),	/* 13 */
/* 196 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (420) */
/* 198 */	NdrFcLong( 0x9 ),	/* 9 */
/* 202 */	NdrFcShort( 0xec ),	/* Offset= 236 (438) */
/* 204 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 208 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (456) */
/* 210 */	NdrFcLong( 0x24 ),	/* 36 */
/* 214 */	NdrFcShort( 0x32a ),	/* Offset= 810 (1024) */
/* 216 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 220 */	NdrFcShort( 0x324 ),	/* Offset= 804 (1024) */
/* 222 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 226 */	NdrFcShort( 0x322 ),	/* Offset= 802 (1028) */
/* 228 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 232 */	NdrFcShort( 0x320 ),	/* Offset= 800 (1032) */
/* 234 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 238 */	NdrFcShort( 0x31e ),	/* Offset= 798 (1036) */
/* 240 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 244 */	NdrFcShort( 0x31c ),	/* Offset= 796 (1040) */
/* 246 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 250 */	NdrFcShort( 0x31a ),	/* Offset= 794 (1044) */
/* 252 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 256 */	NdrFcShort( 0x318 ),	/* Offset= 792 (1048) */
/* 258 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 262 */	NdrFcShort( 0x302 ),	/* Offset= 770 (1032) */
/* 264 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 268 */	NdrFcShort( 0x300 ),	/* Offset= 768 (1036) */
/* 270 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 274 */	NdrFcShort( 0x30a ),	/* Offset= 778 (1052) */
/* 276 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 280 */	NdrFcShort( 0x300 ),	/* Offset= 768 (1048) */
/* 282 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 286 */	NdrFcShort( 0x302 ),	/* Offset= 770 (1056) */
/* 288 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 292 */	NdrFcShort( 0x300 ),	/* Offset= 768 (1060) */
/* 294 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 298 */	NdrFcShort( 0x2fe ),	/* Offset= 766 (1064) */
/* 300 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 304 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (1068) */
/* 306 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 310 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (1072) */
/* 312 */	NdrFcLong( 0x10 ),	/* 16 */
/* 316 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 318 */	NdrFcLong( 0x12 ),	/* 18 */
/* 322 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 324 */	NdrFcLong( 0x13 ),	/* 19 */
/* 328 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 330 */	NdrFcLong( 0x15 ),	/* 21 */
/* 334 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 336 */	NdrFcLong( 0x16 ),	/* 22 */
/* 340 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 342 */	NdrFcLong( 0x17 ),	/* 23 */
/* 346 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 348 */	NdrFcLong( 0xe ),	/* 14 */
/* 352 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (1080) */
/* 354 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 358 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (1090) */
/* 360 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 364 */	NdrFcShort( 0x2da ),	/* Offset= 730 (1094) */
/* 366 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 370 */	NdrFcShort( 0x296 ),	/* Offset= 662 (1032) */
/* 372 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 376 */	NdrFcShort( 0x294 ),	/* Offset= 660 (1036) */
/* 378 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 382 */	NdrFcShort( 0x292 ),	/* Offset= 658 (1040) */
/* 384 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 388 */	NdrFcShort( 0x288 ),	/* Offset= 648 (1036) */
/* 390 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 394 */	NdrFcShort( 0x282 ),	/* Offset= 642 (1036) */
/* 396 */	NdrFcLong( 0x0 ),	/* 0 */
/* 400 */	NdrFcShort( 0x0 ),	/* Offset= 0 (400) */
/* 402 */	NdrFcLong( 0x1 ),	/* 1 */
/* 406 */	NdrFcShort( 0x0 ),	/* Offset= 0 (406) */
/* 408 */	NdrFcShort( 0xffff ),	/* Offset= -1 (407) */
/* 410 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 412 */	NdrFcShort( 0x8 ),	/* 8 */
/* 414 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 416 */	
			0x13, 0x0,	/* FC_OP */
/* 418 */	NdrFcShort( 0xfe6e ),	/* Offset= -402 (16) */
/* 420 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 430 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 432 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 434 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 436 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 438 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 440 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 444 */	NdrFcShort( 0x0 ),	/* 0 */
/* 446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 448 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 450 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 452 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 454 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 456 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 458 */	NdrFcShort( 0x2 ),	/* Offset= 2 (460) */
/* 460 */	
			0x13, 0x0,	/* FC_OP */
/* 462 */	NdrFcShort( 0x220 ),	/* Offset= 544 (1006) */
/* 464 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 466 */	NdrFcShort( 0x18 ),	/* 24 */
/* 468 */	NdrFcShort( 0xa ),	/* 10 */
/* 470 */	NdrFcLong( 0x8 ),	/* 8 */
/* 474 */	NdrFcShort( 0x58 ),	/* Offset= 88 (562) */
/* 476 */	NdrFcLong( 0xd ),	/* 13 */
/* 480 */	NdrFcShort( 0x8a ),	/* Offset= 138 (618) */
/* 482 */	NdrFcLong( 0x9 ),	/* 9 */
/* 486 */	NdrFcShort( 0xb8 ),	/* Offset= 184 (670) */
/* 488 */	NdrFcLong( 0xc ),	/* 12 */
/* 492 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (716) */
/* 494 */	NdrFcLong( 0x24 ),	/* 36 */
/* 498 */	NdrFcShort( 0x138 ),	/* Offset= 312 (810) */
/* 500 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 504 */	NdrFcShort( 0x154 ),	/* Offset= 340 (844) */
/* 506 */	NdrFcLong( 0x10 ),	/* 16 */
/* 510 */	NdrFcShort( 0x16c ),	/* Offset= 364 (874) */
/* 512 */	NdrFcLong( 0x2 ),	/* 2 */
/* 516 */	NdrFcShort( 0x184 ),	/* Offset= 388 (904) */
/* 518 */	NdrFcLong( 0x3 ),	/* 3 */
/* 522 */	NdrFcShort( 0x19c ),	/* Offset= 412 (934) */
/* 524 */	NdrFcLong( 0x14 ),	/* 20 */
/* 528 */	NdrFcShort( 0x1b4 ),	/* Offset= 436 (964) */
/* 530 */	NdrFcShort( 0xffff ),	/* Offset= -1 (529) */
/* 532 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 534 */	NdrFcShort( 0x4 ),	/* 4 */
/* 536 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 542 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 544 */	NdrFcShort( 0x4 ),	/* 4 */
/* 546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 548 */	NdrFcShort( 0x1 ),	/* 1 */
/* 550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	0x13, 0x0,	/* FC_OP */
/* 556 */	NdrFcShort( 0xfde4 ),	/* Offset= -540 (16) */
/* 558 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 560 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 562 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 564 */	NdrFcShort( 0x8 ),	/* 8 */
/* 566 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 568 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 570 */	NdrFcShort( 0x4 ),	/* 4 */
/* 572 */	NdrFcShort( 0x4 ),	/* 4 */
/* 574 */	0x11, 0x0,	/* FC_RP */
/* 576 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (532) */
/* 578 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 580 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 582 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 594 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 596 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 598 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 600 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 608 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 612 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 614 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (582) */
/* 616 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 618 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 620 */	NdrFcShort( 0x8 ),	/* 8 */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 624 */	NdrFcShort( 0x6 ),	/* Offset= 6 (630) */
/* 626 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 628 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 630 */	
			0x11, 0x0,	/* FC_RP */
/* 632 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (600) */
/* 634 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 636 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 644 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 646 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 648 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 650 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 652 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 660 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 664 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 666 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (634) */
/* 668 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 670 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 672 */	NdrFcShort( 0x8 ),	/* 8 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x6 ),	/* Offset= 6 (682) */
/* 678 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 680 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 682 */	
			0x11, 0x0,	/* FC_RP */
/* 684 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (652) */
/* 686 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 688 */	NdrFcShort( 0x4 ),	/* 4 */
/* 690 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 694 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 696 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 698 */	NdrFcShort( 0x4 ),	/* 4 */
/* 700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 702 */	NdrFcShort( 0x1 ),	/* 1 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 708 */	0x13, 0x0,	/* FC_OP */
/* 710 */	NdrFcShort( 0x184 ),	/* Offset= 388 (1098) */
/* 712 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 714 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 716 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 718 */	NdrFcShort( 0x8 ),	/* 8 */
/* 720 */	NdrFcShort( 0x0 ),	/* 0 */
/* 722 */	NdrFcShort( 0x6 ),	/* Offset= 6 (728) */
/* 724 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 726 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 728 */	
			0x11, 0x0,	/* FC_RP */
/* 730 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (686) */
/* 732 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 734 */	NdrFcLong( 0x2f ),	/* 47 */
/* 738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 744 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 746 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 748 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 750 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 752 */	NdrFcShort( 0x1 ),	/* 1 */
/* 754 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 756 */	NdrFcShort( 0x4 ),	/* 4 */
/* 758 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 760 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 762 */	NdrFcShort( 0x10 ),	/* 16 */
/* 764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 766 */	NdrFcShort( 0xa ),	/* Offset= 10 (776) */
/* 768 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 770 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 772 */	NdrFcShort( 0xffd8 ),	/* Offset= -40 (732) */
/* 774 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 776 */	
			0x13, 0x0,	/* FC_OP */
/* 778 */	NdrFcShort( 0xffe4 ),	/* Offset= -28 (750) */
/* 780 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 782 */	NdrFcShort( 0x4 ),	/* 4 */
/* 784 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 788 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 790 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 792 */	NdrFcShort( 0x4 ),	/* 4 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 796 */	NdrFcShort( 0x1 ),	/* 1 */
/* 798 */	NdrFcShort( 0x0 ),	/* 0 */
/* 800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 802 */	0x13, 0x0,	/* FC_OP */
/* 804 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (760) */
/* 806 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 808 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 810 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 812 */	NdrFcShort( 0x8 ),	/* 8 */
/* 814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 816 */	NdrFcShort( 0x6 ),	/* Offset= 6 (822) */
/* 818 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 820 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 822 */	
			0x11, 0x0,	/* FC_RP */
/* 824 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (780) */
/* 826 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 828 */	NdrFcShort( 0x8 ),	/* 8 */
/* 830 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 832 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 834 */	NdrFcShort( 0x10 ),	/* 16 */
/* 836 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 838 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 840 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (826) */
			0x5b,		/* FC_END */
/* 844 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 846 */	NdrFcShort( 0x18 ),	/* 24 */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0xa ),	/* Offset= 10 (860) */
/* 852 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 854 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 856 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (832) */
/* 858 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 860 */	
			0x11, 0x0,	/* FC_RP */
/* 862 */	NdrFcShort( 0xfefa ),	/* Offset= -262 (600) */
/* 864 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 866 */	NdrFcShort( 0x1 ),	/* 1 */
/* 868 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 870 */	NdrFcShort( 0x0 ),	/* 0 */
/* 872 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 874 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 876 */	NdrFcShort( 0x8 ),	/* 8 */
/* 878 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 880 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 882 */	NdrFcShort( 0x4 ),	/* 4 */
/* 884 */	NdrFcShort( 0x4 ),	/* 4 */
/* 886 */	0x13, 0x0,	/* FC_OP */
/* 888 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (864) */
/* 890 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 892 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 894 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 896 */	NdrFcShort( 0x2 ),	/* 2 */
/* 898 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 902 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 904 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 906 */	NdrFcShort( 0x8 ),	/* 8 */
/* 908 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 912 */	NdrFcShort( 0x4 ),	/* 4 */
/* 914 */	NdrFcShort( 0x4 ),	/* 4 */
/* 916 */	0x13, 0x0,	/* FC_OP */
/* 918 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (894) */
/* 920 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 922 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 924 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 926 */	NdrFcShort( 0x4 ),	/* 4 */
/* 928 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 932 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 934 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 936 */	NdrFcShort( 0x8 ),	/* 8 */
/* 938 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 940 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 942 */	NdrFcShort( 0x4 ),	/* 4 */
/* 944 */	NdrFcShort( 0x4 ),	/* 4 */
/* 946 */	0x13, 0x0,	/* FC_OP */
/* 948 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (924) */
/* 950 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 952 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 954 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 956 */	NdrFcShort( 0x8 ),	/* 8 */
/* 958 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 962 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 964 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 966 */	NdrFcShort( 0x8 ),	/* 8 */
/* 968 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 970 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 972 */	NdrFcShort( 0x4 ),	/* 4 */
/* 974 */	NdrFcShort( 0x4 ),	/* 4 */
/* 976 */	0x13, 0x0,	/* FC_OP */
/* 978 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (954) */
/* 980 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 982 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 984 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 986 */	NdrFcShort( 0x8 ),	/* 8 */
/* 988 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 990 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 992 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 994 */	NdrFcShort( 0x8 ),	/* 8 */
/* 996 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 998 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 1000 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1002 */	NdrFcShort( 0xffee ),	/* Offset= -18 (984) */
/* 1004 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1006 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1008 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1010 */	NdrFcShort( 0xffee ),	/* Offset= -18 (992) */
/* 1012 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1012) */
/* 1014 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1016 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1018 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1020 */	NdrFcShort( 0xfdd4 ),	/* Offset= -556 (464) */
/* 1022 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1024 */	
			0x13, 0x0,	/* FC_OP */
/* 1026 */	NdrFcShort( 0xfef6 ),	/* Offset= -266 (760) */
/* 1028 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1030 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 1032 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1034 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1036 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1038 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1040 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1042 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 1044 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1046 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 1048 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1050 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 1052 */	
			0x13, 0x0,	/* FC_OP */
/* 1054 */	NdrFcShort( 0xfd7c ),	/* Offset= -644 (410) */
/* 1056 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1058 */	NdrFcShort( 0xfd7e ),	/* Offset= -642 (416) */
/* 1060 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1062 */	NdrFcShort( 0xfe20 ),	/* Offset= -480 (582) */
/* 1064 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1066 */	NdrFcShort( 0xfe50 ),	/* Offset= -432 (634) */
/* 1068 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1070 */	NdrFcShort( 0xfd9a ),	/* Offset= -614 (456) */
/* 1072 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1074 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1076) */
/* 1076 */	
			0x13, 0x0,	/* FC_OP */
/* 1078 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1098) */
/* 1080 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1082 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1084 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1086 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1088 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1090 */	
			0x13, 0x0,	/* FC_OP */
/* 1092 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1080) */
/* 1094 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1096 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1098 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1100 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1104 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1104) */
/* 1106 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1108 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1110 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1112 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1114 */	NdrFcShort( 0xfc18 ),	/* Offset= -1000 (114) */
/* 1116 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1118 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1120 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1122 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1126 */	NdrFcShort( 0xfc08 ),	/* Offset= -1016 (110) */
/* 1128 */	
			0x12, 0x0,	/* FC_UP */
/* 1130 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (1098) */
/* 1132 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1134 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1136 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1140 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1128) */
/* 1142 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1144 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1146) */
/* 1146 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1150 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1154 */	NdrFcShort( 0xfd1e ),	/* Offset= -738 (416) */
/* 1156 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1158 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 1160 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1162 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1164) */
/* 1164 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1166 */	NdrFcLong( 0x90993c2c ),	/* -1869005780 */
/* 1170 */	NdrFcShort( 0x8725 ),	/* -30939 */
/* 1172 */	NdrFcShort( 0x4c0b ),	/* 19467 */
/* 1174 */	0x82,		/* 130 */
			0x2c,		/* 44 */
/* 1176 */	0x8c,		/* 140 */
			0x8f,		/* 143 */
/* 1178 */	0xe3,		/* 227 */
			0xe,		/* 14 */
/* 1180 */	0x2f,		/* 47 */
			0x71,		/* 113 */
/* 1182 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1184 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1186) */
/* 1186 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1188 */	NdrFcLong( 0x434c180f ),	/* 1129060367 */
/* 1192 */	NdrFcShort( 0xb61 ),	/* 2913 */
/* 1194 */	NdrFcShort( 0x4428 ),	/* 17448 */
/* 1196 */	0xbe,		/* 190 */
			0xa0,		/* 160 */
/* 1198 */	0x49,		/* 73 */
			0x2,		/* 2 */
/* 1200 */	0xc6,		/* 198 */
			0xa2,		/* 162 */
/* 1202 */	0x60,		/* 96 */
			0x6,		/* 6 */
/* 1204 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1206 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1208 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1210 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1212) */
/* 1212 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1214 */	NdrFcLong( 0xbfc52bec ),	/* -1077597204 */
/* 1218 */	NdrFcShort( 0x8b0 ),	/* 2224 */
/* 1220 */	NdrFcShort( 0x4912 ),	/* 18706 */
/* 1222 */	0x9b,		/* 155 */
			0x3c,		/* 60 */
/* 1224 */	0x95,		/* 149 */
			0xf5,		/* 245 */
/* 1226 */	0x13,		/* 19 */
			0xd4,		/* 212 */
/* 1228 */	0xad,		/* 173 */
			0xbe,		/* 190 */
/* 1230 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1232 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1234) */
/* 1234 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1236 */	NdrFcLong( 0x3c6aaef9 ),	/* 1013624569 */
/* 1240 */	NdrFcShort( 0x400b ),	/* 16395 */
/* 1242 */	NdrFcShort( 0x4c15 ),	/* 19477 */
/* 1244 */	0xa9,		/* 169 */
			0xa3,		/* 163 */
/* 1246 */	0xb3,		/* 179 */
			0x1b,		/* 27 */
/* 1248 */	0x6e,		/* 110 */
			0x79,		/* 121 */
/* 1250 */	0x15,		/* 21 */
			0x4a,		/* 74 */
/* 1252 */	
			0x11, 0x0,	/* FC_RP */
/* 1254 */	NdrFcShort( 0xa ),	/* Offset= 10 (1264) */
/* 1256 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1258 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1260) */
/* 1260 */	
			0x12, 0x0,	/* FC_UP */
/* 1262 */	NdrFcShort( 0xff00 ),	/* Offset= -256 (1006) */
/* 1264 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1266 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1268 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1272 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (1256) */
/* 1274 */	
			0x11, 0x0,	/* FC_RP */
/* 1276 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1278) */
/* 1278 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1280 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1282 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1286 */	NdrFcShort( 0xfcc2 ),	/* Offset= -830 (456) */

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
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            },
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            }

        };



/* Standard interface: __MIDL_itf_otcGeodataModel_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IotWorkspaceFactory, ver. 0.0,
   GUID={0xC45AEEAB,0xA045,0x473b,{0xA1,0x43,0xBE,0xA2,0x19,0xA6,0xE6,0x91}} */

#pragma code_seg(".orpc")
static const unsigned short IotWorkspaceFactory_FormatStringOffsetTable[] =
    {
    0,
    34
    };

static const MIDL_STUBLESS_PROXY_INFO IotWorkspaceFactory_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotWorkspaceFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotWorkspaceFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotWorkspaceFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IotWorkspaceFactoryProxyVtbl = 
{
    &IotWorkspaceFactory_ProxyInfo,
    &IID_IotWorkspaceFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotWorkspaceFactory::OpenFromFile */ ,
    (void *) (INT_PTR) -1 /* IotWorkspaceFactory::OpenFolder */
};

const CInterfaceStubVtbl _IotWorkspaceFactoryStubVtbl =
{
    &IID_IotWorkspaceFactory,
    &IotWorkspaceFactory_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotRow, ver. 0.0,
   GUID={0x434C180F,0x0B61,0x4428,{0xBE,0xA0,0x49,0x02,0xC6,0xA2,0x60,0x06}} */

#pragma code_seg(".orpc")
static const unsigned short IotRow_FormatStringOffsetTable[] =
    {
    68,
    96,
    124,
    152,
    186,
    220,
    254,
    276
    };

static const MIDL_STUBLESS_PROXY_INFO IotRow_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotRow_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotRow_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotRow_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IotRowProxyVtbl = 
{
    &IotRow_ProxyInfo,
    &IID_IotRow,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotRow::get_Table */ ,
    (void *) (INT_PTR) -1 /* IotRow::get_FieldCount */ ,
    (void *) (INT_PTR) -1 /* IotRow::get_ID */ ,
    (void *) (INT_PTR) -1 /* IotRow::get_Field */ ,
    (void *) (INT_PTR) -1 /* IotRow::get_Value */ ,
    (void *) (INT_PTR) -1 /* IotRow::put_Value */ ,
    (void *) (INT_PTR) -1 /* IotRow::Update */ ,
    (void *) (INT_PTR) -1 /* IotRow::Delete */
};

const CInterfaceStubVtbl _IotRowStubVtbl =
{
    &IID_IotRow,
    &IotRow_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ITmsWF, ver. 0.0,
   GUID={0xC4424A1C,0xC3D8,0x4D65,{0x91,0xD0,0x75,0x57,0x3C,0x2E,0xAF,0x67}} */

#pragma code_seg(".orpc")
static const unsigned short ITmsWF_FormatStringOffsetTable[] =
    {
    0,
    34,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ITmsWF_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITmsWF_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITmsWF_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITmsWF_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _ITmsWFProxyVtbl = 
{
    0,
    &IID_ITmsWF,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotWorkspaceFactory::OpenFromFile */ ,
    0 /* forced delegation IotWorkspaceFactory::OpenFolder */
};


static const PRPC_STUB_FUNCTION ITmsWF_table[] =
{
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _ITmsWFStubVtbl =
{
    &IID_ITmsWF,
    &ITmsWF_ServerInfo,
    5,
    &ITmsWF_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotField, ver. 0.0,
   GUID={0x5DC04615,0xEB7D,0x45A2,{0xA4,0x05,0x2D,0x79,0xBB,0xA4,0xD2,0xF7}} */

#pragma code_seg(".orpc")
static const unsigned short IotField_FormatStringOffsetTable[] =
    {
    298,
    326,
    124,
    354,
    382,
    410,
    438,
    466
    };

static const MIDL_STUBLESS_PROXY_INFO IotField_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotField_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotField_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotField_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IotFieldProxyVtbl = 
{
    &IotField_ProxyInfo,
    &IID_IotField,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotField::get_Name */ ,
    (void *) (INT_PTR) -1 /* IotField::put_Name */ ,
    (void *) (INT_PTR) -1 /* IotField::get_Length */ ,
    (void *) (INT_PTR) -1 /* IotField::put_Length */ ,
    (void *) (INT_PTR) -1 /* IotField::get_Type */ ,
    (void *) (INT_PTR) -1 /* IotField::put_Type */ ,
    (void *) (INT_PTR) -1 /* IotField::get_Precision */ ,
    (void *) (INT_PTR) -1 /* IotField::put_Precision */
};

const CInterfaceStubVtbl _IotFieldStubVtbl =
{
    &IID_IotField,
    &IotField_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSimpleQuery, ver. 0.0,
   GUID={0xCEFB51F2,0x2462,0x477C,{0x90,0x37,0x69,0xA0,0x6F,0x64,0x63,0x2A}} */

#pragma code_seg(".orpc")
static const unsigned short IotSimpleQuery_FormatStringOffsetTable[] =
    {
    298,
    326,
    494,
    522,
    550
    };

static const MIDL_STUBLESS_PROXY_INFO IotSimpleQuery_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSimpleQuery_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSimpleQuery_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSimpleQuery_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IotSimpleQueryProxyVtbl = 
{
    &IotSimpleQuery_ProxyInfo,
    &IID_IotSimpleQuery,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSimpleQuery::get_Fields */ ,
    (void *) (INT_PTR) -1 /* IotSimpleQuery::put_Fields */ ,
    (void *) (INT_PTR) -1 /* IotSimpleQuery::get_WhereString */ ,
    (void *) (INT_PTR) -1 /* IotSimpleQuery::put_WhereString */ ,
    (void *) (INT_PTR) -1 /* IotSimpleQuery::AddField */
};

const CInterfaceStubVtbl _IotSimpleQueryStubVtbl =
{
    &IID_IotSimpleQuery,
    &IotSimpleQuery_ServerInfo,
    8,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotCursor, ver. 0.0,
   GUID={0x56EBD89B,0x77FC,0x47f8,{0x97,0x5C,0x0C,0xFB,0xEF,0xAB,0x72,0xE3}} */

#pragma code_seg(".orpc")
static const unsigned short IotCursor_FormatStringOffsetTable[] =
    {
    578,
    606,
    634
    };

static const MIDL_STUBLESS_PROXY_INFO IotCursor_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotCursor_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotCursor_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotCursor_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IotCursorProxyVtbl = 
{
    &IotCursor_ProxyInfo,
    &IID_IotCursor,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotCursor::get_Table */ ,
    (void *) (INT_PTR) -1 /* IotCursor::NextRow */ ,
    (void *) (INT_PTR) -1 /* IotCursor::IsEOF */
};

const CInterfaceStubVtbl _IotCursorStubVtbl =
{
    &IID_IotCursor,
    &IotCursor_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotFeatureCursor, ver. 0.0,
   GUID={0x0CCE34BB,0x0DF4,0x453E,{0x9B,0xE9,0x41,0x09,0x20,0x9C,0xB3,0x1F}} */

#pragma code_seg(".orpc")
static const unsigned short IotFeatureCursor_FormatStringOffsetTable[] =
    {
    578,
    606,
    634,
    662
    };

static const MIDL_STUBLESS_PROXY_INFO IotFeatureCursor_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotFeatureCursor_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotFeatureCursor_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotFeatureCursor_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IotFeatureCursorProxyVtbl = 
{
    &IotFeatureCursor_ProxyInfo,
    &IID_IotFeatureCursor,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotCursor::get_Table */ ,
    (void *) (INT_PTR) -1 /* IotCursor::NextRow */ ,
    (void *) (INT_PTR) -1 /* IotCursor::IsEOF */ ,
    (void *) (INT_PTR) -1 /* IotFeatureCursor::NextFeature */
};

const CInterfaceStubVtbl _IotFeatureCursorStubVtbl =
{
    &IID_IotFeatureCursor,
    &IotFeatureCursor_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotShpWF, ver. 0.0,
   GUID={0x108AA1D4,0x8661,0x43E0,{0xB1,0xCD,0xD4,0xEF,0x32,0x05,0x67,0xD7}} */

#pragma code_seg(".orpc")
static const unsigned short IotShpWF_FormatStringOffsetTable[] =
    {
    0,
    34,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotShpWF_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotShpWF_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotShpWF_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotShpWF_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IotShpWFProxyVtbl = 
{
    0,
    &IID_IotShpWF,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotWorkspaceFactory::OpenFromFile */ ,
    0 /* forced delegation IotWorkspaceFactory::OpenFolder */
};


static const PRPC_STUB_FUNCTION IotShpWF_table[] =
{
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotShpWFStubVtbl =
{
    &IID_IotShpWF,
    &IotShpWF_ServerInfo,
    5,
    &IotShpWF_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotIfeWF, ver. 0.0,
   GUID={0x68C740E9,0xF043,0x49D5,{0xA7,0xA6,0xB5,0xA7,0x12,0xCC,0x5E,0xC5}} */

#pragma code_seg(".orpc")
static const unsigned short IotIfeWF_FormatStringOffsetTable[] =
    {
    0,
    34,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IotIfeWF_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotIfeWF_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotIfeWF_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotIfeWF_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IotIfeWFProxyVtbl = 
{
    0,
    &IID_IotIfeWF,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IotWorkspaceFactory::OpenFromFile */ ,
    0 /* forced delegation IotWorkspaceFactory::OpenFolder */
};


static const PRPC_STUB_FUNCTION IotIfeWF_table[] =
{
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IotIfeWFStubVtbl =
{
    &IID_IotIfeWF,
    &IotIfeWF_ServerInfo,
    5,
    &IotIfeWF_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IotRasterBlock, ver. 0.0,
   GUID={0xC598484A,0x347E,0x4436,{0x98,0x4A,0x9A,0xF4,0xB5,0x74,0x60,0x7C}} */

#pragma code_seg(".orpc")
static const unsigned short IotRasterBlock_FormatStringOffsetTable[] =
    {
    690,
    718,
    124,
    354,
    746,
    774,
    802,
    842,
    870
    };

static const MIDL_STUBLESS_PROXY_INFO IotRasterBlock_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotRasterBlock_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotRasterBlock_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotRasterBlock_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IotRasterBlockProxyVtbl = 
{
    &IotRasterBlock_ProxyInfo,
    &IID_IotRasterBlock,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotRasterBlock::get_DataType */ ,
    (void *) (INT_PTR) -1 /* IotRasterBlock::put_DataType */ ,
    (void *) (INT_PTR) -1 /* IotRasterBlock::get_Width */ ,
    (void *) (INT_PTR) -1 /* IotRasterBlock::put_Width */ ,
    (void *) (INT_PTR) -1 /* IotRasterBlock::get_Height */ ,
    (void *) (INT_PTR) -1 /* IotRasterBlock::put_Height */ ,
    (void *) (INT_PTR) -1 /* IotRasterBlock::GetValue */ ,
    (void *) (INT_PTR) -1 /* IotRasterBlock::get_SafeArray */ ,
    (void *) (INT_PTR) -1 /* IotRasterBlock::put_SafeArray */
};

const CInterfaceStubVtbl _IotRasterBlockStubVtbl =
{
    &IID_IotRasterBlock,
    &IotRasterBlock_ServerInfo,
    12,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSelectionSet, ver. 0.0,
   GUID={0xB5B73261,0xA971,0x4040,{0xA5,0x6B,0x93,0x2C,0x85,0xD3,0x11,0x21}} */

#pragma code_seg(".orpc")
static const unsigned short IotSelectionSet_FormatStringOffsetTable[] =
    {
    898,
    926,
    954,
    976,
    1004,
    1032
    };

static const MIDL_STUBLESS_PROXY_INFO IotSelectionSet_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSelectionSet_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSelectionSet_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSelectionSet_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IotSelectionSetProxyVtbl = 
{
    &IotSelectionSet_ProxyInfo,
    &IID_IotSelectionSet,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSelectionSet::get_Count */ ,
    (void *) (INT_PTR) -1 /* IotSelectionSet::IsEOF */ ,
    (void *) (INT_PTR) -1 /* IotSelectionSet::ResetIndex */ ,
    (void *) (INT_PTR) -1 /* IotSelectionSet::NextID */ ,
    (void *) (INT_PTR) -1 /* IotSelectionSet::Add */ ,
    (void *) (INT_PTR) -1 /* IotSelectionSet::get_Table */
};

const CInterfaceStubVtbl _IotSelectionSetStubVtbl =
{
    &IID_IotSelectionSet,
    &IotSelectionSet_ServerInfo,
    9,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotSpatialReference, ver. 0.0,
   GUID={0x3C6AAEF9,0x400B,0x4C15,{0xA9,0xA3,0xB3,0x1B,0x6E,0x79,0x15,0x4A}} */

#pragma code_seg(".orpc")
static const unsigned short IotSpatialReference_FormatStringOffsetTable[] =
    {
    1060,
    1088,
    1122,
    1156,
    1184,
    1212,
    1240,
    1274,
    1302
    };

static const MIDL_STUBLESS_PROXY_INFO IotSpatialReference_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotSpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotSpatialReference_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotSpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IotSpatialReferenceProxyVtbl = 
{
    &IotSpatialReference_ProxyInfo,
    &IID_IotSpatialReference,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotSpatialReference::Clone */ ,
    (void *) (INT_PTR) -1 /* IotSpatialReference::ImportFromWkt */ ,
    (void *) (INT_PTR) -1 /* IotSpatialReference::ImportFromESRI */ ,
    (void *) (INT_PTR) -1 /* IotSpatialReference::ExportToWkt */ ,
    (void *) (INT_PTR) -1 /* IotSpatialReference::IsGeographic */ ,
    (void *) (INT_PTR) -1 /* IotSpatialReference::IsProjected */ ,
    (void *) (INT_PTR) -1 /* IotSpatialReference::IsSame */ ,
    (void *) (INT_PTR) -1 /* IotSpatialReference::GetGeogName */ ,
    (void *) (INT_PTR) -1 /* IotSpatialReference::GetProjName */
};

const CInterfaceStubVtbl _IotSpatialReferenceStubVtbl =
{
    &IID_IotSpatialReference,
    &IotSpatialReference_ServerInfo,
    12,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IotProjTransform, ver. 0.0,
   GUID={0x10D9A3D7,0xBD2B,0x4B51,{0x83,0x06,0x88,0xA8,0xCF,0x64,0xA0,0xF9}} */

#pragma code_seg(".orpc")
static const unsigned short IotProjTransform_FormatStringOffsetTable[] =
    {
    1060,
    1330,
    1358,
    1392
    };

static const MIDL_STUBLESS_PROXY_INFO IotProjTransform_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IotProjTransform_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IotProjTransform_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IotProjTransform_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IotProjTransformProxyVtbl = 
{
    &IotProjTransform_ProxyInfo,
    &IID_IotProjTransform,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IotProjTransform::get_FromSpatialReference */ ,
    (void *) (INT_PTR) -1 /* IotProjTransform::get_ToSpatialReference */ ,
    (void *) (INT_PTR) -1 /* IotProjTransform::SetSpatialReference */ ,
    (void *) (INT_PTR) -1 /* IotProjTransform::Transform */
};

const CInterfaceStubVtbl _IotProjTransformStubVtbl =
{
    &IID_IotProjTransform,
    &IotProjTransform_ServerInfo,
    7,
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

const CInterfaceProxyVtbl * _otcGeodataModel_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IotRowProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotFieldProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ITmsWFProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotRasterBlockProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSelectionSetProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotCursorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotWorkspaceFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotFeatureCursorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotShpWFProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotProjTransformProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotIfeWFProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSimpleQueryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IotSpatialReferenceProxyVtbl,
    0
};

const CInterfaceStubVtbl * _otcGeodataModel_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IotRowStubVtbl,
    ( CInterfaceStubVtbl *) &_IotFieldStubVtbl,
    ( CInterfaceStubVtbl *) &_ITmsWFStubVtbl,
    ( CInterfaceStubVtbl *) &_IotRasterBlockStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSelectionSetStubVtbl,
    ( CInterfaceStubVtbl *) &_IotCursorStubVtbl,
    ( CInterfaceStubVtbl *) &_IotWorkspaceFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IotFeatureCursorStubVtbl,
    ( CInterfaceStubVtbl *) &_IotShpWFStubVtbl,
    ( CInterfaceStubVtbl *) &_IotProjTransformStubVtbl,
    ( CInterfaceStubVtbl *) &_IotIfeWFStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSimpleQueryStubVtbl,
    ( CInterfaceStubVtbl *) &_IotSpatialReferenceStubVtbl,
    0
};

PCInterfaceName const _otcGeodataModel_InterfaceNamesList[] = 
{
    "IotRow",
    "IotField",
    "ITmsWF",
    "IotRasterBlock",
    "IotSelectionSet",
    "IotCursor",
    "IotWorkspaceFactory",
    "IotFeatureCursor",
    "IotShpWF",
    "IotProjTransform",
    "IotIfeWF",
    "IotSimpleQuery",
    "IotSpatialReference",
    0
};

const IID *  _otcGeodataModel_BaseIIDList[] = 
{
    0,
    0,
    &IID_IotWorkspaceFactory,   /* forced */
    0,
    0,
    0,
    0,
    0,
    &IID_IotWorkspaceFactory,   /* forced */
    0,
    &IID_IotWorkspaceFactory,   /* forced */
    0,
    0,
    0
};


#define _otcGeodataModel_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _otcGeodataModel, pIID, n)

int __stdcall _otcGeodataModel_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _otcGeodataModel, 13, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _otcGeodataModel, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _otcGeodataModel, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _otcGeodataModel, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _otcGeodataModel, 13, *pIndex )
    
}

const ExtendedProxyFileInfo otcGeodataModel_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _otcGeodataModel_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _otcGeodataModel_StubVtblList,
    (const PCInterfaceName * ) & _otcGeodataModel_InterfaceNamesList,
    (const IID ** ) & _otcGeodataModel_BaseIIDList,
    & _otcGeodataModel_IID_Lookup, 
    13,
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

