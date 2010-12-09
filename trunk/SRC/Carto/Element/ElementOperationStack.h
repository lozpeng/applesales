#ifndef CELEMENT_OPERATION_STACK_H
#define CELEMENT_OPERATION_STACK_H

#include "ElementOperation.h"
#include "GraphicLayer.h"

namespace Element{


class CARTO_DLL CElementOperationStack
{
public:
	CElementOperationStack();
	CElementOperationStack(Carto::CGraphicLayerPtr pLayer);
	~CElementOperationStack(void);

	void Redo();

	void Undo();

	BOOL CanUndo();

	BOOL CanRedo();

	void AddOperation(OP_TYPE opType, CElementCollection elements);

	void AddOperation(OP_TYPE opType, IElementPtr element);

	void RemoveLastOperation();

	void ClearOperation();

	void SetLayer(Carto::CGraphicLayerPtr pLayer);

public:

	long	m_nMaxRecord;

	std::vector<CElementOperationPtr> m_OperationStack;

	std::vector<CElementOperationPtr>::iterator	m_iterCurPos;

	Carto::CGraphicLayerPtr m_pLayer;

};

typedef SYSTEM::CSmartPtr<CElementOperationStack> CElementOperationStackPtr;
}
#endif
