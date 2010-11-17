#ifndef GEOMETRY_GEOM_POINTCOLLECTION_H
#define GEOMETRY_GEOM_POINTCOLLECTION_H

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
class IPointCollection
{
public:
	IPointCollection(){};
	~IPointCollection(){};

public:

	virtual long PointCount() const;
    
	//��ͼ�ε�������һ���ڵ�
	virtual void AddPoint(Coordinate &coord);

	//����һ����
	virtual void InsertPoint(int index,Coordinate &newpoint);

	//�滻һ����
    virtual void ReplacePoint(int index,Coordinate &newpoint);

    virtual void RemovePoint(int index);

    virtual Coordinate GetPoint(int index);



};













} // GEOMETRY::geom
} //GEOMETRY







#endif
