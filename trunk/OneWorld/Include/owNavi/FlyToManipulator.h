#ifndef GSTERRAIN_FLYTOMANIPULATOR_H_
#define GSTERRAIN_FLYTOMANIPULATOR_H_

#include <owNavi/Export.h>
#include <osg/AnimationPath>
#include <osgGA/CameraManipulator>
#include <osgViewer/Viewer>
#include <owScene/Layer.h>


namespace owNavi
{
	class OWNAVI_EXPORT  FlyToManipulator : public osgGA::CameraManipulator
	{
	public:
		//������ʽ��������
		enum ManipulatorType
		{
			//ȫ��
			GLOBAL,
			//ƽ��
			PLANE
		};

		//������ʽ�Ĺ��캯�� from---��ʼ�Ӿ��� to---Ŀ���Ӿ��� terrain---���� type---������ʽ���� tframe---���Ƶ���� fovy---�������ߵ���ߵ��������ؼ���ļн�
		FlyToManipulator(osg::Matrix &from,osg::Matrix &to,owScene::Layer* layer,ManipulatorType type = GLOBAL,int tframe = 150,float fovy = 60.0);

		virtual const char* className() const { return "FlyTo"; }

		void setPrintOutTimingInfo(bool printOutTimingInfo) { _printOutTimingInfo=printOutTimingInfo; }
		bool getPrintOutTimingInfo() const { return _printOutTimingInfo; }

		/** set the position of the matrix manipulator using a 4x4 Matrix.*/
		virtual void setByMatrix(const osg::Matrixd& matrix) { _matrix = matrix; }

		/** set the position of the matrix manipulator using a 4x4 Matrix.*/
		virtual void setByInverseMatrix(const osg::Matrixd& matrix) { _matrix.invert(matrix); }

		/** get the position of the manipulator as 4x4 Matrix.*/
		virtual osg::Matrixd getMatrix() const { return _matrix; }

		/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
		virtual osg::Matrixd getInverseMatrix() const { return osg::Matrixd::inverse(_matrix); } 


		//void setAnimationPath( osg::AnimationPath* animationPath ) { _animationPath=animationPath; }

		//osg::AnimationPath* getAnimationPath() { return _animationPath.get(); }

		//const osg::AnimationPath* getAnimationPath() const { return _animationPath.get(); }

		bool valid() const { return _animationPath.valid(); }

		void init(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);

		void home(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);
		void home(double currentTime);

		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);

		/** Get the keyboard and mouse usage of this manipulator.*/
		virtual void getUsage(osg::ApplicationUsage& usage) const;

		//�Ƿ���Ҫʹ�÷��в�����ʽ
		bool bNeedFly(){ return _needfly;}

		//��¼����ǰ�Ĳ�����ʽ
		//void SetTerrainManipulator(gvNavigation::TerrainManipulator* terrainmanipulator){_terrainmanipulator = terrainmanipulator;}

		//gvNavigation::TerrainManipulator* GetTerrainManipulator(){return _terrainmanipulator.get();}

		void SetManipulator(osgGA::CameraManipulator* matrixmanipulator){_matrixmanipulator = matrixmanipulator;}

		osgGA::CameraManipulator* GetManipulator(){return _matrixmanipulator.get();}

	private:

		//���߲������̵Ĳ���
		struct  CURVEPARAMETER
		{
			double _a;
			double _b;
			double _c;
			double _sx;
			double _cx;
			double _sy;
			double _cy ;
		};

		//����ԭ�е�osg::AnimationPath�е�getInterpolatedControlPoint����,����ĳ��ʱ���������ȷλ���Լ���̬��
		//time---ʱ���  controlPoint---���صķ���·�����Ƶ�
		bool getcontrolpoint(double time,osg::AnimationPath::ControlPoint& controlPoint);

		//���ݹ��캯���ľ�����������㵽�滮����·����������Ҫ�ĸ��ֲ��� from---��ʼ״̬����Ӿ��� to---Ŀ��״̬����Ӿ��� 
		void computeparameter(osg::Matrix &from,osg::Matrix &to);

		//��������·��
		bool generatepath();

		//����2������ _keypoints---�ؼ��� _distance---���������߶� points---���������ߵ㼯 curveparameter---���߷��̵Ĳ��� 
		bool generatepoints(std::vector<osg::Vec3d> &_keypoints,double _distance,std::vector<osg::Vec3d> &points,CURVEPARAMETER &curveparameter);

		//����������ת������γ��ͶӰ���� points---��ת���ĵ㼯��
		bool  tarnsformfromgeocentric(std::vector<osg::Vec3d> &poins);

		//�Ӿ�γ��ͶӰ����ת������������ points---��ת���ĵ㼯��
		bool  tarnsformtogeocentric(std::vector<osg::Vec3d> &poins);

		//ʹ��΢���ּ���ʱ�� curveparameter---���߲���
		bool computeratios(CURVEPARAMETER &curveparameter);

		//�������·�����Ƶ���̬ eyes---���Ƶ�λ�ü��� targets---Ŀ��㼯�� quats---��̬����
		bool computequats(std::vector<osg::Vec3d> &eyes,std::vector<osg::Vec3d> &targets,std::vector<osg::Quat> &quats);

		//�������·�����Ƶ��ϵ�ʱ�� time---ʱ�伯��
		bool computetime(std::vector<float> &time);

		//Ϊ�������ܷ���ʱ��Ĵ�С,�����˸÷���.
		//alltime---�ܷ���ʱ�� time---���Ƶ�ʱ�伯��
		bool computeenoughtime(float alltime,std::vector<float> &time);

		//�������������ڵ���ƽ���߳�,�Ӷ����ƽ���ٶ� from---��һ��Ĳ������̱��� to---�ڶ���Ĳ������̱��� curveparameter---���߲������̲�����
		double computespeed(float from,float to,CURVEPARAMETER &curveparameter);

		//�������������ڵ������߳��� from---��һ��Ĳ������̱��� to---�ڶ���Ĳ������̱��� curveparameter---���߲������̲�����
		double computedistance(float from,float to,CURVEPARAMETER &curveparameter);

		//�������·�����Ƶ���̬ eye---���Ƶ�λ�� center---���Ƶ�Ŀ��� up---up����
		osg::Quat computequat(osg::Vec3d &eye,osg::Vec3d &center,osg::Vec3d &up);

		//�ռ���������������ת�����ؽ������  v---��ת���� n---�� angle---��ת�Ƕ�
		osg::Vec3d RotateAroudAnyVector(osg::Vec3d v,osg::Vec3d n,float angle);

		//��ȡ�߶�����εĽ��� spoint---��һ���˵� epoint---�ڶ����˵�
		osg::Vec3d getIntersectpoint(osg::Vec3d spoint,osg::Vec3d epoint);

		//�ж���ʼ��Ŀ�����·�����Ƶ�֮���Ƿ����̫��,������һ�������صط�ʹ�ò�ͬ�ļ��㷽ʽ.
		void istoonear();

		//���ط���֮ǰ�Ĳ�����ʽ matrix---�Ӿ���
		void setoldcameramanipulator(osg::Matrix matrix);

	protected:

		bool _valid;

		bool _printOutTimingInfo;

		void handleFrame( double time );

		osg::ref_ptr<osg::AnimationPath> _animationPath;

		double  _timeOffset;
		double  _timeScale;
		double  _pauseTime;
		bool    _isPaused;

		double  _realStartOfTimedPeriod;
		double  _animStartOfTimedPeriod;
		int     _numOfFramesSinceStartOfTimedPeriod;

		osg::Matrixd _matrix;

		//�ӵ�λ�ü���
		std::vector<osg::Vec3d> _eyes;
		//Ŀ���λ�ü���
		std::vector<osg::Vec3d> _centers;
		//������Ŀ���λ�ü���
		std::vector<osg::Vec3d> _targets;
		//�ӵ���̬����
		std::vector<osg::Quat> _quats;
		//�ӵ�up��������
		std::vector<osg::Vec3d> _ups;
		//����
		//owScene::Terrain* _terrain;
		owScene::Layer* _layer;
		//�������ߵ���ߵ��������ؼ���ļн�,����ȷ������߳�.
		float _angle;
		//�ٶȺ͸߶�֮���ϵ��
		float _k;
		//�ӵ����ߺ�Ŀ������ߵĲ���
		CURVEPARAMETER _eyecurvepara,_targetcurvepara;
		//��¼��ǰviewer����
		osgViewer::View* _view;
		//������ʽ������
		ManipulatorType  _manitype;
		//�����ܺ�
		double _ratiocount ;
		//���߳�����ƽ���߶ȵı��ʼ���
		std::vector<double> _ratios;
		//����ȡ������
		int _tframe;
		//��ʶ�ӵ�֮���Ƿ�ܽ�
		bool _toonear;
		//�Ƿ���Ҫ����
		bool _needfly;
		//֮ǰ�Ĳ�����ʽ
		/*	osg::ref_ptr<gvNavigation::TerrainManipulator> _terrainmanipulator;*/
		osg::ref_ptr<osgGA::CameraManipulator> _matrixmanipulator;

		//ִ��һ��
		bool bonce;
	};

	void OWNAVI_EXPORT FlyTo(osgViewer::View* view,owScene::Layer* layer,osg::Matrix &to);
}

#endif