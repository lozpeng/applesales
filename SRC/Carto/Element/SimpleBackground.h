//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/15
// ������  ��ͼҪ�ء���������
//////////////////////////////////////////////////////////////////////

#ifndef CSIMPLE_BACKGROUND_H
#define CSIMPLE_BACKGROUND_H
#include "IBackground.h"
#include "IFillSymbol.h"


namespace Element{

class CARTO_DLL CSimpleBackground :
	public IBackground
{
public:
	CSimpleBackground(void);
	~CSimpleBackground(void);
	CSimpleBackground(const GEOMETRY::geom::Geometry& geometry);

	void serialization(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<CSimpleBackground> Clone();

	void Draw(Display::IDisplayPtr pDisplay);
	void SetSymbol(Display::IFillSymbolPtr pFillSymbol);
	Display::IFillSymbolPtr GetSymbol();

protected:
	void InitFillSymbol();


protected:
	Display::IFillSymbolPtr m_pFillSymbol;

};

typedef SYSTEM::CSmartPtr<CSimpleBackground> CSimpleBackgroundPtr;
}
#endif