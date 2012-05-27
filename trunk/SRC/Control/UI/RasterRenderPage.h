#pragma once

#include "ILayer.h"
#include "Resource.h"
#include "IRenderSetting.h"

class CRasterRenderPage;

class CCustomPane_R : public CBCGPOutlookBarPane
{
	friend class CRasterRenderPage;

	virtual BOOL OnSendCommand (const CBCGPToolbarButton* pButton);
	void EnsureVisible (int iButton);
public:
	CRasterRenderPage* m_pParent;
};

class CRasterRenderPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CRasterRenderPage)

public:
	CRasterRenderPage();
	virtual ~CRasterRenderPage();
public:
	
    virtual void DoDataExchange(CDataExchange* pDX); 
	enum { IDD = IDD_RASTER_RENDER_SET };



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
	CCustomPane_R	m_wndPane;

	Carto::ILayer* m_pLayer;

	CImageList       m_icons;

	std::vector<IRenderSetting*> m_pages;

	long             m_nActivePage;

};
