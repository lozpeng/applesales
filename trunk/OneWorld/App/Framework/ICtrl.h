#ifndef _ICtrl_H_
#define _ICtrl_H_

#include <map>
#include <string>
#include "FrameworkDefine.h"

#define		MapControl		1
#define		LayoutControl	2
#define		TocControl		3

namespace Framework
{

class FRAMEWORK_DLL ICtrl
{

public : 
	ICtrl();
	virtual ~ICtrl();

	/**
	* 获得名称
	*/
	std::string GetName();

public:

	/**
	* 通过控件ID获得用户界面对象
	* @param nUIID 控件ID
	* @return 若存在则返回该对象指针，否则返回为NULL
	*/
	static ICtrl* GetUIObjectByID(int nUIID);

	/**
	* 获得第一个用户界面对象
	* @return 若存在则返回该对象指针，否则返回为NULL
	*/
	static ICtrl* GetFirstUI();

	/**
	* 获得下一个用户界面对象
	* @return 若存在则返回该对象指针，否则返回为NULL
	*/
	static ICtrl* GetNextUI();



protected:

	/**< 创建关联对象*/
	virtual void CreateUI(int nUIID);

	/**< 删除关联对象*/
	virtual void DestroyUI();

	//UIID
	int		m_nID;

};

}
#endif //_ICtrl_H_