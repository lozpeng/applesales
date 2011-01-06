//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/18
// ������  ��ͼ����
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
* CGeoLayout����ͼ����
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
	* ��ȡDisplay
	* @return IDisplayָ��
	*/
	Display::IDisplayPtr GetDisplay();

	//��ȡҳ��
	Element::CPagePtr GetPage();

	/**
	* ����Display
	* @param pNewDisplay Displayָ��
	*/
	Display::IDisplayPtr SetDisplay(Display::IDisplayPtr pNewDisplay);

	/**
	* ���ƺ�
	*/
	void OnAfterDraw();

	/**
	* ����ǰ
	*/
	void OnBeforeDraw();
	/**
	* ����
	*/
	virtual void Draw(long content);

	void PrintToImg();

	virtual CGraphicLayerPtr GetGraphicLayer();

	Element::CGraphicsContainerSelect& GetGraphicsContainerSelect();

	virtual const GEOMETRY::geom::Envelope& GetExtent(){return m_Page->GetPageMarginEnvelope();};

	//Element::CElementOperationStackPtr GetElementOperationStack(){return m_pElementOperStack;};


protected:
	Element::CPagePtr	m_Page;

	//elementͼ��
	CGraphicLayerPtr	m_pGraphicLayer;

	//Display device
	Display::IDisplayPtr m_pDisplay;

	BOOL m_bInitialized;

	//Element::CElementOperationStackPtr m_pElementOperStack;	//ͼԪ��������ջ

};

typedef SYSTEM::CSmartPtr<CPageLayout> CPageLayoutPtr;
}
#endif

