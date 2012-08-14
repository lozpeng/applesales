#include "stdafx.h"
#include "DllResource.h"
#include "IWorkspace.h"
#include "FeatureLayer.h"
#include "IMapCtrl.h"
#include "MapControl.h"
#include "AttributeTable.h"
#include "shapefil.h"
#include "IFeatureSelection.h"
#include "EditorDef.h"
#include "CEditor.h"

#include "DlgConditionSelect.h"
#include "DlgAddField.h"
#include "DlgFRField.h"
#include "DlgFieldProperty.h"
#include "DlgAttrTableProperty.h"
#include "DlgFieldCalculate.h"
#include "DlgFieldStatics.h"

#include <algorithm>

static CString g_strOldFloatFormat = CBCGPGridRow::m_strFormatFloat;
static CString g_strOldDoubleFormat = CBCGPGridRow::m_strFormatDouble;

namespace Control
{

static BOOL CALLBACK GridCallback (BCGPGRID_DISPINFO* pdi, LPARAM lp)
{
	return TRUE;
}

CAttributeTable::CAttributeTable()
{
	m_bEditMode = false;

	m_bLockSelection = false;

	m_CurRow = -1;

	m_CurColumn = -1; 

	m_nHitColumn = -1;

	m_bIsOupputAll = false;

	m_nDecimalNum = 6;

	//初始化选择背景色
	//选择行的颜色
	COLORREF clrSelBackground = m_ColorData.m_SelColors.m_clrBackground;
	if ( clrSelBackground == (COLORREF) -1 )
		clrSelBackground = globalData.clrHilite;

	m_ColorData.m_SelColors.m_clrBackground = clrSelBackground;
	InitColors();
}

CAttributeTable::~CAttributeTable()
{
	m_pFeatureClass.reset();

	m_allFields.clear();
	m_indexes.clear();
	m_sortlist.clear();
	m_curFeature.reset();
	m_pSelection.reset();

	CBCGPGridRow::m_strFormatFloat = g_strOldFloatFormat;
	CBCGPGridRow::m_strFormatDouble = g_strOldDoubleFormat;
}

BOOL CAttributeTable::CreateControl(std::string Name, void *pParent, long nID)
{
	CreateAss( Name );

	CWnd *pWnd = (CWnd*)(pParent);

	BOOL bRet = Create( WS_CHILD |WS_VISIBLE , CRect(0,0,0,0) , pWnd , nID );

	return bRet;
}



BEGIN_MESSAGE_MAP(Control::CAttributeTable, CBCGPGridCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
	
	ON_COMMAND(IDM_FLASH, &CAttributeTable::OnFlash)
	ON_COMMAND(IDM_PANTO, &CAttributeTable::OnPanto)
	ON_COMMAND(IDM_ZOOMTO, &CAttributeTable::OnZoomto)
	ON_COMMAND(IDM_SEL_UNSEL, &CAttributeTable::OnSelUnsel)
	ON_COMMAND(IDM_SEL_REVERSE, &CAttributeTable::OnSelReverse)
	ON_COMMAND(IDM_COPY_ROW, &CAttributeTable::OnCopyRow)
	ON_COMMAND(IDM_PASTE_ROW, &CAttributeTable::OnPasteRow)
	ON_COMMAND(IDM_DEL_ROW, &CAttributeTable::OnDelRow)


	ON_COMMAND(IDM_SORT_ASD, &CAttributeTable::OnSortAsd)
	ON_COMMAND(IDM_SORT_DES, &CAttributeTable::OnSortDes)
	ON_COMMAND(IDM_FIELD_CAL, &CAttributeTable::OnFieldCal)
	ON_COMMAND(IDM_GEOMETRY_CAL, &CAttributeTable::OnGeometryCal)
	ON_COMMAND(IDM_HIDE_FIELD, &CAttributeTable::OnHideField)
	ON_COMMAND(IDM_DEL_FIELD, &CAttributeTable::OnDelField)
	ON_COMMAND(ID_FREEZE_UNFREEZE, &CAttributeTable::OnFreezeUnfreeze)
	ON_COMMAND(IDM_SET_FIELDPRO, &CAttributeTable::OnSetFieldPro)
END_MESSAGE_MAP()

int CAttributeTable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	SetWholeRowSel(TRUE);
	EnableMarkSortedColumn (FALSE);
	EnableHeader (TRUE, BCGP_GRID_HEADER_HIDE_ITEMS);
	SetReadOnly();
	
	return 0;
}

bool CAttributeTable::TableIsOpen()
{
	if(m_pFeatureClass)
	{
		return true;
	}
	return false;
}

void CAttributeTable::CloseTable()
{
	
	//取消选择
	CBCGPGridItemID id;
	SetCurSel (id, SM_NONE, FALSE);
	
	m_pFeatureClass.reset();

//	m_pLayer.reset();
	m_allFields.clear();
	m_indexes.clear();
	m_sortlist.clear();
	m_curFeature.reset();
	m_pSelection.reset();
    
	m_totalRecord =0;
	m_bEditMode =false;
	SetReadOnly();

	RemoveAll();
	DeleteAllColumns();
}

bool CAttributeTable::OpenTable(Geodatabase::IFeatureClassPtr pFeatureClass, bool bIsSelDispField )
{
	ShowWindow( SW_SHOW );
	CDllResource dllRes;

	if(!pFeatureClass)
		return false;
	
	if(TableIsOpen())
		CloseTable();

	//设置矢量数据源
	m_pFeatureClass =pFeatureClass;
	long lFieldCount = 0;
	lFieldCount =m_pFeatureClass->FieldCount();
	m_cDisplayFieldArray.RemoveAll();

	//如果选择显示字段
	if(bIsSelDispField)
	{
		
	}
	else
	{
		//获取要显示的字段名称
		Geodatabase::CFieldPtr pField;
		for(int i=1;i<=lFieldCount;i++)
		{
			pField = m_pFeatureClass->GetField(i);

			m_cDisplayFieldArray.Add(pField->GetName().c_str());
		}
	}

	if(m_cDisplayFieldArray.GetSize() <= 0)
	{
		m_pFeatureClass =NULL;
		return false;
	}

	//通过FeatureClass来获取属性
	m_CurRow=1;
	//显示的字段的数目
	lFieldCount=m_cDisplayFieldArray.GetSize();
	long lItemCount = 0;
	long lValidItemCount = 0;
	lValidItemCount =m_pFeatureClass->FeatureCount();
	lItemCount =lValidItemCount;

	long cx=0;
	long lFieldWidth = 0;
	long lFieldType = 0;
	long lFieldDec = 0;
	long lindex;

	CString fieldname;
	Geodatabase::CFieldPtr pField;
	for(long i = 0; i < m_cDisplayFieldArray.GetSize(); i++)
	{
		fieldname =m_cDisplayFieldArray[i];
		lindex = m_pFeatureClass->FindField(fieldname);
		m_indexes.push_back(lindex);
		pField =m_pFeatureClass->GetField(lindex);
		m_allFields.push_back(pField);
	}

	for(long i=0;i<lFieldCount;i++)
	{
		fieldname =m_cDisplayFieldArray[i];
		//加入新列
		InsertColumn (i, fieldname, 100);
		//得到字段类型
		lFieldType =m_allFields[i]->GetType();

		switch(lFieldType)
		{
		case Geodatabase::FTYPE_GEOMETRY:
		case Geodatabase::FTYPE_BLOB:
			SetColumnWidth(i, 100);
			break;
		case Geodatabase::FTYPE_STRING:
			SetColumnWidth(i, 150);
			break;
		}
	}

	if(lItemCount <= 0)
	{
		EnableVirtualMode (GridCallback, (LPARAM) this);
		////设置列表显示的最大行数
		SetVirtualRows(0);

		SendMessage2Parent(WM_UPDATESELECTNUM);
		return false;
	}
	
	CString ListStr;
	CString csField;
	long lRow=0;
	long lRecLength = 0;
	Geodatabase::CSimpleQuery indexquery;
	indexquery.AddField(m_cDisplayFieldArray[0]);
	//首先执行一次查询，将所有要显示的要素的ID查出来
	Geodatabase::IRowPtr pRow;
	Geodatabase::ICursorPtr pCursor =pFeatureClass->Query(&indexquery);
	if(!pCursor)
		return false;

	while(!pCursor->IsEOF())
	{
		pRow =pCursor->NextRow();
		if(!pRow)
			continue;
	
		m_sortlist.push_back(pRow->GetId());
	}

	EnableVirtualMode (GridCallback, (LPARAM) this);
	////设置列表显示的最大行数
	SetVirtualRows(lValidItemCount);
	
	//更新记录数
	m_totalRecord =lItemCount;
	
	AdjustLayout ();
	SendMessage2Parent(WM_UPDATESELECTNUM);

	return true;
}

//产生一个新行
CBCGPGridRow* CAttributeTable::OnCreateVirtualRow (BCGPGRID_DISPINFO* pdi)
{
	CBCGPGridRow* pRow = CBCGPGridCtrl::OnCreateVirtualRow(pdi);
	return pRow;
}

//产生一个新的subItem
CBCGPGridItem* CAttributeTable::OnCreateVirtualItem (BCGPGRID_DISPINFO* pdi)
{
	int nRow = pdi->item.nRow;
	int nColumn = pdi->item.nCol;

	if(!m_curFeature)
		m_curFeature =m_pFeatureClass->GetFeature(m_sortlist[nRow]);

	if(m_curFeature->GetId()!=m_sortlist[nRow])
		m_curFeature =m_pFeatureClass->GetFeature(m_sortlist[nRow]);

	CBCGPGridItem* pItem = NULL;
	pItem = CreateItem (nRow, nColumn);
	pItem->OnEndEdit();

	//得到字段类型
	long lFieldType =m_allFields[nColumn]->GetType();

	if(lFieldType == Geodatabase::FTYPE_BLOB || lFieldType == Geodatabase::FTYPE_GEOMETRY)
		pItem->SetValue(_T("二进制数据"));
	else if(lFieldType == Geodatabase::FTYPE_FLOAT || lFieldType == Geodatabase::FTYPE_DOUBLE)
		pItem->SetValue(m_curFeature->GetValue(m_indexes[nColumn]).GetAsDouble());
	else
		pItem->SetValue(m_curFeature->GetValue(m_indexes[nColumn]).GetasString().c_str());

	if (lFieldType == Geodatabase::FTYPE_BOOL)
	{
		Geodatabase::FieldValue &fvalue =m_curFeature->GetValue(m_indexes[nColumn]);
        if(fvalue.m_Var.bVal)
			pItem->SetValue(_T("T"));
		else
            pItem->SetValue(_T("F"));
	}

	return pItem;
}

CBCGPGridRow* CAttributeTable::CreateVirtualRow (int nRowIndex)
{
	CString strFloatFormat;
	strFloatFormat.Format( _T("%d"), m_nDecimalNum );
	strFloatFormat.Insert(0, _T("%0.") );
	strFloatFormat.Append(_T("f"));
	
	CBCGPGridRow::m_strFormatFloat = strFloatFormat;
	CBCGPGridRow::m_strFormatDouble = strFloatFormat;
	CBCGPGridRow* pRow = CBCGPGridCtrl::CreateVirtualRow( nRowIndex );
	
	return pRow;
}

bool CAttributeTable::IsEditMode() const
{
	return m_bEditMode;
}

void CAttributeTable::SetEditMode(bool bedit)
{
	m_bEditMode =bedit;
}

void CAttributeTable::ChangeFeatureFromListItem( CBCGPGridItem* pItem, int nRow, int nColumn )
{
	OnItemChanged( pItem, nRow, nColumn );
}

//当改变一个项的值时
void CAttributeTable::OnItemChanged(CBCGPGridItem* pItem, int nRow, int nColumn)
{
	CBCGPGridRow::m_strFormatFloat = g_strOldFloatFormat;
	CBCGPGridRow::m_strFormatDouble = g_strOldDoubleFormat;

	if(!m_bEditMode)
		return;

	if(!TableIsOpen())
		return;

	Geodatabase::CFieldPtr pField =m_allFields[nColumn];
	long lFieldType = pField->GetType();


	if(lFieldType == Geodatabase::FTYPE_BLOB || lFieldType == Geodatabase::FTYPE_GEOMETRY)
		return;

	Geodatabase::IWorkspace *pWorkspace =m_pFeatureClass->GetWorkspace();
	bool bEdit =false;
	if(pWorkspace->IsEditing())
		bEdit =true;
	else
		pWorkspace->StartEdit();

	//获得修改后的值
	long lRecNo =m_sortlist[nRow];
	Geodatabase::CFeaturePtr pFeature =m_pFeatureClass->GetFeature(lRecNo);
	if(!pFeature)
	{
		if(!bEdit)
			pWorkspace->StopEdit(false);
		return;
	}

	_variant_t varValue;
	long lfindex =m_indexes[nColumn];

	switch(lFieldType)
	{
	case Geodatabase::FTYPE_STRING:    //字符型
		{
			varValue =pItem->GetValue();
			pFeature->GetValue(lfindex).SetString((_bstr_t)varValue);
		}
		break;
	case Geodatabase::FTYPE_DATE:    //日期型
		{
			//得到属性值
			varValue =pItem->GetValue();
			Geodatabase::FieldValue::Date date;
			CString strDate =(const char*)((_bstr_t)(varValue));
			CString resToken;
			CString strMsg ="日期输入格式不正确";
			int curPos = 0;
			int inum;
			resToken= strDate.Tokenize(_T("-"),curPos);
			int index =0;
			while (resToken != _T(""))
			{
				index++;
				//判断是否是数字
				inum =atoi(resToken);
				if(index==1)
				{
					if(inum<0)
					{
						MessageBox(strMsg,"提示",MB_OK);
						ResetItemValue(pItem,nColumn,pFeature);
						return;
					}
                    date.Year =inum;
				}
				else if(index==2)
				{
					if(inum<0 || inum>12)
					{
						MessageBox(strMsg,"提示",MB_OK);
						ResetItemValue(pItem,nColumn,pFeature);
						return ;
					}
					date.Month =inum;
				}
				else if(index==3)
				{
					if(inum<0 || inum>31)
					{
						MessageBox(strMsg,"提示",MB_OK);
						ResetItemValue(pItem,nColumn,pFeature);
						return ;
					}
					date.Day =inum;
				}
				else
				{
					MessageBox(strMsg,"提示",MB_OK);
					ResetItemValue(pItem,nColumn,pFeature);
					return;
				}
				resToken= strDate.Tokenize(_T("-"),curPos);
			}
			pFeature->GetValue(lfindex).vtype = Geodatabase::FieldValue::VT_DATE;
			pFeature->GetValue(lfindex).m_Var.date =date;
		}
		break;
	case Geodatabase::FTYPE_DOUBLE:
	case Geodatabase::FTYPE_FLOAT:    //浮点型
		{
			varValue =pItem->GetValue();
			pFeature->GetValue(lfindex).m_Var.dVal = (double)varValue;

		}
		break;
	case Geodatabase::FTYPE_BOOL:    //逻辑型
		{
			//得到属性值
			varValue =pItem->GetValue();
			CString strVal =(const char*)((_bstr_t)(varValue));
			strVal.Trim();
			pFeature->GetValue(lfindex).vtype = Geodatabase::FieldValue::VT_BOOL;
			if(strVal.CompareNoCase("T") == 0)
                pFeature->GetValue(lfindex).m_Var.bVal = true;
			else if(strVal.CompareNoCase("F") == 0)
                 pFeature->GetValue(lfindex).m_Var.bVal =false;
			else
			{
				MessageBox("逻辑性字段输入格式不正确","提示",MB_OK);
				ResetItemValue(pItem,nColumn,pFeature);
				return;
			}
		}
		break;
	case Geodatabase::FTYPE_LONG:    //整型
		{
			varValue =pItem->GetValue();
			pFeature->GetValue(lfindex).m_Var.iVal = atol((_bstr_t)varValue);
		}
		break;
	default:
		break;
	}

	pFeature->Update();
	if(!bEdit)
	{
		pWorkspace->StopEdit(true);
	}

	//加入到编辑的回退中
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	Editor::CEditorPtr pEditor =pMap->GetEditor();
	if(pEditor)
	{
		std::vector<Carto::ILayer*> layers;
		layers.push_back(m_pLayer.get());
		pEditor->AddToCircle(layers);
	}
}

void CAttributeTable::ResetItemValue(CBCGPGridItem* pItem,int nColumn, Geodatabase::CFeaturePtr pFeature)
{
	//得到字段类型
	long lFieldType =m_allFields[nColumn]->GetType();
	if(lFieldType == Geodatabase::FTYPE_BLOB || lFieldType == Geodatabase::FTYPE_GEOMETRY)
		pItem->SetValue(_T("二进制数据"));
	else if(lFieldType == Geodatabase::FTYPE_FLOAT || lFieldType == Geodatabase::FTYPE_DOUBLE)
		pItem->SetValue(pFeature->GetValue(m_indexes[nColumn]).GetAsDouble());
	else
		pItem->SetValue(pFeature->GetValue(m_indexes[nColumn]).GetasString().c_str());

	if (lFieldType == Geodatabase::FTYPE_BOOL)
	{
		Geodatabase::FieldValue &fvalue =pFeature->GetValue(m_indexes[nColumn]);
		if(fvalue.m_Var.bVal)
			pItem->SetValue(_T("T"));
		else
			pItem->SetValue(_T("F"));
	}
	
}

void CAttributeTable::ToggleSortColumn(int nColumn)
{
	CBCGPGridCtrl::ToggleSortColumn(nColumn);

	int nColumnState = m_Columns.GetColumnState (nColumn);
	bool bAscending = true;
	if (nColumnState != 0)
		bAscending = (nColumnState <= 0);

	SetVirtualRows(m_totalRecord);
}


template<class T>
struct ValuePair
{
	T value;
	long index;

	bool operator< (const ValuePair &other)
	{
		return value<other.value;
	}
};

BOOL CAttributeTable::SortByFieldValue(int nColumn,bool bAscending)
{
	if(!m_pFeatureClass)
		return FALSE;

	long lfieldindex =m_indexes[nColumn];
	Geodatabase::CFieldPtr pField = m_allFields[nColumn];

	if(!pField)
		return FALSE;
	
	//得到字段类型
	long lFieldType =pField->GetType();

	if(lFieldType == Geodatabase::FTYPE_BLOB || lFieldType == Geodatabase::FTYPE_GEOMETRY 
		|| lFieldType == Geodatabase::FTYPE_DATE
		|| lFieldType == Geodatabase::FTYPE_TIME || lFieldType ==Geodatabase::FTYPE_UNKNOWN)
		return FALSE;

	Geodatabase::CSimpleQuery indexquery;
	indexquery.AddField(pField->GetName().c_str());
	//首先执行一次查询，将所有要显示的要素的ID查出来
	Geodatabase::IRowPtr pRow;
	Geodatabase::ICursorPtr pCursor =m_pFeatureClass->Query(&indexquery);
	if(!pCursor)
		return FALSE;

	if(lFieldType == Geodatabase::FTYPE_DOUBLE || lFieldType == Geodatabase::FTYPE_FLOAT
		|| lFieldType == Geodatabase::FTYPE_LONG || lFieldType ==Geodatabase::FTYPE_SHORT)
	{
		std::vector<ValuePair<double>> sortvalues;
		ValuePair<double> tempValue;
		//将属性值读出来
		while(!pCursor->IsEOF())
		{
			pRow =pCursor->NextRow();
			if(!pRow)
				continue;

			tempValue.index =pRow->GetId();
			tempValue.value =pRow->GetValue(lfieldindex).GetAsDouble();
			sortvalues.push_back(tempValue);
		}

		if(sortvalues.empty())
			return FALSE;

		//排序
		std::sort(sortvalues.begin(),sortvalues.end());
		m_sortlist.clear();
		//升序
		if(bAscending)
		{
			for(size_t i=0;i<sortvalues.size();i++)
			{
				m_sortlist.push_back(sortvalues[i].index);
			}
		}
		else
		{
			//降序
			for(int i=int(sortvalues.size())-1;i>=0;i--)
			{
				m_sortlist.push_back(sortvalues[i].index);
			}
		}
	}
	else
	{
		std::vector<ValuePair<std::string>> sortvalues;
		ValuePair<std::string> tempValue;

		//将属性值读出来
		while(!pCursor->IsEOF())
		{
			pRow =pCursor->NextRow();
			if(!pRow)
				continue;
			
			tempValue.index =pRow->GetId();
			tempValue.value =pRow->GetValue(lfieldindex).GetasString();
			sortvalues.push_back(tempValue);
		}

		if(sortvalues.empty())
			return FALSE;

		//排序
		std::sort(sortvalues.begin(),sortvalues.end());
		m_sortlist.clear();
		//升序
		if(bAscending)
		{
			for(size_t i=0;i<sortvalues.size();i++)
			{
				m_sortlist.push_back(sortvalues[i].index);
			}
		}
		else
		{
			//降序
			for(int i=int(sortvalues.size())-1;i>=0;i--)
			{
				m_sortlist.push_back(sortvalues[i].index);
			}
		}
	}
	return TRUE;
}

void CAttributeTable::OnSelChanged(const CBCGPGridRange &range, BOOL bSelect)
{
	//设置当前选中的单元格是否可编辑
	if(!m_bLockSelection)
		UpdateSelection();

	long nColumn = m_idActive.m_nColumn;
	if ( nColumn < 0 )
		return;
	
	bool bColumnLocked = GetColumnLocked( nColumn );
	SetReadOnly( !m_bEditMode || bColumnLocked ); 

	CBCGPGridCtrl::OnSelChanged(range,bSelect);
}

void CAttributeTable::OnLButtonUp(UINT nFlags, CPoint point)
{
	CBCGPGridCtrl::OnLButtonUp(nFlags,point);

	//选择列
	int nColumnHit = m_Columns.HitTestColumn ( point );
	if( nColumnHit == -1 )
		return;
	
	SelectColumn( nColumnHit );

}

void CAttributeTable::UpdateSelection()
{
	Geodatabase::IFeatureSelection *pSel = NULL;
	
	pSel = new Geodatabase::IFeatureSelection(m_pFeatureClass.get());
	std::vector<long>::iterator itMaxID = std::max_element(m_sortlist.begin(), m_sortlist.end());
	if(pSel->m_flags.size() < *itMaxID)
		pSel->m_flags.resize(*itMaxID);	
	
	m_pSelection.reset(pSel);
	CBCGPGridRange* pSelRange=NULL;
	int i = 0;
	//查找哪些行被选中了
	for (POSITION pos = m_lstSel.GetHeadPosition(); pos != NULL;)
	{
		pSelRange = m_lstSel.GetNext(pos);

		for(i = pSelRange->m_nTop; i <= pSelRange->m_nBottom; i++)
		{
			int ncol = GetColumnCount()-1;
			if(pSelRange->m_nLeft == 0 && pSelRange->m_nRight == ncol)
				pSel->Add(m_sortlist[i]);
		}	
	}

	m_selRecord = pSel->Count();
	UpdateLayerSelction();
	SendMessage2Parent(WM_UPDATESELECTNUM);
}

bool CAttributeTable::CanEdit()
{
	if(!m_pFeatureClass)
		return false;

	if(m_pFeatureClass->GetWorkspace()->GetType() == Geodatabase::WT_FileSystem)
		return true;
	
	return false;
}

void CAttributeTable::SendMessage2Parent(UINT message, WPARAM wParam, LPARAM lParam )
{
	if (GetSafeHwnd () != NULL)
	{
		CWnd* pOwnerWnd = GetOwner ();
		if (pOwnerWnd != NULL)
			pOwnerWnd->SendMessage (message, wParam, lParam);
	}
}

void CAttributeTable::UpdateLayerSelction()
{
    if(!m_pLayer)
		return;

	//更新图层的选择集
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//图形选择
	(Carto::IFeatureLayerPtr(m_pLayer))->SetSelection(m_pSelection);
	pMapCtrl->UpdateControl(drawGeoSelection);
}

void CAttributeTable::TableQuery()
{
	if(!TableIsOpen())
		return;
	
	CDllResource dllRes;

	CDlgConditionSelect dlg( m_pFeatureClass.get() );
	if(dlg.DoModal()==IDOK)
	{
		CString csQryStr = dlg.mg_csCondition;
		if ( !csQryStr.IsEmpty() )
		{
			//取消排序
			std::sort(m_sortlist.begin(),m_sortlist.end());
            SetVirtualRows(m_totalRecord);
            
			//执行查询
			Geodatabase::CSimpleQuery queryfilter;
			queryfilter.SetWhereString(csQryStr);
			Geodatabase::ISelctionSetPtr pSel =m_pFeatureClass->Select(&queryfilter);

		    SetSelction(pSel);
          
			UpdateLayerSelction();
		}
	}
}


void CAttributeTable::SetSelction(Geodatabase::ISelctionSetPtr pSelection)
{
	m_pSelection = pSelection;  	
	Geodatabase::CSelctionSet *pSel =dynamic_cast<Geodatabase::CSelctionSet*>(m_pSelection.get());
	if (pSel == NULL)
	{
		//取消所有的选择
		SelectNone();
		return;
	}
	std::vector<long>::iterator itMaxID = std::max_element(m_sortlist.begin(), m_sortlist.end());
	if(pSel->m_flags.size() < *itMaxID)
		pSel->m_flags.resize(*itMaxID);		

	m_bLockSelection =true;

	CBCGPGridItemID bid;
	SetCurSel(bid,SM_NONE);
	
	long fid;
	CBCGPGridRange* pSelRange = NULL;
	int istart = -1,iend = -1;
    int j;
	int ncol = GetColumnCount()-1;
	for(int i = 0;i < m_sortlist.size();)
	{
		fid = m_sortlist[i];
		if(pSel->m_flags[fid - 1])
		{
		   istart =i;
		   //判断下面选中的记录是否和这条记录连成一片
           for(iend = istart+1; iend<m_sortlist.size(); iend++)
		   {
			   fid = m_sortlist[iend];
			   if(!pSel->m_flags[fid - 1])
			   {
				   break;
			   }
		   }
		   iend--;

		   pSelRange = new CBCGPGridRange(0, istart,ncol, iend);
		   m_lstSel.AddTail(pSelRange);

		   i = iend + 1;
		}
		else
		{
            i++;
		}
	}

	for (POSITION pos = m_lstSel.GetHeadPosition(); pos != NULL; )
	{
		pSelRange = (CBCGPGridRange*)m_lstSel.GetNext(pos);
		
		SelectRange(*pSelRange, TRUE, TRUE);
	}

    m_bLockSelection =false;

	AdjustLayout();
	SetFocus();
	
	m_selRecord = pSel->Count();

	SendMessage2Parent(WM_UPDATESELECTNUM);
}

void CAttributeTable::OnRButtonDown(UINT nFlags, CPoint point)
{
//	CBCGPGridCtrl::OnRButtonDown(nFlags,point);

	CMenu menu;

	CBCGPGridRow::ClickArea nArea ;
	CBCGPGridItemID itemID;
	CBCGPGridItem   *pItem = NULL;


	CBCGPGridRow *pHitRow = CBCGPGridCtrl::HitTest( point, itemID, pItem, &nArea, FALSE );
	
	CDllResource dllRes;

	if ( pHitRow == NULL  )

	{	int nColumnHit = m_Columns.HitTestColumn ( point );
		if( nColumnHit == -1 )
			return;
		
		m_nHitColumn = nColumnHit;
//		SelectColumn( nColumnHit );
		if ( !menu.LoadMenu( IDR_MENU_SET_COLUMN ) )
			return;

		UpdateMenuStatus(menu.GetSubMenu(0), IDR_MENU_SET_COLUMN );
	}
	else
	{
		if ( nArea == CBCGPGridRow::ClickName)
		{
			if ( !menu.LoadMenu( IDR_MENU_SET_ATTRROW ) )
				return;

			UpdateMenuStatus(menu.GetSubMenu(0), IDR_MENU_SET_ATTRROW );
		}
		else
			return;
	}
	
	CMenu* pPopup = menu.GetSubMenu(0);
	CPoint srnPoint = point;
	ClientToScreen(&srnPoint);
	if ( pPopup )
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, srnPoint.x, srnPoint.y, dynamic_cast<CWnd*>(this));
}

//Operate Rows
void CAttributeTable::OnFlash()
{
	//获得(当前Active行)鼠标定位的行
	if ( !m_idActive.IsRow() )
		return;

	int index = m_idActive.m_nRow;
	
	GEOMETRY::geom::Geometry *pGeo = m_pFeatureClass->GetFeatureShape( m_sortlist[index] );
	
	CMapControl *pMapWnd = dynamic_cast<CMapControl *>( Framework::IMapCtrl::GetActiveMapCtrl() );
	pMapWnd->SendMessage( WM_MESSAGE_FLASH, NULL, (DWORD)(void *)( pGeo ));
}

void CAttributeTable::OnPanto()
{
	if ( !m_idActive.IsRow() )
		return;

	int index = m_idActive.m_nRow;

	GEOMETRY::geom::Geometry *pGeo = m_pFeatureClass->GetFeatureShape( m_sortlist[index] );
	GEOMETRY::geom::Point *ctPt = pGeo->getCentroid();

	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;
	
	pMapCtrl->GetMap()->GetDisplay()->GetDisplayTransformation().SetGeoCenterX( ctPt->getX() );
	pMapCtrl->GetMap()->GetDisplay()->GetDisplayTransformation().SetGeoCenterY( ctPt->getY() );
	pMapCtrl->UpdateControl(drawAll);

	OnFlash();
}

void CAttributeTable::OnZoomto()
{
	if ( !m_idActive.IsRow() )
		return;

	int index = m_idActive.m_nRow;
	GEOMETRY::geom::Geometry *pGeo = m_pFeatureClass->GetFeatureShape( m_sortlist[index] );
	GEOMETRY::geom::Point *ctPt = pGeo->getCentroid();
	const GEOMETRY::geom::Envelope *env = pGeo->getEnvelopeInternal();

	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;
	
	if (typeid(*pGeo)==typeid(GEOMETRY::geom::Point))
	{
		pMapCtrl->GetMap()->GetDisplay()->GetDisplayTransformation().SetGeoCenterX( ctPt->getX() );
		pMapCtrl->GetMap()->GetDisplay()->GetDisplayTransformation().SetGeoCenterY( ctPt->getY() );
		pMapCtrl->GetMap()->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(0.1);
	}
	else
	{
		GEOMETRY::geom::Envelope viewEnv;
		viewEnv.init( (env->getMinX()*11 - env->getMaxX())/10,
					  (env->getMaxX()*11 - env->getMinX())/10,
					  (env->getMinY()*11 - env->getMaxY())/10,
					  (env->getMaxY()*11 - env->getMinY())/10);
		pMapCtrl->GetMap()->GetDisplay()->GetDisplayTransformation().FitViewBound( viewEnv, FALSE );
	}
	
	pMapCtrl->UpdateControl(drawAll);
	OnFlash();
}

void CAttributeTable::OnSelUnsel()
{
	
	CBCGPGridItemID id;
	BOOL bRedraw = TRUE;
	SetCurSel (id, SM_NONE, bRedraw);
}

void CAttributeTable::OnSelReverse()
{
	Geodatabase::CSelctionSet *pSel = new Geodatabase::IFeatureSelection(m_pFeatureClass.get());
	std::vector<long>::iterator itMaxID = std::max_element(m_sortlist.begin(), m_sortlist.end());

	if(m_pSelection)
	{
		m_pSelection->ResetIndex();

		while(!m_pSelection->IsEOF())
		{
			int fid =m_pSelection->NextID();
			if(fid<=*itMaxID)
			{
				pSel->Add(fid);
			}
		}
	}
	
	if(pSel->m_flags.size() < *itMaxID)
		pSel->m_flags.resize(*itMaxID);	
	
	pSel->m_flags.flip();
	for (int i = 0; i < pSel->m_flags.size(); ++i)
	{
		if (std::find(m_sortlist.begin(), m_sortlist.end(), i+1) == m_sortlist.end())
			pSel->m_flags[i] = false;
	}

	SetSelction( pSel );
	UpdateLayerSelction();
}

void CAttributeTable::OnCopyRow()
{
	//--------------------------
	//--复制当前选中的Feature
	//---------------------------
	m_vecCopyFeatures.clear();

	if(m_pSelection)
	{
		m_pSelection->ResetIndex();
		while(!m_pSelection->IsEOF())
		{
			int fid = m_pSelection->NextID();
			m_vecCopyFeatures.push_back( m_pFeatureClass->GetFeature(fid) );
		}
	}

	//--------------------------
	//--格式化复制字符串
	//---------------------------
	CString lpszTextForClipBoard = "";
	CString lpszTextForFormat = "";
	//格式化字段名称
	for ( int i = 0; i < m_cDisplayFieldArray.GetSize(); i++ )
	{	
		lpszTextForFormat = m_cDisplayFieldArray[i];
		if ( strlen( lpszTextForFormat ) <= 16 )
			lpszTextForFormat.Format( _T("%-16s  "), lpszTextForFormat );
		else
			lpszTextForFormat.Format( _T("%s  "), lpszTextForFormat);
	
		lpszTextForClipBoard += lpszTextForFormat;
	}

	lpszTextForClipBoard += "\r\n";
	
	//格式化选中的行
	POSITION pos = m_lstSel.GetHeadPosition();
	while ( pos != NULL)
	{
		CBCGPGridRange *pRange = m_lstSel.GetNext( pos );
		CBCGPGridItem *pItem = NULL;
		for ( int i = pRange->m_nTop; i <= pRange->m_nBottom; i++ )
		{
			CBCGPGridRow *pRow = GetRow( i );

			for ( int j = pRange->m_nLeft; j <= pRange->m_nRight; j++ )
			{
				pItem = pRow->GetItem( j );

				lpszTextForFormat = pItem->GetLabel();

				if ( strlen( lpszTextForFormat ) <= 16 )
					lpszTextForFormat.Format( _T("%-16s  "), lpszTextForFormat );
				else
					lpszTextForFormat.Format( _T("%s  "), lpszTextForFormat);

				lpszTextForClipBoard += lpszTextForFormat;
			}

			lpszTextForClipBoard += "\r\n";
		}
	}
	//--------------------------------------
	//--将格式化后的字符串复制到粘贴板
	//--------------------------------------
	HGLOBAL hglbCopy;
	LPSTR lpstrCopy;

	if ( !OpenClipboard() )
		return;

	EmptyClipboard();

	hglbCopy = GlobalAlloc( GMEM_MOVEABLE, strlen(lpszTextForClipBoard) + 1 );
	if ( hglbCopy == NULL)
	{
		CloseClipboard();
		return;
	}

	lpstrCopy = (LPSTR)GlobalLock( hglbCopy );
	memcpy( lpstrCopy, lpszTextForClipBoard, strlen(lpszTextForClipBoard) + 1 );
	GlobalUnlock( hglbCopy );

	SetClipboardData( CF_TEXT, hglbCopy );

	CloseClipboard();
}

void CAttributeTable::OnPasteRow()
{
	//复制feature
	for ( int i = 0; i < m_vecCopyFeatures.size(); i++ )
	{
		m_pFeatureClass->AddFeature( m_vecCopyFeatures[i]->Clone() );
	}

	//重新加载FeatureClass
	OpenTable( m_pFeatureClass, false );
	
	//清除复制
	m_vecCopyFeatures.clear();
}

void CAttributeTable::OnDelRow()
{
	if(m_pSelection)
	{
		m_pSelection->ResetIndex();
		while(!m_pSelection->IsEOF())
		{
			int fid = m_pSelection->NextID();
			m_pFeatureClass->DeleteFeature( fid );
		}
	}
	m_pSelection.reset();
	if(m_pLayer)
	{ 
		//更新图层的选择集
		//图形选择
		(Carto::IFeatureLayerPtr(m_pLayer))->SetSelection(m_pSelection);
	}
	
    Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(pMapCtrl)
		pMapCtrl->UpdateControl(drawAll);

	//重新加载FeatureClass
	OpenTable( m_pFeatureClass, false );
}

void CAttributeTable::UpdateMenuStatus(CMenu *pMenu, UINT nMenuID)
{	
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	
	switch(nMenuID)
	{
	case IDR_MENU_SET_ATTRROW:
		{
			//粘贴和删除记录
			if ( !pMap->GetEditor()  )
			{
				pMenu->EnableMenuItem(IDM_PASTE_ROW,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
				pMenu->EnableMenuItem(IDM_DEL_ROW,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
			}
			else
			{
				if ( pMap->GetEditor()->IsEditing() )
				{
					pMenu->EnableMenuItem(IDM_PASTE_ROW,MF_BYCOMMAND|MF_ENABLED);
					pMenu->EnableMenuItem(IDM_DEL_ROW,MF_BYCOMMAND|MF_ENABLED);
				}
				else
				{
					pMenu->EnableMenuItem(IDM_PASTE_ROW,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
					pMenu->EnableMenuItem(IDM_DEL_ROW,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
				}
			}
		}
		break;
	case IDR_MENU_SET_COLUMN:
		{
			//字段统计菜单
			CString strColumnName = GetColumnName( m_nHitColumn );
			if ( GetColumnLocked( m_nHitColumn ) )
				strColumnName = strColumnName.Left( strlen( strColumnName ) - 1 );

			long nFieldIndex = m_pFeatureClass->FindField( strColumnName );
			Geodatabase::CFieldPtr pField = m_pFeatureClass->GetField( nFieldIndex );
			
			//if ( pField->GetType() == Geodatabase::FTYPE_SHORT 
			//	|| pField->GetType() == Geodatabase::FTYPE_LONG
			//	|| pField->GetType() == Geodatabase::FTYPE_FLOAT
			//	|| pField->GetType() == Geodatabase::FTYPE_DOUBLE )
			//	//pMenu->EnableMenuItem(IDM_CAL_STASTIC, MF_BYCOMMAND|MF_ENABLED);
			//else
			//	//pMenu->EnableMenuItem(IDM_CAL_STASTIC, MF_BYCOMMAND|MF_DISABLED|MF_GRAYED );
	

			//删除字段菜单	
			if ( !pMap->GetEditor()  )
				pMenu->EnableMenuItem(IDM_DEL_FIELD,MF_BYCOMMAND|MF_ENABLED);
			else
			{
				if ( pMap->GetEditor()->IsEditing() )
					pMenu->EnableMenuItem(IDM_DEL_FIELD,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
				else
					pMenu->EnableMenuItem(IDM_DEL_FIELD,MF_BYCOMMAND|MF_ENABLED);
			}
		}
		break;
	}
}

//Operate Columns
void CAttributeTable::OnSortAsd()
{	
	bool bAscending = true;

	SortByFieldValue( m_nHitColumn, bAscending );
	SetVirtualRows(m_totalRecord);
}

void CAttributeTable::OnSortDes()
{
	bool bAscending = false;

	SortByFieldValue( m_nHitColumn, bAscending );
	SetVirtualRows(m_totalRecord);
}

void CAttributeTable::OnCalStastic()
{
	std::vector<LP_CAL_FIELDVALUE> vCalFieldsVals;
	//加入当前列
	AddColumnForStatics( m_nHitColumn, vCalFieldsVals );

	//加入其它是数字类型列的数据
	for ( int i = 0; i < GetColumnCount(); i++ )
		if ( i != m_nHitColumn )
			AddColumnForStatics( i, vCalFieldsVals );
	CDllResource dllRes;
	CDlgFieldStatics dlgFiedCal;
	dlgFiedCal.InitFieldsValues( vCalFieldsVals );
	dlgFiedCal.DoModal();
}

void CAttributeTable::OnFieldCal()
{
	if (  AfxMessageBox(  _T("该操作不可回撤，是否仍然继续？"),MB_ICONWARNING | MB_OKCANCEL ) != IDOK )
		return;

	//当前选择字段索引
	CString strColumnName = GetColumnName( m_nHitColumn );
	if ( GetColumnLocked( m_nHitColumn ) )
		strColumnName = strColumnName.Left( strlen( strColumnName ) - 1 );
	long nFieldIndex = m_pFeatureClass->FindField( strColumnName );
	
	//当前选择选择的记录号
	std::vector<long> vSelFeatureIndex;
	for (POSITION pos = m_lstSel.GetHeadPosition(); pos != NULL;)
	{
		CBCGPGridRange *pSelRange = m_lstSel.GetNext(pos);
		for(long i = pSelRange->m_nTop; i <= pSelRange->m_nBottom; i++)
		{
			if( pSelRange->m_nLeft == 0 && pSelRange->m_nRight == GetColumnCount()-1 );			
				vSelFeatureIndex.push_back( m_sortlist[i] );
		}	
	}
	
	CDllResource dllRes;
	CDlgFieldCalculate dlgFieldCal;
	dlgFieldCal.Init( nFieldIndex, vSelFeatureIndex, m_sortlist, m_pFeatureClass );
	dlgFieldCal.DoModal();

	//刷新显示
	SetVirtualRows(m_totalRecord);
}

void CAttributeTable::OnGeometryCal()
{
	if (  AfxMessageBox(  _T("该操作不可回撤，是否仍然继续？"),MB_ICONWARNING | MB_OKCANCEL ) != IDOK )
		return;
	
	//---------------添加两个字段AREA和LENGTH---------------------------
	long nIndexArea = m_pFeatureClass->FindField("AREA");
	long nIndexLength = m_pFeatureClass->FindField("LENGTH");
	
	if ( nIndexArea <= 0 )
	{
		Geodatabase::CField field;
		field.SetName( "AREA" );
		field.SetType( Geodatabase::FTYPE_DOUBLE );
		field.SetLength( (long)16 );
		field.SetPrecision( (long)6 );

		m_pFeatureClass->AddField( &field );
		nIndexArea = m_pFeatureClass->FindField("AREA");
	}

	if ( nIndexLength <= 0 )
	{
		Geodatabase::CField field;
		field.SetName( "LENGTH" );
		field.SetType( Geodatabase::FTYPE_DOUBLE );
		field.SetLength( (long)16 );
		field.SetPrecision( (long)6 );

		m_pFeatureClass->AddField( &field );
		nIndexLength = m_pFeatureClass->FindField("LENGTH");
	}
		
	//---------------计算每个Feature的Geometry的面积和周长--------------
	Geodatabase::IWorkspace *pWorkspace = m_pFeatureClass->GetWorkspace();
	bool bEdit =false;
	//矢量正在进行编辑
	if(pWorkspace->IsEditing())
		bEdit =true;
	else
		pWorkspace->StartEdit();
	
	for ( int i = 0; i < m_sortlist.size(); i++ )
	{
		Geodatabase::CFeaturePtr pFeature = m_pFeatureClass->GetFeature( m_sortlist[i] );
		if(!pFeature)
		{
			if(!bEdit)
				pWorkspace->StopEdit(false);
			return;
		}
		
		GEOMETRY::geom::Geometry *pGeometry = pFeature->GetShape();
		double dArea = pGeometry->getArea();
		double dLength = pGeometry->getLength();

		pFeature->GetValue( nIndexArea ).m_Var.dVal = dArea;
		pFeature->GetValue( nIndexLength ).m_Var.dVal = dLength;
		pFeature->Update();

	}
	
	//重新加载FeatureClass
	OpenTable( m_pFeatureClass, false );
}

void CAttributeTable::OnHideField()
{
	if ( m_Columns.GetColumnCount(TRUE) <= 2 )
		return;
	
	bool bVisible = false;
	SetColumnVisible( m_nHitColumn, bVisible );
	AdjustLayout();
}

void CAttributeTable::OnDelField()
{
	if (  AfxMessageBox(  _T("该操作不可回撤，是否仍然继续？"),MB_ICONWARNING | MB_OKCANCEL ) != IDOK )
		return;

	CString strColumnName = GetColumnName( m_nHitColumn );
	if ( GetColumnLocked( m_nHitColumn ) )
		strColumnName = strColumnName.Left( strlen( strColumnName ) - 1 );
	
	long nFieldIndex = m_pFeatureClass->FindField( strColumnName );
	if ( nFieldIndex < 0 )
		return;

	try
	{
       m_pFeatureClass->DeleteField( nFieldIndex );
	}
	catch(std::exception *e)
	{
		MessageBox(e->what());
	}

	//重新加载FeatureClass
	OpenTable( m_pFeatureClass, false );
}

void CAttributeTable::OnFreezeUnfreeze()
{
	CString strColumnName = GetColumnName( m_nHitColumn );
	if ( GetColumnLocked( m_nHitColumn ))
		strColumnName = strColumnName.Left( strlen( strColumnName ) - 1 );
	else
		strColumnName.Format("%s#", strColumnName );

	SetColumnName( m_nHitColumn, strColumnName );
	SetColumnLocked( m_nHitColumn, !GetColumnLocked( m_nHitColumn ) );
	SetVirtualRows(m_totalRecord);
}

void CAttributeTable::OnSetFieldPro()
{
	//字段名称
	CString strColumnName = GetColumnName( m_nHitColumn );
	if ( GetColumnLocked( m_nHitColumn ) )
		strColumnName = strColumnName.Left( strlen( strColumnName ) - 1 );
		
	Geodatabase::CFieldPtr pField = m_pFeatureClass->GetField( m_pFeatureClass->FindField( strColumnName ) );
	//字段类型
	Geodatabase::FIELD_TYPE fieldType = (Geodatabase::FIELD_TYPE)( pField->GetType() );
	
	//字段长度
	long nFieldLength = pField->GetLength();

	//字段精度
	long nFieldPrecision = pField->Precision();

	CDllResource dllRes;

	CDlgFieldProperty dlgFieldProp;
	dlgFieldProp.SetName( strColumnName );
	dlgFieldProp.SetType( fieldType );
	dlgFieldProp.SetLength( nFieldLength );
	dlgFieldProp.SetPrecision( nFieldPrecision );
	dlgFieldProp.SetDecimalNum( m_nDecimalNum );
	
	if ( IDOK == dlgFieldProp.DoModal() )
	{
		SetColumnVisible( m_nHitColumn, dlgFieldProp.GetVisible() );
		m_nDecimalNum = dlgFieldProp.GetDecimalNum();
		AdjustLayout();
		SetVirtualRows(m_totalRecord);
	}
}

bool CAttributeTable::SelectAll( )
{
	if(!TableIsOpen())
		return false;

	CBCGPGridItemID id;
	BOOL bRedraw = TRUE;
	SetCurSel (id, SM_ALL, bRedraw);

	return true;
}

bool CAttributeTable::SelectNone( )
{
	if(!TableIsOpen())
		return false;

	CBCGPGridItemID id;
	BOOL bRedraw = TRUE;
	SetCurSel (id, SM_NONE, bRedraw);

	return true;
}

bool CAttributeTable::ShowAllFields()
{
	if(!TableIsOpen())
		return false;

	for ( int i = 0; i < GetColumnCount(); i++ )
		SetColumnVisible( i, TRUE );

	SetVirtualRows(m_totalRecord);
	return true;
}

bool CAttributeTable::AddField()
{
	if(!TableIsOpen())
		return false;
	
	CDllResource dllRes;
	CDlgAddField dlgAddField;
	if( IDOK == dlgAddField.DoModal() )
	{
		Geodatabase::CField field;
		field.SetName( dlgAddField.GetFieldName() );
		field.SetType( (long)dlgAddField.GetFieldType() );
		field.SetLength( dlgAddField.GetLength() );
		field.SetPrecision( dlgAddField.GetPrecision() );

		try
		{
			m_pFeatureClass->AddField( &field );
		}
		catch (std::exception* e)
		{
            MessageBox(e->what());			
		}
		
	}

	//重新加载FeatureClass
	OpenTable( m_pFeatureClass, false );

	return true;
}

void CAttributeTable::FindReplace()
{
	if(!TableIsOpen())
		return;
	
	CDllResource dllRes;
	CDlgFRField dlgFRField;
	dlgFRField.DoModal();
}

void CAttributeTable::OnDestroy()
{

}

void CAttributeTable::OutputToTxt( LPCTSTR lpszFileName )
{
	if(!TableIsOpen())
		return;
	
	CFile file( lpszFileName, CFile::modeWrite |  CFile::modeCreate);

	//---------格式化输出字符串-------------
	CString lpszTextForTxt = "";
	CString lpszTextForFormat = "";
	
	for ( int i = 0; i < m_cDisplayFieldArray.GetSize(); i++ )
	{	
		lpszTextForFormat = m_cDisplayFieldArray[i];
		if ( strlen( lpszTextForFormat ) <= 16 )
			lpszTextForFormat.Format( _T("%-16s  "), lpszTextForFormat );
		else
			lpszTextForFormat.Format( _T("%s  "), lpszTextForFormat);

		lpszTextForTxt += lpszTextForFormat;
	}
	lpszTextForTxt += "\r\n";

	file.Write( lpszTextForTxt, strlen( lpszTextForTxt ) );
	lpszTextForTxt = "";
	
	std::vector<long> vOutputRows;
	if ( m_bIsOupputAll )
		GetAllRows( vOutputRows, TABLEROW_INDEX );
	else 
		GetSelectRows( vOutputRows , TABLEROW_INDEX );

	for ( int i = 0; i < vOutputRows.size(); ++i )
	{
		CBCGPGridRow *pRow = GetRow( vOutputRows[i] );
		for ( int j = 0; j < m_cDisplayFieldArray.GetSize(); j ++ )
		{
			CBCGPGridItem *pItem = pRow->GetItem( j );
			lpszTextForFormat = pItem->GetLabel();

			if ( strlen( lpszTextForFormat ) <= 16 )
				lpszTextForFormat.Format( _T("%-16s  "), lpszTextForFormat );
			else
				lpszTextForFormat.Format( _T("%s  "), lpszTextForFormat);

			lpszTextForTxt+= lpszTextForFormat;
		}

		lpszTextForTxt += "\r\n";

		file.Write( lpszTextForTxt, strlen( lpszTextForTxt ) );
		lpszTextForTxt = "";

	}
	
	file.Close();
}

void CAttributeTable::OutputToDbf( LPCTSTR lpszFileName )
{
	if(!TableIsOpen())
		return;
	
	//------------创建DBF文件--------------------
	DBFHandle hDBF = DBFCreate( lpszFileName );

	if( hDBF == NULL )
		return;

	Geodatabase::CFieldPtr pField;
	//创建DBF的字段结构
	for( long i = 1; i <= m_pFeatureClass->FieldCount(); i++ )
	{
		pField = m_pFeatureClass->GetField( i );

		if(!pField)
		{
			continue;
		}
		switch(pField->GetType())
		{
		case Geodatabase::FTYPE_LONG:
		case Geodatabase::FTYPE_SHORT:
			{
				if( pField->GetLength() == 0 )
					DBFAddField( hDBF, pField->GetName().c_str(), FTInteger, 11, 0 );		
				else
					DBFAddField( hDBF, pField->GetName().c_str(), FTInteger, pField->GetLength(), 0 );
			}
			break;
		case Geodatabase::FTYPE_FLOAT:
		case Geodatabase::FTYPE_DOUBLE:
			{
				if( pField->GetLength() == 0 )
					DBFAddField( hDBF, pField->GetName().c_str(), FTDouble, 24, pField->Precision());	
				else
					DBFAddField( hDBF, pField->GetName().c_str(), FTDouble, pField->GetLength(), pField->Precision() );
			}
			break;
		case Geodatabase::FTYPE_STRING:
			{
				if( pField->GetLength() < 1)
					DBFAddField( hDBF, pField->GetName().c_str(), FTString, 80, 0 );
				else
					DBFAddField( hDBF, pField->GetName().c_str(), FTString, pField->GetLength(), 0 );
			}
			break;
		case Geodatabase::FTYPE_TIME:
		case Geodatabase::FTYPE_DATE:
			{
				DBFAddNativeFieldType( hDBF, pField->GetName().c_str(), 'D', 8, 0 );
			}
			break;
		default:
			break;
		}
	}
	
	//------------写入DBF文件--------------------
	std::vector<long> vOutputRows;
	if ( m_bIsOupputAll )
		GetAllRows( vOutputRows, TABLEROW_INDEX );
	else 
		GetSelectRows( vOutputRows, TABLEROW_INDEX );

	for ( int i = 0; i < vOutputRows.size(); ++i )
	{
		CBCGPGridRow *pRow = GetRow( vOutputRows[i] );
		for ( int j = 0; j < m_cDisplayFieldArray.GetSize(); j ++ )
		{
			CBCGPGridItem *pItem = pRow->GetItem( j );
			_variant_t val = pItem->GetValue();

			CString szFieldName = GetColumnName( j );
			long nDBFFieldIndex = DBFGetFieldIndex( hDBF, szFieldName );
			
			pField = m_pFeatureClass->GetField( m_pFeatureClass->FindField( szFieldName ) ); 

			switch(pField->GetType())
			{
			case Geodatabase::FTYPE_LONG:
				DBFWriteIntegerAttribute( hDBF, i, nDBFFieldIndex, atol( (_bstr_t)val) );
				break;
			case Geodatabase::FTYPE_SHORT:
				DBFWriteIntegerAttribute( hDBF, i, nDBFFieldIndex, atoi( (_bstr_t)val) );
				break;
			case Geodatabase::FTYPE_FLOAT:
				DBFWriteDoubleAttribute( hDBF, i, nDBFFieldIndex, atof( (_bstr_t)val) );
				break;
			case Geodatabase::FTYPE_DOUBLE:
				DBFWriteDoubleAttribute( hDBF, i, nDBFFieldIndex, atof( (_bstr_t)val) );
				break;
			case Geodatabase::FTYPE_STRING:
				DBFWriteStringAttribute( hDBF, i, nDBFFieldIndex,  (_bstr_t)val );
				break;
			default:
				DBFWriteAttributeDirectly( hDBF, i, nDBFFieldIndex,  (void*)&val );
				break;
			}
		}
	}

	DBFClose( hDBF );

}

void CAttributeTable::SetTableProperty()
{
	if(!TableIsOpen())
		return;

	//选择行的颜色
	COLORREF clrSelBackground = m_ColorData.m_SelColors.m_clrBackground;
	if ( clrSelBackground == (COLORREF) -1 )
		clrSelBackground = globalData.clrHilite;
			
	//表格字体的颜色
	COLORREF clrText = GetTextColor();

	//字体名称
	if( m_hFont == NULL ) 
		m_hFont = GetDefaultFont();
	CFont *pFont = CFont::FromHandle( m_hFont );
	
	LOGFONT logFont;
	pFont->GetLogFont( &logFont );
	CString strFont = logFont.lfFaceName;

	//字体大小
	int nSize = -logFont.lfHeight*72.0 / GetDeviceCaps( this->GetDC()->m_hDC, LOGPIXELSY) + 0.5;
	
	//表格Header高度
	int nHeaderHeight = m_nGridHeaderHeight*100/nSize;

	//表格高度
	int i = GetRowHeight();
	int nTableHeight = GetRowHeight()*100/nSize;

	CDllResource dllRes;
	CDlgAttrTableProperty dlgAttrTable;
	dlgAttrTable.SetSelColor( clrSelBackground );
	dlgAttrTable.SetTableColor( clrText );
	dlgAttrTable.SetFont( strFont );
	dlgAttrTable.SetFontSize( nSize );

	if ( IDOK == dlgAttrTable.DoModal() )
	{
		m_ColorData.m_SelColors.m_clrBackground = dlgAttrTable.GetSelColor();
		m_ColorData.m_clrText = dlgAttrTable.GetTableColor();
		InitColors();
		
		strcpy( logFont.lfFaceName, dlgAttrTable.GetFont() );
		logFont.lfHeight = -MulDiv(dlgAttrTable.GetFontSize(), GetDeviceCaps(this->GetDC()->m_hDC, LOGPIXELSY), 72); ;
		CFont *pNewFont = new CFont;
		pNewFont->CreateFontIndirect( &logFont );
		::DeleteObject( m_hFont );
		m_hFont = (HFONT)(*pNewFont);
		
		AdjustLayout();
	}
}

void CAttributeTable::AddColumnForStatics( int icol, std::vector<LP_CAL_FIELDVALUE>  &vCalFieldsVals )
{
	CString strColumnName = GetColumnName( icol );
	if ( GetColumnLocked( icol ) )
		strColumnName = strColumnName.Left( strlen( strColumnName ) - 1 );

	long nFieldIndex = m_pFeatureClass->FindField( strColumnName );
	Geodatabase::CFieldPtr pField = m_pFeatureClass->GetField( nFieldIndex );
	CString szFieldType = "UNKNOWN";
	if ( pField->GetType() == Geodatabase::FTYPE_SHORT )
		szFieldType = "SHORT";
	else if ( pField->GetType() == Geodatabase::FTYPE_LONG )
		szFieldType = "LONG";
	else if ( pField->GetType() == Geodatabase::FTYPE_FLOAT )
		szFieldType = "FLOAT";
	else if ( pField->GetType() == Geodatabase::FTYPE_DOUBLE )
		szFieldType = "DOUBLE";

	if ( szFieldType == "UNKNOWN")
		return;

	CBCGPGridRange* pSelRange=NULL;

	//加入选中列的数据
	CalFieldValue *pFieldValue = new CalFieldValue();
	pFieldValue->iIndex = icol;
	pFieldValue->szType = szFieldType;
	pFieldValue->szFieldName = strColumnName;

	vCalFieldsVals.push_back( pFieldValue );
}

void CAttributeTable::GetSelectRows( std::vector<long> &vSelRows, ROWTYPE type )
{
	vSelRows.clear();

	CBCGPGridRange* pSelRange=NULL;
	for (POSITION pos = m_lstSel.GetHeadPosition(); pos != NULL;)
	{
		pSelRange = m_lstSel.GetNext(pos);

		for(int i = pSelRange->m_nTop; i <= pSelRange->m_nBottom; i++)
		{
			if( pSelRange->m_nLeft == 0 && pSelRange->m_nRight == GetColumnCount()-1 )
			{
				if ( type == FEAUTE_INDEX )
					vSelRows.push_back( m_sortlist[i] );
				else
					vSelRows.push_back( i );
			}
				
		}	
	}
}

void CAttributeTable::GetAllRows( std::vector<long> &vAllRows, ROWTYPE type )
{
	vAllRows.clear();
	
	if ( type == FEAUTE_INDEX )
	{
		vAllRows.insert( vAllRows.begin(), m_sortlist.begin(), m_sortlist.end() );
	}
	else
	{
		for ( int i = 0; i <m_sortlist.size(); ++i )
		{
			vAllRows.push_back( i );
		}
	}
}

int CAttributeTable::GetRowCount()
{
	return m_sortlist.size();
}

void CAttributeTable::RefreshTable()
{
	//重新加载FeatureClass
	OpenTable( m_pFeatureClass, false );
}

} //namespace Control
