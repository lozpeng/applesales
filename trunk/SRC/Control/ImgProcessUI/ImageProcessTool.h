#ifndef _IMG_PROCESSTOOL_
#define _IMG_PROCESSTOOL_

#include "MapControl.h"
#include <vector>
namespace TreePropSheet
{
	class CTreePropSheetEx;
}
class CResizablePage;
namespace Control
{
class CONTROL_DLL CImageProcessTool
{
public:
	//变化检测窗口
	static void ShowImgChangeDetectDlg();

	static void ShowChangeSymbolDlg();

	static void ShowFuzzyKMeanDlg();

	static void ShowClassVectorDlg();

	static void InitSymbol();

	//水体提取流程
	static void ShowDistillWaterSheet(Control::CMapControl* mapControl, CWnd* pParen = NULL);

	//释放流程向导申请的内存
	static void ReleaseSheets();

	//分类结果编号
	static void ModifyImgClasses();
private:
	static std::vector<TreePropSheet::CTreePropSheetEx*> m_manageSheet;
	static std::vector<CResizablePage*>  m_manageSheetPage;
public:
	//变化结果的标识符号
	static Display::IFillSymbolPtr m_pChangeSymbol;
};

}
#endif