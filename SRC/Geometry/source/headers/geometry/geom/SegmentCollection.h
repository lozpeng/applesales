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
*ISegmentCollection���������߶Ρ����ζ�������ɵļ���ͼ�εĻ��࣬��
* �ṩ�˻�ȡ����ӡ��޸ļ���ͼ���е�Segment�ķ���
*********************************************************************/
class ISegmentCollection
{
	friend class LineString;
	friend class LinearRing;
public:
    ISegmentCollection();
    
	virtual ~ISegmentCollection();

public:
	//��һ��Segment���뵽ͼ�ε���󣬾���ʵ��Ҫ�ɻ������
	virtual void AddSegment(ISegment *pSeg) { };


	ISegment* GetSegment(long index);

	//Segment�����ı�����
	virtual void SegmentsChanged() {};

	long SegmentCount() const;

	//�Ƿ��������
	bool IsContainArc() const;

protected:

	std::vector<ISegment*> m_Segments;

};




} // GEOMETRY::geom
} //GEOMETRY







#endif