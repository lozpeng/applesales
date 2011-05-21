#include "StdAfx.h"
#include "EditDlgManageControl.h"
#include "SymbolPropList.h"
#include "SymbolFactory.h"
#include "IComplexSymbol.h"
#include "Resource.h"

CEditDlgManageControl::CEditDlgManageControl(void)
{
	m_pComplexSymbol = NULL;
}

CEditDlgManageControl::~CEditDlgManageControl(void)
{
}

Display::ISymbolPtr CEditDlgManageControl::GetSymbol()
{
	return m_pSymbol;
}

void CEditDlgManageControl::SetSymbol(Display::ISymbolPtr pSymbol)
{

		if ( pSymbol->GetType() & COMPLEX_SYMBOL )														//当是复合符号
		{
			m_pComplexSymbol = pSymbol;																		//传入复合符号，将当前复合符号设为成员复合符号
			m_pSymbolCopy = m_pComplexSymbol->Clone();												//创建副本给预览用
			m_pStandbyCopySymbol = m_pComplexSymbol->Clone();										//创建备用符号副本
			m_pSymbol = (Display::ISymbolPtr)(((Display::IComplexSymbolPtr)m_pComplexSymbol)->GetAt(0));//将复合符号中的一个符号付给属性控件使用

			if ( pSymbol->GetType() & MARKER_SYMBOL )														//当是点符号
			{
				m_nType = MARKER_SYMBOL;
			}
			else if ( pSymbol->GetType() & LINE_SYMBOL )													//当是线符号
			{
				m_nType = LINE_SYMBOL;
			}
			else if ( pSymbol->GetType() & FILL_SYMBOL )													//当是面符号
			{
				m_nType = FILL_SYMBOL;	
			}
		}
		else 
		{
																			//将传入的普通符号付给属性控件使用
			if( m_pComplexSymbol != NULL)
			{
				((Display::IComplexSymbolPtr)m_pComplexSymbol)->SetSymbol(m_ComplexSymbolLayerCL.GetSelect() ,pSymbol );
				m_pSymbolCopy = m_pComplexSymbol->Clone();
				return;
			}
			m_pStandbyCopySymbol = pSymbol->Clone();												//创建备用副本
			m_pSymbol = pSymbol;	
			if ( pSymbol->GetType() & MARKER_SYMBOL )														//当是点符号
			{
				m_pComplexSymbol = Display::CSymbolFactory::CreateSymbol( COMPLEX_MARKER_SYMBOL );
				m_nType = MARKER_SYMBOL;
			}		
			else if ( pSymbol->GetType() & LINE_SYMBOL )													//当是线符号
			{
				m_pComplexSymbol = Display::CSymbolFactory::CreateSymbol(COMPLEX_LINE_SYMBOL);
				m_nType = LINE_SYMBOL;
			}
			else if ( pSymbol->GetType() & FILL_SYMBOL )													//当是面符号
			{
				m_pComplexSymbol = Display::CSymbolFactory::CreateSymbol(COMPLEX_FILL_SYMBOL);
				m_nType =FILL_SYMBOL;	
			}

			((Display::IComplexSymbolPtr)m_pComplexSymbol)->Add( m_pSymbol );								//将已知传入的符号添加到空复合符号
			m_pSymbolCopy = m_pComplexSymbol->Clone();												//为预览创建副本
			
		}


	

	/*switch (pSymbol->GetType())
	{
	case OT_SIMPLE_MARK_SYMBOL:
	case OT_CHAR_MARK_SYMBOL:
	case OT_ARROW_MARK_SYMBOL:
	case OT_PIC_MARK_SYMBOL:
		{
			m_pSymbol = pSymbol;
			m_pComplexSymbol = Display::CSymbolFactory::CreateSymbol( OT_COMPLEX_MARK_SYMBOL );
			((Display::IComplexMarkSymbolPtr)m_pComplexSymbol)->Add( m_pSymbol );
			m_pSymbolCopy=m_pComplexSymbol->Clone();
			m_pStandbyCopySymbol=m_pComplexSymbol->Clone();
			m_nType=OT_MARK_SYMBOL;
		}
		break;
	case OT_COMPLEX_MARK_SYMBOL:
		{
			m_pComplexSymbol=pSymbol;
			m_pSymbolCopy=m_pComplexSymbol->Clone();
			m_pStandbyCopySymbol=m_pComplexSymbol->Clone();
			m_pSymbol=(Display::ISymbolPtr)(((Display::IComplexMarkSymbolPtr)m_pComplexSymbol)->GetAt(0));
			m_nType=OT_MARK_SYMBOL;
		}
		break;
	case OT_SIMPLE_LINE_SYMBOL:
	case OT_ADV_LINE_SYMBOL:
	case OT_MARK_LINE_SYMBOL:
	case OT_HASH_LINE_SYMBOL:
	case OT_PIC_LINE_SYMBOL:
		{
			m_pComplexSymbol=Display::CSymbolFactory::CreateSymbol(OT_COMPLEX_LINE_SYMBOL);
			((Display::IComplexLineSymbolPtr)m_pComplexSymbol)->Add(pSymbol);
			m_pSymbolCopy=m_pComplexSymbol->Clone();
			m_pStandbyCopySymbol=m_pComplexSymbol->Clone();
			m_pSymbol=pSymbol;
			m_nType=OT_LINE_SYMBOL;
		}
		break;
	case OT_COMPLEX_LINE_SYMBOL:
		{
			m_pComplexSymbol=pSymbol;
			m_pSymbolCopy=m_pComplexSymbol->Clone();
			m_pStandbyCopySymbol=m_pComplexSymbol->Clone();
			m_pSymbol=(Display::ISymbolPtr)(((Display::IComplexLineSymbolPtr)m_pComplexSymbol)->GetAt(0));
			m_nType=OT_LINE_SYMBOL;
		}
		break;
	case OT_SIMPLE_FILL_SYMBOL:
	case OT_MARK_FILL_SYMBOL:
	case OT_LINE_FILL_SYMBOL:
	case OT_PIC_FILL_SYMBOL:
		{
			m_pComplexSymbol=Display::CSymbolFactory::CreateSymbol(OT_COMPLEX_FILL_SYMBOL);
			((Display::IComplexFillSymbolPtr)m_pComplexSymbol)->Add(pSymbol);
			m_pSymbolCopy=m_pComplexSymbol->Clone();
			m_pStandbyCopySymbol=m_pComplexSymbol->Clone();
			m_pSymbol=pSymbol;
			m_nType=OT_FILL_SYMBOL;	
		}
		break;
	case OT_COMPLEX_FILL_SYMBOL:
		{	
			m_pComplexSymbol=pSymbol;
			m_pSymbolCopy=m_pComplexSymbol->Clone();
			m_pStandbyCopySymbol=m_pComplexSymbol->Clone();
			m_pSymbol=(Display::ISymbolPtr)(((Display::IComplexFillSymbolPtr)m_pComplexSymbol)->GetAt(0));
			m_nType=OT_FILL_SYMBOL;
		}
		break;
	
	}*/
}

//SYMBO_LTYPE CEditDlgManageControl::GetSymbolType(Display::ISymbolPtr pSymbol)
//{
//	SYMBO_LTYPE symbolType = pSymbol->GetType();
//	if ( ( SYMBO_LTYPE markSymbolType = ( symbolType & OT_MARK_SYMBOL ) ) == OT_MARK_SYMBOL )
//	{
//		
//	} 
//	else
//	{
//
//	}
//
//}


void CEditDlgManageControl::OnSymbolPropChanged( Display::ISymbolPtr newSymbol , CWnd *wnd )
{
	((Display::IComplexSymbolPtr)m_pComplexSymbol)->SetSymbol( m_ComplexSymbolLayerCL.GetSelect() , newSymbol );
	UpdateComplexSymbolLayerCtrl();

	SetCopySymbol();

	PostMessage( wnd->m_hWnd , WM_REPAINTLEGEND , 0 , 0 );
}

void CEditDlgManageControl::UpdateComplexSymbolLayerCtrl()
{
	m_ComplexSymbolLayerCL.UpDataCSLC( m_pComplexSymbol ,(SYMBOL_TYPE)m_nType );
}
void CEditDlgManageControl::InitComplexSymbolLayerCtrl( void )
{
	RECT rc;
	rc.bottom = 47;
	rc.top = 0;
	rc.left = 0;
	rc.right = 120;
	m_ComplexSymbolLayerCL.InitComplexSymbolLayerCtrl( &rc , IDB_STATE , 24 );
	m_ComplexSymbolLayerCL.UpDataCSLC( m_pComplexSymbol ,(SYMBOL_TYPE)m_nType );
	m_ComplexSymbolLayerCL.SetManageControl(this);
	SetCopySymbol();

}

void CEditDlgManageControl::ReSetSymboltoPropList(Display::ISymbolPtr newSymbol)
{
	SYMBOL_TYPE type = newSymbol->GetType();
	PostMessage( m_pSymbolPropList->GetParent()->m_hWnd , WM_SETSYMBOLSTYLE , type , 0 );
	PostMessage( m_pSymbolPropList->GetParent()->m_hWnd , WM_SETSYMBOLUNIT , newSymbol->GetUnit()  , 0 );
	m_pSymbolPropList->InitSymbolPropList( type );
	m_pSymbolPropList->SetSymbol( newSymbol );
}

void  CEditDlgManageControl::ResetSymboltoLengend(Display::ISymbolPtr newSymbol)
{
	

}

void CEditDlgManageControl::UPdateSymbol( int nIndex, int nState )
{
	bool bState;
	if( nState==1 || nState==3 )
	{
		bState=false;
	}
	else 
	{
		bState=true;
	}
	(( Display::IComplexSymbolPtr )m_pComplexSymbol)->SetSymbolVisible( nIndex , bState );
}

void CEditDlgManageControl::SelectSymbol(int nIndex) 
{
	//重置属性列表及符号类型下拉框符号单位下拉框
	ReSetSymboltoPropList(((Display::IComplexSymbolPtr)m_pComplexSymbol)->GetAt(nIndex));
}
void CEditDlgManageControl::SetCopySymbol(void)
{
	m_pSymbolCopy = m_pComplexSymbol->Clone();
}
int CEditDlgManageControl::GetSelect()
{
	return m_ComplexSymbolLayerCL.GetSelect();
}
void CEditDlgManageControl::SetPropList( int nSelect )
{
	ReSetSymboltoPropList( (( Display::IComplexSymbolPtr )m_pComplexSymbol)->GetAt(nSelect));
}
void CEditDlgManageControl::SetSelect(int nSelect)
{
	m_ComplexSymbolLayerCL.SetSelect(nSelect);
}

void CEditDlgManageControl::ReSetSelectIndexToBegin()
{
	m_ComplexSymbolLayerCL.SetSelect(0);
}