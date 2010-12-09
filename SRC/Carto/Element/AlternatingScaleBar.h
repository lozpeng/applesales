#ifndef IALTERNATING_SCALE_BAR_H
#define IALTERNATING_SCALE_BAR_H
#include "IScaleBar.h"
namespace Element{

class CARTO_DLL CAlternatingScaleBar :public IScaleBar
{
public:
	CAlternatingScaleBar();
	CAlternatingScaleBar(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);
	~CAlternatingScaleBar(void);

	virtual void serialization(SYSTEM::IArchive &ar);   

//	IElementPtr Clone();

protected:

	void DrawNormal(Display::IDisplayPtr pDisplay);

	void DrawBar(Display::IDisplayPtr pDisplay, DIS_RECT rect);



	/**
	* 功能描述:克隆函数
	* @return _ptr_t<IElement> Element智能指针
	*/
	//IElementPtr Clone();

};

typedef SYSTEM::CSmartPtr<CAlternatingScaleBar> CAlternatingScaleBarPtr;
}
#endif
