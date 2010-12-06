//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2009/11/23
  // 描述：   shapefile要素游标  对要素、字段遍历
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
	void GetValues();

	//初始化字段
	void InitFields(const char* fields);
private:

	//标志位
	boost::dynamic_bitset<>  m_flags;	
	//指针中字段的描述集合
	std::vector<Geodatabase::CFieldPtr> m_Fields;

	Geodatabase::CFeaturePtr m_pFeature;

	long m_curPos;

	//是否包含几何字段
	bool m_bhasGeometry;

	//字段在表中的序号
	std::vector<long> m_FieldsIndex;


};


#endif