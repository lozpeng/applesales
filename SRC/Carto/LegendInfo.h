#ifndef  _LEGEND_INFO_H_
#define  _LEGEND_INFO_H_

#include "ISymbol.h"
#include <vector>

namespace Carto
{

struct LegendItem
{
	Display::ISymbolPtr pSymbol; //图例对象的符号
	std::string strLabel; //图例对象的标注
	std::string strDes;  //图例对象的描述，可选，出现在Label的后面
};

/******************************************************************************
*  CLegendGroup表示一组图例对象的集合，包含了多个LegendItem
*
*******************************************************************************/
class CARTO_DLL CLegendGroup
{
public:
	/**
	* 获得图例对象的数目
	*/
	long GetItemCount();

	/**
	* 获得指定位置的图例对象
	* @param index 序号,从0开始
	*/
    LegendItem GetItem(long index);

	/**
	* 添加一个图例对象
	* @param item 图例对象
	*/
	void AddItem(const LegendItem &item);

	/**
	* 获得头文字
	*/
	std::string GetHeading();

	/**
	* 设置头文字
	*/
	void SetHeading(std::string strHeading);

	/**
	* 删除所有的图例对象
	*/
	void Clear();

protected:
	std::vector<LegendItem> m_Items;
	std::string m_strHeading;
};

typedef SYSTEM::CSmartPtr<CLegendGroup> CLegendGroupPtr;

/******************************************************************************
* CLegendInfo描述了图例的信息
*
*******************************************************************************/

class CARTO_DLL CLegendInfo
{
public:
	CLegendInfo();
	virtual ~CLegendInfo();
public:
    
	/**
	* 获得图例组的数目
	*/
	long LegendGroupCount();

	/**
	* 获得指定位置的图例组
	* @param index 序号,从0开始
	*/
	CLegendGroupPtr GetLegendGroup(long index);

	/**
	* 添加一个图例组
	*/
	void AddGroup( CLegendGroupPtr pLegendGroup);

public:
	std::vector<CLegendGroupPtr> m_Groups;

};

typedef SYSTEM::CSmartPtr<CLegendInfo> CLegendInfoPtr;



}




#endif