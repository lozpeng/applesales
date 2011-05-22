//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2010/11/15
  // 描述：  数据层的接口定义，其它地理数据层（栅格、矢量等层）均由其派生
//////////////////////////////////////////////////////////////////////


#ifndef _ILayer_H
#define _ILayer_H

#include <Geometry/geom/Envelope.h>
#include "IGeoDataObject.h"
#include "IDisplay.h"
#include "SimpleQuery.h"
#include "AffineTransform.h"
#include "LegendInfo.h"

namespace GEOMETRY
{
	namespace geom
	{
		class Geometry;
		class Envelope;
	}
}

namespace Carto 
{
	class CARTO_DLL ILayer : public SYSTEM::ISerialization
	{
	public:
public:
	ILayer();
	virtual ~ILayer();

public:
	/**
	* 获得逻辑图层类型
	* @return 返回逻辑图层类型
	*/
	LAYER_TYPE GetLayerType() { return m_layerType; }

	/**
	* 加载数据图层至逻辑图层
	* @param pDataObject 数据对象
	* @return 若加载成功则返回true，否则为false
	*/
	virtual bool SetData(Geodatabase::IGeodataObjectPtr pDataObject);

	/**
	* 绘制
	* @param pDisplay 显示
	* @param content = eDCGeometry 默认为几何体
	* @return 
	*/
	virtual void Draw(Display::IDisplayPtr pDisplay,DRAW_CONTENT content = drawAll);

	/**
	* 获得图层名
	* @return 返回图层名
	*/
	std::string GetName() { return m_Name; }

	/**
	* 设置图层名
	* @param Name 图层名
	*/
	void SetName(std::string Name) { m_Name = Name;}

	/**
	* 获得图层信息
	* @return 返回图层描述信息
	*/
	std::string GetLayerDesciption() { return m_csDescription; }

	/**
	* 设置图层信息
	* @param csDescription 图层信息
	*/
	virtual void SetLayerDescription(std::string csDescription) { m_csDescription = csDescription;}

	/**
	* 获得地理范围
	* @return 地理范围
	*/
	virtual GEOMETRY::geom::Envelope GetEnvelope();

	/**
	* 序列化操作
	* @param System::IArchive &ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	/**
	* 选择图层中某个集合，根据条件产生选择集
	* @param query 查询条件
	* @return 
	*/
	virtual void Select(Geodatabase::CSimpleQuery* query, SELECT_OPTION selectOption = SELECT_REPLACE);

	virtual void ClearSelectionSet()=0;

	/**
	* 从流创建图层
	* @param ar 文档流
	* @return 若创建成功则为图层，失败为NULL
	*/
	static SYSTEM::CSmartPtr<ILayer> CreateLayerFromStream( SYSTEM::IArchive &ar );

	/**
	* 创建图层
	* @param pDataObject 数据对象
	* @return 若创建成功则为图层，失败为NULL
	*/
	static SYSTEM::CSmartPtr<ILayer> CreateLayer(Geodatabase::IGeodataObjectPtr pDataObject);

	/**
	* 获得显示状态
	* @return 若为true则为显示，false为隐藏
	*/
	BOOL GetVisible() { return m_bVisible; }

	/**
	* 设置显示状态
	* @param bVisible true则为显示，false为隐藏
	*/
	void SetVisible(bool bVisible) { m_bVisible = bVisible; }

	/**
	* 获得数据图层
	* @return 若获取成功为数据图层，否则为NULL
	*/
	Geodatabase::IGeodataObjectPtr GetDataObject(void) 
	{ 
		return m_pDataObject;
	}

	/**
	* 获得透明值 
	* @return 返回透明值
	*/
	unsigned short GetTransparentValue() { return m_TransparentAlphaValue; }

	/**
	* 设置透明值
	* @param TransparentValue 透明值
	*/
	void SetTransparent(unsigned short TransparentValue) { m_TransparentAlphaValue=TransparentValue; }

	/**
	* 设置能否进行比例尺范围的设置
	* @param bFlag 若为true则可以设置，false为不可以设置
	*/
	void SetEnableScaleRange(bool bFlag) { m_bScaleRange=bFlag;}

	/**
	* 获得比例尺范围设置的状态
	* @return true则可以设置，false为不可以设置
	*/
	bool GetEnableScaleRange() { return m_bScaleRange; }

	/**
	* 设置比例尺最大范围
	* @param double dScaleMax
	* @return 
	*/
	void SetScaleRangeMax(double dScaleMax) { m_dScaleMax = dScaleMax;}

	/**
	* 设置比例尺最小范围
	* @param double dScaleMin
	* @return 
	*/
	void SetScaleRangeMin(double dScaleMin) { m_dScaleMin = dScaleMin;}

	/**
	* 获得比例尺最大范围
	* @return 
	*/
	double GetScaleRangeMax() { return m_dScaleMax; }

	/**
	* 获得比例尺最小范围
	* @return 
	*/
	double GetScaleRangeMin() { return m_dScaleMin; }

	/**
	* 绘制之前做的处理
	* @return 
	*/
	virtual void BeforeDraw(SYSTEM::CSmartPtr<Display::IDisplay> pDisplay);

	/**
	* 绘制之后做的处理
	* @return 
	*/
	virtual void AfterDraw(SYSTEM::CSmartPtr<Display::IDisplay> pDisplay);

	/*
	设置图层显示顺序
	*/
	void SetLayerPosition(LAYER_POSITION pos);

	LAYER_POSITION GetLayerPostion();

	//auxiliary Layer
	void AddAuxiliaryLayer(SYSTEM::CSmartPtr<ILayer> ptrLayer);

	bool RemoveAuxiliaryLayer(SYSTEM::CSmartPtr<ILayer> ptrLayer);

	bool IsAuxiliaryLayerExist(SYSTEM::CSmartPtr<ILayer> ptrLayer);

	SYSTEM::CSmartPtr<ILayer> GetAuxiliaryLayer(long index);

	long GetAuxiliaryLayerCount();

	CAffineTransformPtr GetAffineTransPtr(){return m_pAffineTransform;}

	/*
	* 得到图例的信息
	*/
	virtual CLegendInfoPtr GetLegendInfo();

public:
	
	//获取/设置图层是否拥有自己独立的显示缓存
	virtual void		get_Cached(bool& bCached);
	virtual void		set_Cached(bool bCached);
	//获取/设置图层缓存ID
	virtual void		get_CacheId(short& sId);
	virtual void		set_CacheId(short sId);


protected:

	//layer name
	std::string m_Name;

	//is visible
	bool m_bVisible;

	//layer description
	std::string m_csDescription;

	//layer's data object
	Geodatabase::IGeodataObjectPtr m_pDataObject;

	//layer type
	LAYER_TYPE m_layerType;

	//transparent 
	unsigned short m_TransparentAlphaValue; // 透明度0~100

	//layer visible range
	bool m_bScaleRange;
	double m_dScaleMax,m_dScaleMin;

	//layer position
	LAYER_POSITION m_Position;

	//auxiliary layers
	std::vector<SYSTEM::CSmartPtr<ILayer>> m_auxiliaryLayers;

	//仿射变换
	CAffineTransformPtr m_pAffineTransform;
protected:
	short				m_sCachedId;			//缓存ID
	bool				m_bCached;				//图层是否拥有缓存

	};

	typedef SYSTEM::CSmartPtr<ILayer> ILayerPtr; //layer智能指针

}
#endif