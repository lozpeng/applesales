#pragma once
#include "afxwin.h"


// CDlgFieldCalculate �Ի���

class CDlgFieldCalculate : public CDialog
{
	DECLARE_DYNAMIC(CDlgFieldCalculate)

public:
	CDlgFieldCalculate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFieldCalculate();

// �Ի�������
	enum { IDD = IDD_FIELD_CALCULATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	afx_msg void OnLbnDblclkLstField();
	afx_msg void OnLbnDblclkLstOperate();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSubstract();
	afx_msg void OnBnClickedBtnMultiply();
	afx_msg void OnBnClickedBtnDivide();
	afx_msg void OnBnClickedBtnEqual();
	afx_msg void OnBnClickedBtnMi();

public:
	void Init( int iFieldIndex, 
		std::vector<long> &vSelFeatures, 
		std::vector<long> &vAllFeatures,
		Geodatabase::IFeatureClassPtr pFeatureClass );
	
private:
	//β���������
	void AddBackBracket( CString &szAdded );
	//��Ӳ�����
	void AddOprator( LPCTSTR szOp );
	
	//����ַ���
	CString GetMathExpr();
	//�Ѵ��ֶα�������ѧ���ʽ������������ʽ�ı��ʽ
	void MathExpreParser( CString &szMathExpr, Geodatabase::CFeaturePtr pFeature );
	//����
	void Calculate();

	//���غ����б�
	void ReLoadFuntionList();

protected:
	CListBox m_LstFields;
	CListBox m_lstFunction;
	CEdit m_edtMathExpr;
	int m_iType;
	BOOL m_bOnlySel;
	CString m_szMathExpr;

	//������FeatureClass
	Geodatabase::IFeatureClassPtr m_pFeatureClass;

private:
	//���ʽѡ��λ�� 
	int m_iStart;
	int m_iEnd;
	
	//ѡ��
	std::vector<int> m_vSelFeatureIndex;

	//ȫ����¼����
	std::vector<int> m_vAllFieldsIndex;

	//�����ֶ�
	int m_iCalFieldIndex;

public:
	afx_msg void OnBnClickedRadioNum();
	afx_msg void OnBnClickedRadioChar();
	afx_msg void OnBnClickedRadioTime();
	afx_msg void OnBnClickedOk();
};
