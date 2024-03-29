/* Generated by Together */
#include "stdafx.h"
#include "DisplayCache.h"
#include "CDC.h"
#include "ISymbol.h"

unsigned long Display::CDisplayCache::DisplayHandle_Count = 0;
Display::DISPLAY_HANDLE_NODES Display::CDisplayCache::DisplayCacheNodes;

Display::CDisplayCache::CDisplayCache()
{

}
Display::CDisplayCache::~CDisplayCache()
{
	ClearCache();
}

// 添加GDI等对象到全局缓存中
Display::DISPLAY_HANDLE_NODE* Display::CDisplayCache::AddToDisplayCache( DISPLAY_HANDLE pHandle , CDC *pDC )
{
	if(pHandle == NULL)
		return NULL;

	Display::DISPLAY_HANDLE_NODE *dhn = new DISPLAY_HANDLE_NODE;
	dhn->pDC = pDC;
	dhn->Handle = pHandle;

	if( DisplayHandle_Count > MAX_COUNT )
	{
		// 如果GDI对象超过规定数量，则进行清理
		unsigned long min = MAX_COUNT/2;
		std::set<Display::DISPLAY_HANDLE_NODE *>::iterator item;
		for ( item = DisplayCacheNodes.begin() ; item != DisplayCacheNodes.end() && DisplayHandle_Count >= min; item++ )
		{
			Display::CDC *pDc = (*item)->pDC;
			pDc->RemoveHandle( (*item)->Handle );
			(*item)->Handle = NULL;
			if(DisplayHandle_Count>0)
			{
				DisplayHandle_Count--;
			}
		}
	}

	DisplayCacheNodes.insert( dhn );
	DisplayHandle_Count++;
	return dhn;
}

// 释放GDI等对象缓存
void Display::CDisplayCache::ReleaseCache( DISPLAY_HANDLE_NODE * pNode )
{
	DisplayCacheNodes.erase( pNode );

	Display::CDC *pDC = pNode->pDC;
	pDC->RemoveHandle( pNode->Handle );

	delete pNode;
	if(DisplayHandle_Count>0)
	{
		DisplayHandle_Count--;
	}
}

// 确认使用对象缓存
BOOL Display::CDisplayCache::UseCache( DISPLAY_HANDLE_NODE *pNode , Display::ISymbol* pSym)
{
	if(pNode == NULL)
		return FALSE;

	if( pNode->Handle != NULL )
	{
		pNode->pDC->SelectObject( pNode->Handle );
	}
	else
	{
		DisplayCacheNodes.erase( pNode );
		pSym->SelectDC( pNode->pDC );
		pSym->SetReadyDraw();
	}
	return TRUE;
}

// 清除所有缓存
void Display::CDisplayCache::ClearCache()
{
	std::vector< DISPLAY_HANDLE_NODE* > nodes;
	std::set<Display::DISPLAY_HANDLE_NODE *>::iterator item;
	for ( item = DisplayCacheNodes.begin() ; item != DisplayCacheNodes.end() ; item++ )
	{
		nodes.push_back( (*item) );
	}
	for ( int i = 0 ; i < nodes.size() ; i++ )
	{
		ReleaseCache( nodes[i] );
	}
}
