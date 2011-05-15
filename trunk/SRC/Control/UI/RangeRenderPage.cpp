// RangeRenderPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RangeRenderPage.h"
#include "FeatureLayer.h"
#include "CotSymbolList.h"
#include "DlgModifyUniClass.h"
// CRangeRenderPage �Ի���

#ifdef DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CRangeRenderPage, CDialog)

CRangeRenderPage::CRangeRenderPage(CWnd* pParent /*=NULL*/)
	: CDialog(CRangeRenderPage::IDD, pParent)
	, m_strHeading(_T(""))
	, m_Breaknum(0)
{
    m_BtnStartcolor.EnableOtherButton(_T("������ɫ"));
	m_BtnEndcolor.EnableOtherButton(_T("������ɫ"));
    
	m_curIndex =-1;
}

CRangeRenderPage::~CRangeRenderPage()
{
}

void CRangeRenderPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RANGE_FIELD, m_ComboFields);
	//DDX_Text(pDX, IDC_EDIT_RANGE_HEADING, m_strHeading);
	//DDX_Control(pDX, IDC_BTN_RANGE_OVERVIEW, m_BtnOverview);
	DDX_Control(pDX, IDC_COMBO_COLORBAR, m_ctlColorRamp);
	DDX_Control(pDX, IDC_RANGE_SYMBOL_LIST, m_list);
	DDX_Text(pDX, IDC_EDIT_RANGE_NUM, m_Breaknum);
	DDX_Control(pDX, IDC_RG_START_COLOR, m_BtnStartcolor);
	DDX_Control(pDX, IDC_RG_END_COLOR, m_BtnEndcolor);
}


BEGIN_MESSAGE_MAP(CRangeRenderPage, CDialog)
	ON_BN_CLICKED(IDC_BTN_AUTO_SETRANGE, &CRangeRenderPage::OnBnClickedBtnAutoSetrange)
	//ON_BN_CLICKED(IDC_BTN_RANGE_OVERVIEW, &CRangeRenderPage::OnBnClickedBtnRangeOverview)
	ON_CBN_SELCHANGE(IDC_COMBO_RANGE_FIELD, &CRangeRenderPage::OnCbnSelchangeComboRangeField)
END_MESSAGE_MAP()


// CRangeRenderPage ��Ϣ�������



BOOL CRangeRenderPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	Init();

	CSpinButtonCtrl	* pSpinTolerance = NULL;
	pSpinTolerance = (CSpinButtonCtrl *)GetDlgItem(IDC_RANGE_NUM_SPIN);
	if (pSpinTolerance)
		pSpinTolerance->SetRange(0, 1000);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//���յȾ��Զ����зֶ�
void CRangeRenderPage::OnBnClickedBtnAutoSetrange()
{
    UpdateData(TRUE);

	if(m_Breaknum<=0 || m_renderField.IsEmpty())
	{
		return;
	}

    double dmin=0.0,dmax =0.0;

	//����ֶε������Сֵ
	GetMinMaxValue(dynamic_cast<Geodatabase::IFeatureClass*>(m_pLayer->GetDataObject().get()),
		            m_renderField,&dmax,&dmin);

    
	m_Classes.clear();
    m_list.DeleteAll();

	COLORREF beginColor =m_ctlColorRamp.get_curStartColor();
	COLORREF endColor =m_ctlColorRamp.get_curEndColor();
    

	RangeItem item;

	Display::ISymbolPtr pDefaultSymbol =CreateDefaultSymbol(dynamic_cast<Geodatabase::IFeatureClass*>(m_pLayer->GetDataObject().get()));

	Display::ISymbolPtr pSymbol;
	//��������Сֵ��ȣ���ֻ��һ����
    if(dmin ==dmax)
	{
        item.max =dmax;
		item.min =dmin;
		pSymbol =pDefaultSymbol->Clone();
		pSymbol->SetColor(beginColor);
		item.pSymbol =pSymbol;

		item.strLabel.Format("%.6f%s%.6f",item.min,"-",item.max);
		
		m_Classes.push_back(item);
	    
	}
	else
	{
		//��ȡ����ɫ�ʵĸ�������
		int begin_r_color = (int)GetRValue(beginColor);
		int begin_g_color = (int)GetGValue(beginColor);
		int begin_b_color = (int)GetBValue(beginColor);

		int end_r_color =(int) GetRValue(endColor);
		int end_g_color =(int) GetGValue(endColor);
		int end_b_color =(int) GetBValue(endColor);

		double dr,dg,db;
        
		BYTE markr,markg,markb;

		if(m_Breaknum == 1)	
		{
			dr = end_r_color - begin_r_color;
			dg = end_g_color - begin_g_color;
			db = end_b_color - begin_b_color;
		}	  
		else
		{
			dr = (end_r_color - begin_r_color) / (double)(m_Breaknum - 1);
			dg = (end_g_color - begin_g_color) / (double)(m_Breaknum - 1);
			db = (end_b_color - begin_b_color) / (double)(m_Breaknum - 1);
		}
        
		double step =(dmax-dmin)/m_Breaknum;
        
	
		//�ֶεķ���
		/*
		upper = min + i * step
		������λ��Чλ
		��һ������Ϊ��һ��������+0.000001
		*/
		//���μ�������
		for(int i=0;i<m_Breaknum;i++)
		{
			markr =begin_r_color+i*dr;
			markg =begin_g_color+i*dg;
			markb =begin_b_color +i*db;

			item.min =dmin+step*i+0.000001;
			item.max =dmin+step*(i+1);
			pSymbol =pDefaultSymbol->Clone();
			pSymbol->SetColor(RGB(markr,markg,markb));
			item.pSymbol =pSymbol;
			item.strLabel.Format("%.6f%s%.6f",item.min,"-",item.max);
			m_Classes.push_back(item);
		}

		//���õ�һ�������һ������
		m_Classes[0].min =dmin;
		m_Classes[m_Breaknum-1].max =dmax;


	}


	//�������ֶ���ӵ��б���
	for(size_t i=0;i<m_Classes.size();i++)
	{
		
		m_list.AddSymbolItem(m_Classes[i].pSymbol,m_Classes[i].strLabel,m_Classes[i].strLabel);
	}

}

void CRangeRenderPage::OnBnClickedBtnRangeOverview()
{
	if(m_curIndex<0 ||m_curIndex>=m_Classes.size())
	{
		return;
	}
     //�ı�����ķ���
	Control::CotSymbolList symlist;
		m_Classes[m_curIndex].pSymbol =symlist.SelectSymbol(m_Classes[m_curIndex].pSymbol);
	
	m_BtnOverview.SetSymbol(m_Classes[m_curIndex].pSymbol.get());

	//�滻���б��е�symbol
	m_list.ReplaceSymbol(m_Classes[m_curIndex].pSymbol,m_curIndex);
	
}


void CRangeRenderPage::OnCbnSelchangeComboRangeField()
{
	CString strTemp =m_renderField;
	//����ѡ����ֶ�
	int index =m_ComboFields.GetCurSel();

	m_ComboFields.GetLBText(index,m_renderField);

	m_strHeading =m_renderField;

	//�����б�
	if(strTemp!=m_renderField)
	{
		m_list.DeleteAll();
		m_Classes.clear();
	}


	UpdateData(FALSE);
}

long CRangeRenderPage::GetRenderType()
{
	return (long)Carto::RANGERENDER;
}

bool CRangeRenderPage::CreateDlg(CWnd *pParent)
{
	return Create(IDD,pParent);
}

Carto::IRenderPtr CRangeRenderPage::GetRender()
{
	UpdateData(TRUE);
	long classnum =m_Classes.size();
	if(classnum>=1)
	{
		m_pRender->SetClassField(std::string(m_renderField));

		m_pRender->SetHeading(std::string(m_strHeading));
		m_pRender->clear();
		m_pRender->SetClassCount(classnum);

		m_pRender->SetminBreakValue(m_Classes[0].min);
		for(long i=0;i<m_Classes.size();i++)
		{
			m_pRender->SetBreakValue(i,m_Classes[i].max);
			m_pRender->SetSymbol(i,m_Classes[i].pSymbol);
			m_pRender->SetLabel(i,std::string(m_Classes[i].strLabel));

		}

	}
	
	return m_pRender;
}

void CRangeRenderPage::Init()
{
	Carto::CFeatureLayer *pLayer =dynamic_cast<Carto::CFeatureLayer*>(m_pLayer);
	Carto::IRenderPtr pRender =pLayer->GetFeatureRender();

	//�����ֶ���Ϣ
	LoadNumericFields(&m_ComboFields,dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get()));
    
	//��ʼ����ɫ��
	COLORREF begin = RGB((((double) rand() / (double) 255) * 255 + 0) , (((double) rand() / (double) 255) * 255 + 0),
		(((double) rand() / (double) 255) * 255 + 0));

	m_BtnStartcolor.SetColor(begin);
	
	COLORREF end = RGB((((double) rand() / (double) 255) * 255 + 0) , (((double) rand() / (double) 255) * 255 + 0),
		(((double) rand() / (double) 255) * 255 + 0));

	m_BtnEndcolor.SetColor(end);


	if(pRender->GetRenderType() ==Carto::RANGERENDER)
	{
        m_pRender =pRender;
        //�õ�������ֶ�
        m_renderField =m_pRender->GetRendFieldsStr().c_str();
        //�õ�Heading
        m_strHeading =m_pRender->GetHeading().c_str();
		
		for (int i=0; i<m_ComboFields.GetCount(); ++i)
		{
			CString str;
			m_ComboFields.GetLBText(i, str);
			if (str == m_renderField)
			{
				m_ComboFields.SetCurSel(i);
				m_ComboFields.GetLBText(i, m_renderField);
				break;
			}
		}
		RangeItem item;
        //���ÿ���������Ϣ
		for(long i=0;i<m_pRender->GetCount();i++)
		{
            if(i==0)
			{
				item.min =m_pRender->GetminBreakValue();
			}
			else
			{
				item.min =m_pRender->GetBreakValue(i-1);
			}
			item.max =m_pRender->GetBreakValue(i);

            item.pSymbol =m_pRender->GetSymbol(i);

			item.strLabel =m_pRender->GetLabel(i).c_str();
		    
			m_Classes.push_back(item);

		}
		m_Breaknum = (int)m_Classes.size();
	}
	else
	{
		//����ǵ�һ�γ�ʼ��
		if(!m_pRender)
		{
			//�½�һ���յķ�ΧRender
			m_pRender.reset(new Carto::CRangeRender());
            
            m_ComboFields.SetCurSel(0);
			m_ComboFields.GetLBText(0, m_renderField);
			m_strHeading = m_renderField;

		}
	}

	InitList();
}

void CRangeRenderPage::InitList()
{
	m_list.DeleteAllItems();
	//��ʼ�������б�
	m_list.InitCol();
	m_list.SetImageSize(40,15);
	m_list.SetRangePage(this);

	if(m_Classes.empty())
	{
		return;
	}
	
	CString strRange;
	
	for(size_t i=0;i<m_Classes.size();i++)
	{
	    //��Χֵ����С�����6λ��Ч����
        strRange.Format("%.6f%s%.6f",m_Classes[i].min,"-",m_Classes[i].max);

		m_list.AddSymbolItem(m_Classes[i].pSymbol,strRange,m_Classes[i].strLabel);
	}
}

void CRangeRenderPage::ShowSymbol(int index)
{
	
	
	m_BtnOverview.SetSymbol(m_Classes[index].pSymbol.get());

	m_curIndex =index;
	
}

void CRangeRenderPage::ModifySelItem(int index)
{
	//CDlgModifyUniClass dlg;

	//CString strValue;
	//strValue.Format("%.6f",m_Classes[index].max);

 //   dlg.m_bUniqueRender =false;
	//dlg.Init(strValue,m_Classes[index].strLabel,m_Classes[index].pSymbol);

	//if(dlg.DoModal()==IDOK)
	//{
	//	//�ı���ű����ֵ
	//	m_Classes[index].pSymbol =dlg.m_pSymbol;
	//	m_Classes[index].strLabel =dlg.m_strLabel;
 //       
 //       //�����Χ�ı�
	//	if(dlg.m_strValue !=strValue)
	//	{
	//		double dmax =atof(dlg.m_strValue);
	//		m_Classes[index].max =dmax;

	//		//�ı���һ�����������
	//		if(index<(m_Classes.size()-1))
	//		{
 //               m_Classes[index+1].min =dmax+0.000001;
	//		}
	//	}
	//	
	//	m_BtnOverview.SetSymbol(m_Classes[index].pSymbol.get());

	//	//�ı��б����ֵ
	//	m_list.ReplaceSymbol(m_Classes[index].pSymbol,index);

	//	CString strRange;
	//	strRange.Format("%.6f%s%.6f",m_Classes[index].min,"-",m_Classes[index].max);
	//	m_list.SetItemText(index,1,strRange);
	//	m_list.SetItemText(index,2,m_Classes[index].strLabel);

	//	if(index<(m_Classes.size()-1))
	//	{
	//		strRange.Format("%.6f%s%.6f",m_Classes[index+1].min,"-",m_Classes[index+1].max);
	//		m_list.SetItemText(index+1,1,strRange);
	//	}

	//}

}
