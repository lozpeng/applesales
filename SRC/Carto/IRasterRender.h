//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/18
// ������  դ�����ݲ����Ⱦ
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
	* ��ѡ�еļ�¼�����л���
	* @param pDisplay ����ָ�룬ָ����ʾ�ӿ�
	* @param pRaster դ������Դ
	*/
	virtual void Draw( Display::IDisplayPtr pDisplay,Geodatabase::IRasterDataset* pRaster) = 0;

	/**
	* �Ե�ǰר��������л�����
	* @param ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	/**
	* ����������ר��
	* @param ar �ĵ���
	* @return ����ר��
	*/
	static SYSTEM::CSmartPtr<IRasterRender> CreateRenderFromStream(SYSTEM::IArchive &ar);

	/**
	* ����ר��
	* @param type ר������
	* @param RenderExtName ��չר����
	* @return ����ר��
	*/
	static SYSTEM::CSmartPtr<IRasterRender> CreateRender( RASTER_RENDER_TYPE type , std::string RenderExtName = "" );


	/**
	* �Ե�ǰRender�е�դ������Դ��ǿ��ʾ����
	* @param nEnhanceMode ��ǿ��ʾ����
	*/
	virtual void ApplyEnhanceDraw(const int nEnhanceMode);

	/** 
	* �Ե�ǰRender�е�դ������ԴӦ�õ�ɫ����ʾ
	* @param pbRed ��ɫͨ��ӳ��ֵ
	* @param pbGreen ��ɫͨ��ӳ��ֵ
	* @param pbBlue ��ɫͨ��ӳ��ֵ
	*/
	virtual void ApplyPaletteDraw(BYTE *pbRed, BYTE *pbGreen, BYTE *pbBlue);


	virtual void SetAffineTransform(CAffineTransformPtr affineTransPtr);

	/*
	* �õ�ͼ������Ϣ
	*/
	virtual CLegendInfoPtr GetLegendInfo();

protected:

	
	RASTER_RENDER_TYPE m_type;

	std::string m_extRenderName;


	//��Ⱦ��դ������Դ
	Geodatabase::IRasterDataset* m_pRasterDataset;

	//���ڶ�̬ͶӰ
	CAffineTransformPtr m_pAffineTransform;


};

typedef SYSTEM::CSmartPtr<IRasterRender> IRasterRenderPtr;


	

}

#endif