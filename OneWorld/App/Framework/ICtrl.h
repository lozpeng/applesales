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
	* �������
	*/
	std::string GetName();

public:

	/**
	* ͨ���ؼ�ID����û��������
	* @param nUIID �ؼ�ID
	* @return �������򷵻ظö���ָ�룬���򷵻�ΪNULL
	*/
	static ICtrl* GetUIObjectByID(int nUIID);

	/**
	* ��õ�һ���û��������
	* @return �������򷵻ظö���ָ�룬���򷵻�ΪNULL
	*/
	static ICtrl* GetFirstUI();

	/**
	* �����һ���û��������
	* @return �������򷵻ظö���ָ�룬���򷵻�ΪNULL
	*/
	static ICtrl* GetNextUI();



protected:

	/**< ������������*/
	virtual void CreateUI(int nUIID);

	/**< ɾ����������*/
	virtual void DestroyUI();

	//UIID
	int		m_nID;

};

}
#endif //_ICtrl_H_