/******************************************************************************
 * $Id: BCGStyleImp.cpp  2009-09-16 10:47:00 $
 *
 * Project:  BCG������
 * Purpose:  �ṩ��ʼ��BCG������ĺ���
 * Author:    �ƺ�־
 * Version:   1.0
 * 09.9.16:  ���SetBCGButtonStyle
 * 09.9.17:  ���SetBCGRadioStyle
 ******************************************************************************/

#include "stdafx.h"
#include "BCGStyleHeader.h"
//#include "BCGStyle.h"
#include <string>
#include "SafeResource.h"
/* ====================================================*/
//��    �ܣ�BCG--Button�������
//��    ����
//			btn:  Ҫ���õ�Button
//		    nId:  BITMAP��ԴID
//			strText:
//			nBorderStyle:
//			nImage:
//			nImageLocation:
//�� �� ֵ��NULL
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
//��    �ܣ�BCG--Radio�������
//��    ����
//			btn:  Ҫ���õ�Button
//		    nOffId:  ��ѡ��״̬��ťBMP��ԴID
//			nOnId:ѡ��״̬��ťBMP��ԴID
//�� �� ֵ��NULL
/*=====================================================*/
//����BCGRadio���
void SetBCGRadioStyle(CBCGPButton& btn,
					  int nOffId,
					  int nOnId)
{
	CSafeResource resInstance;
	//�����ʱ�̶�
	btn.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_NOBORDERS;
	btn.SetImage (EnumRadio::OFFRADIO32);
	btn.SetCheckedImage (EnumRadio::ONRADIO32);
	btn.SizeToContent();
}