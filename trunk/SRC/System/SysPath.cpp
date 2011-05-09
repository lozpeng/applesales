#include "stdafx.h"
#include "SysPath.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

extern HMODULE gModule;

std::string SYSTEM::CSystemPath::GetSystemPath()
{
	char filename[513];
	memset(filename,0,513);
	//得到动态库的名字和路径
	GetModuleFileName(gModule,filename,512);

	std::string fullpath =filename;
	fullpath =fullpath.substr(0,fullpath.rfind("\\")+1);

	return fullpath;
}
