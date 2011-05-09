#ifndef _SYSTEM_SYSPATH_H
#define _SYSTEM_SYSPATH_H

#include <string>

namespace SYSTEM{

class SYSTEM_DLL CSystemPath 
{
public:

	// 函数名称   : GetSystemPath()
	// 描述       : 获得模块所在的绝对路径
	// 返回类型   : static std::string   模块所在的绝对路径
	static std::string GetSystemPath();
};

}

#endif
