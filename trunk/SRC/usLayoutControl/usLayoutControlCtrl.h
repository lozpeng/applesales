#pragma once

// usLayoutControlCtrl.h : CusLayoutCtrl ActiveX �ؼ����������


// CusLayoutCtrl : �й�ʵ�ֵ���Ϣ������� usLayoutControlCtrl.cpp��

class CusLayoutCtrl : public COleControl
{
	DECLARE_DYNCREATE(CusLayoutCtrl)

// ���캯��
public:
	CusLayoutCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CusLayoutCtrl();

	DECLARE_OLECREATE_EX(CusLayoutCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CusLayoutCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CusLayoutCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CusLayoutCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
	};
};

