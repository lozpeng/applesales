#ifndef  DLG_FR_FIELD_
#define  DLG_FR_FIELD_

#include <queue>
// CDlgFRField 对话框

//******************
//*****列表位置
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
//*****查找类
//*****************
class Finder{
	friend class Replacer;

public:
	Finder();
	virtual ~Finder();

public:
	//初始设置
	bool Inite( Control::CAttributeTable *table, 
		LIST_POS &posB, 
		LIST_POS &posE, 
		const char* szFind, 
		bool bIsCap = false,
		bool bIsWholeField = true );
	
	//查询结果是否为空
	bool IsEmpty();

	//下一位置
	LIST_POS& NextPos( int iDir = 0 ); 

	//是否得到查询结果
	bool HasQueryResult();

private:
	bool Find();

private:
	//表格
	Control::CAttributeTable* m_table;
	
	//起始位置和终止位置
	LIST_POS posBegin;
	LIST_POS posEnd;
 
	//查询结果
	std::vector<LIST_POS> m_vecResultPos; 
	//当前查找位置
	int m_iCurIndex;

	//目标字符串
	std::string m_lpszContent;

	//区分大小写
	bool m_bIsCap;
	
	//匹配条件
	bool m_bIsWholeField;
};

//******************
//*****替换类
//*****************
class Replacer
{
public:
	Replacer();
	virtual ~Replacer();

public:
	//初始化
	void Inite( Finder *finder, const char* lpszReplace );

	//替换查找位置 
	bool Replace();

	//替换所有
	bool ReplaceAll();

protected:
	Finder *m_finder;
	
	//替换后的字符串
	std::string m_lpszRelpace;
};


//******************
//CDlgFRField 对话框
//*****************
class CDlgFRField : public CDialog
{
	DECLARE_DYNAMIC(CDlgFRField)

public:
	CDlgFRField(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFRField();

// 对话框数据
	enum { IDD = IDD_FINDREPLACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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

	CString m_strLastFindContent; //上一次查询的内容
	BOOL m_bLastMathCap; //上一次大小写匹配
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