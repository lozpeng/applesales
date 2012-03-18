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

	//���ù����ؼ�
	void SetMapCtrl(_DotMapControl *pMapControl) {m_pMapControl =pMapControl;}
	
	void SetParentCtrl(CotMapTreeCtrl *pTreeCtrl) {m_pTreeCtrl =pTreeCtrl;}
	 

	void Refresh();

	 void SetSelectedLayer(Carto::ILayerPtr ptrLayer);

	//���ͼ��
	 void AddLayer(Carto::ILayerPtr layerPtr, BOOL bExpand = TRUE);

	//ɾ����ǰͼ��	
	 void DeleteLayer(Carto::ILayerPtr ptrLayer);

	//��ӣ���ʼ��һ����ͼ����
	 void AddLayerGroup();

	//ɾ������MAP��ȫ��ͼ��
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

	// ֻ��¼״̬
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

	//ɾ��ͼ��
	afx_msg void OnRemoveLayer();

	//ͼ������
	afx_msg void OnLayerProp();

	//ɾ������ͼ��
	afx_msg void OnRemoveAllLayer();


protected:
	DECLARE_MESSAGE_MAP()

	CImageList m_imgState;
	CImageList m_imageList;
	std::string m_csCtrlName;
	std::map  <HTREEITEM, Carto::ILayerPtr> m_LayerItemMap;

	//MAP�����ڵ����鵽MAP��ΨһIDӳ��
	//std::map  <HTREEITEM, long> m_MapItemMap;

	//MAP�����ڵ㵽MAPָ��ӳ��
	std::map <HTREEITEM,Carto::CMap*> m_itemToMapPtr;

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

	//���ʸ��ͼ���ͼ���ڵ�
	void AddFeatureLayerLegend(Carto::ILayerPtr ptrLayer,HTREEITEM hParent);

	void UpdateMenuStatus(CMenu *pMenu);

	//����ͼ��Ľڵ�
	void UpdateLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM LayerItem);

	//����һ�ŷ�����Ⱦ��ͼƬ
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

	//�ؼ�ָ��
	_DotMapControl *m_pMapControl; 

	CotMapTreeCtrl *m_pTreeCtrl;
public:

	//�Ƿ񵯳������Ĳ˵�
	BOOL m_bShowMenu;

};
