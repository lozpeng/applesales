

#ifndef _Map_h
#define _Map_h

#include "IDisplay.h"
#include "LayerArray.h"
//#include "IEditor.h"
//#include "IEagleEyeView.h"
#include "GraphicLayer.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
#include "ISerialization.h"
//#include "AoiManager.h"
//#include "CrossLine.h"
//#include "ElementOperationStack.h"


namespace Carto
{

	/*
	* CMap是地图对象
	*/
	class CARTO_DLL CMap : public SYSTEM::ISerialization
	{
	public:
		CMap();
		virtual ~CMap();

	public:

		/**
		* 获取Display
		* @return IDisplay指针
		*/
		Display::IDisplayPtr GetDisplay();

		/**
		* 设置Display
		* @param pNewDisplay Display指针
		*/
		Display::IDisplayPtr SetDisplay(Display::IDisplayPtr pNewDisplay);

		/**
		* 绘制
		*/
		virtual void Draw(long content);

		/**
		* 绘制后
		*/
		virtual void OnAfterDraw(long content);

		/**
		* 绘制前
		*/
		virtual void OnBeforeDraw(long content);

		/**
		* 序列化
		* @param ar 文档流
		*serializationEx1 只序列化ELEMENT, serializationEx2只序列化ELMENT除外
		*/
		virtual void serialization(SYSTEM::IArchive &ar);
		void serializationEx1(SYSTEM::IArchive &ar);
		void serializationEx2(SYSTEM::IArchive &ar);

		/**
		* 复制
		* @return CMapPtr
		*/
		SYSTEM::CSmartPtr<CMap> Clone();

		/**
		* 设置地图在mapctrl中的序列号
		* @return 
		*/
		void SetID(long id);

		/**
		*  获得地图在mapctrl中的序列号
		* @return 地图视图序号
		*/
		long GetID();

		/**
		* 获得地图视图名称
		* @return 地图视图名称
		*/
		std::string GetName();

		/**
		* 设置地图视图名称
		* @param Name 地图视图名称
		*/
		void SetName(std::string Name);

		/**
		* 获得地图的单位
		* @return 地图的单位
		*/
		SYSTEM::SYS_UNIT_TYPE GetUnit(){return m_unit;};

		/**
		* 创建新的图层并添加到map中
		* @param pDataObject 数据
		* @return 若添加成功为true，否则为false
		*/
		BOOL AddNewLayer(Geodatabase::IGeodataObjectPtr pDataObject);
		/**
		* 为地图视图添加一个图层
		* @return 若添加成功为true，否则为false
		*/
		BOOL AddLayer(ILayerPtr pLayer);

		/**
		* 删除图层
		* @param iIndex 索引
		* @return 若删除成功为true，否则为false
		*/
		BOOL DeleteLayer(int iIndex);

		/**
		* 删除指定图层
		* @param ptrLayer 指定图层
		* @return 若删除成功为true，否则为false
		*/
		BOOL DeleteLayer(ILayerPtr ptrLayer);

		/**
		* 将图层上移
		* @param ptrLayer 指定图层
		*/
		void MoveLayerUp(ILayerPtr ptrLayer);

		/**
		* 将图层下移
		* @param ptrLayer 指定图层
		*/
		void MoveLayerDown(ILayerPtr ptrLayer);

		/**
		* 将图层移到顶层
		* @param ptrLayer 指定图层
		* @return 
		*/
		void MoveLayerToTop(ILayerPtr ptrLayer);

		/**
		* 将图层移到底层
		* @param ptrLayer 指定图层
		*/
		void MoveLayerToBottom(ILayerPtr ptrLayer);

		/**
		* 清除地图视图中图层
		* @return 
		*/
		void Clear();

		// 浅copy，图层级对象为引用关系
		//SYSTEM::CSmartPtr<CMap> Clone();

		/**
		* 更新地图投影
		* @retrun 指定图层
		*/
		BOOL	UpdateMapProjection(ILayerPtr pLayer);

		/**
		* 获取地图投影
		* @retrun 地图当前投影
		*/
		std::string GetMapProjection();

		/**
		* 将图层移到底层
		* @param ptrLayer 指定图层
		*/
		void	UpdateMapExtent();

		/**
		* 获得图层组
		* @return 图层组
		*/
		CLayerArray& GetLayers();


		/**设置当前激活图层
		*
		* @param ILayerPtr ptrLayer
		* @return 
		*/
		void SetActiveLayer(ILayerPtr ptrLayer);

		/**
		* 得到当前激活图层
		*/

		ILayerPtr GetActiveLayer();

		/**
		* 获得编辑器
		*/
		//IEditorPtr GetEditor() {return m_pEditor;};

		/**
		* 设置编辑器
		*/
		//void SetEditor(IEditorPtr pEditor){m_pEditor =pEditor;}

		/** 
		* 获得鹰眼绘制对象
		*/
		//IEagleEyeViewPtr GetEagleViewDrawer() {return m_pEagleEyeViewPtr;};

		/** 
		* 设置鹰眼绘制对象
		*/
		//void SetEagleViewDrawer(IEagleEyeViewPtr pView) {m_pEagleEyeViewPtr = pView;};

		CGraphicLayerPtr GetGraphicLayer();

		void ResetGraphicLayer();

		//Element::CElementOperationStackPtr GetElementOperationStack(){return m_pElementOperStack;};

		/** 
		* 获得AOI管理类
		*/
		//CAoiManagerPtr GetAOIManager() {return m_pAoiManager;};

		/** 
		* 获得十字丝对象
		*/
		//CCrossLine* GetCrossLiner() {return m_pCrossLine;};

		/** 
		* 设置十字丝对象
		*/
		//void SetCrossLiner(CCrossLine* pCrossLiner) {m_pCrossLine = pCrossLiner;};



		/** 函数名称	:	RegisterDeleteLayer(boost::function fun)
		*描述			:	注册删除图层的回调函数
		* 参数			:	boost::function fun 函数对象
		返回类型		:	boost::signals::connection 信号连接对象*/
		static boost::signals::connection RegisterDeleteLayer(boost::function<void (ILayerPtr)> fun);

		/** 函数名称	:	RegisterActiveLayer(boost::function fun)
		*描述			:	注册激活图层的回调函数
		* 参数			:	boost::function fun 函数对象
		返回类型		:	boost::signals::connection 信号连接对象*/
		static boost::signals::connection RegisterActiveLayer(boost::function<void (ILayerPtr)> fun);

		/** 函数名称	:	RegisterChangeMapExtent(boost::function fun)
		*描述			:	注册更改MAP地理范围的回调函数，当MAP范围变化时，一些需要做的响应
		* 参数			:	boost::function fun 函数对象
		返回类型		:	boost::signals::connection 信号连接对象*/
		static boost::signals::connection RegisterChangeMapExtent(boost::function<void (CMap*)> fun);

		/** 函数名称	:	RegisterChangeMapExtentMode(boost::function fun)
		*描述			:	注册更改MAP地理范围的回调函数，当MAP范围模式变化时，一些需要做的响应
		* 参数			:	boost::function fun 函数对象
		返回类型		:	boost::signals::connection 信号连接对象*/
		static boost::signals::connection CMap::RegisterChangeMapExtentMode(boost::function<void (CMap*)> fun);

		/** 函数名称	:	RegisterChangeMapProj(boost::function fun)
		*描述			:	注册更改MAP投影的回调函数，当MAP投影变化时，一些需要做的响应
		* 参数			:	boost::function fun 函数对象
		返回类型		:	boost::signals::connection 信号连接对象*/
		static boost::signals::connection CMap::RegisterChangeMapProj(boost::function<void (CMap*)> fun);
		/** 函数名称	:	RegisterChangeMapProj(boost::function fun)
		*描述			:	注册更改MAP投影的回调函数，当MAP投影变化时，一些需要做的响应
		* 参数			:	boost::function fun 函数对象
		返回类型		:	boost::signals::connection 信号连接对象*/
		static boost::signals::connection CMap::RegisterMapReDrawed(boost::function<void (CMap*)> fun);

		/** 函数名称	:	RegisterLayerColorAdjust(boost::function fun)
		*描述			:	注册删除图层的回调函数
		* 参数			:	boost::function fun 函数对象
		返回类型		:	boost::signals::connection 信号连接对象*/
		static boost::signals::connection RegisterLayerColorAdjust(boost::function<void (ILayerPtr)> fun);


		////view //////////////////////////////////////////////////////////////////////
		void SetViewBound(DIS_BOUND bound);

		DIS_BOUND GetViewBound();

		void SetViewEnvelope(GEOMETRY::geom::Envelope env){m_viewEnvelope = env;};

		GEOMETRY::geom::Envelope GetViewEnvelope();

		void SetExtentMode(MAP_EXTENT_MODE extMode){m_ExtentMode = extMode;};

		MAP_EXTENT_MODE GetExtentMode();

		void SetReferenceScale(double refScale); 
		double GetReferenceScale();

		void SetFramed(BOOL bFramed);

		void SetFramePageScale(double pageScale,double maptoPageScale);

		virtual const GEOMETRY::geom::Envelope& GetExtent(){return m_Envelope;};

		double GetMapToPageScale(){return m_dbMapToPageScale;};

		void SetDrawBound(DIS_BOUND bound, BOOL bCacheBuffer = FALSE);


	protected:

		long m_lID;

		//地图名
		std::string m_strMapName;

		//map project
		std::string m_strWkt;

		//图层序列
		CLayerArray	m_Layers;	

		//element图层
		CGraphicLayerPtr	m_pGraphicLayer;

		MAP_EXTENT_MODE m_ExtentMode;			//范围模式

		GEOMETRY::geom::Envelope	m_viewEnvelope;

		GEOMETRY::geom::Envelope	m_drawEnvelope;

		double	m_dbReferenceScale;

		//////////////////////////////////////////////////////////////////////////
		//Element::CElementOperationStackPtr m_pElementOperStack;	//图元操作回退栈


		//////////////////////////////////////

		//标识地图是否已经设置投影
		BOOL m_bSetPrj;

		//map extent
		GEOMETRY::geom::Envelope m_Envelope;


		//Display device
		Display::IDisplayPtr m_pDisplay;


		//地图的单位
		SYSTEM::SYS_UNIT_TYPE m_unit;

		//当前激活图层
		//ILayerPtr m_activeLayer;

		//编辑器
		//IEditorPtr m_pEditor;

		//保存当前视图位置的临时对象
		//IEagleEyeViewPtr m_pEagleEyeViewPtr;

		BOOL m_bFramed;

		double m_dbFramePageScale;

		double m_dbMapToPageScale;



		//十字丝
		//CCrossLine* m_pCrossLine;

		//管理AOI
		//CAoiManagerPtr     m_pAoiManager;

		//激活图层在图层数组中的索引
		long m_lActiveLayerId;

	public:
		double m_dbMapFixScale;

	};
	typedef SYSTEM::CSmartPtr<CMap> CMapPtr;

}

#endif