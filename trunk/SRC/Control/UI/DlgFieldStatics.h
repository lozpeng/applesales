#pragma once
#include "afxwin.h"
#include "resource.h"
#include "CommonData.h"
// CDlgFieldStatics �Ի���


class CDlgFieldStatics : public CDialog
{
	DECLARE_DYNAMIC(CDlgFieldStatics)

public:
	CDlgFieldStatics(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFieldStatics();

// �Ի�������
	enum { IDD = IDD_FIELD_STASTIC };

public:
	//��ʼ�������ֶ�ֵ����
	void InitFieldsValues( std::vector<LP_CAL_FIELDVALUE> &vecFields );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelchangeCmbSelfield();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnOutput();

protected:
	//ͳ��
	BOOL Statics( const char *szFieldName );

	//���
	void OutPutResult( const char *szType, 
					long nCount,
					double dMinimum, 
					double dMaxMum,
					double dSum,
					double dMean,
					double dStdDeviation );

	//��ü��������
	void GetCalculateValues( const char *szFieldName );

private:
	//����
	std::vector<LP_CAL_FIELDVALUE> m_vecCalFields;

	//���������
	std::vector<double> m_vecCalValues;
	
	//�Ƿ�ֻ����ѡ�е���
	BOOL  m_bOnlyCalSel;

protected:
	CComboBox m_cmbField;
	CString m_szOutputStatics;
	CString m_szField;		
public:
	afx_msg void OnBnClickedChkSel();
};
