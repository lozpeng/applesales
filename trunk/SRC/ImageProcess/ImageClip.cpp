#include "stdafx.h"
#include "ImageClip.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"
namespace ImageProcess
{

#define XtoCol(dblX, lWidth, stExtent) ((dblX - stExtent.xmin) / (stExtent.xmax - stExtent.xmin) * (lWidth))
#define	YtoRow(dblY, lHeight, stExtent) (lHeight - (dblY - stExtent.ymin) / (stExtent.ymax - stExtent.ymin) * (lHeight))


bool ImgClip(const char* pszInFile, 
	const char* pszOutFile, 
	GEOMETRY::geom::Envelope& aoiExtent,
	double dblCellX,
	double dblCellY)
{
	using namespace Geodatabase;
	long     lWidth1, lHeight1, lWidth2, lHeight2;
	long     lChannelCount, lDataType;
	STExtent stExtent1;

	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(pszInFile);
	if(!pSrcWp)
	{
		return false;
	}
	//打开原文件
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(pszInFile);
	if(!pSrcRS)
	{
		return false;
	}
	//输入影像
	
	GEOMETRY::geom::Envelope env;
	pSrcRS->CreateBuffer();
	pSrcRS->GetExtent(&env);
	stExtent1.xmax =env.getMaxX();
	stExtent1.xmin =env.getMinX();
	stExtent1.ymax =env.getMaxY();
	stExtent1.ymin =env.getMinY();

	pSrcRS->GetSize(&lWidth1, &lHeight1);
	lChannelCount =pSrcRS->GetBandCount();
	
	lDataType =(long)pSrcRS->GetBandDataType(1);


	//重采样后图像的范围计算
	lWidth2 = (long)(aoiExtent.getWidth()/dblCellX + 0.5);
	lHeight2 = (long)(aoiExtent.getHeight()/dblCellY + 0.5);
	
	//获取目标文件文件夹路径
	std::string path =pszOutFile;

	path =path.substr(0,path.rfind('\\'));
	Geodatabase::IWorkspace *pdestWS =CRasterWSFactory::GetInstance()->OpenFolder(path.c_str());
	if(!pdestWS)
	{
		return false;
	}

	//重采样影像建立
	RasFileInfo rasfileInfoDes;
	rasfileInfoDes.lWidth = lWidth2;			//图像的宽度
	rasfileInfoDes.lHeight = lHeight2;			//图像的高度
	rasfileInfoDes.lChannelNum = lChannelCount;	//图像的通道数
	rasfileInfoDes.lDataType = lDataType;

	if(!pdestWS->CreateRasterDataset(pszOutFile,&rasfileInfoDes))
	{
		return false;
	}
    IRasterDatasetPtr rasDestDS =pdestWS->OpenRasterDataset(pszOutFile,false);


	if(!rasDestDS)
	{
		return false;
	}
	rasDestDS->CreateBuffer();

	rasDestDS->SetCoordinateExtent(aoiExtent);

	//图像重采样开始
	BYTE byValue = 0;
	unsigned short usValue = 0;
	short sValue = 0;
	float fValue = 0.0;
	double lon,lat;
	double dblx2, dbly2;
	double dblPixelPosX,dblPixelPosY;
	int k =0;
	//进度条
	int i,j;
	for (long m =0; m < lChannelCount; m++)
	{
		k = m+1;

		dbly2 = aoiExtent.getMaxY() - dblCellY/2;
		for ( i = 0; i < lHeight2; i++)
		{
			
			dblx2 = aoiExtent.getMinX() + dblCellX/2;
			for ( j = 0; j < lWidth2; j++)
			{
				lon=dblx2;
				lat=dbly2;

				dblPixelPosX = XtoCol(lon,lWidth1,stExtent1);
				dblPixelPosY = YtoRow(lat,lHeight1,stExtent1);

				switch((BANDDATATYPE)lDataType)
				{
				case BDT_BYTE:
					{
						pSrcRS->PixelIO(k,dblPixelPosX+0.5,dblPixelPosY+0.5,&byValue,true);

						rasDestDS->PixelIO(m+1, j+1 , i+1, &byValue, false);
					}
					break;
				case BDT_SHORT:
					{
						

						pSrcRS->PixelIO(k,dblPixelPosX+0.5,dblPixelPosY+0.5,&sValue,true);

						rasDestDS->PixelIO(m+1, j+1 , i+1, &sValue, false);
					}
					break;
				case BDT_USHORT:
					{

						pSrcRS->PixelIO(k,dblPixelPosX+0.5,dblPixelPosY+0.5,&usValue,true);

						rasDestDS->PixelIO(m+1, j+1 , i+1, &usValue, false);
					}
					break;
				case BDT_FLOAT:
					{
						pSrcRS->PixelIO(k,dblPixelPosX+0.5,dblPixelPosY+0.5,&fValue,true);

						rasDestDS->PixelIO(m+1, j+1 , i+1, &fValue, false);
					}
					break;
				default:
					break;
				}
				dblx2 += dblCellX;
			}

			dbly2 -= dblCellY;
		}
	}


	pSrcRS->DeleteBuffer();
;
	rasDestDS->DeleteBuffer();


	return true;
}


}