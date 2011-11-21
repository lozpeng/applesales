//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  工具基类
//////////////////////////////////////////////////////////////////////
#ifndef  _ITOOL_H_
#define  _ITOOL_H_

#include <map>
#include "IUIObject.h"

namespace Framework
{

class FRAMEWORK_DLL ITool
{
public:
	ITool(const char* name);
	virtual ~ITool(void);

public:
	//获得名称
	std::string GetName();

	//工具初始化
	virtual void Initialize(IUIObject *pTargetControl);

	virtual ITool* Clone();

	//消息响应
	virtual void LButtonDownEvent (UINT nFlags, CPoint point);
	virtual void LButtonUpEvent (UINT nFlags, CPoint point);
	virtual void RButtonDownEvent (UINT nFlags, CPoint point);
	virtual void MouseMoveEvent (UINT nFlags, CPoint point);
	virtual void KeyDownEvent (UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void KeyUpEvent (UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void LButtonDblClkEvent (UINT nFlags, CPoint point);


public:
	//通过名称得到工具对象
	static ITool* FindTool(std::string strName);

	static ITool* CreateTool(std::string strName);

	//注册工具
	static void RegisterTool(std::string strName, ITool* pTool);

protected:

	std::string m_strName;

	//工具所属控件
	IUIObject *m_pTarget;


protected:

	static std::map<std::string,ITool*> gTools;

};

}
#endif

