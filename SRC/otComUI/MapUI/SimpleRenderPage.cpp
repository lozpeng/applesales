// SimpleRenderPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimpleRenderPage.h"
#include "FeatureLayer.h"
#include "SimpleRender.h"
#include "../CotSymbolList.h"
// CSimpleRenderPage �Ի���

IMPLEMENT_DYNAMIC(CSimpleRenderPage, CDialog)

CSimpleRenderPage::CSimpleRenderPage(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleRenderPage::IDD, pParent)
{

}

CSimpleRenderPage::~CSimpleRenderPage()
{
}

void CSimpleRenderPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SR_PREVIEW, m_PreviewBtn);
}


BEGIN_MESSAGE_MAP(CSimpleRenderPage, CDialog)
	ON_BN_CLICKED(IDC_SR_SYMBOLSET, &CSimpleRenderPage::OnBnClickedSrSymbolset)
END_MESSAGE_MAP()


// CSimpleRenderPage ��Ϣ�������

long CSimpleRenderPage::GetRenderType()
{
	return Carto::SIMPLERENDER;
}

Carto::IRenderPtr CSimpleRenderPage::GetRender()
{
	Carto::CSimpleRenderPtr pRender(new Carto::CSimpleRender());

	pRender->SetSymbol(m_pSymbol);

	return pRender;
}


void CSimpleRenderPage::OnBnClickedSrSymbolset()
{
	
	otComUI::CotSymbolList symlist;
	m_pSymbol =symlist.SelectSymbol(m_pSymbol);
	
	m_PreviewBtn.SetSymbol(m_pSymbol.get());
}

bool CSimpleRenderPage::CreateDlg(CWnd *pParent)
{
	return Create(IDD,pParent);
}
BOOL CSimpleRenderPage::OnInitDialog()
{
	__super::OnInitDialog();

	if(!m_pLayer)
	{
		return FALSE;
	}
	
    Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSimpleRenderPage::Init()
{
	Carto::CFeatureLayer *pLayer =dynamic_cast<Carto::CFeatureLayer*>(m_pLayer);
	Carto::IRenderPtr pRender =pLayer->GetFeatureRender();
	if(pRender->GetRenderType() ==Carto::SIMPLERENDER)
	{
		m_pSymbol =dynamic_cast<Carto::CSimpleRender*>(pRender.get())->GetSymbol();
	}
	else
	{
		
		if(!m_pSymbol)
		{
			//���û�з��ţ��򴴽�һ��Ĭ�ϵķ���
			m_pSymbol =CreateDefaultSymbol(dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get()));
		}
		
	}
	m_PreviewBtn.SetSymbol(m_pSymbol.get());
}