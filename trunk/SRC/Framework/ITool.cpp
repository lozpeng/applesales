#include "StdAfx.h"
#include "ITool.h"

namespace Framework
{

std::map<std::string,ITool*> ITool::gTools;

ITool::ITool(const char* name)
{
	m_pTarget =NULL;
    RegisterTool(name,this);
}

ITool::~ITool(void)
{
}

std::string ITool::GetName()
{
	return m_strName;
}

void ITool::Initialize(IUIObject *pTarget)
{
    m_pTarget =pTarget;
}

void ITool::LButtonDownEvent (UINT nFlags, CPoint point)
{

}

void ITool::LButtonUpEvent (UINT nFlags, CPoint point)
{

}

void ITool::LButtonDblClkEvent (UINT nFlags, CPoint point)
{

}

void ITool::RButtonDownEvent (UINT nFlags, CPoint point)
{

}

void ITool::MouseMoveEvent (UINT nFlags, CPoint point)
{

}

void ITool::KeyDownEvent (UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void ITool::KeyUpEvent (UINT nChar, UINT nRepCnt, UINT nFlags)
{

}



ITool* ITool::FindTool(std::string strName)
{
	std::map<std::string,ITool*>::iterator iter =gTools.find(strName);
	if(iter==gTools.end())
	{
		return NULL;
	}

	return iter->second;
}

ITool* ITool::Clone()
{
	return NULL;
}

ITool* ITool::CreateTool(std::string strName)
{
	std::map<std::string,ITool*>::iterator iter =gTools.find(strName);
	if(iter==gTools.end())
	{
		return NULL;
	}

	return iter->second->Clone();
}

void ITool::RegisterTool(std::string strName, ITool* pTool)
{
	if(FindTool(strName)==NULL)
	{
        gTools[strName] = pTool;
	}
	
}

}
