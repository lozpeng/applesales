#ifndef OWPLUGINS_FEATURE_LABEL_LAYER_H_
#define OWPLUGINS_FEATURE_LABEL_LAYER_H_

#include <owScene/FeatureLayer.h>

using namespace owScene;

namespace owPlugins
{
	class FeatureLabelLayer : public FeatureLayer
	{
	public:
		FeatureLabelLayer();
		~FeatureLabelLayer();

		META_Object(owPlugins,FeatureLabelLayer)

	public:

		virtual osg::Node* createNode(const TerrainTile* tile, Feature* f);

		virtual void read(const Config& config);
		virtual void write(Config& config);

		virtual void setEnable(bool enable);
		virtual bool getEnable();

		virtual bool initialize(ProgressBase* base=NULL);
		virtual bool unInitialize(ProgressBase* base=NULL);

	public:

		enum LABELSIZEMODE
		{
			OBJECT_SIZE,
			SCREEN_SIZE
		};

		///标签字段名
		const std::string GetLabelKey() const {return _key;}
		bool SetLabelKey(const std::string key) { _key = key; return true;}

		LABELSIZEMODE GetLabelSizeMode() const {return _size_mode;}
		bool SetLabelSizeMode(LABELSIZEMODE mode) { _size_mode = mode; return true;}

		///文字大小
		float GetLabelSize() const {return _font_size;}
		bool SetLabelSize(float font_size) { _font_size = font_size; return true;}

	protected:

		FeatureLabelLayer(const FeatureLabelLayer& gl, const CopyOp& copyop = CopyOp::SHALLOW_COPY)
		{
			//not support
		}

	private:

		//数据源名称
		std::string _sourcename;

		//标注字体
		std::string _font_name;

		//标注字体大小
		float _font_size;

		//标注关键字段
		std::string _key;

		//标注大小模式
		LABELSIZEMODE _size_mode;

	
	};
}

#endif //OWPLUGINS_FEATURE_LABEL_LAYER_H_