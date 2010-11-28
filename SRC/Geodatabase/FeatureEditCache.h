//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  编辑缓存
//////////////////////////////////////////////////////////////////////

#ifndef  _FEATUREEDITCACHE_H_
#define  _FEATUREEDITCACHE_H_

#include "IFeatureClass.h"
#include "SpatialQuery.h"
#include <string>
#include <map>
#include <vector>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

namespace Geodatabase
{

//要素编辑的类型
enum EditOperationType
{
    OP_ADD =0,   //添加
	OP_UPDATE =1, //更新
	OP_DELETE =2  //删除
};
//在一个要素类中编辑的一步操作
struct FEditStep
{
    EditOperationType EditType; //操作的类型
    long Fid; //要素的编号
	CFeaturePtr pFeature; 
};

class GEODATABASE_DLL CFeatureEditCache
{
public:
	CFeatureEditCache(IFeatureClass *pFeatureClass);
	virtual ~CFeatureEditCache();

public:

	//获得整个FeatureClass中总的记录数目，包括删除的和新加的
	long GetTotalNum() const;

	//获得有效记录的数目
	long GetValidNum() const;

	//是否能进行回退操作
    bool CanUndo() const;
    //是否能进行重做操作
	bool CanRedo() const;

	void Undo();

	void Redo();
	//添加一个要素
	void AppendFeature(CFeaturePtr pFeature);

	//删除一个要素
	void DeleteFeature(long Fid);
    //更新一个要素
    void UpdateFeature(CFeaturePtr pFeature);

	//要素是否被删除
	bool IsFeatureDelete(long Fid) const;

	//要素是否存在于编辑缓存中
	bool IsFeatureExist(long Fid) const;
	//得到指定要素
	CFeaturePtr GetFeature(long Fid);

	//重新排列整理编辑堆栈，使得它对一个要素的记录只有一条
	void Arrange();

	//在缓存中查询
	void QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,boost::dynamic_bitset<> &flags);

	void Query(CSimpleQuery *query,boost::dynamic_bitset<> &flags);


private:

	//清除掉堆栈中多余的记录
	void RemoveRedundant();

	//简单查询
	void SimpleQuery(CSimpleQuery *query,boost::dynamic_bitset<> &flags);

	//空间查询
	void SpatialQuery(CSpatialQuery *query,boost::dynamic_bitset<> &flags);


public:
	IFeatureClass *m_pFeatureClass;

	std::vector<FEditStep*> m_operationStack;

	long   m_lCursor;    //当前的回滚指针

	long   m_lnextRecId; //下一条记录的Id,也就是总的记录数目加一，包括删除的和新加的记录

	long   m_lvalidNum; //有效的记录的数目

};






}




#endif