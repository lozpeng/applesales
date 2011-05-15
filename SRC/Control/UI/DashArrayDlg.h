#pragma once
#include "DashArrayPropListEx.h"
#include "DashArray.h"
#include "resource.h"
// ���ۺ�����Ի���
class CSymbolEditDlg;
class CDashArrayDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDashArrayDlg)

public:
	CDashArrayDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDashArrayDlg();
	void SetDashArray(Display::CDashArray *dashArray);
	void SetSymbolType(SYMBOL_TYPE type);
	
	void InitList();
	
private:
	void Update();
// �Ի�������
	enum { IDD = IDD_DASHARRAYDLG };
public:
	CDashArrayPropListEx m_wndPropList;					//���ۺ����������б�ؼ�
	CStatic	m_wndPropListLocation;						
	//CtoDashArray m_dashArray;							//���ڴ������ۺ����ݵ�����
private:
	Display::CDashArray *m_pDashArray;
	Display::CDashArray *m_pDashArrayCopy;
	SYMBOL_TYPE m_enumSymbolType;
	CString m_staticUnit;
	//ItoSymbolPtr m_pSymbol;								//����ķ���
	//ItoConfigItemPtr m_pChild;							//����Ľڵ�
	//CSymbolEditDlg * m_pParentDlg;						//����ķ��Ի�������ָ��
	

	//CBCGPProp* m_pPropGroup;								//�����б�����������㣩
	int m_iIndex;										//���ۺ��������
	//CPoint m_cPoint;									//�õ��Ի���λ��ʱ���ڴ洢
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedButtonadd();
public:
	afx_msg void OnBnClickedButtonrmv();
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	afx_msg void OnBnClickedCancel();
};
