

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#ifndef __otcGeometry_h__
#define __otcGeometry_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IotPointCollection_FWD_DEFINED__
#define __IotPointCollection_FWD_DEFINED__
typedef interface IotPointCollection IotPointCollection;
#endif 	/* __IotPointCollection_FWD_DEFINED__ */


#ifndef __IotTransform_FWD_DEFINED__
#define __IotTransform_FWD_DEFINED__
typedef interface IotTransform IotTransform;
#endif 	/* __IotTransform_FWD_DEFINED__ */


#ifndef __IotGeometryCollection_FWD_DEFINED__
#define __IotGeometryCollection_FWD_DEFINED__
typedef interface IotGeometryCollection IotGeometryCollection;
#endif 	/* __IotGeometryCollection_FWD_DEFINED__ */


#ifndef __IotGeometry_FWD_DEFINED__
#define __IotGeometry_FWD_DEFINED__
typedef interface IotGeometry IotGeometry;
#endif 	/* __IotGeometry_FWD_DEFINED__ */


#ifndef __IotEnvelope_FWD_DEFINED__
#define __IotEnvelope_FWD_DEFINED__
typedef interface IotEnvelope IotEnvelope;
#endif 	/* __IotEnvelope_FWD_DEFINED__ */


#ifndef __IotPoint_FWD_DEFINED__
#define __IotPoint_FWD_DEFINED__
typedef interface IotPoint IotPoint;
#endif 	/* __IotPoint_FWD_DEFINED__ */


#ifndef __IotSegment_FWD_DEFINED__
#define __IotSegment_FWD_DEFINED__
typedef interface IotSegment IotSegment;
#endif 	/* __IotSegment_FWD_DEFINED__ */


#ifndef __IotSegmentCollection_FWD_DEFINED__
#define __IotSegmentCollection_FWD_DEFINED__
typedef interface IotSegmentCollection IotSegmentCollection;
#endif 	/* __IotSegmentCollection_FWD_DEFINED__ */


#ifndef __IotLineString_FWD_DEFINED__
#define __IotLineString_FWD_DEFINED__
typedef interface IotLineString IotLineString;
#endif 	/* __IotLineString_FWD_DEFINED__ */


#ifndef __IotLineRing_FWD_DEFINED__
#define __IotLineRing_FWD_DEFINED__
typedef interface IotLineRing IotLineRing;
#endif 	/* __IotLineRing_FWD_DEFINED__ */


#ifndef __IotMultiPoint_FWD_DEFINED__
#define __IotMultiPoint_FWD_DEFINED__
typedef interface IotMultiPoint IotMultiPoint;
#endif 	/* __IotMultiPoint_FWD_DEFINED__ */


#ifndef __IotMultiLineString_FWD_DEFINED__
#define __IotMultiLineString_FWD_DEFINED__
typedef interface IotMultiLineString IotMultiLineString;
#endif 	/* __IotMultiLineString_FWD_DEFINED__ */


#ifndef __IotPolygon_FWD_DEFINED__
#define __IotPolygon_FWD_DEFINED__
typedef interface IotPolygon IotPolygon;
#endif 	/* __IotPolygon_FWD_DEFINED__ */


#ifndef __IotMultiPolygon_FWD_DEFINED__
#define __IotMultiPolygon_FWD_DEFINED__
typedef interface IotMultiPolygon IotMultiPolygon;
#endif 	/* __IotMultiPolygon_FWD_DEFINED__ */


#ifndef __IotGeoConvert_FWD_DEFINED__
#define __IotGeoConvert_FWD_DEFINED__
typedef interface IotGeoConvert IotGeoConvert;
#endif 	/* __IotGeoConvert_FWD_DEFINED__ */


#ifndef __IotCircle_FWD_DEFINED__
#define __IotCircle_FWD_DEFINED__
typedef interface IotCircle IotCircle;
#endif 	/* __IotCircle_FWD_DEFINED__ */


#ifndef __IotEllipse_FWD_DEFINED__
#define __IotEllipse_FWD_DEFINED__
typedef interface IotEllipse IotEllipse;
#endif 	/* __IotEllipse_FWD_DEFINED__ */


#ifndef __IotBezierSpline_FWD_DEFINED__
#define __IotBezierSpline_FWD_DEFINED__
typedef interface IotBezierSpline IotBezierSpline;
#endif 	/* __IotBezierSpline_FWD_DEFINED__ */


#ifndef __IotLine_FWD_DEFINED__
#define __IotLine_FWD_DEFINED__
typedef interface IotLine IotLine;
#endif 	/* __IotLine_FWD_DEFINED__ */


#ifndef __IotBezierCurve_FWD_DEFINED__
#define __IotBezierCurve_FWD_DEFINED__
typedef interface IotBezierCurve IotBezierCurve;
#endif 	/* __IotBezierCurve_FWD_DEFINED__ */


#ifndef __otEnvelope_FWD_DEFINED__
#define __otEnvelope_FWD_DEFINED__

#ifdef __cplusplus
typedef class otEnvelope otEnvelope;
#else
typedef struct otEnvelope otEnvelope;
#endif /* __cplusplus */

#endif 	/* __otEnvelope_FWD_DEFINED__ */


#ifndef __otPoint_FWD_DEFINED__
#define __otPoint_FWD_DEFINED__

#ifdef __cplusplus
typedef class otPoint otPoint;
#else
typedef struct otPoint otPoint;
#endif /* __cplusplus */

#endif 	/* __otPoint_FWD_DEFINED__ */


#ifndef __otLineString_FWD_DEFINED__
#define __otLineString_FWD_DEFINED__

#ifdef __cplusplus
typedef class otLineString otLineString;
#else
typedef struct otLineString otLineString;
#endif /* __cplusplus */

#endif 	/* __otLineString_FWD_DEFINED__ */


#ifndef __otLineRing_FWD_DEFINED__
#define __otLineRing_FWD_DEFINED__

#ifdef __cplusplus
typedef class otLineRing otLineRing;
#else
typedef struct otLineRing otLineRing;
#endif /* __cplusplus */

#endif 	/* __otLineRing_FWD_DEFINED__ */


#ifndef __otMultiPoint_FWD_DEFINED__
#define __otMultiPoint_FWD_DEFINED__

#ifdef __cplusplus
typedef class otMultiPoint otMultiPoint;
#else
typedef struct otMultiPoint otMultiPoint;
#endif /* __cplusplus */

#endif 	/* __otMultiPoint_FWD_DEFINED__ */


#ifndef __otMultiLineString_FWD_DEFINED__
#define __otMultiLineString_FWD_DEFINED__

#ifdef __cplusplus
typedef class otMultiLineString otMultiLineString;
#else
typedef struct otMultiLineString otMultiLineString;
#endif /* __cplusplus */

#endif 	/* __otMultiLineString_FWD_DEFINED__ */


#ifndef __otPolygon_FWD_DEFINED__
#define __otPolygon_FWD_DEFINED__

#ifdef __cplusplus
typedef class otPolygon otPolygon;
#else
typedef struct otPolygon otPolygon;
#endif /* __cplusplus */

#endif 	/* __otPolygon_FWD_DEFINED__ */


#ifndef __otMultiPolygon_FWD_DEFINED__
#define __otMultiPolygon_FWD_DEFINED__

#ifdef __cplusplus
typedef class otMultiPolygon otMultiPolygon;
#else
typedef struct otMultiPolygon otMultiPolygon;
#endif /* __cplusplus */

#endif 	/* __otMultiPolygon_FWD_DEFINED__ */


#ifndef __otGeoConvert_FWD_DEFINED__
#define __otGeoConvert_FWD_DEFINED__

#ifdef __cplusplus
typedef class otGeoConvert otGeoConvert;
#else
typedef struct otGeoConvert otGeoConvert;
#endif /* __cplusplus */

#endif 	/* __otGeoConvert_FWD_DEFINED__ */


#ifndef __otCircle_FWD_DEFINED__
#define __otCircle_FWD_DEFINED__

#ifdef __cplusplus
typedef class otCircle otCircle;
#else
typedef struct otCircle otCircle;
#endif /* __cplusplus */

#endif 	/* __otCircle_FWD_DEFINED__ */


#ifndef __otEllipse_FWD_DEFINED__
#define __otEllipse_FWD_DEFINED__

#ifdef __cplusplus
typedef class otEllipse otEllipse;
#else
typedef struct otEllipse otEllipse;
#endif /* __cplusplus */

#endif 	/* __otEllipse_FWD_DEFINED__ */


#ifndef __otBezierSpline_FWD_DEFINED__
#define __otBezierSpline_FWD_DEFINED__

#ifdef __cplusplus
typedef class otBezierSpline otBezierSpline;
#else
typedef struct otBezierSpline otBezierSpline;
#endif /* __cplusplus */

#endif 	/* __otBezierSpline_FWD_DEFINED__ */


#ifndef __otLine_FWD_DEFINED__
#define __otLine_FWD_DEFINED__

#ifdef __cplusplus
typedef class otLine otLine;
#else
typedef struct otLine otLine;
#endif /* __cplusplus */

#endif 	/* __otLine_FWD_DEFINED__ */


#ifndef __otBezierCurve_FWD_DEFINED__
#define __otBezierCurve_FWD_DEFINED__

#ifdef __cplusplus
typedef class otBezierCurve otBezierCurve;
#else
typedef struct otBezierCurve otBezierCurve;
#endif /* __cplusplus */

#endif 	/* __otBezierCurve_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_otcGeometry_0000 */
/* [local] */ 




typedef /* [helpstring][uuid] */  DECLSPEC_UUID("0F1D6D4C-1C98-4e37-B9B7-0D4C6A25E8AE") 
enum otGeometryType
    {	OT_GEOM_NULL	= 0,
	OT_GEOM_POINT	= OT_GEOM_NULL + 1,
	OT_GEOM_LINESTRING	= OT_GEOM_POINT + 1,
	OT_GEOM_LINERING	= OT_GEOM_LINESTRING + 1,
	OT_GEOM_POLYGON	= OT_GEOM_LINERING + 1,
	OT_GEOM_MULTIPOINT	= OT_GEOM_POLYGON + 1,
	OT_GEOM_MULTILINESTRING	= OT_GEOM_MULTIPOINT + 1,
	OT_GEOM_MULTIPOLYGON	= OT_GEOM_MULTILINESTRING + 1,
	OT_GEOM_GEOMETRYCOLLECTION	= OT_GEOM_MULTIPOLYGON + 1,
	OT_GEOM_LINE	= OT_GEOM_GEOMETRYCOLLECTION + 1,
	OT_GEOM_CIRCULARARC	= OT_GEOM_LINE + 1,
	OT_GEOM_ELLIPTICARC	= OT_GEOM_CIRCULARARC + 1,
	OT_GEOM_CIRCLE	= OT_GEOM_ELLIPTICARC + 1,
	OT_GEOM_ELLIPSE	= OT_GEOM_CIRCLE + 1,
	OT_GEOM_BEZIERSPLINE	= OT_GEOM_ELLIPSE + 1,
	OT_GEOM_BEZIERCURVE	= OT_GEOM_BEZIERSPLINE + 1
    } 	otGeometryType;



extern RPC_IF_HANDLE __MIDL_itf_otcGeometry_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_otcGeometry_0000_v0_0_s_ifspec;

#ifndef __IotPointCollection_INTERFACE_DEFINED__
#define __IotPointCollection_INTERFACE_DEFINED__

/* interface IotPointCollection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotPointCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("67644AA5-0A8D-4ff2-B2E4-51290FB139AA")
    IotPointCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointNum( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Point( 
            /* [in] */ LONG index,
            /* [retval][out] */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPoint( 
            /* [in] */ IotPoint *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InsertPoint( 
            /* [in] */ LONG index,
            /* [in] */ IotPoint *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReplacePoint( 
            /* [in] */ LONG index,
            /* [in] */ IotPoint *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemovePoint( 
            /* [in] */ LONG index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotPointCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotPointCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotPointCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotPointCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointNum )( 
            IotPointCollection * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Point )( 
            IotPointCollection * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPoint )( 
            IotPointCollection * This,
            /* [in] */ IotPoint *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InsertPoint )( 
            IotPointCollection * This,
            /* [in] */ LONG index,
            /* [in] */ IotPoint *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReplacePoint )( 
            IotPointCollection * This,
            /* [in] */ LONG index,
            /* [in] */ IotPoint *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemovePoint )( 
            IotPointCollection * This,
            /* [in] */ LONG index);
        
        END_INTERFACE
    } IotPointCollectionVtbl;

    interface IotPointCollection
    {
        CONST_VTBL struct IotPointCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotPointCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotPointCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotPointCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotPointCollection_get_PointNum(This,pVal)	\
    (This)->lpVtbl -> get_PointNum(This,pVal)

#define IotPointCollection_get_Point(This,index,pVal)	\
    (This)->lpVtbl -> get_Point(This,index,pVal)

#define IotPointCollection_AddPoint(This,point)	\
    (This)->lpVtbl -> AddPoint(This,point)

#define IotPointCollection_InsertPoint(This,index,point)	\
    (This)->lpVtbl -> InsertPoint(This,index,point)

#define IotPointCollection_ReplacePoint(This,index,point)	\
    (This)->lpVtbl -> ReplacePoint(This,index,point)

#define IotPointCollection_RemovePoint(This,index)	\
    (This)->lpVtbl -> RemovePoint(This,index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPointCollection_get_PointNum_Proxy( 
    IotPointCollection * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotPointCollection_get_PointNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPointCollection_get_Point_Proxy( 
    IotPointCollection * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IotPoint **pVal);


void __RPC_STUB IotPointCollection_get_Point_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotPointCollection_AddPoint_Proxy( 
    IotPointCollection * This,
    /* [in] */ IotPoint *point);


void __RPC_STUB IotPointCollection_AddPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotPointCollection_InsertPoint_Proxy( 
    IotPointCollection * This,
    /* [in] */ LONG index,
    /* [in] */ IotPoint *point);


void __RPC_STUB IotPointCollection_InsertPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotPointCollection_ReplacePoint_Proxy( 
    IotPointCollection * This,
    /* [in] */ LONG index,
    /* [in] */ IotPoint *point);


void __RPC_STUB IotPointCollection_ReplacePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotPointCollection_RemovePoint_Proxy( 
    IotPointCollection * This,
    /* [in] */ LONG index);


void __RPC_STUB IotPointCollection_RemovePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotPointCollection_INTERFACE_DEFINED__ */


#ifndef __IotTransform_INTERFACE_DEFINED__
#define __IotTransform_INTERFACE_DEFINED__

/* interface IotTransform */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B227DF87-4B92-43f9-966E-9A4BD620DB8C")
    IotTransform : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ DOUBLE dx,
            /* [in] */ DOUBLE dy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ IotPoint *Origin,
            /* [in] */ DOUBLE dx,
            /* [in] */ DOUBLE dy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ IotPoint *Origin,
            /* [in] */ DOUBLE angle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotTransform * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotTransform * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotTransform * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IotTransform * This,
            /* [in] */ DOUBLE dx,
            /* [in] */ DOUBLE dy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Scale )( 
            IotTransform * This,
            /* [in] */ IotPoint *Origin,
            /* [in] */ DOUBLE dx,
            /* [in] */ DOUBLE dy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IotTransform * This,
            /* [in] */ IotPoint *Origin,
            /* [in] */ DOUBLE angle);
        
        END_INTERFACE
    } IotTransformVtbl;

    interface IotTransform
    {
        CONST_VTBL struct IotTransformVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotTransform_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotTransform_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotTransform_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotTransform_Move(This,dx,dy)	\
    (This)->lpVtbl -> Move(This,dx,dy)

#define IotTransform_Scale(This,Origin,dx,dy)	\
    (This)->lpVtbl -> Scale(This,Origin,dx,dy)

#define IotTransform_Rotate(This,Origin,angle)	\
    (This)->lpVtbl -> Rotate(This,Origin,angle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotTransform_Move_Proxy( 
    IotTransform * This,
    /* [in] */ DOUBLE dx,
    /* [in] */ DOUBLE dy);


void __RPC_STUB IotTransform_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotTransform_Scale_Proxy( 
    IotTransform * This,
    /* [in] */ IotPoint *Origin,
    /* [in] */ DOUBLE dx,
    /* [in] */ DOUBLE dy);


void __RPC_STUB IotTransform_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotTransform_Rotate_Proxy( 
    IotTransform * This,
    /* [in] */ IotPoint *Origin,
    /* [in] */ DOUBLE angle);


void __RPC_STUB IotTransform_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotTransform_INTERFACE_DEFINED__ */


#ifndef __IotGeometryCollection_INTERFACE_DEFINED__
#define __IotGeometryCollection_INTERFACE_DEFINED__

/* interface IotGeometryCollection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotGeometryCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F89C4CC5-548A-478c-B094-BE80FCB1C5CF")
    IotGeometryCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GeometryCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetGeometry( 
            /* [in] */ LONG index,
            /* [retval][out] */ IotGeometry **retGeometry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddGeometry( 
            /* [in] */ IotGeometry *geometry) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotGeometryCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotGeometryCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotGeometryCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotGeometryCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryCount )( 
            IotGeometryCollection * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetGeometry )( 
            IotGeometryCollection * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotGeometry **retGeometry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddGeometry )( 
            IotGeometryCollection * This,
            /* [in] */ IotGeometry *geometry);
        
        END_INTERFACE
    } IotGeometryCollectionVtbl;

    interface IotGeometryCollection
    {
        CONST_VTBL struct IotGeometryCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotGeometryCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotGeometryCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotGeometryCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotGeometryCollection_get_GeometryCount(This,pVal)	\
    (This)->lpVtbl -> get_GeometryCount(This,pVal)

#define IotGeometryCollection_GetGeometry(This,index,retGeometry)	\
    (This)->lpVtbl -> GetGeometry(This,index,retGeometry)

#define IotGeometryCollection_AddGeometry(This,geometry)	\
    (This)->lpVtbl -> AddGeometry(This,geometry)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGeometryCollection_get_GeometryCount_Proxy( 
    IotGeometryCollection * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotGeometryCollection_get_GeometryCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometryCollection_GetGeometry_Proxy( 
    IotGeometryCollection * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IotGeometry **retGeometry);


void __RPC_STUB IotGeometryCollection_GetGeometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometryCollection_AddGeometry_Proxy( 
    IotGeometryCollection * This,
    /* [in] */ IotGeometry *geometry);


void __RPC_STUB IotGeometryCollection_AddGeometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotGeometryCollection_INTERFACE_DEFINED__ */


#ifndef __IotGeometry_INTERFACE_DEFINED__
#define __IotGeometry_INTERFACE_DEFINED__

/* interface IotGeometry */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotGeometry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("031E731D-C0A9-44b0-ADC6-A2779B1D9D60")
    IotGeometry : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GeometryType( 
            /* [retval][out] */ otGeometryType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEnvelope( 
            /* [retval][out] */ IotEnvelope **envelope) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasZ( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HasZ( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasM( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HasM( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsEmpty( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetEmpty( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IotGeometry **geometry) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsValid( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Disjoint( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Touches( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Intersects( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Crosses( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Within( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Overlaps( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Equals( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Covers( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvexHull( 
            /* [retval][out] */ IotGeometry **retGeometry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Buffer( 
            /* [in] */ DOUBLE distance,
            /* [retval][out] */ IotGeometry **retGeometry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Intersection( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ IotGeometry **retGeometry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Union( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ IotGeometry **retGeometry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Difference( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ IotGeometry **retGeometry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SymDifference( 
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ IotGeometry **retGeometry) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotGeometryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotGeometry * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotGeometry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotGeometry * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryType )( 
            IotGeometry * This,
            /* [retval][out] */ otGeometryType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointCount )( 
            IotGeometry * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEnvelope )( 
            IotGeometry * This,
            /* [retval][out] */ IotEnvelope **envelope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasZ )( 
            IotGeometry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasZ )( 
            IotGeometry * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasM )( 
            IotGeometry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasM )( 
            IotGeometry * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            IotGeometry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            IotGeometry * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IotGeometry * This,
            /* [retval][out] */ IotGeometry **geometry);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsValid )( 
            IotGeometry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Disjoint )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Touches )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Intersects )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Crosses )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Within )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Overlaps )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Equals )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Covers )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvexHull )( 
            IotGeometry * This,
            /* [retval][out] */ IotGeometry **retGeometry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Buffer )( 
            IotGeometry * This,
            /* [in] */ DOUBLE distance,
            /* [retval][out] */ IotGeometry **retGeometry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Intersection )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ IotGeometry **retGeometry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Union )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ IotGeometry **retGeometry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Difference )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ IotGeometry **retGeometry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SymDifference )( 
            IotGeometry * This,
            /* [in] */ IotGeometry *other,
            /* [retval][out] */ IotGeometry **retGeometry);
        
        END_INTERFACE
    } IotGeometryVtbl;

    interface IotGeometry
    {
        CONST_VTBL struct IotGeometryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotGeometry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotGeometry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotGeometry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotGeometry_get_GeometryType(This,pVal)	\
    (This)->lpVtbl -> get_GeometryType(This,pVal)

#define IotGeometry_get_PointCount(This,pVal)	\
    (This)->lpVtbl -> get_PointCount(This,pVal)

#define IotGeometry_GetEnvelope(This,envelope)	\
    (This)->lpVtbl -> GetEnvelope(This,envelope)

#define IotGeometry_get_HasZ(This,pVal)	\
    (This)->lpVtbl -> get_HasZ(This,pVal)

#define IotGeometry_put_HasZ(This,newVal)	\
    (This)->lpVtbl -> put_HasZ(This,newVal)

#define IotGeometry_get_HasM(This,pVal)	\
    (This)->lpVtbl -> get_HasM(This,pVal)

#define IotGeometry_put_HasM(This,newVal)	\
    (This)->lpVtbl -> put_HasM(This,newVal)

#define IotGeometry_get_IsEmpty(This,pVal)	\
    (This)->lpVtbl -> get_IsEmpty(This,pVal)

#define IotGeometry_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define IotGeometry_Clone(This,geometry)	\
    (This)->lpVtbl -> Clone(This,geometry)

#define IotGeometry_get_IsValid(This,pVal)	\
    (This)->lpVtbl -> get_IsValid(This,pVal)

#define IotGeometry_Disjoint(This,other,bRet)	\
    (This)->lpVtbl -> Disjoint(This,other,bRet)

#define IotGeometry_Touches(This,other,bRet)	\
    (This)->lpVtbl -> Touches(This,other,bRet)

#define IotGeometry_Intersects(This,other,bRet)	\
    (This)->lpVtbl -> Intersects(This,other,bRet)

#define IotGeometry_Crosses(This,other,bRet)	\
    (This)->lpVtbl -> Crosses(This,other,bRet)

#define IotGeometry_Within(This,other,bRet)	\
    (This)->lpVtbl -> Within(This,other,bRet)

#define IotGeometry_Overlaps(This,other,bRet)	\
    (This)->lpVtbl -> Overlaps(This,other,bRet)

#define IotGeometry_Equals(This,other,bRet)	\
    (This)->lpVtbl -> Equals(This,other,bRet)

#define IotGeometry_Covers(This,other,bRet)	\
    (This)->lpVtbl -> Covers(This,other,bRet)

#define IotGeometry_ConvexHull(This,retGeometry)	\
    (This)->lpVtbl -> ConvexHull(This,retGeometry)

#define IotGeometry_Buffer(This,distance,retGeometry)	\
    (This)->lpVtbl -> Buffer(This,distance,retGeometry)

#define IotGeometry_Intersection(This,other,retGeometry)	\
    (This)->lpVtbl -> Intersection(This,other,retGeometry)

#define IotGeometry_Union(This,other,retGeometry)	\
    (This)->lpVtbl -> Union(This,other,retGeometry)

#define IotGeometry_Difference(This,other,retGeometry)	\
    (This)->lpVtbl -> Difference(This,other,retGeometry)

#define IotGeometry_SymDifference(This,other,retGeometry)	\
    (This)->lpVtbl -> SymDifference(This,other,retGeometry)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGeometry_get_GeometryType_Proxy( 
    IotGeometry * This,
    /* [retval][out] */ otGeometryType *pVal);


void __RPC_STUB IotGeometry_get_GeometryType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGeometry_get_PointCount_Proxy( 
    IotGeometry * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotGeometry_get_PointCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_GetEnvelope_Proxy( 
    IotGeometry * This,
    /* [retval][out] */ IotEnvelope **envelope);


void __RPC_STUB IotGeometry_GetEnvelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGeometry_get_HasZ_Proxy( 
    IotGeometry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotGeometry_get_HasZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotGeometry_put_HasZ_Proxy( 
    IotGeometry * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IotGeometry_put_HasZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGeometry_get_HasM_Proxy( 
    IotGeometry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotGeometry_get_HasM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotGeometry_put_HasM_Proxy( 
    IotGeometry * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IotGeometry_put_HasM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGeometry_get_IsEmpty_Proxy( 
    IotGeometry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotGeometry_get_IsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_SetEmpty_Proxy( 
    IotGeometry * This);


void __RPC_STUB IotGeometry_SetEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Clone_Proxy( 
    IotGeometry * This,
    /* [retval][out] */ IotGeometry **geometry);


void __RPC_STUB IotGeometry_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGeometry_get_IsValid_Proxy( 
    IotGeometry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotGeometry_get_IsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Disjoint_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotGeometry_Disjoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Touches_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotGeometry_Touches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Intersects_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotGeometry_Intersects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Crosses_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotGeometry_Crosses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Within_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotGeometry_Within_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Overlaps_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotGeometry_Overlaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Equals_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotGeometry_Equals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Covers_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotGeometry_Covers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_ConvexHull_Proxy( 
    IotGeometry * This,
    /* [retval][out] */ IotGeometry **retGeometry);


void __RPC_STUB IotGeometry_ConvexHull_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Buffer_Proxy( 
    IotGeometry * This,
    /* [in] */ DOUBLE distance,
    /* [retval][out] */ IotGeometry **retGeometry);


void __RPC_STUB IotGeometry_Buffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Intersection_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ IotGeometry **retGeometry);


void __RPC_STUB IotGeometry_Intersection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Union_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ IotGeometry **retGeometry);


void __RPC_STUB IotGeometry_Union_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_Difference_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ IotGeometry **retGeometry);


void __RPC_STUB IotGeometry_Difference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeometry_SymDifference_Proxy( 
    IotGeometry * This,
    /* [in] */ IotGeometry *other,
    /* [retval][out] */ IotGeometry **retGeometry);


void __RPC_STUB IotGeometry_SymDifference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotGeometry_INTERFACE_DEFINED__ */


#ifndef __IotEnvelope_INTERFACE_DEFINED__
#define __IotEnvelope_INTERFACE_DEFINED__

/* interface IotEnvelope */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotEnvelope;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D3D17ED8-8141-4B37-931B-AB4D2AA8AD8A")
    IotEnvelope : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinX( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MinX( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinY( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MinY( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxX( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MaxX( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxY( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MaxY( 
            /* [in] */ double newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotEnvelopeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotEnvelope * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotEnvelope * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotEnvelope * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinX )( 
            IotEnvelope * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinX )( 
            IotEnvelope * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinY )( 
            IotEnvelope * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinY )( 
            IotEnvelope * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxX )( 
            IotEnvelope * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxX )( 
            IotEnvelope * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxY )( 
            IotEnvelope * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxY )( 
            IotEnvelope * This,
            /* [in] */ double newVal);
        
        END_INTERFACE
    } IotEnvelopeVtbl;

    interface IotEnvelope
    {
        CONST_VTBL struct IotEnvelopeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotEnvelope_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotEnvelope_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotEnvelope_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotEnvelope_get_MinX(This,pVal)	\
    (This)->lpVtbl -> get_MinX(This,pVal)

#define IotEnvelope_put_MinX(This,newVal)	\
    (This)->lpVtbl -> put_MinX(This,newVal)

#define IotEnvelope_get_MinY(This,pVal)	\
    (This)->lpVtbl -> get_MinY(This,pVal)

#define IotEnvelope_put_MinY(This,newVal)	\
    (This)->lpVtbl -> put_MinY(This,newVal)

#define IotEnvelope_get_MaxX(This,pVal)	\
    (This)->lpVtbl -> get_MaxX(This,pVal)

#define IotEnvelope_put_MaxX(This,newVal)	\
    (This)->lpVtbl -> put_MaxX(This,newVal)

#define IotEnvelope_get_MaxY(This,pVal)	\
    (This)->lpVtbl -> get_MaxY(This,pVal)

#define IotEnvelope_put_MaxY(This,newVal)	\
    (This)->lpVtbl -> put_MaxY(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotEnvelope_get_MinX_Proxy( 
    IotEnvelope * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IotEnvelope_get_MinX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotEnvelope_put_MinX_Proxy( 
    IotEnvelope * This,
    /* [in] */ double newVal);


void __RPC_STUB IotEnvelope_put_MinX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotEnvelope_get_MinY_Proxy( 
    IotEnvelope * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IotEnvelope_get_MinY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotEnvelope_put_MinY_Proxy( 
    IotEnvelope * This,
    /* [in] */ double newVal);


void __RPC_STUB IotEnvelope_put_MinY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotEnvelope_get_MaxX_Proxy( 
    IotEnvelope * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IotEnvelope_get_MaxX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotEnvelope_put_MaxX_Proxy( 
    IotEnvelope * This,
    /* [in] */ double newVal);


void __RPC_STUB IotEnvelope_put_MaxX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotEnvelope_get_MaxY_Proxy( 
    IotEnvelope * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IotEnvelope_get_MaxY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotEnvelope_put_MaxY_Proxy( 
    IotEnvelope * This,
    /* [in] */ double newVal);


void __RPC_STUB IotEnvelope_put_MaxY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotEnvelope_INTERFACE_DEFINED__ */


#ifndef __IotPoint_INTERFACE_DEFINED__
#define __IotPoint_INTERFACE_DEFINED__

/* interface IotPoint */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotPoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E345D296-34C1-42EA-95DC-8441FE42F9CB")
    IotPoint : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Z( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Z( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_M( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_M( 
            /* [in] */ DOUBLE newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotPoint * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotPoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotPoint * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IotPoint * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IotPoint * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IotPoint * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IotPoint * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Z )( 
            IotPoint * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Z )( 
            IotPoint * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_M )( 
            IotPoint * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_M )( 
            IotPoint * This,
            /* [in] */ DOUBLE newVal);
        
        END_INTERFACE
    } IotPointVtbl;

    interface IotPoint
    {
        CONST_VTBL struct IotPointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotPoint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotPoint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotPoint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotPoint_get_X(This,pVal)	\
    (This)->lpVtbl -> get_X(This,pVal)

#define IotPoint_put_X(This,newVal)	\
    (This)->lpVtbl -> put_X(This,newVal)

#define IotPoint_get_Y(This,pVal)	\
    (This)->lpVtbl -> get_Y(This,pVal)

#define IotPoint_put_Y(This,newVal)	\
    (This)->lpVtbl -> put_Y(This,newVal)

#define IotPoint_get_Z(This,pVal)	\
    (This)->lpVtbl -> get_Z(This,pVal)

#define IotPoint_put_Z(This,newVal)	\
    (This)->lpVtbl -> put_Z(This,newVal)

#define IotPoint_get_M(This,pVal)	\
    (This)->lpVtbl -> get_M(This,pVal)

#define IotPoint_put_M(This,newVal)	\
    (This)->lpVtbl -> put_M(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPoint_get_X_Proxy( 
    IotPoint * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotPoint_get_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPoint_put_X_Proxy( 
    IotPoint * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotPoint_put_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPoint_get_Y_Proxy( 
    IotPoint * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotPoint_get_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPoint_put_Y_Proxy( 
    IotPoint * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotPoint_put_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPoint_get_Z_Proxy( 
    IotPoint * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotPoint_get_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPoint_put_Z_Proxy( 
    IotPoint * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotPoint_put_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPoint_get_M_Proxy( 
    IotPoint * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotPoint_get_M_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPoint_put_M_Proxy( 
    IotPoint * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotPoint_put_M_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotPoint_INTERFACE_DEFINED__ */


#ifndef __IotSegment_INTERFACE_DEFINED__
#define __IotSegment_INTERFACE_DEFINED__

/* interface IotSegment */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("42899086-1BE7-4870-8485-6DDFC114D6A7")
    IotSegment : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FromPoint( 
            /* [retval][out] */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FromPoint( 
            /* [in] */ IotPoint *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ToPoint( 
            /* [retval][out] */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ToPoint( 
            /* [in] */ IotPoint *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSegment * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FromPoint )( 
            IotSegment * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FromPoint )( 
            IotSegment * This,
            /* [in] */ IotPoint *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ToPoint )( 
            IotSegment * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ToPoint )( 
            IotSegment * This,
            /* [in] */ IotPoint *newVal);
        
        END_INTERFACE
    } IotSegmentVtbl;

    interface IotSegment
    {
        CONST_VTBL struct IotSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSegment_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSegment_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSegment_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSegment_get_FromPoint(This,pVal)	\
    (This)->lpVtbl -> get_FromPoint(This,pVal)

#define IotSegment_put_FromPoint(This,newVal)	\
    (This)->lpVtbl -> put_FromPoint(This,newVal)

#define IotSegment_get_ToPoint(This,pVal)	\
    (This)->lpVtbl -> get_ToPoint(This,pVal)

#define IotSegment_put_ToPoint(This,newVal)	\
    (This)->lpVtbl -> put_ToPoint(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSegment_get_FromPoint_Proxy( 
    IotSegment * This,
    /* [retval][out] */ IotPoint **pVal);


void __RPC_STUB IotSegment_get_FromPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSegment_put_FromPoint_Proxy( 
    IotSegment * This,
    /* [in] */ IotPoint *newVal);


void __RPC_STUB IotSegment_put_FromPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSegment_get_ToPoint_Proxy( 
    IotSegment * This,
    /* [retval][out] */ IotPoint **pVal);


void __RPC_STUB IotSegment_get_ToPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSegment_put_ToPoint_Proxy( 
    IotSegment * This,
    /* [in] */ IotPoint *newVal);


void __RPC_STUB IotSegment_put_ToPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSegment_INTERFACE_DEFINED__ */


#ifndef __IotSegmentCollection_INTERFACE_DEFINED__
#define __IotSegmentCollection_INTERFACE_DEFINED__

/* interface IotSegmentCollection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSegmentCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C3DF7859-3624-4846-861F-015DBC0B98F9")
    IotSegmentCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddSegment( 
            /* [in] */ IotSegment *segment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSegment( 
            /* [in] */ LONG index,
            /* [retval][out] */ IotSegment **ret) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSegmentCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSegmentCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSegmentCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSegmentCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentCount )( 
            IotSegmentCollection * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSegment )( 
            IotSegmentCollection * This,
            /* [in] */ IotSegment *segment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegment )( 
            IotSegmentCollection * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotSegment **ret);
        
        END_INTERFACE
    } IotSegmentCollectionVtbl;

    interface IotSegmentCollection
    {
        CONST_VTBL struct IotSegmentCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSegmentCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSegmentCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSegmentCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSegmentCollection_get_SegmentCount(This,pVal)	\
    (This)->lpVtbl -> get_SegmentCount(This,pVal)

#define IotSegmentCollection_AddSegment(This,segment)	\
    (This)->lpVtbl -> AddSegment(This,segment)

#define IotSegmentCollection_GetSegment(This,index,ret)	\
    (This)->lpVtbl -> GetSegment(This,index,ret)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSegmentCollection_get_SegmentCount_Proxy( 
    IotSegmentCollection * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotSegmentCollection_get_SegmentCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSegmentCollection_AddSegment_Proxy( 
    IotSegmentCollection * This,
    /* [in] */ IotSegment *segment);


void __RPC_STUB IotSegmentCollection_AddSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotSegmentCollection_GetSegment_Proxy( 
    IotSegmentCollection * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IotSegment **ret);


void __RPC_STUB IotSegmentCollection_GetSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSegmentCollection_INTERFACE_DEFINED__ */


#ifndef __IotLineString_INTERFACE_DEFINED__
#define __IotLineString_INTERFACE_DEFINED__

/* interface IotLineString */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotLineString;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CF2D8ABA-5D6A-4732-B81F-DBCA0C5D25AC")
    IotLineString : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsClosed( 
            /* [retval][out] */ VARIANT_BOOL *bRet) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPoint( 
            /* [retval][out] */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartPoint( 
            /* [in] */ IotPoint *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPoint( 
            /* [retval][out] */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndPoint( 
            /* [in] */ IotPoint *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotLineStringVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotLineString * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotLineString * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotLineString * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsClosed )( 
            IotLineString * This,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IotLineString * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPoint )( 
            IotLineString * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartPoint )( 
            IotLineString * This,
            /* [in] */ IotPoint *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPoint )( 
            IotLineString * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndPoint )( 
            IotLineString * This,
            /* [in] */ IotPoint *newVal);
        
        END_INTERFACE
    } IotLineStringVtbl;

    interface IotLineString
    {
        CONST_VTBL struct IotLineStringVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotLineString_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotLineString_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotLineString_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotLineString_IsClosed(This,bRet)	\
    (This)->lpVtbl -> IsClosed(This,bRet)

#define IotLineString_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IotLineString_get_StartPoint(This,pVal)	\
    (This)->lpVtbl -> get_StartPoint(This,pVal)

#define IotLineString_put_StartPoint(This,newVal)	\
    (This)->lpVtbl -> put_StartPoint(This,newVal)

#define IotLineString_get_EndPoint(This,pVal)	\
    (This)->lpVtbl -> get_EndPoint(This,pVal)

#define IotLineString_put_EndPoint(This,newVal)	\
    (This)->lpVtbl -> put_EndPoint(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotLineString_IsClosed_Proxy( 
    IotLineString * This,
    /* [retval][out] */ VARIANT_BOOL *bRet);


void __RPC_STUB IotLineString_IsClosed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLineString_get_Length_Proxy( 
    IotLineString * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotLineString_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLineString_get_StartPoint_Proxy( 
    IotLineString * This,
    /* [retval][out] */ IotPoint **pVal);


void __RPC_STUB IotLineString_get_StartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLineString_put_StartPoint_Proxy( 
    IotLineString * This,
    /* [in] */ IotPoint *newVal);


void __RPC_STUB IotLineString_put_StartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLineString_get_EndPoint_Proxy( 
    IotLineString * This,
    /* [retval][out] */ IotPoint **pVal);


void __RPC_STUB IotLineString_get_EndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLineString_put_EndPoint_Proxy( 
    IotLineString * This,
    /* [in] */ IotPoint *newVal);


void __RPC_STUB IotLineString_put_EndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotLineString_INTERFACE_DEFINED__ */


#ifndef __IotLineRing_INTERFACE_DEFINED__
#define __IotLineRing_INTERFACE_DEFINED__

/* interface IotLineRing */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotLineRing;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("37AAECC0-6AF7-45A9-8222-60E8404F45D4")
    IotLineRing : public IotLineString
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotLineRingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotLineRing * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotLineRing * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotLineRing * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsClosed )( 
            IotLineRing * This,
            /* [retval][out] */ VARIANT_BOOL *bRet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IotLineRing * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPoint )( 
            IotLineRing * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartPoint )( 
            IotLineRing * This,
            /* [in] */ IotPoint *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPoint )( 
            IotLineRing * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndPoint )( 
            IotLineRing * This,
            /* [in] */ IotPoint *newVal);
        
        END_INTERFACE
    } IotLineRingVtbl;

    interface IotLineRing
    {
        CONST_VTBL struct IotLineRingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotLineRing_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotLineRing_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotLineRing_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotLineRing_IsClosed(This,bRet)	\
    (This)->lpVtbl -> IsClosed(This,bRet)

#define IotLineRing_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IotLineRing_get_StartPoint(This,pVal)	\
    (This)->lpVtbl -> get_StartPoint(This,pVal)

#define IotLineRing_put_StartPoint(This,newVal)	\
    (This)->lpVtbl -> put_StartPoint(This,newVal)

#define IotLineRing_get_EndPoint(This,pVal)	\
    (This)->lpVtbl -> get_EndPoint(This,pVal)

#define IotLineRing_put_EndPoint(This,newVal)	\
    (This)->lpVtbl -> put_EndPoint(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotLineRing_INTERFACE_DEFINED__ */


#ifndef __IotMultiPoint_INTERFACE_DEFINED__
#define __IotMultiPoint_INTERFACE_DEFINED__

/* interface IotMultiPoint */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotMultiPoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8928D749-81A2-48A1-8071-5D4739988A1B")
    IotMultiPoint : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotMultiPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotMultiPoint * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotMultiPoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotMultiPoint * This);
        
        END_INTERFACE
    } IotMultiPointVtbl;

    interface IotMultiPoint
    {
        CONST_VTBL struct IotMultiPointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotMultiPoint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotMultiPoint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotMultiPoint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotMultiPoint_INTERFACE_DEFINED__ */


#ifndef __IotMultiLineString_INTERFACE_DEFINED__
#define __IotMultiLineString_INTERFACE_DEFINED__

/* interface IotMultiLineString */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotMultiLineString;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4665385A-34D0-4E4D-8626-1F018A99548B")
    IotMultiLineString : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotMultiLineStringVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotMultiLineString * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotMultiLineString * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotMultiLineString * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IotMultiLineString * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        END_INTERFACE
    } IotMultiLineStringVtbl;

    interface IotMultiLineString
    {
        CONST_VTBL struct IotMultiLineStringVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotMultiLineString_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotMultiLineString_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotMultiLineString_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotMultiLineString_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMultiLineString_get_Length_Proxy( 
    IotMultiLineString * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMultiLineString_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotMultiLineString_INTERFACE_DEFINED__ */


#ifndef __IotPolygon_INTERFACE_DEFINED__
#define __IotPolygon_INTERFACE_DEFINED__

/* interface IotPolygon */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotPolygon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D3A18F5B-90F8-45E4-8EF7-2EC948DCA74F")
    IotPolygon : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InteriorRingCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Area( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExteriorRing( 
            /* [retval][out] */ IotLineRing **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ExteriorRing( 
            /* [in] */ IotLineRing *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InteriorRing( 
            /* [in] */ LONG index,
            /* [retval][out] */ IotLineRing **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_InteriorRing( 
            /* [in] */ LONG index,
            /* [in] */ IotLineRing *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddInteriorRing( 
            /* [in] */ IotLineRing *ring) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotPolygonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotPolygon * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotPolygon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotPolygon * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InteriorRingCount )( 
            IotPolygon * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            IotPolygon * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExteriorRing )( 
            IotPolygon * This,
            /* [retval][out] */ IotLineRing **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExteriorRing )( 
            IotPolygon * This,
            /* [in] */ IotLineRing *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InteriorRing )( 
            IotPolygon * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotLineRing **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InteriorRing )( 
            IotPolygon * This,
            /* [in] */ LONG index,
            /* [in] */ IotLineRing *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddInteriorRing )( 
            IotPolygon * This,
            /* [in] */ IotLineRing *ring);
        
        END_INTERFACE
    } IotPolygonVtbl;

    interface IotPolygon
    {
        CONST_VTBL struct IotPolygonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotPolygon_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotPolygon_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotPolygon_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotPolygon_get_InteriorRingCount(This,pVal)	\
    (This)->lpVtbl -> get_InteriorRingCount(This,pVal)

#define IotPolygon_get_Area(This,pVal)	\
    (This)->lpVtbl -> get_Area(This,pVal)

#define IotPolygon_get_ExteriorRing(This,pVal)	\
    (This)->lpVtbl -> get_ExteriorRing(This,pVal)

#define IotPolygon_put_ExteriorRing(This,newVal)	\
    (This)->lpVtbl -> put_ExteriorRing(This,newVal)

#define IotPolygon_get_InteriorRing(This,index,pVal)	\
    (This)->lpVtbl -> get_InteriorRing(This,index,pVal)

#define IotPolygon_put_InteriorRing(This,index,newVal)	\
    (This)->lpVtbl -> put_InteriorRing(This,index,newVal)

#define IotPolygon_AddInteriorRing(This,ring)	\
    (This)->lpVtbl -> AddInteriorRing(This,ring)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPolygon_get_InteriorRingCount_Proxy( 
    IotPolygon * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotPolygon_get_InteriorRingCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPolygon_get_Area_Proxy( 
    IotPolygon * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotPolygon_get_Area_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPolygon_get_ExteriorRing_Proxy( 
    IotPolygon * This,
    /* [retval][out] */ IotLineRing **pVal);


void __RPC_STUB IotPolygon_get_ExteriorRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPolygon_put_ExteriorRing_Proxy( 
    IotPolygon * This,
    /* [in] */ IotLineRing *newVal);


void __RPC_STUB IotPolygon_put_ExteriorRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPolygon_get_InteriorRing_Proxy( 
    IotPolygon * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IotLineRing **pVal);


void __RPC_STUB IotPolygon_get_InteriorRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPolygon_put_InteriorRing_Proxy( 
    IotPolygon * This,
    /* [in] */ LONG index,
    /* [in] */ IotLineRing *newVal);


void __RPC_STUB IotPolygon_put_InteriorRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotPolygon_AddInteriorRing_Proxy( 
    IotPolygon * This,
    /* [in] */ IotLineRing *ring);


void __RPC_STUB IotPolygon_AddInteriorRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotPolygon_INTERFACE_DEFINED__ */


#ifndef __IotMultiPolygon_INTERFACE_DEFINED__
#define __IotMultiPolygon_INTERFACE_DEFINED__

/* interface IotMultiPolygon */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotMultiPolygon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B57958AB-D268-44BA-8E9B-2BEE1C8C2CD9")
    IotMultiPolygon : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Area( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotMultiPolygonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotMultiPolygon * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotMultiPolygon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotMultiPolygon * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            IotMultiPolygon * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        END_INTERFACE
    } IotMultiPolygonVtbl;

    interface IotMultiPolygon
    {
        CONST_VTBL struct IotMultiPolygonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotMultiPolygon_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotMultiPolygon_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotMultiPolygon_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotMultiPolygon_get_Area(This,pVal)	\
    (This)->lpVtbl -> get_Area(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMultiPolygon_get_Area_Proxy( 
    IotMultiPolygon * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotMultiPolygon_get_Area_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotMultiPolygon_INTERFACE_DEFINED__ */


#ifndef __IotGeoConvert_INTERFACE_DEFINED__
#define __IotGeoConvert_INTERFACE_DEFINED__

/* interface IotGeoConvert */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotGeoConvert;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3FD948E8-3CBF-448A-85F7-A1AFAF204CB5")
    IotGeoConvert : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertGeo( 
            /* [in] */ LONG p,
            /* [in] */ VARIANT_BOOL bown,
            /* [retval][out] */ IotGeometry **retGeo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertIGeo( 
            /* [in] */ IotGeometry *geometry,
            /* [retval][out] */ LONG *ret) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotGeoConvertVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotGeoConvert * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotGeoConvert * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotGeoConvert * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertGeo )( 
            IotGeoConvert * This,
            /* [in] */ LONG p,
            /* [in] */ VARIANT_BOOL bown,
            /* [retval][out] */ IotGeometry **retGeo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertIGeo )( 
            IotGeoConvert * This,
            /* [in] */ IotGeometry *geometry,
            /* [retval][out] */ LONG *ret);
        
        END_INTERFACE
    } IotGeoConvertVtbl;

    interface IotGeoConvert
    {
        CONST_VTBL struct IotGeoConvertVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotGeoConvert_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotGeoConvert_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotGeoConvert_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotGeoConvert_ConvertGeo(This,p,bown,retGeo)	\
    (This)->lpVtbl -> ConvertGeo(This,p,bown,retGeo)

#define IotGeoConvert_ConvertIGeo(This,geometry,ret)	\
    (This)->lpVtbl -> ConvertIGeo(This,geometry,ret)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeoConvert_ConvertGeo_Proxy( 
    IotGeoConvert * This,
    /* [in] */ LONG p,
    /* [in] */ VARIANT_BOOL bown,
    /* [retval][out] */ IotGeometry **retGeo);


void __RPC_STUB IotGeoConvert_ConvertGeo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGeoConvert_ConvertIGeo_Proxy( 
    IotGeoConvert * This,
    /* [in] */ IotGeometry *geometry,
    /* [retval][out] */ LONG *ret);


void __RPC_STUB IotGeoConvert_ConvertIGeo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotGeoConvert_INTERFACE_DEFINED__ */


#ifndef __IotCircle_INTERFACE_DEFINED__
#define __IotCircle_INTERFACE_DEFINED__

/* interface IotCircle */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotCircle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("216DAD59-1C93-45B9-8E37-4F0B049AD3AB")
    IotCircle : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CenterPoint( 
            /* [retval][out] */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CenterPoint( 
            /* [in] */ IotPoint *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Radius( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Radius( 
            /* [in] */ DOUBLE newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotCircleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotCircle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotCircle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotCircle * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CenterPoint )( 
            IotCircle * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CenterPoint )( 
            IotCircle * This,
            /* [in] */ IotPoint *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Radius )( 
            IotCircle * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Radius )( 
            IotCircle * This,
            /* [in] */ DOUBLE newVal);
        
        END_INTERFACE
    } IotCircleVtbl;

    interface IotCircle
    {
        CONST_VTBL struct IotCircleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotCircle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotCircle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotCircle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotCircle_get_CenterPoint(This,pVal)	\
    (This)->lpVtbl -> get_CenterPoint(This,pVal)

#define IotCircle_put_CenterPoint(This,newVal)	\
    (This)->lpVtbl -> put_CenterPoint(This,newVal)

#define IotCircle_get_Radius(This,pVal)	\
    (This)->lpVtbl -> get_Radius(This,pVal)

#define IotCircle_put_Radius(This,newVal)	\
    (This)->lpVtbl -> put_Radius(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotCircle_get_CenterPoint_Proxy( 
    IotCircle * This,
    /* [retval][out] */ IotPoint **pVal);


void __RPC_STUB IotCircle_get_CenterPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotCircle_put_CenterPoint_Proxy( 
    IotCircle * This,
    /* [in] */ IotPoint *newVal);


void __RPC_STUB IotCircle_put_CenterPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotCircle_get_Radius_Proxy( 
    IotCircle * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotCircle_get_Radius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotCircle_put_Radius_Proxy( 
    IotCircle * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotCircle_put_Radius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotCircle_INTERFACE_DEFINED__ */


#ifndef __IotEllipse_INTERFACE_DEFINED__
#define __IotEllipse_INTERFACE_DEFINED__

/* interface IotEllipse */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotEllipse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F0790DE-9A26-4196-8B2C-2D8A9D206868")
    IotEllipse : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CenterPoint( 
            /* [retval][out] */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CenterPoint( 
            /* [in] */ IotPoint *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAxes( 
            /* [out][in] */ DOUBLE *semiMajor,
            /* [out][in] */ DOUBLE *semiMinor) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAxes( 
            /* [in] */ DOUBLE semiMajor,
            /* [in] */ DOUBLE semiMinor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotEllipseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotEllipse * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotEllipse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotEllipse * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CenterPoint )( 
            IotEllipse * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CenterPoint )( 
            IotEllipse * This,
            /* [in] */ IotPoint *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAxes )( 
            IotEllipse * This,
            /* [out][in] */ DOUBLE *semiMajor,
            /* [out][in] */ DOUBLE *semiMinor);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetAxes )( 
            IotEllipse * This,
            /* [in] */ DOUBLE semiMajor,
            /* [in] */ DOUBLE semiMinor);
        
        END_INTERFACE
    } IotEllipseVtbl;

    interface IotEllipse
    {
        CONST_VTBL struct IotEllipseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotEllipse_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotEllipse_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotEllipse_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotEllipse_get_CenterPoint(This,pVal)	\
    (This)->lpVtbl -> get_CenterPoint(This,pVal)

#define IotEllipse_put_CenterPoint(This,newVal)	\
    (This)->lpVtbl -> put_CenterPoint(This,newVal)

#define IotEllipse_GetAxes(This,semiMajor,semiMinor)	\
    (This)->lpVtbl -> GetAxes(This,semiMajor,semiMinor)

#define IotEllipse_SetAxes(This,semiMajor,semiMinor)	\
    (This)->lpVtbl -> SetAxes(This,semiMajor,semiMinor)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotEllipse_get_CenterPoint_Proxy( 
    IotEllipse * This,
    /* [retval][out] */ IotPoint **pVal);


void __RPC_STUB IotEllipse_get_CenterPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotEllipse_put_CenterPoint_Proxy( 
    IotEllipse * This,
    /* [in] */ IotPoint *newVal);


void __RPC_STUB IotEllipse_put_CenterPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotEllipse_GetAxes_Proxy( 
    IotEllipse * This,
    /* [out][in] */ DOUBLE *semiMajor,
    /* [out][in] */ DOUBLE *semiMinor);


void __RPC_STUB IotEllipse_GetAxes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotEllipse_SetAxes_Proxy( 
    IotEllipse * This,
    /* [in] */ DOUBLE semiMajor,
    /* [in] */ DOUBLE semiMinor);


void __RPC_STUB IotEllipse_SetAxes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotEllipse_INTERFACE_DEFINED__ */


#ifndef __IotBezierSpline_INTERFACE_DEFINED__
#define __IotBezierSpline_INTERFACE_DEFINED__

/* interface IotBezierSpline */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotBezierSpline;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FD6436F2-D47E-4DDB-B24C-F7F37D0865D2")
    IotBezierSpline : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LONG numPoints,
            /* [in] */ IotPoint **points) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotBezierSplineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotBezierSpline * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotBezierSpline * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotBezierSpline * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IotBezierSpline * This,
            /* [in] */ LONG numPoints,
            /* [in] */ IotPoint **points);
        
        END_INTERFACE
    } IotBezierSplineVtbl;

    interface IotBezierSpline
    {
        CONST_VTBL struct IotBezierSplineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotBezierSpline_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotBezierSpline_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotBezierSpline_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotBezierSpline_Create(This,numPoints,points)	\
    (This)->lpVtbl -> Create(This,numPoints,points)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotBezierSpline_Create_Proxy( 
    IotBezierSpline * This,
    /* [in] */ LONG numPoints,
    /* [in] */ IotPoint **points);


void __RPC_STUB IotBezierSpline_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotBezierSpline_INTERFACE_DEFINED__ */


#ifndef __IotLine_INTERFACE_DEFINED__
#define __IotLine_INTERFACE_DEFINED__

/* interface IotLine */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotLine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("716150DE-5EC3-454C-B6FB-DC019105E7DE")
    IotLine : public IotSegment
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotLineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotLine * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotLine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotLine * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FromPoint )( 
            IotLine * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FromPoint )( 
            IotLine * This,
            /* [in] */ IotPoint *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ToPoint )( 
            IotLine * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ToPoint )( 
            IotLine * This,
            /* [in] */ IotPoint *newVal);
        
        END_INTERFACE
    } IotLineVtbl;

    interface IotLine
    {
        CONST_VTBL struct IotLineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotLine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotLine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotLine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotLine_get_FromPoint(This,pVal)	\
    (This)->lpVtbl -> get_FromPoint(This,pVal)

#define IotLine_put_FromPoint(This,newVal)	\
    (This)->lpVtbl -> put_FromPoint(This,newVal)

#define IotLine_get_ToPoint(This,pVal)	\
    (This)->lpVtbl -> get_ToPoint(This,pVal)

#define IotLine_put_ToPoint(This,newVal)	\
    (This)->lpVtbl -> put_ToPoint(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotLine_INTERFACE_DEFINED__ */


#ifndef __IotBezierCurve_INTERFACE_DEFINED__
#define __IotBezierCurve_INTERFACE_DEFINED__

/* interface IotBezierCurve */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotBezierCurve;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("719A5E2E-1432-427C-9DC9-9379BDB88576")
    IotBezierCurve : public IotSegment
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FirstCtrlPoint( 
            /* [retval][out] */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FirstCtrlPoint( 
            /* [in] */ IotPoint *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SecondCtrlPoint( 
            /* [retval][out] */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SecondCtrlPoint( 
            /* [in] */ IotPoint *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotBezierCurveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotBezierCurve * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotBezierCurve * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotBezierCurve * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FromPoint )( 
            IotBezierCurve * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FromPoint )( 
            IotBezierCurve * This,
            /* [in] */ IotPoint *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ToPoint )( 
            IotBezierCurve * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ToPoint )( 
            IotBezierCurve * This,
            /* [in] */ IotPoint *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FirstCtrlPoint )( 
            IotBezierCurve * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FirstCtrlPoint )( 
            IotBezierCurve * This,
            /* [in] */ IotPoint *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SecondCtrlPoint )( 
            IotBezierCurve * This,
            /* [retval][out] */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SecondCtrlPoint )( 
            IotBezierCurve * This,
            /* [in] */ IotPoint *newVal);
        
        END_INTERFACE
    } IotBezierCurveVtbl;

    interface IotBezierCurve
    {
        CONST_VTBL struct IotBezierCurveVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotBezierCurve_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotBezierCurve_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotBezierCurve_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotBezierCurve_get_FromPoint(This,pVal)	\
    (This)->lpVtbl -> get_FromPoint(This,pVal)

#define IotBezierCurve_put_FromPoint(This,newVal)	\
    (This)->lpVtbl -> put_FromPoint(This,newVal)

#define IotBezierCurve_get_ToPoint(This,pVal)	\
    (This)->lpVtbl -> get_ToPoint(This,pVal)

#define IotBezierCurve_put_ToPoint(This,newVal)	\
    (This)->lpVtbl -> put_ToPoint(This,newVal)


#define IotBezierCurve_get_FirstCtrlPoint(This,pVal)	\
    (This)->lpVtbl -> get_FirstCtrlPoint(This,pVal)

#define IotBezierCurve_put_FirstCtrlPoint(This,newVal)	\
    (This)->lpVtbl -> put_FirstCtrlPoint(This,newVal)

#define IotBezierCurve_get_SecondCtrlPoint(This,pVal)	\
    (This)->lpVtbl -> get_SecondCtrlPoint(This,pVal)

#define IotBezierCurve_put_SecondCtrlPoint(This,newVal)	\
    (This)->lpVtbl -> put_SecondCtrlPoint(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotBezierCurve_get_FirstCtrlPoint_Proxy( 
    IotBezierCurve * This,
    /* [retval][out] */ IotPoint **pVal);


void __RPC_STUB IotBezierCurve_get_FirstCtrlPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotBezierCurve_put_FirstCtrlPoint_Proxy( 
    IotBezierCurve * This,
    /* [in] */ IotPoint *newVal);


void __RPC_STUB IotBezierCurve_put_FirstCtrlPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotBezierCurve_get_SecondCtrlPoint_Proxy( 
    IotBezierCurve * This,
    /* [retval][out] */ IotPoint **pVal);


void __RPC_STUB IotBezierCurve_get_SecondCtrlPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotBezierCurve_put_SecondCtrlPoint_Proxy( 
    IotBezierCurve * This,
    /* [in] */ IotPoint *newVal);


void __RPC_STUB IotBezierCurve_put_SecondCtrlPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotBezierCurve_INTERFACE_DEFINED__ */



#ifndef __otcGeometry_LIBRARY_DEFINED__
#define __otcGeometry_LIBRARY_DEFINED__

/* library otcGeometry */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_otcGeometry;

EXTERN_C const CLSID CLSID_otEnvelope;

#ifdef __cplusplus

class DECLSPEC_UUID("344A66CC-BDD9-49B8-8945-B0F72002D97B")
otEnvelope;
#endif

EXTERN_C const CLSID CLSID_otPoint;

#ifdef __cplusplus

class DECLSPEC_UUID("6A5D4FE7-1732-4F67-8605-6411760B55FE")
otPoint;
#endif

EXTERN_C const CLSID CLSID_otLineString;

#ifdef __cplusplus

class DECLSPEC_UUID("06C1E7EF-EC63-41B0-A6FC-CF3185CAFC39")
otLineString;
#endif

EXTERN_C const CLSID CLSID_otLineRing;

#ifdef __cplusplus

class DECLSPEC_UUID("DBE796BC-841C-4ABB-A83B-2523CEEC3046")
otLineRing;
#endif

EXTERN_C const CLSID CLSID_otMultiPoint;

#ifdef __cplusplus

class DECLSPEC_UUID("9527C418-8F57-403D-B23F-F4435BFBFBB2")
otMultiPoint;
#endif

EXTERN_C const CLSID CLSID_otMultiLineString;

#ifdef __cplusplus

class DECLSPEC_UUID("692FC1C7-8899-427C-A8BA-64461D26A30B")
otMultiLineString;
#endif

EXTERN_C const CLSID CLSID_otPolygon;

#ifdef __cplusplus

class DECLSPEC_UUID("4BDBD639-E914-4B4E-BC38-F596F7CC3CF1")
otPolygon;
#endif

EXTERN_C const CLSID CLSID_otMultiPolygon;

#ifdef __cplusplus

class DECLSPEC_UUID("48F1AC95-23D5-4395-AD1D-0A887405C283")
otMultiPolygon;
#endif

EXTERN_C const CLSID CLSID_otGeoConvert;

#ifdef __cplusplus

class DECLSPEC_UUID("3F4B78D0-10E9-4222-88FE-9B077CF3DDAC")
otGeoConvert;
#endif

EXTERN_C const CLSID CLSID_otCircle;

#ifdef __cplusplus

class DECLSPEC_UUID("D98CFB7C-5B03-4314-85D9-1CB2A43D03E1")
otCircle;
#endif

EXTERN_C const CLSID CLSID_otEllipse;

#ifdef __cplusplus

class DECLSPEC_UUID("10428073-895D-4F57-8575-B8846D057B98")
otEllipse;
#endif

EXTERN_C const CLSID CLSID_otBezierSpline;

#ifdef __cplusplus

class DECLSPEC_UUID("D7C52CAA-E37E-4C9D-9838-8BE1C8312D2A")
otBezierSpline;
#endif

EXTERN_C const CLSID CLSID_otLine;

#ifdef __cplusplus

class DECLSPEC_UUID("45A0C519-99EB-4D89-8721-7A3C2415AE7B")
otLine;
#endif

EXTERN_C const CLSID CLSID_otBezierCurve;

#ifdef __cplusplus

class DECLSPEC_UUID("CF0D8787-FAD6-48A4-A1DC-2DCAF8E27087")
otBezierCurve;
#endif
#endif /* __otcGeometry_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


