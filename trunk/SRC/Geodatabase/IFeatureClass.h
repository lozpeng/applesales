//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  ʸ�����ݼ��Ļ���
//////////////////////////////////////////////////////////////////////

#ifndef  _IFEATURECLASS_H_
#define  _IFEATURECLASS_H_

#include "ITable.h"
#include "Feature.h"
#include "SystemUnit.h"
#include <string>
namespace GEOMETRY
{
	namespace geom
	{
		class Geometry;
		class Envelope;
	}
}
namespace Geodatabase
{

class IFeatureDataset;

/** 
 * ʸ�����ݼ��Ķ���
 */
 struct FeatureClassDef
 {
	 FeatureClassDef( ):minx(0.0),miny(0.0),maxx(0.0),maxy(0.0),scale(10000),hasz(false),hasm(false){}
	 

	 double minx;
	 double miny;
	 double maxx;
	 double maxy;                        /** ����Դ�������*/
	 std::string wkt;                    //ͶӰ�ַ���
	 std::string description;            //��������
	 long        scale;                   //������
	 long        lshptype;                //ͼ�ε����,ΪGeometry�е����
	 bool      hasz;                     //�Ƿ����zֵ
	 bool      hasm;                     //�Ƿ����mֵ
	 std::vector<CFieldPtr> FieldsDef;   //�ֶ�����

 };

class GEODATABASE_DLL IFeatureClass :public ITable
{
public:
	IFeatureClass(IWorkspace *pWorkspace,IFeatureDataset *pDataset);
	virtual ~IFeatureClass();

public:

	IFeatureDataset *FeatureDataset() const{return m_pDataset;}

	//����Ҫ�ص���Ŀ
	virtual long FeatureCount() const =0;

	//Ҫ�ص�ͼ������,ΪGEOMETRY::geom::GeometryTypeId����
	virtual long ShapeType() =0;

	//ͼ�������ֶε�����
	virtual std::string  ShapeFieldName() =0;

	///////����ΪҪ�صĲ�������///////////////////////////////////////////////////
	//���������д���һ���յ�Ҫ�أ�����Ϊ��
	virtual CFeaturePtr CreateFeature() =0;

	//����Ҫ��ID�Ļ�ȡҪ��,��Ŵ�1��ʼ
	virtual CFeaturePtr GetFeature(long index)=0;

	//����Ҫ��ID��ȡҪ�ص�ͼ��
	virtual GEOMETRY::geom::Geometry* GetFeatureShape(long index) =0;

	//���һ����Ҫ��
	virtual void AddFeature(CFeature* pFeature) =0;

	//����һ��Ҫ��
	virtual void UpdateFeature(CFeature* pFeature) =0;

	//ɾ��һ��Ҫ��
	virtual void DeleteFeature(long index) =0; 
	///////����Ϊ��ѯ�Ĳ�������///////////////////////////////////////////////////

	//���β�ѯ
	virtual ISelctionSetPtr SelectByRect(const double &xmin,const double &ymin, const double &xmax,const double &ymax) =0;

	//ͨ����Χ����ѯ������һ��ָ��
	virtual ICursorPtr QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,CSimpleQuery *pQuery,bool bReadOnly =true) =0;
	///////////ͶӰ���///////////////////////////////////////////////////////////
	virtual std::string GetWkt() const =0;

	virtual void SetWkt(const char* strwkt) =0;

	//�Ƿ����Mֵ��Zֵ
	virtual bool HasM() const =0;

	virtual bool HasZ() const =0;

protected:
	//////////////����Ϊʵ�ֵ�ITable�Ľӿ�///////////////////////////////////
	//�ڱ��д���һ���յļ�¼������Ϊ��
	virtual IRowPtr CreateRow();

	//���ݼ�¼ID��ȡ��¼
	virtual IRowPtr GetRow(long index);

	//���һ���µļ�¼
	virtual void AddRow(IRow* pRow);

	//����һ����¼
	virtual void UpdateRow(IRow* pRow);

	//ɾ��һ����¼
	virtual void DeleteRow(long index); 


public:
	IFeatureDataset   *m_pDataset;



};

typedef  SYSTEM::CSmartPtr<IFeatureClass> IFeatureClassPtr;




}




#endif