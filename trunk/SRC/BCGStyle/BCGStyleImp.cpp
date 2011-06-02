/******************************************************************************
 * $Id: BCGStyleImp.cpp  2009-09-16 10:47:00 $
 *
 * Project:  BCG界面风格
 * Purpose:  提供初始化BCG界面风格的函数
 * Author:    黄鸿志
 * Version:   1.0
 * 09.9.16:  添加SetBCGButtonStyle
 * 09.9.17:  添加SetBCGRadioStyle
 ******************************************************************************/

#include "stdafx.h"
#include "BCGStyleHeader.h"
//#include "BCGStyle.h"
#include <string>
#include "SafeResource.h"
/* ====================================================*/
//功    能：BCG--Button风格设置
//参    数：
//			btn:  要设置的Button
//		    nId:  BITMAP资源ID
//			strText:
//			nBorderStyle:
//			nImage:
//			nImageLocation:
//返 回 值：NULL
/*=====================================================*/

void SetBCGButtonStyle(CBCGPButton& btn, 
					int nId, 
					CString strText, 
					int nBorderStyle, 
					int nImage, 
					int nImageLocation)
{
	CSafeResource resInstance;
	switch (nBorderStyle)
	{
	case 0:
		btn.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		break;

	case 1:
		btn.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;
		break;

	case 2:
		btn.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_3D;
	}

	if (nId < 0)	// Text only
	{
		btn.SetImage ((HBITMAP) NULL);
	}
	else
	{
		btn.SetImage(nId);
	}

	if (nImage == 0)
	{
		btn.SetWindowText (_T(""));
	}
	else
	{
		btn.SetWindowText (strText);
	}

	switch (nImageLocation)
	{
	case 0:
		btn.m_bRighImage = FALSE;
		btn.m_bTopImage = FALSE;
		break;

	case 1:
		btn.m_bRighImage = TRUE;
		btn.m_bTopImage = FALSE;
		break;

	case 2:
		btn.m_bRighImage = FALSE;
		btn.m_bTopImage = TRUE;
		break;
	}
	//return CBCGStyle::OnResetButton(btn, 102, strText, nBorderStyle, nImage, nImageLocation);
}

/* ====================================================*/
//功    能：BCG--Radio风格设置
//参    数：
//			btn:  要设置的Button
//		    nOffId:  非选中状态按钮BMP资源ID
//			nOnId:选中状态按钮BMP资源ID
//返 回 值：NULL
/*=====================================================*/
//设置BCGRadio风格
void SetBCGRadioStyle(CBCGPButton& btn,
					  int nOffId,
					  int nOnId)
{
	CSafeResource resInstance;
	//风格暂时固定
	btn.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_NOBORDERS;
	btn.SetImage (EnumRadio::OFFRADIO32);
	btn.SetCheckedImage (EnumRadio::ONRADIO32);
	btn.SizeToContent();
}