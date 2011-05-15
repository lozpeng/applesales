#ifndef CCOMPLEXFILLSYMBOL_H
#define CCOMPLEXFILLSYMBOL_H
#include "IFillSymbol.h"
#include "CDC.h"
#include "IArchive.h"
#include "alm.h"
#include "IComplexSymbol.h"

namespace Display{
class DISPLAY_DLL CComplexFillSymbol : public IFillSymbol , public IComplexSymbol
{
public:
//	using IFillSymbol::AddRef;
//	using IFillSymbol::Release;
	using IFillSymbol::m_lColor;
	using IFillSymbol::m_pDC;


	CComplexFillSymbol();

	CComplexFillSymbol(const CComplexFillSymbol& ComplexFillSymbol);

	//����"="
	CComplexFillSymbol& operator = (const CComplexFillSymbol& ComplexFillSymbol);

	virtual ~CComplexFillSymbol();

	/////����ʵ������ʵ�ַ���
	virtual void Draw(void* pObject);							//ʵ�ֻ���

	virtual SYMBOL_TYPE GetType();								//�õ�������

	void SetOutLineColor(unsigned long lColor);					//�����ߵ���ɫ

	void SetFillColor(unsigned long lColor);					//���������ɫ

	void SetOutLineWidth(unsigned long size);					//�����ߵĿ��

	void SetOutLine(ILineSymbolPtr mOutLine);			    	//������ָ��

	void SetbOutLine(bool bline);								//�����Ƿ������

	virtual void SelectDC(CDC *pDC);							//װ�仭�������󷽷���������ʵ��

	virtual void Zoom(float rate);

	virtual void DrawLegend( DIS_RECT * rect , int nFlag );

	virtual void SetProperties( const char* PropertyName , const _variant_t& PropertyValue);

	virtual _variant_t GetProperties(const char* PropertyName);
	
	//ʵ�ָ����麯��
	virtual bool Add(ISymbolPtr symbol);

	virtual bool Insert( int index , ISymbolPtr symbol , bool state );

	virtual bool SetSymbol( int index , ISymbolPtr symbol );

	virtual void ClearDC();

public:
	  virtual void serialization(SYSTEM::IArchive & ar);
protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();
private:
	
};
typedef SYSTEM::CSmartPtr<CComplexFillSymbol> IComplexFillSymbolPtr;
}
#endif 