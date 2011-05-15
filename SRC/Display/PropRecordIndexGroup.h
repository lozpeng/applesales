#ifndef CEXCHANGEINFO_H
#define CEXCHANGEINFO_H

#include "SystemDefine.h"
#include "alm.h"
namespace Display
{
/** 
 * ��¼������
 */
class DISPLAY_DLL CPropRecordIndexGroup{
	public:
	CPropRecordIndexGroup(void);
	~CPropRecordIndexGroup(void);

	   /**
	    * ��Ӽ�¼����
		* @param value ����ֵ
		*/
		void AddRecordIndex(unsigned int value);

	   /**
		* ɾ����¼����ֵ
		* @param index ����
		*/
		void RemoveValueByIndex(unsigned int index);

	   /**
		* ��ָ������λ�ò����¼����ֵ
		* @param value ����ֵ
		* @param index ����
		*/
		void InsertRecordIndex(unsigned int value , unsigned int index);

	   /**
		* ���������
		* @return 
		*/
		void Clear();

	   /**
		* ͨ�������������ֵ
		* @param index ����
		*/
		const unsigned int& GetRecordIndexByIndex(unsigned int index);

	   /**
		* �����������
		* @return ������������
		*/
		int GetRecordIndexSize();
	private:
		SYSTEM::CArray<unsigned int> m_hotRecordIndex;
};
}

#endif