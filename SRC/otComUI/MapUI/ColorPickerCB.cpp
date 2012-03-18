#include "stdafx.h"
#include "ColorPickerCB.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//����ENVI��ɫ��ѡ����Ҫ����ɫ������������趨��ɫ�����Ŀ
//const int g_iColorMapIndexs[15] = {2,4,5,6,10,11,12,13,15,16,17,23,28,29,38};
//const int g_iColorMapCount = 15;

const int g_iColorMapIndexs[6] = {23,28,16,17,29,38};
const int g_iColorMapCount = 6;


//IMPLEMENT_DYNAMIC(CColorPickerCB, CComboBox)
CColorPickerCB::CColorPickerCB()
{
	m_pEnviColorMap = new CEnviColorMap();
}


CColorPickerCB::~CColorPickerCB()
{
	if(NULL != m_pEnviColorMap)
	{
		delete m_pEnviColorMap;
	}
}

void CColorPickerCB::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC			dcContext;
	CRect		rItemRect(lpDrawItemStruct->rcItem);
	CRect		rBlockRect(rItemRect);
	CBrush		brFrameBrush;
	int         iState = lpDrawItemStruct->itemState;
	int         iItem = lpDrawItemStruct->itemID;
	// ��ϵCDC����
	if( !dcContext.Attach(lpDrawItemStruct->hDC))				
		return;			

	//������ɫ��ˢ
	brFrameBrush.CreateStockObject(BLACK_BRUSH);			

	rItemRect.DeflateRect(1,1,1,1);
	//�������ڽ���״̬
	if( iState & ODS_FOCUS )								
		dcContext.DrawFocusRect( &rItemRect );
	rItemRect.DeflateRect(1,1,1,1);

	rBlockRect = rItemRect;


	if( iItem != -1 )										
	{
	 	dcContext.SetBkMode( TRANSPARENT );
		COLOR_MAP struColorMap;
		m_pEnviColorMap->GetColorMap(g_iColorMapIndexs[iItem],struColorMap);
        int iColorIndex = 0;
		COLORREF ulColor;
		//�����ɫ����
		for(int i=0; i<rItemRect.Width(); i++)
	   {		   
           iColorIndex = 255 * i / rItemRect.Width();
		   if(0 == iColorIndex)
		   {
			   iColorIndex = 1;
		   }
		   ulColor = RGB(struColorMap.ucR[iColorIndex],struColorMap.ucG[iColorIndex],struColorMap.ucB[iColorIndex]);
		   if(i != 0)
		   {
			   rBlockRect.left = rBlockRect.right;
		   }
		   rBlockRect.right = rBlockRect.left + 1;
		   //�����ɫ����
		   dcContext.FillSolidRect(&rBlockRect, ulColor);
	   }
	}
	//����CDC����
	dcContext.Detach();										
}

void CColorPickerCB::PreSubclassWindow()
{
	if(m_pEnviColorMap->GetOpenResult())
	{
		for(int i=0; i< g_iColorMapCount; i++)
		{
			AddString("");
		}
	}
	CComboBox::PreSubclassWindow();
	//���õ�ǰѡ���colormap
	SetCurSel(0);
}

void CColorPickerCB::GetColorMap(int iIndex,COLOR_MAP& struColorMap)
{
	//������ɫ��Ϣ����
	m_pEnviColorMap->GetColorMap(g_iColorMapIndexs[iIndex],struColorMap);
}
