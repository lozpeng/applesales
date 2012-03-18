

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sat Mar 17 08:25:31 2012
 */
/* Compiler settings for .\otComBase.idl:
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

#ifndef __otComBase_h__
#define __otComBase_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IOriginData_FWD_DEFINED__
#define __IOriginData_FWD_DEFINED__
typedef interface IOriginData IOriginData;
#endif 	/* __IOriginData_FWD_DEFINED__ */


#ifndef __OriginData_FWD_DEFINED__
#define __OriginData_FWD_DEFINED__

#ifdef __cplusplus
typedef class OriginData OriginData;
#else
typedef struct OriginData OriginData;
#endif /* __cplusplus */

#endif 	/* __OriginData_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_otComBase_0000 */
/* [local] */ 

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("0117237D-D754-4745-B5F2-D736B686A746") 
enum otUnits
    {	OT_UNIT_POINT	= 0,
	OT_UNIT_MILLIMETER	= OT_UNIT_POINT + 1,
	OT_UNIT_CENTIMETER	= OT_UNIT_MILLIMETER + 1,
	OT_UNIT_DECIMETER	= OT_UNIT_CENTIMETER + 1,
	OT_UNIT_METER	= OT_UNIT_DECIMETER + 1,
	OT_UNIT_KILOMETER	= OT_UNIT_METER + 1,
	SYS_UNIT_POINT	= OT_UNIT_KILOMETER + 1,
	OT_UNIT_INCH	= SYS_UNIT_POINT + 1,
	OT_UNIT_FEET	= OT_UNIT_INCH + 1,
	OT_UNIT_YARD	= OT_UNIT_FEET + 1,
	OT_UNIT_MILE	= OT_UNIT_YARD + 1,
	OT_UNIT_NAUTICALMILE	= OT_UNIT_MILE + 1,
	OT_UNIT_RADIAN	= OT_UNIT_NAUTICALMILE + 1,
	OT_UNIT_DEGREE	= OT_UNIT_RADIAN + 1,
	OT_UNIT_UNKNOWN	= OT_UNIT_DEGREE + 1
    } 	otUnits;



extern RPC_IF_HANDLE __MIDL_itf_otComBase_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_otComBase_0000_v0_0_s_ifspec;

#ifndef __IOriginData_INTERFACE_DEFINED__
#define __IOriginData_INTERFACE_DEFINED__

/* interface IOriginData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IOriginData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4166D466-63A3-40AB-B1AB-D67DF5B0E855")
    IOriginData : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OriginData( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OriginData( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AutoDestroy( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AutoDestroy( 
            /* [in] */ BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOriginDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOriginData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOriginData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOriginData * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OriginData )( 
            IOriginData * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OriginData )( 
            IOriginData * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoDestroy )( 
            IOriginData * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoDestroy )( 
            IOriginData * This,
            /* [in] */ BOOL newVal);
        
        END_INTERFACE
    } IOriginDataVtbl;

    interface IOriginData
    {
        CONST_VTBL struct IOriginDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOriginData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOriginData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOriginData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOriginData_get_OriginData(This,pVal)	\
    (This)->lpVtbl -> get_OriginData(This,pVal)

#define IOriginData_put_OriginData(This,newVal)	\
    (This)->lpVtbl -> put_OriginData(This,newVal)

#define IOriginData_get_AutoDestroy(This,pVal)	\
    (This)->lpVtbl -> get_AutoDestroy(This,pVal)

#define IOriginData_put_AutoDestroy(This,newVal)	\
    (This)->lpVtbl -> put_AutoDestroy(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IOriginData_get_OriginData_Proxy( 
    IOriginData * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IOriginData_get_OriginData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IOriginData_put_OriginData_Proxy( 
    IOriginData * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IOriginData_put_OriginData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IOriginData_get_AutoDestroy_Proxy( 
    IOriginData * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IOriginData_get_AutoDestroy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IOriginData_put_AutoDestroy_Proxy( 
    IOriginData * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IOriginData_put_AutoDestroy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOriginData_INTERFACE_DEFINED__ */



#ifndef __otComBase_LIBRARY_DEFINED__
#define __otComBase_LIBRARY_DEFINED__

/* library otComBase */
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_otComBase;

EXTERN_C const CLSID CLSID_OriginData;

#ifdef __cplusplus

class DECLSPEC_UUID("72033937-969A-4F43-82E5-DD38C65068AA")
OriginData;
#endif
#endif /* __otComBase_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


