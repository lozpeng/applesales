#ifndef CEXCHANGEINFO_H
#define CEXCHANGEINFO_H

#include "SystemDefine.h"
#include "alm.h"
namespace Display
{
/** 
 * 记录索引集
 */
class DISPLAY_DLL CPropRecordIndexGroup{
	public:
	CPropRecordIndexGroup(void);
	~CPropRecordIndexGroup(void);

	   /**
	    * 添加记录索引
		* @param value 索引值
		*/
		void AddRecordIndex(unsigned int value);

	   /**
		* 删除记录索引值
		* @param index 索引
		*/
		void RemoveValueByIndex(unsigned int index);

	   /**
		* 在指定索引位置插入记录索引值
		* @param value 索引值
		* @param index 索引
		*/
		void InsertRecordIndex(unsigned int value , unsigned int index);

	   /**
		* 清空索引集
		* @return 
		*/
		void Clear();

	   /**
		* 通过索引获得索引值
		* @param index 索引
		*/
		const unsigned int& GetRecordIndexByIndex(unsigned int index);

	   /**
		* 获得索引个数
		* @return 返回索引个数
		*/
		int GetRecordIndexSize();
	private:
		SYSTEM::CArray<unsigned int> m_hotRecordIndex;
};
}

#endif