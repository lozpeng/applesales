// LayerBasepropPage.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "LayerBasepropPage.h"


// CLayerBasepropPage 对话框

IMPLEMENT_DYNAMIC(CLayerBasepropPage, CDialog)

CLayerBasepropPage::CLayerBasepropPage(CWnd* pParent /*=NULL*/)
	: CDialog(CLayerBasepropPage::IDD, pParent)
{

}

CLayerBasepropPage::~CLayerBasepropPage()
{
}

void CLayerBasepropPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLayerBasepropPage, CDialog)
END_MESSAGE_MAP()


// CLayerBasepropPage 消息处理程序
