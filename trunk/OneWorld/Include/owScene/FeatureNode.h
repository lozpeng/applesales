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
	/** ������FeatureLayer�д���������һ��ʸ����¼��id���ýڵ���Ϊ�ӽڵ����FeatureGroupNode�У�FeatureGroupNode
	 * ����TerrainTile�С�
	 * FeatureNode�����˴Ӳ���д�������ʵ��ģ�ͽڵ�*/
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

	/** FeatureGroupNode�ڵ���������ɵ�FeatureNode�ڵ㡣FeatureGroupNode���չ���TerrainTile�С�
	*/
	class OWSCENE_EXPORT FeatureGroupNode : public osg::Group
	{
	public:
		FeatureGroupNode(){;}
		FeatureGroupNode(const FeatureGroupNode& fgn, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,FeatureGroupNode);

	public:

		/** ���FeatureNode*/
		void addFeatureNode(FeatureNode* fn);

		/** ɾ��FeatureNode*/
		void removeFeatureNode(FeatureNode* fn);

		/** ���FeatureNode��Ŀ*/
		unsigned int getNumOfFeatureNode();

		/** ���FeatureNode*/
		FeatureNode* getFeatureNode(unsigned int index);

		FeatureNode* getFeatureNode(FeatureOID id);

	protected:
		~FeatureGroupNode(){;}

	private:

		FeatureNodeList _featurelist;	
	};
}

#endif //_OWSCENE_FEATURENODE_H_