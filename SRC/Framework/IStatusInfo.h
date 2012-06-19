#ifndef _ISTATUSINFO_H_
#define _ISTATUSINFO_H_

#include <string>

namespace Framework
{
class  IStatusInfo
{
public:
	IStatusInfo(){}
	virtual ~IStatusInfo(){}

public:
	virtual void UpdateInfo(std::string info);

	

};
}
#endif