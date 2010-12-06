//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2009/11/23
  // ������   shapefileҪ���α�  ��Ҫ�ء��ֶα���
//////////////////////////////////////////////////////////////////////

#ifndef _SHP_FEATURECURSOR_H_
#define _SHP_FEATURECURSOR_H_

#include "IFeatureCursor.h"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
class CShapefileFeatureClass;

class  CShapefileFeatureCursor :public Geodatabase::IFeatureCursor
{
	friend class CShapefileFeatureClass;
public:
	CShapefileFeatureCursor(CShapefileFeatureClass *pFeatureClass,const char* fields);
	virtual ~CShapefileFeatureCursor();

public:

	//ͨ���ֶ��������ֶε����
	virtual long FindField(const char* name) ;

	//ͨ����ŵõ�һ���ֶε�����
	virtual Geodatabase::CFieldPtr GetField(long index);
	//��ָ����ֶ���Ŀ
	virtual long FieldCount() const;

	virtual Geodatabase::CFeaturePtr NextFeature();


	//ָ���Ƿ��Ѿ�������λ��
	bool IsEOF() const;

private:
	void GetValues();

	//��ʼ���ֶ�
	void InitFields(const char* fields);
private:

	//��־λ
	boost::dynamic_bitset<>  m_flags;	
	//ָ�����ֶε���������
	std::vector<Geodatabase::CFieldPtr> m_Fields;

	Geodatabase::CFeaturePtr m_pFeature;

	long m_curPos;

	//�Ƿ���������ֶ�
	bool m_bhasGeometry;

	//�ֶ��ڱ��е����
	std::vector<long> m_FieldsIndex;


};


#endif