#ifndef _IMapCtrl_h
#define _IMapCtrl_h

#include "IUIObject.h"
#include "Map.h"
#include "IDisplay.h"


namespace Framework
{


class FRAMEWORK_DLL IMapCtrl : public IUIObject
{
public:
	IMapCtrl();
	virtual ~IMapCtrl();

public:

	virtual void ReDraw(long content);

	//控件客户区大小改变事件
	virtual void ControlResize(UINT nType, int cx, int cy);

	//设置地图对象
	virtual void SetMap(Carto::CMapPtr pGeoMap);

	//得到地图对象
	virtual Carto::CMapPtr GetMap();

	//更新地图内容
	virtual void UpdateControl(long content);

	//刷新地图内容
	virtual void RefreshScreen();

	//移动地图内容
	virtual void OffsetClient(long offset_x, long offset_y);

	COLORREF GetBgColor(){return m_BgColor;};

	HDC GetClientDC() {return m_hClientDC;}

	HDC GetMemDC() {return m_hMemDC;}

	//得到控件的大小
	long GetSizeX() { return m_lSizeX;}
	long GetSizeY() {return m_lSizeY;}


protected:
	//将地理内容贴到屏幕上
	void RefreshGeography();

protected:

	
	Carto::CMapPtr m_pGeoMap;

	
	BOOL m_bInitialized;

	HDC m_hClientDC,m_hMemDC;

	long m_lSizeX,m_lSizeY;

	COLORREF m_BgColor;
	long m_lCursorType;
	std::string m_curAction;

	

};

}
#endif