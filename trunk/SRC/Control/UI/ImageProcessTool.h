#ifndef _IMG_PROCESSTOOL_
#define _IMG_PROCESSTOOL_

#include "MapControl.h"

namespace Control
{
class CONTROL_DLL CImageProcessTool
{
public:
	//�仯��ⴰ��
	static void ShowImgChangeDetectDlg();

	//ˮ����ȡ����
	static void ShowDistillWaterSheet(Control::CMapControl* mapControl);
};

}
#endif