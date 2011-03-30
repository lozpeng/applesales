#include "stdafx.h"
#include "MagicStick.h"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

namespace ImageProcess
{

//种子，用来标记位置
typedef struct{
	int Height;
	int Width;
}Seed;

GEOMETRY::geom::Polygon *MagicStick(Geodatabase::IRasterDataset* pDataset,int x,int y,unsigned char rate)
{

	using namespace GEOMETRY::geom;
    long lwidth,lheight;
	pDataset->GetSize(&lwidth,&lheight);
	if(x<=0 || x>lwidth)
	{
		return NULL;
	}
	if(y<=0 || y>lheight)
	{
		return NULL;
	}
	long lband =pDataset->GetBandCount();
	unsigned char *pRed,*pGreen,*pBlue;
	pRed =pGreen =pBlue =NULL;
	long lstartx,lstarty,lendx,lendy;
	long half =700;
	lstartx =(x-half>0)?(x-half):1;
	lstarty =(y-half>0)?(y-half):1;
	lendx =(x+half<=lwidth)?(x+half):lwidth;
	lendy =(y+half<=lheight)?(y+half):lheight;

	double dmin,dmax;
	long lbufferx,lbuffery;
	lbufferx =lendx-lstartx+1;
	lbuffery =lendy-lstarty+1;
	unsigned char value;
	int posx =x-lstartx+1;
	int posy =y-lstarty+1;
	if(lband>=3)
	{

		pRed =new unsigned char[lbufferx*lbuffery];
		pDataset->GetBandMinMaxValue(1,&dmax,&dmin);
		pDataset->DataReadBandNormalize(1,lstartx,lstarty,lendx-lstartx+1,lendy-lstarty+1,lendx-lstartx+1,lendy-lstarty+1,pRed,dmin,dmax);

		pGreen =new unsigned char[lbufferx*lbuffery];
		pDataset->GetBandMinMaxValue(2,&dmax,&dmin);
		pDataset->DataReadBandNormalize(2,lstartx,lstarty,lendx-lstartx+1,lendy-lstarty+1,lendx-lstartx+1,lendy-lstarty+1,pGreen,dmin,dmax);

		pBlue =new unsigned char[lbufferx*lbuffery];
		pDataset->GetBandMinMaxValue(3,&dmax,&dmin);
		pDataset->DataReadBandNormalize(3,lstartx,lstarty,lendx-lstartx+1,lendy-lstarty+1,lendx-lstartx+1,lendy-lstarty+1,pBlue,dmin,dmax);

		value =((int)pRed[(posy-1)*lbufferx+posx-1]+(int)pGreen[(posy-1)*lbufferx+posx-1]+(int)pBlue[(posy-1)*lbufferx+posx-1])/3;

	}
	else
	{
		pRed =new unsigned char[lbufferx*lbuffery];
		pDataset->GetBandMinMaxValue(1,&dmin,&dmax);
		pDataset->DataReadBandNormalize(1,lstartx,lstarty,lendx-lstartx+1,lendy-lstarty+1,lendx-lstartx+1,lendy-lstarty+1,pRed,dmin,dmax);

		value =pRed[(posy-1)*lbufferx+posx-1];
	}

	std::vector<IntPoint> points;

    AreaIncrease(pRed,pGreen,pBlue,lbufferx,lbuffery,x-lstartx+1,y-lstarty+1,value,rate,points);
	if(points.size()<4)
	{
		return NULL;
	}
	//建立一个空的多边形要素
	typedef std::vector<GEOMETRY::geom::Coordinate> CoordVect;
	Geometry *pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();
    Coordinate coord;

	CoordVect *pcoords =new CoordVect(points.size()+1);
	for(int i=0;i<points.size();i++)
	{
		pDataset->PixelToWorld(lstartx+points[i].x,lstarty+points[i].y,&coord.x,&coord.y);
		(*pcoords)[i] =coord;
	}
	(*pcoords)[points.size()] =(*pcoords)[0];

	CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
	LinearRing *pring = GeometryFactory::getDefaultInstance()->createLinearRing(coords);

	((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry((Geometry*)pring);



	if(pRed)
	{
		delete []pRed;
	}
	if(pGreen)
	{
		delete []pGreen;
	}
	if(pBlue)
	{
		delete []pBlue;
	}

    return ((GEOMETRY::geom::Polygon*)pGeometry);   
}


bool AreaIncrease(unsigned char *pRed,unsigned char *pGreen,unsigned char *pBlue,long lwidth,long lheight,int x,int y,unsigned char value,unsigned char rate,std::vector<IntPoint> &points)
{
	//标志是否是单波段
	bool bsingle=false;
	if(0==pGreen && 0==pBlue)
	{
		bsingle=true;
	}


	if(value>255-rate )
		value=255-rate;
	if(value<rate)
		value=rate;

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
	sbitset.resize((lwidth+2)*(lheight+2));

	//初始化种子
	Seeds = new Seed[nPixelCount];
	Seeds[0].Height = y;
	Seeds[0].Width = x;
	StackPoint = 0;
	sbitset.set(lwidth*(y-1)+x-1);

	//单波段时的情况
	if(bsingle)
	{
		unsigned char *lpSrc=0;

		while( StackPoint != -1)
		{
			//取出种子
			iCurrentPixelx = Seeds[StackPoint].Width;
			iCurrentPixely = Seeds[StackPoint].Height;
			StackPoint--;

			lpSrc = pRed + lwidth * (iCurrentPixely-1) + iCurrentPixelx-1;
			//取得当前指针处的像素值
			pixel = *lpSrc;

			//将当前点涂亮
			/**lpSrc = (unsigned char)255;*/

			//判断左面的点，如果在范围内，并且没有入过栈，则压入堆栈

			if(iCurrentPixelx > 1)
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2))
				{
					lpSrc = pRed + lwidth * (iCurrentPixely-1) + iCurrentPixelx-2;
					//取得当前指针处的像素值
					pixel =*lpSrc;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely;
						Seeds[StackPoint].Width = iCurrentPixelx - 1;
						//标志位设为1
						sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2);

					}
				}

			}

			//判断上面的点，如果在范围内，并且没有入过栈，则压入堆栈
			if(iCurrentPixely > 1)
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1))
				{
					lpSrc = pRed+lwidth * (iCurrentPixely-2) + iCurrentPixelx-1;
					//取得当前指针处的像素值
					pixel =*lpSrc;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely-1;
						Seeds[StackPoint].Width = iCurrentPixelx ;
						//标志位设为1
						sbitset.set(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1);

					}
				}
			}

			//判断右面的点，如果为白，则压入堆栈

			if(iCurrentPixelx < lwidth )
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx))
				{
					lpSrc = pRed + lwidth * (iCurrentPixely-1) + iCurrentPixelx;
					//取得当前指针处的像素值
					pixel =*lpSrc;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely;
						Seeds[StackPoint].Width = iCurrentPixelx +1;
						//标志位设为1
						sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx);

					}
				}

			}

			//判断下面的点，如果为白，则压入堆栈

			if(iCurrentPixely <lheight )
			{
				if(!sbitset.test(lwidth * iCurrentPixely + iCurrentPixelx-1))
				{
					lpSrc = pRed+lwidth * iCurrentPixely + iCurrentPixelx-1;
					//取得当前指针处的像素值
					pixel =*lpSrc;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely+1;
						Seeds[StackPoint].Width = iCurrentPixelx ;
						//标志位设为1
						sbitset.set(lwidth * iCurrentPixely + iCurrentPixelx-1);

					}
				}

			}
		}
	}
	//多波段的情况
	else
	{
		unsigned char *lpSrcR=0;
		unsigned char *lpSrcG=0;
		unsigned char *lpSrcB=0;
		long lmove;
		while( StackPoint != -1)
		{
			//取出种子
			iCurrentPixelx = Seeds[StackPoint].Width;
			iCurrentPixely = Seeds[StackPoint].Height;
			StackPoint--;

			lmove=lwidth * (iCurrentPixely-1) + iCurrentPixelx-1;
			lpSrcR = pRed + lmove;
			lpSrcG = pGreen + lmove;
			lpSrcB = pBlue + lmove;
			//取得当前指针处的像素值
			pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

			//将当前点涂亮
			/**lpSrcR = (unsigned char)255;
			*lpSrcG = (unsigned char)255;
			*lpSrcB = (unsigned char)255;*/
			//判断左面的点，如果在范围内，并且没有入过栈，则压入堆栈

			if(iCurrentPixelx > 1)
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2))
				{
					lmove=lwidth * (iCurrentPixely-1) + iCurrentPixelx-2;
					lpSrcR = pRed + lmove;
					lpSrcG = pGreen + lmove;
					lpSrcB = pBlue + lmove;
					//取得当前指针处的像素值
					pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely;
						Seeds[StackPoint].Width = iCurrentPixelx - 1;
						//标志位设为1
						sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2);

					}
				}

			}

			//判断上面的点，如果在范围内，并且没有入过栈，则压入堆栈
			if(iCurrentPixely > 1)
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1))
				{
					lmove=lwidth * (iCurrentPixely-2) + iCurrentPixelx-1;
					lpSrcR = pRed + lmove;
					lpSrcG = pGreen + lmove;
					lpSrcB = pBlue + lmove;
					//取得当前指针处的像素值
					pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely-1;
						Seeds[StackPoint].Width = iCurrentPixelx ;
						//标志位设为1
						sbitset.set(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1);

					}
				}
			}

			//判断右面的点，如果为白，则压入堆栈

			if(iCurrentPixelx < lwidth )
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx))
				{
					lmove=lwidth * (iCurrentPixely-1) + iCurrentPixelx;
					lpSrcR = pRed + lmove;
					lpSrcG = pGreen + lmove;
					lpSrcB = pBlue + lmove;
					//取得当前指针处的像素值
					pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely;
						Seeds[StackPoint].Width = iCurrentPixelx +1;
						//标志位设为1
						sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx);

					}
				}

			}

			//判断下面的点，如果为白，则压入堆栈

			if(iCurrentPixely <lheight )
			{
				if(!sbitset.test(lwidth * iCurrentPixely + iCurrentPixelx-1))
				{
					lmove=lwidth * iCurrentPixely + iCurrentPixelx-1;
					lpSrcR = pRed + lmove;
					lpSrcG = pGreen + lmove;
					lpSrcB = pBlue + lmove;
					//取得当前指针处的像素值
					pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely+1;
						Seeds[StackPoint].Width = iCurrentPixelx ;
						//标志位设为1
						sbitset.set(lwidth * iCurrentPixely + iCurrentPixelx-1);

					}
				}

			}
		}
	}

	/*****************************************************************************
	*边界跟踪
	*
	*****************************************************************************/
	long lpt1,lpt2,drawPt;//点在标志位中的位置
	int i,j;
	bool bStartPoint=false; //是否起始点
	bool bPointfind=false;  //是否找到边界点
	IntPoint StartPoint; //起始格网点
	IntPoint CurPoint,RecordPt; //当前格网点

	//扫描方向,向右为0，按逆时针方向增长

	//int Direction[8][2]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
	int Direction[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
	//起始方向
	int BeginDirect;

	//找到左上角的一个边界点
	for(j=0;j<lheight;j++)
	{
		for(i=0;i<lwidth;i++)
		{
			//如果找到边界点
			if(sbitset.test(lwidth*j+i))
			{
				//设置为起始格网点
				StartPoint.x=i;
				StartPoint.y=j;
				bStartPoint=true;
				break;
			}
		}
		if(bStartPoint)
		{
			break;
		}
	}
	//设当前点为起始格网点
	CurPoint.x=StartPoint.x;
	CurPoint.y=StartPoint.y;

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
			else if(CurPoint.x==lwidth &&(1==BeginDirect || 3==BeginDirect))
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
			else if(CurPoint.y==lheight &&(0==BeginDirect || 2==BeginDirect))
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
				RecordPt.x =drawPt%lwidth;
				RecordPt.y =drawPt/lwidth;
				points.push_back(RecordPt);

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

	//释放堆栈
	delete []Seeds;

	return true;



}


}