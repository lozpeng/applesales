//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  选择集的基类
//////////////////////////////////////////////////////////////////////

#ifndef  _ISELECTIONSET_H_
#define  _ISELECTIONSET_H_

#include "IRow.h"
#include <string>
#include <map>

namespace Geodatabase
{


class ITable;

class GEODATABASE_DLL ISelctionSet
{
public:
	ISelctionSet(ITable *pTable) {m_pTable =pTable;};
	virtual ~ISelctionSet(){};

public:
	//获得选择集所关联的Table对象
	ITable *GetTable() const{return m_pTable;}

	//选中要素的数目
	virtual long Count() const =0;

	//添加一个要素到选择集中
	virtual void Add(long id) =0;

	//和另外一个选择集合并
	virtual void Combine(ISelctionSet* pSelection,SelSetOperation operatetype) =0;

	//得到下一个元素的ID,同时指针向下移
	virtual long NextID() =0;


	//重新设置指针到选择集开始的位置
	virtual void ResetIndex() =0;

	//指针是否已经到最后的位置
	virtual bool IsEOF() const =0;


public:
	ITable  *m_pTable;


};

typedef  SYSTEM::CSmartPtr<ISelctionSet> ISelctionSetPtr;




}




#endif