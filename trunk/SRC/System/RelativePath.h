#ifndef _SYSTEM_RELATIVE_PATH_H_
#define _SYSTEM_RELATIVE_PATH_H_

#include <string>

namespace SYSTEM
{

class SYSTEM_DLL CRelativePath
{
public:
	
	//���û���·��
	static void SetBasePath(const char* strPath);

	//�ж�·���Ƿ������·��
	static bool IsRelativePath(const char* path);

	//�������·��
	static std::string RelativePath(const char* destpath);

	//���ݻ���·�������·���������·��
	static std::string FullPath(const char* relpath);

private:
	//����·���������ļ�������������·�����������·��Ϊ�ο���
	static std::string BasePath; 
};

}
#endif