#pragma once

// otMapPpg.h : CotMapPropPage ����ҳ���������


// CotMapPropPage : �й�ʵ�ֵ���Ϣ������� otMapPpg.cpp��

class CotMapPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CotMapPropPage)
	DECLARE_OLECREATE_EX(CotMapPropPage)

// ���캯��
public:
	CotMapPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_OTMAPCONTROL };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

