#include <owUtil/SpatialReference.h>
#include <owUtil/Log.h>
#include <owUtil/Registry.h>

#include <ogr_api.h>
#include <ogr_spatialref.h>

#include <algorithm>

using namespace owUtil;

static std::string
getOGRAttrValue( void* _handle, const std::string& name, int child_num, bool lowercase =false)
{
	//GDAL_SCOPED_LOCK;
	const char* val = OSRGetAttrValue( _handle, name.c_str(), child_num );
	if ( val )
	{
		std::string t = val;
		if ( lowercase )
		{
			std::transform( t.begin(), t.end(), t.begin(), ::tolower );
		}
		return t;
	}
	return "";
}

SpatialReference::SpatialReferenceCache& SpatialReference::getSpCache()
{
	static SpatialReference::SpatialReferenceCache cache;
	return cache;
}

SpatialReference* SpatialReference::createFromWKT(
									   const std::string& wkt, const std::string& alias, const std::string& name  )
{
	osg::ref_ptr<SpatialReference> result;
	//GDAL_SCOPED_LOCK;
	void* handle = OSRNewSpatialReference( NULL );
	char buf[4096];
	char* buf_ptr = &buf[0];
	strcpy_s( buf, wkt.c_str() );
	if ( OSRImportFromWkt( handle, &buf_ptr ) == OGRERR_NONE )
	{
		result = new SpatialReference( handle, "WKT", alias, name );
		result->Init();
	}
	else 
	{
		OSRDestroySpatialReference( handle );
	}
	return result.release();
}

SpatialReference* SpatialReference::createFromPROJ4(
	const std::string& proj4, const std::string& alias, const std::string& name)
{
	SpatialReference* result = NULL;
	//GDAL_SCOPED_LOCK;
	void* handle = OSRNewSpatialReference( NULL );
	if ( OSRImportFromProj4( handle, proj4.c_str() ) == OGRERR_NONE )
	{
		result = new SpatialReference( handle, "PROJ4", alias, name );
		result->Init();
	}
	else 
	{
		OSRDestroySpatialReference( handle );
	}
	return result;
}

SpatialReference* SpatialReference::create( const std::string& init )
{
	std::string low = init;
	std::transform( low.begin(), low.end(), low.begin(), ::tolower );

	SpatialReferenceCache::iterator itr = getSpCache().find(init);
	if (itr != getSpCache().end())
	{
		return itr->second.get();
	}

	osg::ref_ptr<SpatialReference> srs;

	//spherical-mercator
	if (low == "spherical-mercator" || low == "epsg:900913" || low == "epsg:3785" ||
		low == "epsg:41001" || low == "epsg:102113" || low == "epsg:102100")
	{
		srs = createFromPROJ4(
			"+proj=merc +a=6378137 +b=6378137 +lon_0=0 +k=1 +x_0=0 +y_0=0 +nadgrids=@null +units=m +no_defs",
			init,
			"Spherical Mercator" );
	}
	//ellipsoidal ("world") mercator
	else if (low == "epsg:54004" || low == "epsg:9804" || low == "epsg:3832")
	{
		srs = createFromPROJ4(
			"+proj=merc +lon_0=0 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs",
			init,
			"World Mercator" );
	}
	//common WGS84:
	else if (low == "epsg:4326" || low == "wgs84")
	{
		srs = createFromPROJ4(
			"+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs",
			init,
			"WGS84" );
	}
	else if ( low.find( "+" ) == 0 )
	{
		srs = createFromPROJ4( low, init );
	}
	else if ( low.find( "epsg:" ) == 0 || low.find( "osgeo:" ) == 0 )
	{
		srs = createFromPROJ4( std::string("+init=") + low, init );
	}
	else if ( low.find( "projcs" ) == 0 || low.find( "geogcs" ) == 0 )
	{
		srs = createFromWKT( init, init );
	}
	else
	{
		LOG_WARNING("创建空间参考系统"+init+"失败");
		return NULL;
	}

	getSpCache()[init] = srs;
	return srs.get();
}

SpatialReference* SpatialReference::create( osg::CoordinateSystemNode* csn )
{
	SpatialReference* result = NULL;
	if ( csn && !csn->getCoordinateSystem().empty() )
	{
		result = create( csn->getCoordinateSystem() );
	}
	return result;
}

const std::string& SpatialReference::getName() const
{
	return _name;
}

const std::string& SpatialReference::getInitString() const
{
	return _initstring;
}

const std::string& SpatialReference::getInitType() const
{
	return _inittype;
}

const osg::EllipsoidModel* SpatialReference::getEllipsoid() const
{
	return _ellipsoidmodel;
}

bool SpatialReference::isGeographic() const
{
	return _bGeographic;
}

bool SpatialReference::isProjected() const
{
	return !_bGeographic;
}

bool SpatialReference::isEquivalentTo( const SpatialReference* rhs ) const
{
	if ( !rhs )
		return false;

	if ( this == rhs )
		return true;

	if ( _initstring == rhs->_initstring )
		return true;

	if (isGeographic()  != rhs->isGeographic())
	{
		return false;
	}

	if (this->isGeographic() && rhs->isGeographic() &&
		fabs(this->getEllipsoid()->getRadiusEquator() - rhs->getEllipsoid()->getRadiusEquator())<0.1 &&
		fabs(this->getEllipsoid()->getRadiusPolar() - rhs->getEllipsoid()->getRadiusPolar())<0.1)
	{
		return true;
	}

	//GDAL_SCOPED_LOCK;
	return TRUE == ::OSRIsSame( _handle, rhs->_handle );
}

bool SpatialReference::transform(
			   double x, double y,
			   const SpatialReference* to_srs,
			   double& out_x, double& out_y) const
{
	if (isEquivalentTo(to_srs))
	{
		out_x = x;
		out_y = y;
		return true;
	}

	//GDAL_SCOPED_LOCK;

	void* xform_handle = NULL;
	TransformHandleCache::const_iterator itr = _transformHandleCache.find(to_srs->getInitString());
	if (itr != _transformHandleCache.end())
	{
		xform_handle = itr->second;
	}
	else
	{
		xform_handle = OCTNewCoordinateTransformation( _handle, to_srs->_handle);
		const_cast<SpatialReference*>(this)->_transformHandleCache[to_srs->getInitString()] = xform_handle;
	}

	if ( !xform_handle )
	{
		std::ostringstream os;
		os<< "投影转换失败..." << std::endl;
		os<< "    从 :" << getName() << std::endl;
		os<< "    到： " << to_srs->getName() << std::endl;
		LOG_WARNING(os.str());
		return false;
	}

	double temp_x = x;
	double temp_y = y;
	double temp_z = 0.0;
	bool result;

	if ( OCTTransform( xform_handle, 1, &temp_x, &temp_y, &temp_z ) )
	{
		result = true;
		out_x = temp_x;
		out_y = temp_y;
	}
	else
	{
		std::ostringstream os;
		os<< "从 "
			<< getName() << " 到 " << to_srs->getName()
			<< "转换点失败"<<std::endl;
		result = false;
	}
	return result;
}

bool SpatialReference::transformPoints(
					 const SpatialReference* to_srs, 
					 double* x, double *y,
					 unsigned int numPoints,
					 bool ignore_errors) const
{
	if (isEquivalentTo(to_srs)) return true;

	bool success = false;

	{    
		//GDAL_SCOPED_LOCK;

		void* xform_handle = NULL;
		TransformHandleCache::const_iterator itr = _transformHandleCache.find(to_srs->getInitString());
		if (itr != _transformHandleCache.end())
		{
			std::ostringstream os;
			os << "从缓冲中获得转换句柄" << std::endl;
			LOG_DEBUG(os.str());
			xform_handle = itr->second;
		}
		else
		{
			xform_handle = OCTNewCoordinateTransformation( _handle, to_srs->_handle);
			const_cast<SpatialReference*>(this)->_transformHandleCache[to_srs->getInitString()] = xform_handle;
		}

		if ( !xform_handle )
		{
			std::ostringstream os;
			os<< "投影转换失败..." << std::endl;
			os<< "    从 :" << getName() << std::endl;
			os<< "    到： " << to_srs->getName() << std::endl;
			LOG_WARNING(os.str());
			return false;
		}

		double* temp_z = new double[numPoints];
		success = OCTTransform( xform_handle, numPoints, x, y, temp_z ) > 0;
		delete[] temp_z;

	}
	if(!success)
	{
		std::ostringstream os;
		os<< "从 "
			<< getName() << " 到 " << to_srs->getName()
			<< "转换点失败"<<std::endl;
	}
	return success;
}


bool SpatialReference::transformPoints(
					 const SpatialReference* to_srs,
					 std::vector<osg::Vec3d> *points,
					 bool ignore_errors) const
{
	if (isEquivalentTo(to_srs)) return true;

	int numPoints = points->size();
	double* x = new double[numPoints];
	double* y = new double[numPoints];

	for( int i=0; i<numPoints; i++ )
	{
		x[i] = (*points)[i].x();
		y[i] = (*points)[i].y();
	}

	bool success = transformPoints( to_srs, x, y, numPoints, ignore_errors );

	if ( success )
	{
		for( int i=0; i<numPoints; i++ )
		{
			(*points)[i].x() = x[i];
			(*points)[i].y() = y[i];
		}
	}

	delete[] x;
	delete[] y;

	return success;
}

bool SpatialReference::transformPoints(
					 const SpatialReference* to_srs,
					 osg::Vec3dArray* points,
					 bool ignore_errors) const
{
	if (isEquivalentTo(to_srs)) return true;

	int numPoints = points->size();
	double* x = new double[numPoints];
	double* y = new double[numPoints];

	for( int i=0; i<numPoints; i++ )
	{
		x[i] = (*points)[i].x();
		y[i] = (*points)[i].y();
	}

	bool success = transformPoints( to_srs, x, y, numPoints, ignore_errors );

	if ( success )
	{
		for( int i=0; i<numPoints; i++ )
		{
			(*points)[i].x() = x[i];
			(*points)[i].y() = y[i];
		}
	}

	delete[] x;
	delete[] y;

	return success;
}

bool SpatialReference::transformExtent(
					 const SpatialReference* to_srs,
					 double& in_out_xmin, double& in_out_ymin,
					 double& in_out_xmax, double& in_out_ymax) const
{
	int oks = 0;


	//Transform all points and take the maximum bounding rectangle the resulting points
	double llx, lly;
	double ulx, uly;
	double urx, ury;
	double lrx, lry;

	//Lower Left
	oks += transform( in_out_xmin, in_out_ymin, to_srs, llx, lly ) == true;

	//Upper Left
	oks += transform( in_out_xmin, in_out_ymax, to_srs, ulx, uly ) == true;

	//Upper Right
	oks += transform( in_out_xmax, in_out_ymax, to_srs, urx, ury ) == true;

	//Lower Right
	oks += transform( in_out_xmax, in_out_ymin, to_srs, lrx, lry ) == true;


	if (oks == 4)
	{
		in_out_xmin = osg::minimum(llx, ulx);
		in_out_xmax = osg::maximum(lrx, urx);
		in_out_ymin = osg::minimum(lly, lry);
		in_out_ymax = osg::maximum(uly, ury);
		return true;
	}
	return false;
}

bool SpatialReference::transformExtentPoints(
						   const SpatialReference* to_srs,
						   double in_xmin, double in_ymin,
						   double in_xmax, double in_ymax,
						   double* x, double *y,
						   unsigned int numx, unsigned int numy,
						   bool ignore_errors) const
{
	const double dx = (in_xmax - in_xmin) / (numx - 1);
	const double dy = (in_ymax - in_ymin) / (numy - 1);

	unsigned int pixel = 0;
	double fc = 0.0;
	for (unsigned int c = 0; c < numx; ++c, ++fc)
	{
		const double dest_x = in_xmin + fc * dx;
		double fr = 0.0;
		for (unsigned int r = 0; r < numy; ++r, ++fr)
		{
			const double dest_y = in_ymin + fr * dy;

			x[pixel] = dest_x;
			y[pixel] = dest_y;
			pixel++;     
		}
	}
	return transformPoints(to_srs, x, y, numx * numy, ignore_errors);
}

SpatialReference::SpatialReference( void* handle, const std::string& type, const std::string& init_str, const std::string& name ) :
	osg::Referenced( true ),_inittype(type),_initstring(init_str),_name(name),_handle(handle)
{
	;
}

SpatialReference::~SpatialReference()
{
	if ( _handle)
	{
		//GDAL_SCOPED_LOCK;

		for (TransformHandleCache::iterator itr = _transformHandleCache.begin(); itr != _transformHandleCache.end(); ++itr)
		{
			OCTDestroyCoordinateTransformation(itr->second);
		}
		OSRDestroySpatialReference( _handle );
	}
	_handle = NULL;
}

void SpatialReference::Init()
{
	//GDAL_SCOPED_LOCK;
	_bGeographic = OSRIsGeographic( _handle ) != 0;

	int err;
	double semi_major_axis = OSRGetSemiMajor( _handle, &err );
	double semi_minor_axis = OSRGetSemiMinor( _handle, &err );
	_ellipsoidmodel = new osg::EllipsoidModel( semi_major_axis, semi_minor_axis );

	if ( _name.empty() || _name == "unnamed" )
	{
		_name = _bGeographic? 
			getOGRAttrValue( _handle, "GEOGCS", 0 ) : 
		getOGRAttrValue( _handle, "PROJCS", 0 );
	}

}


void SpatialReference::read(const Config& config)
{
	//TODO
}

void SpatialReference::write(Config& config) const
{
	//TODO
}