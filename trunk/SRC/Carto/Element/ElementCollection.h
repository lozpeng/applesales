//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/10
// ������  �����󼯺�
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

	//���һ��Element
	void Add(IElementPtr pElement);
	//ɾ��һ��element
	void Remove(IElementPtr pElement);
	//�������element
	void Clear();
	//����ָ��element
	IElementPtr QueryElement(const long lIndex);
	//����ָ��element������
	long QueryElement(IElementPtr pElement);
	//����element����Ŀ
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