//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/12
// 描述：  标绘要素的接口  所有标绘要素有其派生
//////////////////////////////////////////////////////////////////////


#ifndef IELEMENT_H
#define IELEMENT_H

#include "ElementDefine.h"
#include "IDisplay.h"
//#include "AdvLineSymbol.h"
#include "SimpleMarkerSymbol.h"
#include "ISerialization.h"
#include "ISelectionTracker.h"
#include "SimpleFillSymbol.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"

namespace Element{
/** @interface */
/**
*类功能概述：Element管理
*/

class CElementCollection;

class CARTO_DLL IElement : public SYSTEM::ISerialization  {
public:
	IElement();

	IElement(const GEOMETRY::geom::Geometry& geometry);
	
	virtual ~IElement();

	/**
	* 功能描述：序列化操作
	* @param SYSTEM::IArchive &ar 档案文件流
	* @return  void
	*/
	virtual void serialization(SYSTEM::IArchive &ar);   
	
	/**
	* 功能描述:克隆函数
	* @return _ptr_t<IElement> Element智能指针
	*/
	virtual SYSTEM::CSmartPtr<IElement> Clone();


	/**
	* 功能描述:从数据流创建图元
	* @param SYSTEM::IArchive &ar 数据流
	* @return _ptr_t<IElement> Element智能指针
	*/
	static SYSTEM::CSmartPtr<IElement> CreateElementFromStream(SYSTEM::IArchive &ar);

	/**
	* 功能描述:新建图元
	* @param ELEMENT_TYPE type 图元类型
	* @return _ptr_t<IElement> Element智能指针
	*/
	static SYSTEM::CSmartPtr<IElement> CreateElement( ELEMENT_TYPE type);
   
	/**
    * 功能描述：设置Element激活
	*/
	void Activate( Display::IDisplayPtr pDisplay);

	/**
	* 功能描述：设置Element不激活
	*/
	void Deactivate(Display::IDisplayPtr pDisplay );
  
	/**
    * 功能描述：是否激活
	* @return bool
	*/
	bool IsActive(Display::IDisplayPtr pDisplay);
	
	/**
	* 功能描述：锁定或解锁element，以设置其是否是read only
	* @param BOOL bLock 标志进行锁定（TRUE）或解锁（FALSE）操作
	*/
	void Lock();

	/**
	* 功能描述：锁定或解锁element，以设置其是否是read only
	* @param BOOL bLock 标志进行锁定（TRUE）或解锁（FALSE）操作
	*/
	void UnLock();
	
	/**
	* 功能描述：返回锁定状态
	* @return BOOL
	*/
	BOOL IsLocked();

	/**
	* 功能描述：返回Element名称
	* @param std::string 名称
	* @return 
	*/
	void SetName(std::string strName);

	/**
	* 功能描述：返回Element名称
	*  @return std::string 名称
	*/
	std::string GetName();
   
	/**
    * 功能描述：返回Element类型
	* @return ELEMENT_TYPE
	*/
	ELEMENT_TYPE GetType();

	/**
	* 功能描述：设置图形
	* @param GEOMETRY::geom::Geometry& geometry 图形,外部管理图形
	* @return void
	*/
	virtual void SetGeometry(GEOMETRY::geom::Geometry& geometry);

	/**
	* 功能描述：设置图形
	* @param GEOMETRY::geom::Geometry& geometry 图形，内部管理图形指针
	* @return void
	*/
	virtual void SetGeometry(GEOMETRY::geom::Geometry* geometry);
	/**
	* 功能描述：返回Element形状
	* @return GEOMETRY::geom::Geometry 图元图形
	*/
	virtual GEOMETRY::geom::Geometry* GetGeometry();

	/**
	* 功能描述：返回Element地理范围
	* @return GEOMETRY::geom::Envelope&
	*/
	virtual  GEOMETRY::geom::Envelope GetEnvelope();

	/**
	* 功能描述：设置符号
	* @param Display::ISymbolPtr 图元符号
	*/
	void SetSymbol(Display::ISymbolPtr pSymbol);

	/**
	* 功能描述：获取符号
	* @return Display::ISymbolPtr 图元符号
	*/
	Display::ISymbolPtr GetSymbol();

	/**
	* 功能描述：设置图元定位点
	* @return ELEMENT_ANCHOR_POS 图元定位点
	*/
	virtual void SetAnchorPos(ELEMENT_ANCHOR_POS anchorpos){m_AnchorPos = anchorpos;};

	/**
	* 功能描述：获取图元定位点
	* @return ELEMENT_ANCHOR_POS 图元定位点
	*/
	virtual ELEMENT_ANCHOR_POS GetAnchorPos(){return m_AnchorPos;};

	//////////////////////////////////////////////////////////////////////////
	/**
	* 功能描述：设置编辑模式
	* @param ELEMENT_EDIT_MODE editMode 编辑模式
	*/
	virtual void SetEditMode(ELEMENT_EDIT_MODE editMode);
	
	/**
	* 功能描述：获取编辑模式
	* @return ELEMENT_EDIT_MODE 编辑模式
	*/
	ELEMENT_EDIT_MODE GetEditMode();

	/**
	* 功能描述：设置绘制模式
	* @param ELEMENT_DRAW_MODE editMode 绘制模式
	*/
	virtual void SetDrawMode(ELEMENT_DRAW_MODE drawMode);

	/**
	* 功能描述：获取绘制模式
	* @return ELEMENT_DRAW_MODE  绘制模式
	*/
	ELEMENT_DRAW_MODE GetDrawMode();

	/**
	* 功能描述：设置是否可以编辑长宽比
	* @return BOOL 
	*/
	virtual void SetWHRatioMode(ELEMENT_WIDTH_HEIGHT_RATIO eWHRatio);

	/**
	* 功能描述：获取是否可以编辑长宽比
	* @return BOOL 
	*/
	virtual BOOL CanSetWHRMode();

	/**
	* 功能描述：获取长宽比模式
	* @return BOOL 
	*/
	ELEMENT_WIDTH_HEIGHT_RATIO GetWHRatioMode();

	//////////////////////////////////////////////////////////////////////////

	/**
	* 功能描述：根据空间选择条件，返回图元选择结果
	* @param GEOMETRY::geom::Geometry* pSelectGeometry 选择范围
	* @param long lSpatialRelation 空间选择条件
	* @param CElementCollection& selectedSubElements 输出参数，被选中的图元的附属图元集合
	* @return BOOL 标志图元自身是否被选中
	*/
	virtual BOOL Select(GEOMETRY::geom::Geometry* pSelectGeometry, long lSpatialRelation, CElementCollection& selectedSubElements,double dbTolerance=0.0);

	/**
	* 功能描述：击中判断
	* @param GEOMETRY::geom::Coordinate coord 给定点的坐标
	* @param bool dbTolerance 容忍距离
	* @BOOL bTestSelectionHandle 是否判断击中handle
	* @return void
	*/
	virtual HIT_TEST_RES HitTest ( GEOMETRY::geom::Coordinate coord, double dbTolerance=0, HIT_MODE nHitMode = HH_HIT_GEOMETRY); 
	
	/**
	* 功能描述：移动Handle
	* @param HIT_HANDLE nHandle 移动的handle
	* @param GEOMETRY::geom::Coordinate coord handle将被移动到的位置
	* @return void
	*/
	virtual void MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord);

	/**
	* 功能描述：移动节点
	* @param long lIndex 移动的节点序号
	* @param GEOMETRY::geom::Coordinate coord 节点将被移动到的位置
	* @return void
	*/
	virtual void MoveVertixTo(long lIndex,GEOMETRY::geom::Coordinate coord);

	/**
	* 功能描述：缩放
	* @param DIS_POINT pPoint 缩放的
	* @param double sx x轴方向的缩放比例
	* @param double sy y轴方向的缩放比例
	* @return void
	*/
	virtual void Scale(DIS_POINT pPoint, double sx, double sy);

	/**
	* 功能描述：平移
	* @param double dx x轴方向的平移距离
	* @param double dy y轴方向的平移距离
	* @return void
	*/
	virtual void Move(double dx, double dy);

	/**
	* 功能描述：旋转
	* @param DIS_POINT pPoint 旋转中心点
	* @param double rotationAngle 旋转角度（PI为单位）
	* @return void
	*/
	virtual void Rotate(DIS_POINT pPoint, double rotationAngle);

	/**
	* 功能描述：改变图形地理范围
	* @param newEnvelope 新的地理范围
	* @return void
	*/
	virtual void ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope);


	ISelectionTrackerPtr GetSelectionTracker(){return m_pSelectionHandle;};

	//////////////////////////////////////////////////////////////////////////
	
	/**
	* 功能描述：绘制
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @param bool bPrint 是否打印
	* @return void
	*/
	virtual void Draw( Display::IDisplayPtr pDisplay/* , ELEMENT_EDIT_MODE editMode = EEM_NO_EDIT*/);

	/**
	* 功能描述：绘制地理范围
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @param bool bPrint 是否打印
	* @return void
	*/
	virtual void DrawEnvelope(Display::IDisplayPtr pDisplay);

	
protected:

	/**
	* 功能描述:图元geometry改变后的事件响应
	* @return void
	*/
	virtual void GeometryChangedEvents();

	/**
	* 功能描述:改变图元geometry的范围
	* @return void
	*/
	/**
	* 功能描述：绘制图元
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawNoEditMode(Display::IDisplayPtr pDisplay);
	/**
	* 功能描述：选择图元绘制
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawSelectMode(Display::IDisplayPtr pDisplay);
	/**
	* 功能描述：编辑图元节点绘制
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawEditVertixMode(Display::IDisplayPtr pDisplay);
	/**
	* 功能描述：绘制正在绘制图元
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawOnDrawMode(Display::IDisplayPtr pDisplay);
	/**
	* 功能描述：移动图元绘制
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawMoveMode(Display::IDisplayPtr pDisplay);
	/**
	* 功能描述：图元正常绘制
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawNormal(Display::IDisplayPtr pDisplay)=0;
	/**
	* 功能描述：图元草稿绘制
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawDraft(Display::IDisplayPtr pDisplay);
	/**
	* 功能描述：打印图元绘制
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawPrint(Display::IDisplayPtr pDisplay);

	/**
	* 功能描述：绘制选择框
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawSelectionTracker(Display::IDisplayPtr pDisplay);

	/**
	* 功能描述：绘制编辑节点
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @return void
	*/
	virtual void DrawVertixTracker(Display::IDisplayPtr pDisplay);
	
protected:
	BOOL m_bLocked;								//是否只读

	BOOL m_bActive;								//在当前display中是否显示

	ELEMENT_TYPE m_enumElementType;				//图元类型

	std::string m_strName;						//图元名称

	//图形、位置、编辑及绘制符号
	GEOMETRY::geom::Geometry* m_pGeometry;	//图元几何形状

	Display::ISymbolPtr	m_pSymbol;			//图元绘制符号

	ELEMENT_ANCHOR_POS m_AnchorPos;				//定位点

	ELEMENT_WIDTH_HEIGHT_RATIO	m_eWHRatio;		//宽高比例调节模式

	BOOL	m_bCanSetWHRMode;					//用户是否能设置宽高比模式

	//绘制、编辑模式
	ELEMENT_DRAW_MODE m_DrawMode;				//标志绘制模式

	ELEMENT_EDIT_MODE m_EditMode;				//标志编辑模式

	//选择、编辑绘制符号
	ISelectionTrackerPtr m_pSelectionHandle;		//选择框

	Display::CSimpleMarkerSymbolPtr m_pVertixMarkerSymbol;

	Display::CSimpleMarkerSymbolPtr m_pControlPtMarkerSymbol;

	Display::CSimpleLineSymbolPtr m_pTrakerLineSymbol;

	Display::CSimpleFillSymbolPtr m_pEnvelopeSymbol; //边界绘制符号

};
typedef SYSTEM::CSmartPtr<IElement> IElementPtr;
}
#endif //IELEMENT_H
