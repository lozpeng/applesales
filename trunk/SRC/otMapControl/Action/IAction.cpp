#include "StdAfx.h"
#include "IAction.h"
#include "../otMapControl.h"
#include "../otMapCtrl.h"
#include "ActionPan.h"
#include "ActionZoomIn.h"
#include "ActionZoomOut.h"
#include "ActionDrawPolygonElement.h"
#include "ActionDrawPolylineElement.h"
#include "ActionDrawRectangleElement.h"
#include "ActionDrawSimpleTextElement.h"
#include "ActionSelectByRect.h"
#include "ActionSelectByPoint.h"
#include "ActionSelByPolygon.h"
#include "ActionSelectElements.h"
#include "ActionSelByCircle.h"
#include "ActionSelectByLine.h"
#include "ActionFeatureInfo.h"
#include "ActionDrawBezierCurveElement.h"
#include "ActionDrawSimpleMarkerElement.h"
#include "ActionDrawFreehandLine.h"

std::map<long,IAction*> IAction::gActions;

std::vector<long> IAction::gActionStack;


IAction::IAction(long id)
{
	m_actionID = id;
	m_pMapCtrl =NULL;
	m_pMap =NULL;
}

IAction::~IAction()
{

}


long IAction::GetActionID()
{
	return m_actionID;
}

void IAction::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	m_pMapCtrl =pMapCtrl;

	m_pMap =pMap;
	m_nStatus = 0; 
	gActionStack.clear();
}

void IAction::LButtonDownEvent (UINT nFlags, CPoint point)
{

}

void IAction::LButtonUpEvent (UINT nFlags, CPoint point)
{

}

void IAction::LButtonDblClkEvent (UINT nFlags, CPoint point)
{

}

void IAction::RButtonDownEvent (UINT nFlags, CPoint point)
{

}

void IAction::MouseMoveEvent (UINT nFlags, CPoint point)
{

}

void IAction::KeyDownEvent (UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void IAction::KeyUpEvent (UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void IAction::UpdateMouseCursor()
{

}

void IAction::UpdateToolBar()
{

}

IAction* IAction::FindAction(long type)
{
	std::map<long,IAction*>::iterator iter;
	iter =gActions.find(type);
	if(iter!=gActions.end())
	{
		return iter->second;
	}
	return NULL;
}


void IAction::RegisterAction(long type, IAction* pAction)
{
	gActions[type] = pAction;
}

void IAction::RegisterAll()
{
    IAction *p;
	p =new CActionZoomOut();
	p =new CActionZoomin();
	p =new CActionPan();
	p =new CActionDrawPolygonElement();
	p =new CActionDrawPolylineElement();
	p =new CActionDrawRectangleElement();
	p =new CActionDrawSimpleTextElement();
	//p =new CActionSelectElements();
	p =new CActionSelByPolygon();
	p =new CActionSelByPoint();
	p =new CActionSelByRect();
	p =new CActionSelByLine();
	p =new CActionSelByCircle();
	p =new CActionFeatureInfo();
	p =new CActionDrawBezierCurveElement();
	p =new CActionDrawSimpleMarkerElement();
	p =new CActionDrawFreehandLine();
}

void IAction::UnRegisterAll()
{
   std::map<long,IAction*>::iterator iter;
   for(iter =gActions.begin();iter!=gActions.end();iter++)
   {
	   delete iter->second;
   }
   gActions.clear();
}