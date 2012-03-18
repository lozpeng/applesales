// GrdintClrComboBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GrdintClrComboBox.h"

GradientColor g_coloritems[5] ={RGB(255,255,0),RGB(255,0,255),
                                RGB(0,0,255),RGB(0,255,255),
                                RGB(127,255,0),RGB(255,127,255),
                                RGB(71,109,6),RGB(239,252,215),
                                RGB(255,255,127),RGB(127,0,255),
                                };
long g_colorCount = 5;
// CGrdintClrComboBox

//IMPLEMENT_DYNAMIC(CGrdintClrComboBox, CComboBox)


CGrdintClrComboBox::CGrdintClrComboBox()
{

}

CGrdintClrComboBox::~CGrdintClrComboBox()
{
}


//BEGIN_MESSAGE_MAP(CGrdintClrComboBox, CComboBox)
//END_MESSAGE_MAP()



// CGrdintClrComboBox ��Ϣ�������



void CGrdintClrComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  ������Ĵ����Ի���ָ����
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

	rBlockRect.DeflateRect(1, 1, 1, 1);

	//�������ڽ���״̬
	if( iState & ODS_FOCUS )								
		dcContext.DrawFocusRect( &rBlockRect );	

	CRect rColorRect(rBlockRect);
    rColorRect.DeflateRect(1,1,1,1);
	CRect rect(rColorRect);

	if( iItem != -1 )										
	{
		if(iItem == 2)
		{
			int aa;
			aa = 5;
		}
		dcContext.SetBkMode( TRANSPARENT );
		COLORREF ulStartColor = g_coloritems[iItem].m_startColor;
		COLORREF ulEndColor = g_coloritems[iItem].m_endColor;
		BYTE rStart = GetRValue(ulStartColor);
		BYTE gStart = GetGValue(ulStartColor);
		BYTE bStart = GetBValue(ulStartColor);
		BYTE rEnd = GetRValue(ulEndColor);
		BYTE gEnd = GetGValue(ulEndColor);
		BYTE bEnd = GetBValue(ulEndColor);


		//�����ɫ����
		for(int i=0; i<rColorRect.Width(); i++)
		{	
			BYTE R = (rEnd - rStart) * i / rColorRect.Width() + rStart;
			BYTE G = (gEnd - gStart) * i / rColorRect.Width() + gStart;
			BYTE B = (bEnd - bStart) * i / rColorRect.Width() + bStart;

			if(i != 0)
			{
				rect.left = rect.right;
			}

			rect.right = rect.left + 1;
			//�����ɫ����
			dcContext.FillSolidRect(&rect, RGB(R, G,B));
		}
	}
	//����CDC����
	dcContext.Detach();	
}

void CGrdintClrComboBox::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	for(int i=0; i<g_colorCount; i++)
	{
		AddString("");
	}


	CComboBox::PreSubclassWindow();

		SetCurSel(0);
}
COLORREF CGrdintClrComboBox::get_curStartColor()
{
	return g_coloritems[GetCurSel()].m_startColor;
}
COLORREF CGrdintClrComboBox::get_curEndColor()
{
	return g_coloritems[GetCurSel()].m_endColor;
}
