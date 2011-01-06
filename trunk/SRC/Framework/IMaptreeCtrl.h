//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.10
// ������  TOC�ؼ��������
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

	//���ͼ��
	virtual void AddLayer(Carto::ILayerPtr player, BOOL bExpand = TRUE) = 0;

	//ɾ����ǰͼ��
	virtual void DeleteLayer(Carto::ILayerPtr pLayer) = 0;

	//ɾ��ȫ��ͼ��
	virtual void DeleteAllLayers() = 0;


	//���Tree�ؼ�
	virtual void ClearControl() = 0;

	//���ǰ��ͼ��ͼ
	virtual Carto::CMapPtr ActivateMap() = 0;
	virtual void ActivateMap(Carto::CMapPtr pMap) = 0;

	//��ӵ�ͼ��ͼ
	virtual BOOL AddMap(long lIndex) = 0;

	//ɾ��ͼ��
	virtual Carto::CMapPtr DeleteMap() = 0;

	//ɾ��ͼ��
	virtual Carto::CMapPtr DeleteMap(Carto::CMapPtr pMap) = 0;

	
	virtual BOOL IsCurItemActivated() = 0;

	//��õ�ǰѡ��������
	int GetSelectedItemType();


	HTREEITEM GetMapItem();

	
	virtual void *GetSelectedItemData(); 

protected:

	//���ڵ�
	HTREEITEM m_hRootItem;

	//
	HTREEITEM m_hMapItem;

	//
	int m_iSelectedItemType;

};

}
#endif