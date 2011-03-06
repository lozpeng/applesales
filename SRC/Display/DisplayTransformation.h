//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  9527
// 时间：  2008/11/27
// 描述：  坐标转换
//////////////////////////////////////////////////////////////////////

#ifndef _DisplayTransformation_h
#define _DisplayTransformation_h

#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
#include "Geometry.h"
#include "SystemUnit.h"

namespace Display
{

inline long DoubleToLong(double sum)
{
	if ( sum > 0 )
	{
		return (long)(sum+0.5);
	}
	else
	{
		return (long)(sum-0.5);
	}
};

class DISPLAY_DLL VIEW_POSITION
{
	friend class CDisplayTransformation;
public:

	/** 构造函数 
	*/
	VIEW_POSITION();
	VIEW_POSITION* operator = (const VIEW_POSITION& pos);

	double GetScale(){return m_dScale;};

	double GetMapScale(){return m_dMapScale;};

	double GetGeoCenterX(){return m_dGeoCenterX;};

	double GetGeoCenterY(){return m_dGeoCenterY;};

	DIS_BOUND GetViewBound(){return m_displayBound;};

	GEOMETRY::geom::Envelope GetViewExtent();

private:
	double	m_dScale;/** 像素比例尺（不考虑单位：地理范围数量/像素数量,一个像素对应一个地图单位）*/
	double  m_dMapScale;/** 地图比例尺（考虑单位：（地理范围数量*mm/mapUnit）/（像素数量*mm/pixelUnit））*/
	double	m_dGeoCenterX,m_dGeoCenterY;/** 中心点X地理坐标、中心点Y地理坐标*/
	DIS_BOUND	m_displayBound; /**屏幕显示范围*/

};

class DISPLAY_DLL CDisplayTransformation
{
public:
	CDisplayTransformation();
	~CDisplayTransformation();

public:

	/**
	* 得到当前视图的坐标范围
	* @bound
	*/
	void GetGeoBound(GEOMETRY::geom::Envelope &bound);

	/**
	* 得到视图参数
	* @return 返回视图参数
	*/
	VIEW_POSITION& GetViewPosition();

	void SetViewPosition(VIEW_POSITION pos);

	void SetMapScale(double mapScale);
	double GetMapScale();

	void SetScale(double scale);
	double GetScale();
	

	double GetGeoCenterX();
	void SetGeoCenterX(double x);

	double GetGeoCenterY();
	void SetGeoCenterY(double y);

	DIS_BOUND GetViewBound();
	void SetViewBound(DIS_BOUND bound);
	void SetViewBound(const long left, const long right, const long top, const long bottom);

	void MoveViewBound(double OffsetX, double OffsetY);

	void SetReferenceScale(double refScale); 
	double GetReferenceScale();


	



	/** 
	*描述  :   注册视窗显示范围改变的回调函数
	*参数  :   boost::function fun函数对象
	*返回类型  :  boost::signals::connection 信号连接对象
	*/
	static boost::signals::connection RegisterChangeViewPos(boost::function<void (VIEW_POSITION)> fun);


	/**
	* 将地理坐标转变为屏幕显示坐标
	* @param x 地理坐标X
	* @param y 地理坐标Y
	* @param px_x 屏幕坐标X
	* @param px_y 屏幕坐标Y
	*/
	void ConvertGeoToDisplay( double x, double y, long &px_x, long &px_y)
	{
		px_x = DoubleToLong((x - m_viewPositon.m_dGeoCenterX)/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0);
		px_y = DoubleToLong((m_viewPositon.m_dGeoCenterY-y)/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0);
	}

	/**
	* 将屏幕显示坐标转变为地理坐标
	* @param px_x 屏幕坐标X
	* @param px_y 屏幕坐标Y
	* @param x 地理坐标X
	* @param y 地理坐标Y
	*/
	void ConvertGeoToDisplay( double x, long &px_x )
	{
		px_x = DoubleToLong(x/m_viewPositon.m_dScale);
	}

	/**
	* 将屏幕显示坐标转变为地理坐标
	* @param px_x 屏幕坐标X
	* @param px_y 屏幕坐标Y
	* @param x 地理坐标X
	* @param y 地理坐标Y
	*/
	void ConvertDisplayToGeo( long px_x, long px_y, double &x, double &y )
	{
		x = (px_x-(m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0)*m_viewPositon.m_dScale+m_viewPositon.m_dGeoCenterX;
		y = ((m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0-px_y)*m_viewPositon.m_dScale+m_viewPositon.m_dGeoCenterY;
	}

	/**
	* 将屏幕显示坐标转变为地理坐标
	* @param px_x 屏幕坐标X
	* @param px_y 屏幕坐标Y
	* @param x 地理坐标X
	* @param y 地理坐标Y
	*/
	void ConvertDisplayToGeo( long px_x, long px_y, GEOMETRY::geom::Coordinate& coord )
	{
		coord.x = (px_x-(m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0)*m_viewPositon.m_dScale+m_viewPositon.m_dGeoCenterX;
		coord.y = ((m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0-px_y)*m_viewPositon.m_dScale+m_viewPositon.m_dGeoCenterY;
	}

	/**
	* 将屏幕显示坐标转变为地理坐标
	* @param px_x 屏幕坐标X
	* @param px_y 屏幕坐标Y
	* @param x 地理坐标X
	* @param y 地理坐标Y
	*/
	void ConvertDisplayToGeo( long px_x, double &x)
	{
		x = px_x*m_viewPositon.m_dScale;
	}

	/**
	* 地理点坐标向屏幕坐标转换
	* @param pEnvelope 文字所在地理坐标
	* @param strText 文字内容
	* @return 返回屏幕点坐标
	*/
	DIS_TEXT* TransformToDisplay(const GEOMETRY::geom::Envelope* pEnvelope,  const std::string strText);


	/**
	* 地理点坐标向屏幕坐标转换
	* @param pPoint 地理点坐标
	* @return 返回屏幕点坐标
	*/
	DIS_POINT* TransformToDisplay(const GEOMETRY::geom::Point *pPoint);

	/**
	* 地理线坐标向屏幕坐标转换
	* @param pLine 地理线坐标

	* @return 返回屏幕线坐标
	*/
	DIS_LINE* TransformToDisplay(const GEOMETRY::geom::LineString* pLine);

	/**
	* 地理多边形转换成屏幕坐标
	* @param pPolygon 地理多边形
	* @return 返回屏幕多边形
	*/
	DIS_POLYGON* TransformToDisplay(const GEOMETRY::geom::Polygon* pPolygon);

	/**
	* 地理坐标矩形转换为屏幕坐标
	* @param pRect 地理坐标矩形
	* @return 返回屏幕矩形坐标
	*/
	DIS_RECT* TransformToDisplay(const GEOMETRY::geom::Envelope* pRect);

	DIS_BOUND* TransformToDisplayBound(const GEOMETRY::geom::Envelope* pBound);

	/**
	* 地理圆形转换成屏幕坐标
	* @param pCircle 地理圆形
	* @return 返回屏幕坐标圆形
	*/
	DIS_CIRCLE* TransformToDisplay(const GEOMETRY::geom::Circle* pCircle);

	/**
	* 地理椭圆转换成屏幕坐标
	* @param pEllipse 地理椭圆
	* @return 返回屏幕椭圆
	*/
	DIS_ELLIPSE* TransformToDisplay(const GEOMETRY::geom::Ellipse* pEllipse);

	/**
	* Bezier曲线转换成屏幕坐标
	* @param pBezier 贝塞尔曲线
	* @return 返回屏幕Bezier
	*/
	DIS_BEZIER* TransformToDisplay(const GEOMETRY::geom::BezierSpline* pBezier);

	double TransformToDisplay(double dblDistance);

	/**
	* 弧段多边形转换成屏幕坐标
	*/
	DIS_ARCPOLYGON* TransformArcPolygon(const GEOMETRY::geom::Polygon* pPolygon);

	/**
	* 屏幕矩形转换为地理坐标范围
	* @param rect 屏幕坐标矩形
	* @param pExtent 转换后的地理坐标范围
	*/
	void TransformToGeo(const DIS_RECT& rect,GEOMETRY::geom::Envelope* pExtent);

	double TransformToGeo(double dblDistance);

	/**
	* 使env范围内的地图适合当前display区域
	* @param env ：地图在当前display中显示的地理范围
	* @param bFullFill:是否填充满显示区域
	*/
	void FitViewBound(const GEOMETRY::geom::Envelope &env, bool bFullFill = FALSE);
	/** 
	*
	* 把m_viewPositon的m_dScale按比例缩放
	*/
   void ZoomViewPosScale(double ratio);

   void ZoomToFixScale(double scale);
   /** 
    *
	* 更新m_viewPosition的m_dScale
	*/
   void UpdateViewPosScale(double dblScale);

	/**
	* Move View Bound
	* @param OffsetX,OffsetY
	*/
	
	void SetUnit(SYSTEM::SYS_UNIT_TYPE unit);

	SYSTEM::SYS_UNIT_TYPE GetUnit();

	void MillimeterToDisplay(double mmVal, long& disVal);

	double MillimeterToGeo( double dmil );

	void TransformToDisplay(const double inWidth, double inHeight, double& outWidth, double &outHeight);


	//根据比例综合线面中的点
	void GeralizeFromScale( const GEOMETRY::geom::CoordinateSequence *pcs, GEOMETRY::geom::CoordinateSequence *poutcs );


	/*
	根据显示范围，快速裁减线面数据,需要调试
	*/
	BOOL DisplayClip( GEOMETRY::geom::Envelope &env, const GEOMETRY::geom::CoordinateSequence *pcs, std::vector<GEOMETRY::geom::Coordinate> &cs_out,BOOL bPolygon);

	std::string GetIndexString(GEOMETRY::geom::Envelope &env, double x, double y, long level);

	void GetRasterBlockRect(GEOMETRY::geom::Envelope env_all, std::string&inxString, double &minX,double &minY,double &maxX,double &maxY);

	void _GetRasterBlockRect(const char* indexStr,long pos, double &minX,double &minY,double &maxX,double &maxY);

	/**
	* 得到当前视图的坐标范围
	* @param minX
	* @param minY
	* @param maxX
	* @param maxY
	*/
	void GetGeoWideOfCurrentView( double &minX , double &minY , double &maxX , double &maxY );

	//前视图
	void SetPreExtent();

	//后视图
	void SetNextExtent();

	bool HasPreExtent();

	bool HasNextExtent();


    void RecordCurExtent(GEOMETRY::geom::Envelope& extent);

protected:

	void ConvertGeoToDisplay( const GEOMETRY::geom::CoordinateSequence *pcs , INT_POINT *pts);

	void ConvertGeoToDisplay( const std::vector<GEOMETRY::geom::Coordinate> &cs , INT_POINT *pts );

	void ConvertGeoToDisplay( const GEOMETRY::geom::CoordinateSequence *pcs , INT_POINT *pts, unsigned long &UseCount);

	void ConvertGeoToDisplay( const std::vector<GEOMETRY::geom::Coordinate> &cs , INT_POINT *pts , unsigned long &UseCount);

	//将堆栈中位于游标之后的记录清除
	void RemoveStack();

	

protected:
	//世界坐标的单位
	SYSTEM::SYS_UNIT_TYPE m_unit;
	//参考比例尺
	double	  m_referenceScale;
	VIEW_POSITION m_viewPositon;

	//视图范围的堆栈，默认保存20个范围
	std::vector<GEOMETRY::geom::Envelope> m_ViewStack;
	int m_curpos;
};

}

#endif