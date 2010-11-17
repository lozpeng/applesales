#include  <Geometry/geom/PointCollection.h>
#include <Geometry/geom/Coordinate.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

	long IPointCollection::PointCount() const
	{
       return 0;
	}

	void IPointCollection::AddPoint(GEOMETRY::geom::Coordinate &coord)
	{

	}

	void IPointCollection::InsertPoint(int index, GEOMETRY::geom::Coordinate &newpoint)
	{
      
	}

	void IPointCollection::ReplacePoint(int index, GEOMETRY::geom::Coordinate &newpoint)
	{
	   
	}

	Coordinate IPointCollection::GetPoint(int index)
	{
		return Coordinate();
	}

	void IPointCollection::RemovePoint(int index)
	{

	}
    



}
}