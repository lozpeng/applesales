//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  界面对象基类
//////////////////////////////////////////////////////////////////////

#ifndef _IUIObject_h
#define _IUIObject_h

#include <map>

namespace Framework
{

//界面组件在注册时使用的名称
class FRAMEWORK_DLL CommonUIName
{
public:
	//主程序的地图控件
	static std::string AppMapControl;

	// 主程序文档
	static std::string AppDocument;
};

class FRAMEWORK_DLL IUIObject : public SYSTEM::ISerialization
{

public : 
	IUIObject();
	virtual ~IUIObject();

	/**
	* 序列化
	* @param ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	/**
	* 获得名称
	*/
	std::string GetName();

	//
	bool GetAutoDestroy() {return m_bAutoDestroy;}
	void SetAutoDetroy(bool bAutoDestroy) { m_bAutoDestroy = bAutoDestroy;}
public:

	/**
	* 通过名称获得用户界面对象
	* @param Name 控件名称
	* @return 若存在则返回该对象指针，否则返回为NULL
	*/
	static IUIObject* GetUIObjectByName(std::string Name);

	/**
	* 获得第一个用户界面对象
	* @return 若存在则返回该对象指针，否则返回为NULL
	*/
	static IUIObject* GetFirstObject();

	/**
	* 获得下一个用户界面对象
	* @return 若存在则返回该对象指针，否则返回为NULL
	*/
	static IUIObject* GetNextObject();



protected:

	/**< 创建关联对象*/
	virtual void CreateAss(std::string Name);

	/**< 删除关联对象*/
	virtual void DestroyAss();

	//oject name
	std::string m_Name;

	//is AutoDestroy
	bool m_bAutoDestroy;

};

}
#endif