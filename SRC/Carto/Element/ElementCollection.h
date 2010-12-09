//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  标绘对象集合
//////////////////////////////////////////////////////////////////////

#ifndef _CELEMENT_COLLECTION_H
#define _CELEMENT_COLLECTION_H

#include "IElement.h"


namespace Element
{

class CARTO_DLL CElementCollection
{
public:
	CElementCollection(void);
	~CElementCollection(void);

	//添加一个Element
	void Add(IElementPtr pElement);
	//删除一个element
	void Remove(IElementPtr pElement);
	//清空所有element
	void Clear();
	//返回指定element
	IElementPtr QueryElement(const long lIndex);
	//返回指定element的索引
	long QueryElement(IElementPtr pElement);
	//返回element的数目
	long Count();

	//
	BOOL IsEmpty(){return Count()>0?FALSE:TRUE;};

protected:
	virtual void CollectionChangedEvent();

protected:
	std::vector<IElementPtr> m_vecElements;
};
}

#endif  