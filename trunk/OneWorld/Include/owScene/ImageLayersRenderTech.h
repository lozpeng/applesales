#ifndef GVTERRAIN_IMAGELAYERRENDERTECH_H_
#define GVTERRAIN_IMAGELAYERRENDERTECH_H_

#include <owScene/export.h>
#include <owScene/TerrainRenderTech.h>
#include <osg/Texture2D>
#include <osg/Texture2DArray>

namespace owScene
{
	/** ”∞œÒ‰÷»æºº ı*/
	class OWSCENE_EXPORT ImageLayersRenderTech : public TerrainRenderTech
	{
	public:
		enum Type
	   {
		   AUTO,
		   TEXTURE2D,
		   TEXTURE2DARRAY
	   };
		ImageLayersRenderTech(const Type type=ImageLayersRenderTech::AUTO);

		ImageLayersRenderTech(const ImageLayersRenderTech&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Object(owScene,ImageLayersRenderTech);

		
	public:

		void applyTexture(osg::Geometry* geometry, 
			std::vector<osg::ref_ptr<osg::Image>>& imglist);

	private:

		void init();
		void init2D();
		
		Type _type;
		
		osg::Texture2D* createTexture2D(osg::ref_ptr<osg::Image>& img);
		osg::Texture2DArray* createTexture2DArray(std::vector<osg::ref_ptr<osg::Image>>& imglist);

	};
}
#endif //GVTERRAIN_IMAGELAYERRENDERTECH_H_