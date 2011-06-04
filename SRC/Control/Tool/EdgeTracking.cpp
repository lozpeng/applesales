
#include "stdafx.h"
#include "EdgeTracking.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


namespace Control
{

#define GetResampleSize(lSize, dblRatio) (((lSize)*(dblRatio) < 1.0) ? (1) : ((long)((lSize)*(dblRatio))))

CEdgeTracking::CEdgeTracking()
{
	SeedPoint.x = 0;
	SeedPoint.y = 0;
	CurPoint.x = 0;
	CurPoint.y = 0;
	mp_pucBufSrc = NULL;
	mg_pfGradient = NULL;
	mg_pfGradientX = NULL;
	mg_pfGradientY = NULL;
}

CEdgeTracking::~CEdgeTracking()
{
	if(mg_pfGradient)
		delete []mg_pfGradient;
	if(mg_pfGradientX)
		delete []mg_pfGradientX;
	if(mg_pfGradientY)
		delete []mg_pfGradientY;
	if(mp_pucBufSrc)
		delete []mp_pucBufSrc;
}

void CEdgeTracking::InitRasData(Geodatabase::IRasterDataset* pDataset,long lChannel,GEOMETRY::geom::Envelope stDrawWorldExtent, RECT rect)
{
	m_pDataset =pDataset;

	
	mg_lChannelIndex=lChannel;
	mg_ChannelType=m_pDataset->GetBandDataType(lChannel);
	
	ReadThemeData(stDrawWorldExtent,rect);
	
	if(mg_pfGradient)
	{
		delete []mg_pfGradient;
		delete []mg_pfGradientX;
		delete []mg_pfGradientY;
		mg_pfGradientX=NULL;
		mg_pfGradientY=NULL;
		mg_pfGradient=NULL;
	}
	mg_pfGradient=new float[mp_lResampleWidth*mp_lResampleHeight];
	mg_pfGradientX=new float[mp_lResampleWidth*mp_lResampleHeight];
	mg_pfGradientY=new float[mp_lResampleWidth*mp_lResampleHeight];
	//将窗口的所有梯度计算出来
	long i,j;
	float fGradX;
	float fGradY;
	
	//计算梯度值
	float fPixelTempArray[8];
	for(i=1;i<mp_lResampleHeight-1;i++)
		for(j=1;j<mp_lResampleWidth-1;j++)
		{
			fPixelTempArray[0]=mp_pucBufSrc[mp_lResampleWidth*(i-1)+j-1];
			fPixelTempArray[1]=mp_pucBufSrc[(mp_lResampleWidth)*(i-1)+j];
			fPixelTempArray[2]=mp_pucBufSrc[(mp_lResampleWidth)*(i-1)+j+1];
			fPixelTempArray[3]=mp_pucBufSrc[(mp_lResampleWidth)*i+j-1];
			fPixelTempArray[4]=mp_pucBufSrc[(mp_lResampleWidth)*i+j+1];
			fPixelTempArray[5]=mp_pucBufSrc[(mp_lResampleWidth)*(i+1)+j-1];
			fPixelTempArray[6]=mp_pucBufSrc[(mp_lResampleWidth)*(i+1)+j];
			fPixelTempArray[7]=mp_pucBufSrc[(mp_lResampleWidth)*(i+1)+j+1];
			fGradY=fPixelTempArray[0]+2*fPixelTempArray[1]+fPixelTempArray[2]-fPixelTempArray[5]-2*fPixelTempArray[6]-fPixelTempArray[7];
			fGradX=fPixelTempArray[2]+2*fPixelTempArray[4]+fPixelTempArray[7]-fPixelTempArray[0]-2*fPixelTempArray[3]-fPixelTempArray[5];
			mg_pfGradientX[mp_lResampleWidth*(i)+j]=fGradX;
			mg_pfGradientY[mp_lResampleWidth*(i)+j]=fGradY;
			mg_pfGradient[mp_lResampleWidth*(i)+j]=sqrt(fGradX*fGradX+fGradY*fGradY);
		}
	
	//上下两条边的梯度
	for(i=1;i<mp_lResampleWidth-1;i++)
	{
		mg_pfGradient[i]=mg_pfGradient[mp_lResampleWidth+i];
		mg_pfGradient[mp_lResampleWidth*(mp_lResampleHeight-1)+i]=mg_pfGradient[mp_lResampleWidth*(mp_lResampleHeight-2)+i];
	}
	//左右两条边的梯度
	for(i=1;i<mp_lResampleHeight-1;i++)
	{
		mg_pfGradient[mp_lResampleWidth*i]=mg_pfGradient[mp_lResampleWidth*i+1];
		mg_pfGradient[mp_lResampleWidth*i+mp_lResampleWidth-1]=mg_pfGradient[mp_lResampleWidth*i+mp_lResampleWidth-1];
	}
	//四个角点的梯度
	mg_pfGradient[0]=mg_pfGradient[1];
	mg_pfGradient[mp_lResampleWidth-1]=mg_pfGradient[mp_lResampleWidth-2];
	mg_pfGradient[mp_lResampleWidth*(mp_lResampleHeight-1)]=mg_pfGradient[mp_lResampleWidth*(mp_lResampleHeight-1)+1];
	mg_pfGradient[mp_lResampleWidth*mp_lResampleHeight-1]=mg_pfGradient[mp_lResampleWidth*mp_lResampleHeight-2];

	mg_fMaxGradient=GetMaxGradient();
	
}

void CEdgeTracking::SetSeedPoint(GEOMETRY::geom::Coordinate point)
{
	SeedPoint=point;
}

void CEdgeTracking::SetCurPoint(GEOMETRY::geom::Coordinate point)
{
	CurPoint=point;
}

//寻找total cost最小的路径
//Dijkstra算法
void CEdgeTracking::GetOptimalPath(long *lCount,POINT **pPathPixel)
{
	long i,j;
	float fCurCost = 0;
	CPoint cSeedPoint;
	CPoint cCurPoint;
	m_pDataset->WorldToPixel( SeedPoint.x, SeedPoint.y, &cSeedPoint.y, &cSeedPoint.x );
	m_pDataset->WorldToPixel( CurPoint.x, CurPoint.y, &cCurPoint.y, &cCurPoint.x );
	PixelToResample( &cSeedPoint );
	PixelToResample( &cCurPoint );
	
	//选样区
	RECT rect;
	lAreaWidth = abs(cSeedPoint.x - cCurPoint.x) + 1;
	lAreaHeight = abs(cSeedPoint.y - cCurPoint.y) + 1;
	if(lAreaWidth > lAreaHeight)
		lAreaHeight = lAreaWidth;
	else
		lAreaWidth = lAreaHeight;
	rect.top = cSeedPoint.y - lAreaHeight + 1;
	rect.left = cSeedPoint.x - lAreaWidth + 1;
	rect.right = cSeedPoint.x + lAreaWidth - 1;
	rect.bottom = cSeedPoint.y + lAreaHeight - 1;
	if(rect.left < 0)
		rect.left = 0;
	if(rect.right >= mp_lResampleWidth)
		rect.right = mp_lResampleWidth - 1;
	if(rect.top < 0)
		rect.top = 0;
	if(rect.bottom >= mp_lResampleHeight)
		rect.bottom = mp_lResampleHeight - 1;
	//样区的高，宽
	lAreaHeight = (rect.bottom - rect.top) + 1;
	lAreaWidth = (rect.right - rect.left) + 1;
	
	GetActiveMaxGradient(rect);

	pbPointHaveSelected = new BOOL[lAreaWidth * lAreaHeight];
	pbPointHaveExpanded = new BOOL[lAreaWidth * lAreaHeight];
	pfTotalCost = new float[lAreaWidth * lAreaHeight];
	pDirection = new DirectionP[lAreaWidth * lAreaHeight];
	plSelectLocation = new long[lAreaWidth * lAreaHeight];
	memset(pbPointHaveSelected, 0, lAreaWidth * lAreaHeight * sizeof(pbPointHaveSelected));
	memset(pbPointHaveExpanded, 0, lAreaWidth * lAreaHeight * sizeof(pbPointHaveSelected));
	
	//从种子点开始
	long lLocation = (cSeedPoint.y - rect.top) * lAreaWidth + cSeedPoint.x - rect.left;
	long lSeedLocation = lLocation;
	pfTotalCost[lSeedLocation] = 0;
	pbPointHaveSelected[lSeedLocation] = TRUE;
	pbPointHaveExpanded[lSeedLocation] = FALSE;
	//种子点的方向指向本身
	pDirection[lSeedLocation].lFirstPointLoc = lSeedLocation;
	pDirection[lSeedLocation].lNextPointLoc = lSeedLocation;
	
	//float fMinValue=0;
	long lNeighberLoc;
	BOOL bExpanded, bSelected;
	
	long lCenterDisX, lCenterDisY;
	long lCurCol, lCurRow;
	long lNeiCol, lNeiRow;
	lCurRow = cSeedPoint.y - rect.top;
	lCurCol = cSeedPoint.x - rect.left;
	lSelectFirstPointer = 0;
	lSelectLastPointer = -1;
	
	//从cost数组中取出当前活动的，值最小的点expand
	float fLocalCost;
	long lWindowLocation, lWindowNeighberLoc;
	while(lLocation >= 0)
	{
		lWindowLocation = (lCurRow + rect.top) * mp_lResampleWidth + lCurCol + rect.left;
		//搜索点的8个邻域
		for(i=-1;i<=1;i++)
			for(j=-1;j<=1;j++)
			{
				if(!( i==0 && j==0 ))
				{
					lNeiRow = lCurRow + i;
					lNeiCol = lCurCol + j;
					lNeighberLoc = lNeiRow * lAreaWidth + lNeiCol;
					if((lNeiRow < lAreaHeight) && (lNeiRow >= 0) 
						&& (lNeiCol < lAreaWidth) && (lNeiCol>=0)) //不能超出选区
					{
						bSelected = pbPointHaveSelected[lNeighberLoc];
						bExpanded = pbPointHaveExpanded[lNeighberLoc];
						lWindowNeighberLoc = (lNeiRow + rect.top) * mp_lResampleWidth 
							                 + lNeiCol + rect.left;
						fLocalCost = GetLocalCost(lWindowLocation, lWindowNeighberLoc);
						//fLocalCost = 0.5;
						//if(abs(i) == 1 && abs(i) == 1)
						//	fLocalCost = 1.717 * fLocalCost;
						//已经搜索到的点需要重新计算cost
						if(bSelected && !bExpanded)
						{
							if(pfTotalCost[lNeighberLoc] > pfTotalCost[lLocation] + fLocalCost)
							{
								pfTotalCost[lNeighberLoc] = pfTotalCost[lLocation] + fLocalCost;
								pDirection[lNeighberLoc].lFirstPointLoc = lNeighberLoc;
								pDirection[lNeighberLoc].lNextPointLoc = lLocation;
							}
						}
						//还没有搜索到的点
						if(!bSelected && !bExpanded)
						{
							pfTotalCost[lNeighberLoc] = pfTotalCost[lLocation] + fLocalCost;
							pDirection[lNeighberLoc].lFirstPointLoc = lNeighberLoc;
							pDirection[lNeighberLoc].lNextPointLoc = lLocation;
							pbPointHaveSelected[lNeighberLoc] = TRUE;
							
							lSelectLastPointer++;
							plSelectLocation[lSelectLastPointer] = lNeighberLoc;
						}
					}
				}
			}
		pbPointHaveSelected[lLocation] = FALSE;
		pbPointHaveExpanded[lLocation] = TRUE;
		
		if(lSelectLastPointer >= lSelectFirstPointer)
		{
			lLocation = plSelectLocation[lSelectFirstPointer];
			lCurRow = lLocation / lAreaWidth;
			lCurCol = lLocation - lCurRow * lAreaWidth;
			lSelectFirstPointer++;
		}else
		{
			lLocation = -1;
		}
		
		
//		GetMinPoint(pfTotalCost, &lLocation, pbPointHaveSelected);
//		lCurRow = lLocation / lAreaWidth;
//		lCurCol = lLocation - lCurRow * lAreaWidth;
		
	}
	
	//确定路径
	long lCurLocation;
	long lNeiLoction;
	lCurLocation = (cCurPoint.y - rect.top) * lAreaWidth + cCurPoint.x - rect.left;
	lNeiLoction = pDirection[lCurLocation].lNextPointLoc;
	
	long lTotalCount = 0;
	long lBreakTag = 0;
	float fAngle;
	CPoint cTempPoint;
	CPoint cPrevPoint;
	CPoint cLastPoint;
	*lCount = 0;
	cTempPoint = cCurPoint;
	ResampleToPixel(&cTempPoint);
	(*pPathPixel)[*lCount] = cTempPoint;
	cPrevPoint = cTempPoint;
	cLastPoint = cTempPoint;
	(*lCount)++;
	lTotalCount++;
	while(lNeiLoction != lSeedLocation)
	{
		lCenterDisY = lNeiLoction / lAreaWidth;
		lCenterDisX = lNeiLoction - lCenterDisY * lAreaWidth;
		cTempPoint.x = lCenterDisX;
		cTempPoint.y = lCenterDisY;
		cTempPoint.x += rect.left;
		cTempPoint.y += rect.top;
		ResampleToPixel(&cTempPoint);
		lTotalCount++;
		lBreakTag++;
		
		if(lBreakTag >= 3)
		{
			if( !((cLastPoint.x == cPrevPoint.x) && (cLastPoint.y == cPrevPoint.y)) )
			{
				fAngle = GetAngleFromThreePoint(cLastPoint, cPrevPoint, cTempPoint);
				if(fAngle > 10)
				{
					(*pPathPixel)[*lCount] = cTempPoint;
					(*lCount)++;
					cLastPoint = cPrevPoint;
					cPrevPoint = cTempPoint;
				}
				else
				{
					cPrevPoint = cTempPoint;
				}
			}
			else
			{
				(*pPathPixel)[*lCount] = cTempPoint;
				(*lCount)++;
				cPrevPoint = cTempPoint;
			}
			lBreakTag = 0;
		}
		lCurLocation = lNeiLoction;
		lNeiLoction = pDirection[lCurLocation].lNextPointLoc;
	}
	
	cTempPoint = cSeedPoint;
	ResampleToPixel(&cTempPoint);
	(*pPathPixel)[*lCount] = cTempPoint;
	
	delete []pbPointHaveExpanded;
	delete []pbPointHaveSelected;
	delete []pfTotalCost;
	delete []pDirection;
	delete []plSelectLocation;
}

//通过连续的3个点计算这3个点连线的夹角
float CEdgeTracking::GetAngleFromThreePoint(const CPoint& pt1, const CPoint& pt2, const CPoint& pt3)
{
	float fAngle;
	float a,b,c;
	a=sqrt(float((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y)));
	b=sqrt(float((pt3.x-pt2.x)*(pt3.x-pt2.x)+(pt3.y-pt2.y)*(pt3.y-pt2.y)));
	c=sqrt(float((pt1.x-pt3.x)*(pt1.x-pt3.x)+(pt1.y-pt3.y)*(pt1.y-pt3.y)));
	float fTemp=(a*a+b*b-c*c)/(2*a*b);
	if(fTemp>1)
		fTemp=1;
	if(fTemp<-1)
		fTemp=-1;
	fAngle=acos(fTemp);
	fAngle=180*fAngle/3.1415926;
	fAngle=180-fAngle;
	return fAngle;
}

//从现有点集中选择cost最小的点
float CEdgeTracking::GetMinPoint(const float *pfTotalCost,long *lLocaotion,const BOOL *pbHaveSearch)
{
	float fMinValue=0;
	long i;
	BOOL bHaveInit=FALSE;
	
	for(i=0;i<lAreaWidth*lAreaHeight;i++)
	{
		if(pbHaveSearch[i]==TRUE)
		{
			if(bHaveInit==FALSE)
			{
				fMinValue=pfTotalCost[i];
				*lLocaotion=i;
			}else
			{
				if(pfTotalCost[i]<fMinValue)
				{
					fMinValue=pfTotalCost[i];
					*lLocaotion=i;
				}
			}
			bHaveInit=TRUE;
		}
	}
	
	if(bHaveInit==FALSE)
		*lLocaotion=-1;       //所有点都已经expanded
	
	return fMinValue;
}

//点p到q的cost
//l(p,q)=wZ*fZ(q)+wD*fD(p,q)+wG*fG(q)
//其中wZ=0.43,wD=0.43,wG=0.14
float CEdgeTracking::GetLocalCost(const POINT& PreversePoint, const POINT& NextPoint)
{
	float fLocalCost=0.0;
	float fPreverseGrad,fNextGrad;
	long lPrevRow,lPrevCol,lNextRow,lNextCol;
	lPrevCol=PreversePoint.x-(SeedPoint.x-lAreaWidth);
	lPrevRow=PreversePoint.y-(SeedPoint.y-lAreaHeight);
	lNextCol=NextPoint.x-(SeedPoint.x-lAreaWidth);
	lNextRow=NextPoint.y-(SeedPoint.y-lAreaHeight);
		
	fPreverseGrad=mg_pfGradient[lArrayLength*lPrevRow+lPrevCol];
	fNextGrad=mg_pfGradient[lArrayLength*lNextRow+lNextCol];
	
	if(mg_fMaxGradient==0)
	{
		fLocalCost=1;
	}else
	{
		fLocalCost=1-(fPreverseGrad+fNextGrad)/(2*mg_fMaxGradient);
	}
	
	return fLocalCost;
}

//点p到q的cost
//l(p,q)=wZ*fZ(q)+wD*fD(p,q)+wG*fG(q)
//其中wZ=0.43,wD=0.43,wG=0.14
float CEdgeTracking::GetLocalCost(long PreversePointLoc, long NextPointLoc)
{
	float fLocalCost=0.0;
	float fPreverseGrad,fNextGrad;
	fPreverseGrad=mg_pfGradient[PreversePointLoc];
	fNextGrad=mg_pfGradient[NextPointLoc];
	if(mg_fMaxGradient==0)
	{
		fLocalCost=1;
	}else
	{
		fLocalCost=1-(fPreverseGrad+fNextGrad)/(2*mg_fMaxGradient);
	}
	
	fLocalCost=fLocalCost*0.35+0.65*GetDirection(PreversePointLoc,NextPointLoc);
	
	return fLocalCost;
}

//边缘检测,检测点及周围4个点的Laplacian算子，将最接近0的点的返回值设为0，其他的设为1
//如果点在边缘上，则返回0，否则返回1
long CEdgeTracking::GetPixelInEdge(const POINT& point)
{
	float fLap[5];
	fLap[0]=abs(GetLaplacian(point.y,point.x));
	fLap[1]=abs(GetLaplacian(point.y-1,point.x));
	fLap[2]=abs(GetLaplacian(point.y,point.x-1));
	fLap[3]=abs(GetLaplacian(point.y,point.x+1));
	fLap[4]=abs(GetLaplacian(point.y+1,point.x));
	
	//long lMin=0;
	for(int i=1;i<5;i++)
	{
		if(fLap[i]<fLap[0])
			return 1;
	}
	
	return 0;
}

//得到点的Laplacian值
float CEdgeTracking::GetLaplacian(long lRow, long lCol)
{
	float fLap;
	BYTE ucValue[5];
	unsigned short usValue[5];
	short sValue[5];
	float fValue[5];
	

	switch((Geodatabase::BANDDATATYPE)mg_ChannelType)
	{
	case Geodatabase::BDT_BYTE:
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow,(void*)&ucValue[0]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow-1,(void*)&ucValue[1]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol-1,lRow,(void*)&ucValue[2]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow+1,(void*)&ucValue[3]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol+1,lRow,(void*)&ucValue[4]);
		fLap=(ucValue[0]*4-ucValue[1]-ucValue[2]-ucValue[3]-ucValue[4]);
		break;
	case Geodatabase::BDT_USHORT:
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow,(void*)&usValue[0]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow-1,(void*)&usValue[1]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol-1,lRow,(void*)&usValue[2]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow+1,(void*)&usValue[3]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol+1,lRow,(void*)&usValue[4]);
		fLap=(usValue[0]*4-usValue[1]-usValue[2]-usValue[3]-usValue[4]);
		break;
	case Geodatabase::BDT_SHORT:
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow,(void*)&sValue[0]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow-1,(void*)&sValue[1]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol-1,lRow,(void*)&sValue[2]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow+1,(void*)&sValue[3]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol+1,lRow,(void*)&sValue[4]);
		fLap=(sValue[0]*4-sValue[1]-sValue[2]-sValue[3]-sValue[4]);
		break;
	case Geodatabase::BDT_FLOAT:
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow,(void*)&fValue[0]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow-1,(void*)&fValue[1]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol-1,lRow,(void*)&fValue[2]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol,lRow+1,(void*)&fValue[3]);
		m_pDataset->GetPixel(mg_lChannelIndex,lCol+1,lRow,(void*)&fValue[4]);
		fLap=(fValue[0]*4-fValue[1]-fValue[2]-fValue[3]-fValue[4]);
		break;
	}

	return fLap;
}

//点的梯度数值(经过线性变换后,边缘的梯度最小)
float CEdgeTracking::GetGradientValue(POINT point)
{
	int i;

	float fGradient=0.0;
	
	POINT pTemp;
	//点周围3*3邻域的梯度值
	float fAreaGradientX[9],fAreaGradientY[9],fAreaGradient[9];
	for(i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
		{
			pTemp.x=point.x+j-2;pTemp.y=point.y+i-2;
			//GetPointSobelGradient(pTemp,&fAreaGradientX[3*(i-1)+(j-1)],&fAreaGradientY[3*(i-1)+(j-1)]);
		}
	
	for(i=0;i<9;i++)
	{
		fAreaGradient[i]=sqrt(fAreaGradientX[i]*fAreaGradientX[i]+fAreaGradientY[i]*fAreaGradientY[i]);
	}
	
	float fMax,fMin;
	fMin=fAreaGradient[0];
	for(i=1;i<9;i++)
	{
		if(fAreaGradient[i]<fMin)
		{
			fMin=fAreaGradient[i];
		}
	}
	for(i=0;i<9;i++)
	{
		fAreaGradient[i]=fAreaGradient[i]-fMin;
	}
	
	fMax=fAreaGradient[0];
	for(i=1;i<9;i++)
	{
		if(fAreaGradient[i]>fMax)
		{
			fMax=fAreaGradient[i];
		}
	}
	if(fMax==0.0)
	{
		fGradient=1;
	}else
	{
		fGradient=1-fAreaGradient[4]/fMax;
	}

	return fGradient;
}

//从点p1到p2的方向相似度(如果两点方向一致，则为0)
float CEdgeTracking::GetDirection(long lFirstLocation, long lNextLocation)
{
	float fDirection=0.0;
	
	float fFirstGraX,fFirstGraY;
	float fFirstDirX,fFirstDirY;
	float fNextGraX,fNextGraY;
	float fNextDirX,fNextDirY;
	
	float fFirstTempX,fFirstTempY;
	float fNextTempX,fNextTempY;
	
	long lFirstX,lFirstY,lNextX,lNextY;
	lFirstY=lFirstLocation/mp_lResampleWidth;
	lFirstX=lFirstLocation-lFirstY*mp_lResampleWidth;
	lNextY=lNextLocation/mp_lResampleWidth;
	lNextX=lNextLocation-lNextY*mp_lResampleWidth;
	
	long lDeltX,lDeltY;
	lDeltX=lNextX-lFirstX;
	lDeltY=lNextY-lFirstY;
	
	fFirstTempX=mg_pfGradientX[lFirstLocation];
	fFirstTempY=mg_pfGradientY[lFirstLocation];
	fNextTempX=mg_pfGradientX[lNextLocation];
	fNextTempY=mg_pfGradientY[lNextLocation];
	
	float fLocationX,fLocationY;
	if((fFirstTempX==0&&fFirstTempY==0)||(fNextTempX==0&&fNextTempY==0))
	{
		return 1;
	}
	
	//梯度方向向量
	float fTempFirst,fTempNext;
	fTempFirst=sqrt(fFirstTempX*fFirstTempX+fFirstTempY*fFirstTempY);
	fTempNext=sqrt(fNextTempX*fNextTempX+fNextTempY*fNextTempY);
	fFirstGraX=fFirstTempX/fTempFirst;
	fFirstGraY=fFirstTempY/fTempFirst;
	fNextGraX=fNextTempX/fTempNext;
	fNextGraY=fNextTempY/fTempNext;
	
	//边缘方向向量
	fFirstDirX=fFirstGraY;
	fFirstDirY=(-1)*fFirstGraX;
	fNextDirX=fNextGraY;
	fNextDirY=(-1)*fNextGraX;
	
	float fDistance;
	fDistance=sqrt(float(lDeltX*lDeltX+lDeltY*lDeltY));
	if(lDeltX*fFirstDirX+lDeltY*fFirstDirY>=0)
	{
		fLocationX=(lNextX-lFirstX)/fDistance;
		fLocationY=(lNextY-lFirstY)/fDistance;
	}else
	{
		fLocationX=(lFirstX-lNextX)/fDistance;
		fLocationY=(lFirstY-lNextY)/fDistance;
	}
	
	float fFirstRenote,fNextRenote;
	fFirstRenote=(fFirstDirX*fLocationX+fFirstDirY*fLocationY);
	fNextRenote=(fNextDirX*fLocationX+fNextDirY*fLocationY);
	if(fFirstRenote<-1)
		fFirstRenote=-1;
	if(fFirstRenote>1)
		fFirstRenote=1;
	if(fNextRenote<-1)
		fNextRenote=-1;
	if(fNextRenote>1)
		fNextRenote=1;
	fDirection=2*(acos(fFirstRenote)+acos(fNextRenote))/(3*PI);
	
	return fDirection;
}

//得到窗口的最大梯度值
float CEdgeTracking::GetMaxGradient()
{
	float fMaxGradient;
	fMaxGradient=mg_pfGradient[0];
	for(long i=1;i<mp_lBufferSize;i++)
	{
		if(mg_pfGradient[i]>fMaxGradient)
			fMaxGradient=mg_pfGradient[i];
	}
	
	return fMaxGradient;
}

//计算矩形样区的最大梯度值
void CEdgeTracking::GetActiveMaxGradient(RECT rect)
{
	float fMaxGradient=0;
	long lLocation;
	for(long i=rect.top;i<=rect.bottom;i++)
		for(long j=rect.left;j<=rect.right;j++)
		{
			lLocation=i*mp_lResampleWidth+j;
			if(fMaxGradient==0||mg_pfGradient[lLocation]>fMaxGradient)
				fMaxGradient=mg_pfGradient[lLocation];
		}
	mg_fMaxGradient=fMaxGradient;
}

//根据窗口重采样
void CEdgeTracking::ReadThemeData(const GEOMETRY::geom::Envelope& stDrawWorldExtent, const RECT& rect)
{
	if (NULL == m_pDataset)
		return;
	
	stScreenWorldExtent = stDrawWorldExtent;
	ScreenRect = rect;
	m_pDataset->WorldToPixel(stDrawWorldExtent.getMinX(), stDrawWorldExtent.getMaxY(), &mp_lRow1, &mp_lCol1);
	m_pDataset->WorldToPixel(stDrawWorldExtent.getMaxX(), stDrawWorldExtent.getMinY(), &mp_lRow2, &mp_lCol2);
	
	mp_lSrcWidth = mp_lCol2 - mp_lCol1 + 1;
	mp_lSrcHeight = mp_lRow2 - mp_lRow1 + 1;

	//计算采样比
	long lDstWidth = rect.right - rect.left + 1;
	mp_dblResampleRatio = (double)lDstWidth / (double)mp_lSrcWidth;

	if (mp_dblResampleRatio > 1.0)
		mp_dblResampleRatio = 1.0;

	
	mp_lResampleWidth = GetResampleSize(mp_lSrcWidth, mp_dblResampleRatio);
	mp_lResampleHeight = GetResampleSize(mp_lSrcHeight, mp_dblResampleRatio);
	
	mp_lBufferSize = mp_lResampleWidth * mp_lResampleHeight;
	
	if (NULL != mp_pucBufSrc) 
	{
		delete[] mp_pucBufSrc;
		mp_pucBufSrc = NULL;
	}

	mp_pucBufSrc = new unsigned char[mp_lBufferSize];
	memset(mp_pucBufSrc, 0, mp_lBufferSize);
	double dmin,dmax;

	m_pDataset->GetBandMinMaxValue(mg_lChannelIndex,&dmax,&dmin);
	m_pDataset->DataReadBandNormalize(mg_lChannelIndex,mp_lCol1,mp_lRow1,mp_lSrcWidth, mp_lSrcHeight,
		      mp_lResampleWidth,mp_lResampleHeight,mp_pucBufSrc,dmin,dmax);

	
}

//从实际象素转换重采样后的象素坐标
void CEdgeTracking::PixelToResample(CPoint *point)
{
	point->y = (point->y - mp_lRow1) * mp_dblResampleRatio;
	point->x = (point->x - mp_lCol1) * mp_dblResampleRatio;
}

//从重采样后的象素转换到实际象素坐标
void CEdgeTracking::ResampleToPixel(CPoint *point)
{
	point->y = point->y / mp_dblResampleRatio + mp_lRow1;
	point->x = point->x / mp_dblResampleRatio + mp_lCol1;
}

void CEdgeTracking::ReleaseMemory()
{
	if(mg_pfGradient)
	{
		delete []mg_pfGradient;
		mg_pfGradient = NULL;
	}
	if(mg_pfGradientX)
	{
		delete []mg_pfGradientX;
		mg_pfGradientX = NULL;
	}
	if(mg_pfGradientY)
	{
		delete []mg_pfGradientY;
		mg_pfGradientY = NULL;
	}
	if(mp_pucBufSrc)
	{
		delete []mp_pucBufSrc;
		mp_pucBufSrc = NULL;
	}
}

}