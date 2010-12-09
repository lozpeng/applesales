#ifndef IGRAPHIC_ELEMENT_H
#define IGRAPHIC_ELEMENT_H
#include "IElement.h"
namespace Element{

class CARTO_DLL IGraphicElement :public IElement
{
public:
	IGraphicElement(void);
	IGraphicElement(const GEOMETRY::geom::Geometry& geometry);
	virtual ~IGraphicElement(void);

	/**
	* 功能描述：绘制草稿（用于修改大小时等的简单绘制）
	* @param Display::IDisplayPtr pDisplay 智能指针IDisplay
	* @param bool bPrint 是否打印
	* @return void
	*/
	void DrawDraftMode( Display::IDisplayPtr pDisplay , bool bPrint);
};

}

#endif;
