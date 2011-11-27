
#include <owNavi/selectHandler.h>
#include <osgViewer/Viewer>
#include <owScene/FeatureNode.h>

using namespace owNavi;

SelNodeHandler::SelNodeHandler()
{

}

SelNodeHandler::~SelNodeHandler()
{
	;
}

bool SelNodeHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if(!_enable)
		return false;

	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::PUSH):
		{
			switch(ea.getButton())
			{
			case(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON):
				{
					osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
					if (!view) return false;

					//////////////////////////////////////////////////////////////////////////

					double mx = ea.getXnormalized();
					double my = ea.getYnormalized();
					double w = 0.05;
					double h = 0.05;
					osgUtil::PolytopeIntersector*  picker = new osgUtil::PolytopeIntersector( osgUtil::Intersector::PROJECTION, mx-w, my-h, mx+w, my+h );

					osgUtil::IntersectionVisitor iv(picker);

					view->getCamera()->accept(iv);

					if (picker->containsIntersections())
					{
						osgUtil::PolytopeIntersector::Intersection intersection = picker->getFirstIntersection();

						osg::NodePath& nodePath = intersection.nodePath;

						osg::NodePath::iterator iter_p = nodePath.begin();
						for(iter_p;iter_p!=nodePath.end();++iter_p)
						{
							owScene::FeatureNode* fn = dynamic_cast<owScene::FeatureNode*>(*iter_p);
							if(fn)
							{
								owScene::Feature* f = fn->getFeature();
								if(f)
								{
									std::cout<<std::endl;
									std::cout<<"Start List FeatureOID: "<<f->getOID()<<" AttributeList: "<<std::endl;
									owScene::AttributeList list = f->getAttributes();
									owScene::AttributeList::iterator iter = list.begin();
									for(iter;iter!=list.end();++iter)
									{
										owScene::Attribute atr = *iter;
										std::cout<<atr.getKey()<<" : "<<atr.asString()<<std::endl;
									}
									std::cout<<"End List FeatureOID: "<<f->getOID()<<" AttributeList: "<<std::endl;
									std::cout<<std::endl;
								}
								break;
							}
						}


					}
					//////////////////////////////////////////////////////////////////////////

					break;
				}
			default:
				break;
			}
			return false;
		}
	default:
		return false;
	}
	return false;
}