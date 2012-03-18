// otSymbolSelector.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "otMapControl.h"
#include "otSymbolSelector.h"
#include "CotSymbolList.h"

// CotSymbolSelector

IMPLEMENT_DYNCREATE(CotSymbolSelector, CCmdTarget)


CotSymbolSelector::CotSymbolSelector()
{
	EnableAutomation();
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	
	AfxOleLockApp();
}

CotSymbolSelector::~CotSymbolSelector()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}


void CotSymbolSelector::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CotSymbolSelector, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CotSymbolSelector, CCmdTarget)
	DISP_FUNCTION_ID(CotSymbolSelector, "SelectSymbol", dispidSelectSymbol, SelectSymbol, VT_UNKNOWN, VTS_UNKNOWN)
END_DISPATCH_MAP()

// ע��: ������� IID_IotSymbolSelector ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {1E5E4427-9C21-4DD0-867E-BAC51C6DAD63}
static const IID IID_IotSymbolSelector =
{ 0x1E5E4427, 0x9C21, 0x4DD0, { 0x86, 0x7E, 0xBA, 0xC5, 0x1C, 0x6D, 0xAD, 0x63 } };

BEGIN_INTERFACE_MAP(CotSymbolSelector, CCmdTarget)
	INTERFACE_PART(CotSymbolSelector, IID_IotSymbolSelector, Dispatch)
END_INTERFACE_MAP()

// {61F0A120-2A95-442F-B541-4B3C309ECAF0}
IMPLEMENT_OLECREATE_FLAGS(CotSymbolSelector, "otMapControl.otSymbolSelector", afxRegApartmentThreading, 0x61f0a120, 0x2a95, 0x442f, 0xb5, 0x41, 0x4b, 0x3c, 0x30, 0x9e, 0xca, 0xf0)


// CotSymbolSelector ��Ϣ�������

IotSymbol* CotSymbolSelector::SelectSymbol(IotSymbol* symbol)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!symbol)
	{
		return NULL;
	}

	IOriginDataPtr pData;
	symbol->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	long ldata;

	pData->get_OriginData(&ldata);

	Display::ISymbolPtr pSymbol =*((Display::ISymbolPtr*)ldata);

	otComUI::CotSymbolList symbollist;

	pSymbol = symbollist.SelectSymbol(pSymbol);

	if(!pSymbol)
	{
		return NULL;
	}

	Display::ISymbolPtr *ppSymbol =new Display::ISymbolPtr(pSymbol);

	IotSymbol *pretSymbol =NULL;


	IotSymbolConvertPtr pCon;

	CoCreateInstance(CLSID_otSymbolConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotSymbolConvert),(void**)&pCon);

	pCon->ConvertSymbol(long(ppSymbol),VARIANT_TRUE,&pretSymbol);

	return NULL;
}
