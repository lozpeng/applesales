/******************************************************************************
 * $Id: BCGStyleHeader.h  2009-09-16 10:47:00 $
 *
 * Project:  BCG界面风格
 * Purpose:  提供初始化BCG界面风格的函数
 * Author:    黄鸿志
 * Version:   1.0
 ******************************************************************************/

#include <string>
class CBCGPButton;
using std::string;

//常用应用按钮
enum EnumApplyBtn
{
	OKBUTTON = 101,     //确定 
	CANCELBUTTON,		//取消
	LEFTBUTTON,
	RIGHTBUTTON,
	HELPBUTTON,
	OPENBUTTON,
	STILLBUTTON,
};
//Radio图标
enum EnumRadio
{
	ONRADIO32 = 301,
	OFFRADIO32,
};

//设置BCGButton风格
void SetBCGButtonStyle(CBCGPButton& btn, 
					int nId, 
					CString strText, 
					int nBorderStyle = 0, 
					int nImage = 2, 
					int nImageLocation = 1);

//设置BCGRadio风格
void SetBCGRadioStyle(CBCGPButton& btn,
					  int nOffId = 0,
					  int nOnId = 0);