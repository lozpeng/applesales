

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __otMapTreeControlidl_h__
#define __otMapTreeControlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DotMapTreeControl_FWD_DEFINED__
#define ___DotMapTreeControl_FWD_DEFINED__
typedef interface _DotMapTreeControl _DotMapTreeControl;
#endif 	/* ___DotMapTreeControl_FWD_DEFINED__ */


#ifndef ___DotMapTreeControlEvents_FWD_DEFINED__
#define ___DotMapTreeControlEvents_FWD_DEFINED__
typedef interface _DotMapTreeControlEvents _DotMapTreeControlEvents;
#endif 	/* ___DotMapTreeControlEvents_FWD_DEFINED__ */


#ifndef __otMapTreeControl_FWD_DEFINED__
#define __otMapTreeControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class otMapTreeControl otMapTreeControl;
#else
typedef struct otMapTreeControl otMapTreeControl;
#endif /* __cplusplus */

#endif 	/* __otMapTreeControl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __otMapTreeControlLib_LIBRARY_DEFINED__
#define __otMapTreeControlLib_LIBRARY_DEFINED__

/* library otMapTreeControlLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_otMapTreeControlLib;

#ifndef ___DotMapTreeControl_DISPINTERFACE_DEFINED__
#define ___DotMapTreeControl_DISPINTERFACE_DEFINED__

/* dispinterface _DotMapTreeControl */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DotMapTreeControl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F8C383A6-BC41-43ED-8DEA-6BFED591B192")
    _DotMapTreeControl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DotMapTreeControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DotMapTreeControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DotMapTreeControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DotMapTreeControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DotMapTreeControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DotMapTreeControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DotMapTreeControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DotMapTreeControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DotMapTreeControlVtbl;

    interface _DotMapTreeControl
    {
        CONST_VTBL struct _DotMapTreeControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DotMapTreeControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DotMapTreeControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DotMapTreeControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DotMapTreeControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DotMapTreeControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DotMapTreeControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DotMapTreeControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DotMapTreeControl_DISPINTERFACE_DEFINED__ */


#ifndef ___DotMapTreeControlEvents_DISPINTERFACE_DEFINED__
#define ___DotMapTreeControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DotMapTreeControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DotMapTreeControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A9D71CB3-7908-4C84-B547-1F6BA6DFEFBC")
    _DotMapTreeControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DotMapTreeControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DotMapTreeControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DotMapTreeControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DotMapTreeControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DotMapTreeControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DotMapTreeControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DotMapTreeControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DotMapTreeControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DotMapTreeControlEventsVtbl;

    interface _DotMapTreeControlEvents
    {
        CONST_VTBL struct _DotMapTreeControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DotMapTreeControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DotMapTreeControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DotMapTreeControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DotMapTreeControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DotMapTreeControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DotMapTreeControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DotMapTreeControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DotMapTreeControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_otMapTreeControl;

#ifdef __cplusplus

class DECLSPEC_UUID("87A8EF82-3CED-4CDA-AFC2-7E6A36FDE490")
otMapTreeControl;
#endif
#endif /* __otMapTreeControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


