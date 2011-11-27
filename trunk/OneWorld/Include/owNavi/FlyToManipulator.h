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
		//操作方式适用类型
		enum ManipulatorType
		{
			//全球
			GLOBAL,
			//平面
			PLANE
		};

		//操作方式的构造函数 from---初始视矩阵 to---目标视矩阵 terrain---地形 type---操作方式类型 tframe---控制点个数 fovy---飞行曲线的最高点与两个关键点的夹角
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

		//是否需要使用飞行操作方式
		bool bNeedFly(){ return _needfly;}

		//记录飞行前的操作方式
		//void SetTerrainManipulator(gvNavigation::TerrainManipulator* terrainmanipulator){_terrainmanipulator = terrainmanipulator;}

		//gvNavigation::TerrainManipulator* GetTerrainManipulator(){return _terrainmanipulator.get();}

		void SetManipulator(osgGA::CameraManipulator* matrixmanipulator){_matrixmanipulator = matrixmanipulator;}

		osgGA::CameraManipulator* GetManipulator(){return _matrixmanipulator.get();}

	private:

		//曲线参数方程的参数
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

		//放弃原有的osg::AnimationPath中的getInterpolatedControlPoint方法,计算某个时间点的相机精确位置以及姿态。
		//time---时间点  controlPoint---返回的飞行路径控制点
		bool getcontrolpoint(double time,osg::AnimationPath::ControlPoint& controlPoint);

		//根据构造函数的矩阵参数来计算到规划飞行路径过程中需要的各种参数 from---初始状态相机视矩阵 to---目标状态相机视矩阵 
		void computeparameter(osg::Matrix &from,osg::Matrix &to);

		//构建飞行路径
		bool generatepath();

		//构建2次曲线 _keypoints---关键点 _distance---曲线上最大高度 points---构建的曲线点集 curveparameter---曲线方程的参数 
		bool generatepoints(std::vector<osg::Vec3d> &_keypoints,double _distance,std::vector<osg::Vec3d> &points,CURVEPARAMETER &curveparameter);

		//从球心坐标转化到经纬度投影坐标 points---待转化的点集合
		bool  tarnsformfromgeocentric(std::vector<osg::Vec3d> &poins);

		//从经纬度投影坐标转化到球心坐标 points---待转化的点集合
		bool  tarnsformtogeocentric(std::vector<osg::Vec3d> &poins);

		//使用微积分计算时间 curveparameter---曲线参数
		bool computeratios(CURVEPARAMETER &curveparameter);

		//计算飞行路径控制点姿态 eyes---控制点位置集合 targets---目标点集合 quats---姿态集合
		bool computequats(std::vector<osg::Vec3d> &eyes,std::vector<osg::Vec3d> &targets,std::vector<osg::Quat> &quats);

		//计算飞行路径控制点上的时间 time---时间集合
		bool computetime(std::vector<float> &time);

		//为了限制总飞行时间的大小,引入了该方法.
		//alltime---总飞行时间 time---控制点时间集合
		bool computeenoughtime(float alltime,std::vector<float> &time);

		//计算曲线上相邻点间的平均高程,从而获得平均速度 from---第一点的参数方程变量 to---第二点的参数方程变量 curveparameter---曲线参数方程参数集
		double computespeed(float from,float to,CURVEPARAMETER &curveparameter);

		//计算曲线上相邻点间的曲线长度 from---第一点的参数方程变量 to---第二点的参数方程变量 curveparameter---曲线参数方程参数集
		double computedistance(float from,float to,CURVEPARAMETER &curveparameter);

		//计算飞行路径控制点姿态 eye---控制点位置 center---控制点目标点 up---up向量
		osg::Quat computequat(osg::Vec3d &eye,osg::Vec3d &center,osg::Vec3d &up);

		//空间向量绕任意轴旋转，返回结果向量  v---旋转向量 n---轴 angle---旋转角度
		osg::Vec3d RotateAroudAnyVector(osg::Vec3d v,osg::Vec3d n,float angle);

		//获取线段与地形的交点 spoint---第一个端点 epoint---第二个端点
		osg::Vec3d getIntersectpoint(osg::Vec3d spoint,osg::Vec3d epoint);

		//判断起始和目标飞行路径控制点之间是否相距太近,根据这一结果在相关地方使用不同的计算方式.
		void istoonear();

		//返回飞行之前的操作方式 matrix---视距阵
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

		//视点位置集合
		std::vector<osg::Vec3d> _eyes;
		//目标点位置集合
		std::vector<osg::Vec3d> _centers;
		//地形上目标点位置集合
		std::vector<osg::Vec3d> _targets;
		//视点姿态集合
		std::vector<osg::Quat> _quats;
		//视点up向量集合
		std::vector<osg::Vec3d> _ups;
		//地形
		//owScene::Terrain* _terrain;
		owScene::Layer* _layer;
		//飞行曲线的最高点与两个关键点的夹角,用于确定顶点高程.
		float _angle;
		//速度和高度之间的系数
		float _k;
		//视点曲线和目标点曲线的参数
		CURVEPARAMETER _eyecurvepara,_targetcurvepara;
		//记录当前viewer对象
		osgViewer::View* _view;
		//操作方式的类型
		ManipulatorType  _manitype;
		//比率总和
		double _ratiocount ;
		//曲线长度与平均高度的比率集合
		std::vector<double> _ratios;
		//曲线取点数量
		int _tframe;
		//标识视点之见是否很近
		bool _toonear;
		//是否需要飞行
		bool _needfly;
		//之前的操作方式
		/*	osg::ref_ptr<gvNavigation::TerrainManipulator> _terrainmanipulator;*/
		osg::ref_ptr<osgGA::CameraManipulator> _matrixmanipulator;

		//执行一次
		bool bonce;
	};

	void OWNAVI_EXPORT FlyTo(osgViewer::View* view,owScene::Layer* layer,osg::Matrix &to);
}

#endif