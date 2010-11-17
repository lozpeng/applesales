#ifndef GEOMETRY_GEOM_GEOMETRY_SNAP_INTERFACE_H
#define GEOMETRY_GEOM_GEOMETRY_SNAP_INTERFACE_H

#include <Geometry/platform.h>
#include <Geometry/inline.h>
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType

#include <string>
#include <iostream>
#include <vector>
#include <memory>


namespace GEOMETRY {
namespace geom { 


class Coordinate;  

//捕捉几何图形的节点、中点等的接口
class ISnap
{
public:
	ISnap(){};
	~ISnap(){};

public:
     /**
	 * 以下为捕捉节点的函数
	 * pPoint为参考点

	 * .tolerance为捕捉距离

	 * poutPt为捕捉到的点

	 * searchDis为到参考点的距离

	 * plpartIndex为捕捉到的点在图形的哪一部分,如果是单一部分的图形，则返回0

	 * plvertexIndex 为捕捉到的点的序号，该序号是相对于它所在的部分

	 * plSegIndex 为捕捉点所在的线段的序号，该序号是相对于它所在的Part

	 *如果成功捕捉返回true
	 */

	//捕捉节点

    virtual bool SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex);
    //捕捉线上点
	virtual bool SnapEdgePoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex);
    //捕捉线的中点
	virtual bool SnapMidPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex);
    //捕捉端点
	virtual bool SnapEndPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex);
	



};













} // GEOMETRY::geom
} //GEOMETRY







#endif
