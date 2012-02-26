#pragma once
#include "afxwin.h"
#include <vector>
#include <map>
#include <string>

// CDlgModifyImgClass 对话框

struct ImgClassInfo
{
	unsigned char value; //类别像素值
	std::string name;  //类别名称
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};
class CDlgModifyImgClass : public CDialog
{
	DECLARE_DYNAMIC(CDlgModifyImgClass)

public:
	CDlgModifyImgClass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgModifyImgClass();

// 对话框数据
	enum { IDD = IDD_DLG_MODIFYIMGCLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnCbnSelchangeComboSelclsFile();
	afx_msg void OnBnClickedBtSelclassfile();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboSelclsValue();
	virtual BOOL OnInitDialog();

public:
	CComboBox m_ComboSelfile;
	CComboBox m_ComboSelClass;
	CString m_strClassfile;
	CString m_classname;
	CBCGPColorButton m_colorbtn;
	std::vector<ImgClassInfo> m_classinfos;
	afx_msg void OnBnClickedBtnColorpick();
	afx_msg void OnEnChangeEditClsname();
	CString m_classvalue;
	afx_msg void OnEnUpdateEditClsname();
	afx_msg void OnEnKillfocusEditClsname();
private:
	void saveClassinfo();
	void loadClassinfo();
};
