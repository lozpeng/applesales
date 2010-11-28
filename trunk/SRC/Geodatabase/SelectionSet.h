//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  CSelctionSet实现了ISelctionSet的接口
//////////////////////////////////////////////////////////////////////

#ifndef  _CSELECTIONSET_H_
#define  _CSELECTIONSET_H_

#include "ISelectionSet.h"
#include <string>
#include <map>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
namespace Geodatabase
{

/********************************************************************************
* CSelctionSet实现了ISelctionSet的接口，它的方式是通过存储选择的要素的ID,通过ID
* 枚举要素
*********************************************************************************/
class GEODATABASE_DLL CSelctionSet :public ISelctionSet
{
public:
	CSelctionSet(ITable *pTable);
	virtual ~CSelctionSet();

public:

	//选中要素的数目
	virtual long Count() const;

	//添加一个要素到选择集中
	virtual void Add(long id);

	//和另外一个选择集合并
	virtual void Combine(ISelctionSet* pSelection,SelSetOperation operatetype);

	//得到下一个元素,同时指针向下移
	virtual long NextID() ;


	//重新设置指针到选择集开始的位置
	virtual void ResetIndex();

	//指针是否已经到最后的位置
	bool IsEOF() const;


public:
	//标志位
	boost::dynamic_bitset<>  m_flags;	

	long m_curPos;
};


typedef  SYSTEM::CSmartPtr<CSelctionSet> CSelctionSetPtr;



}


#endif