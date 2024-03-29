
#ifndef IConfigItem_H
#define IConfigItem_H

#include "SmartPtr.h"

namespace SYSTEM{

class IConfigItem;
typedef CSmartPtr<IConfigItem> IConfigItemPtr;

class SYSTEM_DLL IConfigItem 
{
public:
	virtual ~IConfigItem(){};

	// 函数名称   : GetChilds(long i)
	// 描述       : 得到配置项第i个子节点
	// 返回类型   : IConfigItemPtr   智能指针，指向第i个子节点
	// 参数        : long i   节点的索引
	virtual IConfigItemPtr GetChilds(long i) = 0;	//IConfigItemPtr，得到配置项第i个子节点

	// 函数名称		: GetParent()
	// 描述			: 得到父节点
	// 返回类型		: virtual IConfigItemPtr   智能指针，指向子节点对应的父节点
	// 参数			: void
	virtual IConfigItemPtr GetParent() = 0;

	// 函数名称   : GetChildByName(char *Name)
	// 描述       : 当配置项节点名称唯一时，通过名字得到子节点
	// 返回类型   : IConfigItemPtr    智能指针，指向节点名称对应的子节点
	// 参数        : char *Name   节点名称
	virtual IConfigItemPtr GetChildByName(const char *name) = 0; // 当节点名称唯一时，通过名字得到子节点

	// 函数名称		: GetFirstChild()
	// 描述			: 得到配置项第1个子节点
	// 返回类型		: IConfigItemPtr   智能指针，指向第1个子节点
	// 参数			: void
	virtual IConfigItemPtr GetFirstChild() = 0;

	// 函数名称		: GetLastChild()
	// 描述			: 得到配置项最后子节点
	// 返回类型		: IConfigItemPtr   智能指针，指向最后一个子节点
	// 参数			: void
	virtual IConfigItemPtr GetLastChild() = 0;

	// 函数名称   : GetPreviousSibling()
	// 描述       : 获得当前节点的前个兄弟节点
	// 返回类型   : IConfigItemPtr    智能指针，指向节点名称对应的子节点
	virtual IConfigItemPtr GetPreviousSibling() = 0;

	// 函数名称   : GetNextSibling()
	// 描述       : 获得当前节点的下个兄弟节点
	// 返回类型   : IConfigItemPtr    智能指针，指向节点名称对应的子节点
	virtual IConfigItemPtr GetNextSibling() = 0;

	// 函数名称   : AddChildNode(char *name)
	// 描述       : 添加一个子节点
	// 返回类型   : void 
	// 参数        : char *name   要添加的子节点的名称
	virtual	IConfigItemPtr AddChildNode(const char *name)=0;//添加一个子节点

	// 函数名称   : DeleteChildNode(long i)
	// 描述       : 删除第i个子节点
	// 返回类型   :  void 
	// 参数        : long i   子节点索引
	virtual	bool DeleteChildNode(long i)=0;//删除第i个子节点

	// 函数名称		: DeleteChildByName(const char* name)
	// 描述			: 删除name子节点
	// 返回类型		:  bool
	// 参数			: const char* name   子节点名字
	virtual	bool DeleteChildByName(const char* name)=0;//删除第i个子节点

	// 函数名称   : AddAttributeName(char *name,char *value)
	// 描述       : 添加属性名及其值
	// 返回类型   : virtual void 
	// 参数        : char *name   属性名
	// 参数        : char *value  属性值
	virtual void AddAttribute(const char *name, const char *value)=0;//添加属性名及其值

	// 函数名称   : DeleteAttributeName(char *name)
	// 描述       : 删除属性名
	// 返回类型   : virtual void 
	// 参数        : char *name   属性名
	virtual void DeleteAttributeByName(const char *name)=0;//删除属性名

	// 函数名称   : GetName()
	// 描述       : 获得节点名称
	// 返回类型   : virtual char*   指向节点名称的指针
	virtual const char* GetName() = 0;//获得节点名称

	// 函数名称   : SetName(char *name)
	// 描述       : 设置节点名称
	// 返回类型   : virtual void  
	// 参数        : char *name   子节点名称
	virtual void SetName(const char *name) = 0;//设置节点名称

	// 函数名称   : GetValue()
	// 描述       : 获得节点值
	// 返回类型   : virtual char*   指向节点值的指针
	virtual const char* GetValue() = 0;

	// 函数名称   : SetValue(char *value)
	// 描述       : 设置节点值
	// 返回类型   : virtual void 
	// 参数        : char *value   指向节点值的指针
	virtual void SetValue(const char *value) = 0;

	// 函数名称   : GetChildCount()
	// 描述       : 获得当前节点的子节点的个数
	// 返回类型   : virtual long   子节点个数
	virtual long GetChildCount() = 0;

	// 函数名称   : char* GetProperties(char *propName)
	// 描述       : 根据属性名获得属性值
	// 返回类型   : virtual const   指向属性值的指针
	// 参数        :char *propName  属性名
	virtual const char* GetProperties(const char *propName) = 0;

	// 函数名称   : SetProperties(char *propName, char *value)
	// 描述       : 设置当前属性名对应的属性值
	// 返回类型   : virtual void 
	// 参数        : char *propName   属性名
	// 参数        : char *value      属性值
	virtual void SetProperties(const char *propName, const char *value) = 0;

	virtual void RemoveAllAttributes() = 0; //2007.10.25 张维添加
};

}

#endif //IConfigItem_H
