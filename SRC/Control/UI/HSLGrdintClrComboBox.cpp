// GrdintClrComboBox.cpp : 实现文件
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



// CGrdintClrComboBox 消息处理程序



void CHSLGrdintClrComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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


		//填充颜色区域
		for(int i=0; i<rColorRect.Width(); i++)
		{	
			RGBColor color=colorramp.GetColor(i);

			if(i != 0)
			{
				rect.left = rect.right;
			}

			rect.right = rect.left + 1;
			//填充颜色区域
			dcContext.FillSolidRect(&rect, RGB(color.red, color.green,color.blue));
		}
	}
	//分离CDC对象
	dcContext.Detach();	
}

void CHSLGrdintClrComboBox::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
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
