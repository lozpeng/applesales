//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  Geodatabase��������
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

//�����ռ������
enum WorkspaceType
{
	WT_FileSystem =1,  //�ļ�ϵͳ
	WT_SDE =2,       //�ռ����ݿ�
};

//�ֶ�����
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
 * ���ݶ�������
 */
 enum GEODATATYPE
 {
	 GDT_UNKNOWN_TYPE, //δ֪����
	 GDT_METADATA_SET, //Ԫ����
	 GDT_TABLE,        //���ݱ�
	 GDT_FEATURECLASS,  //ʸ������
	 GDT_FEATUREDATASET, //ʸ������Ŀ¼
	 GDT_RASTERDATASET, //դ�����ݼ�
	 GDT_RASTERCATALOG, //դ��Ŀ¼
	 GDT_TINDATASET    //TIN����
 };

 //�ռ��ѯʱ������Ĺ�ϵ
 enum EnumSpatialRel
 {
	 SpatialRelUndefined, //δ����Ĺ�ϵ

	 SpatialRelIntersects, //��ѯ�������Ŀ�꼸�����ཻ

	 SpatialRelEnvelopeIntersects, //�߽�����ཻ

	 SpatialRelTouches,

	 SpatialRelOverlaps,

	 SpatialRelCrosses,

	 SpatialRelWithin,  //��ѯ��������Ŀ�꼸����֮��

	 SpatialRelContains //��ѯ���������Ŀ�꼸����

 };

 //ѡ�񼯺ϲ��Ĳ�������
 enum SelSetOperation
 {
	 SetUnion =1, //����ѡ����ϼ�
	 SetIntersect =2, //����
	 SetSubtract =3, //��һ��ѡ�񼯼�ȥ�ڶ���
	 SetXOR  =4,      //ѡ�������

 };

 /**դ����������� */
 enum BANDDATATYPE
 {
	 BDT_UNKNOWN , //δ֪
	 BDT_BIT1	, //1λ
	 BDT_BYTE	, //�ֽ���
	 BDT_USHORT	, //�޷��Ŷ�����
	 BDT_SHORT	, //������
	 BDT_ULONG	, //�޷�������
	 BDT_LONG	, //����
	 BDT_FLOAT	, //�����ȸ���
	 BDT_DOUBLE	, //˫���ȸ���
	 BDT_COMPLEX //������


 };


struct RasFileInfo
 {
	 long		lWidth;			//ͼ��Ŀ��
	 long		lHeight;		//ͼ��ĸ߶�
	 long		lChannelNum;	//ͼ���ͨ����
	
	 long		lDataType;		//����λ��
	
	 long        lXSize;         //�ֿ��
	 long        lYSize;         //�ֿ��
 };


}//namespace Geodatabase
#endif