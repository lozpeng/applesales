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
	//�仯��ⴰ��
	static void ShowImgChangeDetectDlg();

	static void ShowChangeSymbolDlg();

	static void ShowFuzzyKMeanDlg();

	static void ShowClassVectorDlg();

	static void InitSymbol();

	//ˮ����ȡ����
	static void ShowDistillWaterSheet(Control::CMapControl* mapControl, CWnd* pParen = NULL);

	//�ͷ�������������ڴ�
	static void ReleaseSheets();

	//���������
	static void ModifyImgClasses();
private:
	static std::vector<TreePropSheet::CTreePropSheetEx*> m_manageSheet;
	static std::vector<CResizablePage*>  m_manageSheetPage;
public:
	//�仯����ı�ʶ����
	static Display::IFillSymbolPtr m_pChangeSymbol;
};

}
#endif