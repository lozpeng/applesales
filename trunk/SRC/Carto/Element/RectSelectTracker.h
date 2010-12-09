#ifndef CRECT_SELECT_TRACKER_H
#define CRECT_SELECT_TRACKER_H

#include "ISelectionTracker.h"



namespace Element{

class CARTO_DLL  CRectSelectTracker :public ISelectionTracker
{
public:
	CRectSelectTracker();
	~CRectSelectTracker(void);



	GEOMETRY::geom::Geometry*	GetGeometry();
	
	void Init(const GEOMETRY::geom::Coordinate& startPt);
	void Update(const GEOMETRY::geom::Coordinate& EndPt);
	void Reset();

protected:
	void UpdateRect(GEOMETRY::geom::Envelope envlope);


protected:
	GEOMETRY::geom::Coordinate m_startPt;
	GEOMETRY::geom::Coordinate m_EndPt;




};

}
#endif
