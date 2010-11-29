
//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/11/18
// 描述：  数据层的渲染定义，其它地理数据层（栅格、矢量等层）均由其派生
//////////////////////////////////////////////////////////////////////

#ifndef _IRender_h
#define _IRender_h
#include "ICursor.h"
#include "ISelectionSet.h"
#include "IDisplay.h"
#include "LegendInfo.h"

namespace Geodatabase
{
	class ICursor;
	class ISelctionSet;
}

namespace Carto
{

class  CARTO_DLL IRender : public SYSTEM::ISerialization
{
public:
	IRender();
	virtual ~IRender();

public:
	/**
	* 对选中的记录集进行绘制
	* @param pDisplay 智能指针，指向显示接口
	* @param pdatarecordset 智能指针，指向记录集
	*/
	virtual void Draw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor ) = 0;

	/**
	* 对选中的记录集进行高亮绘制
	* @param pDisplay 智能指针，指向显示接口
	* @param pdatarecordset 智能指针，指向记录集
	*/
	virtual void HighLightDraw( Display::IDisplayPtr pDisplay,  Geodatabase::ICursorPtr pCursor  );

	/**
	* 对选中的记录集进行高亮绘制
	* @param pDisplay 智能指针，指向显示接口
	* @param pSelections 指向记录集的指针
	*/
	virtual void HighLightDraw(Display::IDisplayPtr pDisplay,  Geodatabase::ISelctionSet* pSelections);

	/**

	/**
	* 获得专题的字段名
	* @return 返回专题的字段名
	*/
	virtual std::string GetRendFieldsStr() = 0;

	/**
	* 复制专题
	* @return 返回专题
	*/
	virtual SYSTEM::CSmartPtr<IRender> CopyNewRender();

	/**
	* 获得专题类型
	* @return 返回专题类型
	*/
	RENDER_TYPE GetRenderType();

	/**
	* 设置Render图层
	* @return
	*/
	void SetAffineTransform(CAffineTransformPtr pAffineTransform) { m_pAffineTransform = pAffineTransform; }

	/**
	* 获得高亮显示的颜色
	* @return 颜色值
	*/
	COLORREF GetHighLightColor();

	/**
	* 设置高亮显示的颜色
	* @param color 颜色值
	*/
	void SetHighLightColor(COLORREF color);

	/**
	* 设置高亮显示的符号
	* @param pSymbol 符号
	*/
	void SetHighLightSymbol(Display::ISymbolPtr pSymbol);

	/**
	* 设置专题矢量类型
	* @param type 矢量类型
	*/
	virtual void SetRenderFeatureType(long type);

	/**
	* 获得专题矢量类型
	* @return 返回矢量类型
	*/
	long GetRenderFeatureType();

	/*
	* 得到图例的信息
	*/
	virtual CLegendInfoPtr GetLegendInfo();

	/**
	* 对当前专题进行序列化操作
	* @param ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar) = 0;

	/**
	* 根据流生成专题
	* @param ar 文档流
	* @return 返回专题
	*/
	static SYSTEM::CSmartPtr<IRender> CreateRenderFromStream(SYSTEM::IArchive &ar);

	/**
	* 创建专题
	* @param type 专题类型
	* @param RenderExtName 扩展专题名
	* @return 返回专题
	*/
	static SYSTEM::CSmartPtr<IRender> CreateRender( RENDER_TYPE type , std::string RenderExtName = "" );

protected:

	COLORREF m_HighLightColor;
	RENDER_TYPE m_type;
	long m_lFeaturetype;

	Display::ISymbolPtr m_pHighLightSymbol;
	Carto::CAffineTransformPtr m_pAffineTransform;

};

typedef SYSTEM::CSmartPtr<IRender> IRenderPtr;


/** @interface */
/** 
* 扩展专题接口
*/
class CARTO_DLL IExtRender : public IRender
{
public:

	/**
	* 获得扩展专题名
	* @return 扩展专题名
	*/
	virtual const std::string& GetExtRenderName();

	/**
	* 获得扩展专题描述
	* @return 返回扩展专题描述
	*/
	virtual const std::string& GetExtRenderDescription();	//2007.10.23张维添加
	virtual void SetProperties( const char* PropertyName , const _variant_t& PropertyValue);//2007.11.30张维修改
	virtual _variant_t GetProperties(const char* PropertyName);

	/**
	* 复制新的专题
	* @return 返回专题
	*/
	virtual SYSTEM::CSmartPtr<IRender> CopyNewRender();

	/**
	* 序列化操作
	* @param ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);
	virtual Display::ISymbolPtr CreateSymbolFromInSideSymbolName() = 0;//2007.12.4张维添加

	/**
	* 设置页面名称
	* @param pageName 页面名称
	*/
	virtual void SetPageName(std::string pageName);

	/**
	* 获得页面名称
	* @return 页面名称
	*/
	virtual std::string GetPageName();
protected:
	IExtRender();
	std::string m_extRenderName;	//2007.10.23张维修改
	std::string m_extRenderDescription;//2007.10.23张维添加
	std::string m_pageName;
};

typedef SYSTEM::CSmartPtr<IExtRender> IExtRenderPtr;

}

#endif