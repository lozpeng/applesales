//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/25
// 描述：  标绘对象——气饱文字
//////////////////////////////////////////////////////////////////////

#ifndef CALLOUT_TEXT_H
#define CALLOUT_TEXT_H
#include "ITextElement.h"
#include "SimpleFillSymbol.h"

namespace Element{
	class CARTO_DLL CCalloutTextElement : public ITextElement
{
public:
	CCalloutTextElement();
	CCalloutTextElement(GEOMETRY::geom::Envelope& env);
	virtual~CCalloutTextElement(void);

	void serialization(SYSTEM::IArchive &ar);


	void DrawNormal(Display::IDisplayPtr pDisplay);

	void Move(double x, double y);

	void MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord);
	
	virtual GEOMETRY::geom::Geometry*	GetGeometry();

	virtual void SetGeometry(GEOMETRY::geom::Geometry* pGeometry);

	void GeometryChangedEvents();

	void MovePoint(double x, double y);

	

	void UpdateGeometry(Display::IDisplayPtr pDisplay);

	void UpdateTextEnv(Display::IDisplayPtr pDisplay);

	void UnionPointAndRect();

	//得到作用点
	GEOMETRY::geom::Coordinate GetAnchorPoint() const {return m_Point;}

	//设置作用点
	void SetAnchorPoint(const GEOMETRY::geom::Coordinate &point){m_Point =point;};

	//得到文字起始点
	GEOMETRY::geom::Coordinate GetTextOrgPoint() const {return m_coordOrg;}

	//设置文字起始点
	void SetTextOrgPoint(const GEOMETRY::geom::Coordinate &point){m_coordOrg =point;};


protected:
	GEOMETRY::geom::Coordinate m_Point;
	GEOMETRY::geom::Envelope m_TextEnv;
	
};

	typedef SYSTEM::CSmartPtr<CCalloutTextElement> CCalloutTextElementPtr;
}

#endif;
