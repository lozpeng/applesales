// UniqueRenderPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UniqueRenderPage.h"
#include "FeatureLayer.h"
#include "ISymbolListCtrl.h"
#include "SimpleQuery.h"
#include "DlgSelectValues.h"
#include "DlgModifyUniClass.h"


#define  DEFAULTVALUE "<��������ֵ>"


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
	//*����*/ON_BN_CLICKED(IDC_BTN_DOWN, &CUniqueRenderPage::OnBnClickedBtnDown)
END_MESSAGE_MAP()


// CUniqueRenderPage ��Ϣ�������

BOOL CUniqueRenderPage::OnInitDialog()
{
	__super::OnInitDialog();

	Init();
    
	UpdateData(FALSE);



	/*m_BtnUp.SetBitmap(m_bpUp);
	m_BtnDown.SetBitmap(m_bpDown);

	m_BtnUp.SetTooltip("����");
    m_BtnDown.SetTooltip("����");*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	//�����������õ�ֵ����Render��

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
		//���Ŀ��ͼ����Ψһֵ��Ⱦ�����������Ը����Ի���
        m_pRender =pRender;
        
		//�о��ֶ�
		LoadFields(&m_ComboFields,dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get()));
		//���Ψһֵ�ֶ�
		m_renderField =m_pRender->GetRendFieldsStr().c_str();

		//���Heading
		m_strHeading =m_pRender->GetHeading().c_str();

		//���Ĭ�Ϸ��ţ�Ĭ�ϱ��
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
		//�о��ֶ�
		LoadFields(&m_ComboFields,dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get()));

		//����ǵ�һ�γ�ʼ��
		if(!m_pRender)
		{
			//�½�һ���յ�ΨһֵRender
			m_pRender.reset(new Carto::CUniqueRender());
              
			m_ComboFields.SetCurSel(0);

			m_ComboFields.GetLBText(0,m_renderField);
			//TrimField(m_renderField);

			m_strHeading =m_renderField;

            //��ʼ��Ĭ�Ϸ���
			m_pDefaultSymbol =CreateDefaultSymbol(dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get()));
			m_DefaultLabel ="<��������ֵ>";

			//���Ĭ�Ϸ�����
			SymbolClass sc;
			sc.index =0;
			sc.pSymbol =m_pDefaultSymbol;
			sc.strLabel =m_DefaultLabel;
			m_SymbolMap["<��������ֵ>"] =sc;
			m_IndexList.push_back("<��������ֵ>");

           

		}
		else
		{
           
		}

		InitList();
		
	}
	
}

void CUniqueRenderPage::InitList()
{
	//��ʼ�������б�
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
		//����ҵ����������
        SymbolClass &sc =iter->second;
		m_BtnOverview.SetSymbol(sc.pSymbol.get());

		m_curValue =value;
	}
}


void CUniqueRenderPage::OnCbnSelchangeComboUniqueField()
{
	CString strTemp =m_renderField;
	//����ѡ����ֶ�
	int index =m_ComboFields.GetCurSel();

	m_ComboFields.GetLBText(index,m_renderField);
	//TrimField(m_renderField);

	
    m_strHeading =m_renderField;

	//�����б�
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

//������е���
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
        
		//��¼��ÿһ�����Ŀ
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

	//����Ĭ�Ϸ���
    pSymbolArray.push_back(m_pDefaultSymbol);

	for ( SCMAP::iterator it = m_SymbolMap.begin() ; it != m_SymbolMap.end() ; it++ )
	{
		pSymbolArray.push_back(it->second.pSymbol);
	}
	//�б���ݷ����������ͼƬ
	m_list.CreateSymbolArrayBitmap( pSymbolArray );
    
	m_IndexList.resize(m_SymbolMap.size()+1);

	sc.strLabel =DEFAULTVALUE;
	sc.index =0;
	sc.pSymbol =m_pDefaultSymbol;
	sc.strCount ="";

	//�����б������Ĭ��ֵ
    m_list.InsertItemEX( 0 ,DEFAULTVALUE , sc.strLabel, sc.strCount);
	int nindex = 1; 

	for (SCMAP::iterator it = m_SymbolMap.begin() ; it != m_SymbolMap.end() ; it++)
	{
		
		m_list.InsertItemEX( nindex ,it->first , it->second.strLabel, it->second.strCount);
		it->second.index =nindex;
        m_IndexList[nindex] =it->first;
		nindex++;
	}

	//���Ĭ�Ϸ��ż��뵽������
    m_SymbolMap[DEFAULTVALUE] =sc;
	m_IndexList[0] =DEFAULTVALUE;


}

void CUniqueRenderPage::OnBnClickedUniAdd()
{
	 //���ֵ
	CDlgSelectValues dlg;
	FillValues(dlg.m_allValues);

	if(dlg.DoModal()==IDOK)
	{
		SymbolClass sc;
        long index =m_IndexList.size();
        //��ѡ�е�ֵ���
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

//ɾ��ѡ�е�һ����¼
void CUniqueRenderPage::OnBnClickedUniRemove()
{
	//ֻ��ѡ��һ��ſ�����
	if(m_list.GetSelectedCount()!=1)
	{
		return;
	}

	POSITION pos = m_list.GetFirstSelectedItemPosition();

	int nItem = m_list.GetNextSelectedItem(pos);

	m_list.DeleteItem(nItem);

	//ɾ����źͷ����б�����Ӧ�ļ�¼
	CString removeValue =m_IndexList[nItem];
	m_IndexList.erase(m_IndexList.begin()+nItem);
	m_SymbolMap.erase(m_SymbolMap.find(removeValue));

	//����ÿ��������
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
		//����ҵ����������
		SymbolClass &sc =iter->second;
		
		Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
		if(pCtrl)
		{
			sc.pSymbol =pCtrl->SelectSymbol(sc.pSymbol);
		}
		m_BtnOverview.SetSymbol(sc.pSymbol.get());

		//�滻���б��е�symbol
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

//��ѡ��������
void CUniqueRenderPage::OnBnClickedBtnUp()
{
	if(m_list.GetItemCount()<=1)
	{
		return;
	}
	//ֻ��ѡ��һ��ſ�����
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

//��ѡ��������
void CUniqueRenderPage::OnBnClickedBtnDown()
{
	if(m_list.GetItemCount()<=1)
	{
		return;
	}
	//ֻ��ѡ��һ��ſ�����
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
	//�����Ĭ��ֵ
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

		//�����ֵ�Ƿ��Ѿ����
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
		//�ı���ű����ֵ
        sc.pSymbol =dlg.m_pSymbol;
		sc.strLabel =dlg.m_strLabel;


		//����Ĭ�Ϸ��ŵ�ֵ�ͱ�ע
		if(strValue==DEFAULTVALUE)
		{
			m_pDefaultSymbol =sc.pSymbol;
			m_DefaultLabel =sc.strLabel;
		}
		m_BtnOverview.SetSymbol(sc.pSymbol.get());

		//�ı��б����ֵ
		m_list.ReplaceSymbol(sc.pSymbol,index);

		m_list.SetItemText(index,2,sc.strLabel);

	}




}