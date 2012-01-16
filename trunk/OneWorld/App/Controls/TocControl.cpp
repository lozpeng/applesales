// MaptreeCtrl.cpp : 实现文件
//

#include "TocControl.h"
#include "DllResource.h"
#include "Resource.h"
#include "owScene/layer.h"
#include "owNavi/FlyToManipulator.h"
#include "owScene/rastersource.h"
#include "owScene/featuresource.h"

#define   DRAG_DELAY   60

namespace Control
{
	IMPLEMENT_DYNAMIC(CTocControl, CTreeCtrl)

		CTocControl::CTocControl()
	{
		m_pOSG = NULL;
	}

	CTocControl::~CTocControl()
	{
	}

	BEGIN_MESSAGE_MAP(CTocControl, CTreeCtrl)
		ON_WM_CREATE()
		ON_COMMAND(ID_ZOOMLAYER, &CTocControl::OnZoomToLayer)
		ON_WM_RBUTTONDOWN()
	END_MESSAGE_MAP()

	BOOL CTocControl::CreateControl(void* pParent, long nID)
	{
		CreateUI(TocControl);
		CWnd *pWnd = (CWnd*)(pParent);
		BOOL bRet = Create( WS_CHILD | WS_VISIBLE | TVS_HASLINES |TVS_LINESATROOT| TVS_HASBUTTONS | TVS_SHOWSELALWAYS , CRect(0,0,0,0) , pWnd , nID );
		return bRet;
	}
	int CTocControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (__super::OnCreate(lpCreateStruct) == -1)
			return -1;
		return 0;
	}
	void CTocControl::Init()
	{
		// Setup trees content:
		HTREEITEM hRoot1 = InsertItem (_T("地形"));
		HTREEITEM hRoot2 = InsertItem (_T("模型"));
		HTREEITEM hRoot3 = InsertItem (_T("物体"));
		InsertItem (_T("纹理层"), hRoot1);
		InsertItem (_T("高程层"), hRoot1);
		InsertItem (_T("矢量层"), hRoot1);
	}
	void CTocControl::RefreshFromOSG(cOSG* pOsg)
	{
		m_pOSG = pOsg;
		owScene::Terrain* pTerrain = pOsg->getScene()->GetTerrain();
		RefreshFromTerrain(pTerrain);
	}
	void CTocControl::RefreshFromTerrain(owScene::Terrain* pTerrain)
	{
		//根节点，"地形"
		HTREEITEM hRootItem = GetRootItem();	
		HTREEITEM hItem = GetChildItem(hRootItem);
		typedef std::pair< HTREEITEM , owScene::Layer*>  LayerItem_Pair;	

		//影像
		int nCount = pTerrain->getImageLayersCount();
		for (int i=0; i<nCount; i++)
		{
			owScene::ImageLayer* pLyr = pTerrain->getImageLayer(i);
			RasterSource* ras = dynamic_cast<RasterSource*>(pLyr->getDataSource());
			if(!ras)
				continue;

			std::string strName = pLyr->getName();
			HTREEITEM hTexItem = InsertItem(strName.c_str(),hItem);
			m_LayerItemMap.insert(LayerItem_Pair(hTexItem,pLyr));
		}

		//高程
		nCount = pTerrain->getElevationLayersCount();
		hItem = GetNextItem(hItem,TVGN_NEXT);
		for (int i=0; i<nCount; i++)
		{
			owScene::ElevationLayer* pLyr = pTerrain->getEvelationLayer(i);
			std::string strName = pLyr->getName();

			HTREEITEM hEleItem = InsertItem(strName.c_str(),hItem);
			m_LayerItemMap.insert(LayerItem_Pair(hEleItem,pLyr));
		}

		//矢量
		hItem = GetNextItem(hItem,TVGN_NEXT);

		nCount = pTerrain->getFeatureLayersCount();
		for (int i=0; i<nCount; i++)
		{
			owScene::FeatureLayer* pLyr = pTerrain->getFeatureLayer(i);
			std::string strName = pLyr->getName();

			HTREEITEM hEleItem = InsertItem(strName.c_str(),hItem);
			m_LayerItemMap.insert(LayerItem_Pair(hEleItem,pLyr));
		}

		nCount = pTerrain->getImageLayersCount();
		for (int i=0; i<nCount; i++)
		{
			owScene::ImageLayer* pLyr = pTerrain->getImageLayer(i);
			owScene::FeatureSource * fs = dynamic_cast<owScene::FeatureSource*>(pLyr->getDataSource());
			if(!fs)
				continue;

			std::string strName = pLyr->getName();
			HTREEITEM hTexItem = InsertItem(strName.c_str(),hItem);
			m_LayerItemMap.insert(LayerItem_Pair(hTexItem,pLyr));
		}


	}
	void CTocControl::AddLayer(owScene::Layer* player, BOOL bExpand)
	{
		std::string strName = player->getName();
		owScene::ElevationLayer* pEleLayer = dynamic_cast<owScene::ElevationLayer*>(player);
		HTREEITEM hRootItem = GetRootItem();
		if (pEleLayer)
		{
			HTREEITEM hItem = this->GetChildItem(hRootItem);
			return;
		}
	}
	//通过图层的指针查找它在树中的节点
	HTREEITEM CTocControl::SearchItemByLayer(owScene::Layer* ptrLayer)
	{
		std::map<HTREEITEM, owScene::Layer*>::const_iterator Layer_Iterator;

		for (Layer_Iterator = m_LayerItemMap.begin(); Layer_Iterator != m_LayerItemMap.end(); Layer_Iterator++)
		{
			if (Layer_Iterator->second == ptrLayer)
			{
				break;
			}

		}

		if (Layer_Iterator == m_LayerItemMap.end())
		{
			return NULL;
		}

		return Layer_Iterator->first;
	}
	void CTocControl::DeleteLayer(owScene::Layer*  pLayer)
	{
	}
	void CTocControl::DeleteAllLayers()
	{
	}
	void CTocControl::OnZoomToLayer()
	{
		HTREEITEM hItem = GetSelectedItem();
		std::map<HTREEITEM, owScene::Layer*>::const_iterator Layer_Iterator;
		for (Layer_Iterator = m_LayerItemMap.begin(); Layer_Iterator != m_LayerItemMap.end(); Layer_Iterator++)
		{
			if (Layer_Iterator->first == hItem)
			{
				break;
			}
		}
		if (Layer_Iterator != m_LayerItemMap.end())
		{
			owScene::Layer* pLyr = Layer_Iterator->second;
			owScene::Scene* pScene = m_pOSG->getScene();
			owScene::Terrain* pTerrain = pScene->GetTerrain();
			osg::Matrix matrix;
			m_pOSG->getTerrainManipulator()->LookAtLayer(pLyr,matrix);
			osgViewer::Viewer* pView = m_pOSG->getViewer();
			owNavi::FlyTo(pView,pLyr,matrix);
		}
	}
	void CTocControl:: OnRButtonDown(UINT nFlags, CPoint point)
	{
		CDllResource hdll;
		SetFocus();
		UINT flag;
		HTREEITEM hHit = HitTest(point, &flag);
		if(hHit && (flag & TVHT_ONITEM))
			SelectItem(hHit);

		std::map<HTREEITEM, owScene::Layer*>::const_iterator Layer_Iterator;
		for (Layer_Iterator = m_LayerItemMap.begin(); Layer_Iterator != m_LayerItemMap.end(); Layer_Iterator++)
		{
			if (Layer_Iterator->first == hHit)
			{
				break;
			}
		}
		if (Layer_Iterator != m_LayerItemMap.end())
		{
			CMenu menu;
			if(!menu.LoadMenu(IDR_MENU_LAYER))
				return;
			CMenu* pPopup = menu.GetSubMenu(0);
			CPoint srnPoint = point;
			ClientToScreen(&srnPoint);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, srnPoint.x, srnPoint.y, dynamic_cast<CWnd*>(this));
		}
	}


}//namespace Control
