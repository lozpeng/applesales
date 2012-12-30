#ifndef OWSCENE_FEATURELAYER_H_
#define OWSCENE_FEATURELAYER_H_

#include <owScene/export.h>
#include <owScene/Layer.h>
#include <owScene/FeatureSource.h>

using namespace owScene;

namespace owScene
{
	class Terrain;
	class TerrainTile;
	class FeatureGroupNode;
	/** 矢量层，在层插件中继承并实现createNode方法，返回创建的模型节点。需要注意事项参考createNode
	* 方法说明*/
	class OWSCENE_EXPORT FeatureLayer : public Layer
	{
	public:
		FeatureLayer();
		FeatureLayer(const FeatureLayer& lyr, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		FeatureSource* getFeatureSource();

		/** 构建FeatureNode的集合节点，此方法中功能为：遍历按照tile范围查询出的矢量记录，并根据矢量记录
		* 调用createNode方法创建出模型节点，再new FeatureNode节点，把创建出的模型节点加入FeatureNode
		* 中，再把FeatureNode加入到FeatureGroupNode节点中，并返回。FeatureGroupNode节点最终会加入
		* 到TerrainTile中。
		*/
		FeatureGroupNode* createFeatureGroupNode(const TerrainTile* tile,ProgressBase* p=NULL);

	public:

		/** 子类中重载实现，必须注意的是：f中包含的坐标必须采用tile中包含的投影进行投影转换，转换为tile的坐标系*/
		virtual osg::Node* createNode(const TerrainTile* tile, Feature* f) = 0;

		virtual void read(const Config& config);
		virtual void write(Config& config);

		///线宽
		float GetLineWidth() const {return _line_width;}
		bool SetLineWidth(float line_width) { _line_width = line_width; return true;}

		///颜色
		const osg::Vec4 GetColor() const {return _color;}
		bool SetColor(const osg::Vec4 color) { _color = color; return true;}

		///抬高高度
		float GetHeightOff() const {return _height_off;}
		bool SetRunUpHeight(float height_off) { _height_off = height_off; return false;}


	protected:

		virtual ~FeatureLayer(){}

	protected:

		//线宽
		float _line_width;

		//颜色
		osg::Vec4 _color;

		//字体抬高
		float _height_off;

		//贴着地面
		bool _on_ground;

	};
}

#endif //OWSCENE_FEATURELAYER_H_