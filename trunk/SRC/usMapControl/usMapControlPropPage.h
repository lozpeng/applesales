#pragma once

// usMapControlPropPage.h : CusMapControlPropPage ����ҳ���������


// CusMapControlPropPage : �й�ʵ�ֵ���Ϣ������� usMapControlPropPage.cpp��

class CusMapControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CusMapControlPropPage)
	DECLARE_OLECREATE_EX(CusMapControlPropPage)

// ���캯��
public:
	CusMapControlPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_USMAPCONTROL };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

