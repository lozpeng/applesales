#ifndef _OWNAVI_SELECTHANDLER_H
#define _OWNAVI_SELECTHANDLER_H

#include <owNavi/export.h>
#include <osgGA/GUIEventHandler>

namespace owNavi
{
	class OWNAVI_EXPORT BaseHandler : public osgGA::GUIEventHandler
	{
	public:
		BaseHandler() : _enable(true){;}
		~BaseHandler(){;}

		virtual void setEnable(bool b) { _enable=b;}
		bool getEnable() { return _enable;}

	protected:

		bool _enable;
	};

	class OWNAVI_EXPORT SelNodeHandler : public BaseHandler
	{
	public:
		SelNodeHandler();
		~SelNodeHandler();

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	};

}

#endif
