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

	//删除rgn
	for(int i=0;i<rgns.size();i++)
	{
		::DeleteObject(rgns[i]);
	}
	return true;
}

}