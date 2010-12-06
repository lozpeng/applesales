/* Generated by Together */

#ifndef CDISPLAYCACHE_H
#define CDISPLAYCACHE_H


namespace Display{
class CDC;
class ISymbol;

typedef struct _DISPLAY_HANDLE_NODE
{
	DISPLAY_HANDLE Handle;
	CDC* pDC;
}DISPLAY_HANDLE_NODE;

typedef std::set< DISPLAY_HANDLE_NODE* > DISPLAY_HANDLE_NODES;

class DISPLAY_DLL CDisplayCache {
public:

		// 添加GDI等对象到全局缓存中
		static DISPLAY_HANDLE_NODE* AddToDisplayCache( DISPLAY_HANDLE pHandle , CDC *pDC );

		// 释放GDI等对象缓存
		static void ReleaseCache( DISPLAY_HANDLE_NODE * pNode );

		// 确认使用对象缓存
		static BOOL UseCache( DISPLAY_HANDLE_NODE *pNode, ISymbol* pSym );

		// 清除所有缓存
		static void ClearCache();

        ~CDisplayCache();

        CDisplayCache();

protected:
	static DISPLAY_HANDLE_NODES DisplayCacheNodes;
	static unsigned long DisplayHandle_Count;
};

}

#endif //CDISPLAYCACHE_H
