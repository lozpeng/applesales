#pragma once

#include "ILayer.h"
#include "Map.h"

enum SELECTED_ITEM_TYPE
{
	eMapItem, 
	eActiveMapItem,
	eLayerItem,
	eLegendItem,
};

class CotMapTreeCtrl;

class CMapTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMapTree)
public:
	CMapTree(void);
	virtual ~CMapTree(void);
public:

	//设置关联控件
	void SetMapCtrl(_DotMapControl *pMapControl) {m_pMapControl =pMapControl;}
	
	void SetParentCtrl(CotMapTreeCtrl *pTreeCtrl) {m_pTreeCtrl =pTreeCtrl;}
	 

	void Refresh();

	 void SetSelectedLayer(Carto::ILayerPtr ptrLayer);

	//添加图层
	 void AddLayer(Carto::ILayerPtr layerPtr, BOOL bExpand = TRUE);

	//删除当前图层	
	 void DeleteLayer(Carto::ILayerPtr ptrLayer);

	//添加（初始化一个）图层组
	 void AddLayerGroup();

	//删除激活MAP下全部图层
	 void DeleteAllLayers();

	//
	 BOOL MoveLayerUp();
	 BOOL MoveLayerDown() ;
	 BOOL MoveLayerToTop();
	 BOOL MoveLayerToBottom();

	//
	 void ModifyItemText(Carto::ILayerPtr ptrLayer, std::string strName);

	//
	 void Clear();


	//
	 BOOL AddMap(long lIndex);



	 BOOL IsCurItemActivated();

	 void *GetSelectedItemData(); 

	// 只记录状态
	void serialization(SYSTEM::IArchive &ar);

public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);	

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	BOOL SetItemState( HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch=TRUE);

	//删除图层
	afx_msg void OnRemoveLayer();

	//图层属性
	afx_msg void OnLayerProp();

	//删除所有图层
	afx_msg void OnRemoveAllLayer();


protected:
	DECLARE_MESSAGE_MAP()

	CImageList m_imgState;
	CImageList m_imageList;
	std::string m_csCtrlName;
	std::map  <HTREEITEM, Carto::ILayerPtr> m_LayerItemMap;

	//MAP的树节点数组到MAP的唯一ID映射
	//std::map  <HTREEITEM, long> m_MapItemMap;

	//MAP的树节点到MAP指针映射
	std::map <HTREEITEM,Carto::CMap*> m_itemToMapPtr;

	UINT          m_TimerTicks;      //处理滚动的定时器所经过的时间
	UINT          m_nScrollTimerID;  //处理滚动的定时器
	CPoint        m_HoverPoint;      //鼠标位置
	UINT          m_nHoverTimerID;   //鼠标敏感定时器
	DWORD         m_dwDragStart;     //按下鼠标左键那一刻的时间
	BOOL          m_bDragging;       //标识是否正在拖动过程中
	CImageList*   m_pDragImage;      //拖动时显示的图象列表
	HTREEITEM     m_hItemDragS;      //被拖动的标签
	HTREEITEM     m_hItemDragD;      //接受拖动的标签

private:
	void AddLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand = TRUE);

	HTREEITEM AddFeatureLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand = TRUE);

	HTREEITEM AddRasterLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand = TRUE);

	HTREEITEM AddTinLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand = TRUE);

	HTREEITEM AddLayerGroupNodes(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand = TRUE);

	HTREEITEM CopyBranch(HTREEITEM htiBranch,HTREEITEM htiNewParent,HTREEITEM htiAfter=TVI_LAST);

	HTREEITEM CopyItem(HTREEITEM hItem,HTREEITEM htiNewParent,HTREEITEM htiAfter= TVI_LAST);

	BOOL ModifyLayersOrder(HTREEITEM  htiNew, HTREEITEM hItemDragS, HTREEITEM hItemDragD);

	BOOL SetFocusLayer();

	void TravelSiblingAndParent(HTREEITEM hItem, int nState);

	void TravelChild(HTREEITEM hItem, int nState);

	BOOL SetLayerVisible(int nState, HTREEITEM hItem);

	void SetParentItemState(HTREEITEM hParentItem);

	HTREEITEM SearchItemByLayer(Carto::ILayerPtr ptrLayer);

	HTREEITEM SearchItemByMap(Carto::CMap* pMap);

	//添加矢量图层的图例节点
	void AddFeatureLayerLegend(Carto::ILayerPtr ptrLayer,HTREEITEM hParent);

	void UpdateMenuStatus(CMenu *pMenu);

	//更新图层的节点
	void UpdateLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM LayerItem);

	//产生一张符号渲染的图片
	void CreateSymbolBmp(Display::ISymbolPtr pSymbol,CBitmap &bmp);

	Carto::CMap* GetMap();

private:

	HTREEITEM m_hRootItem;

	//
	HTREEITEM m_hMapItem;

	//
	int m_iSelectedItemType;

	UINT m_uFlags;
	HTREEITEM m_hActMapItem;

	//控件指针
	_DotMapControl *m_pMapControl; 

	CotMapTreeCtrl *m_pTreeCtrl;
public:

	//是否弹出上下文菜单
	BOOL m_bShowMenu;

};
