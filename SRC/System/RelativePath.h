#ifndef _SYSTEM_RELATIVE_PATH_H_
#define _SYSTEM_RELATIVE_PATH_H_

#include <string>

namespace SYSTEM
{

class SYSTEM_DLL CRelativePath
{
public:
	
	//设置基础路径
	static void SetBasePath(const char* strPath);

	//判断路径是否是相对路径
	static bool IsRelativePath(const char* path);

	//计算相对路径
	static std::string RelativePath(const char* destpath);

	//根据基础路径和相对路径计算绝对路径
	static std::string FullPath(const char* relpath);

private:
	//基础路径，不带文件名，计算的相对路径都是以这个路径为参考，
	static std::string BasePath; 
};

}
#endif