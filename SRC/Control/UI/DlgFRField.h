#ifndef  DLG_FR_FIELD_
#define  DLG_FR_FIELD_

#include <queue>
// CDlgFRField �Ի���

//******************
//*****�б�λ��
//*****************
typedef struct List_pos
{
	long nRow;
	long nColumn;
	List_pos( long nR = -1, long nC = -1 ){ nRow = nR; nColumn = nC; }
}LIST_POS;

class Replacer;
class CAttributeTable;
//******************
//*****������
//*****************
class Finder{
	friend class Replacer;

public:
	Finder();
	virtual ~Finder();

public:
	//��ʼ����
	bool Inite( Control::CAttributeTable *table, 
		LIST_POS &posB, 
		LIST_POS &posE, 
		const char* szFind, 
		bool bIsCap = false,
		bool bIsWholeField = true );
	
	//��ѯ����Ƿ�Ϊ��
	bool IsEmpty();

	//��һλ��
	LIST_POS& NextPos( int iDir = 0 ); 

	//�Ƿ�õ���ѯ���
	bool HasQueryResult();

private:
	bool Find();

private:
	//���
	Control::CAttributeTable* m_table;
	
	//��ʼλ�ú���ֹλ��
	LIST_POS posBegin;
	LIST_POS posEnd;
 
	//��ѯ���
	std::vector<LIST_POS> m_vecResultPos; 
	//��ǰ����λ��
	int m_iCurIndex;

	//Ŀ���ַ���
	std::string m_lpszContent;

	//���ִ�Сд
	bool m_bIsCap;
	
	//ƥ������
	bool m_bIsWholeField;
};

//******************
//*****�滻��
//*****************
class Replacer
{
public:
	Replacer();
	virtual ~Replacer();

public:
	//��ʼ��
	void Inite( Finder *finder, const char* lpszReplace );

	//�滻����λ�� 
	bool Replace();

	//�滻����
	bool ReplaceAll();

protected:
	Finder *m_finder;
	
	//�滻����ַ���
	std::string m_lpszRelpace;
};


//******************
//CDlgFRField �Ի���
//*****************
class CDlgFRField : public CDialog
{
	DECLARE_DYNAMIC(CDlgFRField)

public:
	CDlgFRField(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFRField();

// �Ի�������
	enum { IDD = IDD_FINDREPLACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	afx_msg void OnTcnSelchangeTabFindReplace(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnReplace();
	afx_msg void OnBnClickedBtnReplaceall();

public:
	void UpdateCmbFindContent();

	void UpdateCmbReplaceContent();

protected:
	CString m_strFindContent;
	CComboBox m_cmbFindContent;
	CComboBox m_cmbMatchConditon;
	CString m_strMatchCondition;
	CComboBox m_cmbFindDirection;
	CComboBox m_cmbReplaceContent;
	CString m_strReplaceContent;
	CButton m_btnReplace;
	CButton m_btnReplaceAll;
	BOOL m_bIsMatchCap;
	CTabCtrl m_tabFindReplace;

	CString m_strLastFindContent; //��һ�β�ѯ������
	BOOL m_bLastMathCap; //��һ�δ�Сдƥ��
	CString m_strLastMathConditon;
protected:
	Finder m_Finder;

	Replacer m_Replacer;
private:
	static std::vector<CString> m_slpszFindcontent;
	static std::vector<CString> m_slpszReplacecontent;

public:
	afx_msg void OnCbnSelchangeCmbMatchcondition();
	afx_msg void OnBnClickedChkMatchcaps();
};

#endif // DLG_FR_FIELD_