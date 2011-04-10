// DlgElementSizePosition.cpp : 实现文件
//

#include "stdafx.h"
#include "ElementSizePositionPage.h"
#include <boost/lexical_cast.hpp>


// CElementSizePositionPage 对话框

IMPLEMENT_DYNCREATE(CElementSizePositionPage, CPropertyPage)

CElementSizePositionPage::CElementSizePositionPage()
	: CPropertyPage(CElementSizePositionPage::IDD)
{
	m_psp.dwFlags &= ~PSP_HASHELP;
	m_pElement = NULL;
	m_bModified = FALSE;
}

CElementSizePositionPage::~CElementSizePositionPage()
{
}

void CElementSizePositionPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POS_X, m_EditPosX);
	DDX_Text(pDX, IDC_EDIT_POS_Y, m_EditPosY);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_EditWidth);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_EditHeight);
	DDX_Control(pDX, IDC_EDIT_NAME, m_EditName);
	DDX_Radio(pDX, IDC_RADIO_LEFT_TOP, m_radioAnchor);
	DDX_Check(pDX, IDC_CHK_WH_RATIO, m_bChkWHRatioMode);
	
}

BEGIN_MESSAGE_MAP(CElementSizePositionPage, CPropertyPage)

	ON_EN_CHANGE(IDC_EDIT_POS_X, &CElementSizePositionPage::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT_POS_Y, &CElementSizePositionPage::OnEnChangeEditPosY)
	ON_BN_CLICKED(IDC_RADIO_LEFT_TOP, &CElementSizePositionPage::OnBnClickedRadioLeftTop)
	ON_BN_CLICKED(IDC_RADIO_CENTER_TOP, &CElementSizePositionPage::OnBnClickedRadioCenterTop)
	ON_BN_CLICKED(IDC_RADIO_RIGHT_TOP, &CElementSizePositionPage::OnBnClickedRadioRightTop)
	ON_BN_CLICKED(IDC_RADIO_LEFT_CENTER, &CElementSizePositionPage::OnBnClickedRadioLeftCenter)
	ON_BN_CLICKED(IDC_RADIO_CENTER_CENTER, &CElementSizePositionPage::OnBnClickedRadioCenterCenter)
	ON_BN_CLICKED(IDC_RADIO_RIGHT_CENTER, &CElementSizePositionPage::OnBnClickedRadioRightCenter)
	ON_BN_CLICKED(IDC_RADIO_LEFT_BOTTOM, &CElementSizePositionPage::OnBnClickedRadioLeftBottom)
	ON_BN_CLICKED(IDC_RADIO_CENTER_BOTTOM, &CElementSizePositionPage::OnBnClickedRadioCenterBottom)
	ON_BN_CLICKED(IDC_RADIO_RIGHT_BOTTOM, &CElementSizePositionPage::OnBnClickedRadioRightBottom)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, &CElementSizePositionPage::OnEnChangeEditWidth)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, &CElementSizePositionPage::OnEnChangeEditHeight)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CElementSizePositionPage::OnEnChangeEditName)
	ON_BN_CLICKED(IDC_CHK_WH_RATIO, &CElementSizePositionPage::OnBnClickedChkWhRatio)
	ON_EN_KILLFOCUS(IDC_EDIT_WIDTH, &CElementSizePositionPage::OnEnKillfocusEditWidth)
	ON_EN_KILLFOCUS(IDC_EDIT_HEIGHT, &CElementSizePositionPage::OnEnKillfocusEditHeight)
END_MESSAGE_MAP()

void CElementSizePositionPage::SetLayoutUnit(SYSTEM::SYS_UNIT_TYPE unit)
{
	m_unitText = SYSTEM::UnitConverter::GetBriefUnitLabel(unit);
}

void CElementSizePositionPage::SetElement(Element::IElementPtr pElement)
{
	m_pElement = pElement;

	if(this->m_hWnd)
		SetCtrls();
}

BOOL CElementSizePositionPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	SetCtrls();

	SetModified(FALSE);

	return TRUE;
}

BOOL CElementSizePositionPage::SetCtrls()
{
	if (m_pElement == NULL)
	{
		return FALSE;
	}

	GetDlgItem(IDC_STATIC_UNIT)->SetWindowText(m_unitText.c_str());
	GetDlgItem(IDC_STATIC_UNIT2)->SetWindowText(m_unitText.c_str());
	GetDlgItem(IDC_STATIC_UNIT3)->SetWindowText(m_unitText.c_str());
	GetDlgItem(IDC_STATIC_UNIT4)->SetWindowText(m_unitText.c_str());

	std::string strWnd;
	char chr[100];
	memset(chr,0 , 100*sizeof(char));
	GEOMETRY::geom::Envelope env =  m_pElement->GetEnvelope();


	//SetAnchor
	m_radioAnchor = (int)m_pElement->GetAnchorPos();

	//Set Pos
	GEOMETRY::geom::Coordinate coordAnchor = GetAnchorPos(env);
	m_EditPosX = coordAnchor.x;
	m_EditPosY = coordAnchor.y;

	//Set Size
	m_EditWidth = env.getWidth();
	m_EditHeight = env.getHeight();

	if(abs(m_EditHeight)>0.000001)
		m_WHRatio = m_EditWidth/m_EditHeight;
	else
		m_WHRatio = 1;

	//Set WH Ratio
	if(m_pElement->CanSetWHRMode())
	{
		if(m_pElement->GetWHRatioMode() == Element::EWHR_FIX_RATIO)
			m_bChkWHRatioMode  = TRUE;
		else if(m_pElement->GetWHRatioMode() == Element::EWHR_FREE_RATIO)
			m_bChkWHRatioMode = FALSE;
	}
	else
	{
		GetDlgItem(IDC_CHK_WH_RATIO)->EnableWindow(FALSE);
	}

	//SetName
	m_EditName.SetWindowText(m_pElement->GetName().c_str());

	UpdateData(FALSE);
}

BOOL CElementSizePositionPage::OnApply()
{
	if(!m_bModified)
		return TRUE;

	if(!IsWindow(m_hWnd))
		return FALSE;

	UpdateData();
	//
	GEOMETRY::geom::Envelope newEnv = CalcEnvelope(m_EditPosX, m_EditPosY, m_EditWidth, m_EditHeight);
	m_pElement->ChangeGeometryEnvelopTo(newEnv);

	m_pElement->SetAnchorPos((Element::ELEMENT_ANCHOR_POS)m_radioAnchor);

	if(m_bChkWHRatioMode)
		m_pElement->SetWHRatioMode(Element::EWHR_FIX_RATIO);
	else
		m_pElement->SetWHRatioMode(Element::EWHR_FREE_RATIO);

	CString name;
	m_EditName.GetWindowText(name);
	m_pElement->SetName(name.GetString());

	return TRUE;
	
}

//////////////////////////////////////////////////////////////////////////

GEOMETRY::geom::Envelope CElementSizePositionPage::CalcEnvelope(double fPosX, double fPosY, double fWidth, double fHeight)
{
	switch(m_radioAnchor)
	{
	case 0:
		{
			return GEOMETRY::geom::Envelope(fPosX, fPosX+fWidth,fPosY,  fPosY-fHeight);
		}
		break;
	case 1:
		{
			return GEOMETRY::geom::Envelope(fPosX-fWidth/2, fPosX+fWidth/2,fPosY,  fPosY-fHeight);
		}
		break;
	case 2:
		{
			return GEOMETRY::geom::Envelope(fPosX-fWidth,  fPosX,fPosY, fPosY-fHeight);
		}
		break;
	case 3:
		{
			return GEOMETRY::geom::Envelope(fPosX, fPosX+fWidth,fPosY+fHeight/2,  fPosY-fHeight/2);
		}
		break;
	case 4:
		{
			return GEOMETRY::geom::Envelope(fPosX-fWidth/2, fPosX+fWidth/2,fPosY+fHeight/2,  fPosY-fHeight/2);
		}
		break;
	case 5:
		{
			return GEOMETRY::geom::Envelope(fPosX-fWidth, fPosX,fPosY+fHeight/2,  fPosY-fHeight/2);
		}
		break;
	case 6:
		{
			return GEOMETRY::geom::Envelope(fPosX, fPosX+fWidth,fPosY+fHeight,  fPosY);
		}
		break;
	case 7:
		{
			return GEOMETRY::geom::Envelope(fPosX-fWidth/2, fPosX+fWidth/2,fPosY+fHeight,  fPosY);
		}
		break;
	case 8:
		{
			return GEOMETRY::geom::Envelope(fPosX-fWidth, fPosX,fPosY+fHeight,  fPosY);
		}
		break;
	default:
		{
			return GEOMETRY::geom::Envelope(fPosX, fPosX+fWidth,fPosY,  fPosY-fHeight);
		}
		break;

	}
}

GEOMETRY::geom::Coordinate CElementSizePositionPage::GetAnchorPos(GEOMETRY::geom::Envelope& env)
{
	switch(m_radioAnchor)
	{
	case 0:
		{
			return GEOMETRY::geom::Coordinate(env.getMinX(), env.getMaxY());
		}
		break;
	case 1:
		{
			return GEOMETRY::geom::Coordinate((env.getMinX()+env.getMinX())/2, env.getMaxY());
		}
		break;
	case 2:
		{
			return GEOMETRY::geom::Coordinate(env.getMaxX(), env.getMaxY());
		}
		break;
	case 3:
		{
			return GEOMETRY::geom::Coordinate(env.getMinX(), (env.getMinY()+env.getMaxY())/2);
		}
		break;
	case 4:
		{
			return GEOMETRY::geom::Coordinate((env.getMinX()+env.getMaxX())/2, (env.getMinY()+env.getMaxY())/2);
		}
		break;
	case 5:
		{
			return GEOMETRY::geom::Coordinate(env.getMaxX(), (env.getMinY()+env.getMaxY())/2);
		}
		break;
	case 6:
		{
			return GEOMETRY::geom::Coordinate(env.getMinX(), env.getMinY());
		}
		break;
	case 7:
		{
			return GEOMETRY::geom::Coordinate((env.getMinX()+env.getMaxX())/2, env.getMinY());
		}
		break;
	case 8:
		{
			return GEOMETRY::geom::Coordinate(env.getMaxX(), env.getMinY());
		}
		break;
		
	}
}

void CElementSizePositionPage::SetModified(BOOL bChanged)
{
	CPropertyPage::SetModified(bChanged);

	m_bModified = bChanged;
}

// CDlgElementSizePosition 消息处理程序

void CElementSizePositionPage::OnEnChangeEditPosX()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}

void CElementSizePositionPage::OnEnChangeEditPosY()
{
	
	SetModified();
}

void CElementSizePositionPage::OnBnClickedRadioLeftTop()
{
	SetModified();
}

void CElementSizePositionPage::OnBnClickedRadioCenterTop()
{
	SetModified();
}

void CElementSizePositionPage::OnBnClickedRadioRightTop()
{
	SetModified();
}

void CElementSizePositionPage::OnBnClickedRadioLeftCenter()
{
	SetModified();
}

void CElementSizePositionPage::OnBnClickedRadioCenterCenter()
{
	SetModified();
}

void CElementSizePositionPage::OnBnClickedRadioRightCenter()
{
	SetModified();
}

void CElementSizePositionPage::OnBnClickedRadioLeftBottom()
{
	SetModified();
}

void CElementSizePositionPage::OnBnClickedRadioCenterBottom()
{
	SetModified();
}

void CElementSizePositionPage::OnBnClickedRadioRightBottom()
{
	SetModified();
}

void CElementSizePositionPage::OnEnChangeEditWidth()
{
	

	SetModified();
}

void CElementSizePositionPage::OnEnChangeEditHeight()
{
	SetModified();
}

void CElementSizePositionPage::OnEnChangeEditName()
{
	SetModified();
}

void CElementSizePositionPage::OnBnClickedChkWhRatio()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(m_bChkWHRatioMode)
	{
		if(abs(m_EditPosY)>0.000001)
			m_WHRatio = m_EditWidth/m_EditHeight;
		else
			m_WHRatio = 1;
	}
	SetModified();
}

void CElementSizePositionPage::OnEnKillfocusEditWidth()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(m_bChkWHRatioMode && abs(m_WHRatio)>0.000001)
		m_EditHeight = m_EditWidth / m_WHRatio;

	UpdateData(FALSE);
}


void CElementSizePositionPage::OnEnKillfocusEditHeight()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(m_bChkWHRatioMode)
		m_EditWidth = m_WHRatio*m_EditHeight;

	UpdateData(FALSE);

}
