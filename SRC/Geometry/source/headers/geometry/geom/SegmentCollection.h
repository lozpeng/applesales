#ifndef GEOMETRY_GEOM_SEGMENTCOLLECTION_H
#define GEOMETRY_GEOM_SEGMENTCOLLECTION_H

#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType
#include <Geometry/geom/ISegment.h>
#include <Geometry/inline.h>

#include <string>
#include <vector>
#include <memory> // for auto_ptr

namespace GEOMETRY {
namespace geom { 

class Coordinate; 
class LineString;
class LinearRing;


/********************************************************************
*ISegmentCollection是所有由线段、弧段对象所组成的几何图形的基类，它
* 提供了获取和添加、修改几何图形中的Segment的方法
*********************************************************************/
class ISegmentCollection
{
	friend class LineString;
	friend class LinearRing;
public:
    ISegmentCollection();
    
	virtual ~ISegmentCollection();

public:
	//将一个Segment加入到图形的最后，具体实现要由基类完成
	virtual void AddSegment(ISegment *pSeg) { };


	ISegment* GetSegment(long index);

	//Segment发生改变后调用
	virtual void SegmentsChanged() {};

	long SegmentCount() const;

	//是否包含弧段
	bool IsContainArc() const;

protected:

	std::vector<ISegment*> m_Segments;

};




} // GEOMETRY::geom
} //GEOMETRY







#endif