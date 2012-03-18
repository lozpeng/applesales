

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sat Mar 17 22:14:06 2012
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __otcCarto_h__
#define __otcCarto_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IotGeoPageLayout_FWD_DEFINED__
#define __IotGeoPageLayout_FWD_DEFINED__
typedef interface IotGeoPageLayout IotGeoPageLayout;
#endif 	/* __IotGeoPageLayout_FWD_DEFINED__ */


#ifndef __IotFeatureRender_FWD_DEFINED__
#define __IotFeatureRender_FWD_DEFINED__
typedef interface IotFeatureRender IotFeatureRender;
#endif 	/* __IotFeatureRender_FWD_DEFINED__ */


#ifndef __IotSimpleRender_FWD_DEFINED__
#define __IotSimpleRender_FWD_DEFINED__
typedef interface IotSimpleRender IotSimpleRender;
#endif 	/* __IotSimpleRender_FWD_DEFINED__ */


#ifndef __IElement_FWD_DEFINED__
#define __IElement_FWD_DEFINED__
typedef interface IElement IElement;
#endif 	/* __IElement_FWD_DEFINED__ */


#ifndef __IotFrameElementBase_FWD_DEFINED__
#define __IotFrameElementBase_FWD_DEFINED__
typedef interface IotFrameElementBase IotFrameElementBase;
#endif 	/* __IotFrameElementBase_FWD_DEFINED__ */


#ifndef __IotMarkerElement_FWD_DEFINED__
#define __IotMarkerElement_FWD_DEFINED__
typedef interface IotMarkerElement IotMarkerElement;
#endif 	/* __IotMarkerElement_FWD_DEFINED__ */


#ifndef __IotPolylineElement_FWD_DEFINED__
#define __IotPolylineElement_FWD_DEFINED__
typedef interface IotPolylineElement IotPolylineElement;
#endif 	/* __IotPolylineElement_FWD_DEFINED__ */


#ifndef __IotPolygonElement_FWD_DEFINED__
#define __IotPolygonElement_FWD_DEFINED__
typedef interface IotPolygonElement IotPolygonElement;
#endif 	/* __IotPolygonElement_FWD_DEFINED__ */


#ifndef __IotRectElement_FWD_DEFINED__
#define __IotRectElement_FWD_DEFINED__
typedef interface IotRectElement IotRectElement;
#endif 	/* __IotRectElement_FWD_DEFINED__ */


#ifndef __IotCircleElement_FWD_DEFINED__
#define __IotCircleElement_FWD_DEFINED__
typedef interface IotCircleElement IotCircleElement;
#endif 	/* __IotCircleElement_FWD_DEFINED__ */


#ifndef __IotEllipseElement_FWD_DEFINED__
#define __IotEllipseElement_FWD_DEFINED__
typedef interface IotEllipseElement IotEllipseElement;
#endif 	/* __IotEllipseElement_FWD_DEFINED__ */


#ifndef __IotBezierCurveElement_FWD_DEFINED__
#define __IotBezierCurveElement_FWD_DEFINED__
typedef interface IotBezierCurveElement IotBezierCurveElement;
#endif 	/* __IotBezierCurveElement_FWD_DEFINED__ */


#ifndef __IotPictureElement_FWD_DEFINED__
#define __IotPictureElement_FWD_DEFINED__
typedef interface IotPictureElement IotPictureElement;
#endif 	/* __IotPictureElement_FWD_DEFINED__ */


#ifndef __IotTextElement_FWD_DEFINED__
#define __IotTextElement_FWD_DEFINED__
typedef interface IotTextElement IotTextElement;
#endif 	/* __IotTextElement_FWD_DEFINED__ */


#ifndef __IotCalloutTextElement_FWD_DEFINED__
#define __IotCalloutTextElement_FWD_DEFINED__
typedef interface IotCalloutTextElement IotCalloutTextElement;
#endif 	/* __IotCalloutTextElement_FWD_DEFINED__ */


#ifndef __IotPage_FWD_DEFINED__
#define __IotPage_FWD_DEFINED__
typedef interface IotPage IotPage;
#endif 	/* __IotPage_FWD_DEFINED__ */


#ifndef __IotMapFrame_FWD_DEFINED__
#define __IotMapFrame_FWD_DEFINED__
typedef interface IotMapFrame IotMapFrame;
#endif 	/* __IotMapFrame_FWD_DEFINED__ */


#ifndef __IotLayer_FWD_DEFINED__
#define __IotLayer_FWD_DEFINED__
typedef interface IotLayer IotLayer;
#endif 	/* __IotLayer_FWD_DEFINED__ */


#ifndef __IotRasterLayer_FWD_DEFINED__
#define __IotRasterLayer_FWD_DEFINED__
typedef interface IotRasterLayer IotRasterLayer;
#endif 	/* __IotRasterLayer_FWD_DEFINED__ */


#ifndef __IotFeatureLayer_FWD_DEFINED__
#define __IotFeatureLayer_FWD_DEFINED__
typedef interface IotFeatureLayer IotFeatureLayer;
#endif 	/* __IotFeatureLayer_FWD_DEFINED__ */


#ifndef __IotGraphicLayer_FWD_DEFINED__
#define __IotGraphicLayer_FWD_DEFINED__
typedef interface IotGraphicLayer IotGraphicLayer;
#endif 	/* __IotGraphicLayer_FWD_DEFINED__ */


#ifndef __IGeoMap_FWD_DEFINED__
#define __IGeoMap_FWD_DEFINED__
typedef interface IGeoMap IGeoMap;
#endif 	/* __IGeoMap_FWD_DEFINED__ */


#ifndef ___IGeoMapEvents_FWD_DEFINED__
#define ___IGeoMapEvents_FWD_DEFINED__
typedef interface _IGeoMapEvents _IGeoMapEvents;
#endif 	/* ___IGeoMapEvents_FWD_DEFINED__ */


#ifndef __GeoMap_FWD_DEFINED__
#define __GeoMap_FWD_DEFINED__

#ifdef __cplusplus
typedef class GeoMap GeoMap;
#else
typedef struct GeoMap GeoMap;
#endif /* __cplusplus */

#endif 	/* __GeoMap_FWD_DEFINED__ */


#ifndef __otFeatureLayer_FWD_DEFINED__
#define __otFeatureLayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class otFeatureLayer otFeatureLayer;
#else
typedef struct otFeatureLayer otFeatureLayer;
#endif /* __cplusplus */

#endif 	/* __otFeatureLayer_FWD_DEFINED__ */


#ifndef __otGraphicLayer_FWD_DEFINED__
#define __otGraphicLayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class otGraphicLayer otGraphicLayer;
#else
typedef struct otGraphicLayer otGraphicLayer;
#endif /* __cplusplus */

#endif 	/* __otGraphicLayer_FWD_DEFINED__ */


#ifndef __otMarkerElement_FWD_DEFINED__
#define __otMarkerElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otMarkerElement otMarkerElement;
#else
typedef struct otMarkerElement otMarkerElement;
#endif /* __cplusplus */

#endif 	/* __otMarkerElement_FWD_DEFINED__ */


#ifndef __otPolylineElement_FWD_DEFINED__
#define __otPolylineElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otPolylineElement otPolylineElement;
#else
typedef struct otPolylineElement otPolylineElement;
#endif /* __cplusplus */

#endif 	/* __otPolylineElement_FWD_DEFINED__ */


#ifndef __otPolygonElement_FWD_DEFINED__
#define __otPolygonElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otPolygonElement otPolygonElement;
#else
typedef struct otPolygonElement otPolygonElement;
#endif /* __cplusplus */

#endif 	/* __otPolygonElement_FWD_DEFINED__ */


#ifndef __otRectElement_FWD_DEFINED__
#define __otRectElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otRectElement otRectElement;
#else
typedef struct otRectElement otRectElement;
#endif /* __cplusplus */

#endif 	/* __otRectElement_FWD_DEFINED__ */


#ifndef __otTextElement_FWD_DEFINED__
#define __otTextElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otTextElement otTextElement;
#else
typedef struct otTextElement otTextElement;
#endif /* __cplusplus */

#endif 	/* __otTextElement_FWD_DEFINED__ */


#ifndef __otRasterLayer_FWD_DEFINED__
#define __otRasterLayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class otRasterLayer otRasterLayer;
#else
typedef struct otRasterLayer otRasterLayer;
#endif /* __cplusplus */

#endif 	/* __otRasterLayer_FWD_DEFINED__ */


#ifndef __otCircleElement_FWD_DEFINED__
#define __otCircleElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otCircleElement otCircleElement;
#else
typedef struct otCircleElement otCircleElement;
#endif /* __cplusplus */

#endif 	/* __otCircleElement_FWD_DEFINED__ */


#ifndef __otGeoPageLayout_FWD_DEFINED__
#define __otGeoPageLayout_FWD_DEFINED__

#ifdef __cplusplus
typedef class otGeoPageLayout otGeoPageLayout;
#else
typedef struct otGeoPageLayout otGeoPageLayout;
#endif /* __cplusplus */

#endif 	/* __otGeoPageLayout_FWD_DEFINED__ */


#ifndef __otBezierCurveElement_FWD_DEFINED__
#define __otBezierCurveElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otBezierCurveElement otBezierCurveElement;
#else
typedef struct otBezierCurveElement otBezierCurveElement;
#endif /* __cplusplus */

#endif 	/* __otBezierCurveElement_FWD_DEFINED__ */


#ifndef __otEllipseElement_FWD_DEFINED__
#define __otEllipseElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otEllipseElement otEllipseElement;
#else
typedef struct otEllipseElement otEllipseElement;
#endif /* __cplusplus */

#endif 	/* __otEllipseElement_FWD_DEFINED__ */


#ifndef __otPictureElement_FWD_DEFINED__
#define __otPictureElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otPictureElement otPictureElement;
#else
typedef struct otPictureElement otPictureElement;
#endif /* __cplusplus */

#endif 	/* __otPictureElement_FWD_DEFINED__ */


#ifndef __otCalloutTextElement_FWD_DEFINED__
#define __otCalloutTextElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class otCalloutTextElement otCalloutTextElement;
#else
typedef struct otCalloutTextElement otCalloutTextElement;
#endif /* __cplusplus */

#endif 	/* __otCalloutTextElement_FWD_DEFINED__ */


#ifndef __otSimpleRender_FWD_DEFINED__
#define __otSimpleRender_FWD_DEFINED__

#ifdef __cplusplus
typedef class otSimpleRender otSimpleRender;
#else
typedef struct otSimpleRender otSimpleRender;
#endif /* __cplusplus */

#endif 	/* __otSimpleRender_FWD_DEFINED__ */


#ifndef __otPage_FWD_DEFINED__
#define __otPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class otPage otPage;
#else
typedef struct otPage otPage;
#endif /* __cplusplus */

#endif 	/* __otPage_FWD_DEFINED__ */


#ifndef __otMapFrame_FWD_DEFINED__
#define __otMapFrame_FWD_DEFINED__

#ifdef __cplusplus
typedef class otMapFrame otMapFrame;
#else
typedef struct otMapFrame otMapFrame;
#endif /* __cplusplus */

#endif 	/* __otMapFrame_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_otcCarto_0000 */
/* [local] */ 




typedef /* [helpstring][uuid] */  DECLSPEC_UUID("D3988066-E27E-40f3-B9E6-09344784A441") 
enum otLayerType
    {	OT_Unknown	= 0,
	OT_FeatureLayer	= OT_Unknown + 1,
	OT_RasterLayer	= OT_FeatureLayer + 1,
	OT_TinLayer	= OT_RasterLayer + 1,
	OT_GraphicLayer	= OT_TinLayer + 1
    } 	otLayerType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("4ECACC6D-E0F6-480f-8398-CABCA7C41516") 
enum ElementType
    {	OT_ELEMENT_NONE	= 0x1,
	OT_MAP_FRAME_ELEMENT	= 0x2,
	OT_SIMPLE_POINT_ELEMENT	= 0x11,
	OT_POLYLINE_ELEMENT	= 0x21,
	OT_CURVE_ELEMENT	= 0x22,
	OT_FILL_RECTANGLE_ELEMENT	= 0x41,
	OT_FILL_POLYGON_ELEMENT	= 0x42,
	OT_FILL_CIRCLE_ELEMENT	= 0x43,
	OT_FILL_ELLIPSE_ELEMENT	= 0x44,
	OT_SIMPLE_TEXT_ELEMENT	= 0x81,
	OT_CALLOUT_TEXT_ELEMENT	= 0x82,
	OT_PICTURE_ELEMENT	= 0x201
    } 	ElementType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("90B636E5-B79A-443f-9521-82CD06318061") 
enum otDrawContent
    {	otDrawNone	= 0,
	otDrawGeography	= 0x1,
	otDrawGeoSelection	= 0x2,
	otDrawElement	= 0x4,
	otDrawEdit	= 0x8,
	otdrawTempObj	= 0x10,
	otDrawAll	= 0x1f
    } 	otDrawContent;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("842D741A-DC11-43fd-90B4-9DCD2EC82ABB") 
enum otSelectOption
    {	OT_SELECT_REPLACE	= 0,
	OT_SELECT_ADD	= OT_SELECT_REPLACE + 1,
	OT_SELECT_SUBTRACT	= OT_SELECT_ADD + 1,
	OT_SELECT_INTERSECT	= OT_SELECT_SUBTRACT + 1
    } 	otSelectOption;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2147B361-BE4E-4173-860F-86C7D3DEC0A5") 
enum otFeatureRenderType
    {	OTSIMPLERENDER	= 0,
	OTUNIQUERENDER	= OTSIMPLERENDER + 1,
	OTRANGERENDER	= OTUNIQUERENDER + 1,
	OTDOTDENSITYRENDER	= OTRANGERENDER + 1
    } 	otFeatureRenderType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("AFAF56A9-805A-4a29-B644-22EE4BB1DB47") 
enum otOutputFileType
    {	OT_BMP	= 0,
	OT_JPEG	= OT_BMP + 1,
	OT_TIFF	= OT_JPEG + 1
    } 	otOutputFileType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2435551C-FAE7-4b86-9873-4892752F2117") 
enum RasterEnhanceType
    {	LINESTRETCH	= 1001,
	HISTGRAMNORMAL	= 1002,
	HISTGRAMEQULIZE	= 1003,
	LOGENHANCE	= 1004,
	EXPHANCE	= 1005,
	StANDARDDEV	= 1008
    } 	RasterEnhanceType;



extern RPC_IF_HANDLE __MIDL_itf_otcCarto_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_otcCarto_0000_v0_0_s_ifspec;

#ifndef __IotGeoPageLayout_INTERFACE_DEFINED__
#define __IotGeoPageLayout_INTERFACE_DEFINED__

/* interface IotGeoPageLayout */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotGeoPageLayout;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("20352E96-A989-4153-A4A0-9CA7F91DB52E")
    IotGeoPageLayout : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GraphicLayer( 
            /* [retval][out] */ IotGraphicLayer **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Page( 
            /* [retval][out] */ IotPage **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotGeoPageLayoutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotGeoPageLayout * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotGeoPageLayout * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotGeoPageLayout * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GraphicLayer )( 
            IotGeoPageLayout * This,
            /* [retval][out] */ IotGraphicLayer **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Page )( 
            IotGeoPageLayout * This,
            /* [retval][out] */ IotPage **pVal);
        
        END_INTERFACE
    } IotGeoPageLayoutVtbl;

    interface IotGeoPageLayout
    {
        CONST_VTBL struct IotGeoPageLayoutVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotGeoPageLayout_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotGeoPageLayout_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotGeoPageLayout_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotGeoPageLayout_get_GraphicLayer(This,pVal)	\
    (This)->lpVtbl -> get_GraphicLayer(This,pVal)

#define IotGeoPageLayout_get_Page(This,pVal)	\
    (This)->lpVtbl -> get_Page(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGeoPageLayout_get_GraphicLayer_Proxy( 
    IotGeoPageLayout * This,
    /* [retval][out] */ IotGraphicLayer **pVal);


void __RPC_STUB IotGeoPageLayout_get_GraphicLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGeoPageLayout_get_Page_Proxy( 
    IotGeoPageLayout * This,
    /* [retval][out] */ IotPage **pVal);


void __RPC_STUB IotGeoPageLayout_get_Page_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotGeoPageLayout_INTERFACE_DEFINED__ */



#ifndef __otcCarto_LIBRARY_DEFINED__
#define __otcCarto_LIBRARY_DEFINED__

/* library otcCarto */
/* [helpstring][version][uuid] */ 




EXTERN_C const IID LIBID_otcCarto;

#ifndef __IotFeatureRender_INTERFACE_DEFINED__
#define __IotFeatureRender_INTERFACE_DEFINED__

/* interface IotFeatureRender */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotFeatureRender;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98C98A24-FF62-4599-A003-A6ECE7F78FB8")
    IotFeatureRender : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RenderType( 
            /* [retval][out] */ otFeatureRenderType *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotFeatureRenderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotFeatureRender * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotFeatureRender * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotFeatureRender * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RenderType )( 
            IotFeatureRender * This,
            /* [retval][out] */ otFeatureRenderType *pVal);
        
        END_INTERFACE
    } IotFeatureRenderVtbl;

    interface IotFeatureRender
    {
        CONST_VTBL struct IotFeatureRenderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotFeatureRender_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotFeatureRender_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotFeatureRender_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotFeatureRender_get_RenderType(This,pVal)	\
    (This)->lpVtbl -> get_RenderType(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeatureRender_get_RenderType_Proxy( 
    IotFeatureRender * This,
    /* [retval][out] */ otFeatureRenderType *pVal);


void __RPC_STUB IotFeatureRender_get_RenderType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotFeatureRender_INTERFACE_DEFINED__ */


#ifndef __IotSimpleRender_INTERFACE_DEFINED__
#define __IotSimpleRender_INTERFACE_DEFINED__

/* interface IotSimpleRender */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotSimpleRender;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3BB94E62-A5FA-4D55-98C1-23FA39DA23CD")
    IotSimpleRender : public IotFeatureRender
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Symbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotSimpleRenderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotSimpleRender * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotSimpleRender * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotSimpleRender * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RenderType )( 
            IotSimpleRender * This,
            /* [retval][out] */ otFeatureRenderType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Symbol )( 
            IotSimpleRender * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotSimpleRender * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        END_INTERFACE
    } IotSimpleRenderVtbl;

    interface IotSimpleRender
    {
        CONST_VTBL struct IotSimpleRenderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotSimpleRender_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotSimpleRender_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotSimpleRender_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotSimpleRender_get_RenderType(This,pVal)	\
    (This)->lpVtbl -> get_RenderType(This,pVal)


#define IotSimpleRender_get_Symbol(This,pVal)	\
    (This)->lpVtbl -> get_Symbol(This,pVal)

#define IotSimpleRender_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotSimpleRender_get_Symbol_Proxy( 
    IotSimpleRender * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotSimpleRender_get_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotSimpleRender_put_Symbol_Proxy( 
    IotSimpleRender * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotSimpleRender_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotSimpleRender_INTERFACE_DEFINED__ */


#ifndef __IElement_INTERFACE_DEFINED__
#define __IElement_INTERFACE_DEFINED__

/* interface IElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AEAB375F-2E75-4c81-A0D5-E65EDAD37CD4")
    IElement : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Geometry( 
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Geometry( 
            /* [in] */ /* external definition not present */ IotGeometry *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ ElementType *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        END_INTERFACE
    } IElementVtbl;

    interface IElement
    {
        CONST_VTBL struct IElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IElement_get_Geometry_Proxy( 
    IElement * This,
    /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);


void __RPC_STUB IElement_get_Geometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IElement_put_Geometry_Proxy( 
    IElement * This,
    /* [in] */ /* external definition not present */ IotGeometry *newVal);


void __RPC_STUB IElement_put_Geometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IElement_get_Name_Proxy( 
    IElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IElement_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IElement_put_Name_Proxy( 
    IElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IElement_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IElement_get_Type_Proxy( 
    IElement * This,
    /* [retval][out] */ ElementType *pVal);


void __RPC_STUB IElement_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElement_INTERFACE_DEFINED__ */


#ifndef __IotFrameElementBase_INTERFACE_DEFINED__
#define __IotFrameElementBase_INTERFACE_DEFINED__

/* interface IotFrameElementBase */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotFrameElementBase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D940E6E3-39C2-497f-89A3-3C8E50AF3A05")
    IotFrameElementBase : public IElement
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IotFrameElementBaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotFrameElementBase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotFrameElementBase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotFrameElementBase * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotFrameElementBase * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotFrameElementBase * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotFrameElementBase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotFrameElementBase * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotFrameElementBase * This,
            /* [retval][out] */ ElementType *pVal);
        
        END_INTERFACE
    } IotFrameElementBaseVtbl;

    interface IotFrameElementBase
    {
        CONST_VTBL struct IotFrameElementBaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotFrameElementBase_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotFrameElementBase_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotFrameElementBase_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotFrameElementBase_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotFrameElementBase_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotFrameElementBase_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotFrameElementBase_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotFrameElementBase_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IotFrameElementBase_INTERFACE_DEFINED__ */


#ifndef __IotMarkerElement_INTERFACE_DEFINED__
#define __IotMarkerElement_INTERFACE_DEFINED__

/* interface IotMarkerElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotMarkerElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("93ABBC20-5FAB-4240-841D-64A718F40BE1")
    IotMarkerElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Symbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotMarkerElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotMarkerElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotMarkerElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotMarkerElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotMarkerElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotMarkerElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotMarkerElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotMarkerElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotMarkerElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Symbol )( 
            IotMarkerElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotMarkerElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        END_INTERFACE
    } IotMarkerElementVtbl;

    interface IotMarkerElement
    {
        CONST_VTBL struct IotMarkerElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotMarkerElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotMarkerElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotMarkerElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotMarkerElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotMarkerElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotMarkerElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotMarkerElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotMarkerElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotMarkerElement_get_Symbol(This,pVal)	\
    (This)->lpVtbl -> get_Symbol(This,pVal)

#define IotMarkerElement_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMarkerElement_get_Symbol_Proxy( 
    IotMarkerElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotMarkerElement_get_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMarkerElement_put_Symbol_Proxy( 
    IotMarkerElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotMarkerElement_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotMarkerElement_INTERFACE_DEFINED__ */


#ifndef __IotPolylineElement_INTERFACE_DEFINED__
#define __IotPolylineElement_INTERFACE_DEFINED__

/* interface IotPolylineElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotPolylineElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A22AA436-D71B-415D-8BB1-0217DB45B7E0")
    IotPolylineElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Symbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotPolylineElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotPolylineElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotPolylineElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotPolylineElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotPolylineElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotPolylineElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotPolylineElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotPolylineElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotPolylineElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Symbol )( 
            IotPolylineElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotPolylineElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        END_INTERFACE
    } IotPolylineElementVtbl;

    interface IotPolylineElement
    {
        CONST_VTBL struct IotPolylineElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotPolylineElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotPolylineElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotPolylineElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotPolylineElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotPolylineElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotPolylineElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotPolylineElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotPolylineElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotPolylineElement_get_Symbol(This,pVal)	\
    (This)->lpVtbl -> get_Symbol(This,pVal)

#define IotPolylineElement_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPolylineElement_get_Symbol_Proxy( 
    IotPolylineElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotPolylineElement_get_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPolylineElement_put_Symbol_Proxy( 
    IotPolylineElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotPolylineElement_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotPolylineElement_INTERFACE_DEFINED__ */


#ifndef __IotPolygonElement_INTERFACE_DEFINED__
#define __IotPolygonElement_INTERFACE_DEFINED__

/* interface IotPolygonElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotPolygonElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE4E1D46-6EDE-431A-A727-7B67AD39022B")
    IotPolygonElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Symbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotPolygonElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotPolygonElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotPolygonElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotPolygonElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotPolygonElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotPolygonElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotPolygonElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotPolygonElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotPolygonElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Symbol )( 
            IotPolygonElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotPolygonElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        END_INTERFACE
    } IotPolygonElementVtbl;

    interface IotPolygonElement
    {
        CONST_VTBL struct IotPolygonElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotPolygonElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotPolygonElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotPolygonElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotPolygonElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotPolygonElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotPolygonElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotPolygonElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotPolygonElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotPolygonElement_get_Symbol(This,pVal)	\
    (This)->lpVtbl -> get_Symbol(This,pVal)

#define IotPolygonElement_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPolygonElement_get_Symbol_Proxy( 
    IotPolygonElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotPolygonElement_get_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPolygonElement_put_Symbol_Proxy( 
    IotPolygonElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotPolygonElement_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotPolygonElement_INTERFACE_DEFINED__ */


#ifndef __IotRectElement_INTERFACE_DEFINED__
#define __IotRectElement_INTERFACE_DEFINED__

/* interface IotRectElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotRectElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3E34B214-22B7-4EA8-A1CA-B7BFF5371C04")
    IotRectElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Symbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotRectElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotRectElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotRectElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotRectElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotRectElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotRectElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotRectElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotRectElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotRectElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Symbol )( 
            IotRectElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotRectElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        END_INTERFACE
    } IotRectElementVtbl;

    interface IotRectElement
    {
        CONST_VTBL struct IotRectElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotRectElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotRectElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotRectElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotRectElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotRectElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotRectElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotRectElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotRectElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotRectElement_get_Symbol(This,pVal)	\
    (This)->lpVtbl -> get_Symbol(This,pVal)

#define IotRectElement_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRectElement_get_Symbol_Proxy( 
    IotRectElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotRectElement_get_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotRectElement_put_Symbol_Proxy( 
    IotRectElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotRectElement_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotRectElement_INTERFACE_DEFINED__ */


#ifndef __IotCircleElement_INTERFACE_DEFINED__
#define __IotCircleElement_INTERFACE_DEFINED__

/* interface IotCircleElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotCircleElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D44BFFDF-7ECC-4E13-B044-DC57F8D9778E")
    IotCircleElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Symbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotCircleElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotCircleElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotCircleElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotCircleElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotCircleElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotCircleElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotCircleElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotCircleElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotCircleElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Symbol )( 
            IotCircleElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotCircleElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        END_INTERFACE
    } IotCircleElementVtbl;

    interface IotCircleElement
    {
        CONST_VTBL struct IotCircleElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotCircleElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotCircleElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotCircleElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotCircleElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotCircleElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotCircleElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotCircleElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotCircleElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotCircleElement_get_Symbol(This,pVal)	\
    (This)->lpVtbl -> get_Symbol(This,pVal)

#define IotCircleElement_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotCircleElement_get_Symbol_Proxy( 
    IotCircleElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotCircleElement_get_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotCircleElement_put_Symbol_Proxy( 
    IotCircleElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotCircleElement_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotCircleElement_INTERFACE_DEFINED__ */


#ifndef __IotEllipseElement_INTERFACE_DEFINED__
#define __IotEllipseElement_INTERFACE_DEFINED__

/* interface IotEllipseElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotEllipseElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7ADC815-48C8-458F-BA23-6CD14CF48C19")
    IotEllipseElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Symbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotEllipseElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotEllipseElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotEllipseElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotEllipseElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotEllipseElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotEllipseElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotEllipseElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotEllipseElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotEllipseElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Symbol )( 
            IotEllipseElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotEllipseElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        END_INTERFACE
    } IotEllipseElementVtbl;

    interface IotEllipseElement
    {
        CONST_VTBL struct IotEllipseElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotEllipseElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotEllipseElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotEllipseElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotEllipseElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotEllipseElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotEllipseElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotEllipseElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotEllipseElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotEllipseElement_get_Symbol(This,pVal)	\
    (This)->lpVtbl -> get_Symbol(This,pVal)

#define IotEllipseElement_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotEllipseElement_get_Symbol_Proxy( 
    IotEllipseElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotEllipseElement_get_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotEllipseElement_put_Symbol_Proxy( 
    IotEllipseElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotEllipseElement_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotEllipseElement_INTERFACE_DEFINED__ */


#ifndef __IotBezierCurveElement_INTERFACE_DEFINED__
#define __IotBezierCurveElement_INTERFACE_DEFINED__

/* interface IotBezierCurveElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotBezierCurveElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("146D442A-808A-4C9F-B474-E371E39A9794")
    IotBezierCurveElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Symbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotBezierCurveElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotBezierCurveElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotBezierCurveElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotBezierCurveElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotBezierCurveElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotBezierCurveElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotBezierCurveElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotBezierCurveElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotBezierCurveElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Symbol )( 
            IotBezierCurveElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotBezierCurveElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        END_INTERFACE
    } IotBezierCurveElementVtbl;

    interface IotBezierCurveElement
    {
        CONST_VTBL struct IotBezierCurveElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotBezierCurveElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotBezierCurveElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotBezierCurveElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotBezierCurveElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotBezierCurveElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotBezierCurveElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotBezierCurveElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotBezierCurveElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotBezierCurveElement_get_Symbol(This,pVal)	\
    (This)->lpVtbl -> get_Symbol(This,pVal)

#define IotBezierCurveElement_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotBezierCurveElement_get_Symbol_Proxy( 
    IotBezierCurveElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotBezierCurveElement_get_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotBezierCurveElement_put_Symbol_Proxy( 
    IotBezierCurveElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotBezierCurveElement_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotBezierCurveElement_INTERFACE_DEFINED__ */


#ifndef __IotPictureElement_INTERFACE_DEFINED__
#define __IotPictureElement_INTERFACE_DEFINED__

/* interface IotPictureElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotPictureElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("828574AA-E196-47B6-A3AC-E426D0A97D15")
    IotPictureElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PictureFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PictureFile( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotPictureElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotPictureElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotPictureElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotPictureElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotPictureElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotPictureElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotPictureElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotPictureElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotPictureElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PictureFile )( 
            IotPictureElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PictureFile )( 
            IotPictureElement * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IotPictureElementVtbl;

    interface IotPictureElement
    {
        CONST_VTBL struct IotPictureElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotPictureElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotPictureElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotPictureElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotPictureElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotPictureElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotPictureElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotPictureElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotPictureElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotPictureElement_get_PictureFile(This,pVal)	\
    (This)->lpVtbl -> get_PictureFile(This,pVal)

#define IotPictureElement_put_PictureFile(This,newVal)	\
    (This)->lpVtbl -> put_PictureFile(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPictureElement_get_PictureFile_Proxy( 
    IotPictureElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotPictureElement_get_PictureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotPictureElement_put_PictureFile_Proxy( 
    IotPictureElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotPictureElement_put_PictureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotPictureElement_INTERFACE_DEFINED__ */


#ifndef __IotTextElement_INTERFACE_DEFINED__
#define __IotTextElement_INTERFACE_DEFINED__

/* interface IotTextElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotTextElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ED8B01AF-78F3-41FC-89A3-BBDA308F9D5D")
    IotTextElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Symbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Symbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotTextElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotTextElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotTextElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotTextElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotTextElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotTextElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotTextElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotTextElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotTextElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Symbol )( 
            IotTextElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Symbol )( 
            IotTextElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            IotTextElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            IotTextElement * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IotTextElementVtbl;

    interface IotTextElement
    {
        CONST_VTBL struct IotTextElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotTextElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotTextElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotTextElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotTextElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotTextElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotTextElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotTextElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotTextElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotTextElement_get_Symbol(This,pVal)	\
    (This)->lpVtbl -> get_Symbol(This,pVal)

#define IotTextElement_put_Symbol(This,newVal)	\
    (This)->lpVtbl -> put_Symbol(This,newVal)

#define IotTextElement_get_Text(This,pVal)	\
    (This)->lpVtbl -> get_Text(This,pVal)

#define IotTextElement_put_Text(This,newVal)	\
    (This)->lpVtbl -> put_Text(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotTextElement_get_Symbol_Proxy( 
    IotTextElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotTextElement_get_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotTextElement_put_Symbol_Proxy( 
    IotTextElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotTextElement_put_Symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotTextElement_get_Text_Proxy( 
    IotTextElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotTextElement_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotTextElement_put_Text_Proxy( 
    IotTextElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotTextElement_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotTextElement_INTERFACE_DEFINED__ */


#ifndef __IotCalloutTextElement_INTERFACE_DEFINED__
#define __IotCalloutTextElement_INTERFACE_DEFINED__

/* interface IotCalloutTextElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotCalloutTextElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4E8FA64-ADFD-498E-81D0-F9A52159B60E")
    IotCalloutTextElement : public IElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TextSymbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TextSymbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FillSymbol( 
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FillSymbol( 
            /* [in] */ /* external definition not present */ IotSymbol *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AnchorPoint( 
            /* [retval][out] */ /* external definition not present */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AnchorPoint( 
            /* [in] */ /* external definition not present */ IotPoint *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TextOriginPoint( 
            /* [retval][out] */ /* external definition not present */ IotPoint **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TextOriginPoint( 
            /* [in] */ /* external definition not present */ IotPoint *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotCalloutTextElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotCalloutTextElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotCalloutTextElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotCalloutTextElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotCalloutTextElement * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotCalloutTextElement * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotCalloutTextElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotCalloutTextElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotCalloutTextElement * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TextSymbol )( 
            IotCalloutTextElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TextSymbol )( 
            IotCalloutTextElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillSymbol )( 
            IotCalloutTextElement * This,
            /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillSymbol )( 
            IotCalloutTextElement * This,
            /* [in] */ /* external definition not present */ IotSymbol *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            IotCalloutTextElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            IotCalloutTextElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AnchorPoint )( 
            IotCalloutTextElement * This,
            /* [retval][out] */ /* external definition not present */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AnchorPoint )( 
            IotCalloutTextElement * This,
            /* [in] */ /* external definition not present */ IotPoint *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TextOriginPoint )( 
            IotCalloutTextElement * This,
            /* [retval][out] */ /* external definition not present */ IotPoint **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TextOriginPoint )( 
            IotCalloutTextElement * This,
            /* [in] */ /* external definition not present */ IotPoint *newVal);
        
        END_INTERFACE
    } IotCalloutTextElementVtbl;

    interface IotCalloutTextElement
    {
        CONST_VTBL struct IotCalloutTextElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotCalloutTextElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotCalloutTextElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotCalloutTextElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotCalloutTextElement_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotCalloutTextElement_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotCalloutTextElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotCalloutTextElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotCalloutTextElement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)


#define IotCalloutTextElement_get_TextSymbol(This,pVal)	\
    (This)->lpVtbl -> get_TextSymbol(This,pVal)

#define IotCalloutTextElement_put_TextSymbol(This,newVal)	\
    (This)->lpVtbl -> put_TextSymbol(This,newVal)

#define IotCalloutTextElement_get_FillSymbol(This,pVal)	\
    (This)->lpVtbl -> get_FillSymbol(This,pVal)

#define IotCalloutTextElement_put_FillSymbol(This,newVal)	\
    (This)->lpVtbl -> put_FillSymbol(This,newVal)

#define IotCalloutTextElement_get_Text(This,pVal)	\
    (This)->lpVtbl -> get_Text(This,pVal)

#define IotCalloutTextElement_put_Text(This,newVal)	\
    (This)->lpVtbl -> put_Text(This,newVal)

#define IotCalloutTextElement_get_AnchorPoint(This,pVal)	\
    (This)->lpVtbl -> get_AnchorPoint(This,pVal)

#define IotCalloutTextElement_put_AnchorPoint(This,newVal)	\
    (This)->lpVtbl -> put_AnchorPoint(This,newVal)

#define IotCalloutTextElement_get_TextOriginPoint(This,pVal)	\
    (This)->lpVtbl -> get_TextOriginPoint(This,pVal)

#define IotCalloutTextElement_put_TextOriginPoint(This,newVal)	\
    (This)->lpVtbl -> put_TextOriginPoint(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_get_TextSymbol_Proxy( 
    IotCalloutTextElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotCalloutTextElement_get_TextSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_put_TextSymbol_Proxy( 
    IotCalloutTextElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotCalloutTextElement_put_TextSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_get_FillSymbol_Proxy( 
    IotCalloutTextElement * This,
    /* [retval][out] */ /* external definition not present */ IotSymbol **pVal);


void __RPC_STUB IotCalloutTextElement_get_FillSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_put_FillSymbol_Proxy( 
    IotCalloutTextElement * This,
    /* [in] */ /* external definition not present */ IotSymbol *newVal);


void __RPC_STUB IotCalloutTextElement_put_FillSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_get_Text_Proxy( 
    IotCalloutTextElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotCalloutTextElement_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_put_Text_Proxy( 
    IotCalloutTextElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotCalloutTextElement_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_get_AnchorPoint_Proxy( 
    IotCalloutTextElement * This,
    /* [retval][out] */ /* external definition not present */ IotPoint **pVal);


void __RPC_STUB IotCalloutTextElement_get_AnchorPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_put_AnchorPoint_Proxy( 
    IotCalloutTextElement * This,
    /* [in] */ /* external definition not present */ IotPoint *newVal);


void __RPC_STUB IotCalloutTextElement_put_AnchorPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_get_TextOriginPoint_Proxy( 
    IotCalloutTextElement * This,
    /* [retval][out] */ /* external definition not present */ IotPoint **pVal);


void __RPC_STUB IotCalloutTextElement_get_TextOriginPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotCalloutTextElement_put_TextOriginPoint_Proxy( 
    IotCalloutTextElement * This,
    /* [in] */ /* external definition not present */ IotPoint *newVal);


void __RPC_STUB IotCalloutTextElement_put_TextOriginPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotCalloutTextElement_INTERFACE_DEFINED__ */


#ifndef __IotPage_INTERFACE_DEFINED__
#define __IotPage_INTERFACE_DEFINED__

/* interface IotPage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotPage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6FC775A1-7F40-4B81-92F8-C2B3C3CF3DAC")
    IotPage : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PageEnvelope( 
            /* [retval][out] */ /* external definition not present */ IotEnvelope **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotPage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotPage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotPage * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PageEnvelope )( 
            IotPage * This,
            /* [retval][out] */ /* external definition not present */ IotEnvelope **pVal);
        
        END_INTERFACE
    } IotPageVtbl;

    interface IotPage
    {
        CONST_VTBL struct IotPageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotPage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotPage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotPage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotPage_get_PageEnvelope(This,pVal)	\
    (This)->lpVtbl -> get_PageEnvelope(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotPage_get_PageEnvelope_Proxy( 
    IotPage * This,
    /* [retval][out] */ /* external definition not present */ IotEnvelope **pVal);


void __RPC_STUB IotPage_get_PageEnvelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotPage_INTERFACE_DEFINED__ */


#ifndef __IotMapFrame_INTERFACE_DEFINED__
#define __IotMapFrame_INTERFACE_DEFINED__

/* interface IotMapFrame */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotMapFrame;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3175177D-CFA9-4C82-B789-5EEAF9248931")
    IotMapFrame : public IotFrameElementBase
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Map( 
            /* [retval][out] */ IGeoMap **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Map( 
            /* [in] */ IGeoMap *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ IGeoMap *map,
            /* [in] */ /* external definition not present */ IotEnvelope *envelope) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotMapFrameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotMapFrame * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotMapFrame * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotMapFrame * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IotMapFrame * This,
            /* [retval][out] */ /* external definition not present */ IotGeometry **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            IotMapFrame * This,
            /* [in] */ /* external definition not present */ IotGeometry *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotMapFrame * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotMapFrame * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IotMapFrame * This,
            /* [retval][out] */ ElementType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Map )( 
            IotMapFrame * This,
            /* [retval][out] */ IGeoMap **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Map )( 
            IotMapFrame * This,
            /* [in] */ IGeoMap *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IotMapFrame * This,
            /* [in] */ IGeoMap *map,
            /* [in] */ /* external definition not present */ IotEnvelope *envelope);
        
        END_INTERFACE
    } IotMapFrameVtbl;

    interface IotMapFrame
    {
        CONST_VTBL struct IotMapFrameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotMapFrame_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotMapFrame_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotMapFrame_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotMapFrame_get_Geometry(This,pVal)	\
    (This)->lpVtbl -> get_Geometry(This,pVal)

#define IotMapFrame_put_Geometry(This,newVal)	\
    (This)->lpVtbl -> put_Geometry(This,newVal)

#define IotMapFrame_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotMapFrame_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotMapFrame_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)



#define IotMapFrame_get_Map(This,pVal)	\
    (This)->lpVtbl -> get_Map(This,pVal)

#define IotMapFrame_put_Map(This,newVal)	\
    (This)->lpVtbl -> put_Map(This,newVal)

#define IotMapFrame_Create(This,map,envelope)	\
    (This)->lpVtbl -> Create(This,map,envelope)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotMapFrame_get_Map_Proxy( 
    IotMapFrame * This,
    /* [retval][out] */ IGeoMap **pVal);


void __RPC_STUB IotMapFrame_get_Map_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotMapFrame_put_Map_Proxy( 
    IotMapFrame * This,
    /* [in] */ IGeoMap *newVal);


void __RPC_STUB IotMapFrame_put_Map_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotMapFrame_Create_Proxy( 
    IotMapFrame * This,
    /* [in] */ IGeoMap *map,
    /* [in] */ /* external definition not present */ IotEnvelope *envelope);


void __RPC_STUB IotMapFrame_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotMapFrame_INTERFACE_DEFINED__ */


#ifndef __IotLayer_INTERFACE_DEFINED__
#define __IotLayer_INTERFACE_DEFINED__

/* interface IotLayer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotLayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B7F6D8E-1318-4f33-BBA4-D395AE52D1D0")
    IotLayer : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayerDesciption( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LayerDesciption( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ScaleRangeValid( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ScaleRangeValid( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ScaleRangeMin( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ScaleRangeMin( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ScaleRangeMax( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ScaleRangeMax( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayerType( 
            /* [retval][out] */ otLayerType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DataObject( 
            /* [retval][out] */ /* external definition not present */ IotDataObject **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DataObject( 
            /* [in] */ /* external definition not present */ IotDataObject *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotLayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotLayer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotLayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotLayer * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotLayer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotLayer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayerDesciption )( 
            IotLayer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayerDesciption )( 
            IotLayer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            IotLayer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            IotLayer * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeValid )( 
            IotLayer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeValid )( 
            IotLayer * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeMin )( 
            IotLayer * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeMin )( 
            IotLayer * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeMax )( 
            IotLayer * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeMax )( 
            IotLayer * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayerType )( 
            IotLayer * This,
            /* [retval][out] */ otLayerType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataObject )( 
            IotLayer * This,
            /* [retval][out] */ /* external definition not present */ IotDataObject **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DataObject )( 
            IotLayer * This,
            /* [in] */ /* external definition not present */ IotDataObject *newVal);
        
        END_INTERFACE
    } IotLayerVtbl;

    interface IotLayer
    {
        CONST_VTBL struct IotLayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotLayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotLayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotLayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotLayer_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotLayer_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotLayer_get_LayerDesciption(This,pVal)	\
    (This)->lpVtbl -> get_LayerDesciption(This,pVal)

#define IotLayer_put_LayerDesciption(This,newVal)	\
    (This)->lpVtbl -> put_LayerDesciption(This,newVal)

#define IotLayer_get_Visible(This,pVal)	\
    (This)->lpVtbl -> get_Visible(This,pVal)

#define IotLayer_put_Visible(This,newVal)	\
    (This)->lpVtbl -> put_Visible(This,newVal)

#define IotLayer_get_ScaleRangeValid(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeValid(This,pVal)

#define IotLayer_put_ScaleRangeValid(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeValid(This,newVal)

#define IotLayer_get_ScaleRangeMin(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeMin(This,pVal)

#define IotLayer_put_ScaleRangeMin(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeMin(This,newVal)

#define IotLayer_get_ScaleRangeMax(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeMax(This,pVal)

#define IotLayer_put_ScaleRangeMax(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeMax(This,newVal)

#define IotLayer_get_LayerType(This,pVal)	\
    (This)->lpVtbl -> get_LayerType(This,pVal)

#define IotLayer_get_DataObject(This,pVal)	\
    (This)->lpVtbl -> get_DataObject(This,pVal)

#define IotLayer_put_DataObject(This,newVal)	\
    (This)->lpVtbl -> put_DataObject(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLayer_get_Name_Proxy( 
    IotLayer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotLayer_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLayer_put_Name_Proxy( 
    IotLayer * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotLayer_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLayer_get_LayerDesciption_Proxy( 
    IotLayer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IotLayer_get_LayerDesciption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLayer_put_LayerDesciption_Proxy( 
    IotLayer * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IotLayer_put_LayerDesciption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLayer_get_Visible_Proxy( 
    IotLayer * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotLayer_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLayer_put_Visible_Proxy( 
    IotLayer * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IotLayer_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLayer_get_ScaleRangeValid_Proxy( 
    IotLayer * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IotLayer_get_ScaleRangeValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLayer_put_ScaleRangeValid_Proxy( 
    IotLayer * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IotLayer_put_ScaleRangeValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLayer_get_ScaleRangeMin_Proxy( 
    IotLayer * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotLayer_get_ScaleRangeMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLayer_put_ScaleRangeMin_Proxy( 
    IotLayer * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotLayer_put_ScaleRangeMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLayer_get_ScaleRangeMax_Proxy( 
    IotLayer * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IotLayer_get_ScaleRangeMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLayer_put_ScaleRangeMax_Proxy( 
    IotLayer * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IotLayer_put_ScaleRangeMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLayer_get_LayerType_Proxy( 
    IotLayer * This,
    /* [retval][out] */ otLayerType *pVal);


void __RPC_STUB IotLayer_get_LayerType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotLayer_get_DataObject_Proxy( 
    IotLayer * This,
    /* [retval][out] */ /* external definition not present */ IotDataObject **pVal);


void __RPC_STUB IotLayer_get_DataObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotLayer_put_DataObject_Proxy( 
    IotLayer * This,
    /* [in] */ /* external definition not present */ IotDataObject *newVal);


void __RPC_STUB IotLayer_put_DataObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotLayer_INTERFACE_DEFINED__ */


#ifndef __IotRasterLayer_INTERFACE_DEFINED__
#define __IotRasterLayer_INTERFACE_DEFINED__

/* interface IotRasterLayer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotRasterLayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D8E6C255-17AE-40C6-AE56-04EF940462DA")
    IotRasterLayer : public IotLayer
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TransparentValue( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TransparentValue( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Enhance( 
            /* [in] */ RasterEnhanceType type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBrightAndContrast( 
            /* [in] */ LONG bright,
            /* [in] */ LONG contrast) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotRasterLayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotRasterLayer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotRasterLayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotRasterLayer * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotRasterLayer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotRasterLayer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayerDesciption )( 
            IotRasterLayer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayerDesciption )( 
            IotRasterLayer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            IotRasterLayer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            IotRasterLayer * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeValid )( 
            IotRasterLayer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeValid )( 
            IotRasterLayer * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeMin )( 
            IotRasterLayer * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeMin )( 
            IotRasterLayer * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeMax )( 
            IotRasterLayer * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeMax )( 
            IotRasterLayer * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayerType )( 
            IotRasterLayer * This,
            /* [retval][out] */ otLayerType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataObject )( 
            IotRasterLayer * This,
            /* [retval][out] */ /* external definition not present */ IotDataObject **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DataObject )( 
            IotRasterLayer * This,
            /* [in] */ /* external definition not present */ IotDataObject *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransparentValue )( 
            IotRasterLayer * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransparentValue )( 
            IotRasterLayer * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Enhance )( 
            IotRasterLayer * This,
            /* [in] */ RasterEnhanceType type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetBrightAndContrast )( 
            IotRasterLayer * This,
            /* [in] */ LONG bright,
            /* [in] */ LONG contrast);
        
        END_INTERFACE
    } IotRasterLayerVtbl;

    interface IotRasterLayer
    {
        CONST_VTBL struct IotRasterLayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotRasterLayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotRasterLayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotRasterLayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotRasterLayer_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotRasterLayer_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotRasterLayer_get_LayerDesciption(This,pVal)	\
    (This)->lpVtbl -> get_LayerDesciption(This,pVal)

#define IotRasterLayer_put_LayerDesciption(This,newVal)	\
    (This)->lpVtbl -> put_LayerDesciption(This,newVal)

#define IotRasterLayer_get_Visible(This,pVal)	\
    (This)->lpVtbl -> get_Visible(This,pVal)

#define IotRasterLayer_put_Visible(This,newVal)	\
    (This)->lpVtbl -> put_Visible(This,newVal)

#define IotRasterLayer_get_ScaleRangeValid(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeValid(This,pVal)

#define IotRasterLayer_put_ScaleRangeValid(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeValid(This,newVal)

#define IotRasterLayer_get_ScaleRangeMin(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeMin(This,pVal)

#define IotRasterLayer_put_ScaleRangeMin(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeMin(This,newVal)

#define IotRasterLayer_get_ScaleRangeMax(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeMax(This,pVal)

#define IotRasterLayer_put_ScaleRangeMax(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeMax(This,newVal)

#define IotRasterLayer_get_LayerType(This,pVal)	\
    (This)->lpVtbl -> get_LayerType(This,pVal)

#define IotRasterLayer_get_DataObject(This,pVal)	\
    (This)->lpVtbl -> get_DataObject(This,pVal)

#define IotRasterLayer_put_DataObject(This,newVal)	\
    (This)->lpVtbl -> put_DataObject(This,newVal)


#define IotRasterLayer_get_TransparentValue(This,pVal)	\
    (This)->lpVtbl -> get_TransparentValue(This,pVal)

#define IotRasterLayer_put_TransparentValue(This,newVal)	\
    (This)->lpVtbl -> put_TransparentValue(This,newVal)

#define IotRasterLayer_Enhance(This,type)	\
    (This)->lpVtbl -> Enhance(This,type)

#define IotRasterLayer_SetBrightAndContrast(This,bright,contrast)	\
    (This)->lpVtbl -> SetBrightAndContrast(This,bright,contrast)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotRasterLayer_get_TransparentValue_Proxy( 
    IotRasterLayer * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotRasterLayer_get_TransparentValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotRasterLayer_put_TransparentValue_Proxy( 
    IotRasterLayer * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IotRasterLayer_put_TransparentValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotRasterLayer_Enhance_Proxy( 
    IotRasterLayer * This,
    /* [in] */ RasterEnhanceType type);


void __RPC_STUB IotRasterLayer_Enhance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotRasterLayer_SetBrightAndContrast_Proxy( 
    IotRasterLayer * This,
    /* [in] */ LONG bright,
    /* [in] */ LONG contrast);


void __RPC_STUB IotRasterLayer_SetBrightAndContrast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotRasterLayer_INTERFACE_DEFINED__ */


#ifndef __IotFeatureLayer_INTERFACE_DEFINED__
#define __IotFeatureLayer_INTERFACE_DEFINED__

/* interface IotFeatureLayer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotFeatureLayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B2D9CBB-C4E9-42BF-9331-4919D9758614")
    IotFeatureLayer : public IotLayer
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SelectionSet( 
            /* [retval][out] */ /* external definition not present */ IotSelectionSet **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SelectionSet( 
            /* [in] */ /* external definition not present */ IotSelectionSet *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearSelection( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Select( 
            /* [in] */ /* external definition not present */ IotSimpleQuery *queryFilter,
            /* [in] */ enum otSelectOption option) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Render( 
            /* [retval][out] */ IotFeatureRender **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Render( 
            /* [in] */ IotFeatureRender *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotFeatureLayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotFeatureLayer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotFeatureLayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotFeatureLayer * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotFeatureLayer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotFeatureLayer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayerDesciption )( 
            IotFeatureLayer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayerDesciption )( 
            IotFeatureLayer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            IotFeatureLayer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            IotFeatureLayer * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeValid )( 
            IotFeatureLayer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeValid )( 
            IotFeatureLayer * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeMin )( 
            IotFeatureLayer * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeMin )( 
            IotFeatureLayer * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeMax )( 
            IotFeatureLayer * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeMax )( 
            IotFeatureLayer * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayerType )( 
            IotFeatureLayer * This,
            /* [retval][out] */ otLayerType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataObject )( 
            IotFeatureLayer * This,
            /* [retval][out] */ /* external definition not present */ IotDataObject **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DataObject )( 
            IotFeatureLayer * This,
            /* [in] */ /* external definition not present */ IotDataObject *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectionSet )( 
            IotFeatureLayer * This,
            /* [retval][out] */ /* external definition not present */ IotSelectionSet **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectionSet )( 
            IotFeatureLayer * This,
            /* [in] */ /* external definition not present */ IotSelectionSet *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearSelection )( 
            IotFeatureLayer * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Select )( 
            IotFeatureLayer * This,
            /* [in] */ /* external definition not present */ IotSimpleQuery *queryFilter,
            /* [in] */ enum otSelectOption option);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Render )( 
            IotFeatureLayer * This,
            /* [retval][out] */ IotFeatureRender **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Render )( 
            IotFeatureLayer * This,
            /* [in] */ IotFeatureRender *newVal);
        
        END_INTERFACE
    } IotFeatureLayerVtbl;

    interface IotFeatureLayer
    {
        CONST_VTBL struct IotFeatureLayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotFeatureLayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotFeatureLayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotFeatureLayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotFeatureLayer_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotFeatureLayer_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotFeatureLayer_get_LayerDesciption(This,pVal)	\
    (This)->lpVtbl -> get_LayerDesciption(This,pVal)

#define IotFeatureLayer_put_LayerDesciption(This,newVal)	\
    (This)->lpVtbl -> put_LayerDesciption(This,newVal)

#define IotFeatureLayer_get_Visible(This,pVal)	\
    (This)->lpVtbl -> get_Visible(This,pVal)

#define IotFeatureLayer_put_Visible(This,newVal)	\
    (This)->lpVtbl -> put_Visible(This,newVal)

#define IotFeatureLayer_get_ScaleRangeValid(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeValid(This,pVal)

#define IotFeatureLayer_put_ScaleRangeValid(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeValid(This,newVal)

#define IotFeatureLayer_get_ScaleRangeMin(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeMin(This,pVal)

#define IotFeatureLayer_put_ScaleRangeMin(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeMin(This,newVal)

#define IotFeatureLayer_get_ScaleRangeMax(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeMax(This,pVal)

#define IotFeatureLayer_put_ScaleRangeMax(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeMax(This,newVal)

#define IotFeatureLayer_get_LayerType(This,pVal)	\
    (This)->lpVtbl -> get_LayerType(This,pVal)

#define IotFeatureLayer_get_DataObject(This,pVal)	\
    (This)->lpVtbl -> get_DataObject(This,pVal)

#define IotFeatureLayer_put_DataObject(This,newVal)	\
    (This)->lpVtbl -> put_DataObject(This,newVal)


#define IotFeatureLayer_get_SelectionSet(This,pVal)	\
    (This)->lpVtbl -> get_SelectionSet(This,pVal)

#define IotFeatureLayer_put_SelectionSet(This,newVal)	\
    (This)->lpVtbl -> put_SelectionSet(This,newVal)

#define IotFeatureLayer_ClearSelection(This)	\
    (This)->lpVtbl -> ClearSelection(This)

#define IotFeatureLayer_Select(This,queryFilter,option)	\
    (This)->lpVtbl -> Select(This,queryFilter,option)

#define IotFeatureLayer_get_Render(This,pVal)	\
    (This)->lpVtbl -> get_Render(This,pVal)

#define IotFeatureLayer_put_Render(This,newVal)	\
    (This)->lpVtbl -> put_Render(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeatureLayer_get_SelectionSet_Proxy( 
    IotFeatureLayer * This,
    /* [retval][out] */ /* external definition not present */ IotSelectionSet **pVal);


void __RPC_STUB IotFeatureLayer_get_SelectionSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotFeatureLayer_put_SelectionSet_Proxy( 
    IotFeatureLayer * This,
    /* [in] */ /* external definition not present */ IotSelectionSet *newVal);


void __RPC_STUB IotFeatureLayer_put_SelectionSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotFeatureLayer_ClearSelection_Proxy( 
    IotFeatureLayer * This);


void __RPC_STUB IotFeatureLayer_ClearSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotFeatureLayer_Select_Proxy( 
    IotFeatureLayer * This,
    /* [in] */ /* external definition not present */ IotSimpleQuery *queryFilter,
    /* [in] */ enum otSelectOption option);


void __RPC_STUB IotFeatureLayer_Select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotFeatureLayer_get_Render_Proxy( 
    IotFeatureLayer * This,
    /* [retval][out] */ IotFeatureRender **pVal);


void __RPC_STUB IotFeatureLayer_get_Render_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IotFeatureLayer_put_Render_Proxy( 
    IotFeatureLayer * This,
    /* [in] */ IotFeatureRender *newVal);


void __RPC_STUB IotFeatureLayer_put_Render_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotFeatureLayer_INTERFACE_DEFINED__ */


#ifndef __IotGraphicLayer_INTERFACE_DEFINED__
#define __IotGraphicLayer_INTERFACE_DEFINED__

/* interface IotGraphicLayer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IotGraphicLayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("892F223F-D887-4263-9CCA-2688F298729B")
    IotGraphicLayer : public IotLayer
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddElement( 
            /* [in] */ IElement *element) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetElement( 
            /* [in] */ LONG index,
            /* [retval][out] */ IElement **retElement) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveAllElements( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveElement( 
            /* [in] */ IElement *element) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedElementCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SelectElement( 
            /* [in] */ IElement *element) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsElementSelected( 
            /* [in] */ IElement *element,
            /* [retval][out] */ VARIANT_BOOL *bSelected) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnselectElement( 
            /* [in] */ IElement *element) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSelectedElement( 
            /* [in] */ LONG index,
            /* [retval][out] */ IElement **retElement) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SelectAllElements( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnselectAllElements( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IotGraphicLayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IotGraphicLayer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IotGraphicLayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IotGraphicLayer * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IotGraphicLayer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IotGraphicLayer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayerDesciption )( 
            IotGraphicLayer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayerDesciption )( 
            IotGraphicLayer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            IotGraphicLayer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            IotGraphicLayer * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeValid )( 
            IotGraphicLayer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeValid )( 
            IotGraphicLayer * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeMin )( 
            IotGraphicLayer * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeMin )( 
            IotGraphicLayer * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScaleRangeMax )( 
            IotGraphicLayer * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScaleRangeMax )( 
            IotGraphicLayer * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayerType )( 
            IotGraphicLayer * This,
            /* [retval][out] */ otLayerType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataObject )( 
            IotGraphicLayer * This,
            /* [retval][out] */ /* external definition not present */ IotDataObject **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DataObject )( 
            IotGraphicLayer * This,
            /* [in] */ /* external definition not present */ IotDataObject *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IotGraphicLayer * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddElement )( 
            IotGraphicLayer * This,
            /* [in] */ IElement *element);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetElement )( 
            IotGraphicLayer * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IElement **retElement);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllElements )( 
            IotGraphicLayer * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveElement )( 
            IotGraphicLayer * This,
            /* [in] */ IElement *element);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedElementCount )( 
            IotGraphicLayer * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SelectElement )( 
            IotGraphicLayer * This,
            /* [in] */ IElement *element);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsElementSelected )( 
            IotGraphicLayer * This,
            /* [in] */ IElement *element,
            /* [retval][out] */ VARIANT_BOOL *bSelected);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnselectElement )( 
            IotGraphicLayer * This,
            /* [in] */ IElement *element);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSelectedElement )( 
            IotGraphicLayer * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IElement **retElement);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SelectAllElements )( 
            IotGraphicLayer * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnselectAllElements )( 
            IotGraphicLayer * This);
        
        END_INTERFACE
    } IotGraphicLayerVtbl;

    interface IotGraphicLayer
    {
        CONST_VTBL struct IotGraphicLayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IotGraphicLayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IotGraphicLayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IotGraphicLayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IotGraphicLayer_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IotGraphicLayer_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IotGraphicLayer_get_LayerDesciption(This,pVal)	\
    (This)->lpVtbl -> get_LayerDesciption(This,pVal)

#define IotGraphicLayer_put_LayerDesciption(This,newVal)	\
    (This)->lpVtbl -> put_LayerDesciption(This,newVal)

#define IotGraphicLayer_get_Visible(This,pVal)	\
    (This)->lpVtbl -> get_Visible(This,pVal)

#define IotGraphicLayer_put_Visible(This,newVal)	\
    (This)->lpVtbl -> put_Visible(This,newVal)

#define IotGraphicLayer_get_ScaleRangeValid(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeValid(This,pVal)

#define IotGraphicLayer_put_ScaleRangeValid(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeValid(This,newVal)

#define IotGraphicLayer_get_ScaleRangeMin(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeMin(This,pVal)

#define IotGraphicLayer_put_ScaleRangeMin(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeMin(This,newVal)

#define IotGraphicLayer_get_ScaleRangeMax(This,pVal)	\
    (This)->lpVtbl -> get_ScaleRangeMax(This,pVal)

#define IotGraphicLayer_put_ScaleRangeMax(This,newVal)	\
    (This)->lpVtbl -> put_ScaleRangeMax(This,newVal)

#define IotGraphicLayer_get_LayerType(This,pVal)	\
    (This)->lpVtbl -> get_LayerType(This,pVal)

#define IotGraphicLayer_get_DataObject(This,pVal)	\
    (This)->lpVtbl -> get_DataObject(This,pVal)

#define IotGraphicLayer_put_DataObject(This,newVal)	\
    (This)->lpVtbl -> put_DataObject(This,newVal)


#define IotGraphicLayer_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IotGraphicLayer_AddElement(This,element)	\
    (This)->lpVtbl -> AddElement(This,element)

#define IotGraphicLayer_GetElement(This,index,retElement)	\
    (This)->lpVtbl -> GetElement(This,index,retElement)

#define IotGraphicLayer_RemoveAllElements(This)	\
    (This)->lpVtbl -> RemoveAllElements(This)

#define IotGraphicLayer_RemoveElement(This,element)	\
    (This)->lpVtbl -> RemoveElement(This,element)

#define IotGraphicLayer_get_SelectedElementCount(This,pVal)	\
    (This)->lpVtbl -> get_SelectedElementCount(This,pVal)

#define IotGraphicLayer_SelectElement(This,element)	\
    (This)->lpVtbl -> SelectElement(This,element)

#define IotGraphicLayer_IsElementSelected(This,element,bSelected)	\
    (This)->lpVtbl -> IsElementSelected(This,element,bSelected)

#define IotGraphicLayer_UnselectElement(This,element)	\
    (This)->lpVtbl -> UnselectElement(This,element)

#define IotGraphicLayer_GetSelectedElement(This,index,retElement)	\
    (This)->lpVtbl -> GetSelectedElement(This,index,retElement)

#define IotGraphicLayer_SelectAllElements(This)	\
    (This)->lpVtbl -> SelectAllElements(This)

#define IotGraphicLayer_UnselectAllElements(This)	\
    (This)->lpVtbl -> UnselectAllElements(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_get_Count_Proxy( 
    IotGraphicLayer * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotGraphicLayer_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_AddElement_Proxy( 
    IotGraphicLayer * This,
    /* [in] */ IElement *element);


void __RPC_STUB IotGraphicLayer_AddElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_GetElement_Proxy( 
    IotGraphicLayer * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IElement **retElement);


void __RPC_STUB IotGraphicLayer_GetElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_RemoveAllElements_Proxy( 
    IotGraphicLayer * This);


void __RPC_STUB IotGraphicLayer_RemoveAllElements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_RemoveElement_Proxy( 
    IotGraphicLayer * This,
    /* [in] */ IElement *element);


void __RPC_STUB IotGraphicLayer_RemoveElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_get_SelectedElementCount_Proxy( 
    IotGraphicLayer * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IotGraphicLayer_get_SelectedElementCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_SelectElement_Proxy( 
    IotGraphicLayer * This,
    /* [in] */ IElement *element);


void __RPC_STUB IotGraphicLayer_SelectElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_IsElementSelected_Proxy( 
    IotGraphicLayer * This,
    /* [in] */ IElement *element,
    /* [retval][out] */ VARIANT_BOOL *bSelected);


void __RPC_STUB IotGraphicLayer_IsElementSelected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_UnselectElement_Proxy( 
    IotGraphicLayer * This,
    /* [in] */ IElement *element);


void __RPC_STUB IotGraphicLayer_UnselectElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_GetSelectedElement_Proxy( 
    IotGraphicLayer * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IElement **retElement);


void __RPC_STUB IotGraphicLayer_GetSelectedElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_SelectAllElements_Proxy( 
    IotGraphicLayer * This);


void __RPC_STUB IotGraphicLayer_SelectAllElements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IotGraphicLayer_UnselectAllElements_Proxy( 
    IotGraphicLayer * This);


void __RPC_STUB IotGraphicLayer_UnselectAllElements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IotGraphicLayer_INTERFACE_DEFINED__ */


#ifndef __IGeoMap_INTERFACE_DEFINED__
#define __IGeoMap_INTERFACE_DEFINED__

/* interface IGeoMap */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGeoMap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7BC33468-C328-41E6-8D61-24E46F8BBD7B")
    IGeoMap : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LayerCount( 
            /* [retval][out] */ LONG *Count) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MapUnit( 
            /* [retval][out] */ enum /* external definition not present */ otUnits *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GraphicLayer( 
            /* [retval][out] */ IotGraphicLayer **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddLayer( 
            /* [in] */ IotLayer *layer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLayer( 
            /* [in] */ LONG index,
            /* [retval][out] */ IotLayer **retLayer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveLayers( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteLayer( 
            /* [in] */ LONG index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindLayer( 
            /* [in] */ IotLayer *layer,
            /* [retval][out] */ LONG *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveLayer( 
            /* [in] */ IotLayer *layer,
            /* [in] */ LONG ToIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SpatialReference( 
            /* [retval][out] */ /* external definition not present */ IotSpatialReference **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SpatialReference( 
            /* [in] */ /* external definition not present */ IotSpatialReference *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ZoomActualSize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ZoomFullExtent( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGeoMapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeoMap * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeoMap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeoMap * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGeoMap * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGeoMap * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGeoMap * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGeoMap * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LayerCount )( 
            IGeoMap * This,
            /* [retval][out] */ LONG *Count);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MapUnit )( 
            IGeoMap * This,
            /* [retval][out] */ enum /* external definition not present */ otUnits *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GraphicLayer )( 
            IGeoMap * This,
            /* [retval][out] */ IotGraphicLayer **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IGeoMap * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IGeoMap * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddLayer )( 
            IGeoMap * This,
            /* [in] */ IotLayer *layer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLayer )( 
            IGeoMap * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IotLayer **retLayer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveLayers )( 
            IGeoMap * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteLayer )( 
            IGeoMap * This,
            /* [in] */ LONG index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindLayer )( 
            IGeoMap * This,
            /* [in] */ IotLayer *layer,
            /* [retval][out] */ LONG *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveLayer )( 
            IGeoMap * This,
            /* [in] */ IotLayer *layer,
            /* [in] */ LONG ToIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IGeoMap * This,
            /* [retval][out] */ /* external definition not present */ IotSpatialReference **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SpatialReference )( 
            IGeoMap * This,
            /* [in] */ /* external definition not present */ IotSpatialReference *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ZoomActualSize )( 
            IGeoMap * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ZoomFullExtent )( 
            IGeoMap * This);
        
        END_INTERFACE
    } IGeoMapVtbl;

    interface IGeoMap
    {
        CONST_VTBL struct IGeoMapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeoMap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeoMap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeoMap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeoMap_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGeoMap_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGeoMap_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGeoMap_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IGeoMap_LayerCount(This,Count)	\
    (This)->lpVtbl -> LayerCount(This,Count)

#define IGeoMap_get_MapUnit(This,pVal)	\
    (This)->lpVtbl -> get_MapUnit(This,pVal)

#define IGeoMap_get_GraphicLayer(This,pVal)	\
    (This)->lpVtbl -> get_GraphicLayer(This,pVal)

#define IGeoMap_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IGeoMap_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IGeoMap_AddLayer(This,layer)	\
    (This)->lpVtbl -> AddLayer(This,layer)

#define IGeoMap_GetLayer(This,index,retLayer)	\
    (This)->lpVtbl -> GetLayer(This,index,retLayer)

#define IGeoMap_RemoveLayers(This)	\
    (This)->lpVtbl -> RemoveLayers(This)

#define IGeoMap_DeleteLayer(This,index)	\
    (This)->lpVtbl -> DeleteLayer(This,index)

#define IGeoMap_FindLayer(This,layer,index)	\
    (This)->lpVtbl -> FindLayer(This,layer,index)

#define IGeoMap_MoveLayer(This,layer,ToIndex)	\
    (This)->lpVtbl -> MoveLayer(This,layer,ToIndex)

#define IGeoMap_get_SpatialReference(This,pVal)	\
    (This)->lpVtbl -> get_SpatialReference(This,pVal)

#define IGeoMap_put_SpatialReference(This,newVal)	\
    (This)->lpVtbl -> put_SpatialReference(This,newVal)

#define IGeoMap_ZoomActualSize(This)	\
    (This)->lpVtbl -> ZoomActualSize(This)

#define IGeoMap_ZoomFullExtent(This)	\
    (This)->lpVtbl -> ZoomFullExtent(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGeoMap_LayerCount_Proxy( 
    IGeoMap * This,
    /* [retval][out] */ LONG *Count);


void __RPC_STUB IGeoMap_LayerCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGeoMap_get_MapUnit_Proxy( 
    IGeoMap * This,
    /* [retval][out] */ enum /* external definition not present */ otUnits *pVal);


void __RPC_STUB IGeoMap_get_MapUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGeoMap_get_GraphicLayer_Proxy( 
    IGeoMap * This,
    /* [retval][out] */ IotGraphicLayer **pVal);


void __RPC_STUB IGeoMap_get_GraphicLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGeoMap_get_Name_Proxy( 
    IGeoMap * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IGeoMap_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGeoMap_put_Name_Proxy( 
    IGeoMap * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IGeoMap_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGeoMap_AddLayer_Proxy( 
    IGeoMap * This,
    /* [in] */ IotLayer *layer);


void __RPC_STUB IGeoMap_AddLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGeoMap_GetLayer_Proxy( 
    IGeoMap * This,
    /* [in] */ LONG index,
    /* [retval][out] */ IotLayer **retLayer);


void __RPC_STUB IGeoMap_GetLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGeoMap_RemoveLayers_Proxy( 
    IGeoMap * This);


void __RPC_STUB IGeoMap_RemoveLayers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGeoMap_DeleteLayer_Proxy( 
    IGeoMap * This,
    /* [in] */ LONG index);


void __RPC_STUB IGeoMap_DeleteLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGeoMap_FindLayer_Proxy( 
    IGeoMap * This,
    /* [in] */ IotLayer *layer,
    /* [retval][out] */ LONG *index);


void __RPC_STUB IGeoMap_FindLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGeoMap_MoveLayer_Proxy( 
    IGeoMap * This,
    /* [in] */ IotLayer *layer,
    /* [in] */ LONG ToIndex);


void __RPC_STUB IGeoMap_MoveLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGeoMap_get_SpatialReference_Proxy( 
    IGeoMap * This,
    /* [retval][out] */ /* external definition not present */ IotSpatialReference **pVal);


void __RPC_STUB IGeoMap_get_SpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGeoMap_put_SpatialReference_Proxy( 
    IGeoMap * This,
    /* [in] */ /* external definition not present */ IotSpatialReference *newVal);


void __RPC_STUB IGeoMap_put_SpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGeoMap_ZoomActualSize_Proxy( 
    IGeoMap * This);


void __RPC_STUB IGeoMap_ZoomActualSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGeoMap_ZoomFullExtent_Proxy( 
    IGeoMap * This);


void __RPC_STUB IGeoMap_ZoomFullExtent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGeoMap_INTERFACE_DEFINED__ */


#ifndef ___IGeoMapEvents_DISPINTERFACE_DEFINED__
#define ___IGeoMapEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IGeoMapEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IGeoMapEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A56763EB-DE04-4561-8D4E-1CF5F158FAEA")
    _IGeoMapEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IGeoMapEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IGeoMapEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IGeoMapEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IGeoMapEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IGeoMapEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IGeoMapEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IGeoMapEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IGeoMapEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IGeoMapEventsVtbl;

    interface _IGeoMapEvents
    {
        CONST_VTBL struct _IGeoMapEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IGeoMapEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IGeoMapEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IGeoMapEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IGeoMapEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IGeoMapEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IGeoMapEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IGeoMapEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IGeoMapEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GeoMap;

#ifdef __cplusplus

class DECLSPEC_UUID("91EAA7A2-5758-4B92-A08F-877F1AD469EF")
GeoMap;
#endif

EXTERN_C const CLSID CLSID_otFeatureLayer;

#ifdef __cplusplus

class DECLSPEC_UUID("29FFCCDA-2132-4232-8901-5D4C42DBC0A7")
otFeatureLayer;
#endif

EXTERN_C const CLSID CLSID_otGraphicLayer;

#ifdef __cplusplus

class DECLSPEC_UUID("07C08A06-1859-4E9B-BAA1-90FBD153AD4C")
otGraphicLayer;
#endif

EXTERN_C const CLSID CLSID_otMarkerElement;

#ifdef __cplusplus

class DECLSPEC_UUID("09ADAB83-8667-4764-BAF1-EF1C57927C01")
otMarkerElement;
#endif

EXTERN_C const CLSID CLSID_otPolylineElement;

#ifdef __cplusplus

class DECLSPEC_UUID("7CD1FB96-C0E7-48BF-AFB5-E5B468A8CFC3")
otPolylineElement;
#endif

EXTERN_C const CLSID CLSID_otPolygonElement;

#ifdef __cplusplus

class DECLSPEC_UUID("5B1C2866-BD99-4C6B-ABE1-DAF21B8FBADD")
otPolygonElement;
#endif

EXTERN_C const CLSID CLSID_otRectElement;

#ifdef __cplusplus

class DECLSPEC_UUID("3892BCF3-EF3C-488D-B027-53BAFC084CF3")
otRectElement;
#endif

EXTERN_C const CLSID CLSID_otTextElement;

#ifdef __cplusplus

class DECLSPEC_UUID("4E50DECD-BA9E-4EB0-B392-817679CEFBD4")
otTextElement;
#endif

EXTERN_C const CLSID CLSID_otRasterLayer;

#ifdef __cplusplus

class DECLSPEC_UUID("A1B2ED9C-1A68-45FE-A346-F9DFF9DFB5E2")
otRasterLayer;
#endif

EXTERN_C const CLSID CLSID_otCircleElement;

#ifdef __cplusplus

class DECLSPEC_UUID("5FD0038C-DFC2-4BBF-8B2F-6280D5DBAAB2")
otCircleElement;
#endif

EXTERN_C const CLSID CLSID_otGeoPageLayout;

#ifdef __cplusplus

class DECLSPEC_UUID("58D5B697-2EA1-461A-B6F3-2A0A059DDBFB")
otGeoPageLayout;
#endif

EXTERN_C const CLSID CLSID_otBezierCurveElement;

#ifdef __cplusplus

class DECLSPEC_UUID("BAEFF30B-7A9C-41FC-BE1D-8FE208FDBC44")
otBezierCurveElement;
#endif

EXTERN_C const CLSID CLSID_otEllipseElement;

#ifdef __cplusplus

class DECLSPEC_UUID("7D3AD466-57C8-4991-B57B-FB6359EB1FAD")
otEllipseElement;
#endif

EXTERN_C const CLSID CLSID_otPictureElement;

#ifdef __cplusplus

class DECLSPEC_UUID("90D04AB6-FB73-409D-B38F-5371DF10A3B7")
otPictureElement;
#endif

EXTERN_C const CLSID CLSID_otCalloutTextElement;

#ifdef __cplusplus

class DECLSPEC_UUID("BD5390E6-D1B4-4863-9055-FC5734441BC3")
otCalloutTextElement;
#endif

EXTERN_C const CLSID CLSID_otSimpleRender;

#ifdef __cplusplus

class DECLSPEC_UUID("57138786-BC15-4C16-AFB1-C3870AE9F9D3")
otSimpleRender;
#endif

EXTERN_C const CLSID CLSID_otPage;

#ifdef __cplusplus

class DECLSPEC_UUID("6409EB5F-AA78-4846-8EA2-F8C5863D29D4")
otPage;
#endif

EXTERN_C const CLSID CLSID_otMapFrame;

#ifdef __cplusplus

class DECLSPEC_UUID("2925AA1E-E428-4B3D-B888-04FF1732C342")
otMapFrame;
#endif
#endif /* __otcCarto_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


