#ifndef _OGR_FEATURECURSOR_H_
#define _OGR_FEATURECURSOR_H_

#include "IFeatureCursor.h"


class COGRFeatureClass;
class OGRFeature;

class  COGRFeatureCursor :public Geodatabase::IFeatureCursor
{
	friend class COGRFeatureClass;
public:
	COGRFeatureCursor(COGRFeatureClass *pFeatureClass,const char* fields);
	virtual ~COGRFeatureCursor();

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

	//��ʼ���ֶ�
	void InitFields(const char* fields);
private:


	//ָ�����ֶε���������
	std::vector<Geodatabase::CFieldPtr> m_Fields;


	long m_curPos;

	//�Ƿ���������ֶ�
	bool m_bhasGeometry;

    //��������Ҫ�صĻ���
	std::vector<OGRFeature*> m_Features;



};


#endif