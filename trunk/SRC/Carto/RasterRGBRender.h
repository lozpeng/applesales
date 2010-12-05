#ifndef _RasterRGBRender_H_
#define _RasterRGBRender_H_
#pragma once
#include "irasterrender.h"
#include "IRasterRender.h"
#include "CartoHeader.h"
#include "IRasterDataset.h"

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
		virtual void Draw( Display::IDisplayPtr pDisplay,Geodatabase::IRasterDataset* pRaster);
		/** 
		* ׼�����ڻ��Ƶ�����
		* @param envelop ��ȡ�����ݿ����Χ
		*/
		void ReadDrawData(GEOMETRY::geom::Envelope dataDrawExtent);
	private:

		/**
		* ��������LUT������LUT��ʾ����
		*/
		BOOL DibDraw();
	public:
		/**
		* �����ʾ��ɫ���ε����
		* @return long
		*/
		long GetRedBandIndex() const {return m_ShowBandIndex[0];};

		/**
		* ������ʾ��ɫ���ε����
		* @param lindex �������
		*/
		void SetRedBandIndex(long lindex){m_ShowBandIndex[0] =lindex;UpdateBandPixelInfo(1);};

		/**
		* �����ʾ��ɫ���ε����
		* @return long
		*/
		long GetGreenBandIndex() const {return m_ShowBandIndex[1];};

		/**
		* ������ʾ��ɫ���ε����
		* @param lindex �������
		*/
		void SetGreenBandIndex(long lindex) {m_ShowBandIndex[1] =lindex;UpdateBandPixelInfo(2);};

		/**
		* �����ʾ��ɫ���ε����
		* @return long
		*/
		long GetBlueBandIndex() const {return m_ShowBandIndex[2];};

		/**
		* ������ʾ��ɫ���ε����
		* @param lindex �������
		*/
		void SetBlueBandIndex(long lindex) {m_ShowBandIndex[2] =lindex;UpdateBandPixelInfo(3);};

		/**
		* ���ò�ɫ��Ҷ���ʾ״̬
		*/
		void SetRGBMode(BOOL bRGB) {m_bRGB = bRGB;};

		/**
		* ��ò�ɫ��Ҷ���ʾ״̬��TRUEΪ���ɫ��ʾ��FALSEΪ�Ҷ���ʾ
		*/
		BOOL GetRGBMode() {return m_bRGB;};
		/** 
		* ��ͨ����ϸı�����ͨ��ͳ����Ϣ�ṹ
		*/
		bool UpdateBandPixelInfo(unsigned short RGBType /*R - 1,G - 2,B - 3 */);
		/** 
		* ����ĳһ��ʾͨ����ͳ����Ϣ
		* @param pi ͳ����Ϣ�ṹ��
		* @param RGBType ָ��R G B
		*/
		void SetPixelInfo(const PIXEL_INFO &pi, unsigned short RGBType/*R - 1 , G - 2 , B - 3 */ );
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
