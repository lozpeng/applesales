#include "stdafx.h"
#include "GeoObjectExtract.h"
#include "RasterWSFactory.h"
#include "IWorkspace.h"
#include "SysPath.h"
namespace ImageProcess
{



bool WaterExtract(const char *InputFileName, const char *OutputFileName,std::vector<GEOMETRY::geom::Polygon*> &samples)
{
	using namespace Geodatabase;


	struct SampleInfo
	{
		std::vector<double> low;
		std::vector<double> high;
		std::vector<double> mean; //均值
		std::vector<double> stdval; //标准差
		long   numpoints; //像素数目

	};


	if(samples.empty())
	{
		return false;
	}
	
	
	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(InputFileName);
	if(!pSrcWp)
	{
		return false;
	}
	//打开原文件
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(InputFileName);
	if(!pSrcRS)
	{
		return false;
	}



	long lFileWidth,lFileHeight;
	pSrcRS->GetSize(&lFileWidth,&lFileHeight);

	std::string syspath =SYSTEM::CSystemPath::GetSystemPath();
	syspath+="temp";

	std::string tempfile =syspath+"\\Extract.tif";
	//分类后的影像路径
	std::string path =tempfile;
	
	//删除存在的临时文件
	_unlink(tempfile.c_str());
	
	path =path.substr(0,path.rfind('\\'));
	Geodatabase::IWorkspace *pdestWS =CRasterWSFactory::GetInstance()->OpenFolder(path.c_str());
	if(!pdestWS)
	{
		return false;
	}

	//分类影像建立
	Geodatabase::RasFileInfo rasfileInfoDes;
	rasfileInfoDes.lWidth = lFileWidth;			//图像的宽度
	rasfileInfoDes.lHeight = lFileHeight;			//图像的高度
	rasfileInfoDes.lChannelNum = 1;	//图像的通道数
	rasfileInfoDes.lDataType = (long)Geodatabase::BDT_BYTE;

	if(!pdestWS->CreateRasterDataset(tempfile.c_str(),&rasfileInfoDes))
	{
		return false;
	}
	IRasterDatasetPtr rasDestDS =pdestWS->OpenRasterDataset(tempfile.c_str(),false);

	GEOMETRY::geom::Envelope extent;
	pSrcRS->GetExtent(&extent);
    rasDestDS->SetCoordinateExtent(extent);
	if(!rasDestDS)
	{
		return false;
	}
	GEOMETRY::geom::Polygon *pg =NULL;
	std::vector<HRGN> rgns;
	HRGN hrgn;
	int numPoints;
	GEOMETRY::geom::Coordinate coord;
	//将样本多边形转变为Rgn
    for(int i=0;i<samples.size();i++)
	{
        pg =samples[i];
		if(!pg)
		{
			continue;
		}
		GEOMETRY::geom::LineString *pring =const_cast<GEOMETRY::geom::LineString*>(pg->getExteriorRing());
		if(!pring)
		{
			continue;
		}
		numPoints =pring->PointCount()-1;

		POINT* points =new POINT[numPoints];
		for(int j=0;j<numPoints;j++)
		{
            coord =pring->GetPoint(j);
			pSrcRS->WorldToPixel(coord.x,coord.y,&points[j].x,&points[j].y);
		}
		hrgn =::CreatePolygonRgn(points,numPoints,ALTERNATE);
		if(hrgn)
		{
			rgns.push_back(hrgn);
		}

	}

    long lband =pSrcRS->GetBandCount();
	pSrcRS->CreateBuffer();
	rasDestDS->CreateBuffer();
	int nclass =rgns.size();
    long i,j,k;
	BYTE byValue = 0;
	unsigned short usValue = 0;
	short sValue = 0;
	float fValue = 0.0;

	double dValue;
	std::vector<SampleInfo> sinfos;
	sinfos.resize(rgns.size());
	for(i=0;i<sinfos.size();i++)
	{
		//初始化每种样本信息
		sinfos[i].low.resize(lband,0.0);
		sinfos[i].high.resize(lband,0.0);
		sinfos[i].mean.resize(lband,0.0);
		sinfos[i].stdval.resize(lband,0.0);
		sinfos[i].numpoints =0;
	}
    
	BANDDATATYPE lDataType =pSrcRS->GetBandDataType(1);

	for(long bandid=0;bandid<lband;bandid++)
	{
		//计算每种类别的标准差
		for(i =1;i<=lFileHeight;i++)
		{
			for(j=1;j<=lFileWidth;j++)
			{

				switch((BANDDATATYPE)lDataType)
				{
				case BDT_BYTE:
					{
						pSrcRS->PixelIO(bandid+1,j,i,&byValue,true);
						dValue =byValue;
						
					}
					break;
				case BDT_SHORT:
					{
						pSrcRS->PixelIO(bandid+1,j,i,&sValue,true);
						dValue =sValue;

						
					}
					break;
				case BDT_USHORT:
					{
						pSrcRS->PixelIO(bandid+1,j,i,&usValue,true);
						dValue =usValue;
					
					}
					break;
				case BDT_FLOAT:
					{
						pSrcRS->PixelIO(bandid+1,j,i,&fValue,true);
						dValue =fValue;
					}
					break;
				default:
					break;
				}
				for(k=0;k<nclass;k++)
				{
					if (PtInRegion(rgns[k], j, i))
					{
                        sinfos[k].numpoints++;
						sinfos[k].mean[bandid]+=dValue;
						break;
					}
				}

			}
		}
	}

	//计算样本平均值
	for(i=0;i<sinfos.size();i++)
	{
		
		sinfos[i].numpoints /=lband;
		for(long bandid=0;bandid<lband;bandid++)
		{
           sinfos[i].mean[bandid]/=sinfos[i].numpoints;
		}
        
	}
    double dstd,dmean;
	//计算样本标准差
	for(long bandid=0;bandid<lband;bandid++)
	{
		for(k=0;k<nclass;k++)
		{
			dstd =0.0;
			dmean =sinfos[k].mean[bandid];
			//计算每种类别的标准差
			for(i =1;i<=lFileHeight;i++)
			{
				for(j=1;j<=lFileWidth;j++)
				{
					if (!PtInRegion(rgns[k], j, i))
					{
						continue;
					}

					switch((BANDDATATYPE)lDataType)
					{
					case BDT_BYTE:
						{
							pSrcRS->PixelIO(bandid+1,j,i,&byValue,true);
							dValue =byValue;

						}
						break;
					case BDT_SHORT:
						{
							pSrcRS->PixelIO(bandid+1,j,i,&sValue,true);
							dValue =sValue;


						}
						break;
					case BDT_USHORT:
						{
							pSrcRS->PixelIO(bandid+1,j,i,&usValue,true);
							dValue =usValue;

						}
						break;
					case BDT_FLOAT:
						{
							pSrcRS->PixelIO(bandid+1,j,i,&fValue,true);
							dValue =fValue;
						}
						break;
					default:
						break;
					}

                    dstd+=(dValue-dmean)*(dValue-dmean);



				}
			}
			dstd/=sinfos[k].numpoints;
            dstd =sqrt(dstd);
            sinfos[k].stdval[bandid] =dstd;

		}
	}

	bool bWater;
	long bandid;
	bool binSample,btemp;
	
	for(i =1;i<=lFileHeight;i++)
	{
		for(j=1;j<=lFileWidth;j++)
		{
			binSample =false;
            bWater =false;
			//判断像素在哪个样区内
			for(k=0;k<nclass;k++)
			{
				btemp =false;
				for( bandid=0;bandid<lband;bandid++)
				{
					switch((BANDDATATYPE)lDataType)
					{
					case BDT_BYTE:
						{
							pSrcRS->PixelIO(bandid+1,j,i,&byValue,true);
							dValue =byValue;

						}
						break;
					case BDT_SHORT:
						{
							pSrcRS->PixelIO(bandid+1,j,i,&sValue,true);
							dValue =sValue;


						}
						break;
					case BDT_USHORT:
						{
							pSrcRS->PixelIO(bandid+1,j,i,&usValue,true);
							dValue =usValue;

						}
						break;
					case BDT_FLOAT:
						{
							pSrcRS->PixelIO(bandid+1,j,i,&fValue,true);
							dValue =fValue;
						}
						break;
					default:
						break;
					}
					//判断像素值和平均值的差距是否小于标准差两倍
					if((abs(dValue-sinfos[k].mean[bandid]))<(sinfos[k].stdval[bandid]*2))
					{
						bWater =true;
					}
					else
					{
						bWater =false;
						break;
					}
				}
				if(bWater)
				{
					break;
				}
			}
			
			
			
			if(bWater)
			{
				byValue =1;

			}
			else
			{
				byValue =0;
			}

			rasDestDS->PixelIO(1,j,i,&byValue,false);

		}
	}


	pSrcRS->DeleteBuffer();
	rasDestDS->DeleteBuffer();
    

	//删除rgn
	for(int i=0;i<rgns.size();i++)
	{
		::DeleteObject(rgns[i]);
	}

	return true;
}

}