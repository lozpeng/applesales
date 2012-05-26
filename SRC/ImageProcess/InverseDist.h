#pragma once
#include <vector>
#include <string>
#include "ImageProcessDef.h"
#include "IProgress.h"
namespace ImageProcess
{

/************************************************************************/
/*  �������ֵ                                                                     */
/************************************************************************/
class IMP_DLL CInverseDist
{

public:
	static bool Run(std::vector<double> &dxs,std::vector<double> &dys,std::vector<double> &dzs,
		double xres,double yres,double radius,const char *strout,SYSTEM::IProgress *pProgress,const char*);


};

}

