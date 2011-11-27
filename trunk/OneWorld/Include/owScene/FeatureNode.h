#ifndef _OWSCENE_FEATURENODE_H_
#define _OWSCENE_FEATURENODE_H_

#include <owScene/export.h>
#include <owScene/FeatureLayer.h>
#include <owScene/Feature.h>
#include <osg/Group>

using namespace osg;
using namespace owScene;

namespace owScene
{
	class FeatureGroupNode;
	/** 该类在FeatureLayer中创建，包含一个矢量记录的id，该节点作为子节点挂在FeatureGroupNode中，FeatureGroupNode
	 * 挂在TerrainTile中。
	 * FeatureNode包含了从插件中创建出的实际模型节点*/
	class OWSCENE_EXPORT FeatureNode : public osg::Group
	{
	public:

		FeatureNode(){}
		
		FeatureNode(const FeatureNode&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,FeatureNode);

	public:

		void setFeature(Feature* f) { _feature=f; }
		Feature* getFeature() { return _feature; }

		void setParentLayer(FeatureLayer* layer) { _parentLayer=layer;}
		FeatureLayer* getParentLayer() { return _parentLayer.get(); }

		FeatureGroupNode* getParentFeatureGroupNode();

	public:

		virtual void traverse(NodeVisitor& nv);

	protected:
		
		~FeatureNode(){}

	private:

		osg::ref_ptr<Feature> _feature;
		osg::ref_ptr<FeatureLayer> _parentLayer;
	
	};

	typedef std::vector<osg::ref_ptr<FeatureNode>> FeatureNodeList;

	/** FeatureGroupNode节点包含了若干的FeatureNode节点。FeatureGroupNode最终挂在TerrainTile中。
	*/
	class OWSCENE_EXPORT FeatureGroupNode : public osg::Group
	{
	public:
		FeatureGroupNode(){;}
		FeatureGroupNode(const FeatureGroupNode& fgn, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,FeatureGroupNode);

	public:

		/** 添加FeatureNode*/
		void addFeatureNode(FeatureNode* fn);

		/** 删除FeatureNode*/
		void removeFeatureNode(FeatureNode* fn);

		/** 获得FeatureNode数目*/
		unsigned int getNumOfFeatureNode();

		/** 获得FeatureNode*/
		FeatureNode* getFeatureNode(unsigned int index);

		FeatureNode* getFeatureNode(FeatureOID id);

	protected:
		~FeatureGroupNode(){;}

	private:

		FeatureNodeList _featurelist;	
	};
}

#endif //_OWSCENE_FEATURENODE_H_