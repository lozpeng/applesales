#ifndef ISERIALIZATION_H
#define ISERIALIZATION_H

#include "IArchive.h"

namespace SYSTEM{
/**
*�๦�ܸ������Ե����ļ����������л�����
*/
class SYSTEM_DLL ISerialization 
{
public:

   /**
    * �����������Ե����ļ����������л�����
	* @param SYSTEM::IArchive &ar �����ļ���
	* @return void
	*/
	virtual void serialization(SYSTEM::IArchive &ar);
};

}

#endif //ISERIALIZATION_H
