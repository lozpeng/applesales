#ifndef OWSCENE_RASTERSOURCE_H_
#define OWSCENE_RASTERSOURCE_H_

#include <owScene/export.h>
#include <owUtil/DataSource.h>
#include <owUtil/ProgressBase.h>
#include <owUtil/config.h>
#include <osg/Image>
#include <owScene/Height.h>

using namespace owUtil;

namespace owScene
{
	/** 栅格数据源*/
	class OWSCENE_EXPORT RasterSource : public DataSource
	{
	public:
		RasterSource();

		virtual Height* CreatHeight(const SpatialProperty* sp,unsigned int size,ProgressBase* p=NULL) = 0;

		virtual osg::Image* CreateImage(const SpatialProperty* sp,unsigned int size,ProgressBase* p=NULL) = 0;

	public:

		virtual void read(const Config& config)
		{
			DataSource::read(config);

			//TODO
		}

		virtual void write(Config& config) const
		{
			DataSource::write(config);

			//TODO
		}

	protected:
		virtual ~RasterSource();
	};
}

#endif //OWSCENE_RASTERSOURCE_H_