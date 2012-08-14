//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.10
// ������  TOC�ؼ�
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

	// ���½���
	virtual void UpdateInterface();

	virtual BOOL CreateControl( std::string Name, void *pParent , long nID );


	//���ͼ��
	virtual void AddLayer(Carto::ILayerPtr layerPtr, BOOL bExpand = TRUE);

	//ɾ����ǰͼ��	
	virtual void DeleteLayer(Carto::ILayerPtr ptrLayer);


	//ɾ������MAP��ȫ��ͼ��
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

	//ɾ��ͼ��
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

	//ɾ��ͼ��
	afx_msg void OnRemoveLayer();

	//ͼ������
	afx_msg void OnLayerProp();

	//����ͼ��
	afx_msg void OnActiveLayer();
	void ActiveLayer(HTREEITEM item);
	void ActiveLayer(Carto::CMapPtr pMap);

	//ɾ������ͼ��
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

	//���ʸ��ͼ���ͼ���ڵ�
	void AddFeatureLayerLegend(Carto::ILayerPtr ptrLayer,HTREEITEM hParent);

	void AddRasterLayerLegend(Carto::ILayerPtr ptrLayer,HTREEITEM hParent);

	void UpdateMenuStatus(CMenu *pMenu);

	//����ͼ��Ľڵ�
	void UpdateLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM LayerItem);

	//����һ�ŷ�����Ⱦ��ͼƬ
	void CreateSymbolBmp(Display::ISymbolPtr pSymbol,CBitmap &bmp);


protected:
	DECLARE_MESSAGE_MAP()

	CImageList m_imgState;
	CImageList m_imageList;
	std::string m_csCtrlName;
	std::map  <HTREEITEM, Carto::ILayerPtr> m_LayerItemMap;


	//MAP�����ڵ㵽MAPָ��ӳ��
	std::map <HTREEITEM,Carto::CMapPtr> m_itemToMapPtr;

	UINT          m_TimerTicks;      //��������Ķ�ʱ����������ʱ��
	UINT          m_nScrollTimerID;  //��������Ķ�ʱ��
	CPoint        m_HoverPoint;      //���λ��
	UINT          m_nHoverTimerID;   //������ж�ʱ��
	DWORD         m_dwDragStart;     //������������һ�̵�ʱ��
	BOOL          m_bDragging;       //��ʶ�Ƿ������϶�������
	CImageList*   m_pDragImage;      //�϶�ʱ��ʾ��ͼ���б�
	HTREEITEM     m_hItemDragS;      //���϶��ı�ǩ
	HTREEITEM     m_hItemDragD;      //�����϶��ı�ǩ



private:

	UINT m_uFlags;
	HTREEITEM m_hActMapItem;
	HTREEITEM m_hActLayerItem;

};

}

#endif