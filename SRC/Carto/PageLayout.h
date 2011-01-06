//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/11/18
// 描述：  制图对象
//////////////////////////////////////////////////////////////////////

#ifndef _PAGE_LAYOUT_H
#define _PAGE_LAYOUT_H
#include "IDisplay.h"
#include "GraphicLayer.h"
#include "IElement.h"
#include "Page.h"
//#include "ElementOperationStack.h"

namespace Carto
{

/*
* CGeoLayout是制图对象
*/
class CARTO_DLL CPageLayout : public SYSTEM::ISerialization 
{
public:
	CPageLayout(void);
	~CPageLayout(void);

	virtual void serialization(SYSTEM::IArchive& ar);

	void Initialize(long memDC, long lDCSizeX, long lDCSizeY);

	BOOL Initialized(){return m_bInitialized;};

	/**
	* 获取Display
	* @return IDisplay指针
	*/
	Display::IDisplayPtr GetDisplay();

	//获取页面
	Element::CPagePtr GetPage();

	/**
	* 设置Display
	* @param pNewDisplay Display指针
	*/
	Display::IDisplayPtr SetDisplay(Display::IDisplayPtr pNewDisplay);

	/**
	* 绘制后
	*/
	void OnAfterDraw();

	/**
	* 绘制前
	*/
	void OnBeforeDraw();
	/**
	* 绘制
	*/
	virtual void Draw(long content);

	void PrintToImg();

	virtual CGraphicLayerPtr GetGraphicLayer();

	Element::CGraphicsContainerSelect& GetGraphicsContainerSelect();

	virtual const GEOMETRY::geom::Envelope& GetExtent(){return m_Page->GetPageMarginEnvelope();};

	//Element::CElementOperationStackPtr GetElementOperationStack(){return m_pElementOperStack;};


protected:
	Element::CPagePtr	m_Page;

	//element图层
	CGraphicLayerPtr	m_pGraphicLayer;

	//Display device
	Display::IDisplayPtr m_pDisplay;

	BOOL m_bInitialized;

	//Element::CElementOperationStackPtr m_pElementOperStack;	//图元操作回退栈

};

typedef SYSTEM::CSmartPtr<CPageLayout> CPageLayoutPtr;
}
#endif

