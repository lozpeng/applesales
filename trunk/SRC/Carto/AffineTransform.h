//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/11/28
// 描述：  仿射变换
//////////////////////////////////////////////////////////////////////


#ifndef _AffineTransform_h
#define _AffineTransform_h
namespace GEOMETRY
{
	namespace geom
	{
		class Geometry;
		class Envelope;
	}
}
namespace Carto
{

//仿射变换类
class CAffineTransform
{
public:
	CAffineTransform();
	~CAffineTransform();

public:

	//获取与设置仿射变换是否可用
	bool GetEnableUsed() { return m_bUsed; }
	bool SetEnbleUsed(bool bUsed) { m_bUsed = bUsed;}

	//正变换
	void Transform(GEOMETRY::geom::Geometry *pshape);
	void Transform(double &X, double &Y);
	void Transform(GEOMETRY::geom::Envelope &envelop);


	//逆变换
	void TransformN(GEOMETRY::geom::Geometry *pshape);
	void TransformN(double &X, double &Y);
	void TransformN(GEOMETRY::geom::Envelope &envelop);

	//计算仿射变换参数，在源地里范围内采样点进行投影变换方式
	bool DynaProject(std::string strSrcWkt, std::string strDestWkt,GEOMETRY::geom::Envelope dataEnvelop);

private:
	bool m_bUsed;
	double affineCoefX[3],affineCoefY[3];
	double affineNCoefX[3],affineNCoefY[3];
	void*  m_hProjectTrans; //投影转换结构体的指针
};

typedef SYSTEM::CSmartPtr<CAffineTransform> CAffineTransformPtr;

}

#endif