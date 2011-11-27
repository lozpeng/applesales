#include <owScene/PreRenderGroup.h>
#include <owUtil/OperateDuringUpdate.h>

#include <osg/Hint>

namespace owScene
{
	struct CameraFinalDrawCallback : public osg::Camera::DrawCallback
	{
		CameraFinalDrawCallback(){}

		virtual void operator () (const osg::Camera& camera) const
		{
			getGlobalPreRenderGroup()->removeCamera((osg::Camera*)&camera);
		}
	};

	PreRenderGroup::PreRenderGroup()
	{

	}

	void PreRenderGroup::addCamera(osg::Camera* camera)
	{
		if(!camera)
			return;

		owUtil::AddChildToParentDuringUpdate(camera,this);
	}

	void PreRenderGroup::removeCamera(osg::Camera* camera)
	{
		if(!camera)
			return;

		owUtil::RemoveChildFromParentDuringUpdate(camera,this);
	}

	osg::Camera* PreRenderGroup::createCamera(osg::Image* image, const GeoExtent* extent, int tilesize) const
	{
		osg::Camera* camera = new osg::Camera;

		// set up the background color and clear mask.
		camera->setClearColor(osg::Vec4(1.0f,1.0f,1.0f, 0.0f));
		camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// set the camera to render before the main camera.
		camera->setRenderOrder(osg::Camera::PRE_RENDER);

		// set up projection.
		camera->setProjectionMatrixAsOrtho2D(extent->xMin(), extent->xMax(), extent->yMin(), extent->yMax());

		// set viewport
		camera->setViewport(0, 0, tilesize, tilesize);

		// set view
		camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF_INHERIT_VIEWPOINT);
		camera->setViewMatrix(osg::Matrix::identity());

		// tell the camera to use OpenGL frame buffer object where supported.
		camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);

		// attach the image so its copied on each frame.
		camera->attach(osg::Camera::COLOR_BUFFER, image);

		//
		osg::StateSet *state = camera->getOrCreateStateSet();
		osg::ref_ptr<osg::Hint> hint = new osg::Hint(GL_LINE_SMOOTH_HINT, GL_NICEST);	
		state->setAttribute(hint.get(), osg::StateAttribute::ON);
		state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		camera->setFinalDrawCallback(new CameraFinalDrawCallback());
		return camera;
	}

	osg::ref_ptr<PreRenderGroup> prerendergroup_ptr;

	PreRenderGroup* getGlobalPreRenderGroup()
	{
		if(!prerendergroup_ptr.valid())
		{
			prerendergroup_ptr = new PreRenderGroup();
			prerendergroup_ptr->getOrCreateStateSet()->setRenderBinDetails(-1, "RenderBin");
		}

		return prerendergroup_ptr.get();
	}
}