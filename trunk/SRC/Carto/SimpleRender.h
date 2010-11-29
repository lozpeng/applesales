//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/18
// ������  ʸ�����ݼ���Ⱦ
//////////////////////////////////////////////////////////////////////

#ifndef _Simple_Render_h
#define _Simple_Render_h


namespace Display{
	class ISymbol;
}

namespace Carto
{

class CARTO_DLL CSimpleRender : public IRender
{
public:
	CSimpleRender();
	virtual ~CSimpleRender();

public:

	virtual void SetSymbol(Display::ISymbolPtr pSymbol);

	virtual void Draw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor);

	virtual void HighLightDraw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor );

	virtual void HighLightDraw(Display::IDisplayPtr pDisplay,  Geodatabase::ISelctionSet* pSelections);

	virtual std::string GetRendFieldsStr();

	Display::ISymbolPtr GetSymbol();

	virtual void serialization(SYSTEM::IArchive &ar);

	virtual CLegendInfoPtr GetLegendInfo();

protected:
	Display::ISymbolPtr m_pSymbol;

};

typedef SYSTEM::CSmartPtr<CSimpleRender> CSimpleRenderPtr;

}

#endif