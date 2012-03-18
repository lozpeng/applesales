

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __otcDisplay_h__
#define __otcDisplay_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IotSymbol_FWD_DEFINED__
#define __IotSymbol_FWD_DEFINED__
typedef interface IotSymbol IotSymbol;
#endif 	/* __IotSymbol_FWD_DEFINED__ */


#ifndef __IotMarkerSymbol_FWD_DEFINED__
#define __IotMarkerSymbol_FWD_DEFINED__
typedef interface IotMarkerSymbol IotMarkerSymbol;
#endif 	/* __IotMarkerSymbol_FWD_DEFINED__ */


#ifndef __IotLineSymbol_FWD_DEFINED__
#define __IotLineSymbol_FWD_DEFINED__
typedef interface IotLineSymbol IotLineSymbol;
#endif 	/* __IotLineSymbol_FWD_DEFINED__ */


#ifndef __IotFillSymbol_FWD_DEFINED__
#define __IotFillSymbol_FWD_DEFINED__
typedef interface IotFillSymbol IotFillSymbol;
#endif 	/* __IotFillSymbol_FWD_DEFINED__ */


#ifndef __IotColor_FWD_DEFINED__
#define __IotColor_FWD_DEFINED__
typedef interface IotColor IotColor;
#endif 	/* __IotColor_FWD_DEFINED__ */


#ifndef __IotSimpleMarkerSymbol_FWD_DEFINED__
#define __IotSimpleMarkerSymbol_FWD_DEFINED__
typedef interface IotSimpleMarkerSymbol IotSimpleMarkerSymbol;
#endif 	/* __IotSimpleMarkerSymbol_FWD_DEFINED__ */


#ifndef __IotCharMarkerSymbol_FWD_DEFINED__
#define __IotCharMarkerSymbol_FWD_DEFINED__
typedef interface IotCharMarkerSymbol IotCharMarkerSymbol;
#endif 	/* __IotCharMarkerSymbol_FWD_DEFINED__ */


#ifndef __IotArrowMarkerSymbol_FWD_DEFINED__
#define __IotArrowMarkerSymbol_FWD_DEFINED__
typedef interface IotArrowMarkerSymbol IotArrowMarkerSymbol;
#endif 	/* __IotArrowMarkerSymbol_FWD_DEFINED__ */


#ifndef __IotPicMarkerSymbol_FWD_DEFINED__
#define __IotPicMarkerSymbol_FWD_DEFINED__
typedef interface IotPicMarkerSymbol IotPicMarkerSymbol;
#endif 	/* __IotPicMarkerSymbol_FWD_DEFINED__ */


#ifndef __IotSimpleLineSymbol_FWD_DEFINED__
#define __IotSimpleLineSymbol_FWD_DEFINED__
typedef interface IotSimpleLineSymbol IotSimpleLineSymbol;
#endif 	/* __IotSimpleLineSymbol_FWD_DEFINED__ */


#ifndef __IotAdvLineSymbol_FWD_DEFINED__
#define __IotAdvLineSymbol_FWD_DEFINED__
typedef interface IotAdvLineSymbol IotAdvLineSymbol;
#endif 	/* __IotAdvLineSymbol_FWD_DEFINED__ */


#ifndef __IotHashLineSymbol_FWD_DEFINED__
#define __IotHashLineSymbol_FWD_DEFINED__
typedef interface IotHashLineSymbol IotHashLineSymbol;
#endif 	/* __IotHashLineSymbol_FWD_DEFINED__ */


#ifndef __IotMarkerLineSymbol_FWD_DEFINED__
#define __IotMarkerLineSymbol_FWD_DEFINED__
typedef interface IotMarkerLineSymbol IotMarkerLineSymbol;
#endif 	/* __IotMarkerLineSymbol_FWD_DEFINED__ */


#ifndef __IotSimpleFillSymbol_FWD_DEFINED__
#define __IotSimpleFillSymbol_FWD_DEFINED__
typedef interface IotSimpleFillSymbol IotSimpleFillSymbol;
#endif 	/* __IotSimpleFillSymbol_FWD_DEFINED__ */


#ifndef __IotLineFillSymbol_FWD_DEFINED__
#define __IotLineFillSymbol_FWD_DEFINED__
typedef interface IotLineFillSymbol IotLineFillSymbol;
#endif 	/* __IotLineFillSymbol_FWD_DEFINED__ */


#ifndef __IotMarkerFillSymbol_FWD_DEFINED__
#define __IotMarkerFillSymbol_FWD_DEFINED__
typedef interface IotMarkerFillSymbol IotMarkerFillSymbol;
#endif 	/* __IotMarkerFillSymbol_FWD_DEFINED__ */


#ifndef __IotPicFillSymbol_FWD_DEFINED__
#define __IotPicFillSymbol_FWD_DEFINED__
typedef interface IotPicFillSymbol IotPicFillSymbol;
#endif 	/* __IotPicFillSymbol_FWD_DEFINED__ */


#ifndef __IotGradientFillSymbol_FWD_DEFINED__
#define __IotGradientFillSymbol_FWD_DEFINED__
typedef interface IotGradientFillSymbol IotGradientFillSymbol;
#endif 	/* __IotGradientFillSymbol_FWD_DEFINED__ */


#ifndef __IotComplexMarkerSymbol_FWD_DEFINED__
#define __IotComplexMarkerSymbol_FWD_DEFINED__
typedef interface IotComplexMarkerSymbol IotComplexMarkerSymbol;
#endif 	/* __IotComplexMarkerSymbol_FWD_DEFINED__ */


#ifndef __IotComplexLineSymbol_FWD_DEFINED__
#define __IotComplexLineSymbol_FWD_DEFINED__
typedef interface IotComplexLineSymbol IotComplexLineSymbol;
#endif 	/* __IotComplexLineSymbol_FWD_DEFINED__ */


#ifndef __IotComplexFillSymbol_FWD_DEFINED__
#define __IotComplexFillSymbol_FWD_DEFINED__
typedef interface IotComplexFillSymbol IotComplexFillSymbol;
#endif 	/* __IotComplexFillSymbol_FWD_DEFINED__ */


#ifndef __IotCanvas_FWD_DEFINED__
#define __IotCanvas_FWD_DEFINED__
typedef interface IotCanvas IotCanvas;
#endif 	/* __IotCanvas_FWD_DEFINED__ */


#ifndef __IotSymbolConvert_FWD_DEFINED__
#define __IotSymbolConvert_FWD_DEFINED__
typedef interface IotSymbolConvert IotSymbolConvert;
#endif 	/* __IotSymbolConvert_FWD_DEFINED__ */


#ifndef __IotTextSymbol_FWD_DEFINED__
#define __IotTextSymbol_FWD_DEFINED__
typedef interface IotTextSymbol IotTextSymbol;
#endif 	/* __IotTextSymbol_FWD_DEFINED__ */


#ifndef __IotSymbolLibLoader_FWD_DEFINED__
#define __IotSymbolLibLoader_FWD_DEFINED__
typedef interface IotSymbolLibLoader IotSymbolLibLoader;
#endif 	/* __IotSymbolLibLoader_FWD_DEFINED__ */


#ifndef __IotScreenSketch_FWD_DEFINED__
#define __IotScreenSketch_FWD_DEFINED__
typedef interface IotScreenSketch IotScreenSketch;
#endif 	/* __IotScreenSketch_FWD_DEFINED__ */


#ifndef __otColor_FWD_DEFINED__
#define __otColor_FWD_DEFINED__

#ifdef __cplusplus
typedef class otColor otColor;
#else
typedef struct otColor otColor;
#endif /* __cplusplus */

#endif 	/* __otColor_FWD_DEFINED__ */


#ifndef __otSimpleMarkerSymbol_FWD_DEFINED__
#define __otSimpleMarkerSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSimpleMarkerSymbol otSimpleMarkerSymbol;
#else
typedef struct otSimpleMarkerSymbol otSimpleMarkerSymbol;
#endif /* __cplusplus */

#endif 	/* __otSimpleMarkerSymbol_FWD_DEFINED__ */


#ifndef __otCharMarkerSymbol_FWD_DEFINED__
#define __otCharMarkerSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otCharMarkerSymbol otCharMarkerSymbol;
#else
typedef struct otCharMarkerSymbol otCharMarkerSymbol;
#endif /* __cplusplus */

#endif 	/* __otCharMarkerSymbol_FWD_DEFINED__ */


#ifndef __otArrowMarkerSymbol_FWD_DEFINED__
#define __otArrowMarkerSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otArrowMarkerSymbol otArrowMarkerSymbol;
#else
typedef struct otArrowMarkerSymbol otArrowMarkerSymbol;
#endif /* __cplusplus */

#endif 	/* __otArrowMarkerSymbol_FWD_DEFINED__ */


#ifndef __otPicMarkerSymbol_FWD_DEFINED__
#define __otPicMarkerSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otPicMarkerSymbol otPicMarkerSymbol;
#else
typedef struct otPicMarkerSymbol otPicMarkerSymbol;
#endif /* __cplusplus */

#endif 	/* __otPicMarkerSymbol_FWD_DEFINED__ */


#ifndef __otSimpleLineSymbol_FWD_DEFINED__
#define __otSimpleLineSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSimpleLineSymbol otSimpleLineSymbol;
#else
typedef struct otSimpleLineSymbol otSimpleLineSymbol;
#endif /* __cplusplus */

#endif 	/* __otSimpleLineSymbol_FWD_DEFINED__ */


#ifndef __otAdvLineSymbol_FWD_DEFINED__
#define __otAdvLineSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otAdvLineSymbol otAdvLineSymbol;
#else
typedef struct otAdvLineSymbol otAdvLineSymbol;
#endif /* __cplusplus */

#endif 	/* __otAdvLineSymbol_FWD_DEFINED__ */


#ifndef __otHashLineSymbol_FWD_DEFINED__
#define __otHashLineSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otHashLineSymbol otHashLineSymbol;
#else
typedef struct otHashLineSymbol otHashLineSymbol;
#endif /* __cplusplus */

#endif 	/* __otHashLineSymbol_FWD_DEFINED__ */


#ifndef __otMarkerLineSymbol_FWD_DEFINED__
#define __otMarkerLineSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otMarkerLineSymbol otMarkerLineSymbol;
#else
typedef struct otMarkerLineSymbol otMarkerLineSymbol;
#endif /* __cplusplus */

#endif 	/* __otMarkerLineSymbol_FWD_DEFINED__ */


#ifndef __otSimpleFillSymbol_FWD_DEFINED__
#define __otSimpleFillSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSimpleFillSymbol otSimpleFillSymbol;
#else
typedef struct otSimpleFillSymbol otSimpleFillSymbol;
#endif /* __cplusplus */

#endif 	/* __otSimpleFillSymbol_FWD_DEFINED__ */


#ifndef __otLineFillSymbol_FWD_DEFINED__
#define __otLineFillSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otLineFillSymbol otLineFillSymbol;
#else
typedef struct otLineFillSymbol otLineFillSymbol;
#endif /* __cplusplus */

#endif 	/* __otLineFillSymbol_FWD_DEFINED__ */


#ifndef __otMarkerFillSymbol_FWD_DEFINED__
#define __otMarkerFillSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otMarkerFillSymbol otMarkerFillSymbol;
#else
typedef struct otMarkerFillSymbol otMarkerFillSymbol;
#endif /* __cplusplus */

#endif 	/* __otMarkerFillSymbol_FWD_DEFINED__ */


#ifndef __otPicFillSymbol_FWD_DEFINED__
#define __otPicFillSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otPicFillSymbol otPicFillSymbol;
#else
typedef struct otPicFillSymbol otPicFillSymbol;
#endif /* __cplusplus */

#endif 	/* __otPicFillSymbol_FWD_DEFINED__ */


#ifndef __otGradientFillSymbol_FWD_DEFINED__
#define __otGradientFillSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otGradientFillSymbol otGradientFillSymbol;
#else
typedef struct otGradientFillSymbol otGradientFillSymbol;
#endif /* __cplusplus */

#endif 	/* __otGradientFillSymbol_FWD_DEFINED__ */


#ifndef __otComplexMarkerSymbol_FWD_DEFINED__
#define __otComplexMarkerSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otComplexMarkerSymbol otComplexMarkerSymbol;
#else
typedef struct otComplexMarkerSymbol otComplexMarkerSymbol;
#endif /* __cplusplus */

#endif 	/* __otComplexMarkerSymbol_FWD_DEFINED__ */


#ifndef __otComplexLineSymbol_FWD_DEFINED__
#define __otComplexLineSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otComplexLineSymbol otComplexLineSymbol;
#else
typedef struct otComplexLineSymbol otComplexLineSymbol;
#endif /* __cplusplus */

#endif 	/* __otComplexLineSymbol_FWD_DEFINED__ */


#ifndef __otComplexFillSymbol_FWD_DEFINED__
#define __otComplexFillSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otComplexFillSymbol otComplexFillSymbol;
#else
typedef struct otComplexFillSymbol otComplexFillSymbol;
#endif /* __cplusplus */

#endif 	/* __otComplexFillSymbol_FWD_DEFINED__ */


#ifndef __otCanvas_FWD_DEFINED__
#define __otCanvas_FWD_DEFINED__

#ifdef __cplusplus
typedef class otCanvas otCanvas;
#else
typedef struct otCanvas otCanvas;
#endif /* __cplusplus */

#endif 	/* __otCanvas_FWD_DEFINED__ */


#ifndef __otScreenSketch_FWD_DEFINED__
#define __otScreenSketch_FWD_DEFINED__

#ifdef __cplusplus
typedef class otScreenSketch otScreenSketch;
#else
typedef struct otScreenSketch otScreenSketch;
#endif /* __cplusplus */

#endif 	/* __otScreenSketch_FWD_DEFINED__ */


#ifndef __otSymbolConvert_FWD_DEFINED__
#define __otSymbolConvert_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSymbolConvert otSymbolConvert;
#else
typedef struct otSymbolConvert otSymbolConvert;
#endif /* __cplusplus */

#endif 	/* __otSymbolConvert_FWD_DEFINED__ */


#ifndef __otTextSymbol_FWD_DEFINED__
#define __otTextSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class otTextSymbol otTextSymbol;
#else
typedef struct otTextSymbol otTextSymbol;
#endif /* __cplusplus */

#endif 	/* __otTextSymbol_FWD_DEFINED__ */


#ifndef __otSymbolLibLoader_FWD_DEFINED__
#define __otSymbolLibLoader_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSymbolLibLoader otSymbolLibLoader;
#else
typedef struct otSymbolLibLoader otSymbolLibLoader;
#endif /* __cplusplus */

#endif 	/* __otSymbolLibLoader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_otcDisplay_0000 */
/* [local] */ 


typedef /* [helpstring][uuid] */  DECLSPEC_UUID("0172E7CD-3A80-4816-9E5C-F719E426B5ED") 
enum otSymbolUnit
    {	otPOINTS	= 0,
	otMILLIMETER	= 1,
	otCENTIMETER	= 10,
	otDECIMETER	= 100
    } 	otSymbolUnit;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("B8048F4A-88C3-4593-BA22-C0B3C5F2C5EA") 
enum otSymbolType
    {	otNONE_SYMBOL	= 0x1,
	otTEXT_SYMBOL	= 0x2,
	otMARKER_SYMBOL	= 0x10,
	otLINE_SYMBOL	= 0x20,
	otFILL_SYMBOL	= 0x40,
	otEXT_SYMBOL	= 0x80,
	otCOMPLEX_SYMBOL	= 0x100,
	otSIMPLE_MARKER_SYMBOL	= 0x11,
	otCHAR_MARKER_SYMBOL	= 0x12,
	otARROW_MARKER_SYMBOL	= 0x13,
	otPIC_MARKER_SYMBOL	= 0x14,
	otSIMPLE_LINE_SYMBOL	= 0x21,
	otADV_LINE_SYMBOL	= 0x22,
	otMARKER_LINE_SYMBOL	= 0x23,
	otHASH_LINE_SYMBOL	= 0x24,
	otPIC_LINE_SYMBOL	= 0x25,
	otSIMPLE_FILL_SYMBOL	= 0x41,
	otMARKER_FILL_SYMBOL	= 0x42,
	otLINE_FILL_SYMBOL	= 0x43,
	otPIC_FILL_SYMBOL	= 0x44,
	otGRADIENT_FILL_SYMBOL	= 0x45,
	otCOMPLEX_MARKER_SYMBOL	= otCOMPLEX_SYMBOL | otMARKER_SYMBOL,
	otCOMPLEX_LINE_SYMBOL	= otCOMPLEX_SYMBOL | otLINE_SYMBOL,
	otCOMPLEX_FILL_SYMBOL	= otCOMPLEX_SYMBOL | otFILL_SYMBOL,
	otEXT_MARKER_SYMBOL	= otEXT_SYMBOL | otMARKER_SYMBOL,
	otEXT_LINE_SYMBOL	= otEXT_SYMBOL | otLINE_SYMBOL,
	otEXT_FILL_SYMBOL	= otEXT_SYMBOL | otFILL_SYMBOL,
	otEXT_ALL_SYMBOL	= 0xf0
    } 	otSymbolType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("116B65E1-17D3-4a92-8DF6-4AF23C55808E") 
enum otSimpleMarkerStyle
    {	OT_MARKER_NULL	= 0,
	OT_MARKER_SQUARE	= 1,
	OT_MARKER_CIRCLE	= 2,
	OT_MARKER_CROSS	= 3,
	OT_MARKER_X	= 4,
	OT_MARKER_STAR	= 5,
	OT_MARKER_DIAMOND	= 6
    } 	otSimpleMarkerStyle;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("3835E4BE-0692-4ceb-8756-231146526970") 
enum otSimpleLineStyle
    {	OT_SLINE_SOLID	= 0,
	OT_SLINE_DASH	= 1,
	OT_SLINE_DOT	= 2,
	OT_SLINE_DASHDOT	= 3,
	OT_SLINE_DASHDOTDOT	= 4,
	OT_SLINE_NULL	= 5,
	OT_SLINE_INSIDEFRAME	= 6
    } 	otSimpleLineStyle;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("C2F7A92A-2C7C-4af4-B1F8-13A3CAD90FE8") 
enum otGradientFillType
    {	OT_GRADIENTFILL_LINEAR	= 1,
	OT_GRADIENTFILL_RECTANGLAR	= 2,
	OT_GRADIENTFILL_CIRCLAR	= 3
    } 	otGradientFillType;



extern RPC_IF_HANDLE __MIDL_itf_otcDisplay_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_otcDisplay_0000_v0_0_s_ifspec;

#ifndef __IotSymbol_INTERFACE_DEFINED__
#define __IotSymbol_INTERFACE_DEFINED__

/* interface IotSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3719D63B-9A15-4bc3-AC8A-33543E7092BC")
    IotSymbol : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ otSymbolType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Unit( 
            /* [retval][out] */ otSymbolUnit *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Unit( 
            /* [in] */ otSymbolUnit newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        END_INTERFACE
    } IotSymbolVtbl;

    interface IotSymbol
    {
        CONST_VTBL struct IotSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSymbol_get_Type_Proxy( 
    IotSymbol * This,
    /* [retval][out] */ otSymbolType *pVal);


void __RPC_STUB IotSymbol_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSymbol_get_Unit_Proxy( 
    IotSymbol * This,
    /* [retval][out] */ otSymbolUnit *pVal);


void __RPC_STUB IotSymbol_get_Unit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSymbol_put_Unit_Proxy( 
    IotSymbol * This,
    /* [in] */ otSymbolUnit newVal);


void __RPC_STUB IotSymbol_put_Unit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSymbol_INTERFACE_DEFINED__ */


#ifndef __IotMarkerSymbol_INTERFACE_DEFINED__
#define __IotMarkerSymbol_INTERFACE_DEFINED__

/* interface IotMarkerSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotMarkerSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1797A2E-3B2C-434a-980E-36278B98312C")
    IotMarkerSymbol : public IotSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ IotColor *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OffsetX( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OffsetX( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OffsetY( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OffsetY( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Angle( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Angle( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Size( 
            /* [in] */ DOUBLE newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotMarkerSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotMarkerSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotMarkerSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotMarkerSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotMarkerSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotMarkerSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotMarkerSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotMarkerSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotMarkerSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetX )( 
            IotMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetX )( 
            IotMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetY )( 
            IotMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetY )( 
            IotMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IotMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Angle )( 
            IotMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IotMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            IotMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        END_INTERFACE
    } IotMarkerSymbolVtbl;

    interface IotMarkerSymbol
    {
        CONST_VTBL struct IotMarkerSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotMarkerSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotMarkerSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotMarkerSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotMarkerSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotMarkerSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotMarkerSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotMarkerSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotMarkerSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#define IotMarkerSymbol_get_OffsetX(This,pVal)	\
    (This)->lpVtbl -> get_OffsetX(This,pVal)

#define IotMarkerSymbol_put_OffsetX(This,newVal)	\
    (This)->lpVtbl -> put_OffsetX(This,newVal)

#define IotMarkerSymbol_get_OffsetY(This,pVal)	\
    (This)->lpVtbl -> get_OffsetY(This,pVal)

#define IotMarkerSymbol_put_OffsetY(This,newVal)	\
    (This)->lpVtbl -> put_OffsetY(This,newVal)

#define IotMarkerSymbol_get_Angle(This,pVal)	\
    (This)->lpVtbl -> get_Angle(This,pVal)

#define IotMarkerSymbol_put_Angle(This,newVal)	\
    (This)->lpVtbl -> put_Angle(This,newVal)

#define IotMarkerSymbol_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IotMarkerSymbol_put_Size(This,newVal)	\
    (This)->lpVtbl -> put_Size(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_get_Color_Proxy( 
    IotMarkerSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotMarkerSymbol_get_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_put_Color_Proxy( 
    IotMarkerSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotMarkerSymbol_put_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_get_OffsetX_Proxy( 
    IotMarkerSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMarkerSymbol_get_OffsetX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_put_OffsetX_Proxy( 
    IotMarkerSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotMarkerSymbol_put_OffsetX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_get_OffsetY_Proxy( 
    IotMarkerSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMarkerSymbol_get_OffsetY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_put_OffsetY_Proxy( 
    IotMarkerSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotMarkerSymbol_put_OffsetY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_get_Angle_Proxy( 
    IotMarkerSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMarkerSymbol_get_Angle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_put_Angle_Proxy( 
    IotMarkerSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotMarkerSymbol_put_Angle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_get_Size_Proxy( 
    IotMarkerSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMarkerSymbol_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerSymbol_put_Size_Proxy( 
    IotMarkerSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotMarkerSymbol_put_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotMarkerSymbol_INTERFACE_DEFINED__ */


#ifndef __IotLineSymbol_INTERFACE_DEFINED__
#define __IotLineSymbol_INTERFACE_DEFINED__

/* interface IotLineSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotLineSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8A5B2356-8FF7-4027-A4F8-02ABE13C8C7E")
    IotLineSymbol : public IotSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LineWidth( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LineWidth( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ IotColor *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotLineSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotLineSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotLineSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotLineSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotLineSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotLineSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotLineSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineWidth )( 
            IotLineSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineWidth )( 
            IotLineSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotLineSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotLineSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotLineSymbolVtbl;

    interface IotLineSymbol
    {
        CONST_VTBL struct IotLineSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotLineSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotLineSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotLineSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotLineSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotLineSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotLineSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotLineSymbol_get_LineWidth(This,pVal)	\
    (This)->lpVtbl -> get_LineWidth(This,pVal)

#define IotLineSymbol_put_LineWidth(This,newVal)	\
    (This)->lpVtbl -> put_LineWidth(This,newVal)

#define IotLineSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotLineSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLineSymbol_get_LineWidth_Proxy( 
    IotLineSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotLineSymbol_get_LineWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLineSymbol_put_LineWidth_Proxy( 
    IotLineSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotLineSymbol_put_LineWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLineSymbol_get_Color_Proxy( 
    IotLineSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotLineSymbol_get_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLineSymbol_put_Color_Proxy( 
    IotLineSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotLineSymbol_put_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotLineSymbol_INTERFACE_DEFINED__ */


#ifndef __IotFillSymbol_INTERFACE_DEFINED__
#define __IotFillSymbol_INTERFACE_DEFINED__

/* interface IotFillSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotFillSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("107F6E58-F6E7-44cd-B4DF-A61B3D5F97D2")
    IotFillSymbol : public IotSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DrawOutLine( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DrawOutLine( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OutLine( 
            /* [retval][out] */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OutLine( 
            /* [in] */ IotSymbol *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FillColor( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FillColor( 
            /* [in] */ IotColor *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotFillSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotFillSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotFillSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotFillSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotFillSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotFillSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotFillSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawOutLine )( 
            IotFillSymbol * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawOutLine )( 
            IotFillSymbol * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutLine )( 
            IotFillSymbol * This,
            /* [retval][out] */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutLine )( 
            IotFillSymbol * This,
            /* [in] */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillColor )( 
            IotFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillColor )( 
            IotFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotFillSymbolVtbl;

    interface IotFillSymbol
    {
        CONST_VTBL struct IotFillSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotFillSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotFillSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotFillSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotFillSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotFillSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotFillSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotFillSymbol_get_DrawOutLine(This,pVal)	\
    (This)->lpVtbl -> get_DrawOutLine(This,pVal)

#define IotFillSymbol_put_DrawOutLine(This,newVal)	\
    (This)->lpVtbl -> put_DrawOutLine(This,newVal)

#define IotFillSymbol_get_OutLine(This,pVal)	\
    (This)->lpVtbl -> get_OutLine(This,pVal)

#define IotFillSymbol_put_OutLine(This,newVal)	\
    (This)->lpVtbl -> put_OutLine(This,newVal)

#define IotFillSymbol_get_FillColor(This,pVal)	\
    (This)->lpVtbl -> get_FillColor(This,pVal)

#define IotFillSymbol_put_FillColor(This,newVal)	\
    (This)->lpVtbl -> put_FillColor(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFillSymbol_get_DrawOutLine_Proxy( 
    IotFillSymbol * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotFillSymbol_get_DrawOutLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotFillSymbol_put_DrawOutLine_Proxy( 
    IotFillSymbol * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IotFillSymbol_put_DrawOutLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFillSymbol_get_OutLine_Proxy( 
    IotFillSymbol * This,
    /* [retval][out] */ IotSymbol **pVal);


void __RPC_STUB IotFillSymbol_get_OutLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotFillSymbol_put_OutLine_Proxy( 
    IotFillSymbol * This,
    /* [in] */ IotSymbol *newVal);


void __RPC_STUB IotFillSymbol_put_OutLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFillSymbol_get_FillColor_Proxy( 
    IotFillSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotFillSymbol_get_FillColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotFillSymbol_put_FillColor_Proxy( 
    IotFillSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotFillSymbol_put_FillColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotFillSymbol_INTERFACE_DEFINED__ */


#ifndef __IotColor_INTERFACE_DEFINED__
#define __IotColor_INTERFACE_DEFINED__

/* interface IotColor */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotColor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3ABFAB4-3D14-4F02-ADAF-37AC9CD2D60B")
    IotColor : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Red( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Red( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Green( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Green( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Blue( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Blue( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotColorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotColor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotColor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotColor * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Red )( 
            IotColor * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Red )( 
            IotColor * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Green )( 
            IotColor * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Green )( 
            IotColor * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Blue )( 
            IotColor * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Blue )( 
            IotColor * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } IotColorVtbl;

    interface IotColor
    {
        CONST_VTBL struct IotColorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotColor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotColor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotColor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotColor_get_Red(This,pVal)	\
    (This)->lpVtbl -> get_Red(This,pVal)

#define IotColor_put_Red(This,newVal)	\
    (This)->lpVtbl -> put_Red(This,newVal)

#define IotColor_get_Green(This,pVal)	\
    (This)->lpVtbl -> get_Green(This,pVal)

#define IotColor_put_Green(This,newVal)	\
    (This)->lpVtbl -> put_Green(This,newVal)

#define IotColor_get_Blue(This,pVal)	\
    (This)->lpVtbl -> get_Blue(This,pVal)

#define IotColor_put_Blue(This,newVal)	\
    (This)->lpVtbl -> put_Blue(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotColor_get_Red_Proxy( 
    IotColor * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotColor_get_Red_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotColor_put_Red_Proxy( 
    IotColor * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotColor_put_Red_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotColor_get_Green_Proxy( 
    IotColor * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotColor_get_Green_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotColor_put_Green_Proxy( 
    IotColor * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotColor_put_Green_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotColor_get_Blue_Proxy( 
    IotColor * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotColor_get_Blue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotColor_put_Blue_Proxy( 
    IotColor * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotColor_put_Blue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotColor_INTERFACE_DEFINED__ */


#ifndef __IotSimpleMarkerSymbol_INTERFACE_DEFINED__
#define __IotSimpleMarkerSymbol_INTERFACE_DEFINED__

/* interface IotSimpleMarkerSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSimpleMarkerSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("27409DBF-730B-4756-9D09-5EBF25885E7B")
    IotSimpleMarkerSymbol : public IotMarkerSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DrawOutLine( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DrawOutLine( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OutLineWidth( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OutLineWidth( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MarkerStyle( 
            /* [retval][out] */ otSimpleMarkerStyle *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MarkerStyle( 
            /* [in] */ otSimpleMarkerStyle newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OutLineColor( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OutLineColor( 
            /* [in] */ IotColor *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSimpleMarkerSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSimpleMarkerSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSimpleMarkerSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetX )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetX )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetY )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetY )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Angle )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawOutLine )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawOutLine )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutLineWidth )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutLineWidth )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkerStyle )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ otSimpleMarkerStyle *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkerStyle )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ otSimpleMarkerStyle newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutLineColor )( 
            IotSimpleMarkerSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutLineColor )( 
            IotSimpleMarkerSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotSimpleMarkerSymbolVtbl;

    interface IotSimpleMarkerSymbol
    {
        CONST_VTBL struct IotSimpleMarkerSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSimpleMarkerSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSimpleMarkerSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSimpleMarkerSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSimpleMarkerSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotSimpleMarkerSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotSimpleMarkerSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotSimpleMarkerSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotSimpleMarkerSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#define IotSimpleMarkerSymbol_get_OffsetX(This,pVal)	\
    (This)->lpVtbl -> get_OffsetX(This,pVal)

#define IotSimpleMarkerSymbol_put_OffsetX(This,newVal)	\
    (This)->lpVtbl -> put_OffsetX(This,newVal)

#define IotSimpleMarkerSymbol_get_OffsetY(This,pVal)	\
    (This)->lpVtbl -> get_OffsetY(This,pVal)

#define IotSimpleMarkerSymbol_put_OffsetY(This,newVal)	\
    (This)->lpVtbl -> put_OffsetY(This,newVal)

#define IotSimpleMarkerSymbol_get_Angle(This,pVal)	\
    (This)->lpVtbl -> get_Angle(This,pVal)

#define IotSimpleMarkerSymbol_put_Angle(This,newVal)	\
    (This)->lpVtbl -> put_Angle(This,newVal)

#define IotSimpleMarkerSymbol_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IotSimpleMarkerSymbol_put_Size(This,newVal)	\
    (This)->lpVtbl -> put_Size(This,newVal)


#define IotSimpleMarkerSymbol_get_DrawOutLine(This,pVal)	\
    (This)->lpVtbl -> get_DrawOutLine(This,pVal)

#define IotSimpleMarkerSymbol_put_DrawOutLine(This,newVal)	\
    (This)->lpVtbl -> put_DrawOutLine(This,newVal)

#define IotSimpleMarkerSymbol_get_OutLineWidth(This,pVal)	\
    (This)->lpVtbl -> get_OutLineWidth(This,pVal)

#define IotSimpleMarkerSymbol_put_OutLineWidth(This,newVal)	\
    (This)->lpVtbl -> put_OutLineWidth(This,newVal)

#define IotSimpleMarkerSymbol_get_MarkerStyle(This,pVal)	\
    (This)->lpVtbl -> get_MarkerStyle(This,pVal)

#define IotSimpleMarkerSymbol_put_MarkerStyle(This,newVal)	\
    (This)->lpVtbl -> put_MarkerStyle(This,newVal)

#define IotSimpleMarkerSymbol_get_OutLineColor(This,pVal)	\
    (This)->lpVtbl -> get_OutLineColor(This,pVal)

#define IotSimpleMarkerSymbol_put_OutLineColor(This,newVal)	\
    (This)->lpVtbl -> put_OutLineColor(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSimpleMarkerSymbol_get_DrawOutLine_Proxy( 
    IotSimpleMarkerSymbol * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotSimpleMarkerSymbol_get_DrawOutLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSimpleMarkerSymbol_put_DrawOutLine_Proxy( 
    IotSimpleMarkerSymbol * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IotSimpleMarkerSymbol_put_DrawOutLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSimpleMarkerSymbol_get_OutLineWidth_Proxy( 
    IotSimpleMarkerSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotSimpleMarkerSymbol_get_OutLineWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSimpleMarkerSymbol_put_OutLineWidth_Proxy( 
    IotSimpleMarkerSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotSimpleMarkerSymbol_put_OutLineWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSimpleMarkerSymbol_get_MarkerStyle_Proxy( 
    IotSimpleMarkerSymbol * This,
    /* [retval][out] */ otSimpleMarkerStyle *pVal);


void __RPC_STUB IotSimpleMarkerSymbol_get_MarkerStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSimpleMarkerSymbol_put_MarkerStyle_Proxy( 
    IotSimpleMarkerSymbol * This,
    /* [in] */ otSimpleMarkerStyle newVal);


void __RPC_STUB IotSimpleMarkerSymbol_put_MarkerStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSimpleMarkerSymbol_get_OutLineColor_Proxy( 
    IotSimpleMarkerSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotSimpleMarkerSymbol_get_OutLineColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSimpleMarkerSymbol_put_OutLineColor_Proxy( 
    IotSimpleMarkerSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotSimpleMarkerSymbol_put_OutLineColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSimpleMarkerSymbol_INTERFACE_DEFINED__ */


#ifndef __IotCharMarkerSymbol_INTERFACE_DEFINED__
#define __IotCharMarkerSymbol_INTERFACE_DEFINED__

/* interface IotCharMarkerSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotCharMarkerSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("39F5D04E-3135-45CA-A004-FE0ACA6AE883")
    IotCharMarkerSymbol : public IotMarkerSymbol
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotCharMarkerSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotCharMarkerSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotCharMarkerSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotCharMarkerSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotCharMarkerSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotCharMarkerSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotCharMarkerSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotCharMarkerSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotCharMarkerSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetX )( 
            IotCharMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetX )( 
            IotCharMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetY )( 
            IotCharMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetY )( 
            IotCharMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IotCharMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Angle )( 
            IotCharMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IotCharMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            IotCharMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        END_INTERFACE
    } IotCharMarkerSymbolVtbl;

    interface IotCharMarkerSymbol
    {
        CONST_VTBL struct IotCharMarkerSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotCharMarkerSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotCharMarkerSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotCharMarkerSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotCharMarkerSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotCharMarkerSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotCharMarkerSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotCharMarkerSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotCharMarkerSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#define IotCharMarkerSymbol_get_OffsetX(This,pVal)	\
    (This)->lpVtbl -> get_OffsetX(This,pVal)

#define IotCharMarkerSymbol_put_OffsetX(This,newVal)	\
    (This)->lpVtbl -> put_OffsetX(This,newVal)

#define IotCharMarkerSymbol_get_OffsetY(This,pVal)	\
    (This)->lpVtbl -> get_OffsetY(This,pVal)

#define IotCharMarkerSymbol_put_OffsetY(This,newVal)	\
    (This)->lpVtbl -> put_OffsetY(This,newVal)

#define IotCharMarkerSymbol_get_Angle(This,pVal)	\
    (This)->lpVtbl -> get_Angle(This,pVal)

#define IotCharMarkerSymbol_put_Angle(This,newVal)	\
    (This)->lpVtbl -> put_Angle(This,newVal)

#define IotCharMarkerSymbol_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IotCharMarkerSymbol_put_Size(This,newVal)	\
    (This)->lpVtbl -> put_Size(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotCharMarkerSymbol_INTERFACE_DEFINED__ */


#ifndef __IotArrowMarkerSymbol_INTERFACE_DEFINED__
#define __IotArrowMarkerSymbol_INTERFACE_DEFINED__

/* interface IotArrowMarkerSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotArrowMarkerSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C43B9169-5882-4704-A02D-40E6FA9F095F")
    IotArrowMarkerSymbol : public IotMarkerSymbol
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotArrowMarkerSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotArrowMarkerSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotArrowMarkerSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotArrowMarkerSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotArrowMarkerSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotArrowMarkerSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotArrowMarkerSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotArrowMarkerSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotArrowMarkerSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetX )( 
            IotArrowMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetX )( 
            IotArrowMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetY )( 
            IotArrowMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetY )( 
            IotArrowMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IotArrowMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Angle )( 
            IotArrowMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IotArrowMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            IotArrowMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        END_INTERFACE
    } IotArrowMarkerSymbolVtbl;

    interface IotArrowMarkerSymbol
    {
        CONST_VTBL struct IotArrowMarkerSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotArrowMarkerSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotArrowMarkerSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotArrowMarkerSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotArrowMarkerSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotArrowMarkerSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotArrowMarkerSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotArrowMarkerSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotArrowMarkerSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#define IotArrowMarkerSymbol_get_OffsetX(This,pVal)	\
    (This)->lpVtbl -> get_OffsetX(This,pVal)

#define IotArrowMarkerSymbol_put_OffsetX(This,newVal)	\
    (This)->lpVtbl -> put_OffsetX(This,newVal)

#define IotArrowMarkerSymbol_get_OffsetY(This,pVal)	\
    (This)->lpVtbl -> get_OffsetY(This,pVal)

#define IotArrowMarkerSymbol_put_OffsetY(This,newVal)	\
    (This)->lpVtbl -> put_OffsetY(This,newVal)

#define IotArrowMarkerSymbol_get_Angle(This,pVal)	\
    (This)->lpVtbl -> get_Angle(This,pVal)

#define IotArrowMarkerSymbol_put_Angle(This,newVal)	\
    (This)->lpVtbl -> put_Angle(This,newVal)

#define IotArrowMarkerSymbol_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IotArrowMarkerSymbol_put_Size(This,newVal)	\
    (This)->lpVtbl -> put_Size(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotArrowMarkerSymbol_INTERFACE_DEFINED__ */


#ifndef __IotPicMarkerSymbol_INTERFACE_DEFINED__
#define __IotPicMarkerSymbol_INTERFACE_DEFINED__

/* interface IotPicMarkerSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotPicMarkerSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("59480D48-BA1B-4684-B932-05F177699F2E")
    IotPicMarkerSymbol : public IotMarkerSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PictureFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PictureFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TransparentColor( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TransparentColor( 
            /* [in] */ IotColor *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundColor( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BackgroundColor( 
            /* [in] */ IotColor *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotPicMarkerSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotPicMarkerSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotPicMarkerSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotPicMarkerSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotPicMarkerSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotPicMarkerSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetX )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetX )( 
            IotPicMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetY )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetY )( 
            IotPicMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Angle )( 
            IotPicMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            IotPicMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PictureFile )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PictureFile )( 
            IotPicMarkerSymbol * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransparentColor )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransparentColor )( 
            IotPicMarkerSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundColor )( 
            IotPicMarkerSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackgroundColor )( 
            IotPicMarkerSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotPicMarkerSymbolVtbl;

    interface IotPicMarkerSymbol
    {
        CONST_VTBL struct IotPicMarkerSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotPicMarkerSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotPicMarkerSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotPicMarkerSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotPicMarkerSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotPicMarkerSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotPicMarkerSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotPicMarkerSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotPicMarkerSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#define IotPicMarkerSymbol_get_OffsetX(This,pVal)	\
    (This)->lpVtbl -> get_OffsetX(This,pVal)

#define IotPicMarkerSymbol_put_OffsetX(This,newVal)	\
    (This)->lpVtbl -> put_OffsetX(This,newVal)

#define IotPicMarkerSymbol_get_OffsetY(This,pVal)	\
    (This)->lpVtbl -> get_OffsetY(This,pVal)

#define IotPicMarkerSymbol_put_OffsetY(This,newVal)	\
    (This)->lpVtbl -> put_OffsetY(This,newVal)

#define IotPicMarkerSymbol_get_Angle(This,pVal)	\
    (This)->lpVtbl -> get_Angle(This,pVal)

#define IotPicMarkerSymbol_put_Angle(This,newVal)	\
    (This)->lpVtbl -> put_Angle(This,newVal)

#define IotPicMarkerSymbol_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IotPicMarkerSymbol_put_Size(This,newVal)	\
    (This)->lpVtbl -> put_Size(This,newVal)


#define IotPicMarkerSymbol_get_PictureFile(This,pVal)	\
    (This)->lpVtbl -> get_PictureFile(This,pVal)

#define IotPicMarkerSymbol_put_PictureFile(This,newVal)	\
    (This)->lpVtbl -> put_PictureFile(This,newVal)

#define IotPicMarkerSymbol_get_TransparentColor(This,pVal)	\
    (This)->lpVtbl -> get_TransparentColor(This,pVal)

#define IotPicMarkerSymbol_put_TransparentColor(This,newVal)	\
    (This)->lpVtbl -> put_TransparentColor(This,newVal)

#define IotPicMarkerSymbol_get_BackgroundColor(This,pVal)	\
    (This)->lpVtbl -> get_BackgroundColor(This,pVal)

#define IotPicMarkerSymbol_put_BackgroundColor(This,newVal)	\
    (This)->lpVtbl -> put_BackgroundColor(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPicMarkerSymbol_get_PictureFile_Proxy( 
    IotPicMarkerSymbol * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotPicMarkerSymbol_get_PictureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPicMarkerSymbol_put_PictureFile_Proxy( 
    IotPicMarkerSymbol * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotPicMarkerSymbol_put_PictureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPicMarkerSymbol_get_TransparentColor_Proxy( 
    IotPicMarkerSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotPicMarkerSymbol_get_TransparentColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPicMarkerSymbol_put_TransparentColor_Proxy( 
    IotPicMarkerSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotPicMarkerSymbol_put_TransparentColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPicMarkerSymbol_get_BackgroundColor_Proxy( 
    IotPicMarkerSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotPicMarkerSymbol_get_BackgroundColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPicMarkerSymbol_put_BackgroundColor_Proxy( 
    IotPicMarkerSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotPicMarkerSymbol_put_BackgroundColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotPicMarkerSymbol_INTERFACE_DEFINED__ */


#ifndef __IotSimpleLineSymbol_INTERFACE_DEFINED__
#define __IotSimpleLineSymbol_INTERFACE_DEFINED__

/* interface IotSimpleLineSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSimpleLineSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EDA46204-CF12-4BF3-8811-2DAFB54E8BB9")
    IotSimpleLineSymbol : public IotLineSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LineStyle( 
            /* [retval][out] */ otSimpleLineStyle *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LineStyle( 
            /* [in] */ otSimpleLineStyle newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSimpleLineSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSimpleLineSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSimpleLineSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSimpleLineSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotSimpleLineSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotSimpleLineSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotSimpleLineSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineWidth )( 
            IotSimpleLineSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineWidth )( 
            IotSimpleLineSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotSimpleLineSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotSimpleLineSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineStyle )( 
            IotSimpleLineSymbol * This,
            /* [retval][out] */ otSimpleLineStyle *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineStyle )( 
            IotSimpleLineSymbol * This,
            /* [in] */ otSimpleLineStyle newVal);
        
        END_INTERFACE
    } IotSimpleLineSymbolVtbl;

    interface IotSimpleLineSymbol
    {
        CONST_VTBL struct IotSimpleLineSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSimpleLineSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSimpleLineSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSimpleLineSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSimpleLineSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotSimpleLineSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotSimpleLineSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotSimpleLineSymbol_get_LineWidth(This,pVal)	\
    (This)->lpVtbl -> get_LineWidth(This,pVal)

#define IotSimpleLineSymbol_put_LineWidth(This,newVal)	\
    (This)->lpVtbl -> put_LineWidth(This,newVal)

#define IotSimpleLineSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotSimpleLineSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)


#define IotSimpleLineSymbol_get_LineStyle(This,pVal)	\
    (This)->lpVtbl -> get_LineStyle(This,pVal)

#define IotSimpleLineSymbol_put_LineStyle(This,newVal)	\
    (This)->lpVtbl -> put_LineStyle(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSimpleLineSymbol_get_LineStyle_Proxy( 
    IotSimpleLineSymbol * This,
    /* [retval][out] */ otSimpleLineStyle *pVal);


void __RPC_STUB IotSimpleLineSymbol_get_LineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSimpleLineSymbol_put_LineStyle_Proxy( 
    IotSimpleLineSymbol * This,
    /* [in] */ otSimpleLineStyle newVal);


void __RPC_STUB IotSimpleLineSymbol_put_LineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSimpleLineSymbol_INTERFACE_DEFINED__ */


#ifndef __IotAdvLineSymbol_INTERFACE_DEFINED__
#define __IotAdvLineSymbol_INTERFACE_DEFINED__

/* interface IotAdvLineSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotAdvLineSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FDDD408D-5B2A-4232-BBF2-FF2D4BE46A12")
    IotAdvLineSymbol : public IotLineSymbol
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotAdvLineSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotAdvLineSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotAdvLineSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotAdvLineSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotAdvLineSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotAdvLineSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotAdvLineSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineWidth )( 
            IotAdvLineSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineWidth )( 
            IotAdvLineSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotAdvLineSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotAdvLineSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotAdvLineSymbolVtbl;

    interface IotAdvLineSymbol
    {
        CONST_VTBL struct IotAdvLineSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotAdvLineSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotAdvLineSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotAdvLineSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotAdvLineSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotAdvLineSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotAdvLineSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotAdvLineSymbol_get_LineWidth(This,pVal)	\
    (This)->lpVtbl -> get_LineWidth(This,pVal)

#define IotAdvLineSymbol_put_LineWidth(This,newVal)	\
    (This)->lpVtbl -> put_LineWidth(This,newVal)

#define IotAdvLineSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotAdvLineSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotAdvLineSymbol_INTERFACE_DEFINED__ */


#ifndef __IotHashLineSymbol_INTERFACE_DEFINED__
#define __IotHashLineSymbol_INTERFACE_DEFINED__

/* interface IotHashLineSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotHashLineSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6C75C746-7EBC-40A1-84D0-3F2B4165413D")
    IotHashLineSymbol : public IotLineSymbol
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotHashLineSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotHashLineSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotHashLineSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotHashLineSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotHashLineSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotHashLineSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotHashLineSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineWidth )( 
            IotHashLineSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineWidth )( 
            IotHashLineSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotHashLineSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotHashLineSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotHashLineSymbolVtbl;

    interface IotHashLineSymbol
    {
        CONST_VTBL struct IotHashLineSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotHashLineSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotHashLineSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotHashLineSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotHashLineSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotHashLineSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotHashLineSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotHashLineSymbol_get_LineWidth(This,pVal)	\
    (This)->lpVtbl -> get_LineWidth(This,pVal)

#define IotHashLineSymbol_put_LineWidth(This,newVal)	\
    (This)->lpVtbl -> put_LineWidth(This,newVal)

#define IotHashLineSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotHashLineSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotHashLineSymbol_INTERFACE_DEFINED__ */


#ifndef __IotMarkerLineSymbol_INTERFACE_DEFINED__
#define __IotMarkerLineSymbol_INTERFACE_DEFINED__

/* interface IotMarkerLineSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotMarkerLineSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21D5AFE5-E6C8-4048-BB4B-34B038E0D382")
    IotMarkerLineSymbol : public IotLineSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MarkerSymbol( 
            /* [retval][out] */ IotMarkerSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MarkerSymbol( 
            /* [in] */ IotMarkerSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotMarkerLineSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotMarkerLineSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotMarkerLineSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotMarkerLineSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotMarkerLineSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotMarkerLineSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotMarkerLineSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineWidth )( 
            IotMarkerLineSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineWidth )( 
            IotMarkerLineSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotMarkerLineSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotMarkerLineSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkerSymbol )( 
            IotMarkerLineSymbol * This,
            /* [retval][out] */ IotMarkerSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkerSymbol )( 
            IotMarkerLineSymbol * This,
            /* [in] */ IotMarkerSymbol *newVal);
        
        END_INTERFACE
    } IotMarkerLineSymbolVtbl;

    interface IotMarkerLineSymbol
    {
        CONST_VTBL struct IotMarkerLineSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotMarkerLineSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotMarkerLineSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotMarkerLineSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotMarkerLineSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotMarkerLineSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotMarkerLineSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotMarkerLineSymbol_get_LineWidth(This,pVal)	\
    (This)->lpVtbl -> get_LineWidth(This,pVal)

#define IotMarkerLineSymbol_put_LineWidth(This,newVal)	\
    (This)->lpVtbl -> put_LineWidth(This,newVal)

#define IotMarkerLineSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotMarkerLineSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)


#define IotMarkerLineSymbol_get_MarkerSymbol(This,pVal)	\
    (This)->lpVtbl -> get_MarkerSymbol(This,pVal)

#define IotMarkerLineSymbol_put_MarkerSymbol(This,newVal)	\
    (This)->lpVtbl -> put_MarkerSymbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerLineSymbol_get_MarkerSymbol_Proxy( 
    IotMarkerLineSymbol * This,
    /* [retval][out] */ IotMarkerSymbol **pVal);


void __RPC_STUB IotMarkerLineSymbol_get_MarkerSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerLineSymbol_put_MarkerSymbol_Proxy( 
    IotMarkerLineSymbol * This,
    /* [in] */ IotMarkerSymbol *newVal);


void __RPC_STUB IotMarkerLineSymbol_put_MarkerSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotMarkerLineSymbol_INTERFACE_DEFINED__ */


#ifndef __IotSimpleFillSymbol_INTERFACE_DEFINED__
#define __IotSimpleFillSymbol_INTERFACE_DEFINED__

/* interface IotSimpleFillSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSimpleFillSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7E000018-2A71-46F6-AD2F-BF89B66B4CED")
    IotSimpleFillSymbol : public IotFillSymbol
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotSimpleFillSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSimpleFillSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSimpleFillSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSimpleFillSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotSimpleFillSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotSimpleFillSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotSimpleFillSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawOutLine )( 
            IotSimpleFillSymbol * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawOutLine )( 
            IotSimpleFillSymbol * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutLine )( 
            IotSimpleFillSymbol * This,
            /* [retval][out] */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutLine )( 
            IotSimpleFillSymbol * This,
            /* [in] */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillColor )( 
            IotSimpleFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillColor )( 
            IotSimpleFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotSimpleFillSymbolVtbl;

    interface IotSimpleFillSymbol
    {
        CONST_VTBL struct IotSimpleFillSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSimpleFillSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSimpleFillSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSimpleFillSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSimpleFillSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotSimpleFillSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotSimpleFillSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotSimpleFillSymbol_get_DrawOutLine(This,pVal)	\
    (This)->lpVtbl -> get_DrawOutLine(This,pVal)

#define IotSimpleFillSymbol_put_DrawOutLine(This,newVal)	\
    (This)->lpVtbl -> put_DrawOutLine(This,newVal)

#define IotSimpleFillSymbol_get_OutLine(This,pVal)	\
    (This)->lpVtbl -> get_OutLine(This,pVal)

#define IotSimpleFillSymbol_put_OutLine(This,newVal)	\
    (This)->lpVtbl -> put_OutLine(This,newVal)

#define IotSimpleFillSymbol_get_FillColor(This,pVal)	\
    (This)->lpVtbl -> get_FillColor(This,pVal)

#define IotSimpleFillSymbol_put_FillColor(This,newVal)	\
    (This)->lpVtbl -> put_FillColor(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotSimpleFillSymbol_INTERFACE_DEFINED__ */


#ifndef __IotLineFillSymbol_INTERFACE_DEFINED__
#define __IotLineFillSymbol_INTERFACE_DEFINED__

/* interface IotLineFillSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotLineFillSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("398832F1-2E6D-45DB-9C8D-AE154F85E613")
    IotLineFillSymbol : public IotFillSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Angle( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Angle( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_separation( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_separation( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Offset( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Offset( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LineSymbol( 
            /* [retval][out] */ IotLineSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LineSymbol( 
            /* [in] */ IotLineSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotLineFillSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotLineFillSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotLineFillSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotLineFillSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotLineFillSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotLineFillSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotLineFillSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawOutLine )( 
            IotLineFillSymbol * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawOutLine )( 
            IotLineFillSymbol * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutLine )( 
            IotLineFillSymbol * This,
            /* [retval][out] */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutLine )( 
            IotLineFillSymbol * This,
            /* [in] */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillColor )( 
            IotLineFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillColor )( 
            IotLineFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IotLineFillSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Angle )( 
            IotLineFillSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_separation )( 
            IotLineFillSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_separation )( 
            IotLineFillSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Offset )( 
            IotLineFillSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Offset )( 
            IotLineFillSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineSymbol )( 
            IotLineFillSymbol * This,
            /* [retval][out] */ IotLineSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineSymbol )( 
            IotLineFillSymbol * This,
            /* [in] */ IotLineSymbol *newVal);
        
        END_INTERFACE
    } IotLineFillSymbolVtbl;

    interface IotLineFillSymbol
    {
        CONST_VTBL struct IotLineFillSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotLineFillSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotLineFillSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotLineFillSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotLineFillSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotLineFillSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotLineFillSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotLineFillSymbol_get_DrawOutLine(This,pVal)	\
    (This)->lpVtbl -> get_DrawOutLine(This,pVal)

#define IotLineFillSymbol_put_DrawOutLine(This,newVal)	\
    (This)->lpVtbl -> put_DrawOutLine(This,newVal)

#define IotLineFillSymbol_get_OutLine(This,pVal)	\
    (This)->lpVtbl -> get_OutLine(This,pVal)

#define IotLineFillSymbol_put_OutLine(This,newVal)	\
    (This)->lpVtbl -> put_OutLine(This,newVal)

#define IotLineFillSymbol_get_FillColor(This,pVal)	\
    (This)->lpVtbl -> get_FillColor(This,pVal)

#define IotLineFillSymbol_put_FillColor(This,newVal)	\
    (This)->lpVtbl -> put_FillColor(This,newVal)


#define IotLineFillSymbol_get_Angle(This,pVal)	\
    (This)->lpVtbl -> get_Angle(This,pVal)

#define IotLineFillSymbol_put_Angle(This,newVal)	\
    (This)->lpVtbl -> put_Angle(This,newVal)

#define IotLineFillSymbol_get_separation(This,pVal)	\
    (This)->lpVtbl -> get_separation(This,pVal)

#define IotLineFillSymbol_put_separation(This,newVal)	\
    (This)->lpVtbl -> put_separation(This,newVal)

#define IotLineFillSymbol_get_Offset(This,pVal)	\
    (This)->lpVtbl -> get_Offset(This,pVal)

#define IotLineFillSymbol_put_Offset(This,newVal)	\
    (This)->lpVtbl -> put_Offset(This,newVal)

#define IotLineFillSymbol_get_LineSymbol(This,pVal)	\
    (This)->lpVtbl -> get_LineSymbol(This,pVal)

#define IotLineFillSymbol_put_LineSymbol(This,newVal)	\
    (This)->lpVtbl -> put_LineSymbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLineFillSymbol_get_Angle_Proxy( 
    IotLineFillSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotLineFillSymbol_get_Angle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLineFillSymbol_put_Angle_Proxy( 
    IotLineFillSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotLineFillSymbol_put_Angle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLineFillSymbol_get_separation_Proxy( 
    IotLineFillSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotLineFillSymbol_get_separation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLineFillSymbol_put_separation_Proxy( 
    IotLineFillSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotLineFillSymbol_put_separation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLineFillSymbol_get_Offset_Proxy( 
    IotLineFillSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotLineFillSymbol_get_Offset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLineFillSymbol_put_Offset_Proxy( 
    IotLineFillSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotLineFillSymbol_put_Offset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLineFillSymbol_get_LineSymbol_Proxy( 
    IotLineFillSymbol * This,
    /* [retval][out] */ IotLineSymbol **pVal);


void __RPC_STUB IotLineFillSymbol_get_LineSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLineFillSymbol_put_LineSymbol_Proxy( 
    IotLineFillSymbol * This,
    /* [in] */ IotLineSymbol *newVal);


void __RPC_STUB IotLineFillSymbol_put_LineSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotLineFillSymbol_INTERFACE_DEFINED__ */


#ifndef __IotMarkerFillSymbol_INTERFACE_DEFINED__
#define __IotMarkerFillSymbol_INTERFACE_DEFINED__

/* interface IotMarkerFillSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotMarkerFillSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B26681BD-81F8-43BF-A229-ACAA3623B48F")
    IotMarkerFillSymbol : public IotFillSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OffsetX( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OffsetX( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OffsetY( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OffsetY( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SeparationX( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SeparationX( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SeparationY( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SeparationY( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MarkSymbol( 
            /* [retval][out] */ IotMarkerSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MarkSymbol( 
            /* [in] */ IotMarkerSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotMarkerFillSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotMarkerFillSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotMarkerFillSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotMarkerFillSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotMarkerFillSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawOutLine )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawOutLine )( 
            IotMarkerFillSymbol * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutLine )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutLine )( 
            IotMarkerFillSymbol * This,
            /* [in] */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillColor )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillColor )( 
            IotMarkerFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetX )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetX )( 
            IotMarkerFillSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetY )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetY )( 
            IotMarkerFillSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SeparationX )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SeparationX )( 
            IotMarkerFillSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SeparationY )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SeparationY )( 
            IotMarkerFillSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkSymbol )( 
            IotMarkerFillSymbol * This,
            /* [retval][out] */ IotMarkerSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkSymbol )( 
            IotMarkerFillSymbol * This,
            /* [in] */ IotMarkerSymbol *newVal);
        
        END_INTERFACE
    } IotMarkerFillSymbolVtbl;

    interface IotMarkerFillSymbol
    {
        CONST_VTBL struct IotMarkerFillSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotMarkerFillSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotMarkerFillSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotMarkerFillSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotMarkerFillSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotMarkerFillSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotMarkerFillSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotMarkerFillSymbol_get_DrawOutLine(This,pVal)	\
    (This)->lpVtbl -> get_DrawOutLine(This,pVal)

#define IotMarkerFillSymbol_put_DrawOutLine(This,newVal)	\
    (This)->lpVtbl -> put_DrawOutLine(This,newVal)

#define IotMarkerFillSymbol_get_OutLine(This,pVal)	\
    (This)->lpVtbl -> get_OutLine(This,pVal)

#define IotMarkerFillSymbol_put_OutLine(This,newVal)	\
    (This)->lpVtbl -> put_OutLine(This,newVal)

#define IotMarkerFillSymbol_get_FillColor(This,pVal)	\
    (This)->lpVtbl -> get_FillColor(This,pVal)

#define IotMarkerFillSymbol_put_FillColor(This,newVal)	\
    (This)->lpVtbl -> put_FillColor(This,newVal)


#define IotMarkerFillSymbol_get_OffsetX(This,pVal)	\
    (This)->lpVtbl -> get_OffsetX(This,pVal)

#define IotMarkerFillSymbol_put_OffsetX(This,newVal)	\
    (This)->lpVtbl -> put_OffsetX(This,newVal)

#define IotMarkerFillSymbol_get_OffsetY(This,pVal)	\
    (This)->lpVtbl -> get_OffsetY(This,pVal)

#define IotMarkerFillSymbol_put_OffsetY(This,newVal)	\
    (This)->lpVtbl -> put_OffsetY(This,newVal)

#define IotMarkerFillSymbol_get_SeparationX(This,pVal)	\
    (This)->lpVtbl -> get_SeparationX(This,pVal)

#define IotMarkerFillSymbol_put_SeparationX(This,newVal)	\
    (This)->lpVtbl -> put_SeparationX(This,newVal)

#define IotMarkerFillSymbol_get_SeparationY(This,pVal)	\
    (This)->lpVtbl -> get_SeparationY(This,pVal)

#define IotMarkerFillSymbol_put_SeparationY(This,newVal)	\
    (This)->lpVtbl -> put_SeparationY(This,newVal)

#define IotMarkerFillSymbol_get_MarkSymbol(This,pVal)	\
    (This)->lpVtbl -> get_MarkSymbol(This,pVal)

#define IotMarkerFillSymbol_put_MarkSymbol(This,newVal)	\
    (This)->lpVtbl -> put_MarkSymbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_get_OffsetX_Proxy( 
    IotMarkerFillSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMarkerFillSymbol_get_OffsetX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_put_OffsetX_Proxy( 
    IotMarkerFillSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotMarkerFillSymbol_put_OffsetX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_get_OffsetY_Proxy( 
    IotMarkerFillSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMarkerFillSymbol_get_OffsetY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_put_OffsetY_Proxy( 
    IotMarkerFillSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotMarkerFillSymbol_put_OffsetY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_get_SeparationX_Proxy( 
    IotMarkerFillSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMarkerFillSymbol_get_SeparationX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_put_SeparationX_Proxy( 
    IotMarkerFillSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotMarkerFillSymbol_put_SeparationX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_get_SeparationY_Proxy( 
    IotMarkerFillSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMarkerFillSymbol_get_SeparationY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_put_SeparationY_Proxy( 
    IotMarkerFillSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotMarkerFillSymbol_put_SeparationY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_get_MarkSymbol_Proxy( 
    IotMarkerFillSymbol * This,
    /* [retval][out] */ IotMarkerSymbol **pVal);


void __RPC_STUB IotMarkerFillSymbol_get_MarkSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerFillSymbol_put_MarkSymbol_Proxy( 
    IotMarkerFillSymbol * This,
    /* [in] */ IotMarkerSymbol *newVal);


void __RPC_STUB IotMarkerFillSymbol_put_MarkSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotMarkerFillSymbol_INTERFACE_DEFINED__ */


#ifndef __IotPicFillSymbol_INTERFACE_DEFINED__
#define __IotPicFillSymbol_INTERFACE_DEFINED__

/* interface IotPicFillSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotPicFillSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E814FCE-21F8-4C1F-A7A7-F5BA00FF33F7")
    IotPicFillSymbol : public IotFillSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PictureFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PictureFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundColor( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BackgroundColor( 
            /* [in] */ IotColor *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TransparentColor( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TransparentColor( 
            /* [in] */ IotColor *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotPicFillSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotPicFillSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotPicFillSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotPicFillSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotPicFillSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotPicFillSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotPicFillSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawOutLine )( 
            IotPicFillSymbol * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawOutLine )( 
            IotPicFillSymbol * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutLine )( 
            IotPicFillSymbol * This,
            /* [retval][out] */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutLine )( 
            IotPicFillSymbol * This,
            /* [in] */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillColor )( 
            IotPicFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillColor )( 
            IotPicFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PictureFile )( 
            IotPicFillSymbol * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PictureFile )( 
            IotPicFillSymbol * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundColor )( 
            IotPicFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackgroundColor )( 
            IotPicFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransparentColor )( 
            IotPicFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransparentColor )( 
            IotPicFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotPicFillSymbolVtbl;

    interface IotPicFillSymbol
    {
        CONST_VTBL struct IotPicFillSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotPicFillSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotPicFillSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotPicFillSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotPicFillSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotPicFillSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotPicFillSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotPicFillSymbol_get_DrawOutLine(This,pVal)	\
    (This)->lpVtbl -> get_DrawOutLine(This,pVal)

#define IotPicFillSymbol_put_DrawOutLine(This,newVal)	\
    (This)->lpVtbl -> put_DrawOutLine(This,newVal)

#define IotPicFillSymbol_get_OutLine(This,pVal)	\
    (This)->lpVtbl -> get_OutLine(This,pVal)

#define IotPicFillSymbol_put_OutLine(This,newVal)	\
    (This)->lpVtbl -> put_OutLine(This,newVal)

#define IotPicFillSymbol_get_FillColor(This,pVal)	\
    (This)->lpVtbl -> get_FillColor(This,pVal)

#define IotPicFillSymbol_put_FillColor(This,newVal)	\
    (This)->lpVtbl -> put_FillColor(This,newVal)


#define IotPicFillSymbol_get_PictureFile(This,pVal)	\
    (This)->lpVtbl -> get_PictureFile(This,pVal)

#define IotPicFillSymbol_put_PictureFile(This,newVal)	\
    (This)->lpVtbl -> put_PictureFile(This,newVal)

#define IotPicFillSymbol_get_BackgroundColor(This,pVal)	\
    (This)->lpVtbl -> get_BackgroundColor(This,pVal)

#define IotPicFillSymbol_put_BackgroundColor(This,newVal)	\
    (This)->lpVtbl -> put_BackgroundColor(This,newVal)

#define IotPicFillSymbol_get_TransparentColor(This,pVal)	\
    (This)->lpVtbl -> get_TransparentColor(This,pVal)

#define IotPicFillSymbol_put_TransparentColor(This,newVal)	\
    (This)->lpVtbl -> put_TransparentColor(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPicFillSymbol_get_PictureFile_Proxy( 
    IotPicFillSymbol * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotPicFillSymbol_get_PictureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPicFillSymbol_put_PictureFile_Proxy( 
    IotPicFillSymbol * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotPicFillSymbol_put_PictureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPicFillSymbol_get_BackgroundColor_Proxy( 
    IotPicFillSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotPicFillSymbol_get_BackgroundColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPicFillSymbol_put_BackgroundColor_Proxy( 
    IotPicFillSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotPicFillSymbol_put_BackgroundColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPicFillSymbol_get_TransparentColor_Proxy( 
    IotPicFillSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotPicFillSymbol_get_TransparentColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPicFillSymbol_put_TransparentColor_Proxy( 
    IotPicFillSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotPicFillSymbol_put_TransparentColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotPicFillSymbol_INTERFACE_DEFINED__ */


#ifndef __IotGradientFillSymbol_INTERFACE_DEFINED__
#define __IotGradientFillSymbol_INTERFACE_DEFINED__

/* interface IotGradientFillSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotGradientFillSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E914FCE-21F8-4C1F-A747-F5BA00EF33A7")
    IotGradientFillSymbol : public IotFillSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BeginColor( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BeginColor( 
            /* [in] */ IotColor *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndColor( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndColor( 
            /* [in] */ IotColor *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GradientFillType( 
            /* [retval][out] */ otGradientFillType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GradientFillType( 
            /* [in] */ otGradientFillType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentCounts( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SegmentCounts( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Percent( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Percent( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Angle( 
            /* [retval][out] */ FLOAT *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Angle( 
            /* [in] */ FLOAT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotGradientFillSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotGradientFillSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotGradientFillSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotGradientFillSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotGradientFillSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawOutLine )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawOutLine )( 
            IotGradientFillSymbol * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutLine )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutLine )( 
            IotGradientFillSymbol * This,
            /* [in] */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillColor )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillColor )( 
            IotGradientFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BeginColor )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BeginColor )( 
            IotGradientFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndColor )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndColor )( 
            IotGradientFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GradientFillType )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ otGradientFillType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GradientFillType )( 
            IotGradientFillSymbol * This,
            /* [in] */ otGradientFillType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentCounts )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SegmentCounts )( 
            IotGradientFillSymbol * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Percent )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Percent )( 
            IotGradientFillSymbol * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IotGradientFillSymbol * This,
            /* [retval][out] */ FLOAT *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Angle )( 
            IotGradientFillSymbol * This,
            /* [in] */ FLOAT newVal);
        
        END_INTERFACE
    } IotGradientFillSymbolVtbl;

    interface IotGradientFillSymbol
    {
        CONST_VTBL struct IotGradientFillSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotGradientFillSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotGradientFillSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotGradientFillSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotGradientFillSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotGradientFillSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotGradientFillSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotGradientFillSymbol_get_DrawOutLine(This,pVal)	\
    (This)->lpVtbl -> get_DrawOutLine(This,pVal)

#define IotGradientFillSymbol_put_DrawOutLine(This,newVal)	\
    (This)->lpVtbl -> put_DrawOutLine(This,newVal)

#define IotGradientFillSymbol_get_OutLine(This,pVal)	\
    (This)->lpVtbl -> get_OutLine(This,pVal)

#define IotGradientFillSymbol_put_OutLine(This,newVal)	\
    (This)->lpVtbl -> put_OutLine(This,newVal)

#define IotGradientFillSymbol_get_FillColor(This,pVal)	\
    (This)->lpVtbl -> get_FillColor(This,pVal)

#define IotGradientFillSymbol_put_FillColor(This,newVal)	\
    (This)->lpVtbl -> put_FillColor(This,newVal)


#define IotGradientFillSymbol_get_BeginColor(This,pVal)	\
    (This)->lpVtbl -> get_BeginColor(This,pVal)

#define IotGradientFillSymbol_put_BeginColor(This,newVal)	\
    (This)->lpVtbl -> put_BeginColor(This,newVal)

#define IotGradientFillSymbol_get_EndColor(This,pVal)	\
    (This)->lpVtbl -> get_EndColor(This,pVal)

#define IotGradientFillSymbol_put_EndColor(This,newVal)	\
    (This)->lpVtbl -> put_EndColor(This,newVal)

#define IotGradientFillSymbol_get_GradientFillType(This,pVal)	\
    (This)->lpVtbl -> get_GradientFillType(This,pVal)

#define IotGradientFillSymbol_put_GradientFillType(This,newVal)	\
    (This)->lpVtbl -> put_GradientFillType(This,newVal)

#define IotGradientFillSymbol_get_SegmentCounts(This,pVal)	\
    (This)->lpVtbl -> get_SegmentCounts(This,pVal)

#define IotGradientFillSymbol_put_SegmentCounts(This,newVal)	\
    (This)->lpVtbl -> put_SegmentCounts(This,newVal)

#define IotGradientFillSymbol_get_Percent(This,pVal)	\
    (This)->lpVtbl -> get_Percent(This,pVal)

#define IotGradientFillSymbol_put_Percent(This,newVal)	\
    (This)->lpVtbl -> put_Percent(This,newVal)

#define IotGradientFillSymbol_get_Angle(This,pVal)	\
    (This)->lpVtbl -> get_Angle(This,pVal)

#define IotGradientFillSymbol_put_Angle(This,newVal)	\
    (This)->lpVtbl -> put_Angle(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_get_BeginColor_Proxy( 
    IotGradientFillSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotGradientFillSymbol_get_BeginColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_put_BeginColor_Proxy( 
    IotGradientFillSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotGradientFillSymbol_put_BeginColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_get_EndColor_Proxy( 
    IotGradientFillSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotGradientFillSymbol_get_EndColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_put_EndColor_Proxy( 
    IotGradientFillSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotGradientFillSymbol_put_EndColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_get_GradientFillType_Proxy( 
    IotGradientFillSymbol * This,
    /* [retval][out] */ otGradientFillType *pVal);


void __RPC_STUB IotGradientFillSymbol_get_GradientFillType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_put_GradientFillType_Proxy( 
    IotGradientFillSymbol * This,
    /* [in] */ otGradientFillType newVal);


void __RPC_STUB IotGradientFillSymbol_put_GradientFillType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_get_SegmentCounts_Proxy( 
    IotGradientFillSymbol * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotGradientFillSymbol_get_SegmentCounts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_put_SegmentCounts_Proxy( 
    IotGradientFillSymbol * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotGradientFillSymbol_put_SegmentCounts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_get_Percent_Proxy( 
    IotGradientFillSymbol * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotGradientFillSymbol_get_Percent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_put_Percent_Proxy( 
    IotGradientFillSymbol * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotGradientFillSymbol_put_Percent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_get_Angle_Proxy( 
    IotGradientFillSymbol * This,
    /* [retval][out] */ FLOAT *pVal);


void __RPC_STUB IotGradientFillSymbol_get_Angle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotGradientFillSymbol_put_Angle_Proxy( 
    IotGradientFillSymbol * This,
    /* [in] */ FLOAT newVal);


void __RPC_STUB IotGradientFillSymbol_put_Angle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotGradientFillSymbol_INTERFACE_DEFINED__ */


#ifndef __IotComplexMarkerSymbol_INTERFACE_DEFINED__
#define __IotComplexMarkerSymbol_INTERFACE_DEFINED__

/* interface IotComplexMarkerSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotComplexMarkerSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("16F3B5D1-4723-4645-A2A8-369F6DFCC9E9")
    IotComplexMarkerSymbol : public IotMarkerSymbol
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotComplexMarkerSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotComplexMarkerSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotComplexMarkerSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotComplexMarkerSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotComplexMarkerSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotComplexMarkerSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotComplexMarkerSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotComplexMarkerSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotComplexMarkerSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetX )( 
            IotComplexMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetX )( 
            IotComplexMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetY )( 
            IotComplexMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetY )( 
            IotComplexMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IotComplexMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Angle )( 
            IotComplexMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IotComplexMarkerSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            IotComplexMarkerSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        END_INTERFACE
    } IotComplexMarkerSymbolVtbl;

    interface IotComplexMarkerSymbol
    {
        CONST_VTBL struct IotComplexMarkerSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotComplexMarkerSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotComplexMarkerSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotComplexMarkerSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotComplexMarkerSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotComplexMarkerSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotComplexMarkerSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotComplexMarkerSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotComplexMarkerSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#define IotComplexMarkerSymbol_get_OffsetX(This,pVal)	\
    (This)->lpVtbl -> get_OffsetX(This,pVal)

#define IotComplexMarkerSymbol_put_OffsetX(This,newVal)	\
    (This)->lpVtbl -> put_OffsetX(This,newVal)

#define IotComplexMarkerSymbol_get_OffsetY(This,pVal)	\
    (This)->lpVtbl -> get_OffsetY(This,pVal)

#define IotComplexMarkerSymbol_put_OffsetY(This,newVal)	\
    (This)->lpVtbl -> put_OffsetY(This,newVal)

#define IotComplexMarkerSymbol_get_Angle(This,pVal)	\
    (This)->lpVtbl -> get_Angle(This,pVal)

#define IotComplexMarkerSymbol_put_Angle(This,newVal)	\
    (This)->lpVtbl -> put_Angle(This,newVal)

#define IotComplexMarkerSymbol_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IotComplexMarkerSymbol_put_Size(This,newVal)	\
    (This)->lpVtbl -> put_Size(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotComplexMarkerSymbol_INTERFACE_DEFINED__ */


#ifndef __IotComplexLineSymbol_INTERFACE_DEFINED__
#define __IotComplexLineSymbol_INTERFACE_DEFINED__

/* interface IotComplexLineSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotComplexLineSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B0226DB-2624-45EF-A113-A8BC1F2E7D23")
    IotComplexLineSymbol : public IotLineSymbol
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotComplexLineSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotComplexLineSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotComplexLineSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotComplexLineSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotComplexLineSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotComplexLineSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotComplexLineSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineWidth )( 
            IotComplexLineSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineWidth )( 
            IotComplexLineSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IotComplexLineSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IotComplexLineSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotComplexLineSymbolVtbl;

    interface IotComplexLineSymbol
    {
        CONST_VTBL struct IotComplexLineSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotComplexLineSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotComplexLineSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotComplexLineSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotComplexLineSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotComplexLineSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotComplexLineSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotComplexLineSymbol_get_LineWidth(This,pVal)	\
    (This)->lpVtbl -> get_LineWidth(This,pVal)

#define IotComplexLineSymbol_put_LineWidth(This,newVal)	\
    (This)->lpVtbl -> put_LineWidth(This,newVal)

#define IotComplexLineSymbol_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IotComplexLineSymbol_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotComplexLineSymbol_INTERFACE_DEFINED__ */


#ifndef __IotComplexFillSymbol_INTERFACE_DEFINED__
#define __IotComplexFillSymbol_INTERFACE_DEFINED__

/* interface IotComplexFillSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotComplexFillSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D9CBB941-385C-4AF3-8DD8-503DF67103E4")
    IotComplexFillSymbol : public IotFillSymbol
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotComplexFillSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotComplexFillSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotComplexFillSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotComplexFillSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotComplexFillSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotComplexFillSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotComplexFillSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawOutLine )( 
            IotComplexFillSymbol * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawOutLine )( 
            IotComplexFillSymbol * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutLine )( 
            IotComplexFillSymbol * This,
            /* [retval][out] */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutLine )( 
            IotComplexFillSymbol * This,
            /* [in] */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillColor )( 
            IotComplexFillSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillColor )( 
            IotComplexFillSymbol * This,
            /* [in] */ IotColor *newVal);
        
        END_INTERFACE
    } IotComplexFillSymbolVtbl;

    interface IotComplexFillSymbol
    {
        CONST_VTBL struct IotComplexFillSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotComplexFillSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotComplexFillSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotComplexFillSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotComplexFillSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotComplexFillSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotComplexFillSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotComplexFillSymbol_get_DrawOutLine(This,pVal)	\
    (This)->lpVtbl -> get_DrawOutLine(This,pVal)

#define IotComplexFillSymbol_put_DrawOutLine(This,newVal)	\
    (This)->lpVtbl -> put_DrawOutLine(This,newVal)

#define IotComplexFillSymbol_get_OutLine(This,pVal)	\
    (This)->lpVtbl -> get_OutLine(This,pVal)

#define IotComplexFillSymbol_put_OutLine(This,newVal)	\
    (This)->lpVtbl -> put_OutLine(This,newVal)

#define IotComplexFillSymbol_get_FillColor(This,pVal)	\
    (This)->lpVtbl -> get_FillColor(This,pVal)

#define IotComplexFillSymbol_put_FillColor(This,newVal)	\
    (This)->lpVtbl -> put_FillColor(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotComplexFillSymbol_INTERFACE_DEFINED__ */


#ifndef __IotCanvas_INTERFACE_DEFINED__
#define __IotCanvas_INTERFACE_DEFINED__

/* interface IotCanvas */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotCanvas;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E269D07-6C04-443B-B560-6CF841926208")
    IotCanvas : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotCanvasVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotCanvas * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotCanvas * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotCanvas * This);
        
        END_INTERFACE
    } IotCanvasVtbl;

    interface IotCanvas
    {
        CONST_VTBL struct IotCanvasVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotCanvas_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotCanvas_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotCanvas_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotCanvas_INTERFACE_DEFINED__ */


#ifndef __IotSymbolConvert_INTERFACE_DEFINED__
#define __IotSymbolConvert_INTERFACE_DEFINED__

/* interface IotSymbolConvert */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSymbolConvert;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("751B8D1B-9231-48F0-8DEA-CD8B82F7A7E2")
    IotSymbolConvert : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertSymbol( 
            LONG ldata,
            /* [in] */ VARIANT_BOOL bown,
            /* [retval][out] */ IotSymbol **retSymbol) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSymbolConvertVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSymbolConvert * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSymbolConvert * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSymbolConvert * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertSymbol )( 
            IotSymbolConvert * This,
            LONG ldata,
            /* [in] */ VARIANT_BOOL bown,
            /* [retval][out] */ IotSymbol **retSymbol);
        
        END_INTERFACE
    } IotSymbolConvertVtbl;

    interface IotSymbolConvert
    {
        CONST_VTBL struct IotSymbolConvertVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSymbolConvert_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSymbolConvert_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSymbolConvert_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSymbolConvert_ConvertSymbol(This,ldata,bown,retSymbol)	\
    (This)->lpVtbl -> ConvertSymbol(This,ldata,bown,retSymbol)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSymbolConvert_ConvertSymbol_Proxy( 
    IotSymbolConvert * This,
    LONG ldata,
    /* [in] */ VARIANT_BOOL bown,
    /* [retval][out] */ IotSymbol **retSymbol);


void __RPC_STUB IotSymbolConvert_ConvertSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSymbolConvert_INTERFACE_DEFINED__ */


#ifndef __IotTextSymbol_INTERFACE_DEFINED__
#define __IotTextSymbol_INTERFACE_DEFINED__

/* interface IotTextSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotTextSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3D75BBF9-65B4-419C-9E02-A0B1D78DDCCF")
    IotTextSymbol : public IotSymbol
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Size( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Angle( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Angle( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TextColor( 
            /* [retval][out] */ IotColor **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TextColor( 
            /* [in] */ IotColor *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IFontDisp *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotTextSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotTextSymbol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotTextSymbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotTextSymbol * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotTextSymbol * This,
            /* [retval][out] */ otSymbolType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IotTextSymbol * This,
            /* [retval][out] */ otSymbolUnit *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Unit )( 
            IotTextSymbol * This,
            /* [in] */ otSymbolUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IotTextSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            IotTextSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IotTextSymbol * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Angle )( 
            IotTextSymbol * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TextColor )( 
            IotTextSymbol * This,
            /* [retval][out] */ IotColor **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TextColor )( 
            IotTextSymbol * This,
            /* [in] */ IotColor *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IotTextSymbol * This,
            /* [retval][out] */ IFontDisp **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IotTextSymbol * This,
            /* [in] */ IFontDisp *newVal);
        
        END_INTERFACE
    } IotTextSymbolVtbl;

    interface IotTextSymbol
    {
        CONST_VTBL struct IotTextSymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotTextSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotTextSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotTextSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotTextSymbol_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotTextSymbol_get_Unit(This,pVal)	\
    (This)->lpVtbl -> get_Unit(This,pVal)

#define IotTextSymbol_put_Unit(This,newVal)	\
    (This)->lpVtbl -> put_Unit(This,newVal)


#define IotTextSymbol_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IotTextSymbol_put_Size(This,newVal)	\
    (This)->lpVtbl -> put_Size(This,newVal)

#define IotTextSymbol_get_Angle(This,pVal)	\
    (This)->lpVtbl -> get_Angle(This,pVal)

#define IotTextSymbol_put_Angle(This,newVal)	\
    (This)->lpVtbl -> put_Angle(This,newVal)

#define IotTextSymbol_get_TextColor(This,pVal)	\
    (This)->lpVtbl -> get_TextColor(This,pVal)

#define IotTextSymbol_put_TextColor(This,newVal)	\
    (This)->lpVtbl -> put_TextColor(This,newVal)

#define IotTextSymbol_get_Font(This,pVal)	\
    (This)->lpVtbl -> get_Font(This,pVal)

#define IotTextSymbol_put_Font(This,newVal)	\
    (This)->lpVtbl -> put_Font(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotTextSymbol_get_Size_Proxy( 
    IotTextSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotTextSymbol_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotTextSymbol_put_Size_Proxy( 
    IotTextSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotTextSymbol_put_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotTextSymbol_get_Angle_Proxy( 
    IotTextSymbol * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotTextSymbol_get_Angle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotTextSymbol_put_Angle_Proxy( 
    IotTextSymbol * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotTextSymbol_put_Angle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotTextSymbol_get_TextColor_Proxy( 
    IotTextSymbol * This,
    /* [retval][out] */ IotColor **pVal);


void __RPC_STUB IotTextSymbol_get_TextColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotTextSymbol_put_TextColor_Proxy( 
    IotTextSymbol * This,
    /* [in] */ IotColor *newVal);


void __RPC_STUB IotTextSymbol_put_TextColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotTextSymbol_get_Font_Proxy( 
    IotTextSymbol * This,
    /* [retval][out] */ IFontDisp **pVal);


void __RPC_STUB IotTextSymbol_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotTextSymbol_put_Font_Proxy( 
    IotTextSymbol * This,
    /* [in] */ IFontDisp *newVal);


void __RPC_STUB IotTextSymbol_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotTextSymbol_INTERFACE_DEFINED__ */


#ifndef __IotSymbolLibLoader_INTERFACE_DEFINED__
#define __IotSymbolLibLoader_INTERFACE_DEFINED__

/* interface IotSymbolLibLoader */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSymbolLibLoader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8D3709D7-6DD5-4728-8DCC-8B3A5D6A7A52")
    IotSymbolLibLoader : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR libName,
            /* [retval][out] */ VARIANT_BOOL *ret) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSymbol( 
            /* [in] */ BSTR name,
            /* [retval][out] */ IotSymbol **retSymbol) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSymbolLibLoaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSymbolLibLoader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSymbolLibLoader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSymbolLibLoader * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IotSymbolLibLoader * This,
            /* [in] */ BSTR libName,
            /* [retval][out] */ VARIANT_BOOL *ret);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSymbol )( 
            IotSymbolLibLoader * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ IotSymbol **retSymbol);
        
        END_INTERFACE
    } IotSymbolLibLoaderVtbl;

    interface IotSymbolLibLoader
    {
        CONST_VTBL struct IotSymbolLibLoaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSymbolLibLoader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSymbolLibLoader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSymbolLibLoader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSymbolLibLoader_Open(This,libName,ret)	\
    (This)->lpVtbl -> Open(This,libName,ret)

#define IotSymbolLibLoader_GetSymbol(This,name,retSymbol)	\
    (This)->lpVtbl -> GetSymbol(This,name,retSymbol)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSymbolLibLoader_Open_Proxy( 
    IotSymbolLibLoader * This,
    /* [in] */ BSTR libName,
    /* [retval][out] */ VARIANT_BOOL *ret);


void __RPC_STUB IotSymbolLibLoader_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSymbolLibLoader_GetSymbol_Proxy( 
    IotSymbolLibLoader * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ IotSymbol **retSymbol);


void __RPC_STUB IotSymbolLibLoader_GetSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSymbolLibLoader_INTERFACE_DEFINED__ */



#ifndef __otcDisplay_LIBRARY_DEFINED__
#define __otcDisplay_LIBRARY_DEFINED__

/* library otcDisplay */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_otcDisplay;

#ifndef __IotScreenSketch_INTERFACE_DEFINED__
#define __IotScreenSketch_INTERFACE_DEFINED__

/* interface IotScreenSketch */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotScreenSketch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B65D1224-3598-43E1-86C6-7C18C76F18D9")
    IotScreenSketch : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Create( 
            enum /* external definition not present */ otGeometryType type) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ScreenCanvas( 
            /* [in] */ IotCanvas *newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ IotSymbol *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Stop( 
            /* [retval][out] */ /* external definition not present */ IotGeometry **retGeometry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPoint( 
            /* external definition not present */ IotPoint *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMousePoint( 
            /* [in] */ /* external definition not present */ IotPoint *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCircleCenter( 
            /* [in] */ /* external definition not present */ IotPoint *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetEllipseTopLeft( 
            /* [in] */ /* external definition not present */ IotPoint *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetRectTopLeft( 
            /* [in] */ /* external definition not present */ IotPoint *point) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotScreenSketchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotScreenSketch * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotScreenSketch * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotScreenSketch * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IotScreenSketch * This,
            enum /* external definition not present */ otGeometryType type);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScreenCanvas )( 
            IotScreenSketch * This,
            /* [in] */ IotCanvas *newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotScreenSketch * This,
            /* [in] */ IotSymbol *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IotScreenSketch * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IotScreenSketch * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **retGeometry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPoint )( 
            IotScreenSketch * This,
            /* external definition not present */ IotPoint *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetMousePoint )( 
            IotScreenSketch * This,
            /* [in] */ /* external definition not present */ IotPoint *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCircleCenter )( 
            IotScreenSketch * This,
            /* [in] */ /* external definition not present */ IotPoint *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEllipseTopLeft )( 
            IotScreenSketch * This,
            /* [in] */ /* external definition not present */ IotPoint *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetRectTopLeft )( 
            IotScreenSketch * This,
            /* [in] */ /* external definition not present */ IotPoint *point);
        
        END_INTERFACE
    } IotScreenSketchVtbl;

    interface IotScreenSketch
    {
        CONST_VTBL struct IotScreenSketchVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotScreenSketch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotScreenSketch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotScreenSketch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotScreenSketch_Create(This,type)	\
    (This)->lpVtbl -> Create(This,type)

#define IotScreenSketch_put_ScreenCanvas(This,newVal)	\
    (This)->lpVtbl -> put_ScreenCanvas(This,newVal)

#define IotScreenSketch_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#define IotScreenSketch_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IotScreenSketch_Stop(This,retGeometry)	\
    (This)->lpVtbl -> Stop(This,retGeometry)

#define IotScreenSketch_AddPoint(This,point)	\
    (This)->lpVtbl -> AddPoint(This,point)

#define IotScreenSketch_SetMousePoint(This,point)	\
    (This)->lpVtbl -> SetMousePoint(This,point)

#define IotScreenSketch_SetCircleCenter(This,point)	\
    (This)->lpVtbl -> SetCircleCenter(This,point)

#define IotScreenSketch_SetEllipseTopLeft(This,point)	\
    (This)->lpVtbl -> SetEllipseTopLeft(This,point)

#define IotScreenSketch_SetRectTopLeft(This,point)	\
    (This)->lpVtbl -> SetRectTopLeft(This,point)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_Create_Proxy( 
    IotScreenSketch * This,
    enum /* external definition not present */ otGeometryType type);


void __RPC_STUB IotScreenSketch_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_put_ScreenCanvas_Proxy( 
    IotScreenSketch * This,
    /* [in] */ IotCanvas *newVal);


void __RPC_STUB IotScreenSketch_put_ScreenCanvas_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_put_Symbol_Proxy( 
    IotScreenSketch * This,
    /* [in] */ IotSymbol *newVal);


void __RPC_STUB IotScreenSketch_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_Start_Proxy( 
    IotScreenSketch * This);


void __RPC_STUB IotScreenSketch_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_Stop_Proxy( 
    IotScreenSketch * This,
    /* [retval][out] */ /* external definition not present */ IotGeometry **retGeometry);


void __RPC_STUB IotScreenSketch_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_AddPoint_Proxy( 
    IotScreenSketch * This,
    /* external definition not present */ IotPoint *point);


void __RPC_STUB IotScreenSketch_AddPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_SetMousePoint_Proxy( 
    IotScreenSketch * This,
    /* [in] */ /* external definition not present */ IotPoint *point);


void __RPC_STUB IotScreenSketch_SetMousePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_SetCircleCenter_Proxy( 
    IotScreenSketch * This,
    /* [in] */ /* external definition not present */ IotPoint *point);


void __RPC_STUB IotScreenSketch_SetCircleCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_SetEllipseTopLeft_Proxy( 
    IotScreenSketch * This,
    /* [in] */ /* external definition not present */ IotPoint *point);


void __RPC_STUB IotScreenSketch_SetEllipseTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotScreenSketch_SetRectTopLeft_Proxy( 
    IotScreenSketch * This,
    /* [in] */ /* external definition not present */ IotPoint *point);


void __RPC_STUB IotScreenSketch_SetRectTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotScreenSketch_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_otColor;

#ifdef __cplusplus

class DECLSPEC_UUID("A697DF9C-D3E8-4BCF-86D1-6987C26A8546")
otColor;
#endif

EXTERN_C const CLSID CLSID_otSimpleMarkerSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("DC6C369B-EA27-4FCB-8906-7508F8FA4A2C")
otSimpleMarkerSymbol;
#endif

EXTERN_C const CLSID CLSID_otCharMarkerSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("0E87A077-D0E6-4353-9E47-663C660A220B")
otCharMarkerSymbol;
#endif

EXTERN_C const CLSID CLSID_otArrowMarkerSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("6AD355FA-FE9A-4C2C-A131-7C946F2FE82D")
otArrowMarkerSymbol;
#endif

EXTERN_C const CLSID CLSID_otPicMarkerSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("B33304AB-A61C-4CD2-B109-B5392091C5B0")
otPicMarkerSymbol;
#endif

EXTERN_C const CLSID CLSID_otSimpleLineSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("779F8606-279E-471E-B2BE-6EE5A5F2D4A9")
otSimpleLineSymbol;
#endif

EXTERN_C const CLSID CLSID_otAdvLineSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("C8432A67-F6A1-4FDA-980F-D3FCD0A17DD3")
otAdvLineSymbol;
#endif

EXTERN_C const CLSID CLSID_otHashLineSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("8445B8A3-8B9D-422D-A074-9236E1BC4029")
otHashLineSymbol;
#endif

EXTERN_C const CLSID CLSID_otMarkerLineSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("452E98A1-4135-419A-9FC3-A9714A7C8958")
otMarkerLineSymbol;
#endif

EXTERN_C const CLSID CLSID_otSimpleFillSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("93B81013-DA84-4413-944D-15C81EF1EC53")
otSimpleFillSymbol;
#endif

EXTERN_C const CLSID CLSID_otLineFillSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("FD15140D-3358-496C-9E25-3EC2561AC7ED")
otLineFillSymbol;
#endif

EXTERN_C const CLSID CLSID_otMarkerFillSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("92C59C1C-684E-431E-A7B5-29A0692F2C02")
otMarkerFillSymbol;
#endif

EXTERN_C const CLSID CLSID_otPicFillSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("56ECB028-1126-4625-B0CD-9E06EAEB10E3")
otPicFillSymbol;
#endif

EXTERN_C const CLSID CLSID_otGradientFillSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("EF13EE24-EF7B-44BA-9E54-E3AEB1466718")
otGradientFillSymbol;
#endif

EXTERN_C const CLSID CLSID_otComplexMarkerSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("EF19AE24-EF7B-440A-9E55-E6AEB146D748")
otComplexMarkerSymbol;
#endif

EXTERN_C const CLSID CLSID_otComplexLineSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("C2BF7A7D-0317-4708-B0DC-0E9C56559FCF")
otComplexLineSymbol;
#endif

EXTERN_C const CLSID CLSID_otComplexFillSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("187D30A9-9564-43A1-908A-E16B6DD66990")
otComplexFillSymbol;
#endif

EXTERN_C const CLSID CLSID_otCanvas;

#ifdef __cplusplus

class DECLSPEC_UUID("2D840C7B-D85C-4FCB-A880-F77557DCEED8")
otCanvas;
#endif

EXTERN_C const CLSID CLSID_otScreenSketch;

#ifdef __cplusplus

class DECLSPEC_UUID("85D728B2-0CE5-4E8A-AB1B-7A1EE54F3DB3")
otScreenSketch;
#endif

EXTERN_C const CLSID CLSID_otSymbolConvert;

#ifdef __cplusplus

class DECLSPEC_UUID("CF43A7C4-66C4-4A6C-B122-2C49DFA72890")
otSymbolConvert;
#endif

EXTERN_C const CLSID CLSID_otTextSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("F77D8A36-14CD-48B8-9488-3560388717D6")
otTextSymbol;
#endif

EXTERN_C const CLSID CLSID_otSymbolLibLoader;

#ifdef __cplusplus

class DECLSPEC_UUID("CF4EAA89-A08A-49B1-A163-D9D07FD25A47")
otSymbolLibLoader;
#endif
#endif /* __otcDisplay_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


