// GrdintClrComboBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HSLGrdintClrComboBox.h"
#include "HSLColorRamp.h"
using namespace Display;

struct HSLGradientColor
{
	HSLColor m_startColor;
	HSLColor m_endColor;
};

static HSLGradientColor g_coloritems[5] ={HSLColor(190,70,99),HSLColor(190,70,13),
HSLColor(13*1.5,0.4166*173,0.4166*229),HSLColor(13*1.5,0.4166*173,0.4166*142),
HSLColor(29*1.5,0.4166*168,0.4166*229),HSLColor(29*1.5,0.4166*168,0.4166*33),
HSLColor(228*1.5,0.4166*231,0.4166*236),HSLColor(228*1.5,0.4166*231,0.4166*118),
HSLColor(127*1.5,0.4166*79,0.4166*212),HSLColor(127*1.5,0.4166*79,0.4166*89),
};

static long g_colorCount = 5;
// CGrdintClrComboBox

//IMPLEMENT_DYNAMIC(CGrdintClrComboBox, CComboBox)


CHSLGrdintClrComboBox::CHSLGrdintClrComboBox()
{

}

CHSLGrdintClrComboBox::~CHSLGrdintClrComboBox()
{
}


//BEGIN_MESSAGE_MAP(CGrdintClrComboBox, CComboBox)
//END_MESSAGE_MAP()



// CGrdintClrComboBox ��Ϣ�������



void CHSLGrdintClrComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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
		HSLColor ulStartColor = g_coloritems[iItem].m_startColor;
		HSLColor ulEndColor = g_coloritems[iItem].m_endColor;

		HSLColorRamp colorramp;
		colorramp.setStartColor(ulStartColor);
		colorramp.setEndColor(ulEndColor);
		colorramp.setSize(rColorRect.Width());

		/*BYTE rStart = GetRValue(ulStartColor);
		BYTE gStart = GetGValue(ulStartColor);
		BYTE bStart = GetBValue(ulStartColor);
		BYTE rEnd = GetRValue(ulEndColor);
		BYTE gEnd = GetGValue(ulEndColor);
		BYTE bEnd = GetBValue(ulEndColor);*/


		//�����ɫ����
		for(int i=0; i<rColorRect.Width(); i++)
		{	
			RGBColor color=colorramp.GetColor(i);

			if(i != 0)
			{
				rect.left = rect.right;
			}

			rect.right = rect.left + 1;
			//�����ɫ����
			dcContext.FillSolidRect(&rect, RGB(color.red, color.green,color.blue));
		}
	}
	//����CDC����
	dcContext.Detach();	
}

void CHSLGrdintClrComboBox::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	for(int i=0; i<g_colorCount; i++)
	{
		AddString("");
	}


	CComboBox::PreSubclassWindow();

	SetCurSel(0);
}
HSLColor CHSLGrdintClrComboBox::get_curStartColor()
{
	return g_coloritems[GetCurSel()].m_startColor;
}
HSLColor CHSLGrdintClrComboBox::get_curEndColor()
{
	return g_coloritems[GetCurSel()].m_endColor;
}
