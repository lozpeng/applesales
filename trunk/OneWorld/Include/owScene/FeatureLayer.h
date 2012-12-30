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
	/** ʸ���㣬�ڲ����м̳в�ʵ��createNode���������ش�����ģ�ͽڵ㡣��Ҫע������ο�createNode
	* ����˵��*/
	class OWSCENE_EXPORT FeatureLayer : public Layer
	{
	public:
		FeatureLayer();
		FeatureLayer(const FeatureLayer& lyr, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		FeatureSource* getFeatureSource();

		/** ����FeatureNode�ļ��Ͻڵ㣬�˷����й���Ϊ����������tile��Χ��ѯ����ʸ����¼��������ʸ����¼
		* ����createNode����������ģ�ͽڵ㣬��new FeatureNode�ڵ㣬�Ѵ�������ģ�ͽڵ����FeatureNode
		* �У��ٰ�FeatureNode���뵽FeatureGroupNode�ڵ��У������ء�FeatureGroupNode�ڵ����ջ����
		* ��TerrainTile�С�
		*/
		FeatureGroupNode* createFeatureGroupNode(const TerrainTile* tile,ProgressBase* p=NULL);

	public:

		/** ����������ʵ�֣�����ע����ǣ�f�а���������������tile�а�����ͶӰ����ͶӰת����ת��Ϊtile������ϵ*/
		virtual osg::Node* createNode(const TerrainTile* tile, Feature* f) = 0;

		virtual void read(const Config& config);
		virtual void write(Config& config);

		///�߿�
		float GetLineWidth() const {return _line_width;}
		bool SetLineWidth(float line_width) { _line_width = line_width; return true;}

		///��ɫ
		const osg::Vec4 GetColor() const {return _color;}
		bool SetColor(const osg::Vec4 color) { _color = color; return true;}

		///̧�߸߶�
		float GetHeightOff() const {return _height_off;}
		bool SetRunUpHeight(float height_off) { _height_off = height_off; return false;}


	protected:

		virtual ~FeatureLayer(){}

	protected:

		//�߿�
		float _line_width;

		//��ɫ
		osg::Vec4 _color;

		//����̧��
		float _height_off;

		//���ŵ���
		bool _on_ground;

	};
}

#endif //OWSCENE_FEATURELAYER_H_