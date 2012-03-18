

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sat Mar 17 22:46:16 2012
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

#ifndef __otcGeodataModel_h__
#define __otcGeodataModel_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IotWorkspaceFactory_FWD_DEFINED__
#define __IotWorkspaceFactory_FWD_DEFINED__
typedef interface IotWorkspaceFactory IotWorkspaceFactory;
#endif 	/* __IotWorkspaceFactory_FWD_DEFINED__ */


#ifndef __IotRow_FWD_DEFINED__
#define __IotRow_FWD_DEFINED__
typedef interface IotRow IotRow;
#endif 	/* __IotRow_FWD_DEFINED__ */


#ifndef __ITmsWF_FWD_DEFINED__
#define __ITmsWF_FWD_DEFINED__
typedef interface ITmsWF ITmsWF;
#endif 	/* __ITmsWF_FWD_DEFINED__ */


#ifndef __IotField_FWD_DEFINED__
#define __IotField_FWD_DEFINED__
typedef interface IotField IotField;
#endif 	/* __IotField_FWD_DEFINED__ */


#ifndef __IotSimpleQuery_FWD_DEFINED__
#define __IotSimpleQuery_FWD_DEFINED__
typedef interface IotSimpleQuery IotSimpleQuery;
#endif 	/* __IotSimpleQuery_FWD_DEFINED__ */


#ifndef __IotCursor_FWD_DEFINED__
#define __IotCursor_FWD_DEFINED__
typedef interface IotCursor IotCursor;
#endif 	/* __IotCursor_FWD_DEFINED__ */


#ifndef __IotFeatureCursor_FWD_DEFINED__
#define __IotFeatureCursor_FWD_DEFINED__
typedef interface IotFeatureCursor IotFeatureCursor;
#endif 	/* __IotFeatureCursor_FWD_DEFINED__ */


#ifndef __IotShpWF_FWD_DEFINED__
#define __IotShpWF_FWD_DEFINED__
typedef interface IotShpWF IotShpWF;
#endif 	/* __IotShpWF_FWD_DEFINED__ */


#ifndef __IotIfeWF_FWD_DEFINED__
#define __IotIfeWF_FWD_DEFINED__
typedef interface IotIfeWF IotIfeWF;
#endif 	/* __IotIfeWF_FWD_DEFINED__ */


#ifndef __IotRasterBlock_FWD_DEFINED__
#define __IotRasterBlock_FWD_DEFINED__
typedef interface IotRasterBlock IotRasterBlock;
#endif 	/* __IotRasterBlock_FWD_DEFINED__ */


#ifndef __IotSelectionSet_FWD_DEFINED__
#define __IotSelectionSet_FWD_DEFINED__
typedef interface IotSelectionSet IotSelectionSet;
#endif 	/* __IotSelectionSet_FWD_DEFINED__ */


#ifndef __IotSpatialReference_FWD_DEFINED__
#define __IotSpatialReference_FWD_DEFINED__
typedef interface IotSpatialReference IotSpatialReference;
#endif 	/* __IotSpatialReference_FWD_DEFINED__ */


#ifndef __IotProjTransform_FWD_DEFINED__
#define __IotProjTransform_FWD_DEFINED__
typedef interface IotProjTransform IotProjTransform;
#endif 	/* __IotProjTransform_FWD_DEFINED__ */


#ifndef __IotWorkspace_FWD_DEFINED__
#define __IotWorkspace_FWD_DEFINED__
typedef interface IotWorkspace IotWorkspace;
#endif 	/* __IotWorkspace_FWD_DEFINED__ */


#ifndef __IotSpatialQuery_FWD_DEFINED__
#define __IotSpatialQuery_FWD_DEFINED__
typedef interface IotSpatialQuery IotSpatialQuery;
#endif 	/* __IotSpatialQuery_FWD_DEFINED__ */


#ifndef __IotDataObject_FWD_DEFINED__
#define __IotDataObject_FWD_DEFINED__
typedef interface IotDataObject IotDataObject;
#endif 	/* __IotDataObject_FWD_DEFINED__ */


#ifndef __IotTable_FWD_DEFINED__
#define __IotTable_FWD_DEFINED__
typedef interface IotTable IotTable;
#endif 	/* __IotTable_FWD_DEFINED__ */


#ifndef __IotFeatureClass_FWD_DEFINED__
#define __IotFeatureClass_FWD_DEFINED__
typedef interface IotFeatureClass IotFeatureClass;
#endif 	/* __IotFeatureClass_FWD_DEFINED__ */


#ifndef __IotRasterDataset_FWD_DEFINED__
#define __IotRasterDataset_FWD_DEFINED__
typedef interface IotRasterDataset IotRasterDataset;
#endif 	/* __IotRasterDataset_FWD_DEFINED__ */


#ifndef __IotRow_FWD_DEFINED__
#define __IotRow_FWD_DEFINED__
typedef interface IotRow IotRow;
#endif 	/* __IotRow_FWD_DEFINED__ */


#ifndef __IotFeature_FWD_DEFINED__
#define __IotFeature_FWD_DEFINED__
typedef interface IotFeature IotFeature;
#endif 	/* __IotFeature_FWD_DEFINED__ */


#ifndef __otWorkspace_FWD_DEFINED__
#define __otWorkspace_FWD_DEFINED__

#ifdef __cplusplus
typedef class otWorkspace otWorkspace;
#else
typedef struct otWorkspace otWorkspace;
#endif /* __cplusplus */

#endif 	/* __otWorkspace_FWD_DEFINED__ */


#ifndef __TmsWF_FWD_DEFINED__
#define __TmsWF_FWD_DEFINED__

#ifdef __cplusplus
typedef class TmsWF TmsWF;
#else
typedef struct TmsWF TmsWF;
#endif /* __cplusplus */

#endif 	/* __TmsWF_FWD_DEFINED__ */


#ifndef __otFeatureClass_FWD_DEFINED__
#define __otFeatureClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class otFeatureClass otFeatureClass;
#else
typedef struct otFeatureClass otFeatureClass;
#endif /* __cplusplus */

#endif 	/* __otFeatureClass_FWD_DEFINED__ */


#ifndef __otField_FWD_DEFINED__
#define __otField_FWD_DEFINED__

#ifdef __cplusplus
typedef class otField otField;
#else
typedef struct otField otField;
#endif /* __cplusplus */

#endif 	/* __otField_FWD_DEFINED__ */


#ifndef __otFeature_FWD_DEFINED__
#define __otFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class otFeature otFeature;
#else
typedef struct otFeature otFeature;
#endif /* __cplusplus */

#endif 	/* __otFeature_FWD_DEFINED__ */


#ifndef __otSimpleQuery_FWD_DEFINED__
#define __otSimpleQuery_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSimpleQuery otSimpleQuery;
#else
typedef struct otSimpleQuery otSimpleQuery;
#endif /* __cplusplus */

#endif 	/* __otSimpleQuery_FWD_DEFINED__ */


#ifndef __otSpatialQuery_FWD_DEFINED__
#define __otSpatialQuery_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSpatialQuery otSpatialQuery;
#else
typedef struct otSpatialQuery otSpatialQuery;
#endif /* __cplusplus */

#endif 	/* __otSpatialQuery_FWD_DEFINED__ */


#ifndef __otFeatureCursor_FWD_DEFINED__
#define __otFeatureCursor_FWD_DEFINED__

#ifdef __cplusplus
typedef class otFeatureCursor otFeatureCursor;
#else
typedef struct otFeatureCursor otFeatureCursor;
#endif /* __cplusplus */

#endif 	/* __otFeatureCursor_FWD_DEFINED__ */


#ifndef __otShpWF_FWD_DEFINED__
#define __otShpWF_FWD_DEFINED__

#ifdef __cplusplus
typedef class otShpWF otShpWF;
#else
typedef struct otShpWF otShpWF;
#endif /* __cplusplus */

#endif 	/* __otShpWF_FWD_DEFINED__ */


#ifndef __otRasterDataset_FWD_DEFINED__
#define __otRasterDataset_FWD_DEFINED__

#ifdef __cplusplus
typedef class otRasterDataset otRasterDataset;
#else
typedef struct otRasterDataset otRasterDataset;
#endif /* __cplusplus */

#endif 	/* __otRasterDataset_FWD_DEFINED__ */


#ifndef __otIfeWF_FWD_DEFINED__
#define __otIfeWF_FWD_DEFINED__

#ifdef __cplusplus
typedef class otIfeWF otIfeWF;
#else
typedef struct otIfeWF otIfeWF;
#endif /* __cplusplus */

#endif 	/* __otIfeWF_FWD_DEFINED__ */


#ifndef __otRasterBlock_FWD_DEFINED__
#define __otRasterBlock_FWD_DEFINED__

#ifdef __cplusplus
typedef class otRasterBlock otRasterBlock;
#else
typedef struct otRasterBlock otRasterBlock;
#endif /* __cplusplus */

#endif 	/* __otRasterBlock_FWD_DEFINED__ */


#ifndef __otSelectionSet_FWD_DEFINED__
#define __otSelectionSet_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSelectionSet otSelectionSet;
#else
typedef struct otSelectionSet otSelectionSet;
#endif /* __cplusplus */

#endif 	/* __otSelectionSet_FWD_DEFINED__ */


#ifndef __otSpatialReference_FWD_DEFINED__
#define __otSpatialReference_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSpatialReference otSpatialReference;
#else
typedef struct otSpatialReference otSpatialReference;
#endif /* __cplusplus */

#endif 	/* __otSpatialReference_FWD_DEFINED__ */


#ifndef __otProjTransform_FWD_DEFINED__
#define __otProjTransform_FWD_DEFINED__

#ifdef __cplusplus
typedef class otProjTransform otProjTransform;
#else
typedef struct otProjTransform otProjTransform;
#endif /* __cplusplus */

#endif 	/* __otProjTransform_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_otcGeodataModel_0000 */
/* [local] */ 









typedef /* [helpstring][uuid] */  DECLSPEC_UUID("735CF597-780E-430f-BD97-5768D17BED0B") 
enum otWorkspaceType
    {	OWT_FileSystem	= 1,
	OWT_OTSDE	= 2
    } 	otWorkspaceType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("7B78B972-316F-4784-87F1-117B663C6EC5") 
enum otSpatialRel
    {	otSpatialRelUndefined	= 0,
	otSpatialRelIntersects	= otSpatialRelUndefined + 1,
	otSpatialRelEnvelopeIntersects	= otSpatialRelIntersects + 1,
	otSpatialRelTouches	= otSpatialRelEnvelopeIntersects + 1,
	otSpatialRelOverlaps	= otSpatialRelTouches + 1,
	otSpatialRelCrosses	= otSpatialRelOverlaps + 1,
	otSpatialRelWithin	= otSpatialRelCrosses + 1,
	otSpatialRelContains	= otSpatialRelWithin + 1
    } 	otSpatialRel;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("B6BF3975-1FA7-40ba-B82A-40CA6C38589D") 
enum otDataType
    {	OT_UNKNOWN_TYPE	= 0,
	OT_METADATA_SET	= OT_UNKNOWN_TYPE + 1,
	OT_TABLE	= OT_METADATA_SET + 1,
	OT_FEATURECLASS	= OT_TABLE + 1,
	OT_FEATUREDATASET	= OT_FEATURECLASS + 1,
	OT_RASTERDATASET	= OT_FEATUREDATASET + 1,
	OT_RASTERCATALOG	= OT_RASTERDATASET + 1,
	OT_TINDATASET	= OT_RASTERCATALOG + 1,
	OT_TOPODATASET	= OT_TINDATASET + 1
    } 	otDataType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("99590811-ECAD-4f60-BD5B-746E87489231") 
enum otFieldType
    {	FTYPE_UNKNOWN	= 0,
	FTYPE_BOOL	= FTYPE_UNKNOWN + 1,
	FTYPE_SHORT	= FTYPE_BOOL + 1,
	FTYPE_LONG	= FTYPE_SHORT + 1,
	FTYPE_FLOAT	= FTYPE_LONG + 1,
	FTYPE_DOUBLE	= FTYPE_FLOAT + 1,
	FTYPE_STRING	= FTYPE_DOUBLE + 1,
	FTYPE_DATE	= FTYPE_STRING + 1,
	FTYPE_TIME	= FTYPE_DATE + 1,
	FTYPE_GEOMETRY	= FTYPE_TIME + 1,
	FTYPE_BLOB	= FTYPE_GEOMETRY + 1,
	FTYPE_CLOB	= FTYPE_BLOB + 1,
	FTYPE_RASTERBLOCK	= FTYPE_CLOB + 1
    } 	otFieldType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("80519D5D-3F0F-4a69-97FD-BCE8FA3E8446") 
enum otBandType
    {	OTB_UNKNOWN	= 0,
	OTB_BIT1	= OTB_UNKNOWN + 1,
	OTB_BYTE	= OTB_BIT1 + 1,
	OTB_USHORT	= OTB_BYTE + 1,
	OTB_SHORT	= OTB_USHORT + 1,
	OTB_ULONG	= OTB_SHORT + 1,
	OTB_LONG	= OTB_ULONG + 1,
	OTB_FLOAT	= OTB_LONG + 1,
	OTB_DOUBLE	= OTB_FLOAT + 1
    } 	otBandType;



extern RPC_IF_HANDLE __MIDL_itf_otcGeodataModel_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_otcGeodataModel_0000_v0_0_s_ifspec;

#ifndef __IotWorkspaceFactory_INTERFACE_DEFINED__
#define __IotWorkspaceFactory_INTERFACE_DEFINED__

/* interface IotWorkspaceFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotWorkspaceFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C45AEEAB-A045-473b-A143-BEA219A6E691")
    IotWorkspaceFactory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenFromFile( 
            /* [in] */ BSTR filename,
            /* [retval][out] */ IotWorkspace **workspace) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenFolder( 
            /* [in] */ BSTR name,
            /* [retval][out] */ IotWorkspace **retWorkspace) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotWorkspaceFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotWorkspaceFactory * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotWorkspaceFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotWorkspaceFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFromFile )( 
            IotWorkspaceFactory * This,
            /* [in] */ BSTR filename,
            /* [retval][out] */ IotWorkspace **workspace);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFolder )( 
            IotWorkspaceFactory * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ IotWorkspace **retWorkspace);
        
        END_INTERFACE
    } IotWorkspaceFactoryVtbl;

    interface IotWorkspaceFactory
    {
        CONST_VTBL struct IotWorkspaceFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotWorkspaceFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotWorkspaceFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotWorkspaceFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotWorkspaceFactory_OpenFromFile(This,filename,workspace)	\
    (This)->lpVtbl -> OpenFromFile(This,filename,workspace)

#define IotWorkspaceFactory_OpenFolder(This,name,retWorkspace)	\
    (This)->lpVtbl -> OpenFolder(This,name,retWorkspace)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspaceFactory_OpenFromFile_Proxy( 
    IotWorkspaceFactory * This,
    /* [in] */ BSTR filename,
    /* [retval][out] */ IotWorkspace **workspace);


void __RPC_STUB IotWorkspaceFactory_OpenFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspaceFactory_OpenFolder_Proxy( 
    IotWorkspaceFactory * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ IotWorkspace **retWorkspace);


void __RPC_STUB IotWorkspaceFactory_OpenFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotWorkspaceFactory_INTERFACE_DEFINED__ */


#ifndef __IotRow_INTERFACE_DEFINED__
#define __IotRow_INTERFACE_DEFINED__

/* interface IotRow */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotRow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("434C180F-0B61-4428-BEA0-4902C6A26006")
    IotRow : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Table( 
            /* [retval][out] */ IotTable **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FieldCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Field( 
            /* [in] */ LONG index,
            /* [retval][out] */ IotField **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [in] */ LONG index,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ LONG index,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Update( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotRowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotRow * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotRow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotRow * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Table )( 
            IotRow * This,
            /* [retval][out] */ IotTable **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FieldCount )( 
            IotRow * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IotRow * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Field )( 
            IotRow * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotField **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IotRow * This,
            /* [in] */ LONG index,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IotRow * This,
            /* [in] */ LONG index,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IotRow * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IotRow * This);
        
        END_INTERFACE
    } IotRowVtbl;

    interface IotRow
    {
        CONST_VTBL struct IotRowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotRow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotRow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotRow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotRow_get_Table(This,pVal)	\
    (This)->lpVtbl -> get_Table(This,pVal)

#define IotRow_get_FieldCount(This,pVal)	\
    (This)->lpVtbl -> get_FieldCount(This,pVal)

#define IotRow_get_ID(This,pVal)	\
    (This)->lpVtbl -> get_ID(This,pVal)

#define IotRow_get_Field(This,index,pVal)	\
    (This)->lpVtbl -> get_Field(This,index,pVal)

#define IotRow_get_Value(This,index,pVal)	\
    (This)->lpVtbl -> get_Value(This,index,pVal)

#define IotRow_put_Value(This,index,newVal)	\
    (This)->lpVtbl -> put_Value(This,index,newVal)

#define IotRow_Update(This)	\
    (This)->lpVtbl -> Update(This)

#define IotRow_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRow_get_Table_Proxy( 
    IotRow * This,
    /* [retval][out] */ IotTable **pVal);


void __RPC_STUB IotRow_get_Table_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRow_get_FieldCount_Proxy( 
    IotRow * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotRow_get_FieldCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRow_get_ID_Proxy( 
    IotRow * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotRow_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRow_get_Field_Proxy( 
    IotRow * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IotField **pVal);


void __RPC_STUB IotRow_get_Field_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRow_get_Value_Proxy( 
    IotRow * This,
    /* [in] */ LONG index,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IotRow_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotRow_put_Value_Proxy( 
    IotRow * This,
    /* [in] */ LONG index,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IotRow_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotRow_Update_Proxy( 
    IotRow * This);


void __RPC_STUB IotRow_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotRow_Delete_Proxy( 
    IotRow * This);


void __RPC_STUB IotRow_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotRow_INTERFACE_DEFINED__ */


#ifndef __ITmsWF_INTERFACE_DEFINED__
#define __ITmsWF_INTERFACE_DEFINED__

/* interface ITmsWF */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITmsWF;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C4424A1C-C3D8-4D65-91D0-75573C2EAF67")
    ITmsWF : public IotWorkspaceFactory
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITmsWFVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITmsWF * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITmsWF * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITmsWF * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFromFile )( 
            ITmsWF * This,
            /* [in] */ BSTR filename,
            /* [retval][out] */ IotWorkspace **workspace);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFolder )( 
            ITmsWF * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ IotWorkspace **retWorkspace);
        
        END_INTERFACE
    } ITmsWFVtbl;

    interface ITmsWF
    {
        CONST_VTBL struct ITmsWFVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITmsWF_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITmsWF_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITmsWF_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITmsWF_OpenFromFile(This,filename,workspace)	\
    (This)->lpVtbl -> OpenFromFile(This,filename,workspace)

#define ITmsWF_OpenFolder(This,name,retWorkspace)	\
    (This)->lpVtbl -> OpenFolder(This,name,retWorkspace)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITmsWF_INTERFACE_DEFINED__ */


#ifndef __IotField_INTERFACE_DEFINED__
#define __IotField_INTERFACE_DEFINED__

/* interface IotField */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotField;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5DC04615-EB7D-45A2-A405-2D79BBA4D2F7")
    IotField : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ otFieldType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ otFieldType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Precision( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Precision( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotFieldVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotField * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotField * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotField * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotField * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotField * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IotField * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            IotField * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotField * This,
            /* [retval][out] */ otFieldType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IotField * This,
            /* [in] */ otFieldType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Precision )( 
            IotField * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Precision )( 
            IotField * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } IotFieldVtbl;

    interface IotField
    {
        CONST_VTBL struct IotFieldVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotField_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotField_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotField_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotField_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotField_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotField_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IotField_put_Length(This,newVal)	\
    (This)->lpVtbl -> put_Length(This,newVal)

#define IotField_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotField_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define IotField_get_Precision(This,pVal)	\
    (This)->lpVtbl -> get_Precision(This,pVal)

#define IotField_put_Precision(This,newVal)	\
    (This)->lpVtbl -> put_Precision(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotField_get_Name_Proxy( 
    IotField * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotField_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotField_put_Name_Proxy( 
    IotField * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotField_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotField_get_Length_Proxy( 
    IotField * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotField_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotField_put_Length_Proxy( 
    IotField * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotField_put_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotField_get_Type_Proxy( 
    IotField * This,
    /* [retval][out] */ otFieldType *pVal);


void __RPC_STUB IotField_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotField_put_Type_Proxy( 
    IotField * This,
    /* [in] */ otFieldType newVal);


void __RPC_STUB IotField_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotField_get_Precision_Proxy( 
    IotField * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotField_get_Precision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotField_put_Precision_Proxy( 
    IotField * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotField_put_Precision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotField_INTERFACE_DEFINED__ */


#ifndef __IotSimpleQuery_INTERFACE_DEFINED__
#define __IotSimpleQuery_INTERFACE_DEFINED__

/* interface IotSimpleQuery */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSimpleQuery;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CEFB51F2-2462-477C-9037-69A06F64632A")
    IotSimpleQuery : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Fields( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Fields( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WhereString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WhereString( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddField( 
            /* [in] */ BSTR fieldname) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSimpleQueryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSimpleQuery * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSimpleQuery * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSimpleQuery * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fields )( 
            IotSimpleQuery * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fields )( 
            IotSimpleQuery * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WhereString )( 
            IotSimpleQuery * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WhereString )( 
            IotSimpleQuery * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddField )( 
            IotSimpleQuery * This,
            /* [in] */ BSTR fieldname);
        
        END_INTERFACE
    } IotSimpleQueryVtbl;

    interface IotSimpleQuery
    {
        CONST_VTBL struct IotSimpleQueryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSimpleQuery_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSimpleQuery_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSimpleQuery_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSimpleQuery_get_Fields(This,pVal)	\
    (This)->lpVtbl -> get_Fields(This,pVal)

#define IotSimpleQuery_put_Fields(This,newVal)	\
    (This)->lpVtbl -> put_Fields(This,newVal)

#define IotSimpleQuery_get_WhereString(This,pVal)	\
    (This)->lpVtbl -> get_WhereString(This,pVal)

#define IotSimpleQuery_put_WhereString(This,newVal)	\
    (This)->lpVtbl -> put_WhereString(This,newVal)

#define IotSimpleQuery_AddField(This,fieldname)	\
    (This)->lpVtbl -> AddField(This,fieldname)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSimpleQuery_get_Fields_Proxy( 
    IotSimpleQuery * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotSimpleQuery_get_Fields_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSimpleQuery_put_Fields_Proxy( 
    IotSimpleQuery * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotSimpleQuery_put_Fields_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSimpleQuery_get_WhereString_Proxy( 
    IotSimpleQuery * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotSimpleQuery_get_WhereString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSimpleQuery_put_WhereString_Proxy( 
    IotSimpleQuery * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotSimpleQuery_put_WhereString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSimpleQuery_AddField_Proxy( 
    IotSimpleQuery * This,
    /* [in] */ BSTR fieldname);


void __RPC_STUB IotSimpleQuery_AddField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSimpleQuery_INTERFACE_DEFINED__ */


#ifndef __IotCursor_INTERFACE_DEFINED__
#define __IotCursor_INTERFACE_DEFINED__

/* interface IotCursor */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotCursor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56EBD89B-77FC-47f8-975C-0CFBEFAB72E3")
    IotCursor : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Table( 
            /* [retval][out] */ IotTable **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NextRow( 
            /* [retval][out] */ IotRow **row) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsEOF( 
            /* [retval][out] */ VARIANT_BOOL *ret) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotCursorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotCursor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotCursor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotCursor * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Table )( 
            IotCursor * This,
            /* [retval][out] */ IotTable **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NextRow )( 
            IotCursor * This,
            /* [retval][out] */ IotRow **row);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsEOF )( 
            IotCursor * This,
            /* [retval][out] */ VARIANT_BOOL *ret);
        
        END_INTERFACE
    } IotCursorVtbl;

    interface IotCursor
    {
        CONST_VTBL struct IotCursorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotCursor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotCursor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotCursor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotCursor_get_Table(This,pVal)	\
    (This)->lpVtbl -> get_Table(This,pVal)

#define IotCursor_NextRow(This,row)	\
    (This)->lpVtbl -> NextRow(This,row)

#define IotCursor_IsEOF(This,ret)	\
    (This)->lpVtbl -> IsEOF(This,ret)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotCursor_get_Table_Proxy( 
    IotCursor * This,
    /* [retval][out] */ IotTable **pVal);


void __RPC_STUB IotCursor_get_Table_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotCursor_NextRow_Proxy( 
    IotCursor * This,
    /* [retval][out] */ IotRow **row);


void __RPC_STUB IotCursor_NextRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotCursor_IsEOF_Proxy( 
    IotCursor * This,
    /* [retval][out] */ VARIANT_BOOL *ret);


void __RPC_STUB IotCursor_IsEOF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotCursor_INTERFACE_DEFINED__ */


#ifndef __IotFeatureCursor_INTERFACE_DEFINED__
#define __IotFeatureCursor_INTERFACE_DEFINED__

/* interface IotFeatureCursor */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotFeatureCursor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0CCE34BB-0DF4-453E-9BE9-4109209CB31F")
    IotFeatureCursor : public IotCursor
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NextFeature( 
            /* [retval][out] */ IotFeature **retFeature) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotFeatureCursorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotFeatureCursor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotFeatureCursor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotFeatureCursor * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Table )( 
            IotFeatureCursor * This,
            /* [retval][out] */ IotTable **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NextRow )( 
            IotFeatureCursor * This,
            /* [retval][out] */ IotRow **row);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsEOF )( 
            IotFeatureCursor * This,
            /* [retval][out] */ VARIANT_BOOL *ret);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NextFeature )( 
            IotFeatureCursor * This,
            /* [retval][out] */ IotFeature **retFeature);
        
        END_INTERFACE
    } IotFeatureCursorVtbl;

    interface IotFeatureCursor
    {
        CONST_VTBL struct IotFeatureCursorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotFeatureCursor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotFeatureCursor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotFeatureCursor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotFeatureCursor_get_Table(This,pVal)	\
    (This)->lpVtbl -> get_Table(This,pVal)

#define IotFeatureCursor_NextRow(This,row)	\
    (This)->lpVtbl -> NextRow(This,row)

#define IotFeatureCursor_IsEOF(This,ret)	\
    (This)->lpVtbl -> IsEOF(This,ret)


#define IotFeatureCursor_NextFeature(This,retFeature)	\
    (This)->lpVtbl -> NextFeature(This,retFeature)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotFeatureCursor_NextFeature_Proxy( 
    IotFeatureCursor * This,
    /* [retval][out] */ IotFeature **retFeature);


void __RPC_STUB IotFeatureCursor_NextFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotFeatureCursor_INTERFACE_DEFINED__ */


#ifndef __IotShpWF_INTERFACE_DEFINED__
#define __IotShpWF_INTERFACE_DEFINED__

/* interface IotShpWF */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotShpWF;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("108AA1D4-8661-43E0-B1CD-D4EF320567D7")
    IotShpWF : public IotWorkspaceFactory
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotShpWFVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotShpWF * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotShpWF * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotShpWF * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFromFile )( 
            IotShpWF * This,
            /* [in] */ BSTR filename,
            /* [retval][out] */ IotWorkspace **workspace);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFolder )( 
            IotShpWF * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ IotWorkspace **retWorkspace);
        
        END_INTERFACE
    } IotShpWFVtbl;

    interface IotShpWF
    {
        CONST_VTBL struct IotShpWFVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotShpWF_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotShpWF_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotShpWF_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotShpWF_OpenFromFile(This,filename,workspace)	\
    (This)->lpVtbl -> OpenFromFile(This,filename,workspace)

#define IotShpWF_OpenFolder(This,name,retWorkspace)	\
    (This)->lpVtbl -> OpenFolder(This,name,retWorkspace)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotShpWF_INTERFACE_DEFINED__ */


#ifndef __IotIfeWF_INTERFACE_DEFINED__
#define __IotIfeWF_INTERFACE_DEFINED__

/* interface IotIfeWF */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotIfeWF;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("68C740E9-F043-49D5-A7A6-B5A712CC5EC5")
    IotIfeWF : public IotWorkspaceFactory
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotIfeWFVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotIfeWF * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotIfeWF * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotIfeWF * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFromFile )( 
            IotIfeWF * This,
            /* [in] */ BSTR filename,
            /* [retval][out] */ IotWorkspace **workspace);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFolder )( 
            IotIfeWF * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ IotWorkspace **retWorkspace);
        
        END_INTERFACE
    } IotIfeWFVtbl;

    interface IotIfeWF
    {
        CONST_VTBL struct IotIfeWFVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotIfeWF_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotIfeWF_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotIfeWF_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotIfeWF_OpenFromFile(This,filename,workspace)	\
    (This)->lpVtbl -> OpenFromFile(This,filename,workspace)

#define IotIfeWF_OpenFolder(This,name,retWorkspace)	\
    (This)->lpVtbl -> OpenFolder(This,name,retWorkspace)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotIfeWF_INTERFACE_DEFINED__ */


#ifndef __IotRasterBlock_INTERFACE_DEFINED__
#define __IotRasterBlock_INTERFACE_DEFINED__

/* interface IotRasterBlock */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotRasterBlock;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C598484A-347E-4436-984A-9AF4B574607C")
    IotRasterBlock : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DataType( 
            /* [retval][out] */ otBandType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DataType( 
            /* [in] */ otBandType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ LONG X,
            /* [in] */ LONG Y,
            /* [retval][out] */ VARIANT *value) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SafeArray( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SafeArray( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotRasterBlockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotRasterBlock * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotRasterBlock * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotRasterBlock * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataType )( 
            IotRasterBlock * This,
            /* [retval][out] */ otBandType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DataType )( 
            IotRasterBlock * This,
            /* [in] */ otBandType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IotRasterBlock * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IotRasterBlock * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IotRasterBlock * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IotRasterBlock * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IotRasterBlock * This,
            /* [in] */ LONG X,
            /* [in] */ LONG Y,
            /* [retval][out] */ VARIANT *value);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SafeArray )( 
            IotRasterBlock * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SafeArray )( 
            IotRasterBlock * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IotRasterBlockVtbl;

    interface IotRasterBlock
    {
        CONST_VTBL struct IotRasterBlockVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotRasterBlock_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotRasterBlock_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotRasterBlock_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotRasterBlock_get_DataType(This,pVal)	\
    (This)->lpVtbl -> get_DataType(This,pVal)

#define IotRasterBlock_put_DataType(This,newVal)	\
    (This)->lpVtbl -> put_DataType(This,newVal)

#define IotRasterBlock_get_Width(This,pVal)	\
    (This)->lpVtbl -> get_Width(This,pVal)

#define IotRasterBlock_put_Width(This,newVal)	\
    (This)->lpVtbl -> put_Width(This,newVal)

#define IotRasterBlock_get_Height(This,pVal)	\
    (This)->lpVtbl -> get_Height(This,pVal)

#define IotRasterBlock_put_Height(This,newVal)	\
    (This)->lpVtbl -> put_Height(This,newVal)

#define IotRasterBlock_GetValue(This,X,Y,value)	\
    (This)->lpVtbl -> GetValue(This,X,Y,value)

#define IotRasterBlock_get_SafeArray(This,pVal)	\
    (This)->lpVtbl -> get_SafeArray(This,pVal)

#define IotRasterBlock_put_SafeArray(This,newVal)	\
    (This)->lpVtbl -> put_SafeArray(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterBlock_get_DataType_Proxy( 
    IotRasterBlock * This,
    /* [retval][out] */ otBandType *pVal);


void __RPC_STUB IotRasterBlock_get_DataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotRasterBlock_put_DataType_Proxy( 
    IotRasterBlock * This,
    /* [in] */ otBandType newVal);


void __RPC_STUB IotRasterBlock_put_DataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterBlock_get_Width_Proxy( 
    IotRasterBlock * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotRasterBlock_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotRasterBlock_put_Width_Proxy( 
    IotRasterBlock * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotRasterBlock_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterBlock_get_Height_Proxy( 
    IotRasterBlock * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotRasterBlock_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotRasterBlock_put_Height_Proxy( 
    IotRasterBlock * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotRasterBlock_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotRasterBlock_GetValue_Proxy( 
    IotRasterBlock * This,
    /* [in] */ LONG X,
    /* [in] */ LONG Y,
    /* [retval][out] */ VARIANT *value);


void __RPC_STUB IotRasterBlock_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterBlock_get_SafeArray_Proxy( 
    IotRasterBlock * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IotRasterBlock_get_SafeArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotRasterBlock_put_SafeArray_Proxy( 
    IotRasterBlock * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IotRasterBlock_put_SafeArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotRasterBlock_INTERFACE_DEFINED__ */


#ifndef __IotSelectionSet_INTERFACE_DEFINED__
#define __IotSelectionSet_INTERFACE_DEFINED__

/* interface IotSelectionSet */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSelectionSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B5B73261-A971-4040-A56B-932C85D31121")
    IotSelectionSet : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsEOF( 
            /* [retval][out] */ VARIANT_BOOL *ret) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetIndex( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NextID( 
            /* [retval][out] */ LONG *id) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ LONG id) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Table( 
            /* [retval][out] */ IotTable **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSelectionSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSelectionSet * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSelectionSet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSelectionSet * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IotSelectionSet * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsEOF )( 
            IotSelectionSet * This,
            /* [retval][out] */ VARIANT_BOOL *ret);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ResetIndex )( 
            IotSelectionSet * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NextID )( 
            IotSelectionSet * This,
            /* [retval][out] */ LONG *id);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IotSelectionSet * This,
            /* [in] */ LONG id);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Table )( 
            IotSelectionSet * This,
            /* [retval][out] */ IotTable **pVal);
        
        END_INTERFACE
    } IotSelectionSetVtbl;

    interface IotSelectionSet
    {
        CONST_VTBL struct IotSelectionSetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSelectionSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSelectionSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSelectionSet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSelectionSet_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IotSelectionSet_IsEOF(This,ret)	\
    (This)->lpVtbl -> IsEOF(This,ret)

#define IotSelectionSet_ResetIndex(This)	\
    (This)->lpVtbl -> ResetIndex(This)

#define IotSelectionSet_NextID(This,id)	\
    (This)->lpVtbl -> NextID(This,id)

#define IotSelectionSet_Add(This,id)	\
    (This)->lpVtbl -> Add(This,id)

#define IotSelectionSet_get_Table(This,pVal)	\
    (This)->lpVtbl -> get_Table(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSelectionSet_get_Count_Proxy( 
    IotSelectionSet * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotSelectionSet_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSelectionSet_IsEOF_Proxy( 
    IotSelectionSet * This,
    /* [retval][out] */ VARIANT_BOOL *ret);


void __RPC_STUB IotSelectionSet_IsEOF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSelectionSet_ResetIndex_Proxy( 
    IotSelectionSet * This);


void __RPC_STUB IotSelectionSet_ResetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSelectionSet_NextID_Proxy( 
    IotSelectionSet * This,
    /* [retval][out] */ LONG *id);


void __RPC_STUB IotSelectionSet_NextID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSelectionSet_Add_Proxy( 
    IotSelectionSet * This,
    /* [in] */ LONG id);


void __RPC_STUB IotSelectionSet_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSelectionSet_get_Table_Proxy( 
    IotSelectionSet * This,
    /* [retval][out] */ IotTable **pVal);


void __RPC_STUB IotSelectionSet_get_Table_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSelectionSet_INTERFACE_DEFINED__ */


#ifndef __IotSpatialReference_INTERFACE_DEFINED__
#define __IotSpatialReference_INTERFACE_DEFINED__

/* interface IotSpatialReference */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSpatialReference;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C6AAEF9-400B-4C15-A9A3-B31B6E79154A")
    IotSpatialReference : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IotSpatialReference **spatialReference) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ImportFromWkt( 
            /* [in] */ BSTR wkt,
            /* [retval][out] */ VARIANT_BOOL *bSuccess) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ImportFromESRI( 
            /* [in] */ BSTR wkt,
            /* [retval][out] */ VARIANT_BOOL *bSuccess) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ExportToWkt( 
            /* [retval][out] */ BSTR *wkt) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsGeographic( 
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsProjected( 
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsSame( 
            /* [in] */ IotSpatialReference *other,
            /* [retval][out] */ VARIANT_BOOL *bSame) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetGeogName( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetProjName( 
            /* [retval][out] */ BSTR *name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSpatialReferenceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSpatialReference * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSpatialReference * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSpatialReference * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IotSpatialReference * This,
            /* [retval][out] */ IotSpatialReference **spatialReference);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ImportFromWkt )( 
            IotSpatialReference * This,
            /* [in] */ BSTR wkt,
            /* [retval][out] */ VARIANT_BOOL *bSuccess);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ImportFromESRI )( 
            IotSpatialReference * This,
            /* [in] */ BSTR wkt,
            /* [retval][out] */ VARIANT_BOOL *bSuccess);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ExportToWkt )( 
            IotSpatialReference * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsGeographic )( 
            IotSpatialReference * This,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsProjected )( 
            IotSpatialReference * This,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsSame )( 
            IotSpatialReference * This,
            /* [in] */ IotSpatialReference *other,
            /* [retval][out] */ VARIANT_BOOL *bSame);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetGeogName )( 
            IotSpatialReference * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetProjName )( 
            IotSpatialReference * This,
            /* [retval][out] */ BSTR *name);
        
        END_INTERFACE
    } IotSpatialReferenceVtbl;

    interface IotSpatialReference
    {
        CONST_VTBL struct IotSpatialReferenceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSpatialReference_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSpatialReference_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSpatialReference_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSpatialReference_Clone(This,spatialReference)	\
    (This)->lpVtbl -> Clone(This,spatialReference)

#define IotSpatialReference_ImportFromWkt(This,wkt,bSuccess)	\
    (This)->lpVtbl -> ImportFromWkt(This,wkt,bSuccess)

#define IotSpatialReference_ImportFromESRI(This,wkt,bSuccess)	\
    (This)->lpVtbl -> ImportFromESRI(This,wkt,bSuccess)

#define IotSpatialReference_ExportToWkt(This,wkt)	\
    (This)->lpVtbl -> ExportToWkt(This,wkt)

#define IotSpatialReference_IsGeographic(This,bRet)	\
    (This)->lpVtbl -> IsGeographic(This,bRet)

#define IotSpatialReference_IsProjected(This,bRet)	\
    (This)->lpVtbl -> IsProjected(This,bRet)

#define IotSpatialReference_IsSame(This,other,bSame)	\
    (This)->lpVtbl -> IsSame(This,other,bSame)

#define IotSpatialReference_GetGeogName(This,name)	\
    (This)->lpVtbl -> GetGeogName(This,name)

#define IotSpatialReference_GetProjName(This,name)	\
    (This)->lpVtbl -> GetProjName(This,name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSpatialReference_Clone_Proxy( 
    IotSpatialReference * This,
    /* [retval][out] */ IotSpatialReference **spatialReference);


void __RPC_STUB IotSpatialReference_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSpatialReference_ImportFromWkt_Proxy( 
    IotSpatialReference * This,
    /* [in] */ BSTR wkt,
    /* [retval][out] */ VARIANT_BOOL *bSuccess);


void __RPC_STUB IotSpatialReference_ImportFromWkt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSpatialReference_ImportFromESRI_Proxy( 
    IotSpatialReference * This,
    /* [in] */ BSTR wkt,
    /* [retval][out] */ VARIANT_BOOL *bSuccess);


void __RPC_STUB IotSpatialReference_ImportFromESRI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSpatialReference_ExportToWkt_Proxy( 
    IotSpatialReference * This,
    /* [retval][out] */ BSTR *wkt);


void __RPC_STUB IotSpatialReference_ExportToWkt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSpatialReference_IsGeographic_Proxy( 
    IotSpatialReference * This,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotSpatialReference_IsGeographic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSpatialReference_IsProjected_Proxy( 
    IotSpatialReference * This,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotSpatialReference_IsProjected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSpatialReference_IsSame_Proxy( 
    IotSpatialReference * This,
    /* [in] */ IotSpatialReference *other,
    /* [retval][out] */ VARIANT_BOOL *bSame);


void __RPC_STUB IotSpatialReference_IsSame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSpatialReference_GetGeogName_Proxy( 
    IotSpatialReference * This,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB IotSpatialReference_GetGeogName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSpatialReference_GetProjName_Proxy( 
    IotSpatialReference * This,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB IotSpatialReference_GetProjName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSpatialReference_INTERFACE_DEFINED__ */


#ifndef __IotProjTransform_INTERFACE_DEFINED__
#define __IotProjTransform_INTERFACE_DEFINED__

/* interface IotProjTransform */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotProjTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10D9A3D7-BD2B-4B51-8306-88A8CF64A0F9")
    IotProjTransform : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FromSpatialReference( 
            /* [retval][out] */ IotSpatialReference **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ToSpatialReference( 
            /* [retval][out] */ IotSpatialReference **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSpatialReference( 
            /* [in] */ IotSpatialReference *from,
            /* [in] */ IotSpatialReference *to) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ LONG count,
            /* [in] */ SAFEARRAY * *inX,
            /* [in] */ SAFEARRAY * *inY,
            /* [out][in] */ SAFEARRAY * *outX,
            /* [out][in] */ SAFEARRAY * *outY) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotProjTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotProjTransform * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotProjTransform * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotProjTransform * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FromSpatialReference )( 
            IotProjTransform * This,
            /* [retval][out] */ IotSpatialReference **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ToSpatialReference )( 
            IotProjTransform * This,
            /* [retval][out] */ IotSpatialReference **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetSpatialReference )( 
            IotProjTransform * This,
            /* [in] */ IotSpatialReference *from,
            /* [in] */ IotSpatialReference *to);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IotProjTransform * This,
            /* [in] */ LONG count,
            /* [in] */ SAFEARRAY * *inX,
            /* [in] */ SAFEARRAY * *inY,
            /* [out][in] */ SAFEARRAY * *outX,
            /* [out][in] */ SAFEARRAY * *outY);
        
        END_INTERFACE
    } IotProjTransformVtbl;

    interface IotProjTransform
    {
        CONST_VTBL struct IotProjTransformVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotProjTransform_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotProjTransform_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotProjTransform_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotProjTransform_get_FromSpatialReference(This,pVal)	\
    (This)->lpVtbl -> get_FromSpatialReference(This,pVal)

#define IotProjTransform_get_ToSpatialReference(This,pVal)	\
    (This)->lpVtbl -> get_ToSpatialReference(This,pVal)

#define IotProjTransform_SetSpatialReference(This,from,to)	\
    (This)->lpVtbl -> SetSpatialReference(This,from,to)

#define IotProjTransform_Transform(This,count,inX,inY,outX,outY)	\
    (This)->lpVtbl -> Transform(This,count,inX,inY,outX,outY)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotProjTransform_get_FromSpatialReference_Proxy( 
    IotProjTransform * This,
    /* [retval][out] */ IotSpatialReference **pVal);


void __RPC_STUB IotProjTransform_get_FromSpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotProjTransform_get_ToSpatialReference_Proxy( 
    IotProjTransform * This,
    /* [retval][out] */ IotSpatialReference **pVal);


void __RPC_STUB IotProjTransform_get_ToSpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotProjTransform_SetSpatialReference_Proxy( 
    IotProjTransform * This,
    /* [in] */ IotSpatialReference *from,
    /* [in] */ IotSpatialReference *to);


void __RPC_STUB IotProjTransform_SetSpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotProjTransform_Transform_Proxy( 
    IotProjTransform * This,
    /* [in] */ LONG count,
    /* [in] */ SAFEARRAY * *inX,
    /* [in] */ SAFEARRAY * *inY,
    /* [out][in] */ SAFEARRAY * *outX,
    /* [out][in] */ SAFEARRAY * *outY);


void __RPC_STUB IotProjTransform_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotProjTransform_INTERFACE_DEFINED__ */



#ifndef __otcGeodatabase_LIBRARY_DEFINED__
#define __otcGeodatabase_LIBRARY_DEFINED__

/* library otcGeodatabase */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_otcGeodatabase;

#ifndef __IotWorkspace_INTERFACE_DEFINED__
#define __IotWorkspace_INTERFACE_DEFINED__

/* interface IotWorkspace */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotWorkspace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DC845E45-7E27-40CD-AFFE-0A19246D4C84")
    IotWorkspace : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ otWorkspaceType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenFeatureClass( 
            /* [in] */ BSTR filename,
            /* [retval][out] */ IotFeatureClass **FeatureClass) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsEditing( 
            /* [retval][out] */ VARIANT_BOOL *bret) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartEdit( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StopEdit( 
            /* [in] */ VARIANT_BOOL save) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartEditOperation( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StopEditOperation( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UndoEdit( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RedoEdit( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CanUndo( 
            /* [retval][out] */ VARIANT_BOOL *bret) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CanRedo( 
            /* [retval][out] */ VARIANT_BOOL *ret) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenRasterDataset( 
            /* [in] */ BSTR filename,
            /* [in] */ VARIANT_BOOL ReadOnly,
            /* [retval][out] */ IotRasterDataset **ret) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateFeatureClass( 
            /* [in] */ BSTR filename,
            /* [in] */ /* external definition not present */ IotEnvelope *extent,
            /* [in] */ BSTR projWkt,
            /* [in] */ enum /* external definition not present */ otGeometryType FeatureType,
            /* [in] */ VARIANT_BOOL hasZ,
            /* [in] */ VARIANT_BOOL hasM,
            /* [in] */ LONG numField,
            /* [in] */ SAFEARRAY * *fields,
            /* [retval][out] */ IotFeatureClass **retFeatureClass) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotWorkspaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotWorkspace * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotWorkspace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotWorkspace * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotWorkspace * This,
            /* [retval][out] */ otWorkspaceType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Path )( 
            IotWorkspace * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenFeatureClass )( 
            IotWorkspace * This,
            /* [in] */ BSTR filename,
            /* [retval][out] */ IotFeatureClass **FeatureClass);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsEditing )( 
            IotWorkspace * This,
            /* [retval][out] */ VARIANT_BOOL *bret);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StartEdit )( 
            IotWorkspace * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StopEdit )( 
            IotWorkspace * This,
            /* [in] */ VARIANT_BOOL save);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StartEditOperation )( 
            IotWorkspace * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StopEditOperation )( 
            IotWorkspace * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UndoEdit )( 
            IotWorkspace * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RedoEdit )( 
            IotWorkspace * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CanUndo )( 
            IotWorkspace * This,
            /* [retval][out] */ VARIANT_BOOL *bret);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CanRedo )( 
            IotWorkspace * This,
            /* [retval][out] */ VARIANT_BOOL *ret);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpenRasterDataset )( 
            IotWorkspace * This,
            /* [in] */ BSTR filename,
            /* [in] */ VARIANT_BOOL ReadOnly,
            /* [retval][out] */ IotRasterDataset **ret);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateFeatureClass )( 
            IotWorkspace * This,
            /* [in] */ BSTR filename,
            /* [in] */ /* external definition not present */ IotEnvelope *extent,
            /* [in] */ BSTR projWkt,
            /* [in] */ enum /* external definition not present */ otGeometryType FeatureType,
            /* [in] */ VARIANT_BOOL hasZ,
            /* [in] */ VARIANT_BOOL hasM,
            /* [in] */ LONG numField,
            /* [in] */ SAFEARRAY * *fields,
            /* [retval][out] */ IotFeatureClass **retFeatureClass);
        
        END_INTERFACE
    } IotWorkspaceVtbl;

    interface IotWorkspace
    {
        CONST_VTBL struct IotWorkspaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotWorkspace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotWorkspace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotWorkspace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotWorkspace_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IotWorkspace_get_Path(This,pVal)	\
    (This)->lpVtbl -> get_Path(This,pVal)

#define IotWorkspace_OpenFeatureClass(This,filename,FeatureClass)	\
    (This)->lpVtbl -> OpenFeatureClass(This,filename,FeatureClass)

#define IotWorkspace_IsEditing(This,bret)	\
    (This)->lpVtbl -> IsEditing(This,bret)

#define IotWorkspace_StartEdit(This)	\
    (This)->lpVtbl -> StartEdit(This)

#define IotWorkspace_StopEdit(This,save)	\
    (This)->lpVtbl -> StopEdit(This,save)

#define IotWorkspace_StartEditOperation(This)	\
    (This)->lpVtbl -> StartEditOperation(This)

#define IotWorkspace_StopEditOperation(This)	\
    (This)->lpVtbl -> StopEditOperation(This)

#define IotWorkspace_UndoEdit(This)	\
    (This)->lpVtbl -> UndoEdit(This)

#define IotWorkspace_RedoEdit(This)	\
    (This)->lpVtbl -> RedoEdit(This)

#define IotWorkspace_CanUndo(This,bret)	\
    (This)->lpVtbl -> CanUndo(This,bret)

#define IotWorkspace_CanRedo(This,ret)	\
    (This)->lpVtbl -> CanRedo(This,ret)

#define IotWorkspace_OpenRasterDataset(This,filename,ReadOnly,ret)	\
    (This)->lpVtbl -> OpenRasterDataset(This,filename,ReadOnly,ret)

#define IotWorkspace_CreateFeatureClass(This,filename,extent,projWkt,FeatureType,hasZ,hasM,numField,fields,retFeatureClass)	\
    (This)->lpVtbl -> CreateFeatureClass(This,filename,extent,projWkt,FeatureType,hasZ,hasM,numField,fields,retFeatureClass)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotWorkspace_get_Type_Proxy( 
    IotWorkspace * This,
    /* [retval][out] */ otWorkspaceType *pVal);


void __RPC_STUB IotWorkspace_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotWorkspace_get_Path_Proxy( 
    IotWorkspace * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotWorkspace_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_OpenFeatureClass_Proxy( 
    IotWorkspace * This,
    /* [in] */ BSTR filename,
    /* [retval][out] */ IotFeatureClass **FeatureClass);


void __RPC_STUB IotWorkspace_OpenFeatureClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_IsEditing_Proxy( 
    IotWorkspace * This,
    /* [retval][out] */ VARIANT_BOOL *bret);


void __RPC_STUB IotWorkspace_IsEditing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_StartEdit_Proxy( 
    IotWorkspace * This);


void __RPC_STUB IotWorkspace_StartEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_StopEdit_Proxy( 
    IotWorkspace * This,
    /* [in] */ VARIANT_BOOL save);


void __RPC_STUB IotWorkspace_StopEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_StartEditOperation_Proxy( 
    IotWorkspace * This);


void __RPC_STUB IotWorkspace_StartEditOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_StopEditOperation_Proxy( 
    IotWorkspace * This);


void __RPC_STUB IotWorkspace_StopEditOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_UndoEdit_Proxy( 
    IotWorkspace * This);


void __RPC_STUB IotWorkspace_UndoEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_RedoEdit_Proxy( 
    IotWorkspace * This);


void __RPC_STUB IotWorkspace_RedoEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_CanUndo_Proxy( 
    IotWorkspace * This,
    /* [retval][out] */ VARIANT_BOOL *bret);


void __RPC_STUB IotWorkspace_CanUndo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_CanRedo_Proxy( 
    IotWorkspace * This,
    /* [retval][out] */ VARIANT_BOOL *ret);


void __RPC_STUB IotWorkspace_CanRedo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_OpenRasterDataset_Proxy( 
    IotWorkspace * This,
    /* [in] */ BSTR filename,
    /* [in] */ VARIANT_BOOL ReadOnly,
    /* [retval][out] */ IotRasterDataset **ret);


void __RPC_STUB IotWorkspace_OpenRasterDataset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotWorkspace_CreateFeatureClass_Proxy( 
    IotWorkspace * This,
    /* [in] */ BSTR filename,
    /* [in] */ /* external definition not present */ IotEnvelope *extent,
    /* [in] */ BSTR projWkt,
    /* [in] */ enum /* external definition not present */ otGeometryType FeatureType,
    /* [in] */ VARIANT_BOOL hasZ,
    /* [in] */ VARIANT_BOOL hasM,
    /* [in] */ LONG numField,
    /* [in] */ SAFEARRAY * *fields,
    /* [retval][out] */ IotFeatureClass **retFeatureClass);


void __RPC_STUB IotWorkspace_CreateFeatureClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotWorkspace_INTERFACE_DEFINED__ */


#ifndef __IotSpatialQuery_INTERFACE_DEFINED__
#define __IotSpatialQuery_INTERFACE_DEFINED__

/* interface IotSpatialQuery */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSpatialQuery;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E541D0C8-E8EF-4FF5-8021-1C4664BCFA5A")
    IotSpatialQuery : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpatialRelation( 
            /* [retval][out] */ otSpatialRel *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SpatialRelation( 
            /* [in] */ otSpatialRel newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Geometry( 
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Geometry( 
            /* [in] */ /* external definition not present */ IotGeometry *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSpatialQueryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSpatialQuery * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSpatialQuery * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSpatialQuery * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialRelation )( 
            IotSpatialQuery * This,
            /* [retval][out] */ otSpatialRel *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SpatialRelation )( 
            IotSpatialQuery * This,
            /* [in] */ otSpatialRel newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotSpatialQuery * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotSpatialQuery * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        END_INTERFACE
    } IotSpatialQueryVtbl;

    interface IotSpatialQuery
    {
        CONST_VTBL struct IotSpatialQueryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSpatialQuery_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSpatialQuery_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSpatialQuery_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSpatialQuery_get_SpatialRelation(This,pVal)	\
    (This)->lpVtbl -> get_SpatialRelation(This,pVal)

#define IotSpatialQuery_put_SpatialRelation(This,newVal)	\
    (This)->lpVtbl -> put_SpatialRelation(This,newVal)

#define IotSpatialQuery_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotSpatialQuery_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSpatialQuery_get_SpatialRelation_Proxy( 
    IotSpatialQuery * This,
    /* [retval][out] */ otSpatialRel *pVal);


void __RPC_STUB IotSpatialQuery_get_SpatialRelation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSpatialQuery_put_SpatialRelation_Proxy( 
    IotSpatialQuery * This,
    /* [in] */ otSpatialRel newVal);


void __RPC_STUB IotSpatialQuery_put_SpatialRelation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSpatialQuery_get_Geometry_Proxy( 
    IotSpatialQuery * This,
    /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);


void __RPC_STUB IotSpatialQuery_get_Geometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSpatialQuery_put_Geometry_Proxy( 
    IotSpatialQuery * This,
    /* [in] */ /* external definition not present */ IotGeometry *newVal);


void __RPC_STUB IotSpatialQuery_put_Geometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSpatialQuery_INTERFACE_DEFINED__ */


#ifndef __IotDataObject_INTERFACE_DEFINED__
#define __IotDataObject_INTERFACE_DEFINED__

/* interface IotDataObject */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotDataObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3B54E8E-CCD7-4d21-9D12-F7CC2700E4DC")
    IotDataObject : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetType( 
            otDataType *type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetExtent( 
            /* [retval][out] */ /* external definition not present */ IotEnvelope **envelope) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Workspace( 
            /* [retval][out] */ IotWorkspace **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotDataObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotDataObject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotDataObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotDataObject * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetType )( 
            IotDataObject * This,
            otDataType *type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IotDataObject * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetExtent )( 
            IotDataObject * This,
            /* [retval][out] */ /* external definition not present */ IotEnvelope **envelope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Workspace )( 
            IotDataObject * This,
            /* [retval][out] */ IotWorkspace **pVal);
        
        END_INTERFACE
    } IotDataObjectVtbl;

    interface IotDataObject
    {
        CONST_VTBL struct IotDataObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotDataObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotDataObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotDataObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotDataObject_GetType(This,type)	\
    (This)->lpVtbl -> GetType(This,type)

#define IotDataObject_GetName(This,name)	\
    (This)->lpVtbl -> GetName(This,name)

#define IotDataObject_GetExtent(This,envelope)	\
    (This)->lpVtbl -> GetExtent(This,envelope)

#define IotDataObject_get_Workspace(This,pVal)	\
    (This)->lpVtbl -> get_Workspace(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotDataObject_GetType_Proxy( 
    IotDataObject * This,
    otDataType *type);


void __RPC_STUB IotDataObject_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotDataObject_GetName_Proxy( 
    IotDataObject * This,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB IotDataObject_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotDataObject_GetExtent_Proxy( 
    IotDataObject * This,
    /* [retval][out] */ /* external definition not present */ IotEnvelope **envelope);


void __RPC_STUB IotDataObject_GetExtent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotDataObject_get_Workspace_Proxy( 
    IotDataObject * This,
    /* [retval][out] */ IotWorkspace **pVal);


void __RPC_STUB IotDataObject_get_Workspace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotDataObject_INTERFACE_DEFINED__ */


#ifndef __IotTable_INTERFACE_DEFINED__
#define __IotTable_INTERFACE_DEFINED__

/* interface IotTable */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotTable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("90993C2C-8725-4c0b-822C-8C8FE30E2F71")
    IotTable : public IotDataObject
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Query( 
            /* [in] */ IotSimpleQuery *queryFilter,
            /* [in] */ VARIANT_BOOL bReadOnly,
            /* [retval][out] */ IotCursor **retCursor) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Select( 
            /* [in] */ IotSimpleQuery *queryFilter,
            /* [retval][out] */ IotSelectionSet **ret) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FieldCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetField( 
            /* [in] */ LONG index,
            /* [retval][out] */ IotField **field) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindField( 
            /* [in] */ BSTR name,
            /* [retval][out] */ LONG *index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotTableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotTable * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotTable * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotTable * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetType )( 
            IotTable * This,
            otDataType *type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IotTable * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetExtent )( 
            IotTable * This,
            /* [retval][out] */ /* external definition not present */ IotEnvelope **envelope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Workspace )( 
            IotTable * This,
            /* [retval][out] */ IotWorkspace **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Query )( 
            IotTable * This,
            /* [in] */ IotSimpleQuery *queryFilter,
            /* [in] */ VARIANT_BOOL bReadOnly,
            /* [retval][out] */ IotCursor **retCursor);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Select )( 
            IotTable * This,
            /* [in] */ IotSimpleQuery *queryFilter,
            /* [retval][out] */ IotSelectionSet **ret);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FieldCount )( 
            IotTable * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetField )( 
            IotTable * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotField **field);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindField )( 
            IotTable * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ LONG *index);
        
        END_INTERFACE
    } IotTableVtbl;

    interface IotTable
    {
        CONST_VTBL struct IotTableVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotTable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotTable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotTable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotTable_GetType(This,type)	\
    (This)->lpVtbl -> GetType(This,type)

#define IotTable_GetName(This,name)	\
    (This)->lpVtbl -> GetName(This,name)

#define IotTable_GetExtent(This,envelope)	\
    (This)->lpVtbl -> GetExtent(This,envelope)

#define IotTable_get_Workspace(This,pVal)	\
    (This)->lpVtbl -> get_Workspace(This,pVal)


#define IotTable_Query(This,queryFilter,bReadOnly,retCursor)	\
    (This)->lpVtbl -> Query(This,queryFilter,bReadOnly,retCursor)

#define IotTable_Select(This,queryFilter,ret)	\
    (This)->lpVtbl -> Select(This,queryFilter,ret)

#define IotTable_get_FieldCount(This,pVal)	\
    (This)->lpVtbl -> get_FieldCount(This,pVal)

#define IotTable_GetField(This,index,field)	\
    (This)->lpVtbl -> GetField(This,index,field)

#define IotTable_FindField(This,name,index)	\
    (This)->lpVtbl -> FindField(This,name,index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotTable_Query_Proxy( 
    IotTable * This,
    /* [in] */ IotSimpleQuery *queryFilter,
    /* [in] */ VARIANT_BOOL bReadOnly,
    /* [retval][out] */ IotCursor **retCursor);


void __RPC_STUB IotTable_Query_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotTable_Select_Proxy( 
    IotTable * This,
    /* [in] */ IotSimpleQuery *queryFilter,
    /* [retval][out] */ IotSelectionSet **ret);


void __RPC_STUB IotTable_Select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotTable_get_FieldCount_Proxy( 
    IotTable * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotTable_get_FieldCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotTable_GetField_Proxy( 
    IotTable * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IotField **field);


void __RPC_STUB IotTable_GetField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotTable_FindField_Proxy( 
    IotTable * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ LONG *index);


void __RPC_STUB IotTable_FindField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotTable_INTERFACE_DEFINED__ */


#ifndef __IotFeatureClass_INTERFACE_DEFINED__
#define __IotFeatureClass_INTERFACE_DEFINED__

/* interface IotFeatureClass */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotFeatureClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8510FECB-1125-4B18-BCBA-DCEC58D49541")
    IotFeatureClass : public IotTable
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FeatureCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeFieldName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFeature( 
            /* [in] */ LONG index,
            /* [retval][out] */ IotFeature **feature) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasM( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasZ( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeType( 
            /* [retval][out] */ enum /* external definition not present */ otGeometryType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateFeature( 
            /* [retval][out] */ IotFeature **retFeature) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteFeature( 
            /* [in] */ LONG index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddFeature( 
            /* [in] */ IotFeature *feature) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpatialReference( 
            /* [retval][out] */ IotSpatialReference **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotFeatureClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotFeatureClass * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotFeatureClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotFeatureClass * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetType )( 
            IotFeatureClass * This,
            otDataType *type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IotFeatureClass * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetExtent )( 
            IotFeatureClass * This,
            /* [retval][out] */ /* external definition not present */ IotEnvelope **envelope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Workspace )( 
            IotFeatureClass * This,
            /* [retval][out] */ IotWorkspace **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Query )( 
            IotFeatureClass * This,
            /* [in] */ IotSimpleQuery *queryFilter,
            /* [in] */ VARIANT_BOOL bReadOnly,
            /* [retval][out] */ IotCursor **retCursor);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Select )( 
            IotFeatureClass * This,
            /* [in] */ IotSimpleQuery *queryFilter,
            /* [retval][out] */ IotSelectionSet **ret);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FieldCount )( 
            IotFeatureClass * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetField )( 
            IotFeatureClass * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotField **field);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindField )( 
            IotFeatureClass * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ LONG *index);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FeatureCount )( 
            IotFeatureClass * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeFieldName )( 
            IotFeatureClass * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFeature )( 
            IotFeatureClass * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotFeature **feature);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasM )( 
            IotFeatureClass * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasZ )( 
            IotFeatureClass * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeType )( 
            IotFeatureClass * This,
            /* [retval][out] */ enum /* external definition not present */ otGeometryType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateFeature )( 
            IotFeatureClass * This,
            /* [retval][out] */ IotFeature **retFeature);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteFeature )( 
            IotFeatureClass * This,
            /* [in] */ LONG index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddFeature )( 
            IotFeatureClass * This,
            /* [in] */ IotFeature *feature);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IotFeatureClass * This,
            /* [retval][out] */ IotSpatialReference **pVal);
        
        END_INTERFACE
    } IotFeatureClassVtbl;

    interface IotFeatureClass
    {
        CONST_VTBL struct IotFeatureClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotFeatureClass_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotFeatureClass_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotFeatureClass_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotFeatureClass_GetType(This,type)	\
    (This)->lpVtbl -> GetType(This,type)

#define IotFeatureClass_GetName(This,name)	\
    (This)->lpVtbl -> GetName(This,name)

#define IotFeatureClass_GetExtent(This,envelope)	\
    (This)->lpVtbl -> GetExtent(This,envelope)

#define IotFeatureClass_get_Workspace(This,pVal)	\
    (This)->lpVtbl -> get_Workspace(This,pVal)


#define IotFeatureClass_Query(This,queryFilter,bReadOnly,retCursor)	\
    (This)->lpVtbl -> Query(This,queryFilter,bReadOnly,retCursor)

#define IotFeatureClass_Select(This,queryFilter,ret)	\
    (This)->lpVtbl -> Select(This,queryFilter,ret)

#define IotFeatureClass_get_FieldCount(This,pVal)	\
    (This)->lpVtbl -> get_FieldCount(This,pVal)

#define IotFeatureClass_GetField(This,index,field)	\
    (This)->lpVtbl -> GetField(This,index,field)

#define IotFeatureClass_FindField(This,name,index)	\
    (This)->lpVtbl -> FindField(This,name,index)


#define IotFeatureClass_get_FeatureCount(This,pVal)	\
    (This)->lpVtbl -> get_FeatureCount(This,pVal)

#define IotFeatureClass_get_ShapeFieldName(This,pVal)	\
    (This)->lpVtbl -> get_ShapeFieldName(This,pVal)

#define IotFeatureClass_GetFeature(This,index,feature)	\
    (This)->lpVtbl -> GetFeature(This,index,feature)

#define IotFeatureClass_get_HasM(This,pVal)	\
    (This)->lpVtbl -> get_HasM(This,pVal)

#define IotFeatureClass_get_HasZ(This,pVal)	\
    (This)->lpVtbl -> get_HasZ(This,pVal)

#define IotFeatureClass_get_ShapeType(This,pVal)	\
    (This)->lpVtbl -> get_ShapeType(This,pVal)

#define IotFeatureClass_CreateFeature(This,retFeature)	\
    (This)->lpVtbl -> CreateFeature(This,retFeature)

#define IotFeatureClass_DeleteFeature(This,index)	\
    (This)->lpVtbl -> DeleteFeature(This,index)

#define IotFeatureClass_AddFeature(This,feature)	\
    (This)->lpVtbl -> AddFeature(This,feature)

#define IotFeatureClass_get_SpatialReference(This,pVal)	\
    (This)->lpVtbl -> get_SpatialReference(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_get_FeatureCount_Proxy( 
    IotFeatureClass * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotFeatureClass_get_FeatureCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_get_ShapeFieldName_Proxy( 
    IotFeatureClass * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotFeatureClass_get_ShapeFieldName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_GetFeature_Proxy( 
    IotFeatureClass * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IotFeature **feature);


void __RPC_STUB IotFeatureClass_GetFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_get_HasM_Proxy( 
    IotFeatureClass * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotFeatureClass_get_HasM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_get_HasZ_Proxy( 
    IotFeatureClass * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotFeatureClass_get_HasZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_get_ShapeType_Proxy( 
    IotFeatureClass * This,
    /* [retval][out] */ enum /* external definition not present */ otGeometryType *pVal);


void __RPC_STUB IotFeatureClass_get_ShapeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_CreateFeature_Proxy( 
    IotFeatureClass * This,
    /* [retval][out] */ IotFeature **retFeature);


void __RPC_STUB IotFeatureClass_CreateFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_DeleteFeature_Proxy( 
    IotFeatureClass * This,
    /* [in] */ LONG index);


void __RPC_STUB IotFeatureClass_DeleteFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_AddFeature_Proxy( 
    IotFeatureClass * This,
    /* [in] */ IotFeature *feature);


void __RPC_STUB IotFeatureClass_AddFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeatureClass_get_SpatialReference_Proxy( 
    IotFeatureClass * This,
    /* [retval][out] */ IotSpatialReference **pVal);


void __RPC_STUB IotFeatureClass_get_SpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotFeatureClass_INTERFACE_DEFINED__ */


#ifndef __IotRasterDataset_INTERFACE_DEFINED__
#define __IotRasterDataset_INTERFACE_DEFINED__

/* interface IotRasterDataset */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotRasterDataset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05626CAA-F7D6-41B7-976A-63D175787C71")
    IotRasterDataset : public IotDataObject
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Writable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ChannelCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Projection( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Projection( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasPyramid( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateRasterBlock( 
            /* [in] */ LONG BandIndex,
            /* [in] */ LONG width,
            /* [in] */ LONG height,
            /* [retval][out] */ IotRasterBlock **ret) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReadData( 
            /* [in] */ LONG BandIndex,
            /* [in] */ LONG row,
            /* [in] */ LONG col,
            /* [in] */ IotRasterBlock *RasterBlock) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpatialReference( 
            /* [retval][out] */ IotSpatialReference **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotRasterDatasetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotRasterDataset * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotRasterDataset * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotRasterDataset * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetType )( 
            IotRasterDataset * This,
            otDataType *type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IotRasterDataset * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetExtent )( 
            IotRasterDataset * This,
            /* [retval][out] */ /* external definition not present */ IotEnvelope **envelope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Workspace )( 
            IotRasterDataset * This,
            /* [retval][out] */ IotWorkspace **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Writable )( 
            IotRasterDataset * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChannelCount )( 
            IotRasterDataset * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IotRasterDataset * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IotRasterDataset * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Projection )( 
            IotRasterDataset * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Projection )( 
            IotRasterDataset * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasPyramid )( 
            IotRasterDataset * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateRasterBlock )( 
            IotRasterDataset * This,
            /* [in] */ LONG BandIndex,
            /* [in] */ LONG width,
            /* [in] */ LONG height,
            /* [retval][out] */ IotRasterBlock **ret);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReadData )( 
            IotRasterDataset * This,
            /* [in] */ LONG BandIndex,
            /* [in] */ LONG row,
            /* [in] */ LONG col,
            /* [in] */ IotRasterBlock *RasterBlock);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IotRasterDataset * This,
            /* [retval][out] */ IotSpatialReference **pVal);
        
        END_INTERFACE
    } IotRasterDatasetVtbl;

    interface IotRasterDataset
    {
        CONST_VTBL struct IotRasterDatasetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotRasterDataset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotRasterDataset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotRasterDataset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotRasterDataset_GetType(This,type)	\
    (This)->lpVtbl -> GetType(This,type)

#define IotRasterDataset_GetName(This,name)	\
    (This)->lpVtbl -> GetName(This,name)

#define IotRasterDataset_GetExtent(This,envelope)	\
    (This)->lpVtbl -> GetExtent(This,envelope)

#define IotRasterDataset_get_Workspace(This,pVal)	\
    (This)->lpVtbl -> get_Workspace(This,pVal)


#define IotRasterDataset_get_Writable(This,pVal)	\
    (This)->lpVtbl -> get_Writable(This,pVal)

#define IotRasterDataset_get_ChannelCount(This,pVal)	\
    (This)->lpVtbl -> get_ChannelCount(This,pVal)

#define IotRasterDataset_get_Width(This,pVal)	\
    (This)->lpVtbl -> get_Width(This,pVal)

#define IotRasterDataset_get_Height(This,pVal)	\
    (This)->lpVtbl -> get_Height(This,pVal)

#define IotRasterDataset_get_Projection(This,pVal)	\
    (This)->lpVtbl -> get_Projection(This,pVal)

#define IotRasterDataset_put_Projection(This,newVal)	\
    (This)->lpVtbl -> put_Projection(This,newVal)

#define IotRasterDataset_get_HasPyramid(This,pVal)	\
    (This)->lpVtbl -> get_HasPyramid(This,pVal)

#define IotRasterDataset_CreateRasterBlock(This,BandIndex,width,height,ret)	\
    (This)->lpVtbl -> CreateRasterBlock(This,BandIndex,width,height,ret)

#define IotRasterDataset_ReadData(This,BandIndex,row,col,RasterBlock)	\
    (This)->lpVtbl -> ReadData(This,BandIndex,row,col,RasterBlock)

#define IotRasterDataset_get_SpatialReference(This,pVal)	\
    (This)->lpVtbl -> get_SpatialReference(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_get_Writable_Proxy( 
    IotRasterDataset * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotRasterDataset_get_Writable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_get_ChannelCount_Proxy( 
    IotRasterDataset * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotRasterDataset_get_ChannelCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_get_Width_Proxy( 
    IotRasterDataset * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotRasterDataset_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_get_Height_Proxy( 
    IotRasterDataset * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotRasterDataset_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_get_Projection_Proxy( 
    IotRasterDataset * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotRasterDataset_get_Projection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_put_Projection_Proxy( 
    IotRasterDataset * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotRasterDataset_put_Projection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_get_HasPyramid_Proxy( 
    IotRasterDataset * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotRasterDataset_get_HasPyramid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_CreateRasterBlock_Proxy( 
    IotRasterDataset * This,
    /* [in] */ LONG BandIndex,
    /* [in] */ LONG width,
    /* [in] */ LONG height,
    /* [retval][out] */ IotRasterBlock **ret);


void __RPC_STUB IotRasterDataset_CreateRasterBlock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_ReadData_Proxy( 
    IotRasterDataset * This,
    /* [in] */ LONG BandIndex,
    /* [in] */ LONG row,
    /* [in] */ LONG col,
    /* [in] */ IotRasterBlock *RasterBlock);


void __RPC_STUB IotRasterDataset_ReadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterDataset_get_SpatialReference_Proxy( 
    IotRasterDataset * This,
    /* [retval][out] */ IotSpatialReference **pVal);


void __RPC_STUB IotRasterDataset_get_SpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotRasterDataset_INTERFACE_DEFINED__ */


#ifndef __IotFeature_INTERFACE_DEFINED__
#define __IotFeature_INTERFACE_DEFINED__

/* interface IotFeature */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotFeature;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BFC52BEC-08B0-4912-9B3C-95F513D4ADBE")
    IotFeature : public IotRow
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Shape( 
            /* [in] */ /* external definition not present */ IotGeometry *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeClone( 
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotFeatureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotFeature * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotFeature * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotFeature * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Table )( 
            IotFeature * This,
            /* [retval][out] */ IotTable **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FieldCount )( 
            IotFeature * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IotFeature * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Field )( 
            IotFeature * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotField **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IotFeature * This,
            /* [in] */ LONG index,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IotFeature * This,
            /* [in] */ LONG index,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IotFeature * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IotFeature * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IotFeature * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Shape )( 
            IotFeature * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeClone )( 
            IotFeature * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        END_INTERFACE
    } IotFeatureVtbl;

    interface IotFeature
    {
        CONST_VTBL struct IotFeatureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotFeature_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotFeature_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotFeature_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotFeature_get_Table(This,pVal)	\
    (This)->lpVtbl -> get_Table(This,pVal)

#define IotFeature_get_FieldCount(This,pVal)	\
    (This)->lpVtbl -> get_FieldCount(This,pVal)

#define IotFeature_get_ID(This,pVal)	\
    (This)->lpVtbl -> get_ID(This,pVal)

#define IotFeature_get_Field(This,index,pVal)	\
    (This)->lpVtbl -> get_Field(This,index,pVal)

#define IotFeature_get_Value(This,index,pVal)	\
    (This)->lpVtbl -> get_Value(This,index,pVal)

#define IotFeature_put_Value(This,index,newVal)	\
    (This)->lpVtbl -> put_Value(This,index,newVal)

#define IotFeature_Update(This)	\
    (This)->lpVtbl -> Update(This)

#define IotFeature_Delete(This)	\
    (This)->lpVtbl -> Delete(This)


#define IotFeature_get_Shape(This,pVal)	\
    (This)->lpVtbl -> get_Shape(This,pVal)

#define IotFeature_put_Shape(This,newVal)	\
    (This)->lpVtbl -> put_Shape(This,newVal)

#define IotFeature_get_ShapeClone(This,pVal)	\
    (This)->lpVtbl -> get_ShapeClone(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeature_get_Shape_Proxy( 
    IotFeature * This,
    /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);


void __RPC_STUB IotFeature_get_Shape_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotFeature_put_Shape_Proxy( 
    IotFeature * This,
    /* [in] */ /* external definition not present */ IotGeometry *newVal);


void __RPC_STUB IotFeature_put_Shape_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeature_get_ShapeClone_Proxy( 
    IotFeature * This,
    /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);


void __RPC_STUB IotFeature_get_ShapeClone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotFeature_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_otWorkspace;

#ifdef __cplusplus

class DECLSPEC_UUID("D0F4E02C-2744-44F0-AA4E-236DB4B0C32E")
otWorkspace;
#endif

EXTERN_C const CLSID CLSID_TmsWF;

#ifdef __cplusplus

class DECLSPEC_UUID("C2A9DB38-525F-4926-BBEF-EF8D704753C2")
TmsWF;
#endif

EXTERN_C const CLSID CLSID_otFeatureClass;

#ifdef __cplusplus

class DECLSPEC_UUID("5EA62603-C8B4-4D41-A9C0-F9341201BC33")
otFeatureClass;
#endif

EXTERN_C const CLSID CLSID_otField;

#ifdef __cplusplus

class DECLSPEC_UUID("383530D5-D824-4B98-A3C7-5F941250614C")
otField;
#endif

EXTERN_C const CLSID CLSID_otFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("88DF126B-E46A-42C3-911A-F1CBFE2DA4A5")
otFeature;
#endif

EXTERN_C const CLSID CLSID_otSimpleQuery;

#ifdef __cplusplus

class DECLSPEC_UUID("728BB52A-09D1-4FE2-9A99-8AA6D940BB70")
otSimpleQuery;
#endif

EXTERN_C const CLSID CLSID_otSpatialQuery;

#ifdef __cplusplus

class DECLSPEC_UUID("982AFA8F-D953-4D45-B2CD-FA6502968253")
otSpatialQuery;
#endif

EXTERN_C const CLSID CLSID_otFeatureCursor;

#ifdef __cplusplus

class DECLSPEC_UUID("1F6A9940-E855-4B2C-974D-512DD777717B")
otFeatureCursor;
#endif

EXTERN_C const CLSID CLSID_otShpWF;

#ifdef __cplusplus

class DECLSPEC_UUID("FE912E8F-0120-4288-8BF5-31C3469ED287")
otShpWF;
#endif

EXTERN_C const CLSID CLSID_otRasterDataset;

#ifdef __cplusplus

class DECLSPEC_UUID("1B8A8D38-5302-4355-A68D-4FD0DBF6CE72")
otRasterDataset;
#endif

EXTERN_C const CLSID CLSID_otIfeWF;

#ifdef __cplusplus

class DECLSPEC_UUID("5DF07ECB-A7DC-4CEB-B1DF-573BDA73CCE4")
otIfeWF;
#endif

EXTERN_C const CLSID CLSID_otRasterBlock;

#ifdef __cplusplus

class DECLSPEC_UUID("4F7B55B0-24F6-436C-BB78-9BA6B7C791A8")
otRasterBlock;
#endif

EXTERN_C const CLSID CLSID_otSelectionSet;

#ifdef __cplusplus

class DECLSPEC_UUID("10103FA4-F23A-499A-8F47-2EED0D114278")
otSelectionSet;
#endif

EXTERN_C const CLSID CLSID_otSpatialReference;

#ifdef __cplusplus

class DECLSPEC_UUID("AE6077B3-97E6-407C-8598-E70B32B0EBAC")
otSpatialReference;
#endif

EXTERN_C const CLSID CLSID_otProjTransform;

#ifdef __cplusplus

class DECLSPEC_UUID("6701C06C-4ED5-408B-9D57-48941DBB23D6")
otProjTransform;
#endif
#endif /* __otcGeodatabase_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


