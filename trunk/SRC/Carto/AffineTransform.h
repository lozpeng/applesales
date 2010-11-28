//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/28
// ������  ����任
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

//����任��
class CAffineTransform
{
public:
	CAffineTransform();
	~CAffineTransform();

public:

	//��ȡ�����÷���任�Ƿ����
	bool GetEnableUsed() { return m_bUsed; }
	bool SetEnbleUsed(bool bUsed) { m_bUsed = bUsed;}

	//���任
	void Transform(GEOMETRY::geom::Geometry *pshape);
	void Transform(double &X, double &Y);
	void Transform(GEOMETRY::geom::Envelope &envelop);


	//��任
	void TransformN(GEOMETRY::geom::Geometry *pshape);
	void TransformN(double &X, double &Y);
	void TransformN(GEOMETRY::geom::Envelope &envelop);

	//�������任��������Դ���ﷶΧ�ڲ��������ͶӰ�任��ʽ
	bool DynaProject(std::string strSrcWkt, std::string strDestWkt,GEOMETRY::geom::Envelope dataEnvelop);

private:
	bool m_bUsed;
	double affineCoefX[3],affineCoefY[3];
	double affineNCoefX[3],affineNCoefY[3];
	void*  m_hProjectTrans; //ͶӰת���ṹ���ָ��
};

typedef SYSTEM::CSmartPtr<CAffineTransform> CAffineTransformPtr;

}

#endif