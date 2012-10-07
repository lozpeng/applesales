#ifndef _LAYOUT_PRINT_TO_IMAGE_H
#define _LAYOUT_PRINT_TO_IMAGE_H



#include "ICommand.h"
#include "ILayoutCtrl.h"
#include "IRasterDataset.h"

namespace Control
{

class  CPrintToImageCmd : public  Framework::ICommand
{
public:
	CPrintToImageCmd();
	~CPrintToImageCmd();

public:
	virtual void Initialize(Framework::IUIObject *pTargetControl);

	void Click();

protected:
	Framework::ILayoutCtrl *m_pLayoutCtrl;

protected:
	Geodatabase::IRasterDatasetPtr CreatePrintImg(CString csPrintImgPath, Geodatabase::RasFileInfo rasInfo);

	void PrintToImg(CString csPrintImgPath, double dpi);
};

}


#endif