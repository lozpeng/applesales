#ifndef _MAPTREECONTROL_H_
#define _MAPTREECONTROL_H_

#include <afxcmn.h>
#include "ControlDefine.h"
#include "ITocCtrl.h"
#include "owScene/Terrain.h"
#include "MFC_OSG.h"

namespace Control
{

	class CONTROL_DLL CTocControl : public CTreeCtrl,public Framework::ITocCtrl
	{
		DECLARE_DYNAMIC(CTocControl)

	public:
		CTocControl();
		virtual ~CTocControl();

	public:
		virtual BOOL	CreateControl(void* pParent , long nID );
	public:
		afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void	OnZoomToLayer();
		afx_msg void	OnRButtonDown(UINT nFlags, CPoint point);
	protected:
		DECLARE_MESSAGE_MAP()
	public:
		void			Init();
		void			RefreshFromOSG(cOSG* pOsg);
		void			RefreshFromTerrain(owScene::Terrain* pTerrain);
		void			AddLayer(owScene::Layer* player, BOOL bExpand = TRUE);
		void			DeleteLayer(owScene::Layer*  pLayer);
		void			DeleteAllLayers();
	protected:
		HTREEITEM		SearchItemByLayer(owScene::Layer* ptrLayer);
		std::map		<HTREEITEM, owScene::Layer*> m_LayerItemMap;
		cOSG*			m_pOSG;
	};

}

#endif