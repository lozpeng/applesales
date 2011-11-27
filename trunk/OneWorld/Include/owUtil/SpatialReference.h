#ifndef owUtil_SPATIALREFERENCE_H_
#define owUtil_SPATIALREFERENCE_H_

#include <owUtil/export.h>
#include <owUtil/SpatialReference.h>
#include <owUtil/config.h>
#include <osg/CoordinateSystemNode>
#include <OpenThreads/Mutex>
#include <map>

namespace owUtil
{
	class OWUTIL_EXPORT SpatialReference : public osg::Referenced
	{
	public:
		static SpatialReference* create( const std::string& init );
		static SpatialReference* create( osg::CoordinateSystemNode* csn );

	public:

		const std::string& getName() const;
		const std::string& getInitString() const;
		const std::string& getInitType() const;
		const osg::EllipsoidModel* getEllipsoid() const;
		bool isGeographic() const;
		bool isProjected() const;
		bool isEquivalentTo( const SpatialReference* rhs ) const;

	public:

		bool transform(
			double x, double y,
			const SpatialReference* to_srs,
			double& out_x, double& out_y) const;

		bool transformPoints(
			const SpatialReference* to_srs, 
			double* x, double *y,
			unsigned int numPoints,
			bool ignore_errors =false) const;

		bool transformPoints(
			const SpatialReference* to_srs,
			osg::Vec3dArray* points,
			bool ignore_errors =false) const;

		bool transformPoints(
			const SpatialReference* to_srs,
			std::vector<osg::Vec3d> *points,
			bool ignore_errors =false) const;

		bool transformExtent(
			const SpatialReference* to_srs,
			double& in_out_xmin, double& in_out_ymin,
			double& in_out_xmax, double& in_out_ymax) const;

		bool transformExtentPoints(
			const SpatialReference* to_srs,
			double in_xmin, double in_ymin,
			double in_xmax, double in_ymax,
			double* x, double *y,
			unsigned int numx, unsigned int numy,
			bool ignore_errors = false ) const;

	public:

		void read(const Config& config);
		void write(Config& config) const;

	private:

		typedef std::map<std::string,osg::ref_ptr<SpatialReference>> SpatialReferenceCache;
		static SpatialReferenceCache& getSpCache();

		typedef std::map<std::string,void*> TransformHandleCache;
		TransformHandleCache _transformHandleCache;

	private:

		static SpatialReference* createFromWKT(
			const std::string& wkt, const std::string& alias, const std::string& name ="" );

		static SpatialReference* createFromPROJ4(
			const std::string& proj4, const std::string& alias, const std::string& name ="" );

		void Init();

	protected:
		SpatialReference( void* handle, const std::string& type, const std::string& init_str, const std::string& name );
		~SpatialReference();

	private:

		osg::ref_ptr<osg::EllipsoidModel> _ellipsoidmodel;
		bool _bGeographic;
		std::string _initstring;
		std::string _inittype;
		std::string _name;
		void* _handle;
	};
}

#endif //owUtil_SPATIALREFERENCE_H_