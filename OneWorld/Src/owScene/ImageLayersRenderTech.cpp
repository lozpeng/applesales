#include <owScene/ImageLayersRenderTech.h>
#include <owUtil/Capabilities.h>
#include <osgDB/FileUtils>

using namespace owScene;

ImageLayersRenderTech::ImageLayersRenderTech(const ImageLayersRenderTech::Type type):_type(type)
{
	if (_type == ImageLayersRenderTech::TEXTURE2DARRAY)
	{
		init();
	}
	else if(_type == ImageLayersRenderTech::TEXTURE2D)
	{
		init2D();
	}
	else
	{
		if (owUtil::Capabilities::Instance().supportsTextureArrays())//判断opengl是否支持texture2DArray
		{
			init();
		}
		else
		{
			init2D();
		}
	}
}

ImageLayersRenderTech::ImageLayersRenderTech(const ImageLayersRenderTech& tech,const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
:TerrainRenderTech(tech,copyop)
{

}

osg::Texture2D* ImageLayersRenderTech::createTexture2D(osg::ref_ptr<osg::Image>& img)
{
	osg::Texture2D* txt = new osg::Texture2D;
	txt->setDataVariance(osg::Object::DYNAMIC);

	osg::Image* image = img;
	image->setInternalTextureFormat(GL_RGBA);
	txt->setImage(image);
	txt->setName(image->getName());

	txt->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
	txt->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
	txt->setWrap( osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP_TO_EDGE );
	txt->setWrap( osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP_TO_EDGE );
	txt->setWrap( osg::Texture2D::WRAP_R, osg::Texture2D::CLAMP_TO_EDGE );

	return txt;
}
osg::Texture2DArray* ImageLayersRenderTech::createTexture2DArray(std::vector<osg::ref_ptr<osg::Image>>& imglist)
{
	osg::Texture2DArray* t2d = new osg::Texture2DArray ;
	t2d->setDataVariance(osg::Object::DYNAMIC);

	t2d->setTextureDepth(imglist.size());

	for (unsigned int i=0;i<imglist.size();i++)
	{
		osg::Image* image = imglist[i];
		image->setInternalTextureFormat(GL_RGBA);
		t2d->setImage(i, imglist[i].get());
	}

	t2d->setFilter(osg::Texture2DArray::MIN_FILTER, osg::Texture2DArray::LINEAR);
	t2d->setFilter(osg::Texture2DArray::MAG_FILTER, osg::Texture2DArray::LINEAR);
	t2d->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	t2d->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
	t2d->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);

	return t2d;
}

void ImageLayersRenderTech::applyTexture(osg::Geometry* geometry, 
										 std::vector<osg::ref_ptr<osg::Image>>& imglist)
{
	if (_type == ImageLayersRenderTech::TEXTURE2DARRAY)
	{
		geometry->getOrCreateStateSet()->setTextureAttribute(0, 
			createTexture2DArray(imglist), osg::StateAttribute::ON);
	}
	else if (_type == ImageLayersRenderTech::TEXTURE2D)
	{
		for (unsigned int i=0;i<imglist.size();i++)
		{
			geometry->getOrCreateStateSet()->setTextureAttributeAndModes(i,
				createTexture2D(imglist[i]),osg::StateAttribute::ON);
		}
	}
	else
	{
		if (owUtil::Capabilities::Instance().supportsTextureArrays())//判断opengl是否支持texture2DArray
		{
			geometry->getOrCreateStateSet()->setTextureAttribute(0, 
				createTexture2DArray(imglist), osg::StateAttribute::ON);
		}
		else
		{
			for (unsigned int i=0;i<imglist.size();i++)
			{
				geometry->getOrCreateStateSet()->setTextureAttributeAndModes(i,
					createTexture2D(imglist[i]),osg::StateAttribute::ON);
			}
		}
	}
}

void ImageLayersRenderTech::init()
{
	osg::Shader* fShader = new osg::Shader(osg::Shader::FRAGMENT);
	osg::Shader* vShader = new osg::Shader(osg::Shader::VERTEX);


	std::string strfrag = osgDB::findLibraryFile("shader\\texture.frag");
	fShader->loadShaderSourceFromFile(strfrag);

	std::string strvert = osgDB::findLibraryFile("shader\\texture.vert");
	vShader->loadShaderSourceFromFile(strvert);

	_program->addShader(fShader);
	_program->addShader(vShader);


	osg::Uniform* u = new osg::Uniform(osg::Uniform::SAMPLER_2D_ARRAY, "tex");
	_uniforms.push_back(u);



}

void ImageLayersRenderTech::init2D()
{

}