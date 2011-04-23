#include "stdafx.h"
#include "ColorPickerCB.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//根据ENVI颜色表选择需要的颜色表的索引，并设定颜色表的数目
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
	// 联系CDC对象
	if( !dcContext.Attach(lpDrawItemStruct->hDC))				
		return;			

	//创建黑色画刷
	brFrameBrush.CreateStockObject(BLACK_BRUSH);			

	rItemRect.DeflateRect(1,1,1,1);
	//如果该项处于焦点状态
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
		//填充颜色区域
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
		   //填充颜色区域
		   dcContext.FillSolidRect(&rBlockRect, ulColor);
	   }
	}
	//分离CDC对象
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
	//设置当前选择的colormap
	SetCurSel(0);
}

void CColorPickerCB::GetColorMap(int iIndex,COLOR_MAP& struColorMap)
{
	//更新颜色信息数据
	m_pEnviColorMap->GetColorMap(g_iColorMapIndexs[iIndex],struColorMap);
}
