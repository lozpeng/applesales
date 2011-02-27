#include "StdAfx.h"
#include "RasterRGBRender.h"
#include "IRasterDataset.h"
#include "ImgProFunction.h"
#include "RasterLUTAlgorithm.h"
#include "DIB.h"

namespace Carto
{
	template<class T>
	static float Nearest(T*p1,float lRow,float lCol,long width,long height)
	{
		if((int)lRow <0 || (int)lRow > height - 1 || (int)lCol <0 || (int)lCol > width - 1)return 0;
		else
			return p1[(int)lRow * width + (int)lCol];
	}

	/*�Ŵ���ʾ״̬�µ��ز�������
	* @ param  drawExtent�����������Χ
	* @ param  lResampleWidth lResampleHeight �������ȣ��߶�
	* @ param  pucBufDraw ���������ʾ���ݿ�
	* @ param  dataExtent ��ȡ���ݿ����Χ
	* @ param  lDataWidth lDataHeight ��ȡ���ݿ��ȣ��߶�
	* @ param  pucBufData ��ȡ���ݿ�
	*/
	static void Resample(GEOMETRY::geom::Envelope drawExtent,long lResampleWidth,long lResampleHeight,unsigned char*pucBufDraw,GEOMETRY::geom::Envelope dataExtent,long lDataWidth,long lDataHeight,unsigned char*pucBufData)
	{
		double drawXSize = (drawExtent.getMaxX() - drawExtent.getMinX()) / lResampleWidth;
		double drawYSize = (drawExtent.getMaxY() - drawExtent.getMinY()) / lResampleHeight;

		double dataXSize = (dataExtent.getMaxX() - dataExtent.getMinX()) / lDataWidth;
		double dataYSize = (dataExtent.getMaxY() - dataExtent.getMinY()) / lDataHeight;

		//�ز��� �Ѷ�ȡ�������������ʾ����
		float xPos,yPos;
		for (int i=1;i<=lResampleHeight;i++)
		{
			for (int j=1;j<=lResampleWidth;j++)
			{

				xPos = (drawExtent.getMinX() + (j-0.5)*drawXSize - dataExtent.getMinX()) / dataXSize;
				yPos = (dataExtent.getMaxY() - (drawExtent.getMaxY() - (i)*drawYSize)) / dataYSize;

				pucBufDraw[(i-1)*lResampleWidth+(j-1)] = Nearest(pucBufData,yPos,xPos,lDataWidth,lDataHeight);

			}
		}

	}

	CRasterRGBRender::CRasterRGBRender(void)
	{
		m_type = RASTER_RGBRENDER;
		m_bLocked = false;
		mp_pucBufSrc[0] = NULL;
		mp_pucBufSrc[1] = NULL;
		mp_pucBufSrc[2] = NULL;

		mp_pucBufPro[0] = NULL;
		mp_pucBufPro[1] = NULL;
		mp_pucBufPro[2] = NULL;
		m_pDisplay = NULL;

		memset(m_ShowBandIndex,1,sizeof(long)*3);

		m_bRGB = FALSE;

		m_bBackTrans = FALSE;

		m_transColor = RGB(0,0,0);


		m_usBrightness = 50;
		m_usContrastness = 45;

		mg_crStart = RGB(0, 0, 0);

		mg_crEnd = RGB(255, 255, 255);

		mg_bStretched = TRUE;

		for (int i = 0; i < 256; i ++)
		{
			mg_byRed[i] = i;
			mg_byGreen[i] = i;
			mg_byBlue[i] = i;
		}

		for (int i=0; i<3; i++)
		{
			this->m_PixelInfo[i].Min = 0;
			this->m_PixelInfo[i].Max = 0;
		}
		m_fStandardDeviationScale = 1.5;

		mp_dblResampleRatio = 1.0;	

		mp_lResampleWidth = 0;

		mp_lResampleHeight = 0;

		mp_lResampleBufferSize = 0;
	}
	CRasterRGBRender::~CRasterRGBRender(void)
	{
		if (NULL != mp_pucBufSrc[0])
		{
			delete[] mp_pucBufSrc[0];
			mp_pucBufSrc[0] = NULL;
		}
		if (NULL != mp_pucBufSrc[1])
		{
			delete[] mp_pucBufSrc[1];
			mp_pucBufSrc[1] = NULL;
		}
		if (NULL != mp_pucBufSrc[2])
		{
			delete[] mp_pucBufSrc[2];
			mp_pucBufSrc[2] = NULL;
		}


		if (NULL != mp_pucBufPro[0])
		{
			delete[] mp_pucBufPro[0];
			mp_pucBufPro[0] = NULL;
		}
		if (NULL != mp_pucBufPro[1])
		{
			delete[] mp_pucBufPro[1];
			mp_pucBufPro[1] = NULL;
		}
		if (NULL != mp_pucBufPro[2])
		{
			delete[] mp_pucBufPro[2];
			mp_pucBufPro[2] = NULL;
		}
	}
	void CRasterRGBRender::Draw(Display::IDisplayPtr pDisplay, Geodatabase::IRasterDataset *pRaster)
	{
		if(!pRaster)
		{
			return;
		}

		m_pDisplay = pDisplay;

		m_pRasterDataset =pRaster;

		if (!m_bLocked)
		{
			//��ͼ�ĵ���Χ
			GEOMETRY::geom::Envelope viewExtent;
			pDisplay->GetDisplayTransformation().GetGeoBound(viewExtent);

			//����Դ�ĵ���Χ
			GEOMETRY::geom::Envelope dataExtent;
			pRaster->GetExtent(&dataExtent);

			//�����Ƿ���Ҫ��̬ͶӰ���Ƽ�����������ͼ�ϵ���ʾ��Χ
			GEOMETRY::geom::Envelope dataDrawExtent;

			//�жϷ�Χ�Ƿ��ཻ
			if(!dataExtent.intersects(viewExtent))
				return;

			//������ʾ�ĵ���Χ
			dataExtent.intersection(viewExtent,dataDrawExtent);

			RECT destRect;

			//��������ͼ�е�Ŀ�귶Χ
			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(dataDrawExtent.getMinX(),dataDrawExtent.getMinY(),destRect.left,destRect.bottom);
			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(dataDrawExtent.getMaxX(),dataDrawExtent.getMaxY(),destRect.right,destRect.top);

			if(destRect.bottom ==destRect.top || destRect.left ==destRect.right)
				return;
			m_destRect = destRect;

			m_DrawDataEnv = dataDrawExtent;

			ReadDrawData(dataDrawExtent);

		}
		DibDraw();
	}
	void CRasterRGBRender::ReadDrawData(GEOMETRY::geom::Envelope dataDrawExtent)
	{

		//����Դ�ĵ���Χ
		GEOMETRY::geom::Envelope dataExtent;
		m_pRasterDataset->GetExtent(&dataExtent);

		long left,right,top,bottom;
		//�����ȡ���ݵķ�Χ
		m_pRasterDataset->WorldToPixel(dataDrawExtent.getMinX(),dataDrawExtent.getMinY(),&left,&bottom);
		m_pRasterDataset->WorldToPixel(dataDrawExtent.getMaxX(),dataDrawExtent.getMaxY(),&right,&top);


		//��ȡ���ݵĵ���Χ
		GEOMETRY::geom::Envelope dataReadExtent;
		double xReslution,yReslution;
		m_pRasterDataset->GetCellSize(&xReslution,&yReslution);
		double xmin,xmax,ymin,ymax;
		double readWidth,readHeight;
		xmin = dataExtent.getMinX() + (left -1) * xReslution;
		ymax = dataExtent.getMaxY() - (top -1) * yReslution;
		xmax = dataExtent.getMinX() + (right) * xReslution;
		ymin = dataExtent.getMaxY() - (bottom) * yReslution;//��Χ���㵽���ص����½�
		dataReadExtent.init(xmin,xmax,ymin,ymax);

		readWidth = right-left+1;
		readHeight = bottom-top+1;

		for (;dataReadExtent.getMaxY() < dataDrawExtent.getMaxY() && dataReadExtent.getMaxY() < dataExtent.getMaxY();)
		{
			dataReadExtent.init(dataReadExtent.getMinX(),dataReadExtent.getMaxX(),dataReadExtent.getMinY(),dataReadExtent.getMaxY()+yReslution);
			readHeight+=1;
			top-=1;
		}
		for (;dataReadExtent.getMinY() > dataDrawExtent.getMinY() && dataReadExtent.getMinY() > dataExtent.getMinY();)
		{
			dataReadExtent.init(dataReadExtent.getMinX(),dataReadExtent.getMaxX(),dataReadExtent.getMinY()-yReslution,dataReadExtent.getMaxY());
			readHeight+=1;
			bottom+=1;
		}
		for (;dataReadExtent.getMaxX() < dataDrawExtent.getMaxX() && dataReadExtent.getMaxX() < dataExtent.getMaxX();)
		{
			dataReadExtent.init(dataReadExtent.getMinX(),dataReadExtent.getMaxX()+xReslution,dataReadExtent.getMinY(),dataReadExtent.getMaxY());
			readWidth+=1;
			right+=1;
		}
		for (;dataReadExtent.getMinX() > dataDrawExtent.getMinX() && dataReadExtent.getMinX() > dataExtent.getMinX();)
		{
			dataReadExtent.init(dataReadExtent.getMinX()-xReslution,dataReadExtent.getMaxX(),dataReadExtent.getMinY(),dataReadExtent.getMaxY());
			readWidth+=1;
			left-=1;
		}


		//���������
		mp_dblResampleRatio =(double)(m_destRect.right-m_destRect.left+1)/(double)(readWidth);

		mp_lResampleWidth = readWidth*(mp_dblResampleRatio) < 1.0 ? 1.0 : (readWidth*mp_dblResampleRatio);
		mp_lResampleHeight = readHeight*(mp_dblResampleRatio) < 1.0 ? 1.0 : (readHeight*mp_dblResampleRatio);
		mp_lResampleBufferSize = mp_lResampleWidth*mp_lResampleHeight;

		long lcolors =(m_bRGB)?0 :256;

		if(lcolors ==256)
		{
			if (NULL != mp_pucBufSrc[0]) 
			{
				delete[] mp_pucBufSrc[0];
				mp_pucBufSrc[0] = NULL;
			}
			if (NULL != mp_pucBufPro[0]) 
			{
				delete[] mp_pucBufPro[0];
				mp_pucBufPro[0] = NULL;
			}

			mp_pucBufSrc[0] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];
			mp_pucBufPro[0] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];

			memset(mp_pucBufSrc[0], 0, mp_lResampleWidth * mp_lResampleHeight);
			memset(mp_pucBufPro[0], 0, mp_lResampleWidth * mp_lResampleHeight);

			m_pRasterDataset->GetBandMinMaxValue(m_ShowBandIndex[0], &m_PixelInfo[0].Max, &m_PixelInfo[0].Min);
			if (mp_dblResampleRatio > 1)
			{
				unsigned char* pucTempBuf = new unsigned char[readWidth*readHeight];

				m_pRasterDataset->DataReadBandNormalize(m_ShowBandIndex[0],left,top,readWidth,readHeight,readWidth,readHeight,pucTempBuf,m_PixelInfo[0].Min,m_PixelInfo[0].Max);

				Resample(dataDrawExtent,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[0],dataReadExtent,readWidth,readHeight,pucTempBuf);

				delete[] pucTempBuf;

			}
			else
				m_pRasterDataset->DataReadBandNormalize(m_ShowBandIndex[0],left,top,readWidth,readHeight,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[0],m_PixelInfo[0].Min,m_PixelInfo[0].Max);
		}
		else
		{

			if (NULL != mp_pucBufSrc[0])
			{
				delete[] mp_pucBufSrc[0];
				mp_pucBufSrc[0] = NULL;
			}
			if (NULL != mp_pucBufSrc[1])
			{
				delete[] mp_pucBufSrc[1];
				mp_pucBufSrc[1] = NULL;
			}
			if (NULL != mp_pucBufSrc[2])
			{
				delete[] mp_pucBufSrc[2];
				mp_pucBufSrc[2] = NULL;
			}


			if (NULL != mp_pucBufPro[0])
			{
				delete[] mp_pucBufPro[0];
				mp_pucBufPro[0] = NULL;
			}
			if (NULL != mp_pucBufPro[1])
			{
				delete[] mp_pucBufPro[1];
				mp_pucBufPro[1] = NULL;
			}
			if (NULL != mp_pucBufPro[2])
			{
				delete[] mp_pucBufPro[2];
				mp_pucBufPro[2] = NULL;
			}
			mp_pucBufSrc[0] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];
			mp_pucBufSrc[1] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];
			mp_pucBufSrc[2] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];

			mp_pucBufPro[0] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];
			mp_pucBufPro[1] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];
			mp_pucBufPro[2] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];

			memset(mp_pucBufSrc[0], 0, mp_lResampleWidth * mp_lResampleHeight);
			memset(mp_pucBufPro[0], 0, mp_lResampleWidth * mp_lResampleHeight);

			memset(mp_pucBufSrc[1], 0, mp_lResampleWidth * mp_lResampleHeight);
			memset(mp_pucBufPro[1], 0, mp_lResampleWidth * mp_lResampleHeight);

			memset(mp_pucBufSrc[2], 0, mp_lResampleWidth * mp_lResampleHeight);
			memset(mp_pucBufPro[2], 0, mp_lResampleWidth * mp_lResampleHeight);

			m_pRasterDataset->GetBandMinMaxValue(m_ShowBandIndex[0], &m_PixelInfo[0].Max, &m_PixelInfo[0].Min);
			if (mp_dblResampleRatio > 1)
			{
				unsigned char* pucTempBuf = new unsigned char[readWidth*readHeight];

				m_pRasterDataset->DataReadBandNormalize(m_ShowBandIndex[0],left,top,readWidth,readHeight,readWidth,readHeight,pucTempBuf,m_PixelInfo[0].Min,m_PixelInfo[0].Max);

				Resample(dataDrawExtent,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[0],dataReadExtent,readWidth,readHeight,pucTempBuf);

				delete[] pucTempBuf;

			}
			else
				m_pRasterDataset->DataReadBandNormalize(m_ShowBandIndex[0],left,top,readWidth,readHeight,mp_lResampleWidth, mp_lResampleHeight,mp_pucBufSrc[0],m_PixelInfo[0].Min,m_PixelInfo[0].Max);

			m_pRasterDataset->GetBandMinMaxValue(m_ShowBandIndex[1], &m_PixelInfo[1].Max, &m_PixelInfo[1].Min);
			if (mp_dblResampleRatio > 1)
			{
				unsigned char* pucTempBuf = new unsigned char[readWidth*readHeight];

				m_pRasterDataset->DataReadBandNormalize(m_ShowBandIndex[1],left,top,readWidth,readHeight,readWidth, readHeight,pucTempBuf,m_PixelInfo[0].Min,m_PixelInfo[0].Max);

				Resample(dataDrawExtent,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[1],dataReadExtent,readWidth,readHeight,pucTempBuf);

				delete[] pucTempBuf;

			}
			else
				m_pRasterDataset->DataReadBandNormalize(m_ShowBandIndex[1],left,top,readWidth,readHeight,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[1],m_PixelInfo[1].Min,m_PixelInfo[1].Max);

			m_pRasterDataset->GetBandMinMaxValue(m_ShowBandIndex[2], &m_PixelInfo[2].Max, &m_PixelInfo[2].Min);
			if (mp_dblResampleRatio > 1)
			{
				unsigned char* pucTempBuf = new unsigned char[readWidth*readHeight];

				m_pRasterDataset->DataReadBandNormalize(m_ShowBandIndex[2],left,top,readWidth,readHeight,readWidth, readHeight,pucTempBuf,m_PixelInfo[0].Min,m_PixelInfo[0].Max);

				Resample(dataDrawExtent,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[2],dataReadExtent,readWidth,readHeight,pucTempBuf);

				delete[] pucTempBuf;

			}
			else
				m_pRasterDataset->DataReadBandNormalize(m_ShowBandIndex[2],left,top,readWidth,readHeight,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[2],m_PixelInfo[2].Min,m_PixelInfo[2].Max);
			/*m_pRasterDataset->DataReadBand(m_ShowBandIndex[0],top,left,readWidth,readHeight,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[0]);
			m_pRasterDataset->DataReadBand(m_ShowBandIndex[1],top,left,readWidth,readHeight,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[1]);
			m_pRasterDataset->DataReadBand(m_ShowBandIndex[2],top,left,readWidth,readHeight,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[2]);*/
		}
	}

	BOOL CRasterRGBRender::DibDraw()
	{
		if(!m_pRasterDataset)
			return FALSE;

		if(!m_pDisplay)
			return FALSE;

		if(mg_lstProFun.size()==0)
		{
			CImagePro_LutRollback* m_LutRec=new CImagePro_LutRollback;
			m_LutRec->m_pRasRender =this;
			m_LutRec->AddLUTHistroy();
			m_LutRec->m_AdjustCount = 0;
			mg_lstProFun.push_back(m_LutRec);	//�������ӵ����棬Ϊ��֧�ֻ���
		}

		long lcolors =(m_bRGB)?0 :256;

		Display::CDIB dib;

		if (!m_bRGB)
		{
			dib.Create(mp_lResampleWidth,mp_lResampleHeight,lcolors);

			dib.SetPalette(mg_byRed, mg_byGreen, mg_byBlue);

			unsigned char pLut[256];
			GetChannelLUT(m_ShowBandIndex[0], pLut);
			ApplyLut(pLut,mp_pucBufSrc[0],mp_pucBufPro[0],mp_lResampleBufferSize);

			dib.SetImgDataBW(1,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[0]);
		}
		else
		{
			dib.Create(mp_lResampleWidth,mp_lResampleHeight,lcolors);

			unsigned char pLut[3][256];

			{
				GetChannelLUT(m_ShowBandIndex[0], pLut[0]);
				ApplyLut( pLut[0], mp_pucBufSrc[0], mp_pucBufPro[0],mp_lResampleBufferSize);

				GetChannelLUT(m_ShowBandIndex[1], pLut[1]);
				ApplyLut( pLut[1], mp_pucBufSrc[1], mp_pucBufPro[1],mp_lResampleBufferSize);

				GetChannelLUT(m_ShowBandIndex[2], pLut[2]);
				ApplyLut( pLut[2], mp_pucBufSrc[2], mp_pucBufPro[2],mp_lResampleBufferSize);

			}

			ApplyImageProFunction(mp_lResampleBufferSize,mp_pucBufPro[0], mp_pucBufPro[1],mp_pucBufPro[2]);

			dib.SetImgDataBW(1,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[0]);

			dib.SetImgDataBW(2,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[1]);

			dib.SetImgDataBW(3,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[2]);
		}
		dib.Draw(m_pDisplay->GetDrawDC()->GetSafeHdc(),1,1,mp_lResampleWidth,mp_lResampleHeight,m_destRect);
		return TRUE;
	}
	bool CRasterRGBRender::UpdateBandPixelInfo(unsigned short RGBType)
	{
		if(!m_pRasterDataset)
			return false;

		/*if (!m_pRasterDataset->GetChannelStatisInfo(m_ShowBandIndex[RGBType-1],m_PixelInfo[RGBType-1].mp_pHist,&m_PixelInfo[RGBType-1].Max,&m_PixelInfo[RGBType-1].Min,&m_PixelInfo[RGBType-1].Avg,&m_PixelInfo[RGBType-1].Std))
		{
		m_PixelInfo[RGBType-1].Valid = false;
		return false;
		}	

		m_PixelInfo[RGBType-1].Valid = true;*/
		return true;
	}
	void CRasterRGBRender::SetPixelInfo(const PIXEL_INFO &pi, unsigned short RGBType)
	{
		assert(RGBType>=1 && RGBType <= 3);

		RGBType--;

		m_PixelInfo[RGBType] = pi;
	}
	BOOL CRasterRGBRender::GetBandLUT (long lChannelIndex, BYTE *pbLUT, long *plNumNodes,GEOMETRY::geom::Coordinate* pstNodes)
{

	if(NULL == m_pRasterDataset)
		return FALSE;

	if (!m_bRGB)
	{
		if ((1 != lChannelIndex))
			return FALSE;
	}
	else
	{
		if ((0 >= lChannelIndex) || (3 < lChannelIndex))
			return FALSE;
	}

	lChannelIndex --;

	return m_pRasterDataset->GetChannelLUT(m_ShowBandIndex[lChannelIndex], pbLUT, plNumNodes,pstNodes);
}

BOOL CRasterRGBRender::SetBandLUT (long lChannelIndex, BYTE *pbLUT, long lNumNodes,GEOMETRY::geom::Coordinate* pstNodes)
{

	if(NULL == m_pRasterDataset)
		return FALSE;

	if (!m_bRGB)
	{
		if ((1 != lChannelIndex))
			return FALSE;
	}
	else
	{
		if ((0 >= lChannelIndex) || (3 < lChannelIndex))
			return FALSE;
	}

	lChannelIndex --;

   if(m_pRasterDataset->SetChannelLUT(m_ShowBandIndex[lChannelIndex],pbLUT,lNumNodes,pstNodes))
   {
	   return TRUE;
   }
   else
	   return FALSE;
}

bool	CRasterRGBRender::GetChannelLUT(long lChannelIndex, BYTE *pbLUT, long *plNodesCount , GEOMETRY::geom::Coordinate* pstPts )
{
	//if(!m_pIfe)
	//{
	//	return false;
	//}
	//
	//long nodecount;
	////��ȡ�ڵ���Ŀ
	//if(!m_pIfe->GetChannelLUT(lChannelIndex,pbLUT,&nodecount,NULL))
	//{
 //      return false;
	//}
	//if(plNodesCount)
	//{
	//	*plNodesCount =nodecount;
	//}

	//if(pstPts && nodecount>0)
	//{

 //       //��ȡ�ڵ�����
 //       STPoint *points =new STPoint[nodecount];
	//	if(!m_pIfe->GetChannelLUT(lChannelIndex,pbLUT,&nodecount,points))
	//	{
	//		delete []points;
	//		return false;
	//	}
	//	for(long i=0;i<nodecount;i++)
	//	{
	//		pstPts[i].x =points[i].x;
	//		pstPts[i].y =points[i].y;
	//	}

	//}

	return true;
}

bool	CRasterRGBRender::SetChannelLUT(long lChannelIndex, BYTE *pbLUT, long lNodesCount , GEOMETRY::geom::Coordinate* pstPts )
{
	/*if(!m_pIfe)
	{
	return false;
	}
	STPoint *points =NULL;
	if(lNodesCount>0 && pstPts)
	{
	points =new STPoint[lNodesCount];
	for(long i=0;i<lNodesCount;i++)
	{
	points[i].x =pstPts[i].x;
	points[i].y =pstPts[i].y;

	}
	}
	return m_pIfe->SetChannelLUT(lChannelIndex,pbLUT,lNodesCount,points) ? true:false;*/
	return true;
}
void CRasterRGBRender::ApplyImageProFunction(long lBufLen,unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3)
{
	list<CImageProFunction*>::iterator it = mg_lstProFun.begin();


	while(it != mg_lstProFun.end())
	{
		(*(*it))(lBufLen,pChannel1, pChannel2, pChannel3);

		it++;
	}
}
}

