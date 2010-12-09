#ifndef CENVELOPE_TRAKER_H
#define CCALLOUT_TRAKER_H

#include "ISelectionTracker.h"



namespace Element{

	class CARTO_DLL CCalloutTracker :public ISelectionTracker
	{
	public:
		CCalloutTracker();
		CCalloutTracker(const GEOMETRY::geom::Geometry& geometry);
		~CCalloutTracker(void);

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

		void SetHandle(const GEOMETRY::geom::Coordinate& handle);

	};

	typedef SYSTEM::CSmartPtr<CCalloutTracker> CCalloutTrackerPtr;
}
#endif
