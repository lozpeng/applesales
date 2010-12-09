#include "StdAfx.h"
#include "ElementOperationStack.h"

namespace Element{

CElementOperationStack::CElementOperationStack()
{
	m_pLayer = NULL;

	m_nMaxRecord = 50;

	m_iterCurPos = m_OperationStack.begin();
}

CElementOperationStack::CElementOperationStack(Carto::CGraphicLayerPtr pLayer)
{
	m_pLayer = pLayer;

	m_nMaxRecord = 50;

	m_iterCurPos = m_OperationStack.begin();
}

CElementOperationStack::~CElementOperationStack(void)
{
}

BOOL CElementOperationStack::CanUndo()
{
	if(m_iterCurPos == m_OperationStack.begin())
		return FALSE;

	return (*(m_iterCurPos-1))->CanUndo();
}

BOOL CElementOperationStack::CanRedo()
{
	if(m_iterCurPos == m_OperationStack.end())
		return FALSE;

	return (*m_iterCurPos)->CanRedo();
}

void CElementOperationStack::Redo()
{
	if(m_iterCurPos == m_OperationStack.end())
		return;

	if((*m_iterCurPos)->CanRedo())
	{
		(*m_iterCurPos)->Redo();

		if( m_iterCurPos != m_OperationStack.end())
			m_iterCurPos++;
	}		
}

void CElementOperationStack::Undo()
{
	if( m_iterCurPos != m_OperationStack.begin() )
		m_iterCurPos--;

	if((*m_iterCurPos)->CanUndo())
	{
		(*m_iterCurPos)->Undo();		
	}		
}

void CElementOperationStack::AddOperation(OP_TYPE opType, CElementCollection elements)
{
	CElementOperationPtr pOper(new CElementOperation(m_pLayer));

	if(!pOper->SetOperation(opType, elements))
		return;

	if(m_iterCurPos != m_OperationStack.end() && m_OperationStack.size()!=0)
	{
		m_OperationStack.erase(m_iterCurPos, m_OperationStack.end());

		//(*m_iterCurPos)->SetCanUndo(TRUE);
	}	

	m_OperationStack.push_back(pOper);

	if(m_OperationStack.size()>m_nMaxRecord)
		m_OperationStack.erase(m_OperationStack.begin());

	m_iterCurPos = m_OperationStack.end();	
}

void CElementOperationStack::AddOperation(OP_TYPE opType, IElementPtr element)
{
	CElementOperationPtr pOper(new CElementOperation(m_pLayer));

	if(!pOper->SetOperation(opType, element))
		return;

	if(m_OperationStack.size()!=0 && m_iterCurPos != m_OperationStack.end())
	{
		m_OperationStack.erase(m_iterCurPos, m_OperationStack.end());

		//(*m_iterCurPos)->SetCanUndo(TRUE);
	}

	m_OperationStack.push_back(pOper);

	if(m_OperationStack.size()>m_nMaxRecord)
		m_OperationStack.erase(m_OperationStack.begin());

	m_iterCurPos = m_OperationStack.end();
}

void CElementOperationStack::RemoveLastOperation()
{
	if(m_iterCurPos == m_OperationStack.end() && m_iterCurPos != m_OperationStack.begin())
		m_iterCurPos--;

	m_OperationStack.pop_back();
}

void CElementOperationStack::ClearOperation()
{
	m_OperationStack.clear();

	m_iterCurPos = m_OperationStack.begin();
}

void CElementOperationStack::SetLayer(Carto::CGraphicLayerPtr pLayer)
{
	m_pLayer = pLayer;
}

};