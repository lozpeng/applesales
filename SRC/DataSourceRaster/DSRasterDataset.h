//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.7
// ������  GDALդ�����ݼ�
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
	* �����Ƿ��д
	* @return ��д����true,���򷵻�false
	*/
	virtual bool IsWritable();

	/**
	* �õ�������Ŀ
	* @return ������Ŀ
	*/
	virtual long GetBandCount();


	//�õ����ݼ��ķ�Χ��pEnvelop�Ƿ��صķ�Χ
	virtual bool GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const;

	/**
	* �õ�ͼ��ĳ���
	* @ ����plWidth��ָ��,���ڷ���ͼ����� 
	* @ ����plHeight��ָ��,���ڷ���ͼ��߶�
	* @return �ɹ�����true,ʧ�ܷ���false
	*/
	virtual bool GetSize(long *plWidth, long *plHeight);

	/**
	* �õ���Ԫ�ķֱ���
	* @ ����pdblSizeX��ָ��,���ڷ���ͼ��X����ķֱ��� 
	* @ ����pdblSizeY��ָ��,���ڷ���ͼ��Y����ķֱ��� 
	* @return �ɹ�����true,ʧ�ܷ���false
	*/
	virtual bool GetCellSize (double *pdblSizeX, double *pdblSizeY);

	/**
	* �õ�ָ�����ε���������
	* @����lChannelIndex���������
	* @return ������������
	*/
	virtual Geodatabase::BANDDATATYPE GetBandDataType(long lChannelIndex);

	
	/**
	* ��ȡ�򿪵�ͼ��һ��ͨ�������ֵ����Сֵ
	* @����lChannelIndex���������
	* @����pvMaxValue�����ص����ֵ
	* @����pvMinValue�����ص���Сֵ
	* @return ������������
	*/
	virtual	bool GetBandMinMaxValue(long lChannelIndex, void *pvMaxValue, void *pvMinValue);


	/**
	* ����ͼ��ĵ�����Χ
	* @����extent���µĵ�����Χ
	* @return �ɹ�����true,ʧ�ܷ���false
	*/
	virtual bool SetCoordinateExtent(const GEOMETRY::geom::Envelope &extent);

	
	/**
	* ��������ת��Ϊ��������
	* @����dblX����������X
	* @����dblX����������Y
	* @����plRow���������������к�
	* @����plCol���������������к�
	* @return �ɹ�����true,ʧ�ܷ���false
	*/
	virtual bool WorldToPixel (double dblX, double dblY, long *plCol,long *plRow);

	
	/**
	* ��������ת��Ϊ��������
	* @����lRow�����ص��к�
	* @����lCol�����ص��к�
	* @����pdblX�������������X
	* @����pdblY�������������Y
	* @return �ɹ�����true,ʧ�ܷ���false
	*/
	virtual bool PixelToWorld (long lCol, long lRow, double *pdblX, double *pdblY);


	/**
	* ��ȡͼ��ͶӰ�ַ���
	* @return ͶӰ�ַ���wkt
	*/
	virtual std::string GetProjection();

	/**
	* ���ô򿪵�ͼ���ͶӰ��Ϣ
	* @����pszWKT: ͶӰ�ַ���
	* @return �ɹ�����true,ʧ�ܷ���false
	*/
	virtual	bool SetProjection(const char *pszWKT);


	/**
	* ��ȡ�򿪵�ͼ��һ��ͨ����ָ���С��е�����ֵ
	* @����lBandlIndex��ͨ����
	* @����lRow�����ص��к�
	* @����lCol: ���ص��к�
    * @����pvValue: ����ֵ
	* @return �ɹ�����true,ʧ�ܷ���false
	*/
	virtual	bool    GetPixel(long lBandlIndex, long lCol, long lRow, void *pvValue);

	/**
	* ����ͼ��һ��ͨ����ָ���С��е�����ֵ
	* @����lBandlIndex��ͨ����
	* @����lRow�����ص��к�
	* @����lCol: ���ص��к�
	* @����pvValue: ����ֵ
	* @return �ɹ�����true,ʧ�ܷ���false
	*/
	virtual	bool	SetPixel(long lBandlIndex, long lCol,long lRow,  void *pvValue);

	
	bool DataReadBandNormalize(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer,double& minValue,double& maxValue);

	bool DataReadBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, void *pvBuffer);

	bool DataWriteBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, void *pvBuffer);



	/*@*****************************������������ؽӿ�********************************************@*/


	/**
	* ͼ���Ƿ��н�����
	* @return ����н���������true,û�з���false
	*/
	virtual	bool	HasPyramid();
	
	//����������
	bool BuildPyramid(double dResample);

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



private:
	GDALDataset	*m_pDataset;

	bool m_bReadOnly;

	long m_lBand;



};







#endif