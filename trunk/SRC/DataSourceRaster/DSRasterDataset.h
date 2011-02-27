//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.7
// 描述：  GDAL栅格数据集
//////////////////////////////////////////////////////////////////////

#ifndef _DS_RASTERDATASET_H_
#define _DS_RASTERDATASET_H_

#include "IRasterDataset.h"
#include "gdal_priv.h"
class CRasterWorkspace;


class  CDSRasterDataset: public Geodatabase::IRasterDataset
{
	friend class CRasterWorkspace;
public:
	CDSRasterDataset(CRasterWorkspace *pWorkspace,GDALDataset *pDataset,bool bRead,const char *name);
	virtual ~CDSRasterDataset();
public:


	/**
	* 数据是否可写
	* @return 可写返回true,否则返回false
	*/
	virtual bool IsWritable();

	/**
	* 得到波段数目
	* @return 波段数目
	*/
	virtual long GetBandCount();


	//得到数据集的范围，pEnvelop是返回的范围
	virtual bool GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const;

	/**
	* 得到图像的长宽
	* @ 参数plWidth，指针,用于返回图像宽度 
	* @ 参数plHeight，指针,用于返回图像高度
	* @return 成功返回true,失败返回false
	*/
	virtual bool GetSize(long *plWidth, long *plHeight);

	/**
	* 得到象元的分辨率
	* @ 参数pdblSizeX，指针,用于返回图像X方向的分辨率 
	* @ 参数pdblSizeY，指针,用于返回图像Y方向的分辨率 
	* @return 成功返回true,失败返回false
	*/
	virtual bool GetCellSize (double *pdblSizeX, double *pdblSizeY);

	/**
	* 得到指定波段的数据类型
	* @参数lChannelIndex：波段序号
	* @return 波段数据类型
	*/
	virtual Geodatabase::BANDDATATYPE GetBandDataType(long lChannelIndex);

	
	/**
	* 获取打开的图像一个通道的最大值与最小值
	* @参数lChannelIndex：波段序号
	* @参数pvMaxValue：返回的最大值
	* @参数pvMinValue：返回的最小值
	* @return 波段数据类型
	*/
	virtual	bool GetBandMinMaxValue(long lChannelIndex, double *pvMaxValue, double *pvMinValue);


	/**
	* 设置图像的地理范围
	* @参数extent：新的地理范围
	* @return 成功返回true,失败返回false
	*/
	virtual bool SetCoordinateExtent(const GEOMETRY::geom::Envelope &extent);

	
	/**
	* 地理坐标转化为像素坐标
	* @参数dblX：地理坐标X
	* @参数dblX：地理坐标Y
	* @参数plRow：输出像素坐标的行号
	* @参数plCol：输出像素坐标的列号
	* @return 成功返回true,失败返回false
	*/
	virtual bool WorldToPixel (double dblX, double dblY, long *plCol,long *plRow);

	
	/**
	* 像素坐标转化为地理坐标
	* @参数lRow：像素的行号
	* @参数lCol：像素的列号
	* @参数pdblX：输出地理坐标X
	* @参数pdblY：输出地理坐标Y
	* @return 成功返回true,失败返回false
	*/
	virtual bool PixelToWorld (long lCol, long lRow, double *pdblX, double *pdblY);


	/**
	* 获取图像投影字符串
	* @return 投影字符串wkt
	*/
	virtual std::string GetProjection();

	/**
	* 设置打开的图像的投影信息
	* @参数pszWKT: 投影字符串
	* @return 成功返回true,失败返回false
	*/
	virtual	bool SetProjection(const char *pszWKT);


	/**
	* 获取打开的图像一个通道的指定行、列的像素值
	* @参数lBandlIndex：通道号
	* @参数lRow：像素的行号
	* @参数lCol: 像素的列号
    * @参数pvValue: 像素值
	* @return 成功返回true,失败返回false
	*/
	virtual	bool    GetPixel(long lBandlIndex, long lCol, long lRow, void *pvValue);

	/**
	* 设置图像一个通道的指定行、列的像素值
	* @参数lBandlIndex：通道号
	* @参数lRow：像素的行号
	* @参数lCol: 像素的列号
	* @参数pvValue: 像素值
	* @return 成功返回true,失败返回false
	*/
	virtual	bool	SetPixel(long lBandlIndex, long lCol,long lRow,  void *pvValue);

	
	bool DataReadBandNormalize(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer,double& minValue,double& maxValue);

	bool DataReadBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, void *pvBuffer);

	bool DataWriteBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, void *pvBuffer);


	/*@*****************************获得调色板、LUT等信息的接口*********************************@*/

	/**
	* 获取打开的图像一个通道的调色板信息
	* @参数lChannelIndex: 波段号
	* @参数pbRed:   调色板红波段的值
	* @参数pbGreen: 调色板绿波段的值
	* @参数pbBlue:  调色板蓝波段的值
	* @return 成功返回true,失败返回false
	*/
	virtual	bool    GetChannelPalette(long lChannelIndex, BYTE *pbRed, BYTE *pbGreen, BYTE *pbBlue);

	/**
	* 设置打开的图像一个通道的调色板信息
	* @参数lChannelIndex: 波段号
	* @参数pbRed:   调色板红波段的值
	* @参数pbGreen: 调色板绿波段的值
	* @参数pbBlue:  调色板蓝波段的值
	* @return 成功返回true,失败返回false
	*/
	virtual	bool	SetChannelPalette(long lChannelIndex, BYTE *pbRed, BYTE *pbGreen, BYTE *pbBlue);

	/**
	* 获取打开的图像一个通道的 LUT 信息
	* @参数lChannelIndex: 波段号
	* @参数pbLUT:   LUT值
	* @参数plNodesCount: 节点的数目
	* @参数pstPts:  节点的坐标
	* @return 成功返回true,失败返回false
	*/
	virtual	bool	GetChannelLUT(long lChannelIndex, BYTE *pbLUT, long *plNodesCount = NULL, GEOMETRY::geom::Coordinate* pstPts = NULL);

	/**
	* 设置打开的图像一个通道的 LUT 信息
	* @参数lChannelIndex: 波段号
	* @参数pbLUT:   LUT值
	* @参数plNodesCount: 节点的数目
	* @参数pstPts:  节点的坐标
	* @return 成功返回true,失败返回false
	*/
	virtual	bool	SetChannelLUT(long lChannelIndex, BYTE *pbLUT, long lNodesCount = 0, GEOMETRY::geom::Coordinate* pstPts = NULL);

	/*@*****************************金字塔操作相关接口********************************************@*/


	/**
	* 图像是否有金字塔
	* @return 如果有金字塔返回true,没有返回false
	*/
	virtual	bool	HasPyramid();
	
	//建立金字塔
	bool BuildPyramid(double dResample,SYSTEM::IProgress* pProgress);

	bool DataReadPyramidBand(long lLevel, long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight,long lBuffSizeX, long lBuffSizeY, void *pvBuffer);


	bool GetPyramidSize( long lLevel, long *lWidth, long *lHeight);

	bool GetPyramidCellSize(long lLevel, double *pdCellX, double *pdCellY);

	bool GetPyramidLevelNum(long *lLevelNum);

	bool ReadPyramidNormal(long lLevel,long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer);


private:

	void Init();

	template<class T>
	bool ReadNormal(T dummyTemp,long lBandIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, BYTE *pbBuffer,double dminValue,double dmaxValue );

	template<class T>
	bool PyramidNormal(T dummyTemp,long lLevel,long lBandIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, BYTE *pbBuffer,double dminValue,double dmaxValue);

	template<class T>
	bool ComputeMinMax(long lBandIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, void *pbBuffer,double *pMin,double *pMax);

private:
	GDALDataset	*m_pDataset;

	bool m_bReadOnly;

	long m_lBand;

	double *m_pdMins;
	double *m_pdMaxs;



};







#endif