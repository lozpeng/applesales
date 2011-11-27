#ifndef OWSCENE_IMAGEPROXY_H_
#define OWSCENE_IMAGEPROXY_H_

#include <owScene/export.h>

#include <osg/Image>

namespace owScene
{
	/**Image代理类，包含一个osg::Image对象。*/
	class OWSCENE_EXPORT ImageProxy : public osg::Referenced
	{
	public:
		ImageProxy(){;}
		ImageProxy(osg::Image* image) : _image(image) { }
		~ImageProxy(){}

	public:

		void set(osg::Image* image) { _image = image;}
		
		osg::Image* get() { return _image.get(); }

		bool valid() { return _image.valid(); }


	private:

		osg::ref_ptr<osg::Image> _image;
	};
}

#endif //OWSCENE_IMAGEPROXY_H_