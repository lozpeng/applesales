//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2008/11/26
  // ������  �򵥵������

// �򵥵����
//		�� ���Ի��ƿ�������ɫ���������״
//			1Ϊ�����Σ�
//			2ΪԲ�Σ�
//			3Ϊʮ���Σ�
//			4Ϊx�Σ�
//			5Ϊ���Σ�
//			6Ϊ�Զ��壬��Ҫ���û��ƺ���
//////////////////////////////////////////////////////////////////////

#ifndef _CSIMPLEMARKERSYMBOL_H
#define _CSIMPLEMARKERSYMBOL_H

#include "DisplayCache.h"


#include "IMarkerSymbol.h"
#include "CDC.h"
#include "IArchive.h"

namespace Display{

	typedef void ( __stdcall *DRAWSTYLE_FUNC )( Display::CDC* , const DIS_POINT* , unsigned long , long , long );

class DISPLAY_DLL CSimpleMarkerSymbol : public IMarkerSymbol
{
public:
	CSimpleMarkerSymbol();

	CSimpleMarkerSymbol( const CSimpleMarkerSymbol& SimpleMarkSymbol );

	CSimpleMarkerSymbol& operator = ( const CSimpleMarkerSymbol& SimpleMarkSymbol );

	virtual ~CSimpleMarkerSymbol();

	// ��������   : SetProperties( const char* PropertyName , const _variant_t& PropertyValue )
	// ����       : ��������
	// ��������   : virtual void 
	// ����       : const char* PropertyName   ��������
	// ����       : const _variant_t& PropertyValue   ����ֵ
	virtual void SetProperties( const char* PropertyName , const _variant_t& PropertyValue );

	// ��������   : GetProperties(const char* PropertyName)
	// ����       : �õ�����
	// ��������   : virtual _variant_t 
	// ����       : const char* PropertyName   ��������
	virtual _variant_t GetProperties( const char* PropertyName );

	// ��������   : Draw(void* pObject)
	// ����       : ����
	// ��������   : virtual void 
	// ����       : void* pObject   ���Ŷ���
	virtual void Draw( void* pObject );

	// ��������   : GetType()
	// ����       : �õ��������ͣ����ؼ򵥵���ţ�������ʹ��
	// ��������   : virtual SYMBOL_TYPE    �������� 
	virtual SYMBOL_TYPE GetType();

	// ��������   : Zoom(float rate)
	// ����       : ���ݱ������з�������
	// ��������   : virtual void 
	// ����       : float rate
	virtual void Zoom( float rate );

	/*
		������Ҫ��ʾ�ķ��ţ��������֣�
			1Ϊ�����Σ�
			2ΪԲ�Σ�
			3Ϊʮ���Σ�
			4Ϊx�Σ�
			5Ϊ���Σ�
			6Ϊ�Զ��壬��Ҫ���û��ƺ���
			Ĭ��Ϊ0������
	*/

	// ��������   : SetMarkerType( SIMPLE_MARKER_STYLE enumType , DRAWSTYLE_FUNC Func = NULL)
	// ����       : ������Ҫ��ʾ�ķ���
	// ��������   : void 
	// ����       : SIMPLE_MARKER_STYLE enumType   ö�ٵ��������
	// ����       : DRAWSTYLE_FUNC Func = NULL
	void SetMarkerType( SIMPLE_MARKER_STYLE enumType , DRAWSTYLE_FUNC Func = NULL);		
			
	// ��������   : GetMarkerType()
	// ����       : �õ�����
	// ��������   : SIMPLE_MARKER_STYLE 
	SIMPLE_MARKER_STYLE GetMarkerType();									//�õ�����

	// ��������   : SetOutLineWidth( unsigned long width )
	// ����       : ���ñ߽��ߵĿ��
	// ��������   : void 
	// ����       : unsigned long width
	void SetOutLineWidth( float width );					//����OutLine�Ŀ��

	// ��������   : GetOutLineWidth
	// ����       : ��ñ߽��ߵĿ��
	// ��������   : unsigned long 
	float GetOutLineWidth();								//�õ�OutLine�Ŀ��

	// ��������   : SetOutLineColor( unsigned long lColor )
	// ����       : ���ñ߽��ߵ���ɫ
	// ��������   : void 
	// ����       : unsigned long lColor
	void SetOutLineColor( unsigned long lColor );					//���������ߵ���ɫ

	// ��������   : GetOutLineColor()
	// ����       : �õ��߽��ߵ���ɫ
	// ��������   : unsigned long 
	unsigned long GetOutLineColor();								//�õ������ߵ���ɫ

	// ��������   : SetOutLineFlag( bool bOutLine )
	// ����       : �����Ƿ���Ʊ߽���
	// ��������   : void 
	// ����       : bool bOutLine   �ж��Ƿ���Ʊ߽���
	void SetOutLineFlag( bool bOutLine );							//�����Ƿ����������

	// ��������   : GetOutLineFlag()
	// ����       : �õ��Ƿ���Ʊ߽�������
	// ��������   : bool 
	bool GetOutLineFlag();											//�õ��Ƿ��������������
	
	// ��������   : SetCustomDrawFunction()
	// ����       : �����Զ��庯��
	// ��������   : void 
	void SetCustomDrawFunction();								    // �����Զ��庯��
public:

	// ��������   : SelectDC(Display::CDC *pDC)
	// ����       : װ�仭��,ͨ��������ʼ������
	// ��������   : virtual void 
	// ����       : Display::CDC *pDC
    virtual void SelectDC( CDC * pDC );

	// ��������   : SetReadyDraw()
	// ����       : ��selectDC��������Ļ��ƾ��װ�뵱ǰ��������ɻ���ǰ��׼������
	// ��������   : virtual void 
	virtual void SetReadyDraw();

	// ��������   : ClearDC
	// ����       : �������
	// ��������   : virtual void 
	virtual void ClearDC();

	// ��������   : serialization(otSystem::IArchive &ar)
	// ����       : ���л�����
	// ��������   : virtual void 
	// ����       : otSystem::IArchive &ar   �����ļ���
    virtual void serialization( SYSTEM::IArchive & ar );
protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();
private:

	unsigned long m_lOutLineWidth;									//outline�Ŀ��
	float m_fOutLineWidth;

	SIMPLE_MARKER_STYLE m_enumMarkType;									//�򵥷�������

	unsigned long m_lOutLineColor;									//����ŵı߿�����ɫ

	bool m_bOutLine;												//�Ƿ���Ʊ߿���


	///////////////////////

	DISPLAY_HANDLE_NODE* m_hPenHandle;								//�洢�ʻ���

	DISPLAY_HANDLE_NODE* m_hBrushHandle;							//�洢ˢ�ӻ���

	//////////////////////

	DRAWSTYLE_FUNC m_StyleFunc;
};

typedef SYSTEM::CSmartPtr<CSimpleMarkerSymbol> CSimpleMarkerSymbolPtr;
}
#endif //CSIMPLEMARKSYMBOL_H
