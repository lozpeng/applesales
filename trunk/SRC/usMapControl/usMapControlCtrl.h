#pragma once
#include "InternalControl.h"
// usMapControlCtrl.h : CusMapCtrl ActiveX �ؼ����������


// CusMapCtrl : �й�ʵ�ֵ���Ϣ������� usMapControlCtrl.cpp��

class CusMapCtrl : public COleControl
{
	DECLARE_DYNCREATE(CusMapCtrl)

// ���캯��
public:
	CusMapCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CusMapCtrl();

	DECLARE_OLECREATE_EX(CusMapCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CusMapCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CusMapCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CusMapCtrl)		// �������ƺ�����״̬

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
		dispidRefresh = 2L,
		dispidAddShpfile = 1L

	};
protected:
	

private:
	CInternalControl m_MapControl;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	void AddShpfile(LPCTSTR filename);
	void Refresh(void);
};
