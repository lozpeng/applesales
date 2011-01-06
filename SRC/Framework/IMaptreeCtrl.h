//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.10
// 描述：  TOC控件对象基类
//////////////////////////////////////////////////////////////////////

#ifndef _IMaptreeCtrl_h
#define _IMaptreeCtrl_h

#include "IUIObject.h"
#include "Map.h"

namespace Framework
{

enum SELECTED_ITEM_TYPE
{
	eMapItem, 
	eActiveMapItem,
	eLayerItem,
	eLegendItem,
};

class FRAMEWORK_DLL IMaptreeCtrl : public IUIObject
{
	struct OT_TREESTATE
	{
		bool bExpand;
		bool bSelected;
	};

public:
	IMaptreeCtrl();
	virtual ~IMaptreeCtrl();

public:

	//添加图层
	virtual void AddLayer(Carto::ILayerPtr player, BOOL bExpand = TRUE) = 0;

	//删除当前图层
	virtual void DeleteLayer(Carto::ILayerPtr pLayer) = 0;

	//删除全部图层
	virtual void DeleteAllLayers() = 0;


	//清空Tree控件
	virtual void ClearControl() = 0;

	//激活当前地图视图
	virtual Carto::CMapPtr ActivateMap() = 0;
	virtual void ActivateMap(Carto::CMapPtr pMap) = 0;

	//添加地图视图
	virtual BOOL AddMap(long lIndex) = 0;

	//删除图层
	virtual Carto::CMapPtr DeleteMap() = 0;

	//删除图层
	virtual Carto::CMapPtr DeleteMap(Carto::CMapPtr pMap) = 0;

	
	virtual BOOL IsCurItemActivated() = 0;

	//获得当前选中项类型
	int GetSelectedItemType();


	HTREEITEM GetMapItem();

	
	virtual void *GetSelectedItemData(); 

protected:

	//根节点
	HTREEITEM m_hRootItem;

	//
	HTREEITEM m_hMapItem;

	//
	int m_iSelectedItemType;

};

}
#endif