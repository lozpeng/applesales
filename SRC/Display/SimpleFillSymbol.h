//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2008/11/26
  // ������  ���������
//////////////////////////////////////////////////////////////////////

#ifndef CSIMPLEFILLSYMBOL_H
#define CSIMPLEFILLSYMBOL_H

////////////////////////////////////////////////////////////////////////////////
//
// �������
//		�� ������ɫ�����Ի��Ʊ߽���
//
////////////////////////////////////////////////////////////////////////////////

#include "IFillSymbol.h"
#include "DisplayCache.h"
#include "CDC.h"
#include "IArchive.h"
namespace Display{
	
class DISPLAY_DLL CSimpleFillSymbol : public IFillSymbol 
{
public:
	CSimpleFillSymbol();															//���忽�����캯��

	CSimpleFillSymbol(const CSimpleFillSymbol& toSimpleFillSymbol);

	CSimpleFillSymbol& operator = (const CSimpleFillSymbol& toSimpleFillSymbol);

	~CSimpleFillSymbol();

	// ��������   : Draw(void* pObject)
	// ����       : ʵ�ֻ���
	// ��������   : virtual void 
	// ����       : void* pObject
	 virtual void Draw(void* pObject);				  

	 // ��������   : GetType()
	 // ����       : �õ�������
	 // ��������   : virtual SYMBOL_TYPE 
	 virtual SYMBOL_TYPE GetType();

	 // ��������   : SelectDC(CDC *pDC)
	 // ����       : ���ñʣ�ˢ�������
	 // ��������   : virtual void 
	 // ����       : CDC *pDC   ���ƾ�� 
	 virtual void SelectDC(Display::CDC * pDC);
	
	 // ��������   : SetReadyDraw()
	 // ����       : ��selectDC��������Ļ��ƾ��װ�뵱ǰ��������ɻ���ǰ��׼������
	 // ��������   : virtual void 
	 virtual void SetReadyDraw();

	 // ��������   : ClearDC()
	 // ����       : �������
	 // ��������   : virtual void 
	 virtual void ClearDC();

	 // ��������   : Zoom(float rate)
	 // ����       : ���ݱ������з�������
	 // ��������   : virtual void 
	 // ����       : float rate
	 virtual void Zoom(float rate);
protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();
protected:
	DISPLAY_HANDLE_NODE* m_hBrushHandle;											//ˢ��ID

public:

    virtual void serialization(SYSTEM::IArchive & ar);
};

typedef SYSTEM::CSmartPtr<CSimpleFillSymbol> CSimpleFillSymbolPtr;
}

#endif //CSIMPLEFILLSYMBOL_H
