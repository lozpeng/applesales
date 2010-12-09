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
	* 功能描述：击中判断
	* @param double x 给定点的x坐标
	* @param  double y 给定点的y坐标
	* @param bool dbTolerance 容忍距离
	* @return void
	*/
	HIT_HANDLE HitTest( GEOMETRY::geom::Coordinate coord, double dbTolerance=0); 

	/**
	* 功能描述：移动Handle
	* @param HIT_HANDLE nHandle 移动的handle
	* @param GEOMETRY::geom::Coordinate coord handle将被移动到的位置
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
