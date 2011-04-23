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

	void SetDashGroupCount(unsigned long lCount);					//�������ۺ�����Ҫʹ�õĸ���

	unsigned long GetDashGroupCount();								//�õ����õ�Ҫʹ�õ��������

	void AddDash(float lData);								//������ۺ�����

	float GetDash(unsigned long lIndex);					//���������ŵõ�������ĳ��ֵ

	void RemoveDash(unsigned long lIndex);							//�Ƴ������е�ĳ��ֵ
	 
	int GetDashSize();												//�õ�ʵ����װ����������

	unsigned long* GetData();										//�õ��������ݵ��׵�ַ

	void SetDash(float lData,unsigned long lIndex);			//����ָ��λ�õ�����Ԫ�ص�ֵ
private:
	std::vector<float>	m_dashArray;					//��ʼһ�����飬���ڴ������ۺ���ʽ
	std::vector<unsigned long> m_lDashArray;
	unsigned long m_lCount;
	SYSTEM::SYS_UNIT_TYPE m_enumUnit;
	ISymbolPtr m_pSymbol;
public:

    virtual void serialization(SYSTEM::IArchive &ar);
};

}
