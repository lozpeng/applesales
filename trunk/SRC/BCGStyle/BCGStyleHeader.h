/******************************************************************************
 * $Id: BCGStyleHeader.h  2009-09-16 10:47:00 $
 *
 * Project:  BCG������
 * Purpose:  �ṩ��ʼ��BCG������ĺ���
 * Author:    �ƺ�־
 * Version:   1.0
 ******************************************************************************/

#include <string>
class CBCGPButton;
using std::string;

//����Ӧ�ð�ť
enum EnumApplyBtn
{
	OKBUTTON = 101,     //ȷ�� 
	CANCELBUTTON,		//ȡ��
	LEFTBUTTON,
	RIGHTBUTTON,
	HELPBUTTON,
	OPENBUTTON,
	STILLBUTTON,
};
//Radioͼ��
enum EnumRadio
{
	ONRADIO32 = 301,
	OFFRADIO32,
};

//����BCGButton���
void SetBCGButtonStyle(CBCGPButton& btn, 
					int nId, 
					CString strText, 
					int nBorderStyle = 0, 
					int nImage = 2, 
					int nImageLocation = 1);

//����BCGRadio���
void SetBCGRadioStyle(CBCGPButton& btn,
					  int nOffId = 0,
					  int nOnId = 0);