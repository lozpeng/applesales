//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/23
// 描述：  标绘对象选择集
//////////////////////////////////////////////////////////////////////

#ifndef CGRAPHICS_CONTAINER_SELECT_H
#define CGRAPHICS_CONTAINER_SELECT_H
#include "IElement.h"
#include "ElementCollection.h"

namespace Element{

class CARTO_DLL CGraphicsContainerSelect
{
public:
	CGraphicsContainerSelect(void);
	~CGraphicsContainerSelect(void);

	//添加一个Element
	void SelectElement(IElementPtr pElement);
	//添加多个Element
	void SelectElements(CElementCollection elements);
	//
//	virtual void SelectAllElements()=0;
	//
	IElementPtr GetSelectedElement(const long lIndex);
	//
	CElementCollection& GetSelectedElements();
	//
	long GetSelectedElementCount();
	//
	void UnselectAllElements();
	//
	void UnselectElement(IElementPtr pElement);
	//
	void UnselectElements(CElementCollection elements);

	//
	DIS_RECT* SelectionBounds(Display::IDisplayPtr pDisplay);
	//
	DIS_RECT* SelectionTracker(Display::IDisplayPtr pDisplay, long lIndex);

	BOOL IsSelectedElementEmpty(){return m_SelElements.Count()==0;};

	BOOL IsElementSelected(IElementPtr pElement);



protected:
	CElementCollection m_SelElements;

};

typedef SYSTEM::CSmartPtr<CGraphicsContainerSelect> CGraphicsContainerSelectPtr;

}
#endif
