#ifndef CENVELOPE_TRAKER_H
#define CENVELOPE_TRAKER_H

#include "ISelectionTracker.h"



namespace Element{

class CARTO_DLL CEnvelopeTracker :public ISelectionTracker
{
public:
	CEnvelopeTracker(const GEOMETRY::geom::Envelope& envelope,HANDLE_TYPE handleType = HT_NONE);
	CEnvelopeTracker(const GEOMETRY::geom::Geometry& geometry, HANDLE_TYPE handleType = HT_NONE);
	~CEnvelopeTracker(void);

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

	void SetGeometry(const GEOMETRY::geom::Geometry& geometry);

protected:
	void UpdateEnvelope();
	void UpdateHandle();
	void UpdateGeometryByEnvelope();

protected:
	GEOMETRY::geom::Envelope m_envelope;
};

typedef SYSTEM::CSmartPtr<CEnvelopeTracker> CEnvelopeTrackerPtr;
}
#endif
