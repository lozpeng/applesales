#pragma once

#include "ILayer.h"
#include "Resource.h"
#include "IRenderSetting.h"

class CFeatureRenderPage;

class CCustomPane : public CBCGPOutlookBarPane
{
	friend class CFeatureRenderPage;

	virtual BOOL OnSendCommand (const CBCGPToolbarButton* pButton);
	void EnsureVisible (int iButton);

	CFeatureRenderPage* m_pParent;
};

class CFeatureRenderPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFeatureRenderPage)

public:
	CFeatureRenderPage();
	virtual ~CFeatureRenderPage();
public:
	
    virtual void DoDataExchange(CDataExchange* pDX); 
	enum { IDD = IDD_FEATURE_RENDER_SET };



	DECLARE_MESSAGE_MAP()
public:

	void SetLayer(Carto::ILayer* player);

	virtual BOOL OnInitDialog();

	void SetActivePage(int index);

	virtual BOOL OnApply();

private:

	void CreateImageCtrl();
    
	void AddImageButtons();

protected:
	
	//用来放置图片的面板
	CBCGPOutlookBar		m_wndOutlookBar;
	CCustomPane	m_wndPane;

	Carto::ILayer* m_pLayer;

	CImageList       m_icons;

	std::vector<IRenderSetting*> m_pages;

	long             m_nActivePage;

};
