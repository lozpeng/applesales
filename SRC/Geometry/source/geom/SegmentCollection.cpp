#include <Geometry/geom/SegmentCollection.h>
#include <Geometry/geom/Coordinate.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom


ISegmentCollection::ISegmentCollection()
{

}

ISegmentCollection::~ISegmentCollection()
{
	for(size_t i=0;i<m_Segments.size();i++)
	{
		delete m_Segments[i];
	}
	m_Segments.clear();

}

long ISegmentCollection::SegmentCount() const
{
	if(m_Segments.empty())
	{
		return 0;
	}

	return m_Segments.size();
}

ISegment* ISegmentCollection::GetSegment(long index)
{
	if(index<0 || index>=m_Segments.size())
	{
		return NULL;
	}
	return m_Segments[index];
}

bool ISegmentCollection::IsContainArc() const
{
	for(size_t i=0;i<m_Segments.size();i++)
	{
		if(m_Segments[i]->getGeometryTypeId()!=GEOM_LINE)
		{
			return true;
		}
	}
	return false;
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY