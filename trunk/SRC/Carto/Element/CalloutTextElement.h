//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/25
// ������  �����󡪡���������
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

	//�õ����õ�
	GEOMETRY::geom::Coordinate GetAnchorPoint() const {return m_Point;}

	//�������õ�
	void SetAnchorPoint(const GEOMETRY::geom::Coordinate &point){m_Point =point;};

	//�õ�������ʼ��
	GEOMETRY::geom::Coordinate GetTextOrgPoint() const {return m_coordOrg;}

	//����������ʼ��
	void SetTextOrgPoint(const GEOMETRY::geom::Coordinate &point){m_coordOrg =point;};


protected:
	GEOMETRY::geom::Coordinate m_Point;
	GEOMETRY::geom::Envelope m_TextEnv;
	
};

	typedef SYSTEM::CSmartPtr<CCalloutTextElement> CCalloutTextElementPtr;
}

#endif;
