#include "StdAfx.h"
#include "ActionZoomActualSize.h"
#include "../otMapControl.h"
#include "../otMapCtrl.h"
#include "Map.h"


CActionZoomActualSize::CActionZoomActualSize() : IAction(actionZoomActualSize)
{
	RegisterAction(actionZoomActualSize,this);
}

CActionZoomActualSize::~CActionZoomActualSize()
{

}
void CActionZoomActualSize::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	IAction::Init(pMapCtrl,pMap);

}
void CActionZoomActualSize::Triger()
{
	m_pMap->GetDisplay()->GetDisplayTransformation().SetScale(1);

	//IAction::Triger();

	//m_pMapCtrl->UpdateControl(drawAll);
}