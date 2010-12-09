//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/15
// ������  ��ͼҪ�ء����߿�
//////////////////////////////////////////////////////////////////////

#ifndef CSIMPLE_BORDER_H
#define CSIMPLE_BORDER_H
#include "IBorder.h"
#include "SimpleFillSymbol.h"


namespace Element{

class CARTO_DLL CSimpleBorder :
	public IBorder
{
public:
	CSimpleBorder(void);
	//���캯�� pGeometry��״���ڲ��ͷ�
	CSimpleBorder(const GEOMETRY::geom::Geometry& geometry);
	~CSimpleBorder(void);

	void serialization(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<CSimpleBorder> Clone();

	void SetSymbol(Display::ILineSymbolPtr pLineSymbol);
	Display::ILineSymbolPtr GetSymbol();

	void Draw(Display::IDisplayPtr pDisplay);

protected:
	void InitFillSymbol();

protected:
	Display::CSimpleFillSymbolPtr m_pFillSymbol;

};

typedef SYSTEM::CSmartPtr<CSimpleBorder> CSimpleBorderPtr;
}
#endif
