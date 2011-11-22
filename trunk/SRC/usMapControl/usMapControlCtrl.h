#pragma once
#include "InternalControl.h"
#include "ICommand.h"
#include "ITool.h"


// CusMapCtrl : �й�ʵ�ֵ���Ϣ������� usMapControlCtrl.cpp��

class CusMapCtrl : public COleControl,public Framework::IMapCtrl
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
		dispidCurTool = 3,
		dispidRefresh = 2L,
		dispidAddShpfile = 1L

	};
protected:
	


public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	void AddShpfile(LPCTSTR filename);
	void Refresh(void);

private:
	Framework::ITool* GetTool(usToolType tooltype);

private:
	//��ǰ����
	Framework::ITool* m_pCurTool;

	usToolType m_Tooltype;
protected:
	usToolType GetCurTool(void);
	void SetCurTool(usToolType newVal);
};

