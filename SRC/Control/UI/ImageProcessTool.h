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

	//ˮ����ȡ����
	static void ShowDistillWaterSheet(Control::CMapControl* mapControl, CWnd* pParen = NULL);

	//�ͷ�������������ڴ�
	static void ReleaseSheets();
private:
	static std::vector<TreePropSheet::CTreePropSheetEx*> m_manageSheet;
	static std::vector<CResizablePage*>  m_manageSheetPage;
};

}
#endif