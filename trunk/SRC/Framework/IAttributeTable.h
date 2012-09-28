#ifndef _IATTRIBUTE_TABLE_H_
#define _IATTRIBUTE_TABLE_H_


#include "IUIObject.h"
#include "ILayer.h"
#include "ISelectionSet.h"

namespace Framework
{

/********************************************************************************
* IAttributeTable是矢量属性表的基类
* 
*********************************************************************************/

class FRAMEWORK_DLL IAttributeTable :public IUIObject
{
public:
	IAttributeTable();
	virtual ~IAttributeTable();
public:

	/**
	* 关闭数据表
	*/
	virtual void CloseTable();

	/**
	* 关闭数据表
	*/
	virtual void RefreshTable(){};

	/**
	* 设置属性表的关联图层
	*/
	virtual void SetLayer(Carto::ILayerPtr pLayer);


	/**
	* 判断数据表是否已经打开
	*/
	virtual bool TableIsOpen();


	/**
	* 更新图层的选择集
	*/
	virtual void UpdateLayerSelction();

	/**
	* 数据表是否可以编辑
	*/
	virtual bool CanEdit( );


	/**
	* 选择全部
	*/
	void SelectAll();

	/**
	* 取消选择
	*/
	void SelectNone();

	/**
	* 得到记录总数
	*/
	long GetRecordCount(){return m_totalRecord;}

	/**
	* 得到选中的数目
	*/
	long GetSelectCount(){return m_selRecord;}

	/**
	* 设置选择集
	*/
   virtual void SetSelction(Geodatabase::ISelctionSetPtr pSel);

	/**
	* 得到属性表对应的图层
	*/
	virtual Carto::ILayerPtr GetCurSelectLayer();

	static IAttributeTable* GetActiveAttributeTable();

protected:
	Carto::ILayerPtr m_pLayer; //属性表关联的图层

	//总记录数
	long m_totalRecord;

	//选中记录数
	long m_selRecord;

};

}


#endif