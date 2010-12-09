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
	* �������������Ʋݸ壨�����޸Ĵ�Сʱ�ȵļ򵥻��ƣ�
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @param bool bPrint �Ƿ��ӡ
	* @return void
	*/
	void DrawDraftMode( Display::IDisplayPtr pDisplay , bool bPrint);
};

}

#endif;
