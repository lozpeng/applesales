#pragma once


// CLayerBasepropPage �Ի���

class CLayerBasepropPage : public CDialog
{
	DECLARE_DYNAMIC(CLayerBasepropPage)

public:
	CLayerBasepropPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLayerBasepropPage();

// �Ի�������
	enum { IDD = IDD_LAYERPROP_GENERAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
