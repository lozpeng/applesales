#ifndef CGROUP_ELEMENT_H
#define CGROUP_ELEMENT_H
#include "IElement.h"
#include "ElementCollection.h"

namespace Element{


class CARTO_DLL CGroupElement: public IElement, public CElementCollection
{
public:
	CGroupElement(void);
	~CGroupElement(void);

	void serialization(SYSTEM::IArchive &ar);

//	SYSTEM::CSmartPtr<IElement> Clone();

	void ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope);

	/**
	* ��������������
	* @param DIS_POINT pPoint ���ŵ�
	* @param double sx x�᷽������ű���
	* @param double sy y�᷽������ű���
	* @return void
	*/
	void Scale(DIS_POINT pPoint, double sx, double sy);

	/**
	* ����������ƽ��
	* @param double dx x�᷽���ƽ�ƾ���
	* @param double dy y�᷽���ƽ�ƾ���
	* @return void
	*/
	void Move(double dx, double dy);

	/**
	* ������������ת
	* @param DIS_POINT pPoint ��ת���ĵ�
	* @param double rotationAngle ��ת�Ƕȣ�PIΪ��λ��
	* @return void
	*/
	void Rotate(DIS_POINT pPoint, double rotationAngle);


	void DrawNormal(Display::IDisplayPtr pDisplay);

	void SetWHRatioMode(ELEMENT_WIDTH_HEIGHT_RATIO eWHRatio);

	BOOL IsElementExist(IElementPtr pElement);

	BOOL IsMapSurroundElementExist();

protected:
	void CollectionChangedEvent();


};


typedef SYSTEM::CSmartPtr<CGroupElement> CGroupElementPtr;
}
#endif