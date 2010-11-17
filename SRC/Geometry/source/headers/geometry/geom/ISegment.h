/**********************************************************************
 * ISegmentΪ���зֶμ���ģ�͵Ļ��࣬���߶Ρ����Ρ�����������
 * 
 *  ����������������ã������յ㣬��ʵ�ʵĵ�����洢����Ӧ�ĸ߼�ͼ�ε�
 *  �������У���LineString,LineRing,Polygon
 *   
 *  ISegment�ṩ���ʺ��޸������յ�ĺ�������ӦҲ���޸İ�����Segment��
 *  �߼�ͼ�εĵ�
 *
 * 
 * 
 * 
 * 
 *
 **********************************************************************/


#ifndef GEOMETRY_GEOM_ISEGMENT_H
#define GEOMETRY_GEOM_ISEGMENT_H

#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType

#include <Geometry/inline.h>

#include <string>
#include <vector>
#include <memory> // for auto_ptr

namespace GEOMETRY {
namespace geom { 

class Coordinate;  

class ISegment: public Geometry
{
	//ISegment���󲢲����ⲿ�ĺ�����������Ҫ�����ļ̳ж��󹹽�
protected:

	ISegment();
    
	//�ù��캯����ʵ���������յ���󣬲���ֵ
	ISegment(const Coordinate &p0,const Coordinate &p1);
    //�ù��캯��ֻ�Ὣ�����յ��ָ���ַ������Ա������
	//ISegment��ֻ���������յ������
	ISegment(Coordinate *pFromPt,Coordinate *pToPt );
public:
     
	//�����������ͷ������յ���ڴ棬��Ϊ�����յ㱣���ڸ߼�ͼ�ε�����������
	virtual ~ISegment();

/******************************************************************
*ʵ��Geometry�ĺ���
******************************************************************/
public:

	virtual const Coordinate* getCoordinate() const;


    virtual CoordinateSequence* getCoordinates() const;

	virtual size_t getNumPoints() const {return 2;};

	virtual bool isSimple() const {return true;};


    virtual void SetEmpty();

	virtual bool isEmpty() const;

	virtual Dimension::DimensionType getDimension() const {return Dimension::L;}


	virtual Geometry* getBoundary() const{return NULL ;};

	virtual int getBoundaryDimension() const {return 0;};

	virtual void apply_rw(const CoordinateFilter *filter) { }; 
	virtual void apply_ro(CoordinateFilter *filter) const { };

	virtual void normalize() {};
protected:

	virtual Envelope::AutoPtr computeEnvelopeInternal() const {return Envelope::AutoPtr(NULL);}; //Abstract

	virtual int compareToSameClass(const Geometry *geom) const{return 0;}; //Abstract

/******************************************************************
*����ΪISegment����Ĳ���
******************************************************************/
public:
   //�õ���ʼ�����ֹ��
   Coordinate GetFromPoint() const;

   Coordinate GetToPoint() const;

   //������ʼ�����ֹ��

   void setFromPoint(const Coordinate &pt);

   void setToPoint(const Coordinate &pt);

   //���������յ��ָ��
   void setFromPtr(Coordinate *pPt);

   void setToPtr(Coordinate  *pPt);

   
   //�öεĳ���
   virtual double Length() const =0;

   //�õ���������ϵ�
   virtual void CloestLinePoint(const Coordinate &pt, Coordinate &ret) const=0;

   //�߶ε��е�
   virtual void MidPoint(Coordinate &ret) const =0;

public:

	/******************************************************************
	*����ı任����,��Segment���ڵĸ߼�ͼ����ITransform�������ã�
	*�����ƶ������ţ���תSegment���˶˵�������еĲ���
	******************************************************************/
	//
	virtual void SegMove(double dx,double dy){}

	virtual void SegMirror(const Coordinate &p1,const Coordinate &p2){}

	virtual void SegScale(const Coordinate &OriginPt,double dx,double dy){}

	virtual void SegRotate(const Coordinate &OriginPt,double angle){}
protected:


protected:
     
	//�����յ��ָ��
     Coordinate *m_pFromPt;

     Coordinate *m_pToPt;

	 //�Ƿ���Ҫɾ����ʼ��ֹ��ָ��
	 bool m_bAutoDestroy;
    


};





} // GEOMETRY::geom
} //GEOMETRY







#endif
