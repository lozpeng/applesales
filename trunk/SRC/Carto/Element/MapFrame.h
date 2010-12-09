//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/14
// 描述：  制图要素——地图框
//////////////////////////////////////////////////////////////////////

#ifndef CMAP_FRAME_H
#define CMAP_FRAME_H
#include "IFrameElementBase.h"
#include "MapGrids.h"
#include "IMapSurround.h"
#include "Map.h"
#include "GraphicsContainer.h"

#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>

typedef boost::signals::connection  connection_t;

namespace Element{

class CARTO_DLL CMapFrame :public IFrameElementBase
{
public:
	CMapFrame();
	CMapFrame(const GEOMETRY::geom::Geometry& geometry, Carto::CMapPtr pGeoMap);
	~CMapFrame(void);

	virtual void serialization(SYSTEM::IArchive &ar);

	//创建附属图元
	IMapSurroundPtr CreateMapSurroundElement(ELEMENT_TYPE enumElementType);
	
	//获取网格
	CMapGrids&	GetMapGrids();

	//设置与frame关联的地图
	void SetMap(Carto::CMapPtr pMap);

	//获取与frame关联的地图
	Carto::CMapPtr GetMap();

	void SetMapToPageScale(double scale);
	
	//属性编辑
	//地图/页面比例
	double	GetMapToPageScale();

	//地图显示范围模式
	void SetViewExtAutoMode();

	void SetViewExtFixScaleMode(double dbMapScale, GEOMETRY::geom::Coordinate coordLeftBottom);

	void SetViewExtFixExtentMode(GEOMETRY::geom::Envelope viewExtent);

	GEOMETRY::geom::Envelope GetViewEnvelope();

	long GetMapID();

	void SetMapFrameID(long id){m_MapFrameID = id;};

	long GetMapFrameID(){return m_MapFrameID;}; 

	/** 函数名称	:	RegisterDeleteLayer(boost::function fun)
	*描述			:	注册删除图层的回调函数
	* 参数			:	boost::function fun 函数对象
	返回类型		:	boost::signals::connection 信号连接对象*/
	static boost::signals::connection RegisterMapFrameProperChanged(boost::function<void (CMapFrame*)> fun);

	/** 函数名称	:	RegisterDeleteLayer(boost::function fun)
	*描述			:	注册删除图层的回调函数
	* 参数			:	boost::function fun 函数对象
	返回类型		:	boost::signals::connection 信号连接对象*/
	static boost::signals::connection RegisterMapFrameMapSetted(boost::function<void (CMapFrame*)> fun);


protected:
	void UpdateMapFrame(Display::IDisplayPtr pDisplay);
	
	void DrawNormal(Display::IDisplayPtr pDisplay);

	void DrawMap(Display::IDisplayPtr pDisplay);

	void DrawGrids(Display::IDisplayPtr pDisplay);

	void ReDrawMap(Display::IDisplayPtr pDisplay);

	void ReCalcGrid();

	void ReCalcMapToPageScale(Display::IDisplayPtr pDisplay);

	void SetMapFrameDirty(BOOL bDirty);

	void GeometryChangedEvents();

	void SetStandardMappingState( BOOL bIsStdMap = TRUE );

	BOOL GetStandardMappingState( void );

protected:
	connection_t m_ConnectionMapExtentModeChange;

	connection_t m_ConnectionMapRedrawed;

	connection_t m_ConnectionViewChange;

	void CallbackMapRedrawedFun(Carto::CMap* pMap);

	void CallbackMapExtentModeChangedFun(Carto::CMap* pMap);

	void CallbackViewPosChange(Display::VIEW_POSITION viewPosition);


protected:

	int					m_mapID;				//只在序列化read时作暂时保留mapid的作用；

	Carto::CMapPtr m_pGeoMap;				//与Frame关联的Map

	BOOL				m_bStandardMap;			//标志是否为标准制图状态

	long				m_MapFrameID;			//唯一标识mapframe的ID号，由GraphicLayer管理，用于mapsurroundElement寻找相关的Mapframe

	BOOL				m_bMapProperChanged;	//标识mapframe属性是否更改

	//固定比例尺属性
	double				m_dbMapScale;			//Map相对layout的比例尺

	BOOL				m_bNewMapScale;			//标志固定比例尺是否更新

	GEOMETRY::geom::Coordinate	m_coordLeftBottom;	//固定比例尺时左下角的位置 

	//固定范围
	BOOL		m_bNewFixViewExtent;			//标志固定范围是否更新

	CMapGrids	m_Grids;						//网格


	DIS_BOUND	m_drawBound;

};

typedef SYSTEM::CSmartPtr<CMapFrame> CMapFramePtr;

}
#endif
