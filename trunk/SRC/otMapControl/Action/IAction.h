#pragma once

namespace Carto
{
	class CMap;
}

class CotMapCtrl;

//cursor
#define CURSOR_COUNT 14
enum CURSOR_TYPE
{
	cursorNormal,
	cursorPan,
	cursorZoomOut,
	cursorZoomIn,
	cursorCross,
	cursorSizeAll,
	cursorleftTop,
	cursorRightTop,
	cursorTopBottom,
	cursorLeftRight,
	cursorOnVertix,
	cursorVertixMove,
	cursorOnLine,
	cursorModifyShape
};

//所有MapCtrl有关的动作类的接口
class IAction
{
public:
	IAction(long id);
	virtual ~IAction(void);

public:
	
	//action ID
	long GetActionID();

	
	virtual void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);

	//action response
	virtual void LButtonDownEvent (UINT nFlags, CPoint point);
	virtual void LButtonUpEvent (UINT nFlags, CPoint point);
	virtual void RButtonDownEvent (UINT nFlags, CPoint point);
	virtual void MouseMoveEvent (UINT nFlags, CPoint point);
	virtual void KeyDownEvent (UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void KeyUpEvent (UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void LButtonDblClkEvent (UINT nFlags, CPoint point);

	//
	virtual void Triger(){};

	//update mouse toolbar's status
	virtual void UpdateMouseCursor();
	virtual void UpdateToolBar();

public:
	//get action object
	static IAction* FindAction(long id);


	//register action
	static void RegisterAction(long id, IAction* pAction);

	//注册所有的Action
	static void RegisterAll();
    //销毁所有Action
	static void UnRegisterAll();

protected:

	//action type
	long m_actionID;

	//action status
	long m_nStatus;

	Carto::CMap *m_pMap;

	CotMapCtrl *m_pMapCtrl;

protected:

	//all actions
	static std::map<long,IAction*> gActions;

	//Action  Stack.
	static std::vector<long> gActionStack;
};
