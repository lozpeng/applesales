#pragma once

#include "MapTree.h"
// otMapTreeCtrl.h : CotMapTreeCtrl ActiveX �ؼ����������


// CotMapTreeCtrl : �й�ʵ�ֵ���Ϣ������� otMapTreeCtrl.cpp��

class CotMapTreeCtrl : public COleControl
{
	DECLARE_DYNCREATE(CotMapTreeCtrl)

// ���캯��
public:
	CotMapTreeCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CotMapTreeCtrl();

	DECLARE_OLECREATE_EX(CotMapTreeCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CotMapTreeCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CotMapTreeCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CotMapTreeCtrl)		// �������ƺ�����״̬

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
		eventidOnMouseMove = 4L,
		eventidOnMouseUp = 3L,
		eventidOnMouseDown = 2L,
		eventidOnDoubleClick = 1L,
		dispidShowPopMenu =4L,
		dispidHasLine = 3L,
		dispidUpdate = 2L,
		dispidSetFriendControl = 1L
	};

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);


protected:
	void SetFriendControl(IDispatch* MapControl);

	void Update(void);

	VARIANT_BOOL GetHasLine(void);

	void SetHasLine(VARIANT_BOOL newVal);

	VARIANT_BOOL GetShowPopMenu(void);

	void SetShowPopMenu(VARIANT_BOOL newVal);

public:
	/**
	* �������˫���¼�
	* @param button ��ʾ���µ�������ĸ���,0����û�а�����1���������2�����Ҽ�,3�������
	* @param flag ���ֵ������,���ڼ�¼����һЩ����������
	* @param X �����X���꣬�ͻ�������ϵ
	* @param Y �����Y���꣬�ͻ�������ϵ
	* 
	*/
	void FireDoubleClick(LONG button, LONG flag, LONG x, LONG y);


	/**
	* ������굥���¼�
	* @param button ��ʾ���µ�������ĸ���,1���������2�����Ҽ�,3�������
	* @param flag ���ֵ������,���ڼ�¼����һЩ����������
	* @param X �����X���꣬�ͻ�������ϵ
	* @param Y �����Y���꣬�ͻ�������ϵ
	* 
	*/
	void FireMouseDown(LONG button, LONG flag, LONG x, LONG y);

	/**
	* �������̧���¼�
	* @param button ��ʾ���µ�������ĸ���,1���������2�����Ҽ�,3�������
	* @param flag ���ֵ������,���ڼ�¼����һЩ����������
	* @param X �����X���꣬�ͻ�������ϵ
	* @param Y �����Y���꣬�ͻ�������ϵ
	* 
	*/
	void FireMouseUp(LONG button, LONG flag, LONG x, LONG y);


	void FireMouseMove(LONG button, LONG flag, LONG x, LONG y);


public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

private:
	CMapTree m_wndTree;

	//�ؼ�ָ��
	_DotMapControl *m_pMapControl;

	//������ʽ�Ƿ������
	BOOL  m_hasLine;
};

