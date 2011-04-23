// UniqueRenderPage.cpp : 实现文件
//

#include "stdafx.h"
#include "UniqueRenderPage.h"
#include "FeatureLayer.h"
#include "ISymbolListCtrl.h"
#include "SimpleQuery.h"
#include "DlgSelectValues.h"
#include "DlgModifyUniClass.h"


#define  DEFAULTVALUE "<其它所有值>"


IMPLEMENT_DYNAMIC(CUniqueRenderPage, CDialog)

CUniqueRenderPage::CUniqueRenderPage(CWnd* pParent /*=NULL*/)
	: CDialog(CUniqueRenderPage::IDD, pParent)
	, m_strHeading(_T(""))
{
	m_bpUp.LoadBitmap(IDB_UP);
	m_bpDown.LoadBitmap(IDB_DOWN);
}

CUniqueRenderPage::~CUniqueRenderPage()
{
}

void CUniqueRenderPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UNIQUE_SYMBOL_LIST, m_list);
	//DDX_Control(pDX, IDC_BTN_UNI_OVERVIEW, m_BtnOverview);
	DDX_Control(pDX, IDC_COMBO_UNIQUE_FIELD, m_ComboFields);
	//DDX_Text(pDX, IDC_EDIT_UNI_HEADING, m_strHeading);
	//DDX_Control(pDX, IDC_BTN_UP, m_BtnUp);
	//DDX_Control(pDX, IDC_BTN_DOWN, m_BtnDown);
}


BEGIN_MESSAGE_MAP(CUniqueRenderPage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIQUE_FIELD, &CUniqueRenderPage::OnCbnSelchangeComboUniqueField)
	ON_BN_CLICKED(IDC_UNI_ADDALL, &CUniqueRenderPage::OnBnClickedUniAddall)
	ON_BN_CLICKED(IDC_UNI_ADD, &CUniqueRenderPage::OnBnClickedUniAdd)
	ON_BN_CLICKED(IDC_UNI_REMOVE, &CUniqueRenderPage::OnBnClickedUniRemove)
	ON_BN_CLICKED(IDC_UNI_REMOVEALL, &CUniqueRenderPage::OnBnClickedUniRemoveall)
	//ON_BN_CLICKED(IDC_BTN_UNI_SYMBOLSET, &CUniqueRenderPage::OnBnClickedBtnUniSymbolset)
	//ON_BN_CLICKED(IDC_BTN_UNI_OVERVIEW, &CUniqueRenderPage::OnBnClickedBtnUniOverview)
	ON_WM_DESTROY()
	//ON_BN_CLICKED(IDC_BTN_UP, &CUniqueRenderPage::OnBnClickedBtnUp)
	//*、、*/ON_BN_CLICKED(IDC_BTN_DOWN, &CUniqueRenderPage::OnBnClickedBtnDown)
END_MESSAGE_MAP()


// CUniqueRenderPage 消息处理程序

BOOL CUniqueRenderPage::OnInitDialog()
{
	__super::OnInitDialog();

	Init();
    
	UpdateData(FALSE);



	/*m_BtnUp.SetBitmap(m_bpUp);
	m_BtnDown.SetBitmap(m_bpDown);

	m_BtnUp.SetTooltip("上移");
    m_BtnDown.SetTooltip("下移");*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


bool CUniqueRenderPage::CreateDlg(CWnd *pParent)
{
	return Create(IDD,pParent);
}

long CUniqueRenderPage::GetRenderType()
{
	return Carto::UNIQUERENDER;
}

Carto::IRenderPtr CUniqueRenderPage::GetRender()
{
	UpdateData(TRUE);
    

	m_pRender->clear();
	//将界面上设置的值填入Render中

	m_pRender->SetUniqueFieldsStr(std::string(m_renderField));
	SCMAP::iterator iter;

	for(size_t i=0;i<m_IndexList.size();i++)
	{
		if(m_IndexList[i]!=DEFAULTVALUE)
		{
			SymbolClass &sc =m_SymbolMap[m_IndexList[i]];
            m_pRender->SetUniqueValue(std::string(m_IndexList[i]),std::string(sc.strLabel),sc.pSymbol);
		}
	}
	
	m_pRender->SetDefaultSymbol(m_pDefaultSymbol);
	m_pRender->SetDefaultLabel(std::string(m_DefaultLabel));
	m_pRender->SetHeading(std::string(m_strHeading));


	return m_pRender;
}

void CUniqueRenderPage::Init()
{
	Carto::CFeatureLayer *pLayer =dynamic_cast<Carto::CFeatureLayer*>(m_pLayer);
	Carto::IRenderPtr pRender =pLayer->GetFeatureRender();
	if(pRender->GetRenderType() ==Carto::UNIQUERENDER)
	{
		//如果目标图层是唯一值渲染，则将它的属性赋给对话框
        m_pRender =pRender;
        
		//列举字段
		LoadFields(&m_ComboFields,dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get()));
		//获得唯一值字段
		m_renderField =m_pRender->GetRendFieldsStr().c_str();

		//获得Heading
		m_strHeading =m_pRender->GetHeading().c_str();

		//获得默认符号，默认标记
		m_pDefaultSymbol =m_pRender->GetDefaultSymbol();
		m_DefaultLabel =m_pRender->GetDefaultLabel().c_str();

		m_SymbolMap.clear();
		m_IndexList.clear();
		m_curValue ="";
		m_BtnOverview.SetSymbol(NULL);

		long index;
		SymbolClass sc;
		CString strValue;
		for(index=0;index<m_pRender->GetCount();index++)
		{
			strValue =m_pRender->GetValue(index).c_str();
			m_IndexList.push_back(strValue);
			sc.index =index;
			sc.pSymbol =m_pRender->GetUniqueValue(std::string(strValue));
			sc.strLabel =m_pRender->GetLabel(std::string(strValue)).c_str();
			m_SymbolMap[strValue] =sc;
		}
		InitList();

	}
	else
	{
		//列举字段
		LoadFields(&m_ComboFields,dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get()));

		//如果是第一次初始化
		if(!m_pRender)
		{
			//新建一个空的唯一值Render
			m_pRender.reset(new Carto::CUniqueRender());
              
			m_ComboFields.SetCurSel(0);

			m_ComboFields.GetLBText(0,m_renderField);
			//TrimField(m_renderField);

			m_strHeading =m_renderField;

            //初始化默认符号
			m_pDefaultSymbol =CreateDefaultSymbol(dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get()));
			m_DefaultLabel ="<其它所有值>";

			//添加默认符号项
			SymbolClass sc;
			sc.index =0;
			sc.pSymbol =m_pDefaultSymbol;
			sc.strLabel =m_DefaultLabel;
			m_SymbolMap["<其它所有值>"] =sc;
			m_IndexList.push_back("<其它所有值>");

           

		}
		else
		{
           
		}

		InitList();
		
	}
	
}

void CUniqueRenderPage::InitList()
{
	//初始化符号列表
	m_list.InitCol();
	m_list.SetImageSize(40,15);
    m_list.SetUniquePage(this);
    
	if(m_SymbolMap.empty())
	{
		return;
	}
	for(size_t i=0;i<m_IndexList.size();i++)
	{
		SymbolClass &sc =m_SymbolMap[m_IndexList[i]];

		m_list.AddSymbolItem(sc.pSymbol,m_IndexList[i],sc.strLabel,sc.strCount);
	}
	

	
}

void CUniqueRenderPage::ShowSymbol(CString &value)
{
	SCMAP::iterator iter =m_SymbolMap.find(value);
	if(iter!=m_SymbolMap.end())
	{
		//如果找到了这个符号
        SymbolClass &sc =iter->second;
		m_BtnOverview.SetSymbol(sc.pSymbol.get());

		m_curValue =value;
	}
}


void CUniqueRenderPage::OnCbnSelchangeComboUniqueField()
{
	CString strTemp =m_renderField;
	//更新选择的字段
	int index =m_ComboFields.GetCurSel();

	m_ComboFields.GetLBText(index,m_renderField);
	//TrimField(m_renderField);

	
    m_strHeading =m_renderField;

	//更新列表
	if(strTemp!=m_renderField)
	{
		m_list.DeleteAll();
		m_SymbolMap.clear();
		m_IndexList.clear();
		m_curValue ="";
		m_BtnOverview.SetSymbol(NULL);
	}
	

	UpdateData(FALSE);

}

//添加所有的类
void CUniqueRenderPage::OnBnClickedUniAddall()
{
	OnBnClickedUniRemoveall();

	if(m_renderField=="")
	{
		return;
	}


	typedef std::map<std::string,long>  Countmaps;
	Countmaps Tempmap;

	//
	if ( m_pDefaultSymbol->GetType() & MARKER_SYMBOL )														
	{
		m_nType = SIMPLE_MARKER_SYMBOL ;
	}
	else if ( m_pDefaultSymbol->GetType() & LINE_SYMBOL )													
	{
		m_nType =SIMPLE_LINE_SYMBOL ;
	}
	else if ( m_pDefaultSymbol->GetType() & FILL_SYMBOL )													
	{
		m_nType =SIMPLE_FILL_SYMBOL;
	}
	else
	{
		return ;
	}

	Carto::CFeatureLayer *pLayer =dynamic_cast<Carto::CFeatureLayer*>(m_pLayer);

	Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());

	if(!pFeatureClass)
	{
		return;
	}


	long index =pFeatureClass->FindField(m_renderField);
	if(index<=0)
	{
		return;
	}
	std::string strVal;
	Geodatabase::CSimpleQuery queryfilter;
	queryfilter.AddField(m_renderField);
	Geodatabase::ICursorPtr pCursor =pFeatureClass->Query(&queryfilter);
	if(!pCursor)
	{
		return;
	}
	Geodatabase::IRowPtr prow;
	while(!pCursor->IsEOF())
	{
		prow =pCursor->NextRow();
		if(!prow)
			continue;

		strVal =prow->GetValue(index).GetasString();

		if (strVal.size()==0)
		{
			continue;
		}
        
		//记录下每一类的数目
		Countmaps::iterator it = Tempmap.find( strVal );
		if( it == Tempmap.end())
		{
			Tempmap[strVal] = 1;
		}
		else
		{
			Tempmap[strVal]+=1;
		}
		

	}

	CString strCount;
	
	SymbolClass sc;
	CString strValue;
	for (Countmaps::iterator  it = Tempmap.begin() ; it != Tempmap.end() ; it++ )
	{
		sc.strLabel = it->first.c_str();
	
		sc.strCount.Format( "%d", it->second ) ;
		sc.pSymbol = AddUniquerSymbol();
		m_SymbolMap[it->first.c_str()] =sc;

		
	}
	//Display::ISymbolArrayPtr pSymbolArray(new Display:: CSymbolArray);
	vector<Display::ISymbolPtr> pSymbolArray;

	//加入默认符号
    pSymbolArray.push_back(m_pDefaultSymbol);

	for ( SCMAP::iterator it = m_SymbolMap.begin() ; it != m_SymbolMap.end() ; it++ )
	{
		pSymbolArray.push_back(it->second.pSymbol);
	}
	//列表根据符号数组产生图片
	m_list.CreateSymbolArrayBitmap( pSymbolArray );
    
	m_IndexList.resize(m_SymbolMap.size()+1);

	sc.strLabel =DEFAULTVALUE;
	sc.index =0;
	sc.pSymbol =m_pDefaultSymbol;
	sc.strCount ="";

	//现在列表中添加默认值
    m_list.InsertItemEX( 0 ,DEFAULTVALUE , sc.strLabel, sc.strCount);
	int nindex = 1; 

	for (SCMAP::iterator it = m_SymbolMap.begin() ; it != m_SymbolMap.end() ; it++)
	{
		
		m_list.InsertItemEX( nindex ,it->first , it->second.strLabel, it->second.strCount);
		it->second.index =nindex;
        m_IndexList[nindex] =it->first;
		nindex++;
	}

	//最后将默认符号加入到数组中
    m_SymbolMap[DEFAULTVALUE] =sc;
	m_IndexList[0] =DEFAULTVALUE;


}

void CUniqueRenderPage::OnBnClickedUniAdd()
{
	 //添加值
	CDlgSelectValues dlg;
	FillValues(dlg.m_allValues);

	if(dlg.DoModal()==IDOK)
	{
		SymbolClass sc;
        long index =m_IndexList.size();
        //将选中的值添加
		for(size_t i=0;i<dlg.m_values.size();i++)
		{
            sc.strLabel =dlg.m_values[i];
			if(sc.strLabel==DEFAULTVALUE)
			{
				sc.pSymbol =m_pDefaultSymbol;
			}
			else
			{
                sc.pSymbol = AddUniquerSymbol();
			}
			
			sc.index =index;
            m_list.AddSymbolItem( sc.pSymbol ,sc.strLabel , sc.strLabel, sc.strCount);

			m_IndexList.push_back(sc.strLabel);
			m_SymbolMap[sc.strLabel] =sc;

			index++;
		}
	}
}

//删除选中的一条记录
void CUniqueRenderPage::OnBnClickedUniRemove()
{
	//只有选中一项才可以用
	if(m_list.GetSelectedCount()!=1)
	{
		return;
	}

	POSITION pos = m_list.GetFirstSelectedItemPosition();

	int nItem = m_list.GetNextSelectedItem(pos);

	m_list.DeleteItem(nItem);

	//删除序号和符号列表中相应的记录
	CString removeValue =m_IndexList[nItem];
	m_IndexList.erase(m_IndexList.begin()+nItem);
	m_SymbolMap.erase(m_SymbolMap.find(removeValue));

	//更新每个类的序号
	for(int i=nItem;i<m_IndexList.size();i++)
	{
		m_SymbolMap[m_IndexList[i]].index =i;
	}

}

void CUniqueRenderPage::OnBnClickedUniRemoveall()
{
	m_list.DeleteAll();
	m_SymbolMap.clear();
	m_IndexList.clear();
	m_curValue ="";
	m_BtnOverview.SetSymbol(NULL);
}

void CUniqueRenderPage::OnBnClickedBtnUniSymbolset()
{
	OnBnClickedBtnUniOverview();
}

void CUniqueRenderPage::OnBnClickedBtnUniOverview()
{

	SCMAP::iterator iter =m_SymbolMap.find(m_curValue);
	if(iter!=m_SymbolMap.end())
	{
		//如果找到了这个符号
		SymbolClass &sc =iter->second;
		
		Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
		if(pCtrl)
		{
			sc.pSymbol =pCtrl->SelectSymbol(sc.pSymbol);
		}
		m_BtnOverview.SetSymbol(sc.pSymbol.get());

		//替换掉列表中的symbol
		m_list.ReplaceSymbol(sc.pSymbol,sc.index);
		if(m_curValue==DEFAULTVALUE)
		{
			m_pDefaultSymbol =sc.pSymbol;
		}
	}
}

void CUniqueRenderPage::OnDestroy()
{
	__super::OnDestroy();

	UpdateData(TRUE);
}


Display::ISymbolPtr CUniqueRenderPage::AddUniquerSymbol()
{
	
	Display::ISymbolPtr pSymbol;

	COLORREF lColor = RGB((((double) rand() / (double) 255) * 255 + 0) , (((double) rand() / (double) 255) * 255 + 0),
		(((double) rand() / (double) 255) * 255 + 0));
	pSymbol= m_pDefaultSymbol->Clone();
	pSymbol->SetColor( lColor );
	return pSymbol;
}

//将选中行上移
void CUniqueRenderPage::OnBnClickedBtnUp()
{
	if(m_list.GetItemCount()<=1)
	{
		return;
	}
	//只有选中一项才可以用
	if(m_list.GetSelectedCount()!=1)
	{
		return;
	}
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	
    int nItem = m_list.GetNextSelectedItem(pos);

	if(nItem==0)
	{
		return;
	}
    
    m_list.ReposItem(nItem,nItem-1);

	CString strValue;
	strValue =m_IndexList[nItem];
	m_IndexList[nItem] =m_IndexList[nItem-1];
	m_IndexList[nItem-1] =strValue;

	m_SymbolMap[m_IndexList[nItem]].index =nItem;
	m_SymbolMap[m_IndexList[nItem-1]].index =nItem-1;
		
	
}

//将选中行下移
void CUniqueRenderPage::OnBnClickedBtnDown()
{
	if(m_list.GetItemCount()<=1)
	{
		return;
	}
	//只有选中一项才可以用
	if(m_list.GetSelectedCount()!=1)
	{
		return;
	}

	POSITION pos = m_list.GetFirstSelectedItemPosition();

	int nItem = m_list.GetNextSelectedItem(pos);

	if(nItem==(m_list.GetItemCount()-1))
	{
		return;
	}
	m_list.ReposItem(nItem,nItem+1);

	CString strValue;
	strValue =m_IndexList[nItem];
	m_IndexList[nItem] =m_IndexList[nItem+1];
	m_IndexList[nItem+1] =strValue;

	m_SymbolMap[m_IndexList[nItem]].index =nItem;
	m_SymbolMap[m_IndexList[nItem+1]].index =nItem+1;
}

void CUniqueRenderPage::FillValues(std::vector<CString> &allValues)
{
	if(m_renderField=="")
	{
		return;
	}

	//
	if ( m_pDefaultSymbol->GetType() & MARKER_SYMBOL )														
	{
		m_nType = SIMPLE_MARKER_SYMBOL ;
	}
	else if ( m_pDefaultSymbol->GetType() & LINE_SYMBOL )													
	{
		m_nType =SIMPLE_LINE_SYMBOL ;
	}
	else if ( m_pDefaultSymbol->GetType() & FILL_SYMBOL )													
	{
		m_nType =SIMPLE_FILL_SYMBOL;
	}
	else
	{
		return ;
	}

	Carto::CFeatureLayer *pLayer =dynamic_cast<Carto::CFeatureLayer*>(m_pLayer);

	Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());

	if(!pFeatureClass)
	{
		return;
	}


	long index =pFeatureClass->FindField(m_renderField);
	if(index<=0)
	{
		return;
	}
	std::string strVal;
	Geodatabase::CSimpleQuery queryfilter;
	queryfilter.AddField(m_renderField);
	Geodatabase::ICursorPtr pCursor =pFeatureClass->Query(&queryfilter);
	if(!pCursor)
	{
		return;
	}
	//先添加默认值
	if(m_SymbolMap.find(DEFAULTVALUE)==m_SymbolMap.end())
	{
		
		allValues.push_back(DEFAULTVALUE);
	}

	Geodatabase::IRowPtr prow;
	while(!pCursor->IsEOF())
	{
		prow =pCursor->NextRow();
		if(!prow)
			continue;

		strVal =prow->GetValue(index).GetasString();

		if (strVal.size()==0)
		{
			continue;
		}

		//看这个值是否已经添加
        if(m_SymbolMap.find(strVal.c_str())==m_SymbolMap.end())
		{
			
			allValues.push_back(strVal.c_str());
		}

	}

}

void CUniqueRenderPage::ModifySelItem(int index)
{
	CDlgModifyUniClass dlg;

	CString strValue =m_IndexList[index];
	
	SymbolClass &sc =m_SymbolMap[strValue];

	dlg.Init(strValue,sc.strLabel,sc.pSymbol);

	if(dlg.DoModal()==IDOK)
	{
		//改变符号表里的值
        sc.pSymbol =dlg.m_pSymbol;
		sc.strLabel =dlg.m_strLabel;


		//设置默认符号的值和标注
		if(strValue==DEFAULTVALUE)
		{
			m_pDefaultSymbol =sc.pSymbol;
			m_DefaultLabel =sc.strLabel;
		}
		m_BtnOverview.SetSymbol(sc.pSymbol.get());

		//改变列表里的值
		m_list.ReplaceSymbol(sc.pSymbol,index);

		m_list.SetItemText(index,2,sc.strLabel);

	}




}