#pragma once

#include "CDC.h"
#include "IMarkerSymbol.h"
#include "IArchive.h"
#include "DisplayCache.h"

namespace Display{

class DISPLAY_DLL CArrowMarkerSymbol : public IMarkerSymbol
{
public:
	CArrowMarkerSymbol();

	CArrowMarkerSymbol(const CArrowMarkerSymbol& toArrowMarkerSymbol);

	CArrowMarkerSymbol& operator = (const CArrowMarkerSymbol& toArrowMarkerSymbol);

	virtual~CArrowMarkerSymbol();

	virtual void ClearDC();

	virtual void SetProperties(const char* PropertyName , const _variant_t& PropertyValue);

	virtual _variant_t GetProperties(const char* PropertyName);			//�õ���ǰ���ŵ��������÷�������.���û�д����Է���0.


	/////����ʵ����ʵ��
	virtual void Draw(void* pObject);		//ʵ�ֻ���

	virtual SYMBOL_TYPE GetType();			//�õ�������

	virtual void Zoom(float rate);

	//�����������ɼ̳и����࣬�ɱ����า��
	void SetRate(float fRate);		//���÷��ź��򳤶�

	float GetRate();				//�õ����ź��򳤶�	

    virtual void SelectDC(Display::CDC * pDC);

    virtual void SetReadyDraw();

    virtual void serialization(SYSTEM::IArchive & ar);			
protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();
private://�������������
	float m_fRate;							//���泤�����

	unsigned long m_lWidth;					//���,�ڲ�����


	DISPLAY_HANDLE_NODE* m_hPenHandle;	
	DISPLAY_HANDLE_NODE* m_hBrushHandle;

	unsigned long m_lInsideReviseX;			//�ڲ�x����У��,ʹ����Ļ��Ƶ�Ϊ���ŵ����ĵ�
	
	long DIS_POINTs[6];						//�����ͷ��3������
};

typedef SYSTEM::CSmartPtr<CArrowMarkerSymbol> CArrowMarkerSymbolPtr;

}

