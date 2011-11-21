//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  ���߻���
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
	//�������
	std::string GetName();

	//���߳�ʼ��
	virtual void Initialize(IUIObject *pTargetControl);

	virtual ITool* Clone();

	//��Ϣ��Ӧ
	virtual void LButtonDownEvent (UINT nFlags, CPoint point);
	virtual void LButtonUpEvent (UINT nFlags, CPoint point);
	virtual void RButtonDownEvent (UINT nFlags, CPoint point);
	virtual void MouseMoveEvent (UINT nFlags, CPoint point);
	virtual void KeyDownEvent (UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void KeyUpEvent (UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void LButtonDblClkEvent (UINT nFlags, CPoint point);


public:
	//ͨ�����Ƶõ����߶���
	static ITool* FindTool(std::string strName);

	static ITool* CreateTool(std::string strName);

	//ע�Ṥ��
	static void RegisterTool(std::string strName, ITool* pTool);

protected:

	std::string m_strName;

	//���������ؼ�
	IUIObject *m_pTarget;


protected:

	static std::map<std::string,ITool*> gTools;

};

}
#endif

