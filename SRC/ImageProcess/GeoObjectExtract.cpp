#include "stdafx.h"
#include "GeoObjectExtract.h"
#include "RasterWSFactory.h"
#include "ShapefileWorkspaceFactory.h"
#include "IWorkspace.h"
#include "SysPath.h"
#include "IFeatureClass.h"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
namespace ImageProcess
{

static long gCurProgress;
//将提取结果转化为矢量
static bool CreateShpResult(Geodatabase::IRasterDataset* pDataset,const char *OutputFileName,int nminSize,SYSTEM::IProgress *pProgress)
{
	using namespace GEOMETRY::geom;

	std::string path =OutputFileName;
	//得到文件路径
	path =path.substr(0,path.rfind('\\'));

	Geodatabase::IWorkspace *pshpWS =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(OutputFileName);
	if(!pshpWS)
	{
		return false;
	}


	Geodatabase::FeatureClassDef fdef;
	fdef.hasz =false;

	fdef.lshptype = GEOMETRY::geom::GEOS_POLYGON;

	Geodatabase::CField *pField =new Geodatabase::CField();
	pField->SetType(Geodatabase::FTYPE_LONG);
	pField->SetName("ID");
	pField->SetLength(10);
	fdef.FieldsDef.push_back(Geodatabase::CFieldPtr(pField));

	//创建结果矢量
	Geodatabase::IFeatureClassPtr pFeatureClass =pshpWS->CreateFeatureClass(OutputFileName,fdef);

	if(!pFeatureClass)
	{
		return false;
	}

	
	pDataset->CreateBuffer();

	
    
    long lwidth,lheight;
	pDataset->GetSize(&lwidth,&lheight);

	//像素值
	unsigned char pixel;

	//种子堆栈及指针
	Seed *Seeds;
	int StackPoint;

	//当前像素位置
	int iCurrentPixelx,iCurrentPixely;

	//当前扫描区域象素总数
	const unsigned int nPixelCount=lwidth*lheight;
	//标志位
	boost::dynamic_bitset<> sbitset;
	boost::dynamic_bitset<> processbitset;
	boost::dynamic_bitset<> srcbitset;
	srcbitset.resize(nPixelCount);
	sbitset.resize(nPixelCount);
	processbitset.resize(nPixelCount);

	Seeds = new Seed[nPixelCount];

	unsigned char *lpSrc=0;

	long lpt1,lpt2,drawPt;//点在标志位中的位置
	bool bStartPoint=false; //是否起始点
	bool bPointfind=false;  //是否找到边界点
	IntPoint StartPoint; //起始格网点
	IntPoint CurPoint,RecordPt; //当前格网点

	//扫描方向,向右为0，按逆时针方向增长

	int Direction[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
	//起始方向
	int BeginDirect;

	//建立一个空的多边形要素
	GEOMETRY::geom::Geometry* pGeometry =NULL;
	Coordinate coord;

	//开始编辑
	pshpWS->StartEdit();
	pshpWS->StartEditOperation();

	Geodatabase::CFeaturePtr pFeature;

	long i,j;
	long ltotal;
	std::vector<IntPoint> points;

	//将二值图转换为掩码图
	for(j=0;j<lheight;j++)
	{
		for(i=0;i<lwidth;i++)
		{
            pDataset->PixelIO(1,i+1,j+1,&pixel,true);
			if(pixel==1)
			{
				srcbitset.set(lwidth*j+i);
			}
		}
	}
	pDataset->DeleteBuffer();
	long ltotalProgress =lwidth*lheight;
	int m,n;
	gCurProgress=0;
	for(j=0;j<lheight;j++)
	{
		for(i=0;i<lwidth;i++)
		{
			//读取该点像素值
             //pDataset->PixelIO(1,i+1,j+1,&pixel,true);
			 //如果该点没有处理，则作为种子点
			 if(srcbitset.test(lwidth*j+i) && (!processbitset.test(lwidth*j+i)))
			 {
 
				 ltotal =1;
				 sbitset.reset();
				 //初始化种子
				 
				 Seeds[0].Height = j+1;
				 Seeds[0].Width = i+1;
				 StackPoint = 0;
				 sbitset.set(lwidth*j+i);

				 while( StackPoint != -1)
				 {
					 //取出种子
					 iCurrentPixelx = Seeds[StackPoint].Width;
					 iCurrentPixely = Seeds[StackPoint].Height;
					 StackPoint--;

					 processbitset.set(lwidth*j+i);
                  
					 //取得当前指针处的像素值
					  /*pDataset->PixelIO(1,iCurrentPixelx,iCurrentPixely,&pixel,true);*/
					 
					 //判断左面的点，如果在范围内，并且没有入过栈，则压入堆栈

					 if(iCurrentPixelx > 1)
					 {
						 if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2))
						 {
							 
							 //pDataset->PixelIO(1,iCurrentPixelx-1,iCurrentPixely,&pixel,true);
							 
							 if (srcbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2))
							 {
								 StackPoint++;
								 Seeds[StackPoint].Height = iCurrentPixely;
								 Seeds[StackPoint].Width = iCurrentPixelx - 1;
								 //标志位设为1
								 sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2);
								 processbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2);

								 ltotal++;

							 }
						 }

					 }

					 //判断上面的点，如果在范围内，并且没有入过栈，则压入堆栈
					 if(iCurrentPixely > 1)
					 {
						 if(!sbitset.test(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1))
						 {
							// pDataset->PixelIO(1,iCurrentPixelx,iCurrentPixely-1,&pixel,true);
							

							 if (srcbitset.test(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1))
							 {
								 StackPoint++;
								 Seeds[StackPoint].Height = iCurrentPixely-1;
								 Seeds[StackPoint].Width = iCurrentPixelx ;
								 //标志位设为1
								 sbitset.set(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1);

								 processbitset.set(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1);
								 ltotal++;

							 }
						 }
					 }

					 //判断右面的点，如果为白，则压入堆栈

					 if(iCurrentPixelx < lwidth )
					 {
						 if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx))
						 {
							// pDataset->PixelIO(1,iCurrentPixelx+1,iCurrentPixely,&pixel,true);
							
							 if (srcbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx))
							 {
								 StackPoint++;
								 Seeds[StackPoint].Height = iCurrentPixely;
								 Seeds[StackPoint].Width = iCurrentPixelx +1;
								 //标志位设为1
								 sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx);
								 processbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx);

								 ltotal++;

							 }
						 }

					 }

					 //判断下面的点，如果为白，则压入堆栈

					 if(iCurrentPixely <lheight )
					 {
						 if(!sbitset.test(lwidth * iCurrentPixely + iCurrentPixelx-1))
						 {
							 //pDataset->PixelIO(1,iCurrentPixelx,iCurrentPixely+1,&pixel,true);
							
							 if (srcbitset.test(lwidth * iCurrentPixely + iCurrentPixelx-1))
							 {
								 StackPoint++;
								 Seeds[StackPoint].Height = iCurrentPixely+1;
								 Seeds[StackPoint].Width = iCurrentPixelx ;
								 //标志位设为1
								 sbitset.set(lwidth * iCurrentPixely + iCurrentPixelx-1);
								 processbitset.set(lwidth * iCurrentPixely + iCurrentPixelx-1);

								 ltotal++;

							 }
						 }

					 }
				 }

				 //判断这个区域包含的点数目是否小于最小阈值
				 if(ltotal>=nminSize)
				 {
					 bStartPoint =false;
					 
					 //将这区域矢量化
					 points.clear();
					 //找到左上角的一个边界点
					 for(n=0;n<lheight;n++)
					 {
						 for(m=0;m<lwidth;m++)
						 {
							 //如果找到边界点
							 if(sbitset.test(lwidth*n+m))
							 {
								 //设置为起始格网点
								 StartPoint.x=m;
								 StartPoint.y=n;
								 bStartPoint=true;
								 break;
							 }
						 }
						 if(bStartPoint)
						 {
							 break;
						 }
					 }
					 if(bStartPoint)
					 {
						 //设当前点为起始格网点
						 CurPoint.x=StartPoint.x;
						 CurPoint.y=StartPoint.y;
						 points.push_back(CurPoint);

						 //初始扫描方向为下方
						 BeginDirect=3;
						 bStartPoint=false;


						 while(!bStartPoint)
						 {
							 bPointfind=false;
							 while(!bPointfind)
							 {
								 //如果扫描方向朝下
								 if(3==BeginDirect)
								 {
									 lpt1=lwidth*CurPoint.y+CurPoint.x-1;
									 lpt2=lwidth*CurPoint.y+CurPoint.x;
								 }
								 //扫描方向朝上
								 else if(1==BeginDirect)
								 {
									 lpt1=lwidth*(CurPoint.y-1)+CurPoint.x-1;
									 lpt2=lwidth*(CurPoint.y-1)+CurPoint.x;
								 }
								 //扫描方向朝右
								 else if(0==BeginDirect)
								 {
									 lpt1=lwidth*(CurPoint.y-1)+CurPoint.x;
									 lpt2=lwidth*CurPoint.y+CurPoint.x;
								 }
								 //扫描方向朝左
								 else if(2==BeginDirect)
								 {
									 lpt1=lwidth*(CurPoint.y-1)+CurPoint.x-1;
									 lpt2=lwidth*CurPoint.y+CurPoint.x-1;
								 }


								 //考虑格网点在图像边界的情况
								 //格网点是左边界点，并且扫描方向是上下方向
								 if(CurPoint.x==0 && (1==BeginDirect || 3==BeginDirect))
								 {

									 if(sbitset.test(lpt2))
									 {
										 bPointfind=true;
										 drawPt=lpt2;
									 }

								 }
								 //格网点是右边界点,并且扫描方向是上下方向
								 else if(CurPoint.x==lwidth-1 &&(1==BeginDirect || 3==BeginDirect))
								 {

									 if(sbitset.test(lpt1))
									 {
										 bPointfind=true;
										 drawPt=lpt1;
									 }

								 }
								 //格网点是上边界点,并且扫描方向是左右方向
								 else if(CurPoint.y==0 &&(0==BeginDirect || 2==BeginDirect))
								 {
									 if(sbitset.test(lpt2))
									 {
										 bPointfind=true;
										 drawPt=lpt2;
									 }
								 }
								 //格网点是下边界点,并且扫描方向是左右方向
								 else if(CurPoint.y==lheight-1 &&(0==BeginDirect || 2==BeginDirect))
								 {
									 if(sbitset.test(lpt1))
									 {
										 bPointfind=true;
										 drawPt=lpt1;
									 }
								 }
								 //格网点是普通情况
								 else
								 {
									 if( sbitset.test(lpt1) ^ sbitset.test(lpt2) )
									 {
										 bPointfind=true;
										 if(sbitset.test(lpt1))
										 {
											 drawPt=lpt1;
										 }
										 else
										 {
											 drawPt=lpt2;
										 }
									 }
								 }
								 //如果是边界点
								 if(bPointfind)
								 {
									 CurPoint.x=CurPoint.x+Direction[BeginDirect][0];
									 CurPoint.y=CurPoint.y+Direction[BeginDirect][1];
									 //如果回到起始点，退出循环
									 if(CurPoint.x==StartPoint.x && CurPoint.y==StartPoint.y)
									 {
										 bStartPoint=true; 

									 }
									 //记录边界点
									 /* RecordPt.x =drawPt%lwidth;
									 RecordPt.y =drawPt/lwidth;*/
									 points.push_back(CurPoint);


									 //逆时针方向旋转1格
									 BeginDirect++;
									 if(BeginDirect==4)
									 {
										 BeginDirect=0;
									 }


								 }
								 //如果这一方向没有找到，则改变扫描方向
								 else
								 {
									 BeginDirect--;
									 if(BeginDirect==-1)
									 {
										 BeginDirect=3;
									 }

								 }
							 }
						 }

						 if(points.size()>4)
						 {
							 typedef std::vector<GEOMETRY::geom::Coordinate> CoordVect;
							 pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();


							 CoordVect *pcoords =new CoordVect(points.size());
							 for(int k=0;k<points.size();k++)
							 {
								 pDataset->PixelToWorld(points[k].x,points[k].y,&coord.x,&coord.y);
								 (*pcoords)[k] =coord;
							 }


							 CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
							 LinearRing *pring = GeometryFactory::getDefaultInstance()->createLinearRing(coords);

							 ((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry((Geometry*)pring);

							 //产生一个新的要素
							 pFeature =pFeatureClass->CreateFeature();
							 pFeature->SetShape( pGeometry);

							 //提交要素
							 pFeatureClass->AddFeature(pFeature.get());
						 }

					 }
				 }
					

				 //将区域的点标志为已经处理
                /* for(int k=0;k<nPixelCount;k++)
				 {
					 if(sbitset.test(k))
					 {
                         processbitset.set(k);
					 }
				 }*/
			 }

             if(pProgress)
			 {
				 gCurProgress++;
				 
				pProgress->UpdateProgress("",0.3+0.7*(double(gCurProgress))/(double)ltotalProgress);
				 
			 }
			 
		}
	}
	pshpWS->StopEditOperation();
	pshpWS->StopEdit(true);

	if(Seeds)
	{
		delete []Seeds;
	}
	

	
	return true;
}

bool WaterExtract(const char *InputFileName, const char *OutputFileName,std::vector<GEOMETRY::geom::Polygon*> &samples,int nminsize,SYSTEM::IProgress *pProgress)
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

	//建立进度条
	if(pProgress)
	{
		pProgress->Create("处理中",SYSTEM::IProgress::Percent,100);
		pProgress->UpdateProgress("",0.01);

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

	long ltotalProgress =lband*lFileHeight*lFileHeight;
    gCurProgress =0;

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

	
	if(pProgress)
	{
		pProgress->UpdateProgress("",0.1);
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

	if(pProgress)
	{
		pProgress->UpdateProgress("",0.2);
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
	if(pProgress)
	{
		pProgress->UpdateProgress("",0.1);
	}
    //生成shp
    bool bret =CreateShpResult(rasDestDS.get(),OutputFileName,nminsize,pProgress);

	if(pProgress)
	{
		pProgress->UpdateProgress("",1.0);
		pProgress->Close();
	}

	return bret;
}




}