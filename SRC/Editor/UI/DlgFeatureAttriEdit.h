#pragma once

#include "resource.h"
#include "ILayer.h"
#include "BCGPPropList.h"
using std::vector;

class CDlgFeatureAttriEdit : public CDialog
{
	DECLARE_DYNAMIC(CDlgFeatureAttriEdit)

public:
	CDlgFeatureAttriEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFeatureAttriEdit();

// �Ի�������
	enum { IDD = IDD_FEATURE_ATRIEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnPropertyChanged (WPARAM,LPARAM); 
	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();

	afx_msg void OnSelchangedTreeFeatures(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnTvnSelchangingTreeSelfeatures(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTreeSelfeatures(NMHDR *pNMHDR, LRESULT *pResult);


	virtual void OnOK();
public:
	//����ѡ���Ҫ��
	void SetFeatures(vector<Carto::ILayer*> &allLayers);

	void Refresh();

	//�����ϴ��޸ĵ�����
	void SavePreAttribute();

private:
    vector<Carto::ILayer*>   m_allLayers;


	vector<CString>   m_layerNames;

	HTREEITEM         m_hpreTreeItem;

	CStatic m_propListLoc;

	CBCGPPropList m_PropList;

	CTreeCtrl m_SelFeatureTree;

};
