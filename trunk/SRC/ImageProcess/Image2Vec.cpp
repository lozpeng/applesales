#include "StdAfx.h"
#include "Image2Vec.h"
#include "RasterWSFactory.h"
#include "ShapefileWorkspaceFactory.h"
#include "IWorkspace.h"
#include "SysPath.h"
#include "IFeatureClass.h"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

namespace ImageProcess
{

bool ImgClass2Shp(const char *infile,const char *outfile,unsigned char classval)
{
	using namespace GEOMETRY::geom;

	if(!infile || !outfile)
	{
		return false;
	}

	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(infile);
	if(!pSrcWp)
	{
		return false;
	}
	//打开原文件
	Geodatabase::IRasterDatasetPtr pDataset =pSrcWp->OpenRasterDataset(infile);
	if(!pDataset)
	{
		return false;
	}

	std::string path =outfile;
	//得到文件路径
	path =path.substr(0,path.rfind('\\'));

	Geodatabase::IWorkspace *pshpWS =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(outfile);
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
	Geodatabase::IFeatureClassPtr pFeatureClass =pshpWS->CreateFeatureClass(outfile,fdef);

	if(!pFeatureClass)
	{
		return false;
	}
    

	pDataset->CreateBuffer();



	long lwidth,lheight;
	pDataset->GetSize(&lwidth,&lheight);
    
	//最小矢量化区域的大小
	int nminSize=10;
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

	//将原始类别图像转换为掩码图
	for(j=0;j<lheight;j++)
	{
		for(i=0;i<lwidth;i++)
		{
			pDataset->PixelIO(1,i+1,j+1,&pixel,true);
			if(pixel==classval)
			{
				srcbitset.set(lwidth*j+i);
			}
		}
	}
	pDataset->DeleteBuffer();
	long ltotalProgress =lwidth*lheight;
	int m,n;
	
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

}