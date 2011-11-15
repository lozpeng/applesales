#include "StdAfx.h"
#include "InternalControl.h"

CInternalControl::CInternalControl(void)
{
   
}

CInternalControl::~CInternalControl(void)
{
   
}

void CInternalControl::CreateAss(std::string Name)
{
	Framework::IUIObject::CreateAss(Name);
}


bool CInternalControl::Create(CWnd *pWnd)
{
	if(!pWnd)
	{
		return false;
	}
	m_hClientDC = ::GetDC(pWnd->GetSafeHwnd());
	m_hMemDC = ::CreateCompatibleDC(m_hClientDC);

	m_hCtrlWnd = pWnd->GetSafeHwnd();

	//创建一个新地图
	Carto::CMapPtr ptrMap = new Carto::CMap();


	ptrMap->SetName("Map--1");

	Framework::IMapCtrl::SetMap(ptrMap);

	return true;
}