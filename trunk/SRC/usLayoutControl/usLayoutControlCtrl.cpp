// usLayoutControlCtrl.cpp : CusLayoutCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "usLayoutControl.h"
#include "usLayoutControlCtrl.h"
#include "usLayoutControlPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CusLayoutCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CusLayoutCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CusLayoutCtrl, COleControl)
	DISP_FUNCTION_ID(CusLayoutCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CusLayoutCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CusLayoutCtrl, 1)
	PROPPAGEID(CusLayoutControlPropPage::guid)
END_PROPPAGEIDS(CusLayoutCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CusLayoutCtrl, "USLAYOUTCONTROL.usLayoutControlCtrl.1",
	0x6729de6c, 0xb113, 0x441e, 0x9c, 0xc1, 0xc6, 0x76, 0xa, 0xa5, 0x1, 0xe6)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CusLayoutCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_DusLayoutControl =
		{ 0x2A2508B5, 0xE59A, 0x40B5, { 0x8C, 0x23, 0x90, 0x9C, 0x2F, 0x8F, 0x65, 0xAF } };
const IID BASED_CODE IID_DusLayoutControlEvents =
		{ 0x5EF20983, 0x2A99, 0x49E8, { 0xB5, 0xC7, 0xF7, 0xDE, 0xCF, 0xD1, 0x78, 0x1A } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwusLayoutControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CusLayoutCtrl, IDS_USLAYOUTCONTROL, _dwusLayoutControlOleMisc)



// CusLayoutCtrl::CusLayoutCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CusLayoutCtrl ��ϵͳע�����

BOOL CusLayoutCtrl::CusLayoutCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_USLAYOUTCONTROL,
			IDB_USLAYOUTCONTROL,
			afxRegApartmentThreading,
			_dwusLayoutControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CusLayoutCtrl::CusLayoutCtrl - ���캯��

CusLayoutCtrl::CusLayoutCtrl()
{
	InitializeIIDs(&IID_DusLayoutControl, &IID_DusLayoutControlEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CusLayoutCtrl::~CusLayoutCtrl - ��������

CusLayoutCtrl::~CusLayoutCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CusLayoutCtrl::OnDraw - ��ͼ����

void CusLayoutCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CusLayoutCtrl::DoPropExchange - �־���֧��

void CusLayoutCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CusLayoutCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CusLayoutCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CusLayoutCtrl::AboutBox - ���û���ʾ�����ڡ���

void CusLayoutCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_USLAYOUTCONTROL);
	dlgAbout.DoModal();
}



// CusLayoutCtrl ��Ϣ�������
