#pragma once

// usLayoutControlPropPage.h : CusLayoutControlPropPage ����ҳ���������


// CusLayoutControlPropPage : �й�ʵ�ֵ���Ϣ������� usLayoutControlPropPage.cpp��

class CusLayoutControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CusLayoutControlPropPage)
	DECLARE_OLECREATE_EX(CusLayoutControlPropPage)

// ���캯��
public:
	CusLayoutControlPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_USLAYOUTCONTROL };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

