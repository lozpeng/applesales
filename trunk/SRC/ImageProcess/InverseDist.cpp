#include "StdAfx.h"
#include "InverseDist.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"
namespace ImageProcess
{

using namespace std;

static GEOMETRY::geom::Envelope CalExtent(std::vector<double> &dxs,std::vector<double> &dys)
{
	double xmin=1e30,xmax=-1e30,ymin=1e30,ymax=-1e30;
	for(size_t i=0;i<dxs.size();i++)
	{
		if(dxs[i]<xmin)
		{
			xmin=dxs[i];
		}
		if(dxs[i]>xmax)
		{
			xmax=dxs[i];
		}

		if(dys[i]<ymin)
		{
			ymin=dys[i];
		}
		if(dys[i]>ymax)
		{
			ymax=dys[i];
		}
	}

	return GEOMETRY::geom::Envelope(xmin,xmax,ymin,ymax);
	

}

struct WeightAndZ
{
	WeightAndZ(double w, double zz) : weight(w), z(zz) {}
	double weight;
	double z;
};

bool CInverseDist::Run(std::vector<double> &dxs, std::vector<double> &dys, std::vector<double> &dzs,
					   double xres,double yres, double radius, const char *strout,SYSTEM::IProgress *pProgress,const char *strProName)
{

	using namespace Geodatabase;
	if(dxs.empty() ||dys.empty() ||dzs.empty())
	{
        return false;
	}
	if(!strout)
	{
		return false;
	}

	//建立进度条
	if(pProgress)
	{
		pProgress->Create(strProName,SYSTEM::IProgress::Percent,100);
		pProgress->UpdateProgress("",0.01);

	}

	GEOMETRY::geom::Envelope extent=CalExtent(dxs,dys);
	long width,height;
	width=(extent.getMaxX()-extent.getMinX())/xres;
	height=(extent.getMaxY()-extent.getMinY())/yres;

	std::string path =strout;

	path =path.substr(0,path.rfind('\\'));
	Geodatabase::IWorkspace *pdestWS =CRasterWSFactory::GetInstance()->OpenFolder(path.c_str());
	if(!pdestWS)
	{
		return false;
	}

	//影像建立
	RasFileInfo rasfileInfoDes;
	rasfileInfoDes.lWidth = width;			//图像的宽度
	rasfileInfoDes.lHeight = height;			//图像的高度
	rasfileInfoDes.lChannelNum = 1;	//图像的通道数
	rasfileInfoDes.lDataType = BDT_FLOAT;

	if(!pdestWS->CreateRasterDataset(strout,&rasfileInfoDes))
	{
		return false;
	}
	IRasterDatasetPtr rasDestDS =pdestWS->OpenRasterDataset(strout,false);


	if(!rasDestDS)
	{
		return false;
	}
	rasDestDS->CreateBuffer();

	rasDestDS->SetCoordinateExtent(extent);

	long i,j,k,totalPro=1;
	int m;
	double xpos,ypos;
	double distance = 0;
	double weight = 0;
	double totalWeight = 0;
    vector<WeightAndZ> vecWeight;
	double nodeValue;
	float fvalue;
	for(i=1;i<=height;i++)
	{
		for(j=1;j<=width;j++)
		{
            rasDestDS->PixelToWorld(j,i,&xpos,&ypos);

			vecWeight.clear();

			totalWeight=0;

			nodeValue=0;

			for(k=0;k<dxs.size();k++)
			{
				distance = ::sqrt((::pow((xpos - dxs[k]), 2) + ::pow((ypos - dys[k]), 2)));
				if(distance == 0) 
				{
					nodeValue=dzs[k];
					break;
				}
				
				if(distance > radius) 
				{
					
					continue;
				}

				weight = 1 / ::pow(distance, 4);
				vecWeight.push_back(WeightAndZ(weight, dzs[k]));

				totalWeight += weight;
				
			}
			for(m=0; m<vecWeight.size(); m++)
			{

				vecWeight[m].weight /= totalWeight;
			}
			for(m=0; m<vecWeight.size(); m++) 
			{
				nodeValue += vecWeight[m].weight * vecWeight[m].z;
				
			}
			fvalue=nodeValue;

			rasDestDS->PixelIO(1, j , i, &fvalue, false);

			totalPro++;

			if(pProgress)
			{
				pProgress->UpdateProgress("",1.0*totalPro/(height*width));
			}
		}
	
	
	}
    
	rasDestDS->DeleteBuffer();

	if(pProgress)
	{
		pProgress->UpdateProgress("",1.0);
		pProgress->Close();
	}

	return true;


}


}
