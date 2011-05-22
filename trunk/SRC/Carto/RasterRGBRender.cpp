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

	/*放大显示状态下的重采样函数
	* @ param  drawExtent绘制区域地理范围
	* @ param  lResampleWidth lResampleHeight 采样后宽度，高度
	* @ param  pucBufDraw 采样后的显示数据块
	* @ param  dataExtent 读取数据块地理范围
	* @ param  lDataWidth lDataHeight 读取数据块宽度，高度
	* @ param  pucBufData 读取数据块
	*/
	static void Resample(GEOMETRY::geom::Envelope drawExtent,long lResampleWidth,long lResampleHeight,unsigned char*pucBufDraw,GEOMETRY::geom::Envelope dataExtent,long lDataWidth,long lDataHeight,unsigned char*pucBufData)
	{
		double drawXSize = (drawExtent.getMaxX() - drawExtent.getMinX()) / lResampleWidth;
		double drawYSize = (drawExtent.getMaxY() - drawExtent.getMinY()) / lResampleHeight;

		double dataXSize = (dataExtent.getMaxX() - dataExtent.getMinX()) / lDataWidth;
		double dataYSize = (dataExtent.getMaxY() - dataExtent.getMinY()) / lDataHeight;

		//重采样 把读取块采样到用于显示块里
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

		m_ppLut = NULL;
		/*int nCount = m_pRasterDataset->GetBandCount();
		m_ppLut = new BYTE*[nCount];
		m_nodecount = 256;
		for (int j=0; j<nCount; j++)
		{
			m_ppLut[j] =new BYTE[256];
			for (int i=0; i<256; ++i)
			{
				m_ppLut[j][i] = i;
			}
		}*/

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
		int nCount = m_pRasterDataset->GetBandCount();
		for (int i=0; i<nCount; ++i)
		{
			delete[] m_ppLut[i];
		}
		delete []m_ppLut;
		m_ppLut = NULL;
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
			//视图的地理范围
			GEOMETRY::geom::Envelope viewExtent;
			pDisplay->GetDisplayTransformation().GetGeoBound(viewExtent);

			//数据源的地理范围
			GEOMETRY::geom::Envelope dataExtent;
			pRaster->GetExtent(&dataExtent);

			//根据是否需要动态投影绘制计算数据在视图上的显示范围
			GEOMETRY::geom::Envelope dataDrawExtent;

			//判断范围是否相交
			if(!dataExtent.intersects(viewExtent))
				return;

			//数据显示的地理范围
			dataExtent.intersection(viewExtent,dataDrawExtent);

			RECT destRect;

			//计算在视图中的目标范围
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

		//数据源的地理范围
		GEOMETRY::geom::Envelope dataExtent;
		m_pRasterDataset->GetExtent(&dataExtent);

		long left,right,top,bottom;
		//计算读取数据的范围
		m_pRasterDataset->WorldToPixel(dataDrawExtent.getMinX(),dataDrawExtent.getMinY(),&left,&bottom);
		m_pRasterDataset->WorldToPixel(dataDrawExtent.getMaxX(),dataDrawExtent.getMaxY(),&right,&top);


		//读取数据的地理范围
		GEOMETRY::geom::Envelope dataReadExtent;
		double xReslution,yReslution;
		m_pRasterDataset->GetCellSize(&xReslution,&yReslution);
		double xmin,xmax,ymin,ymax;
		double readWidth,readHeight;
		xmin = dataExtent.getMinX() + (left -1) * xReslution;
		ymax = dataExtent.getMaxY() - (top -1) * yReslution;
		xmax = dataExtent.getMinX() + (right) * xReslution;
		ymin = dataExtent.getMaxY() - (bottom) * yReslution;//范围计算到像素的右下角
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


		//计算采样率
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
			mg_lstProFun.push_back(m_LutRec);	//必须增加到后面，为了支持回退
		}

		long lcolors =(m_bRGB)?0 :256;

		Display::CDIB dib;

		if (!m_bRGB)
		{
			dib.Create(mp_lResampleWidth,mp_lResampleHeight,lcolors);

			dib.SetPalette(mg_byRed, mg_byGreen, mg_byBlue);

			BYTE* pLut = new BYTE[256];
			GetChannelLUT(m_ShowBandIndex[0], pLut);
			ApplyLut(pLut,mp_pucBufSrc[0],mp_pucBufPro[0],mp_lResampleBufferSize);
			delete[] pLut;
			pLut = NULL;
			dib.SetImgDataBW(1,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[0]);
		}
		else
		{
			dib.Create(mp_lResampleWidth,mp_lResampleHeight,lcolors);

			BYTE pLut[3][256];
			BYTE** ppLut = new BYTE*[3];
			for (int i=0;i<3;++i)
			{
				ppLut[i] = new BYTE[256];
				memset(ppLut[i], 0, sizeof(BYTE)*256);
			}

			{
				GetChannelLUT(m_ShowBandIndex[0], ppLut[0]);
				ApplyLut( ppLut[0], mp_pucBufSrc[0], mp_pucBufPro[0],mp_lResampleBufferSize);

				GetChannelLUT(m_ShowBandIndex[1], ppLut[1]);
				ApplyLut( ppLut[1], mp_pucBufSrc[1], mp_pucBufPro[1],mp_lResampleBufferSize);

				GetChannelLUT(m_ShowBandIndex[2], ppLut[2]);
				ApplyLut( ppLut[2], mp_pucBufSrc[2], mp_pucBufPro[2],mp_lResampleBufferSize);

			}
			for (int i=0; i<3; ++i)
			{
				delete[] ppLut[i];
			}
			delete[] ppLut;
			ppLut = NULL;

			ApplyImageProFunction(mp_lResampleBufferSize,mp_pucBufPro[0], mp_pucBufPro[1],mp_pucBufPro[2]);

			dib.SetImgDataBW(1,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufPro[0]);

			dib.SetImgDataBW(2,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufPro[1]);

			dib.SetImgDataBW(3,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufPro[2]);
		}

		short sId = -1;
		m_pDisplay->get_ActiveCache(sId);
		long lMemDC = 0;
		m_pDisplay->get_CacheMemDC(sId, &lMemDC);
		long lDC = 0;
		lDC = m_pDisplay->GetDrawDC()->GetSafeHdc();
		RECT rc = m_pDisplay->GetDisplayTransformation().GetViewBound().GetRect();
		if (0 != lMemDC)
		{
			HBRUSH hbrush = ::CreateSolidBrush(m_pDisplay->GetBgColor());
			lDC = lMemDC;
			::FillRect((HDC)lMemDC, &rc, hbrush);
		}
		dib.Draw(lDC ,1,1,mp_lResampleWidth,mp_lResampleHeight,m_destRect);

		if (0 <= sId)
		{
			m_pDisplay->DrawCache(m_pDisplay->GetDrawDC()->GetSafeHdc(), sId, rc, rc);
			
		}

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
BOOL CRasterRGBRender::GetBandLUT (long lChannelIndex, BYTE *&pbLUT, long *plNumNodes,GEOMETRY::geom::Coordinate* pstNodes)
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

	return GetChannelLUT(m_ShowBandIndex[lChannelIndex], pbLUT, plNumNodes,pstNodes);
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

   if(SetChannelLUT(m_ShowBandIndex[lChannelIndex],pbLUT,lNumNodes,pstNodes))
   {
	   return TRUE;
   }
   else
	   return FALSE;
}

bool	CRasterRGBRender::GetChannelLUT(long lChannelIndex, BYTE *&pbLUT, long *plNodesCount , GEOMETRY::geom::Coordinate* pstPts )
{
	//if(plNodesCount)
	//{
	//	*plNodesCount = m_nodecount;
	//}

	//if(pstPts && m_nodecount>0)
	//{

 //       //获取节点坐标
	//	for(long i=0;i<m_nodecount;i++)
	//	{
	//		pstPts[i].x = i;
	//		pstPts[i].y = m_ppLut[lChannelIndex][i];
	//	}
	//}
	if (NULL == m_ppLut)
	{
		int nCount = m_pRasterDataset->GetBandCount();
		m_ppLut = new BYTE*[nCount];
		m_nodecount = 256;
		for (int j=0; j<nCount; j++)
		{
			m_ppLut[j] =new BYTE[256];
			for (int i=0; i<256; ++i)
			{
				m_ppLut[j][i] = i;
			}
		}
	}
	for(long i=0;i<m_nodecount;i++)
	{
		pbLUT[i] = m_ppLut[lChannelIndex-1][i];
	}
	return true;
}

bool	CRasterRGBRender::SetChannelLUT(long lChannelIndex, BYTE *pbLUT, long lNodesCount , GEOMETRY::geom::Coordinate* pstPts )
{
	/*if(lNodesCount>0 && pstPts)
	{
		for(long i=0;i<lNodesCount;i++)
		{
			m_ppLut[lChannelIndex][(int)pstPts[i].x] = pstPts[i].y;
		}
	}*/
	if (NULL == m_ppLut)
	{
		int nCount = m_pRasterDataset->GetBandCount();
		m_ppLut = new BYTE*[nCount];
		m_nodecount = 256;
		for (int j=0; j<nCount; j++)
		{
			m_ppLut[j] =new BYTE[256];
			for (int i=0; i<256; ++i)
			{
				m_ppLut[j][i] = i;
			}
		}
	}
	for(long i=0;i<m_nodecount;i++)
	{
		m_ppLut[lChannelIndex-1][i] = pbLUT[i];
	}
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
void CRasterRGBRender::SetBrightAndContrast(BYTE *srcRLUT,BYTE *srcGLUT,BYTE *srcBLUT,int brightVal,int contrastVal)
{
	if (brightVal == 50 && contrastVal ==50)
		return;
	
	long rChannel,gChannel,bChannel;

	rChannel=GetRedBandIndex();
	gChannel=GetGreenBandIndex();
	bChannel=GetBlueBandIndex();
	
	//计算调整后的LUT

	brightVal -= 50;
	contrastVal -=50;

	double realConVal;  //实际用于调整的对比度幅度值

	if(contrastVal < 0)
		realConVal = 1.0 + contrastVal/200.0;
	else
		realConVal = 1.0 + contrastVal/100.0;

	int pMidBriCon = int(brightVal-127*realConVal + 127);

	int iValue;
	BYTE dispRLUT[256],dispGLUT[256],dispBLUT[256];

	for( int i = 0; i< 256; i++)
	{	
		iValue = int(srcRLUT[i]*realConVal + pMidBriCon); 

		if(iValue > 255)
			dispRLUT[i] = 255;
		else if(iValue < 0)
			dispRLUT[i] = 0;
		else
			dispRLUT[i] = iValue;			

		iValue = int(srcGLUT[i]*realConVal + pMidBriCon); 

		if(iValue > 255)
			dispGLUT[i] = 255;
		else if(iValue < 0)
			dispGLUT[i] = 0;
		else
			dispGLUT[i] = iValue;	

		iValue = int(srcBLUT[i]*realConVal + pMidBriCon); 

		if(iValue > 255)
			dispBLUT[i] = 255;
		else if(iValue < 0)
			dispBLUT[i] = 0;
		else
			dispBLUT[i] = iValue;

	}

	SetBandLUT(rChannel,dispRLUT);
	SetBandLUT(gChannel,dispGLUT);
	SetBandLUT(bChannel,dispBLUT);

}

void CRasterRGBRender::SetBrightAndContrast(BYTE *srcLUT,int brightVal,int contrastVal)
{
	if (brightVal == 50 && contrastVal ==50)
		return;	

	//计算调整后的LUT

	brightVal -= 50;
	contrastVal -=50;

	double realConVal;  //实际用于调整的对比度幅度值

	if(contrastVal < 0)
		realConVal = 1.0 + contrastVal/200.0;
	else
		realConVal = 1.0 + contrastVal/100.0;

	int pMidBriCon = int(brightVal-127*realConVal + 127);

	int iValue;
	BYTE dispLUT[256];

	for( int i = 0; i< 256; i++)
	{	
		iValue = int(srcLUT[i]*realConVal + pMidBriCon); 

		if(iValue > 255)
			dispLUT[i] = 255;
		else if(iValue < 0)
			dispLUT[i] = 0;
		else
			dispLUT[i] = iValue;
	}

	SetBandLUT(1,dispLUT);

}

}

