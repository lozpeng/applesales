//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  9527
// ʱ�䣺  2008/11/27
// ������  ����ת��
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

	/** ���캯�� 
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
	double	m_dScale;/** ���ر����ߣ������ǵ�λ������Χ����/��������,һ�����ض�Ӧһ����ͼ��λ��*/
	double  m_dMapScale;/** ��ͼ�����ߣ����ǵ�λ��������Χ����*mm/mapUnit��/����������*mm/pixelUnit����*/
	double	m_dGeoCenterX,m_dGeoCenterY;/** ���ĵ�X�������ꡢ���ĵ�Y��������*/
	DIS_BOUND	m_displayBound; /**��Ļ��ʾ��Χ*/

};

class DISPLAY_DLL CDisplayTransformation
{
public:
	CDisplayTransformation();
	~CDisplayTransformation();

public:

	/**
	* �õ���ǰ��ͼ�����귶Χ
	* @bound
	*/
	void GetGeoBound(GEOMETRY::geom::Envelope &bound);

	/**
	* �õ���ͼ����
	* @return ������ͼ����
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
	*����  :   ע���Ӵ���ʾ��Χ�ı�Ļص�����
	*����  :   boost::function fun��������
	*��������  :  boost::signals::connection �ź����Ӷ���
	*/
	static boost::signals::connection RegisterChangeViewPos(boost::function<void (VIEW_POSITION)> fun);


	/**
	* ����������ת��Ϊ��Ļ��ʾ����
	* @param x ��������X
	* @param y ��������Y
	* @param px_x ��Ļ����X
	* @param px_y ��Ļ����Y
	*/
	void ConvertGeoToDisplay( double x, double y, long &px_x, long &px_y)
	{
		px_x = DoubleToLong((x - m_viewPositon.m_dGeoCenterX)/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0);
		px_y = DoubleToLong((m_viewPositon.m_dGeoCenterY-y)/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0);
	}

	/**
	* ����Ļ��ʾ����ת��Ϊ��������
	* @param px_x ��Ļ����X
	* @param px_y ��Ļ����Y
	* @param x ��������X
	* @param y ��������Y
	*/
	void ConvertGeoToDisplay( double x, long &px_x )
	{
		px_x = DoubleToLong(x/m_viewPositon.m_dScale);
	}

	/**
	* ����Ļ��ʾ����ת��Ϊ��������
	* @param px_x ��Ļ����X
	* @param px_y ��Ļ����Y
	* @param x ��������X
	* @param y ��������Y
	*/
	void ConvertDisplayToGeo( long px_x, long px_y, double &x, double &y )
	{
		x = (px_x-(m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0)*m_viewPositon.m_dScale+m_viewPositon.m_dGeoCenterX;
		y = ((m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0-px_y)*m_viewPositon.m_dScale+m_viewPositon.m_dGeoCenterY;
	}

	/**
	* ����Ļ��ʾ����ת��Ϊ��������
	* @param px_x ��Ļ����X
	* @param px_y ��Ļ����Y
	* @param x ��������X
	* @param y ��������Y
	*/
	void ConvertDisplayToGeo( long px_x, long px_y, GEOMETRY::geom::Coordinate& coord )
	{
		coord.x = (px_x-(m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0)*m_viewPositon.m_dScale+m_viewPositon.m_dGeoCenterX;
		coord.y = ((m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0-px_y)*m_viewPositon.m_dScale+m_viewPositon.m_dGeoCenterY;
	}

	/**
	* ����Ļ��ʾ����ת��Ϊ��������
	* @param px_x ��Ļ����X
	* @param px_y ��Ļ����Y
	* @param x ��������X
	* @param y ��������Y
	*/
	void ConvertDisplayToGeo( long px_x, double &x)
	{
		x = px_x*m_viewPositon.m_dScale;
	}

	/**
	* �������������Ļ����ת��
	* @param pEnvelope �������ڵ�������
	* @param strText ��������
	* @return ������Ļ������
	*/
	DIS_TEXT* TransformToDisplay(const GEOMETRY::geom::Envelope* pEnvelope,  const std::string strText);


	/**
	* �������������Ļ����ת��
	* @param pPoint ���������
	* @return ������Ļ������
	*/
	DIS_POINT* TransformToDisplay(const GEOMETRY::geom::Point *pPoint);

	/**
	* ��������������Ļ����ת��
	* @param pLine ����������

	* @return ������Ļ������
	*/
	DIS_LINE* TransformToDisplay(const GEOMETRY::geom::LineString* pLine);

	/**
	* ��������ת������Ļ����
	* @param pPolygon ��������
	* @return ������Ļ�����
	*/
	DIS_POLYGON* TransformToDisplay(const GEOMETRY::geom::Polygon* pPolygon);

	/**
	* �����������ת��Ϊ��Ļ����
	* @param pRect �����������
	* @return ������Ļ��������
	*/
	DIS_RECT* TransformToDisplay(const GEOMETRY::geom::Envelope* pRect);

	DIS_BOUND* TransformToDisplayBound(const GEOMETRY::geom::Envelope* pBound);

	/**
	* ����Բ��ת������Ļ����
	* @param pCircle ����Բ��
	* @return ������Ļ����Բ��
	*/
	DIS_CIRCLE* TransformToDisplay(const GEOMETRY::geom::Circle* pCircle);

	/**
	* ������Բת������Ļ����
	* @param pEllipse ������Բ
	* @return ������Ļ��Բ
	*/
	DIS_ELLIPSE* TransformToDisplay(const GEOMETRY::geom::Ellipse* pEllipse);

	/**
	* Bezier����ת������Ļ����
	* @param pBezier ����������
	* @return ������ĻBezier
	*/
	DIS_BEZIER* TransformToDisplay(const GEOMETRY::geom::BezierSpline* pBezier);

	double TransformToDisplay(double dblDistance);

	/**
	* ���ζ����ת������Ļ����
	*/
	DIS_ARCPOLYGON* TransformArcPolygon(const GEOMETRY::geom::Polygon* pPolygon);

	/**
	* ��Ļ����ת��Ϊ�������귶Χ
	* @param rect ��Ļ�������
	* @param pExtent ת����ĵ������귶Χ
	*/
	void TransformToGeo(const DIS_RECT& rect,GEOMETRY::geom::Envelope* pExtent);

	double TransformToGeo(double dblDistance);

	/**
	* ʹenv��Χ�ڵĵ�ͼ�ʺϵ�ǰdisplay����
	* @param env ����ͼ�ڵ�ǰdisplay����ʾ�ĵ���Χ
	* @param bFullFill:�Ƿ��������ʾ����
	*/
	void FitViewBound(const GEOMETRY::geom::Envelope &env, bool bFullFill = FALSE);
	/** 
	*
	* ��m_viewPositon��m_dScale����������
	*/
   void ZoomViewPosScale(double ratio);

   void ZoomToFixScale(double scale);
   /** 
    *
	* ����m_viewPosition��m_dScale
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


	//���ݱ����ۺ������еĵ�
	void GeralizeFromScale( const GEOMETRY::geom::CoordinateSequence *pcs, GEOMETRY::geom::CoordinateSequence *poutcs );


	/*
	������ʾ��Χ�����ٲü���������,��Ҫ����
	*/
	BOOL DisplayClip( GEOMETRY::geom::Envelope &env, const GEOMETRY::geom::CoordinateSequence *pcs, std::vector<GEOMETRY::geom::Coordinate> &cs_out,BOOL bPolygon);

	std::string GetIndexString(GEOMETRY::geom::Envelope &env, double x, double y, long level);

	void GetRasterBlockRect(GEOMETRY::geom::Envelope env_all, std::string&inxString, double &minX,double &minY,double &maxX,double &maxY);

	void _GetRasterBlockRect(const char* indexStr,long pos, double &minX,double &minY,double &maxX,double &maxY);

	/**
	* �õ���ǰ��ͼ�����귶Χ
	* @param minX
	* @param minY
	* @param maxX
	* @param maxY
	*/
	void GetGeoWideOfCurrentView( double &minX , double &minY , double &maxX , double &maxY );

	//ǰ��ͼ
	void SetPreExtent();

	//����ͼ
	void SetNextExtent();

	bool HasPreExtent();

	bool HasNextExtent();


    void RecordCurExtent(GEOMETRY::geom::Envelope& extent);

protected:

	void ConvertGeoToDisplay( const GEOMETRY::geom::CoordinateSequence *pcs , INT_POINT *pts);

	void ConvertGeoToDisplay( const std::vector<GEOMETRY::geom::Coordinate> &cs , INT_POINT *pts );

	void ConvertGeoToDisplay( const GEOMETRY::geom::CoordinateSequence *pcs , INT_POINT *pts, unsigned long &UseCount);

	void ConvertGeoToDisplay( const std::vector<GEOMETRY::geom::Coordinate> &cs , INT_POINT *pts , unsigned long &UseCount);

	//����ջ��λ���α�֮��ļ�¼���
	void RemoveStack();

	

protected:
	//��������ĵ�λ
	SYSTEM::SYS_UNIT_TYPE m_unit;
	//�ο�������
	double	  m_referenceScale;
	VIEW_POSITION m_viewPositon;

	//��ͼ��Χ�Ķ�ջ��Ĭ�ϱ���20����Χ
	std::vector<GEOMETRY::geom::Envelope> m_ViewStack;
	int m_curpos;
};

}

#endif