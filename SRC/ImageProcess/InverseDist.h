#pragma once
#include <vector>
#include <string>

namespace ImageProcess
{

/************************************************************************/
/*  �������ֵ                                                                     */
/************************************************************************/
class CInverseDist
{

public:
	static bool Run(std::vector<double> dxs,std::vector<double> dys,std::vector<double> dzs,
		double xres,double yres,double radius,const char *strout);


};

}

