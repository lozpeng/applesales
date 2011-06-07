#include "stdafx.h"
#include "DistanceClassify.h"
#include "RasterWSFactory.h"
#include "IWorkspace.h"

namespace ImageProcess
{




inline bool GetCLSRect(ClassInfo* pstCls, RECT *pRect)
{
	if ((NULL == pstCls) || (NULL == pRect))
		return false;

	pRect->top = 100000000;
	pRect->left = 100000000;
	pRect->right = 0;
	pRect->bottom = 0;

	RECT rectTemp;
	if (!GetRgnBox(pstCls->hRgn, &rectTemp))
		return false;
	pRect->top = min (pRect->top, rectTemp.top);
	pRect->left = min (pRect->left, rectTemp.left);
	pRect->bottom = max (pRect->bottom, rectTemp.bottom);
	pRect->right = max (pRect->right, rectTemp.right);
	return true;
}

inline bool InCLS (long i, long j, ClassInfo* pstCls) 
{
	
	if (PtInRegion(pstCls->hRgn, j, i))
		return true;

	return false;
}

static int brinv(double * a,int n)
{ 
	int *is,*js,i,j,k,l,u,v;
	double d,p;

	//==一维情况下(n==1),0的逆阵为无穷大,而原先brinv函
	//==数的输出却为0,下面的代码将其设定为1e300;
	//==这种情况不仅在一维情况下会出现,在多维情况下同
	//==样会出现(只要样区完全均一),即	协方差阵为0,也要
	//==将其逆阵设为无穷大(比如1e300);
	j=0;
	for(i=0;j<(n*n);i++)
	{
		if (a[i]==0) j++;
		else break;
	}
	if (j==n*n) {
		for(i=0;i<n*n;i++)
			a[i]=1e300;
		return TRUE;
	}



	//is=malloc(n*sizeof(int));
	is=new int[n];
	js=new int[n];
	//js=malloc(n*sizeof(int));
	for (k=0; k<=n-1; k++)
	{ d=0.0;
	for (i=k; i<=n-1; i++)
		for (j=k; j<=n-1; j++)
		{ l=i*n+j; p=fabs(a[l]);
	if (p>d) { d=p; is[k]=i; js[k]=j;}
	}
	if (d+1.0==1.0)
	{ //free(is); 
		//free(js); 
		delete []is;
		delete []js;	
		return(0);
	}
	if (is[k]!=k)
		for (j=0; j<=n-1; j++)
		{ u=k*n+j; v=is[k]*n+j;
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	if (js[k]!=k)
		for (i=0; i<=n-1; i++)
		{ u=i*n+k; v=i*n+js[k];
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	l=k*n+k;
	a[l]=1.0/a[l];
	for (j=0; j<=n-1; j++)
		if (j!=k)
		{ u=k*n+j; a[u]=a[u]*a[l];}
		for (i=0; i<=n-1; i++)
			if (i!=k)
				for (j=0; j<=n-1; j++)
					if (j!=k)
					{ u=i*n+j;
		a[u]=a[u]-a[i*n+k]*a[k*n+j];
		}
		for (i=0; i<=n-1; i++)
			if (i!=k)
			{ u=i*n+k; a[u]=-a[u]*a[l];}
	}
	for (k=n-1; k>=0; k--)
	{ if (js[k]!=k)
	for (j=0; j<=n-1; j++)
	{ u=k*n+j; v=js[k]*n+j;
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	if (is[k]!=k)
		for (i=0; i<=n-1; i++)
		{ u=i*n+k; v=i*n+is[k];
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	}
	delete []is;
	delete []js;
	return(1);
}

static bool CalcClassCentre(Geodatabase::IRasterDataset* InRs, long *plMapViewIndexIn, long *plChannelDataType, long Bandnum, long lWidth,long lHeight, ClassInfo* pstCls, double *m_Center, double *m_Coffs)
{
	double *cof1;
	//初始化空间。   
	BOOL bOK;
	BYTE byValue = 0;
	short sValue = 0;
	unsigned short usValue = 0;
	float fValue = 0.0;

	cof1 = new double[Bandnum];
	if(cof1 == NULL|| m_Center == NULL|| m_Coffs == NULL)
		return false;

	//初始化为零
	for(long k =0; k<Bandnum; k++)
	{
		m_Center[k] = 0;
		for(long l =0; l<Bandnum; l++)
			m_Coffs[k*Bandnum+l] =0;
	}


	long  counter =0;

	//获取类中心。

	//声明一个大数组
	double* m_temp = new double[Bandnum]; 
	long k = 0;
	for(k =0; k<Bandnum; k++)
	{
		m_temp[k] = 0;
	}

	RECT rectCls;
	GetCLSRect(pstCls, &rectCls);

	for(long l =0; l<Bandnum; l++)
	{
		for(long i= 1;  i<= lHeight;  i++)
		{
			for(long j= 1; j<= lWidth ; j++)
			{
				
				//如果不在AOI范围内，Continue,否则lCount++
				if( i < rectCls.top || i > rectCls.bottom || j< rectCls.left || j > rectCls.right)
					continue;

				if(!InCLS(i, j, pstCls))
					continue;

				switch(plChannelDataType[l])
				{
				case 0:
					{
						InRs->PixelIO(plMapViewIndexIn[l],  j, i,&byValue, true);
						m_temp[l]+=byValue;
						break;
					}
				case 1:
					{
						InRs->PixelIO(plMapViewIndexIn[l],  j, i,&usValue, true);
						m_temp[l]+=usValue;
						break;	
					}

				case 2:
					{
						InRs->PixelIO(plMapViewIndexIn[l],  j, i,&sValue, true);
						m_temp[l]+=sValue;
						break;
					}


				case 3:
					{
						InRs->PixelIO(plMapViewIndexIn[l],  j, i,&fValue, true);
						m_temp[l]+=fValue;
						break;
					}
				
				default:
					return false;
				}

				counter ++;
			}
			
		}
	}
		counter = counter / Bandnum;
		if(counter == 0)
		{
			delete[] m_temp;
			delete[] cof1;
			return FALSE;
		}

		for(long l =0; l<Bandnum; l++)
			m_Center[l] = m_temp[l]/counter;

		delete[] m_temp;

		//获取协方差矩阵    	
		for(long i= 1;  i<= lHeight;  i++)
		{
			for(long j= 1; j<= lWidth; j++)
			{
				if( i< rectCls.top || i > rectCls.bottom || j < rectCls.left || j > rectCls.right)
					continue;

				if(!InCLS(i, j, pstCls))
					continue;
				for(long l =0; l<Bandnum; l++)
				{
					
					switch(plChannelDataType[l])
					{
					case 0:
						{
							InRs->PixelIO(plMapViewIndexIn[l],  j, i,&byValue, true);
							cof1[l] =(double)byValue - m_Center[l];
							break;
						}
					case 1:
						{
							InRs->PixelIO(plMapViewIndexIn[l],  j, i,&usValue, true);
							cof1[l] =(double)usValue - m_Center[l];
							break;	
						}

					case 2:
						{
							InRs->PixelIO(plMapViewIndexIn[l],  j, i,&sValue, true);
							cof1[l] =(double)sValue - m_Center[l];
							break;
						}


					case 3:
						{
							InRs->PixelIO(plMapViewIndexIn[l],  j, i,&fValue, true);
							cof1[l] =(double)fValue - m_Center[l];
							break;
						}
					
					default:
						return false;
					}

					//				cof1[l]= im[l][i*ix+j] - m_Center[l];
				}
				for(long i1=0; i1<Bandnum; i1++)
					for(long i2=0; i2<Bandnum; i2++)
						m_Coffs[i1*Bandnum+i2] += cof1[i1]*cof1[i2]/(counter);
			}
			
		}

		delete[] cof1;
		return true;
}


static bool MinDistanceClassify(Geodatabase::IRasterDataset *InRs, long *plMapViewIndexIn, long *plChannelDataType, Geodatabase::IRasterDataset *OutRs, long lWidth, long lHeight, long lNumCh,  ClassifyInfo* pstClss)
{

	long i,j,k,l=0,m,kind;	
	double dmin,d;	
	double **m_Center=NULL;
	double **m_Coffs=NULL;
	long lclassnum =pstClss->lClsCount;

	m_Center = new double*[lclassnum];
	m_Coffs = new double*[lclassnum];
	BOOL bOK;
	BYTE byValue = 0;
	short sValue = 0;
	unsigned short usValue = 0;
	float fValue = 0.0;
	BYTE red,green,blue;
    
	InRs->CreateBuffer();
	OutRs->CreateBuffer();

	for(i=0;i<lclassnum;i++)
	{
		m_Center[i] = new double[lNumCh];
		m_Coffs[i] = new double[lNumCh*lNumCh];	

		CalcClassCentre(InRs, plMapViewIndexIn, plChannelDataType, lNumCh, lWidth, lHeight, &(pstClss->pstCls[i]), m_Center[i], m_Coffs[i]);
	}
	for(i=1;i<=lHeight;i++)
	{
		for(j=1;j<=lWidth;j++)
		{
			dmin = 1000000.0; l =0;

			for(m=0;m<lclassnum;m++)
			{
				d = 0.0;
				for(k = 0; k<lNumCh; k++)
				{

					switch((Geodatabase::BANDDATATYPE)plChannelDataType[k])
					{
					case Geodatabase::BDT_BYTE:
						{
                            InRs->PixelIO(plMapViewIndexIn[k],  j, i,&byValue, true);
							d+=(byValue-m_Center[m][k])*(byValue-m_Center[m][k]);
							break;
						}
					case Geodatabase::BDT_USHORT:
						{
							InRs->PixelIO(plMapViewIndexIn[k],  j, i,&usValue, true);
							d+=(usValue-m_Center[m][k])*(usValue-m_Center[m][k]);
							break;	
						}
						
					case Geodatabase::BDT_SHORT:
						{
                            InRs->PixelIO(plMapViewIndexIn[k],  j, i,&sValue, true);
							d+=(sValue-m_Center[m][k])*(sValue-m_Center[m][k]);
							break;
						}
						
					
					case Geodatabase::BDT_FLOAT:
						{
                            InRs->PixelIO(plMapViewIndexIn[k],  j, i,&fValue, true);
							d+=(fValue-m_Center[m][k])*(fValue-m_Center[m][k]);
							break;
						}
						
					default:
						return false;
					}
				}
				l++;				
				if(d >= dmin) 
					continue;
				dmin = d;  kind =l;	
			}
			
			//查找该像素相应的值，对应它所属类的颜色
            red =pstClss->pstCls[kind-1].Red;
			green =pstClss->pstCls[kind-1].Green;
			blue =pstClss->pstCls[kind-1].Blue;

			//写入值
            OutRs->PixelIO(1,j,i,(void*)&red,false);
			/*OutRs->PixelIO(2,j,i,(void*)&green,false);
			OutRs->PixelIO(3,j,i,(void*)&blue,false);*/

		
			
		}

	}
	InRs->DeleteBuffer();
	OutRs->DeleteBuffer();
	for(i=0;i<lclassnum;i++)
	{
		delete []m_Center[i];
		delete []m_Coffs[i];
	}
	delete []m_Center;
	delete []m_Coffs;

	return true;
}


static bool MaloblusClassify(Geodatabase::IRasterDataset *InRs, long *plMapViewIndexIn, long *plChannelDataType, Geodatabase::IRasterDataset *OutRs, long lWidth, long lHeight, long lNumCh,  ClassifyInfo* pstClss)
{
	long i,j,k,l=0,m,n,kind=0;
	double **m_Center=NULL;
	double **m_Coffs=NULL;
	double dmin,*diff,*tmp,d;

	long lExpClass =pstClss->lClsCount;
	m_Center = new double*[lExpClass];
	m_Coffs = new double*[lExpClass];
	BOOL bOK = TRUE;

	BYTE byValue = 0;
	short sValue = 0;
	unsigned short usValue = 0;
	float fValue = 0.0;
	BYTE red,green,blue;

	InRs->CreateBuffer();
	OutRs->CreateBuffer();


	for(i=0;i<lExpClass;i++)
	{
		m_Center[i] = new double[lNumCh];
		m_Coffs[i] = new double[lNumCh*lNumCh];	
		CalcClassCentre(InRs, plMapViewIndexIn, plChannelDataType, lNumCh, lWidth, lHeight, &(pstClss->pstCls[i]), m_Center[i], m_Coffs[i]);
		
		brinv(m_Coffs[i],lNumCh);

	}
	diff = new double[lNumCh];	
	tmp  = new double[lNumCh];
	for(i=0;i<lHeight;i++)
	{
		for(j=0;j<lWidth;j++)
		{
			dmin = 1000000.0; l =0;
			for(m=0;m<lExpClass;m++)
			{	
				
				for(n = 0; n < lNumCh; n++)
				{
					
					switch(plChannelDataType[n])
					{
					case 0:
						{
							InRs->PixelIO(plMapViewIndexIn[n],  j, i,&byValue, true);
							diff[n] = byValue - m_Center[m][n];
							break;
						}
					case 1:
						{
							InRs->PixelIO(plMapViewIndexIn[n],  j, i,&usValue, true);
							diff[n] = usValue - m_Center[m][n];
							break;	
						}

					case 2:
						{
							InRs->PixelIO(plMapViewIndexIn[n],  j, i,&sValue, true);
							diff[n] = sValue - m_Center[m][n];
							break;
						}


					case 3:
						{
							InRs->PixelIO(plMapViewIndexIn[n],  j, i,&fValue, true);
							diff[n] = fValue - m_Center[m][n];
							break;
						}

					default:
						return false;
					}
				}

				for(n=0; n<lNumCh; n++){
					tmp[n] = 0;
					for(k= 0; k<lNumCh; k++)
						tmp[n] += diff[k]*m_Coffs[m][k*lNumCh+n];
				}
				d = 0.0;
				for(k=0; k<lNumCh; k++)
					d += tmp[k]*diff[k];				
				l++;
				if(d >= dmin)  continue;
				dmin = d;  kind =l;	
			}
			
			//查找该像素相应的值，对应它所属类的颜色
			red =pstClss->pstCls[kind-1].Red;
			green =pstClss->pstCls[kind-1].Green;
			blue =pstClss->pstCls[kind-1].Blue;

			//写入值
			OutRs->PixelIO(1,j,i,(void*)&red,false);
			OutRs->PixelIO(2,j,i,(void*)&green,false);
			OutRs->PixelIO(3,j,i,(void*)&blue,false);


			
		}

	}

	InRs->DeleteBuffer();
	OutRs->DeleteBuffer();

	for(i=0;i<lExpClass;i++)
	{
		delete []m_Center[i];
		delete []m_Coffs[i];
	}
	delete []m_Center;
	delete []m_Coffs;
	delete []diff;	
	delete []tmp;
	return true;
}


bool DistanceClassify(const char *InputFileName, long lInputChannelCount, long* plChannelIndex,
	const char *OutputFileName, long lOutputChannelNum, 
	long lSurveyDistMethod, ClassifyInfo *ClsInfo,
	long* plValue, long* plColor)
{

	using namespace Geodatabase;
	if(!ClsInfo)
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


	//获取目标文件文件夹路径
	std::string path =OutputFileName;

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

	if(!pdestWS->CreateRasterDataset(OutputFileName,&rasfileInfoDes))
	{
		return false;
	}
	IRasterDatasetPtr rasDestDS =pdestWS->OpenRasterDataset(OutputFileName,false);


	if(!rasDestDS)
	{
		return false;
	}
	
    //获得波段的数据类型
	long *plChannelDataType =new long[lInputChannelCount];
	for(long i=0;i<lInputChannelCount;i++)
	{
		plChannelDataType[i] =(long)pSrcRS->GetBandDataType(plChannelIndex[i]);
	}

	//计算滚动条的执行数目
	long lReadCount;
	lReadCount = (ClsInfo->lClsCount)* lFileHeight * lInputChannelCount + (ClsInfo->lClsCount)*lFileHeight + lFileHeight* lFileWidth ;

	

		switch(lSurveyDistMethod)
		{
		case 0://调用最小距离分类
			{
				if(!MinDistanceClassify(pSrcRS.get(), plChannelIndex, plChannelDataType,rasDestDS.get(), lFileWidth, lFileHeight, lInputChannelCount, ClsInfo))
				{
				
				


					return false; 
				}
			}
			break;
		case 1:
			{
				if(!MaloblusClassify(pSrcRS.get(), plChannelIndex, plChannelDataType,rasDestDS.get(), lFileWidth, lFileHeight, lInputChannelCount, ClsInfo))
				{
					

					return false; 
				}
			}
			break;
		case 2:
			{
				/*if(!BayesClassify(hSegIn, plMapViewIndexIn, plChannelDataType,hSegOut, lMapViewIndexOut, lFileWidth, lFileHeight, lInputChannelCount, stClss.lClsCount, &stClss, plValue))
				{
					ClearUpCls(&stClss);
					delete[] plMapViewIndexIn;
					TT_ProgressEnd( hProgress );
					TT_ProgressClose( &hProgress );
					SEG_FileClose(&hSegIn);
					SEG_FileClose(&hSegOut);






					return FALSE; 
				}*/
			}
			break;
		default:
			break;
		}

		



	return true;
}



} //namespace ImageProcess