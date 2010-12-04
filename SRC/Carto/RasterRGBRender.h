#ifndef _RasterRGBRender_H_
#define _RasterRGBRender_H_
#pragma once
#include "irasterrender.h"
#include "IRasterRender.h"
#include "CartoHeader.h"

#include <list>
using std::list;

namespace Carto
{
	class CARTO_DLL CRasterRGBRender : public IRasterRender
	{
	public:
		CRasterRGBRender(void);
		~CRasterRGBRender(void);
	public:
		/**
	* ��ѡ�еļ�¼�����л���
	* @param pDisplay ����ָ�룬ָ����ʾ�ӿ�
	* @param pRaster դ������Դ
	*/
	virtual void Draw( Display::IDisplayPtr pDisplay,GeodataModel::IRasterDataset* pRaster);
	protected:

		Display::IDisplayPtr m_pDisplay;

		//RGB���ε����
		long m_ShowBandIndex[3];

		//��ʾRGB��Ҷ���ʾ
		BOOL m_bRGB;

		//��ǰ���һ�εĴ������ǿ�㷨
		long				mg_lProcessMethod;

		COLORREF			mg_crStart;//����ɫ����ʼɫ

		COLORREF			mg_crEnd;//����ɫ����ʼɫ

		BOOL				mg_bStretched;//�Ƿ�Ϊ����ɫ 

		//R G B��ɫ��

		BYTE				mg_byRed[256];

		BYTE				mg_byGreen[256];

		BYTE				mg_byBlue[256];


		//͸����ʾ
		BOOL   m_bBackTrans;

		//͸��ɫ
		COLORREF  m_transColor;	

		unsigned short				m_usBrightness;		//���ȵ���ֵ0~100
		unsigned short				m_usContrastness;	//�Աȶȵ���ֵ0~100

		//ֱ��ͼ����ʱ�ĳ߶�
		float m_fStandardDeviationScale;

		PIXEL_INFO m_PixelInfo[3];

		//��Ӧ��ʾ��ԭʼ��������
		unsigned char	*mp_pucBufSrc[3];

		//��Ӧ��ʾ��ԭʼ�������ݾ��������б����õ�������
		unsigned char	*mp_pucBufPro[3];	

		//������ʾ�ĵ���Χ
		GEOMETRY::geom::Envelope m_DrawDataEnv;

		//��ǰ������
		double			mp_dblResampleRatio;	

		//���ڶ�ȡ��ʾ��ͼ�������
		long			mp_lResampleWidth;

		//���ڶ�ȡ��ʾ��ͼ�������
		long			mp_lResampleHeight;

		//�������ݳߴ�
		long          mp_lResampleBufferSize;

		//��Ļ���Ʒ�Χ
		RECT m_destRect;


		bool m_bLocked;
	};
	typedef SYSTEM::CSmartPtr<CRasterRGBRender> CRasterRGBRenderPtr;
}
#endif //_RasterRGBRender_H_
