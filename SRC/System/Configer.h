#ifndef CConfiger_H
#define CConfiger_H

#include <string>
#include "ConfigItem.h"


namespace SYSTEM{

class SYSTEM_DLL CXMLConfiguration : public CConfigItem
{
public:
	CXMLConfiguration();
	virtual ~CXMLConfiguration();

	// 函数名称   : Initialize()
	// 描述       : 初始化环境变量(无论实例化多少个对象,该函数在使用过程中仅调用一次)
	// 返回类型   : void 
	static void Initialize();

	// 函数名称   : Uninitialize()
	// 描述       : 释放所有环境变量
	// 返回类型   : void 
	static void Uninitialize();

	// 函数名称   : CreateXmlFile()
	// 描述       : 创建一个xml文件
	// 返回类型   : void 
	virtual void Create(std::string  xmlpath , std::string  charCode , std::string rootNodeName);

	// 函数名称   : Open(std::string xmlpath)
	// 描述       : 打开指定的XML文件
	// 返回类型   : void 
	virtual bool Open(std::string xmlpath);

	// 函数名称   : Parse(std:string xmlcontent)
	// 描述       : 解析xml文件流
	// 返回类型   : void 
	virtual void Parse(std::string xmlcontent);

	// 函数名称   : Close
	// 描述       : 关闭以打开的XML文件
	// 返回类型   : void 
	virtual void Close();

	// 函数名称   : Save()
	// 描述       : 保存数据到XML文件中去
	// 返回类型   : void 
	void Save(); //保存更改	

private:
	std::string xmlFile; //所要解析的文件
    void * impl; //DOMImplementation
    void * parser; //解析器	//XercesDOMParser类型
};

typedef SYSTEM::CSmartPtr<CXMLConfiguration> XMLConfigurationPtr;

/*****************CConfiger类之针对平台内部使用************************/

class SYSTEM_DLL CConfiger : public CXMLConfiguration
{
public:
	static void Initialize(std::string identity);

	// 函数名称   : * GetConfigerRoot()
	// 描述       : 初始化并得到根节点
	// 返回类型   : static CConfiger   根节点
	static SYSTEM::IConfigItemPtr GetConfigerRoot(); //初始化并得到根节点

	// 函数名称   : Terminate()
	// 描述       : 删除XML处理模块的对象
	// 返回类型   : static void   
	static void Terminate(); //删除XML处理模块的对象

private:
	CConfiger();
};
typedef SYSTEM::CSmartPtr<CConfiger> IConfigerPtr;

}

#endif //CConfiger_H
