#ifndef owUtil_SPATIALPROPERTY_H_
#define owUtil_SPATIALPROPERTY_H_

#include <owUtil/export.h>
#include <owUtil/GeoExtent.h>
#include <owUtil/SpatialReference.h>

namespace owUtil
{
	class OWUTIL_EXPORT SpatialProperty : public osg::Referenced
	{
	public:
		SpatialProperty();
		SpatialProperty(GeoExtent* e, SpatialReference* sp);
		~SpatialProperty();

	public:

		void setGeoExtent(GeoExtent* e);
		GeoExtent* getGeoExtent();
		const GeoExtent* getGeoExtent() const;

		void setSrs(SpatialReference* sp);
		SpatialReference* getSrs();
		const SpatialReference* getSrs() const;

		bool isValid();

	private:

		osg::ref_ptr<GeoExtent> _extent;
		osg::ref_ptr<SpatialReference> _sp;
	};
}
#endif //owUtil_SPATIALPROPERTY_H_