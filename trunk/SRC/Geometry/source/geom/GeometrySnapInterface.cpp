#include  <Geometry/geom/GeometrySnapInterface.h>
#include <Geometry/geom/Coordinate.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

	//��׽�ڵ�
	bool ISnap::SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex)
	{
		return false;
	}
	//��׽���ϵ�
	bool ISnap::SnapEdgePoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex)
	{
		return false;
	}
	//��׽�ߵ��е�
	bool ISnap::SnapMidPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex)
	{
		return false;
	}
	//��׽�˵�
	bool ISnap::SnapEndPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex)
	{
		return false;
	}
    



} // GEOMETRY::geom
}