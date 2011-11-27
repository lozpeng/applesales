#include <owScene/geoshape.h>
#include <osg/Notify>

using namespace owScene;

GeoShape::GeoShape()
{
	;
}


GeoShape::GeoShape( const GeoShape& rhs )
{
	shape_type    = rhs.shape_type;
	parts         = rhs.parts;
	extent_cache  = rhs.extent_cache;
}


GeoShape::GeoShape( const GeoShape::ShapeType& _shape_type)
				   : shape_type( _shape_type )
{

}


GeoShape::~GeoShape()
{
	//NOP
}


const GeoShape::ShapeType&
GeoShape::getShapeType() const
{
	return shape_type;
}


void
GeoShape::setShapeType( const ShapeType& _type )
{
	shape_type = _type;
}


unsigned int
GeoShape::getPartCount() const
{
	return parts.size();
}


const GeoPointList&
GeoShape::getPart( unsigned int i ) const
{
	return parts[i];
}


GeoPointList&
GeoShape::getPart( unsigned int i )
{
	return parts[i];
}


GeoPartList&
GeoShape::getParts()
{
	return parts;
}


const GeoPartList&
GeoShape::getParts() const
{
	return parts;
}


GeoPointList&
GeoShape::addPart()
{
	parts.push_back( GeoPointList() );
	caculateExtent();
	return parts.back();
}


GeoPointList&
GeoShape::addPart( const GeoPointList& part )
{
	parts.push_back( part );
	caculateExtent();
	return parts.back();
}


GeoPointList&
GeoShape::addPart( unsigned int size )
{
	parts.push_back( GeoPointList( size ) );
	caculateExtent();
	return parts.back();
}


unsigned int
GeoShape::getTotalPointCount() const
{
	unsigned int total = 0;
	for( GeoPartList::const_iterator i = parts.begin(); i != parts.end(); i++ )
		total += i->size();
	return total;
}


const GeoExtent*
GeoShape::getExtent() const
{
	return extent_cache.get();
}

GeoExtent* GeoShape::getExtent()
{
	return extent_cache.get();
}

osg::Vec2 
GeoShape::getCenter() const
{
	return extent_cache->center();
}

void GeoShape::caculateExtent()
{
	struct ExtentVisitor : public GeoPointVisitor {
		ExtentVisitor() { e = new GeoExtent(); }
		osg::ref_ptr<GeoExtent> e;
		virtual bool visitPoint(GeoPoint& p ) {
			e->expandToInclude(p.x(),p.y());
			return true;
		}
		virtual bool visitPoint( const GeoPoint& p ) {
			e->expandToInclude(p.x(),p.y());
			return true;
		}
	};

	ExtentVisitor vis;
	accept( vis );

	// cast to non-const is OK for caching only
	extent_cache = vis.e.get();
}


bool
GeoShape::accept( GeoPointVisitor& visitor )
{
	for( unsigned int pi = 0; pi < getPartCount(); pi++ )
	{
		GeoPointList& part = getPart( pi );
		for( unsigned int vi = 0; vi < part.size(); vi++ )
		{
			if ( !visitor.visitPoint( part[vi] ) )
				return false;
		}
	}
	return true;
}


bool
GeoShape::accept( GeoPointVisitor& visitor ) const
{
	for( unsigned int pi = 0; pi < getPartCount(); pi++ )
	{
		const GeoPointList& part = getPart( pi );
		for( unsigned int vi = 0; vi < part.size(); vi++ )
		{
			if ( !visitor.visitPoint( part[vi] ) )
				return false;
		}
	}
	return true;
}

bool
GeoShape::intersects( const GeoExtent* ex ) const
{
	if(!ex)
		return false;

	for( GeoPartList::const_iterator i = getParts().begin(); i != getParts().end(); i++ )
	{
		const GeoPointList& part = *i;
		if ( part.intersects( ex ) )
			return true;
	}
	return false;
}

/**************************************************************************/


bool
GeoShapeList::intersects( const GeoExtent* ex ) const
{
	if(!ex)
		return false;

	for( GeoShapeList::const_iterator i = begin(); i != end(); i++ )
	{
		const GeoShape& shape = *i;
		if ( shape.intersects( ex ) )
			return true;
	}
	return false;
}


bool
GeoShapeList::accept( GeoPartVisitor& visitor )
{
	for( GeoShapeList::iterator i = begin(); i != end(); i++ )
	{
		for( GeoPartList::iterator j = (*i).getParts().begin(); j != (*i).getParts().end(); j++ )
		{
			if ( !visitor.visitPart( *j ) )
				return false;
		}
	}
	return true;
}

bool 
GeoShapeList::accept( GeoPartVisitor& visitor ) const
{
	for( GeoShapeList::const_iterator i = begin(); i != end(); i++ )
	{
		for( GeoPartList::const_iterator j = (*i).getParts().begin(); j != (*i).getParts().end(); j++ )
		{
			if ( !visitor.visitPart( *j ) )
				return false;;
		}
	}
	return true;
}


bool
GeoShapeList::accept( GeoPointVisitor& visitor )
{
	for( GeoShapeList::iterator i = begin(); i != end(); i++ )
	{
		for( GeoPartList::iterator j = (*i).getParts().begin(); j != (*i).getParts().end(); j++ )
		{
			for( GeoPointList::iterator k = (*j).begin(); k != (*j).end(); k++ )
			{
				if ( !visitor.visitPoint( *k ) )
					return false;
			}
		}
	}
	return true;
}

bool 
GeoShapeList::accept( GeoPointVisitor& visitor ) const
{
	for( GeoShapeList::const_iterator i = begin(); i != end(); i++ )
	{
		for( GeoPartList::const_iterator j = (*i).getParts().begin(); j != (*i).getParts().end(); j++ )
		{
			for( GeoPointList::const_iterator k = (*j).begin(); k != (*j).end(); k++ )
			{
				if ( !visitor.visitPoint( *k ) )
					return false;
			}
		}
	}
	return true;
}
