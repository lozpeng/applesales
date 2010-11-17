#ifndef ISERIALIZATION_H
#define ISERIALIZATION_H

#include "IArchive.h"

namespace SYSTEM{
/**
*类功能概述：对档案文件流进行序列化操作
*/
class SYSTEM_DLL ISerialization 
{
public:

   /**
    * 功能描述：对档案文件流进行序列化操作
	* @param SYSTEM::IArchive &ar 档案文件流
	* @return void
	*/
	virtual void serialization(SYSTEM::IArchive &ar);
};

}

#endif //ISERIALIZATION_H
