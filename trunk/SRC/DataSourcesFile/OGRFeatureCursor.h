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

	//通过字段名查找字段的序号
	virtual long FindField(const char* name) ;

	//通过序号得到一个字段的描述
	virtual Geodatabase::CFieldPtr GetField(long index);
	//该指针的字段数目
	virtual long FieldCount() const;

	virtual Geodatabase::CFeaturePtr NextFeature();


	//指针是否已经到最后的位置
	bool IsEOF() const;

private:

	//初始化字段
	void InitFields(const char* fields);
private:


	//指针中字段的描述集合
	std::vector<Geodatabase::CFieldPtr> m_Fields;


	long m_curPos;

	//是否包含几何字段
	bool m_bhasGeometry;

    //保存所有要素的缓存
	std::vector<OGRFeature*> m_Features;



};


#endif