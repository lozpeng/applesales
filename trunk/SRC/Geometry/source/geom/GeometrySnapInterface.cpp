#include  <Geometry/geom/GeometrySnapInterface.h>
#include <Geometry/geom/Coordinate.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

	//捕捉节点
	bool ISnap::SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex)
	{
		return false;
	}
	//捕捉线上点
	bool ISnap::SnapEdgePoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex)
	{
		return false;
	}
	//捕捉线的中点
	bool ISnap::SnapMidPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex)
	{
		return false;
	}
	//捕捉端点
	bool ISnap::SnapEndPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex)
	{
		return false;
	}
    



} // GEOMETRY::geom
}