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

		///��ǩ�ֶ���
		const std::string GetLabelKey() const {return _key;}
		bool SetLabelKey(const std::string key) { _key = key; return true;}

		LABELSIZEMODE GetLabelSizeMode() const {return _size_mode;}
		bool SetLabelSizeMode(LABELSIZEMODE mode) { _size_mode = mode; return true;}

		///���ִ�С
		float GetLabelSize() const {return _font_size;}
		bool SetLabelSize(float font_size) { _font_size = font_size; return true;}

	protected:

		FeatureLabelLayer(const FeatureLabelLayer& gl, const CopyOp& copyop = CopyOp::SHALLOW_COPY)
		{
			//not support
		}

	private:

		//����Դ����
		std::string _sourcename;

		//��ע����
		std::string _font_name;

		//��ע�����С
		float _font_size;

		//��ע�ؼ��ֶ�
		std::string _key;

		//��ע��Сģʽ
		LABELSIZEMODE _size_mode;

	
	};
}

#endif //OWPLUGINS_FEATURE_LABEL_LAYER_H_