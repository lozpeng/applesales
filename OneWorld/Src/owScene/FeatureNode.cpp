#include <owScene/FeatureNode.h>
#include <osgUtil/UpdateVisitor>

using namespace owScene;

FeatureNode::FeatureNode(const FeatureNode& fn,const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
: Group(fn,copyop)
{

}

FeatureGroupNode* FeatureNode::getParentFeatureGroupNode()
{
	return dynamic_cast<FeatureGroupNode*>(getParent(0));
}

void FeatureNode::traverse(NodeVisitor& nv)
{
	osgUtil::UpdateVisitor* uv = dynamic_cast<osgUtil::UpdateVisitor*>(&nv);
	if(uv)
		return osg::Group::traverse(nv);
	return osg::Group::traverse(nv);
}

//////////////////////////////////////////////////////////////////////////FeatureGroupNode

FeatureGroupNode::FeatureGroupNode(const FeatureGroupNode& fgn, const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
: Group(fgn,copyop)
{

}

void FeatureGroupNode::addFeatureNode(FeatureNode* fn)
{
	if(!fn)
		return;
	setDataVariance(osg::Object::DYNAMIC);
	addChild(fn);
	_featurelist.push_back(fn);
}

void FeatureGroupNode::removeFeatureNode(FeatureNode* fn)
{
	if(!fn)
		return;
	setDataVariance(osg::Object::DYNAMIC);
	removeChild(fn);
	FeatureNodeList::iterator iter = _featurelist.begin();
	for(;iter!=_featurelist.end();++iter)
	{
		if(*iter==fn)
		{
			_featurelist.erase(iter);
			break;
		}
	}
}

unsigned int FeatureGroupNode::getNumOfFeatureNode()
{
	return _featurelist.size();
}

FeatureNode* FeatureGroupNode::getFeatureNode(unsigned int index)
{
	if(index>=_featurelist.size())
		return NULL;
	return _featurelist[index].get();
}

FeatureNode* FeatureGroupNode::getFeatureNode(FeatureOID id)
{
	FeatureNodeList::iterator iter = _featurelist.begin();
	for(;iter!=_featurelist.end();++iter)
	{
		if((*iter)->getFeature() && (*iter)->getFeature()->getOID()==id)
		{
			return (*iter).get();
		}
	}

	return NULL;
}