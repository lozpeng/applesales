//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/23
// 描述：  标绘对象管理器 负责对所有标绘对象的管理
//////////////////////////////////////////////////////////////////////


#ifndef _CELEMENT_CONTAINER_H
#define _CELEMENT_CONTAINER_H

#include "IElement.h"
#include "ElementCollection.h"
#include "GroupElement.h"

namespace Element
{

class CARTO_DLL CGraphicsContainer : public SYSTEM::ISerialization
{
public:
	CGraphicsContainer(void);
	~CGraphicsContainer(void);

	/**
	* 序列化操作
	* @param SYSTEM::IArchive &ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);


	//添加一个Element
	virtual void AddElement(IElementPtr pElement);
	//添加多个Element
	virtual void AddElements(CElementCollection elements, BOOL bFrontToBackOrder = TRUE);
	//插入一个Element
	virtual void SetElementAt(long lIndex, IElementPtr pElement);
	//插入一个Element
	void InserElementAt(long lIndex, IElementPtr pElement);
	//删除一个Element
	virtual void RemoveElement(IElementPtr pElement);
	//删除所有Element
	virtual void RemoveAllElements();
	//将指定Element在排序中前移一步
	virtual void BringForward(IElementPtr pElement);
	//将指定Element在排序中前移一步
	virtual void BringForward(CElementCollection pElements);
	//将指定Element在排序中后移一步
	virtual void SendBackward(IElementPtr pElement);
	//将指定Element在排序中后移一步
	virtual void SendBackward(CElementCollection pElements);
	//将指定Element移动到最前
	virtual void BringToFront(IElementPtr pElement);
	//将指定Element移动到最前
	virtual void BringToFront(CElementCollection pElements);
	//将指定Element移动到最后
	virtual void SendToBack(IElementPtr pElement);
	//将指定Element移动到最后
	virtual void SendToBack(CElementCollection pElements);
	//将Container中的一个Element移动到GroupElement中
	virtual void MoveElementToGroup(IElementPtr pElement, CGroupElementPtr pGroupElement);
	//将GroupElement中的一个Element移到Container中
	virtual void MoveElementFromGroup(IElementPtr pElement, CGroupElementPtr pGroupElement);
	//返回下一个Element，如果已到末尾，则返回NULL
	virtual IElementPtr Next();
	//返回上一个Element，如果已到开始，则返回NULL
	virtual IElementPtr Pre();
	//重置内部指针，使其指向第一个Element,返回第一个Element
	virtual IElementPtr Reset(BOOL bFirst = TRUE);
	//返回指定位置的elements
	virtual CElementCollection& LocateElements(const GEOMETRY::geom::Coordinate *point);
	//返回指定范围内的elements,bContain标志是否全覆盖
	virtual CElementCollection& LocateElementsByEnvelope(const GEOMETRY::geom::Envelope *pEnvlope, BOOL bContain = FALSE);

	virtual long GetElementCount();

	virtual IElementPtr GetElement(long nIndex);

	virtual long FindElement(IElementPtr pElement);
public:
	static boost::signals::connection RegisterContainerChanged(boost::function<void (Element::IElementPtr pElement)> fun);
protected:
	virtual void ContainerChangedEvent(IElementPtr pElement);

protected:
	std::vector<IElementPtr> m_vecElements;
	std::vector<IElementPtr>::iterator m_iter;

};

typedef SYSTEM::CSmartPtr<CGraphicsContainer> CGraphicsContainerPtr;
}

#endif
