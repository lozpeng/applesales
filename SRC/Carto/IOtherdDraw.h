#ifndef _IEXTEND_DRAW_H
#define _IEXTEND_DRAW_H

#include "IDisplay.h"

namespace Carto
{

//扩展绘制内容的接口
class CARTO_DLL IOtherDraw
{
public:
	IOtherDraw();
	virtual ~IOtherDraw();

public:

	/**
	* 绘制
	* @param pDisplay 绘制的环境
	*/
	virtual void Draw(Display::IDisplayPtr pDisplay) =0;

	/**
	* 得到绘制内容的名称
	*/
	std::string GetName();

	/**
	* 设置绘制内容的名称
	*/
	void SetName(const char *strName);

protected:
	std::string m_name;

};


}


#endif