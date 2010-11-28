//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  Geodatabase基础定义
//////////////////////////////////////////////////////////////////////

#ifndef _GEODATABASE_DEFINE_H_
#define _GEODATABASE_DEFINE_H_


#if defined GEODATABASE_EXPORTS
#define GEODATABASE_DLL __declspec(dllexport)
#else
#define GEODATABASE_DLL __declspec(dllimport)
#pragma comment(lib,"Geodatabase.lib")
#pragma message("Automatically linking with Geodatabase.dll")
#endif

namespace Geodatabase
{

//工作空间的类型
enum WorkspaceType
{
	WT_FileSystem =1,  //文件系统
	WT_SDE =2,       //空间数据库
};

//字段类型
enum FIELD_TYPE
{
	FTYPE_UNKNOWN,
	FTYPE_BOOL,
	FTYPE_SHORT,  
	FTYPE_LONG,
	FTYPE_FLOAT,  
	FTYPE_DOUBLE,
	FTYPE_STRING,
	FTYPE_DATE,   
	FTYPE_TIME,
	FTYPE_GEOMETRY,
	FTYPE_BLOB,
	FTYPE_RASTERBLOCK,
};

 /** 
 * 数据对象类型
 */
 enum GEODATATYPE
 {
	 GDT_UNKNOWN_TYPE, //未知类型
	 GDT_METADATA_SET, //元数据
	 GDT_TABLE,        //数据表
	 GDT_FEATURECLASS,  //矢量数据
	 GDT_FEATUREDATASET, //矢量数据目录
	 GDT_RASTERDATASET, //栅格数据集
	 GDT_RASTERCATALOG, //栅格目录
	 GDT_TINDATASET    //TIN数据
 };

 //空间查询时几何体的关系
 enum EnumSpatialRel
 {
	 SpatialRelUndefined, //未定义的关系

	 SpatialRelIntersects, //查询几何体和目标几何体相交

	 SpatialRelEnvelopeIntersects, //边界矩形相交

	 SpatialRelTouches,

	 SpatialRelOverlaps,

	 SpatialRelCrosses,

	 SpatialRelWithin,  //查询几何体在目标几何体之内

	 SpatialRelContains //查询几何体包含目标几何体

 };

 //选择集合并的操作类型
 enum SelSetOperation
 {
	 SetUnion =1, //两个选择集求合集
	 SetIntersect =2, //交集
	 SetSubtract =3, //第一个选择集减去第二个
	 SetXOR  =4,      //选择集求异或

 };

 /**栅格的数据类型 */
 enum BANDDATATYPE
 {
	 BDT_UNKNOWN , //未知
	 BDT_BIT1	, //1位
	 BDT_BYTE	, //字节型
	 BDT_USHORT	, //无符号短整型
	 BDT_SHORT	, //短整形
	 BDT_ULONG	, //无符号整形
	 BDT_LONG	, //整形
	 BDT_FLOAT	, //单精度浮点
	 BDT_DOUBLE	, //双精度浮点
	 BDT_COMPLEX //复合型


 };


struct RasFileInfo
 {
	 long		lWidth;			//图像的宽度
	 long		lHeight;		//图像的高度
	 long		lChannelNum;	//图像的通道数
	
	 long		lDataType;		//数据位数
	
	 long        lXSize;         //分块宽
	 long        lYSize;         //分块高
 };


}//namespace Geodatabase
#endif