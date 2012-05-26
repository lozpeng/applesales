#include "StdAfx.h"
#include "RasterClassifyColorRender.h"
#include "DIB.h"
namespace Carto
{

CRasterClassifyColorRender::CRasterClassifyColorRender():m_nBreak(0)
{

	mp_pucBufSrc[0] = NULL;
	mp_pucBufSrc[1] = NULL;
	mp_pucBufSrc[2] = NULL;

}

CRasterClassifyColorRender::~CRasterClassifyColorRender()
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

}

void CRasterClassifyColorRender::Draw(Display::IDisplayPtr pDisplay,Geodatabase::IRasterDataset* pRaster)
{

	if(!pRaster)
	{
		return;
	}
	if(!m_pColorRamp)
	{
		return;
	}

	m_pDisplay = pDisplay;

	m_pRasterDataset =pRaster;


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

	Geodatabase::BANDDATATYPE datatype=pRaster->GetBandDataType(1);
	switch(datatype)
	{
	case Geodatabase::BDT_BYTE:
		{
			
			ReadDrawData<BYTE>(dataDrawExtent);
			break;
		}
		
	case Geodatabase::BDT_SHORT:
		{
			
			ReadDrawData<short>(dataDrawExtent);
			break;
		}
		
	case Geodatabase::BDT_USHORT:
		{
			
			ReadDrawData<unsigned short>(dataDrawExtent);
			break;
		}
		
	case Geodatabase::BDT_LONG:
		{
			
			ReadDrawData<long>(dataDrawExtent);
			break;
		}
		
	case Geodatabase::BDT_FLOAT:
		{
			
			ReadDrawData<float>(dataDrawExtent);
			break;
		}
		
	default:
		return;
		
	}
	

	
	DibDraw();
}



void CRasterClassifyColorRender::serialization(SYSTEM::IArchive &ar)
{

}

void CRasterClassifyColorRender::setColorRamp(Display::IColorRampPtr pColorRamp)
{
	if(!pColorRamp)
	{
		return;
	}
	this->m_pColorRamp=pColorRamp;
	m_pColorRamp->setSize(m_nBreak);

	//��ȡ��ɫ
	m_colorgroup.resize(m_nBreak);

	for(int i=0;i<m_nBreak;i++)
	{
		m_colorgroup[i]=m_pColorRamp->GetColor(i);
	}
	
}

template<class DataType>
void CRasterClassifyColorRender::ReadDrawData(GEOMETRY::geom::Envelope dataDrawExtent/*,DataType nulldata*/)
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

	mp_pucBufSrc[0] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];
	mp_pucBufSrc[1] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];
	mp_pucBufSrc[2] = new unsigned char[mp_lResampleWidth * mp_lResampleHeight];

	memset(mp_pucBufSrc[0], 0, mp_lResampleWidth * mp_lResampleHeight);

	memset(mp_pucBufSrc[1], 0, mp_lResampleWidth * mp_lResampleHeight);
	
	memset(mp_pucBufSrc[2], 0, mp_lResampleWidth * mp_lResampleHeight);
	

	double dmin,dmax;
	m_pRasterDataset->GetBandMinMaxValue(1, &dmax, &dmin);


	DataType *pbuffer=new DataType[mp_lResampleWidth * mp_lResampleHeight];

	//��ȡԭʼ����
	m_pRasterDataset->DataReadBand(1,left,top,readWidth,readHeight,mp_lResampleWidth,mp_lResampleHeight,pbuffer);

	double dvalue;
	int index;
	double dsegvalue=(dmax-dmin)/m_nBreak;
	for(long i=0;i<mp_lResampleWidth * mp_lResampleHeight;i++)
	{
        dvalue=(double)pbuffer[i];
		if(dvalue<dmin)
		{
			dvalue=dmin;
		}
		if(dvalue>dmax)
		{
			dvalue=dmax;
		}
		index=(dvalue-dmin)/dsegvalue;
		if(index==m_nBreak)
		{
			index=m_nBreak-1;
		}
		mp_pucBufSrc[0][i]=(unsigned char)m_colorgroup[index].red;
		mp_pucBufSrc[1][i]=(unsigned char)m_colorgroup[index].green;
		mp_pucBufSrc[2][i]=(unsigned char)m_colorgroup[index].blue;




	}
	

	if(pbuffer)
	{
		delete []pbuffer;
		pbuffer=NULL;
	}

}


bool CRasterClassifyColorRender::DibDraw()
{
	if(!m_pRasterDataset)
		return false;

	if(!m_pDisplay)
		return false;

	

	long lcolors =0;

	Display::CDIB dib;

	dib.Create(mp_lResampleWidth,mp_lResampleHeight,lcolors);

	dib.SetImgDataBW(1,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[0]);

	dib.SetImgDataBW(2,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[1]);

	dib.SetImgDataBW(3,1,1,mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc[2]);

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

	return true;
}

} //namespace Carto