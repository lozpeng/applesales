// DashArrayDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DashArrayDlg.h"
#include "SymbolPropList.h"
// CDashArrayDlg 对话框

IMPLEMENT_DYNAMIC(CDashArrayDlg, CBCGPDialog)

CDashArrayDlg::CDashArrayDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDashArrayDlg::IDD, pParent)
{
	
	m_iIndex=0;
	m_pDashArray = NULL;
	m_pDashArrayCopy = NULL;
}

CDashArrayDlg::~CDashArrayDlg()
{
//	delete m_pDashArray;
	delete m_pDashArrayCopy;
	m_pDashArray = NULL;
	m_pDashArrayCopy = NULL;

}

void CDashArrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROPLISTDASHARRAY, m_wndPropListLocation);
	DDX_Text( pDX , IDC_STATICUNIT , m_staticUnit);
}


BEGIN_MESSAGE_MAP(CDashArrayDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BUTTONADD, &CDashArrayDlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTONRMV, &CDashArrayDlg::OnBnClickedButtonrmv)
	ON_BN_CLICKED(IDOK, &CDashArrayDlg::OnBnClickedOk)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDCANCEL, &CDashArrayDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDashArrayDlg 消息处理程序

BOOL CDashArrayDlg::OnInitDialog()
{
		CBCGPDialog::OnInitDialog();

		// TODO:  在此添加额外的初始化
		CRect dlgRect;
		this->GetClientRect(&dlgRect);

		CRect rectPropList;
		m_wndPropListLocation.GetClientRect (&rectPropList);
		m_wndPropListLocation.MapWindowPoints (this, &rectPropList);

		m_wndPropList.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, this , (UINT)-1 );

		m_wndPropList.EnableHeaderCtrl ( TRUE , "属性"  ,  " 值 " );
		m_wndPropList.EnableDesciptionArea ();
		m_wndPropList.SetVSDotNetLook (TRUE);

		m_wndPropList.SetAlphabeticMode (FALSE);
		m_wndPropList.SetShowDragContext (TRUE);

		m_wndPropList.SetBoolLabels("是","否");


	//装入数据
	InitList();
	
	return TRUE;
}

void CDashArrayDlg::SetDashArray(Display::CDashArray *dashArray)
{
	if ( dashArray != NULL )
	{
		m_pDashArray = dashArray;
		if (m_pDashArrayCopy != NULL)
		{
			delete m_pDashArrayCopy;
		}

		m_pDashArrayCopy = new Display::CDashArray;
		*m_pDashArrayCopy = *dashArray;

		SYSTEM::SYS_UNIT_TYPE unit = dashArray->GetUnit();
		if (unit == SYSTEM::SYS_UNIT_PIXEL)
		{
			m_staticUnit = "单位：像素";
		}
		else if (unit == SYSTEM::SYS_UNIT_MILLIMETER)
		{
			m_staticUnit = "单位：毫米";
		}
		else if (unit == SYSTEM::SYS_UNIT_CENTIMETER)
		{
			m_staticUnit = "单位：厘米";
		}
		else if (unit == SYSTEM::SYS_UNIT_DECIMETER)
		{
			m_staticUnit = "单位：分米";
		}
		else if (unit == SYSTEM::SYS_UNIT_POINT)
		{
			m_staticUnit = "单位：磅";
		}
	}
}

void CDashArrayDlg::SetSymbolType(SYMBOL_TYPE type)
{
	m_enumSymbolType = type;
}

void CDashArrayDlg::InitList()
{
	m_wndPropList.RemoveAll();

	if ( !(m_enumSymbolType & LINE_SYMBOL) )
	{
		return;
	}

	if ( m_pDashArray == NULL )
	{
		return;
	}

	CBCGPProp *propGroup = new CBCGPProp ("设置线的破折号数组样式");
	for ( unsigned long i = 1 ; i <= m_pDashArray->GetDashGroupCount() ; ++i )
	{
		CBCGPPropEx *tempnode = NULL;

		if(m_enumSymbolType == ADV_LINE_SYMBOL)
		{
			//奇数行
			if(i % 2)
				tempnode=new CBCGPPropEx ("短线长度", (float)m_pDashArray->GetDash(i-1),"请在1和200之间选择\n仅在高级线样式为用户自定义线时可用",i);
			else
				tempnode=new CBCGPPropEx ("空隙长度", (float)m_pDashArray->GetDash(i-1),"请在1和200之间选择\n仅在高级线样式为用户自定义线时可用",i);
		} 
		else
		{
			tempnode=new CBCGPPropEx ("点间距", (float)m_pDashArray->GetDash(i-1),"请在1和200之间选择",i);
		}

		tempnode->EnableSpinControl (TRUE, 1 , 200);
		m_iIndex = i;
		propGroup->AddSubItem (tempnode);
	}
	m_wndPropList.AddProperty(propGroup);
}


void CDashArrayDlg::OnBnClickedButtonadd()
{	
	if ( m_pDashArray == NULL )
	{
		return;
	}
	Update();
	m_pDashArray->AddDash(10);
	m_pDashArray->SetDashGroupCount(m_pDashArray->GetDashGroupCount() + 1);
	InitList();
}

void CDashArrayDlg::OnBnClickedButtonrmv()
{
	if ( m_pDashArray == NULL )
	{
		return;
	}
	Update();
	if( m_iIndex == 1 )
	{
		::MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd , "数组个数最少为1！" , "警告" ,MB_OK);
		return;
	}

	m_pDashArray->RemoveDash( m_iIndex - 1 );
	m_pDashArray->SetDashGroupCount(m_pDashArray->GetDashGroupCount() - 1);
	InitList();
}

void CDashArrayDlg::Update()
{
	if ( m_pDashArray == NULL )
	{
		return;
	}

	for ( unsigned long i = 0 ; i < m_pDashArray->GetDashGroupCount() ; ++i )
	{
		_variant_t data = m_wndPropList.GetProperty(0)->GetSubItem(i)->GetValue();
		m_pDashArray->SetDash(data , i);
	}

}

void CDashArrayDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	Update();
	CDashArrayDlg::OnOK();
}

//void CDashArrayDlg::SetPoint(CPoint point)
//{	
	/*TO_BEGIN
		m_cPoint=point;
	TO_END_NORET*/
//}
void CDashArrayDlg::OnMouseMove(UINT nFlags, CPoint point)
{	
	CBCGPDialog::OnMouseMove(nFlags, point);

	if(m_wndPropList.m_setFocus)
	{
		this->SetFocus();	
		m_wndPropList.m_setFocus = false;
	}
}


void CDashArrayDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	*m_pDashArray = *m_pDashArrayCopy;
	CDashArrayDlg::OnCancel();
}
