//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2008/11/26
  // ������  ���߷�����
//////////////////////////////////////////////////////////////////////
#ifndef _CSIMPLELINESYMBOL_H
#define _CSIMPLELINESYMBOL_H

#include "ILineSymbol.h"
#include "DisplayCache.h"

namespace Display{

class DISPLAY_DLL CSimpleLineSymbol : public ILineSymbol
{
public:
	CSimpleLineSymbol();

	CSimpleLineSymbol(const CSimpleLineSymbol& SimpleLineSymbol);

	CSimpleLineSymbol& operator = (const CSimpleLineSymbol& SimpleLineSymbol);

	virtual ~CSimpleLineSymbol();

	// ��������   : SetProperties( const char* PropertyName , const _variant_t& PropertyValue )
	// ����       : ��������
	// ��������   : virtual void 
	// ����       : const char* PropertyName   ��������
	// ����       : const _variant_t& PropertyValue   ����ֵ
	virtual void SetProperties( const char* PropertyName , const _variant_t& PropertyValue);

	// ��������   : GetProperties(const char* PropertyName)
	// ����       : �õ�����
	// ��������   : virtual _variant_t 
	// ����       : const char* PropertyName   ��������
	virtual _variant_t GetProperties(const char* PropertyName);			//�õ���ǰ���ŵ��������÷�������.���û�д����Է���0.


	/////����ʵ������ʵ�ַ���

	// ��������   : Draw(void* pObject)
	// ����       : ����
	// ��������   : virtual void 
	// ����       : void* pObject   ���Ŷ���
	virtual void Draw(void* pObject);				//ʵ�ֻ���

	// ��������   : GetType()
	// ����       : ���������
	// ��������   : virtual SYMBOL_TYPE 
	virtual SYMBOL_TYPE GetType();					//�õ�������

	// ��������   : Zoom(float rate)
	// ����       : ���ݱ������з�������
	// ��������   : virtual void 
	// ����       : float rate
	virtual void Zoom(float rate);

	//�����������ɼ̳и����࣬�ɱ����า��

	// ��������   : GetLineStyle()
	// ����       : �õ�����ʽ
	// ��������   : SIMLINESTYLE 
	SIMLINE_STYLE GetLineStyle();					//�õ�����ʽ

	// ��������   : SetLineStyle(SIMLINESTYLE nStyle)
	// ����       : ��������ʽ
	// ��������   : void 
	// ����       : SIMLINESTYLE nStyle
	void SetLineStyle(SIMLINE_STYLE nStyle);

	// ��������   : SelectDC(CDC * pDC)
	// ����       : װ�仭��,ͨ��������ʼ������
	// ��������   : virtual void 
	// ����       : CDC * pDC
	virtual void SelectDC(CDC * pDC);

	// ��������   : SetReadyDraw()
	// ����       : ��selectDC��������Ļ��ƾ��װ�뵱ǰ��������ɻ���ǰ��׼������
	// ��������   : virtual void 
    virtual void SetReadyDraw();

	// ��������   : ClearDC()
	// ����       : �������
	// ��������   : virtual void 
	virtual void ClearDC();

protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();

private://�������������
	SIMLINE_STYLE m_enumLineType;					//����ʽö��

	DISPLAY_HANDLE_NODE* m_hPenHandle;							//�ʶ��󻺴�

public:

	// ��������   : serialization(otSystem::IArchive &ar)
	// ����       : ���л�����
	// ��������   : virtual void 
	// ����       : otSystem::IArchive &ar   �����ļ���
    virtual void serialization(SYSTEM::IArchive & ar);
};

typedef SYSTEM::CSmartPtr<CSimpleLineSymbol> CSimpleLineSymbolPtr;
}

#endif //CSIMPLELINESYMBOL_H
