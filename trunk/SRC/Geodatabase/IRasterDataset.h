//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  栅格数据集的基类
//////////////////////////////////////////////////////////////////////

#ifndef  _IRASTERDATASET_H_
#define  _IRASTERDATASET_H_

#include "IGeodataObject.h"
#include "IProgress.h"

namespace GEOMETRY
{
	namespace geom
	{
		class Coordinate;
	}
}
namespace Geodatabase
{

	class IRasterCatalog;

class GEODATABASE_DLL IRasterDataset: public IGeodataObject
{
public:
	IRasterDataset(IWorkspace *pWorkspace,IRasterCatalog *pRasterCatalog);
	virtual ~IRasterDataset();

public:
	
	/**
	* 返回数据集所在的栅格目录指针
	* @return 返回IRasterCatalog的指针
	*/
	IRasterCatalog* GetRasterCatalog() const {return m_pRasterCatalog;}

	
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
	virtual BANDDATATYPE GetBandDataType(long lChannelIndex);

	
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

	
	virtual bool DataReadBandNormalize(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer,double& minValue,double& maxValue);

	virtual bool DataReadBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, void *pvBuffer);

	virtual bool DataWriteBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, void *pvBuffer);



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

	

protected:

	IRasterCatalog *m_pRasterCatalog;
};


typedef  SYSTEM::CSmartPtr<IRasterDataset> IRasterDatasetPtr;



}




#endif