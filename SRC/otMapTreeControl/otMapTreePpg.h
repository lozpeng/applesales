#pragma once

// otMapTreePpg.h : CotMapTreePropPage ����ҳ���������


// CotMapTreePropPage : �й�ʵ�ֵ���Ϣ������� otMapTreePpg.cpp��

class CotMapTreePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CotMapTreePropPage)
	DECLARE_OLECREATE_EX(CotMapTreePropPage)

// ���캯��
public:
	CotMapTreePropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_OTMAPTREECONTROL };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

