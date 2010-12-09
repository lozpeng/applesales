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
	* 功能描述：缩放
	* @param DIS_POINT pPoint 缩放的
	* @param double sx x轴方向的缩放比例
	* @param double sy y轴方向的缩放比例
	* @return void
	*/
	void Scale(DIS_POINT pPoint, double sx, double sy);

	/**
	* 功能描述：平移
	* @param double dx x轴方向的平移距离
	* @param double dy y轴方向的平移距离
	* @return void
	*/
	void Move(double dx, double dy);

	/**
	* 功能描述：旋转
	* @param DIS_POINT pPoint 旋转中心点
	* @param double rotationAngle 旋转角度（PI为单位）
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