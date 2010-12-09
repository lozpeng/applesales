//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/12
// ������  ���Ҫ��ѡ�� 
//////////////////////////////////////////////////////////////////////

#ifndef CSELECTION_HANDLE_H
#define CSELECTION_HANDLE_H

#include "ISelectionTracker.h"
#include "SimpleFillSymbol.h"
#include "SimpleMarkerSymbol.h"


namespace Element{

class CARTO_DLL CSelectionHandle :public ISelectionTracker
{
public:
	CSelectionHandle(const GEOMETRY::geom::Envelope& envlope, HANDLE_TYPE handleType = HT_NONE);
	~CSelectionHandle(void);

	SYSTEM::CSmartPtr<CSelectionHandle> Clone();

	void Draw(const Display::IDisplayPtr pDisplay);

	void DrawBorderLine(const Display::IDisplayPtr pDisplay);

	void DrawHandlePoint(const Display::IDisplayPtr pDisplay);

	void SetOutlineColor(COLORREF color);

	/**
	* ���������������ж�
	* @param double x �������x����
	* @param  double y �������y����
	* @param bool dbTolerance ���̾���
	* @return void
	*/
	HIT_HANDLE HitTest( GEOMETRY::geom::Coordinate coord, double dbTolerance=0); 

	/**
	* �����������ƶ�Handle
	* @param HIT_HANDLE nHandle �ƶ���handle
	* @param GEOMETRY::geom::Coordinate coord handle�����ƶ�����λ��
	* @return void
	*/
	void MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord);

	void SetEnvelope(const GEOMETRY::geom::Envelope& envlope);

	GEOMETRY::geom::Envelope GetEnvelope(){return m_envelope;};

	HANDLE_TYPE GetHandleType(){return m_handleType;};


protected:


protected:
	HANDLE_TYPE m_handleType; //
	Display::CSimpleMarkerSymbolPtr m_pMarkerSymbol; //����handle�ļ򵥵����
	GEOMETRY::geom::MultiPoint* m_pHandlePoints;    //handle
	GEOMETRY::geom::Envelope m_envelope;
	COLORREF m_color;

};

typedef SYSTEM::CSmartPtr<CSelectionHandle> CSelectionHandlePtr;
}
#endif
