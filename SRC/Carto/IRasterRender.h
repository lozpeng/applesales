//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/11/18
// 描述：  栅格数据层的渲染
//////////////////////////////////////////////////////////////////////

#ifndef _IRASTER_RENDER_h
#define _IRASTER_RENDER_h

#include "IDisplay.h"
#include "LegendInfo.h"

namespace Geodatabase
{
	class IRasterDataset;
}

namespace Carto
{

class  CARTO_DLL IRasterRender : public SYSTEM::ISerialization
{
public:
	IRasterRender();
	virtual ~IRasterRender();

public:

	/**
	* 对选中的记录集进行绘制
	* @param pDisplay 智能指针，指向显示接口
	* @param pRaster 栅格数据源
	*/
	virtual void Draw( Display::IDisplayPtr pDisplay,Geodatabase::IRasterDataset* pRaster) = 0;

	/**
	* 对当前专题进行序列化操作
	* @param ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	/**
	* 根据流生成专题
	* @param ar 文档流
	* @return 返回专题
	*/
	static SYSTEM::CSmartPtr<IRasterRender> CreateRenderFromStream(SYSTEM::IArchive &ar);

	/**
	* 创建专题
	* @param type 专题类型
	* @param RenderExtName 扩展专题名
	* @return 返回专题
	*/
	static SYSTEM::CSmartPtr<IRasterRender> CreateRender( RASTER_RENDER_TYPE type , std::string RenderExtName = "" );


	/**
	* 对当前Render中的栅格数据源增强显示绘制
	* @param nEnhanceMode 增强显示方法
	*/
	virtual void ApplyEnhanceDraw(const int nEnhanceMode);

	/** 
	* 对当前Render中的栅格数据源应用调色板显示
	* @param pbRed 红色通道映射值
	* @param pbGreen 绿色通道映射值
	* @param pbBlue 蓝色通道映射值
	*/
	virtual void ApplyPaletteDraw(BYTE *pbRed, BYTE *pbGreen, BYTE *pbBlue);


	virtual void SetAffineTransform(CAffineTransformPtr affineTransPtr);

	/*
	* 得到图例的信息
	*/
	virtual CLegendInfoPtr GetLegendInfo();

protected:

	
	RASTER_RENDER_TYPE m_type;

	std::string m_extRenderName;


	//渲染的栅格数据源
	Geodatabase::IRasterDataset* m_pRasterDataset;

	//用于动态投影
	CAffineTransformPtr m_pAffineTransform;


};

typedef SYSTEM::CSmartPtr<IRasterRender> IRasterRenderPtr;


	

}

#endif