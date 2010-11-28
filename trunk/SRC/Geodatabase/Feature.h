//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  CFeature�ౣ����һ��ʸ��Ҫ�ص�ͼ����Ϣ��������Ϣ
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_FEATURE_H_
#define  _GEODATABASE_FEATURE_H_

#include "IRow.h"
#include <string>
#include <vector>
#include <comutil.h>

namespace GEOMETRY
{
	namespace geom
	{
		class Geometry;
	}
}

namespace Geodatabase
{

class IFeatureClass;
class CField;

class GEODATABASE_DLL CFeature: public IRow 
{
public:
	CFeature(IFeatureClass *pFeatureClass,long oid);

	//��������
	CFeature(const CFeature &other);

	virtual ~CFeature();

public:

	//�õ�ʸ��ͼ��
	GEOMETRY::geom::Geometry* GetShape() const {return m_pGeometry;};

	//�õ�ͼ�εĿ���
	GEOMETRY::geom::Geometry* GetShapeClone() const;

	//����ͼ��
	void SetShape(GEOMETRY::geom::Geometry* pGeometry);

	//�����ı���ر���
	virtual void Update();
	//�ڱ���ɾ���ü�¼
	virtual void Delete();
	//�����е�ֵ�ƿ�
	virtual void SetEmpty();

	//�õ�Ҫ�صĿ���
	virtual CFeature* Clone();


public:
	GEOMETRY::geom::Geometry*   m_pGeometry;


};

typedef  SYSTEM::CSmartPtr<CFeature> CFeaturePtr;




}




#endif