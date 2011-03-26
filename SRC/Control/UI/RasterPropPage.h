#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "ILayer.h"
// CRasterPropPage �Ի���

class CRasterPropPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CRasterPropPage)

public:
	CRasterPropPage();
	virtual ~CRasterPropPage();

// �Ի�������
	enum { IDD = IDD_RASTER_PROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_wndPropListLocation;
	virtual BOOL OnInitDialog();

	void SetLayer(Carto::ILayer* player);

private:
	Carto::ILayer* m_player;

	CBCGPPropList	m_wndPropList;
};
