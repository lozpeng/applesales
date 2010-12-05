//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/11/18
// 描述：  注记渲染
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
	//标注Symbol属性
	void SetSymbol( Display::CTextSymbolPtr pSymbol );
	Display::CTextSymbolPtr GetSymbol( void );
	
	//标注字段属性 
	std::string GetRendFieldstr( void );
	void SetRendFieldstr( std::string strRenderField );
	
	//标注缩放属性 
	BOOL GetIsZoom( void );
	void SetIsZoom( BOOL bIsZoom);

	//绘制
	void Draw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor );
	
	//获得文字的外边框
	DIS_RECT GetTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text, GEOMETRY::geom::Envelope env);

	
	std::string CLabelRender::GetRendFieldsStr();

protected:
	//符号
	Display::CTextSymbolPtr m_pSymbol;

	//字段
	std::string m_strRenderField;

	//是否缩放
	BOOL m_bIsZoom;
};

typedef SYSTEM::CSmartPtr<CLabelRender> CLabelRenderPtr;

}

#endif