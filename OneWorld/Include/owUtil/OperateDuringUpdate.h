#ifndef owUtil_OPERATEDURINGUPDATE_H_
#define owUtil_OPERATEDURINGUPDATE_H_

#include <owUtil/export.h>
#include <osg/Node>
#include <osg/Group>

namespace owUtil
{
	void OWUTIL_EXPORT AddChildToParentDuringUpdate(osg::Node* child, osg::Group* parent);
	void OWUTIL_EXPORT RemoveChildFromParentDuringUpdate(osg::Node* child, osg::Group* parent);
	void OWUTIL_EXPORT ReplaceChildFromParentDuringUpdate(osg::Node* child, osg::Node* by, osg::Group* parent);
}

#endif //owUtil_OPERATEDURINGUPDATE_H_