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

//��׽����ͼ�εĽڵ㡢�е�ȵĽӿ�
class ISnap
{
public:
	ISnap(){};
	~ISnap(){};

public:
     /**
	 * ����Ϊ��׽�ڵ�ĺ���
	 * pPointΪ�ο���

	 * .toleranceΪ��׽����

	 * poutPtΪ��׽���ĵ�

	 * searchDisΪ���ο���ľ���

	 * plpartIndexΪ��׽���ĵ���ͼ�ε���һ����,����ǵ�һ���ֵ�ͼ�Σ��򷵻�0

	 * plvertexIndex Ϊ��׽���ĵ����ţ������������������ڵĲ���

	 * plSegIndex Ϊ��׽�����ڵ��߶ε���ţ������������������ڵ�Part

	 *����ɹ���׽����true
	 */

	//��׽�ڵ�

    virtual bool SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex);
    //��׽���ϵ�
	virtual bool SnapEdgePoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex);
    //��׽�ߵ��е�
	virtual bool SnapMidPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex);
    //��׽�˵�
	virtual bool SnapEndPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex);
	



};













} // GEOMETRY::geom
} //GEOMETRY







#endif
