#pragma once
#include "ElementProperSheet.h"
#include "ElementSizePositionPage.h"
#include "ElementProperSheet.h"
#include "ScalebarMarkPage.h"
#include "ScalebarUnitPage.h"
#include "ScalebarStylePage.h"

class CScaleBarProperSheet :
	public CElementProperSheet
{
	DECLARE_DYNAMIC(CScaleBarProperSheet)
public:
	CScaleBarProperSheet(CString name , CWnd *pWnd = NULL);
	~CScaleBarProperSheet(void);

public:

	virtual INT_PTR DoModal();

	void SetElement(Element::IScaleBarPtr pElement);

	Element::IScaleBarPtr GetElement();

public:
	DECLARE_MESSAGE_MAP()

public:
	BOOL m_bTypeChanged;

public:
	CElementSizePositionPage sizePosPage;
	//CElementFramePage FramePage;
	CScalebarMarkPage MarkNumPage;
	CScalebarUnitPage UnitPage;
	CScalebarStylePage StylePage;

};
