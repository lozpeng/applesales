

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __otMapControlidl_h__
#define __otMapControlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DotMapControl_FWD_DEFINED__
#define ___DotMapControl_FWD_DEFINED__
typedef interface _DotMapControl _DotMapControl;
#endif 	/* ___DotMapControl_FWD_DEFINED__ */


#ifndef ___DotMapControlEvents_FWD_DEFINED__
#define ___DotMapControlEvents_FWD_DEFINED__
typedef interface _DotMapControlEvents _DotMapControlEvents;
#endif 	/* ___DotMapControlEvents_FWD_DEFINED__ */


#ifndef __otMapControl_FWD_DEFINED__
#define __otMapControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class otMapControl otMapControl;
#else
typedef struct otMapControl otMapControl;
#endif /* __cplusplus */

#endif 	/* __otMapControl_FWD_DEFINED__ */


#ifndef __IotSymbolSelector_FWD_DEFINED__
#define __IotSymbolSelector_FWD_DEFINED__
typedef interface IotSymbolSelector IotSymbolSelector;
#endif 	/* __IotSymbolSelector_FWD_DEFINED__ */


#ifndef __otSymbolSelector_FWD_DEFINED__
#define __otSymbolSelector_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSymbolSelector otSymbolSelector;
#else
typedef struct otSymbolSelector otSymbolSelector;
#endif /* __cplusplus */

#endif 	/* __otSymbolSelector_FWD_DEFINED__ */


#ifndef __IotLayerProperty_FWD_DEFINED__
#define __IotLayerProperty_FWD_DEFINED__
typedef interface IotLayerProperty IotLayerProperty;
#endif 	/* __IotLayerProperty_FWD_DEFINED__ */


#ifndef __otLayerProperty_FWD_DEFINED__
#define __otLayerProperty_FWD_DEFINED__

#ifdef __cplusplus
typedef class otLayerProperty otLayerProperty;
#else
typedef struct otLayerProperty otLayerProperty;
#endif /* __cplusplus */

#endif 	/* __otLayerProperty_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_otMapControl_0000 */
/* [local] */ 

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("BDD9D0AD-421E-4b85-880C-13711CB69B7A") 
enum otActionType
    {	actionNone	= 0,
	actionPan	= 1,
	actionZoomIn	= 2,
	actionZoomOut	= 3,
	actionDrawPolylineElement	= actionZoomOut + 1,
	actionDrawPolygonElement	= actionDrawPolylineElement + 1,
	actionDrawRectElement	= actionDrawPolygonElement + 1,
	actionDrawTextElement	= actionDrawRectElement + 1,
	actionSelectElement	= actionDrawTextElement + 1,
	actionSelectByPoint	= actionSelectElement + 1,
	actionSelectByRect	= actionSelectByPoint + 1,
	actionSelectByPolygon	= actionSelectByRect + 1,
	actionSelectByLine	= actionSelectByPolygon + 1,
	actionSelectByCircle	= actionSelectByLine + 1,
	actionIdentifyFeature	= actionSelectByCircle + 1,
	actionDrawBezierCurveElement	= actionIdentifyFeature + 1,
	actionDrawSimpleMarkerElement	= actionDrawBezierCurveElement + 1,
	actionDrawFreehandLineElement	= actionDrawSimpleMarkerElement + 1,
	actionZoomActualSize	= actionDrawFreehandLineElement + 1
    } 	otActionType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("EED68378-9C6F-46ce-9DEF-65BED7BC3073") 
enum otMouseType
    {	otMouseDefault	= 0,
	otMouseCustom	= otMouseDefault + 1
    } 	otMouseType;



extern RPC_IF_HANDLE __MIDL_itf_otMapControl_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_otMapControl_0000_v0_0_s_ifspec;


#ifndef __otMapControlLib_LIBRARY_DEFINED__
#define __otMapControlLib_LIBRARY_DEFINED__

/* library otMapControlLib */
/* [control][helpstring][helpfile][version][uuid] */ 



EXTERN_C const IID LIBID_otMapControlLib;

#ifndef ___DotMapControl_DISPINTERFACE_DEFINED__
#define ___DotMapControl_DISPINTERFACE_DEFINED__

/* dispinterface _DotMapControl */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DotMapControl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1C60EC25-8C5A-4B28-AEF7-017C158D4017")
    _DotMapControl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DotMapControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DotMapControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DotMapControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DotMapControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DotMapControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DotMapControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DotMapControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DotMapControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DotMapControlVtbl;

    interface _DotMapControl
    {
        CONST_VTBL struct _DotMapControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DotMapControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DotMapControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DotMapControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DotMapControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DotMapControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DotMapControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DotMapControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DotMapControl_DISPINTERFACE_DEFINED__ */


#ifndef ___DotMapControlEvents_DISPINTERFACE_DEFINED__
#define ___DotMapControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DotMapControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DotMapControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5E23396E-8367-4E8E-A9FF-CBA23B378FAA")
    _DotMapControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DotMapControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DotMapControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DotMapControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DotMapControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DotMapControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DotMapControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DotMapControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DotMapControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DotMapControlEventsVtbl;

    interface _DotMapControlEvents
    {
        CONST_VTBL struct _DotMapControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DotMapControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DotMapControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DotMapControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DotMapControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DotMapControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DotMapControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DotMapControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DotMapControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_otMapControl;

#ifdef __cplusplus

class DECLSPEC_UUID("875F9C3B-337B-4D2C-A325-277F2E1D2068")
otMapControl;
#endif

#ifndef __IotSymbolSelector_DISPINTERFACE_DEFINED__
#define __IotSymbolSelector_DISPINTERFACE_DEFINED__

/* dispinterface IotSymbolSelector */
/* [uuid] */ 


EXTERN_C const IID DIID_IotSymbolSelector;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1E5E4427-9C21-4DD0-867E-BAC51C6DAD63")
    IotSymbolSelector : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IotSymbolSelectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSymbolSelector * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSymbolSelector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSymbolSelector * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IotSymbolSelector * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IotSymbolSelector * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IotSymbolSelector * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IotSymbolSelector * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IotSymbolSelectorVtbl;

    interface IotSymbolSelector
    {
        CONST_VTBL struct IotSymbolSelectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSymbolSelector_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSymbolSelector_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSymbolSelector_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSymbolSelector_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IotSymbolSelector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IotSymbolSelector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IotSymbolSelector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IotSymbolSelector_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_otSymbolSelector;

#ifdef __cplusplus

class DECLSPEC_UUID("61F0A120-2A95-442F-B541-4B3C309ECAF0")
otSymbolSelector;
#endif

#ifndef __IotLayerProperty_DISPINTERFACE_DEFINED__
#define __IotLayerProperty_DISPINTERFACE_DEFINED__

/* dispinterface IotLayerProperty */
/* [uuid] */ 


EXTERN_C const IID DIID_IotLayerProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("63E2AB56-8483-4405-AB79-40B81AEF1CCC")
    IotLayerProperty : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IotLayerPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotLayerProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotLayerProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotLayerProperty * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IotLayerProperty * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IotLayerProperty * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IotLayerProperty * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IotLayerProperty * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IotLayerPropertyVtbl;

    interface IotLayerProperty
    {
        CONST_VTBL struct IotLayerPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotLayerProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotLayerProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotLayerProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotLayerProperty_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IotLayerProperty_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IotLayerProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IotLayerProperty_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IotLayerProperty_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_otLayerProperty;

#ifdef __cplusplus

class DECLSPEC_UUID("798B7203-4A4B-48a9-B802-FB4C66246040")
otLayerProperty;
#endif
#endif /* __otMapControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


