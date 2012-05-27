//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/23
// ������  ����������� ��������б�����Ĺ���
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
	* ���л�����
	* @param SYSTEM::IArchive &ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar);


	//���һ��Element
	virtual void AddElement(IElementPtr pElement);
	//��Ӷ��Element
	virtual void AddElements(CElementCollection elements, BOOL bFrontToBackOrder = TRUE);
	//����һ��Element
	virtual void SetElementAt(long lIndex, IElementPtr pElement);
	//����һ��Element
	void InserElementAt(long lIndex, IElementPtr pElement);
	//ɾ��һ��Element
	virtual void RemoveElement(IElementPtr pElement);
	//ɾ������Element
	virtual void RemoveAllElements();
	//��ָ��Element��������ǰ��һ��
	virtual void BringForward(IElementPtr pElement);
	//��ָ��Element��������ǰ��һ��
	virtual void BringForward(CElementCollection pElements);
	//��ָ��Element�������к���һ��
	virtual void SendBackward(IElementPtr pElement);
	//��ָ��Element�������к���һ��
	virtual void SendBackward(CElementCollection pElements);
	//��ָ��Element�ƶ�����ǰ
	virtual void BringToFront(IElementPtr pElement);
	//��ָ��Element�ƶ�����ǰ
	virtual void BringToFront(CElementCollection pElements);
	//��ָ��Element�ƶ������
	virtual void SendToBack(IElementPtr pElement);
	//��ָ��Element�ƶ������
	virtual void SendToBack(CElementCollection pElements);
	//��Container�е�һ��Element�ƶ���GroupElement��
	virtual void MoveElementToGroup(IElementPtr pElement, CGroupElementPtr pGroupElement);
	//��GroupElement�е�һ��Element�Ƶ�Container��
	virtual void MoveElementFromGroup(IElementPtr pElement, CGroupElementPtr pGroupElement);
	//������һ��Element������ѵ�ĩβ���򷵻�NULL
	virtual IElementPtr Next();
	//������һ��Element������ѵ���ʼ���򷵻�NULL
	virtual IElementPtr Pre();
	//�����ڲ�ָ�룬ʹ��ָ���һ��Element,���ص�һ��Element
	virtual IElementPtr Reset(BOOL bFirst = TRUE);
	//����ָ��λ�õ�elements
	virtual CElementCollection& LocateElements(const GEOMETRY::geom::Coordinate *point);
	//����ָ����Χ�ڵ�elements,bContain��־�Ƿ�ȫ����
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
