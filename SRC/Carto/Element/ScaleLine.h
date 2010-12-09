//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  制图要素——线状比例尺
//////////////////////////////////////////////////////////////////////

#ifndef CSCALE_LINE_H
#define CSCALE_LINE_H
#include "IScaleBar.h"
namespace Element{

class CARTO_DLL CScaleLine :public IScaleBar
{
public:
	CScaleLine();
	CScaleLine(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);
	~CScaleLine(void);

	virtual void serialization(SYSTEM::IArchive &ar);   

//	IElementPtr Clone();

protected:

	void ConvertMillimeterToPixel(Display::IDisplayPtr pDisplay);

	void DrawNormal(Display::IDisplayPtr pDisplay);

	void DrawBar(Display::IDisplayPtr pDisplay, DIS_RECT rect);



	/**
	* 功能描述:克隆函数
	* @return _ptr_t<IElement> Element智能指针
	*/
	//IElementPtr Clone();

};

typedef SYSTEM::CSmartPtr<CScaleLine> CScaleLinePtr;
}
#endif
