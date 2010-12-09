#include "StdAfx.h"
#include "ElementOperation.h"
#include "MapFrame.h"

namespace Element{

CElementOperation::CElementOperation(void)
{
	m_bCanUndo = TRUE;
}

CElementOperation::CElementOperation(Carto::CGraphicLayerPtr pLayer)
{
	m_pLayer = pLayer;

	m_bCanUndo = TRUE;
}

CElementOperation::~CElementOperation(void)
{
}

BOOL CElementOperation::CanRedo()
{
	return !m_bCanUndo;
}

BOOL CElementOperation::CanUndo()
{
	return m_bCanUndo;
}

void CElementOperation::Redo()
{
	m_pLayer->UnselectAllElements();
	switch(m_opType)
	{
	case OPT_GROUP:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{
				CGroupElementPtr pElement = m_ElementsOperInfo[i].element.first;
				int nGroupCount = pElement->Count();
				for(int j=nGroupCount-1; j>=0; j--)
				{
					m_pLayer->RemoveElement(pElement->QueryElement(j));
				}

				m_pLayer->AddElement(pElement);
				m_pLayer->SelectElement(pElement);
			}

		}
		break;
	case OPT_UNGROUP:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{
				CGroupElementPtr pElement = m_ElementsOperInfo[i].element.first;
				int nGroupCount = pElement->Count();
				for(int j=nGroupCount-1; j>=0; j--)
				{
					m_pLayer->SelectElement(pElement->QueryElement(j));
					m_pLayer->AddElement(pElement->QueryElement(j));
				}

				m_pLayer->RemoveElement(pElement);
			}
		}
		break;
	case OPT_ADD:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{
				m_pLayer->AddElement(m_ElementsOperInfo[i].element.first);
				m_pLayer->SelectElement(m_ElementsOperInfo[i].element.first);
			}
		}
		break;
	case OPT_REMOVE:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{
				m_pLayer->RemoveElement(m_ElementsOperInfo[i].element.first);
			}
		}
		break;
	case OPT_EDIT_PROPERTY:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{
				IElementPtr pElement = m_ElementsOperInfo[i].element.first;
				IElementPtr pCopyElement = m_ElementsOperInfo[i].element.second;

				SYSTEM::CBinArchive ar1;
				pElement->serialization( ar1 );

				SYSTEM::CBinArchive ar2;
				pCopyElement->serialization( ar2 );

				ar2.SetReadState();
				ar2.SetPosToBegin();
				pElement->serialization( ar2 );

				ar1.SetReadState();
				ar1.SetPosToBegin();
				pCopyElement->serialization( ar1 );
	
				m_pLayer->SelectElement(pElement);
			}
		}
		break;
	case OPT_MOVE_UP:
		{
			Element::CElementCollection collect;
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
				collect.Add(m_ElementsOperInfo[i].element.first);

			m_pLayer->SendBackward(collect);

			m_pLayer->SelectElements(collect);
		}
		break;
	case OPT_MOVE_DOWN:
		{
			Element::CElementCollection collect;
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
				collect.Add(m_ElementsOperInfo[i].element.first);

			m_pLayer->BringForward(collect);

			m_pLayer->SelectElements(collect);
		}
		break;
	case OPT_MOVE_TOP:
		{
			Element::CElementCollection collect;
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
				collect.Add(m_ElementsOperInfo[i].element.first);

			m_pLayer->SendToBack(collect);

			m_pLayer->SelectElements(collect);
		}
		break;
	case OPT_MOVE_BOTTOM:
		{
			Element::CElementCollection collect;
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
				collect.Add(m_ElementsOperInfo[i].element.first);

			m_pLayer->BringToFront(collect);

			m_pLayer->SelectElements(collect);
		}
		break;
	default:
		break;
	}

	m_bCanUndo = TRUE;
}

void CElementOperation::Undo()
{
	m_pLayer->UnselectAllElements();

	switch(m_opType)
	{
	case OPT_GROUP:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{
				CGroupElementPtr pElement = m_ElementsOperInfo[i].element.first;
				int nGroupCount = pElement->Count();
				for(int j=nGroupCount-1; j>=0; j--)
				{
					m_pLayer->SelectElement(pElement->QueryElement(j));
					m_pLayer->AddElement(pElement->QueryElement(j));
				}

				m_pLayer->RemoveElement(pElement);
			}
		}
		break;
	case OPT_UNGROUP:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{
				CGroupElementPtr pElement = m_ElementsOperInfo[i].element.first;
				int nGroupCount = pElement->Count();
				for(int j=nGroupCount-1; j>=0; j--)
				{
					m_pLayer->RemoveElement(pElement->QueryElement(j));
				}

				m_pLayer->AddElement(pElement);
				m_pLayer->SelectElement(pElement);
			}
		}
		break;
	case OPT_ADD:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{
				IElementPtr pElement = m_ElementsOperInfo[i].element.first;
				
				m_pLayer->RemoveElement(pElement);
			}
		}
		break;
	case OPT_REMOVE:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{

				IElementPtr pElement = m_ElementsOperInfo[i].element.first;
	
				m_pLayer->AddElement(pElement);
	
				m_pLayer->SelectElement(pElement);
			}
		}
		break;
	case OPT_EDIT_PROPERTY:
		{
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
			{
				IElementPtr pElement = m_ElementsOperInfo[i].element.first;
				IElementPtr pCopyElement = m_ElementsOperInfo[i].element.second;

				SYSTEM::CBinArchive ar1;
				pElement->serialization( ar1 );

				SYSTEM::CBinArchive ar2;
				pCopyElement->serialization( ar2 );

				ar2.SetReadState();
				ar2.SetPosToBegin();
				pElement->serialization( ar2 );

				ar1.SetReadState();
				ar1.SetPosToBegin();
				pCopyElement->serialization( ar1 );

				m_pLayer->SelectElement(pElement);
			}
		}
		break;	
	case OPT_MOVE_UP:
		{
			Element::CElementCollection collect;
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
				collect.Add(m_ElementsOperInfo[i].element.first);

			m_pLayer->BringForward(collect);

			m_pLayer->SelectElements(collect);
		}
		break;
	case OPT_MOVE_DOWN:
		{
			Element::CElementCollection collect;
			for(int i=0; i<m_ElementsOperInfo.size(); i++)
				collect.Add(m_ElementsOperInfo[i].element.first);

			m_pLayer->SendBackward(collect);

			m_pLayer->SelectElements(collect);
		}
		break;
	case OPT_MOVE_TOP:
		{
			for(int i=0; i<m_pLayer->GetElementCount(); i++)
			{
				IElementPtr pElement = m_pLayer->GetElement(i);
				IElementPtr pOperElement;

				/*if(pElement->GetType() == ET_MAP_FRAME_ELEMENT)
				{
					CGraphicsContainerPtr surrouds = ((CMapFramePtr)pElement)->GetMapSurroundContainer();
					for(int k=0; k<surrouds->GetElementCount(); k++)
					{
						IMapSurroundPtr pMapSurround = surrouds->GetElement(k);
						for(int j=0; j<m_ElementsOperInfo.size(); j++)
						{
							pOperElement = m_ElementsOperInfo[j].element.first;
							if(pOperElement == pMapSurround)
							{
								unsigned long pos = m_ElementsOperInfo[j].pos;
								surrouds->RemoveElement(pOperElement);
								surrouds->InserElementAt(pos, pOperElement);
								m_pLayer->SelectElement(pElement);
								break;
							}
						}
					}			
				}
				else
				{*/
					for(int j=0; j<m_ElementsOperInfo.size(); j++)
					{
						pOperElement = m_ElementsOperInfo[j].element.first;
						if(pOperElement == pElement)
						{
							unsigned long pos = m_ElementsOperInfo[j].pos;
							m_pLayer->RemoveElement(pOperElement);
							m_pLayer->InserElementAt(pos, pOperElement);
							m_pLayer->SelectElement(pElement);
							break;
						}
					}				
				/*}	*/
			}

		}
		break;
	case OPT_MOVE_BOTTOM:
		{
			for(int i=0; i<m_pLayer->GetElementCount(); i++)
			{
				IElementPtr pElement = m_pLayer->GetElement(i);
				IElementPtr pOperElement;

				/*if(pElement->GetType() == ET_MAP_FRAME_ELEMENT)
				{
					CGraphicsContainerPtr surrouds = ((CMapFramePtr)pElement)->GetMapSurroundContainer();
					for(int k=surrouds->GetElementCount()-1; k>=0; --k)
					{
						IMapSurroundPtr pMapSurround = surrouds->GetElement(k);
						for(int j=0; j<m_ElementsOperInfo.size(); j++)
						{
							pOperElement = m_ElementsOperInfo[j].element.first;
							if(pOperElement == pMapSurround)
							{
								unsigned long pos = m_ElementsOperInfo[j].pos;
								surrouds->RemoveElement(pOperElement);
								surrouds->InserElementAt(pos, pOperElement);
								m_pLayer->SelectElement(pElement);
								break;
							}
						}
					}			
				}
				else
				{*/
					for(int i=m_pLayer->GetElementCount()-1; i>=0; i--)
					{
						IElementPtr pElement = m_pLayer->GetElement(i);
						IElementPtr pOperElement;
						for(int j=0; j<m_ElementsOperInfo.size(); j++)
						{
							pOperElement = m_ElementsOperInfo[j].element.first;
							if(pOperElement == pElement)
							{
								unsigned long pos = m_ElementsOperInfo[j].pos;
								m_pLayer->RemoveElement(pOperElement);
								m_pLayer->InserElementAt(pos, pOperElement);
								m_pLayer->SelectElement(pElement);
								break;
							}
						}
					}
				/*}*/
			}
		}
		break;
	default:
		break;
	}

	m_bCanUndo = FALSE;
}

BOOL CElementOperation::SetOperation(OP_TYPE opType, CElementCollection elements)
{
	switch(opType)
	{
	case OPT_GROUP:		
	case OPT_UNGROUP:
		{
			if(elements.Count() == 0)
				return FALSE;

			IElementPtr pElement = elements.QueryElement(0);
			if(pElement->GetType()!=ET_GROUP_ELEMENT)
				return FALSE;

			ElementOperInfo info;
			info.element.first = pElement;
			info.element.second = NULL;

			m_ElementsOperInfo.push_back(info);
		}
		break;
	case OPT_ADD:
	case OPT_REMOVE:
		{
			for(int i=0; i<elements.Count(); i++)
			{
				IElementPtr pElement = elements.QueryElement(i);

				ElementOperInfo info;
				info.element.first = pElement;
				info.element.second = NULL;

				m_ElementsOperInfo.push_back(info);
			}			
		}
		break;
	case OPT_EDIT_PROPERTY:
		{
			for(int i=0; i<elements.Count(); i++)
			{
				IElementPtr pElement = elements.QueryElement(i);

				ElementOperInfo info;
				info.element.first = pElement;
				info.element.second = pElement->Clone();

				m_ElementsOperInfo.push_back(info);
			}			
		}
		break;
	case OPT_MOVE_UP:
	case OPT_MOVE_DOWN:
		{
			for(int i=0; i<elements.Count(); i++)
			{
				IElementPtr pElement = elements.QueryElement(i);

				ElementOperInfo info;
				info.element.first = pElement;
				info.element.second = NULL;

				m_ElementsOperInfo.push_back(info);
			}			
		}
		break;
	case OPT_MOVE_TOP:
	case OPT_MOVE_BOTTOM:
		{
			for(int i=0; i<elements.Count(); i++)
			{
				IElementPtr pElement = elements.QueryElement(i);

				ElementOperInfo info;
				info.element.first = pElement;
				info.element.second = NULL;
				/*if(pElement->GetType() & ET_MAP_FRAME_ELEMENT)
				{
					info.pos = ((IMapSurroundPtr)pElement)->GetMapFrame()->GetMapSurroundContainer()->FindElement(pElement);
				}
				else
				{		*/		
					info.pos = m_pLayer->FindElement(pElement);
				/*}*/

				m_ElementsOperInfo.push_back(info);
			}			
		}
		break;
	default:
		break;
	}

	SetOperationType(opType);

	return TRUE;
}

BOOL CElementOperation::SetOperation(OP_TYPE opType, IElementPtr element)
{
	switch(opType)
	{
	case OPT_GROUP:
	case OPT_UNGROUP:
		{
			if(element->GetType()!=ET_GROUP_ELEMENT)
				return FALSE;

			ElementOperInfo info;
			info.element.first = element;
			info.element.second = NULL;

			m_ElementsOperInfo.push_back(info);
		}
		break;
	case OPT_ADD:
	case OPT_REMOVE:
		{
			ElementOperInfo info;
			info.element.first = element;
			info.element.second = NULL;

			m_ElementsOperInfo.push_back(info);
		}
		break;
	case OPT_EDIT_PROPERTY:
		{
			ElementOperInfo info;
			info.element.first = element;
			info.element.second = element->Clone();

			m_ElementsOperInfo.push_back(info);
		}
		break;
	case OPT_MOVE_UP:
	case OPT_MOVE_DOWN:
		{
			ElementOperInfo info;
			info.element.first = element;
			info.element.second = NULL;

			m_ElementsOperInfo.push_back(info);
		}
		break;
	case OPT_MOVE_TOP:
	case OPT_MOVE_BOTTOM:
		{
			ElementOperInfo info;
			info.element.first = element;
			info.element.second = NULL;
			/*if(element->GetType() & ET_MAP_FRAME_ELEMENT)
			{
				info.pos = ((IMapSurroundPtr)element)->GetMapFrame()->GetMapSurroundContainer()->FindElement(element);
			}
			else
			{*/				
				info.pos = m_pLayer->FindElement(element);
			/*}*/
			m_ElementsOperInfo.push_back(info);
		}
		break;
	default:
		break;
	}

	SetOperationType(opType);

	return TRUE;
}

std::string CElementOperation::GetMenuString()
{
	return m_menuString;
}


void CElementOperation::SetOperationType(OP_TYPE opType)
{
	m_opType = opType;

	switch(m_opType)
	{
	case OPT_ADD:
		m_menuString = "创建图元";
		break;
	case OPT_REMOVE:
		m_menuString = "删除图元";
		break;
	case OPT_EDIT_PROPERTY:
		m_menuString = "编辑图元";
		break;
	case OPT_GROUP:
		m_menuString = "图元成组";
		break;
	case OPT_UNGROUP:
		m_menuString = "图元打散";
		break;
	}
}

};