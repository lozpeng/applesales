#ifndef GSTERRAIN_AUTOCLIPPLANEHANDLER_H
#define GSTERRAIN_AUTOCLIPPLANEHANDLER_H

#include <owNavi/export.h>
#include <owScene/Terrain.h>
#include <osgGA/GUIEventHandler>
#include <osgGA/EventVisitor>

using namespace owScene;

namespace owNavi
{
	/**
	* An event handler that automatically calculates optimal near and
	* far clip planes for a geocentric map node. Just add this to your
	* main Viewer and go.
	*
	* This only works properly for geocentric (round earth) maps.
	*/
	class OWNAVI_EXPORT AutoClipPlaneHandler : public osgGA::GUIEventHandler
	{
	public:
		/**
		* Constructs a new clip plane handler.
		*/
		AutoClipPlaneHandler(Terrain* terrain);

		/**
		* Whether to automatically set the far clip to the horizon. default=true.
		*/
		void setAutoFarPlaneClipping(bool enabled) { _autoFarPlaneClipping = enabled; }
		bool getAutoFarPlaneClipping() const { return _autoFarPlaneClipping; }


	public: // EventHandler

		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );

		void frame( osgGA::GUIActionAdapter& aa );

	private:

		osg::ref_ptr<Terrain> _terrain;
		bool _geocentric;
		int _frame;
		double _nfrAtRadius, _nfrAtDoubleRadius, _rp;
		bool _autoFarPlaneClipping;
	};


	class OWNAVI_EXPORT AutoClipPlaneCallback : public osg::NodeCallback
	{
	public:
		AutoClipPlaneCallback(Terrain* terrain)
		{
			_handler = new AutoClipPlaneHandler( terrain );
		}

		virtual void operator()( osg::Node* node, osg::NodeVisitor* nv )
		{
			osgGA::EventVisitor* ev = dynamic_cast<osgGA::EventVisitor*>( nv );
			if ( ev ) {
				_handler->frame( *ev->getActionAdapter() );
			}
			traverse( node, nv );
		}

		osg::ref_ptr<AutoClipPlaneHandler> _handler;
	};

}

#endif // GSUTIL_AUTOCLIPPLANEHANDLER_H

