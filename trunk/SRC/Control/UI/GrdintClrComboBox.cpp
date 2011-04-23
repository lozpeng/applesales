// GrdintClrComboBox.cpp : 实现文件
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



// CGrdintClrComboBox 消息处理程序



void CGrdintClrComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	CDC			dcContext;
	CRect		rItemRect(lpDrawItemStruct->rcItem);
	CRect		rBlockRect(rItemRect);
	CBrush		brFrameBrush;
	int         iState = lpDrawItemStruct->itemState;
	int         iItem = lpDrawItemStruct->itemID;
	// 联系CDC对象
	if( !dcContext.Attach(lpDrawItemStruct->hDC))				
		return;			

	//创建黑色画刷
	brFrameBrush.CreateStockObject(BLACK_BRUSH);	

	rBlockRect.DeflateRect(1, 1, 1, 1);

	//如果该项处于焦点状态
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


		//填充颜色区域
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
			//填充颜色区域
			dcContext.FillSolidRect(&rect, RGB(R, G,B));
		}
	}
	//分离CDC对象
	dcContext.Detach();	
}

void CGrdintClrComboBox::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
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
