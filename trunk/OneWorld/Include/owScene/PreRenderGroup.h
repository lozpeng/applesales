#ifndef _OWSCENE_PRERENDERGROUP_H_
#define _OWSCENE_PRERENDERGROUP_H_

#include <owScene/export.h>
#include <owUtil/GeoExtent.h>

#include <osg/Group>
#include <osg/Camera>
#include <osg/Image>

using namespace owUtil;

namespace owScene
{
	class OWSCENE_EXPORT PreRenderGroup : public osg::Group
	{
	public:
		PreRenderGroup();

		void addCamera(osg::Camera* camera);
		void removeCamera(osg::Camera* camera);

		osg::Camera* createCamera(osg::Image* image, const GeoExtent* extent, int tilesize) const;

	protected:
		virtual ~PreRenderGroup(){}
	};

	OWSCENE_EXPORT PreRenderGroup* getGlobalPreRenderGroup();
}
#endif //_OWSCENE_PRERENDERGROUP_H_