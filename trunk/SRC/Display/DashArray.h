#pragma once

#include "ISerialization.h"
#include "IArchive.h"
#include "ISymbol.h"
namespace Display{
class DISPLAY_DLL CDashArray : public SYSTEM::ISerialization
{
public:
	CDashArray(Display::ISymbolPtr symbol);
	CDashArray();
public:
	virtual ~CDashArray();

	CDashArray(const CDashArray& toDashArray);

	//CDashArray& operator = (const CDashArray& toDashArray);

	SYSTEM::SYS_UNIT_TYPE GetUnit();

	void SetDashGroupCount(unsigned long lCount);					//设置破折号数组要使用的个数

	unsigned long GetDashGroupCount();								//得到设置的要使用的数组个数

	void AddDash(float lData);								//添加破折号数组

	float GetDash(unsigned long lIndex);					//根据索引号得到数组中某个值

	void RemoveDash(unsigned long lIndex);							//移除数组中的某个值
	 
	int GetDashSize();												//得到实际上装入的数组个数

	unsigned long* GetData();										//得到数组数据的首地址

	void SetDash(float lData,unsigned long lIndex);			//设置指定位置的数组元素的值
private:
	std::vector<float>	m_dashArray;					//初始一个数组，用于储存破折号样式
	std::vector<unsigned long> m_lDashArray;
	unsigned long m_lCount;
	SYSTEM::SYS_UNIT_TYPE m_enumUnit;
	ISymbolPtr m_pSymbol;
public:

    virtual void serialization(SYSTEM::IArchive &ar);
};

}
