
#ifndef CConfigItem_H
#define CConfigItem_H

#include "IConfigItem.h"

namespace SYSTEM{

class SYSTEM_DLL CConfigItem : public IConfigItem 
{
public:

    CConfigItem();

    virtual ~CConfigItem();

	// 函数名称		: GetChilds(long i)
	// 描述			: 得到第i个子节点
	// 返回类型		: virtual IConfigItemPtr   智能指针，指向第i个子节点
	// 参数			: long i    节点的索引
	virtual IConfigItemPtr GetChilds(long i); //得到第i个子节点

	// 函数名称		: GetParent()
	// 描述			: 得到父节点
	// 返回类型		: virtual IConfigItemPtr   智能指针，指向子节点对应的父节点
	// 参数			: void
	virtual IConfigItemPtr GetParent();

	// 函数名称   : GetChildByName(char *Name)
	// 描述       : 当节点名称唯一时，通过名字得到子节点
	// 返回类型   : virtual IConfigItemPtr   智能指针，指向节点名称对应的子节点
	// 参数        : char *Name   节点名称
	virtual IConfigItemPtr GetChildByName(const char *Name); // 当节点名称唯一时，通过名字得到子节点

	// 函数名称		: GetFirstChild()
	// 描述			: 得到配置项第1个子节点
	// 返回类型		: IConfigItemPtr   智能指针，指向第1个子节点
	// 参数			: void
	virtual IConfigItemPtr GetFirstChild();

	// 函数名称		: GetLastChild()
	// 描述			: 得到配置项最后子节点
	// 返回类型		: IConfigItemPtr   智能指针，指向最后一个子节点
	// 参数			: void
	virtual IConfigItemPtr GetLastChild();

	// 函数名称   : GetPreviousSibling()
	// 描述       : 获得当前节点的前个兄弟节点
	// 返回类型   : IConfigItemPtr    智能指针，指向节点名称对应的子节点
	virtual IConfigItemPtr GetPreviousSibling();

	// 函数名称   : GetNextSibling()
	// 描述       : 获得当前节点的下个兄弟节点
	// 返回类型   : IConfigItemPtr    智能指针，指向节点名称对应的子节点
	virtual IConfigItemPtr GetNextSibling();

	// 函数名称   : * GetName()
	// 描述       : 获得节点名称
	// 返回类型   : virtual char   指向节点名称的指针 
	virtual const char * GetName(); //得到节点名称

	// 函数名称   : SetName(char * name)
	// 描述       : 设置节点名称
	// 返回类型   : virtual void   
	// 参数        : char * name   节点名称
	virtual void SetName(const char * name); //设置节点名称

	// 函数名称   : * GetValue()
	// 描述       : 获得节点的值
	// 返回类型   : virtual char   节点值
	virtual const char * GetValue(); //得到节点值

	// 函数名称   : SetValue(char * value)
	// 描述       : 设置节点值
	// 返回类型   : virtual void 
	// 参数        : char * value   节点值
	virtual void SetValue(const char * value); //设置节点值

	// 函数名称   : GetChildCount()
	// 描述       : 得到当前节点的子节点个数
	// 返回类型   : virtual long 
	virtual long GetChildCount(); //得到子节点个数

	// 函数名称   : char * GetProperties(char * propName)
	// 描述       : 获得属性名对应的属性值
	// 返回类型   : virtual const 
	// 参数       : char * propName   属性名
	virtual const char * GetProperties(const char * propName); //得到属性值

	// 函数名称   : SetProperties(char * propName, char * value)
	// 描述       : 根据当前节点的属性名设置属性值
	// 返回类型   : virtual void 
	// 参数       : char * propName   属性名
	// 参数       : char * value   属性值
	virtual void SetProperties(const char * propName, const char * value); //设置属性值

	// 函数名称   : AddChildNode(char * name)
	// 描述       : 添加当前节点的子节点
	// 返回类型   : virtual void 
	// 参数        : char * name   子节点名称
	virtual SYSTEM::IConfigItemPtr AddChildNode(const char * name); //添加子节点

	// 函数名称   : DeleteChildNode(long i)
	// 描述       : 删除当前节点的第i个子节点
	// 返回类型   : virtual void 
	// 参数        : long i   子节点索引
	virtual bool DeleteChildNode(long i); //删除子节点

	// 函数名称		: DeleteChildByName(const char* name)
	// 描述			: 删除name子节点
	// 返回类型		:  bool
	// 参数			: const char* name   子节点名字
	virtual	bool DeleteChildByName(const char* name);//删除第i个子节点

	// 函数名称   : AddAttributeName(char * name, char * value)
	// 描述       : 添加属性名及其值
	// 返回类型   : virtual void 
	// 参数        :char * name   属性名
	// 参数        :char * value   属性值
	virtual void AddAttribute(const char * name, const char * value); //添加属性名及其值

	// 函数名称   : DeleteAttributeName(char * name)
	// 描述       : 根据属性名删除这个属性
	// 返回类型   : virtual void 
	// 参数        : char * name   属性名
	virtual void DeleteAttributeByName(const char * name); //删除属性名及其值

	// 函数名称   : DeleteAttributeName(char * name)
	// 描述       : 删除所有属性
	// 返回类型   : virtual void 
	virtual void RemoveAllAttributes();

protected:

    void * itemElement; //DOMElement

    void * doc; //DOMDocument

	char * m_curValue;
};

}

#endif //CConfigItem_H
