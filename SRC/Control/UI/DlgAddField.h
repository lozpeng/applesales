#pragma once
#include "afxwin.h"
#include "Field.h"


// CDlgAddField �Ի���

class CDlgAddField : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddField)

public:
	CDlgAddField(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAddField();

// �Ի�������
	enum { IDD = IDD_ADD_FIELD };

public:
	CString GetFieldName(){ return m_strName; }

	Geodatabase::FIELD_TYPE GetFieldType(){ return m_fieldType; }

	long GetLength() { return m_nLength; }

	long GetPrecision() { return m_nPrecision; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	//��ʼ�������б�
	void InitFieldTypes();
	
	virtual BOOL OnInitDialog();
	
	afx_msg void OnEnChangeEdtName();
	afx_msg void OnCbnSelchangeCmbType();
	
private:
	//�ؼ� ���� 
	CString m_strName;
	CComboBox m_cmbType;
	long m_nLength;
	long m_nPrecision;

	//�ֶ�����
	Geodatabase::FIELD_TYPE m_fieldType;
};
