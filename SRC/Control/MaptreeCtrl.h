//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.10
// 描述：  TOC控件
//////////////////////////////////////////////////////////////////////

#ifndef _MAPTREECONTROL_H_
#define _MAPTREECONTROL_H_

#include "IMaptreeCtrl.h"

namespace Control
{

class CONTROL_DLL CMaptreeCtrl : public CTreeCtrl,public Framework::IMaptreeCtrl
{
	DECLARE_DYNAMIC(CMaptreeCtrl)

public:
	CMaptreeCtrl();
	virtual ~CMaptreeCtrl();

public:

	virtual void RefreshFromDoc();

	// 更新界面
	virtual void UpdateInterface();

	virtual BOOL CreateControl( std::string Name, void *pParent , long nID );


	//添加图层
	virtual void AddLayer(Carto::ILayerPtr layerPtr, BOOL bExpand = TRUE);

	//删除当前图层	
	virtual void DeleteLayer(Carto::ILayerPtr ptrLayer);


	//删除激活MAP下全部图层
	virtual void DeleteAllLayers();


	virtual void ClearControl();

   //
	virtual Carto::CMapPtr ActivateMap();

	//
	virtual void ActivateMap(Carto::CMapPtr pMap);

	//
	virtual BOOL AddMap(long lIndex);

	//
	virtual Carto::CMapPtr DeleteMap();

	//删除图层
	virtual Carto::CMapPtr DeleteMap(Carto::CMapPtr pMap);

	virtual BOOL IsCurItemActivated();

	virtual void *GetSelectedItemData(); 

	virtual void OpenAttributeTable(Carto::ILayerPtr pLayer, Geodatabase::IFeatureClassPtr pFeatureClass){}

	virtual void CloseAttibuteTable(){}

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

	afx_msg void OnLoadFeatureData();
	afx_msg void OnLoadRaster();

	//删除图层
	afx_msg void OnRemoveLayer();

	//图层属性
	afx_msg void OnLayerProp();

	//激活图层
	afx_msg void OnActiveLayer();
	void ActiveLayer(HTREEITEM item);
	void ActiveLayer(Carto::CMapPtr pMap);

	//删除所有图层
	afx_msg void OnRemoveAllLayer();

	afx_msg void OnDeleteMap();

	afx_msg void OnActiveMap();

	afx_msg void OnMapProp();

	afx_msg void OnZoomToLayer();

	afx_msg void OnObjExport();

	afx_msg void OnOpenAttribute();

	BOOL SetItemState( HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch=TRUE);


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

	HTREEITEM SearchItemByMap(Carto::CMapPtr pMap);

	//添加矢量图层的图例节点
	void AddFeatureLayerLegend(Carto::ILayerPtr ptrLayer,HTREEITEM hParent);

	void AddRasterLayerLegend(Carto::ILayerPtr ptrLayer,HTREEITEM hParent);

	void UpdateMenuStatus(CMenu *pMenu);

	//更新图层的节点
	void UpdateLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM LayerItem);

	//产生一张符号渲染的图片
	void CreateSymbolBmp(Display::ISymbolPtr pSymbol,CBitmap &bmp);


protected:
	DECLARE_MESSAGE_MAP()

	CImageList m_imgState;
	CImageList m_imageList;
	std::string m_csCtrlName;
	std::map  <HTREEITEM, Carto::ILayerPtr> m_LayerItemMap;


	//MAP的树节点到MAP指针映射
	std::map <HTREEITEM,Carto::CMapPtr> m_itemToMapPtr;

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

	UINT m_uFlags;
	HTREEITEM m_hActMapItem;
	HTREEITEM m_hActLayerItem;

};

}

#endif