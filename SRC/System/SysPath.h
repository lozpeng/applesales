#ifndef _SYSTEM_SYSPATH_H
#define _SYSTEM_SYSPATH_H

#include <string>

namespace SYSTEM{

class SYSTEM_DLL CSystemPath 
{
public:

	// ��������   : GetSystemPath()
	// ����       : ���ģ�����ڵľ���·��
	// ��������   : static std::string   ģ�����ڵľ���·��
	static std::string GetSystemPath();
};

}

#endif
