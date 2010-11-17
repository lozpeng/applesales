#ifndef GEOMETRY_GEOM_LINE_H
#define GEOMETRY_GEOM_LINE_H

#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType
#include <Geometry/geom/ISegment.h>


#include <string>
#include <vector>
#include <memory> // for auto_ptr

namespace GEOMETRY {
namespace geom { 

class Coordinate;  

/******************************************************************************
*�߶μ̳���ISegment��Ϊ�ͼ�ͼ�Σ���������ߡ��߻�������εȸ߼�ͼ�ε�Ԫ��
*
******************************************************************************/
class Line: public ISegment
{
	
public:

	Line();
    
	//�ù��캯����ʵ���������յ���󣬲���ֵ
	Line(const Coordinate &p0,const Coordinate &p1);

	Line(Coordinate *pFromPt,Coordinate *pToPt );

	//�����������ͷ������յ���ڴ棬��Ϊ�����յ㱣���ڸ߼�ͼ�ε�����������
	virtual ~Line();
public:
     
	

/******************************************************************
*ʵ��Geometry�ĺ���
******************************************************************/
public:

     std::string getGeometryType() const {return "Line";}; 

	 GeometryTypeId getGeometryTypeId() const {return GEOM_LINE;};
	 Geometry* clone() const;

	 bool equalsExact(const Geometry *other, double tolerance=0) const;


protected:



/******************************************************************
*����Ϊʵ��ISegment�Ľӿ�
******************************************************************/
public:

   
   //���߶εĳ���
    double Length() const;

    void CloestLinePoint(const Coordinate &pt, Coordinate &ret) const;

		//�߶ε��е�
    void MidPoint(Coordinate &ret) const;

/******************************************************************
*����ΪLine��һЩ����
******************************************************************/
public:

	//�жϵ�Ĵ���������߶ε�λ��
	double projectionFactor(const Coordinate& p) const;

};





} // GEOMETRY::geom
} //GEOMETRY







#endif
