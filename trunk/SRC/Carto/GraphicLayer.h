//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/28
// 描述：  标绘对象层
//////////////////////////////////////////////////////////////////////


#ifndef _GraphicLayer_h
#define _GraphicLayer_h
#include "GraphicsContainer.h"
#include "GraphicsContainerSelect.h"
#include "SpatialQuery.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
#include "ILayer.h"

namespace Carto
{

class CARTO_DLL CGraphicLayer : public ILayer, public Element::CGraphicsContainer
								, public Element::CGraphicsContainerSelect
{
public:
	CGraphicLayer();
	CGraphicLayer(const GEOMETRY::geom::Envelope& envelope);
	virtual ~CGraphicLayer();

	/**
	* 序列化操作
	* @param SYSTEM::IArchive &ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	/**
	* 选择图层中某个集合，根据条件产生选择集
	* @param query 查询条件
	* @return 
	*/
	void Select(Geodatabase::CSimpleQuery* query, SELECT_OPTION selectOption = SELECT_REPLACE);

	void ClearSelectionSet();

	void Draw(Display::IDisplayPtr pDisplay,DRAW_CONTENT content);

	void SelectAllElements();

	GEOMETRY::geom::Envelope GetEnvelope();

	void AddElement(Element::IElementPtr pElement);

	void RemoveElement(Element::IElementPtr pElement);
	
	void BringForward(Element::IElementPtr pElement);

	void SendBackward(Element::IElementPtr pElement);

	void BringToFront(Element::IElementPtr pElement);

	void SendToBack(Element::IElementPtr pElement);

	void BringForward(Element::CElementCollection pElements);

	void SendBackward(Element::CElementCollection pElements);

	void BringToFront(Element::CElementCollection pElements);

	void SendToBack(Element::CElementCollection pElements);

	//将Element保存为shp 当前选择或者全部
	void SaveElementAsShp(std::string filename,bool bSlected=false);

	/*
	*描述			:	注册删除图元的回调函数
	* 参数			:	boost::function fun 函数对象
	*返回类型		:	boost::signals::connection 信号连接对象*/
	static boost::signals::connection RegisterDeleteElement(boost::function<void (Element::IElementPtr pElement)> fun);

protected:
	void SpatialSelect(Geodatabase::CSpatialQuery* query, SELECT_OPTION selectOption = SELECT_REPLACE);

	void SetMapFrame();

protected:
	GEOMETRY::geom::Envelope m_envelope;
};
typedef SYSTEM::CSmartPtr<CGraphicLayer> CGraphicLayerPtr;

};

#endif