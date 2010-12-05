//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/18
// ������  ע����Ⱦ
//////////////////////////////////////////////////////////////////////

#ifndef _LABEL_RENDER_H
#define _LABEL_RENDER_H

#include "TextSymbol.h"

namespace Display{
	class ISymbol;
}

namespace Carto
{

class CARTO_DLL CLabelRender : public SYSTEM::ISerialization
{
public:
	CLabelRender();
	virtual ~CLabelRender();

	virtual void serialization(SYSTEM::IArchive &ar);

public:
	//��עSymbol����
	void SetSymbol( Display::CTextSymbolPtr pSymbol );
	Display::CTextSymbolPtr GetSymbol( void );
	
	//��ע�ֶ����� 
	std::string GetRendFieldstr( void );
	void SetRendFieldstr( std::string strRenderField );
	
	//��ע�������� 
	BOOL GetIsZoom( void );
	void SetIsZoom( BOOL bIsZoom);

	//����
	void Draw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor );
	
	//������ֵ���߿�
	DIS_RECT GetTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text, GEOMETRY::geom::Envelope env);

	
	std::string CLabelRender::GetRendFieldsStr();

protected:
	//����
	Display::CTextSymbolPtr m_pSymbol;

	//�ֶ�
	std::string m_strRenderField;

	//�Ƿ�����
	BOOL m_bIsZoom;
};

typedef SYSTEM::CSmartPtr<CLabelRender> CLabelRenderPtr;

}

#endif