#ifndef _IMG_PROCESSTOOL_
#define _IMG_PROCESSTOOL_

namespace Control
{
class CONTROL_DLL CImageProcessTool
{
public:
	//变化检测窗口
	static void ShowImgChangeDetectDlg();

	//水体提取流程
	static void ShowDistillWaterSheet();
};

}
#endif