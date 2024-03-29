// RangeRenderPage.cpp : 实现文件
//

#include "stdafx.h"
#include "ClassifyColorRenderPage.h"
#include "RasterLayer.h"
#include "CotSymbolList.h"
#include "DlgModifyUniClass.h"
#include "ColorDefine.h"
#include "HSLColorRamp.h"
// CRangeRenderPage 对话框

#ifdef DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CClassifyColorPage, CDialog)

CClassifyColorPage::CClassifyColorPage(CWnd* pParent /*=NULL*/)
	: CDialog(CClassifyColorPage::IDD, pParent)
	, m_strHeading(_T(""))
	, m_Breaknum(0)
{
    m_BtnStartcolor.EnableOtherButton(_T("其它颜色"));
	m_BtnEndcolor.EnableOtherButton(_T("其它颜色"));
    
	m_curIndex =-1;
}

CClassifyColorPage::~CClassifyColorPage()
{
}

void CClassifyColorPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_RANGE_FIELD, m_ComboFields);
	//DDX_Text(pDX, IDC_EDIT_RANGE_HEADING, m_strHeading);
	//DDX_Control(pDX, IDC_BTN_RANGE_OVERVIEW, m_BtnOverview);
	DDX_Control(pDX, IDC_COMBO_COLORBAR_R, m_ctlColorRamp);
	DDX_Control(pDX, IDC_RANGE_SYMBOL_LIST_R, m_list);
	DDX_Text(pDX, IDC_EDIT_RANGE_NUM_R, m_Breaknum);
	//DDX_Control(pDX, IDC_RG_START_COLOR, m_BtnStartcolor);
	//DDX_Control(pDX, IDC_RG_END_COLOR, m_BtnEndcolor);
}


BEGIN_MESSAGE_MAP(CClassifyColorPage, CDialog)
	ON_BN_CLICKED(IDC_BTN_AUTO_SETRANGE_R, &CClassifyColorPage::OnBnClickedBtnAutoSetrange)
	//ON_BN_CLICKED(IDC_BTN_RANGE_OVERVIEW, &CRangeRenderPage::OnBnClickedBtnRangeOverview)
	//ON_CBN_SELCHANGE(IDC_COMBO_RANGE_FIELD, &CClassifyColorPage::OnCbnSelchangeComboRangeField)
END_MESSAGE_MAP()


// CRangeRenderPage 消息处理程序



BOOL CClassifyColorPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	Init();

	CSpinButtonCtrl	* pSpinTolerance = NULL;
	pSpinTolerance = (CSpinButtonCtrl *)GetDlgItem(IDC_RANGE_NUM_SPIN_R);
	if (pSpinTolerance)
		pSpinTolerance->SetRange(0, 1000);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//按照等距自动进行分段
void CClassifyColorPage::OnBnClickedBtnAutoSetrange()
{
    UpdateData(TRUE);

	if(m_Breaknum<=0)
	{
		return;
	}

    double dmin=0.0,dmax =0.0;

	//获得字段的最大最小值

	Geodatabase::IRasterDatasetPtr pRaster =m_pLayer->GetDataObject();
	if(pRaster)
	{
		pRaster->GetBandMinMaxValue(1,&dmax,&dmin);
	}

 //   
	m_Classes.clear();
    m_list.DeleteAll();

	Display::HSLColor beginColor =m_ctlColorRamp.get_curStartColor();
	Display::HSLColor endColor =m_ctlColorRamp.get_curEndColor();
 //   

	Display::RGBColor rgbBeginColor,rgbEndColor;

	RangeItem item;

	Display::ISymbolPtr pDefaultSymbol =CreateDefaultSymbol(dynamic_cast<Geodatabase::IFeatureClass*>(m_pLayer->GetDataObject().get()));

	Display::ISymbolPtr pSymbol;
	//如果最大最小值相等，则只分一个段
    if(dmin ==dmax)
	{
        item.max =dmax;
		item.min =dmin;
		pSymbol =pDefaultSymbol->Clone();
		beginColor.toRGBColor(&rgbBeginColor);
		pSymbol->SetColor(RGB(rgbBeginColor.red,rgbBeginColor.green,rgbBeginColor.blue));
		item.pSymbol =pSymbol;

		item.strLabel.Format("%.6f%s%.6f",item.min,"-",item.max);
		
		m_Classes.push_back(item);
	    
	}
	else
	{
		//获取过渡色彩的各个分量
		
		beginColor.toRGBColor(&rgbBeginColor);
		endColor.toRGBColor(&rgbEndColor);

		int begin_r_color = rgbBeginColor.red;
		int begin_g_color = rgbBeginColor.green;
		int begin_b_color = rgbBeginColor.blue;

		int end_r_color =rgbEndColor.red;
		int end_g_color =rgbEndColor.green;
		int end_b_color =rgbEndColor.blue;

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
        
	
		//分段的方法
		/*
		upper = min + i * step
		保留六位有效位
		下一个区间为上一个的上限+0.000001
		*/
		//依次加入区间
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

		//设置第一个和最后一个区间
		m_Classes[0].min =dmin;
		m_Classes[m_Breaknum-1].max =dmax;


	}


	//将各个分段添加到列表中
	for(size_t i=0;i<m_Classes.size();i++)
	{
		
		m_list.AddSymbolItem(m_Classes[i].pSymbol,m_Classes[i].strLabel,m_Classes[i].strLabel);
	}

}

void CClassifyColorPage::OnBnClickedBtnRangeOverview()
{
	if(m_curIndex<0 ||m_curIndex>=m_Classes.size())
	{
		return;
	}
     //改变区间的符号
	Control::CotSymbolList symlist;
		m_Classes[m_curIndex].pSymbol =symlist.SelectSymbol(m_Classes[m_curIndex].pSymbol);
	
	m_BtnOverview.SetSymbol(m_Classes[m_curIndex].pSymbol.get());

	//替换掉列表中的symbol
	m_list.ReplaceSymbol(m_Classes[m_curIndex].pSymbol,m_curIndex);
	
}


void CClassifyColorPage::OnCbnSelchangeComboRangeField()
{
	CString strTemp =m_renderField;
	//更新选择的字段
	int index =m_ComboFields.GetCurSel();

	m_ComboFields.GetLBText(index,m_renderField);

	m_strHeading =m_renderField;

	//更新列表
	if(strTemp!=m_renderField)
	{
		m_list.DeleteAll();
		m_Classes.clear();
	}


	UpdateData(FALSE);
}

long CClassifyColorPage::GetRenderType()
{
	return (long)Carto::RASTER_CLASSIFY_COLORRAMP_RENDER;
}

bool CClassifyColorPage::CreateDlg(CWnd *pParent)
{
	return Create(IDD,pParent);
}

Carto::IRasterRenderPtr CClassifyColorPage::GetRasterRender()
{
	UpdateData(TRUE);
	long classnum =m_Classes.size();
	if(classnum<1)
	{
		return NULL;

	}
	if(classnum>=1)
	{
		Display::HSLColorRampPtr pHslramp=new Display::HSLColorRamp();

		Display::HSLColor beginColor =m_ctlColorRamp.get_curStartColor();
		Display::HSLColor endColor =m_ctlColorRamp.get_curEndColor();

		pHslramp->setStartColor(beginColor);
		pHslramp->setEndColor(endColor);
		pHslramp->setSize(classnum);

		m_pRender->setBreak(classnum);
		m_pRender->setColorRamp(pHslramp);


	}
	
	return m_pRender;
}

void CClassifyColorPage::Init()
{
	Carto::CRasterLayer *pLayer =dynamic_cast<Carto::CRasterLayer*>(m_pLayer);
	Carto::IRasterRenderPtr pRender =pLayer->GetRender();

	if(pRender->GetRenderType() ==Carto::RASTER_CLASSIFY_COLORRAMP_RENDER)
	{
        m_pRender =pRender;

		m_Breaknum = m_pRender->getBreak();
			
		if(m_Breaknum<=0)
		{
			return;
		}

    double dmin=0.0,dmax =0.0;

	//获得字段的最大最小值

	Geodatabase::IRasterDatasetPtr pRaster =m_pLayer->GetDataObject();
	if(pRaster)
	{
		pRaster->GetBandMinMaxValue(1,&dmax,&dmin);
	}

 //   
	m_Classes.clear();

	Display::HSLColorRampPtr pHslramp = m_pRender->getColorRamp();
	Display::HSLColor beginColor =pHslramp->getStartColor();
	Display::HSLColor endColor =pHslramp->getEndColor();


	Display::RGBColor rgbBeginColor,rgbEndColor;

	RangeItem item;

	Display::ISymbolPtr pDefaultSymbol =CreateDefaultSymbol(dynamic_cast<Geodatabase::IFeatureClass*>(m_pLayer->GetDataObject().get()));

	Display::ISymbolPtr pSymbol;
	//如果最大最小值相等，则只分一个段
    if(dmin ==dmax)
	{
        item.max =dmax;
		item.min =dmin;
		pSymbol =pDefaultSymbol->Clone();
		beginColor.toRGBColor(&rgbBeginColor);
		pSymbol->SetColor(RGB(rgbBeginColor.red,rgbBeginColor.green,rgbBeginColor.blue));
		item.pSymbol =pSymbol;

		item.strLabel.Format("%.6f%s%.6f",item.min,"-",item.max);
		
		m_Classes.push_back(item);
	    
	}
	else
	{
		//获取过渡色彩的各个分量
		
		beginColor.toRGBColor(&rgbBeginColor);
		endColor.toRGBColor(&rgbEndColor);

		int begin_r_color = rgbBeginColor.red;
		int begin_g_color = rgbBeginColor.green;
		int begin_b_color = rgbBeginColor.blue;

		int end_r_color =rgbEndColor.red;
		int end_g_color =rgbEndColor.green;
		int end_b_color =rgbEndColor.blue;

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
        
	
		//分段的方法
		/*
		upper = min + i * step
		保留六位有效位
		下一个区间为上一个的上限+0.000001
		*/
		//依次加入区间
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

		//设置第一个和最后一个区间
		m_Classes[0].min =dmin;
		m_Classes[m_Breaknum-1].max =dmax;


	}
		

	}
	else
	{
		//如果是第一次初始化
		if(!m_pRender)
		{
			//新建一个空的范围Render
			m_pRender.reset(new Carto::CRasterClassifyColorRender());
           
		}
	}

	InitList();
}

void CClassifyColorPage::InitList()
{
	m_list.DeleteAllItems();
	//初始化符号列表
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
	    //范围值保留小数点后6位有效数字
        strRange.Format("%.6f%s%.6f",m_Classes[i].min,"-",m_Classes[i].max);

		m_list.AddSymbolItem(m_Classes[i].pSymbol,strRange,m_Classes[i].strLabel);
	}
}

void CClassifyColorPage::ShowSymbol(int index)
{
	
	
	m_BtnOverview.SetSymbol(m_Classes[index].pSymbol.get());

	m_curIndex =index;
	
}

void CClassifyColorPage::ModifySelItem(int index)
{
	//CDlgModifyUniClass dlg;

	//CString strValue;
	//strValue.Format("%.6f",m_Classes[index].max);

 //   dlg.m_bUniqueRender =false;
	//dlg.Init(strValue,m_Classes[index].strLabel,m_Classes[index].pSymbol);

	//if(dlg.DoModal()==IDOK)
	//{
	//	//改变符号表里的值
	//	m_Classes[index].pSymbol =dlg.m_pSymbol;
	//	m_Classes[index].strLabel =dlg.m_strLabel;
 //       
 //       //如果范围改变
	//	if(dlg.m_strValue !=strValue)
	//	{
	//		double dmax =atof(dlg.m_strValue);
	//		m_Classes[index].max =dmax;

	//		//改变下一个区间的下限
	//		if(index<(m_Classes.size()-1))
	//		{
 //               m_Classes[index+1].min =dmax+0.000001;
	//		}
	//	}
	//	
	//	m_BtnOverview.SetSymbol(m_Classes[index].pSymbol.get());

	//	//改变列表里的值
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

