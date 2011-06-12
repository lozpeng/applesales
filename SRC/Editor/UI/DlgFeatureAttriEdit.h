#pragma once

#include "resource.h"
#include "ILayer.h"
#include "BCGPPropList.h"
#include "CEditor.h"
using std::vector;

class CDlgFeatureAttriEdit : public CDialog
{
	DECLARE_DYNAMIC(CDlgFeatureAttriEdit)

public:
	CDlgFeatureAttriEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFeatureAttriEdit();

// 对话框数据
	enum { IDD = IDD_FEATURE_ATRIEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnPropertyChanged (WPARAM,LPARAM); 
	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();

	afx_msg void OnSelchangedTreeFeatures(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnTvnSelchangingTreeSelfeatures(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTreeSelfeatures(NMHDR *pNMHDR, LRESULT *pResult);


	virtual void OnOK();
public:
	//设置选择的要素
	void SetFeatures(vector<Carto::ILayer*> &allLayers,Editor::CEditor *pEditor);

	void Refresh();

	//保存上次修改的属性
	void SavePreAttribute();

private:
    vector<Carto::ILayer*>   m_allLayers;


	vector<CString>   m_layerNames;

	HTREEITEM         m_hpreTreeItem;

	CStatic m_propListLoc;

	CBCGPPropList m_PropList;

	CTreeCtrl m_SelFeatureTree;

	//做过修改的图层，用来记录回退
	vector<Carto::ILayer*>   m_ModifyLayers;

	Editor::CEditor *m_pEditor;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
