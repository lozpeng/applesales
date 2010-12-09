#ifndef CELEMENT_OPERATION_H
#define CELEMENT_OPERATION_H

#include "ElementCollection.h"
#include "GraphicLayer.h"


namespace Element{

struct ElementOperInfo
{
	std::pair<Element::IElementPtr, Element::IElementPtr> element;

	unsigned long pos;
};


class CARTO_DLL CElementOperation
{
public:
	CElementOperation(void);
	CElementOperation(Carto::CGraphicLayerPtr pLayer);
	~CElementOperation(void);

	virtual void Redo();

	virtual void Undo();

	virtual BOOL CanRedo();

	virtual BOOL CanUndo();

	virtual void SetCanUndo(BOOL bCanUndo){m_bCanUndo = bCanUndo;};

	virtual BOOL SetOperation(OP_TYPE opType, CElementCollection elements);

	virtual BOOL SetOperation(OP_TYPE opType, IElementPtr element);

	virtual std::string GetMenuString();

protected:

	virtual void SetOperationType(OP_TYPE opType);

protected:

	Carto::CGraphicLayerPtr m_pLayer;

	BOOL		m_bCanUndo;

	OP_TYPE		m_opType;

	std::string m_menuString;

	std::vector<ElementOperInfo> m_ElementsOperInfo;
};

typedef SYSTEM::CSmartPtr<CElementOperation> CElementOperationPtr;

}
#endif
