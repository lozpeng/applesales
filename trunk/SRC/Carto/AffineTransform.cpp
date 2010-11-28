#include "StdAfx.h"
#include "AffineTransform.h"
#include "ProjTransform.h"
#include <geometry/geom/LineString.h>
#include <geometry/geom/Geometry.h>
#include <geometry/geom/Polygon.h>
#include <geometry/geom/Coordinate.h>
#include <geometry/geom/GeometryCollection.h>


namespace Carto
{
void EqNorm(double *a,int n,double b,double *aa, double *ab,double p)
{
	int  i,j;

	for (i=0; i<n; i++) 
	{
		for (j=0; j<n; j++) 
			*aa++ += p* a[i] * a[j];

		*ab++ += p* a[i] * b;
	}
}

int agaus(double *a,double *b,int n)
{
	int *js,l,k,i,j,is,p,q;
	double d,t;
	js=(int *)malloc(n*sizeof(int));
	l=1;
	for (k=0;k<=n-2;k++)
	{ d=0.0;
	for (i=k;i<=n-1;i++)
		for (j=k;j<=n-1;j++)
		{ t=fabs(a[i*n+j]);
	if (t>d) { d=t; js[k]=j; is=i;}
	}
	if (d+1.0==1.0) l=0;
	else
	{ if (js[k]!=k)
	for (i=0;i<=n-1;i++)
	{ p=i*n+k; q=i*n+js[k];
	t=a[p]; a[p]=a[q]; a[q]=t;
	}
	if (is!=k)
	{ for (j=k;j<=n-1;j++)
	{ p=k*n+j; q=is*n+j;
	t=a[p]; a[p]=a[q]; a[q]=t;
	}
	t=b[k]; b[k]=b[is]; b[is]=t;
	}
	}
	if (l==0)
	{ free(js); printf("fail\n");
	return(0);
	}
	d=a[k*n+k];
	for (j=k+1;j<=n-1;j++)
	{ p=k*n+j; a[p]=a[p]/d;}
	b[k]=b[k]/d;
	for (i=k+1;i<=n-1;i++)
	{ for (j=k+1;j<=n-1;j++)
	{ p=i*n+j;
	a[p]=a[p]-a[i*n+k]*a[k*n+j];
	}
	b[i]=b[i]-a[i*n+k]*b[k];
	}
	}
	d=a[(n-1)*n+n-1];
	if (fabs(d)+1.0==1.0)
	{ free(js); printf("fail\n");
	return(0);
	}
	b[n-1]=b[n-1]/d;
	for (i=n-2;i>=0;i--)
	{ t=0.0;
	for (j=i+1;j<=n-1;j++)
		t=t+a[i*n+j]*b[j];
	b[i]=b[i]-t;
	}
	js[n-1]=n-1;
	for (k=n-1;k>=0;k--)
		if (js[k]!=k)
		{ t=b[k]; b[k]=b[js[k]]; b[js[k]]=t;}
		free(js);
		return(1);
}

void PolynCal1(double *x1, double *y1, double *x2, double *y2, int n,
	double *cofx, double *cofy)
{
	for(int i=0; i<n; i++)
	{
		x1[i]=(cofx[0]+cofx[1]*x2[i]+cofx[2]*y2[i]);
		y1[i]=(cofy[0]+cofy[1]*x2[i]+cofy[2]*y2[i]);
	}
}

void PolynCoff1(double *x1, double *y1, double *x2, double *y2, int n,
	double *cofx, double *cofy, double *rmsx, double *rmsy)
{
	double a[3],aa[9],al[3];
	int    i;

	//x 
	memset(aa,0,sizeof(double)*9);
	memset(al,0,sizeof(double)*3);	
	for(i=0; i<n; i++)
	{
		a[0] = 1.0;
		a[1] = x2[i];	a[2] = y2[i];  
		EqNorm(a,3,x1[i],aa,al,1.0);
	}
	agaus(aa, al, 3);
	memcpy(cofx, al, sizeof(double)*3);

	//y
	memset(aa,0,sizeof(double)*9);
	memset(al,0,sizeof(double)*3);	
	for(i=0; i<n; i++)
	{
		a[0] = 1.0;
		a[1] = x2[i];	a[2] = y2[i];  
		EqNorm(a,3,y1[i],aa,al,1.0);
	}
	agaus(aa, al, 3);
	memcpy(cofy, al, sizeof(double)*3);

	//rmsx
	if(rmsx)
	{
		for(i=0; i<n; i++)
			rmsx[i]=(cofx[0]+cofx[1]*x2[i]+cofx[2]*y2[i])-x1[i];
	}
	//rmsy
	if(rmsy)
	{
		for(i=0; i<n; i++)
			rmsy[i]=(cofy[0]+cofy[1]*x2[i]+cofy[2]*y2[i])-y1[i];
	}

}


CAffineTransform::CAffineTransform()
{
	m_bUsed = false;
	m_hProjectTrans = NULL;
	memset(affineCoefX, 0, sizeof(double)*3);
	memset(affineCoefY, 0, sizeof(double)*3);
	memset(affineNCoefX, 0, sizeof(double)*3);
	memset(affineNCoefY, 0, sizeof(double)*3);

}


CAffineTransform::~CAffineTransform()
{
	//释放掉投影转换的参数
	if(m_hProjectTrans)
	{
		//IPE_ProjectTransFree((HPROJECTTRANS*)(&m_hProjectTrans));
	}

}

//正变换
void CAffineTransform::Transform(GEOMETRY::geom::Geometry *pshape)
{
	if(!pshape)
	{
		return;
	}
	double destX,destY;
	GEOMETRY::geom::Coordinate coord;

	switch(pshape->getGeometryTypeId())
	{
	case GEOMETRY::geom::GEOS_POINT:
		{
			coord =pshape->GetPoint(0);

			PolynCal1(&destX,&destY,&coord.x,&coord.y,1,affineCoefX,affineCoefY);

			coord.x =destX;
			coord.y =destY;

			pshape->ReplacePoint(0,coord);

			break;
		}
	case GEOMETRY::geom::GEOS_LINESTRING:
	case GEOMETRY::geom::GEOS_LINEARRING:
		{
			const GEOMETRY::geom::CoordinateSequence *cs =((GEOMETRY::geom::LineString*)pshape)->getCoordinatesRO();

			//对数组里的每个点进行转换
			for(long i=0;i<cs->getSize();i++)
			{
				coord =cs->getAt(i);

				PolynCal1(&destX,&destY,&coord.x,&coord.y,1,affineCoefX,affineCoefY);

				coord.x =destX;
				coord.y =destY;

				cs->getAt(i) =coord;

			}


			break;
		}

	case GEOMETRY::geom::GEOS_POLYGON:
		{

			long lpart =((GEOMETRY::geom::Polygon*)pshape)->GeometryCount();

			for(long i=0;i<lpart;i++)
			{

				Transform(((GEOMETRY::geom::Polygon*)pshape)->GetGeometry(i));
			}
			break;
		}
	case GEOMETRY::geom::GEOS_MULTIPOINT:
	case GEOMETRY::geom::GEOS_MULTILINESTRING:
	case GEOMETRY::geom::GEOS_MULTIPOLYGON:
		{
			GEOMETRY::geom::GeometryCollection *pGeoCol = (GEOMETRY::geom::GeometryCollection*)pshape;
			for(int i = 0 ; i < pGeoCol->getNumGeometries() ; i++ )
			{
				Transform((GEOMETRY::geom::Geometry*)pGeoCol->getGeometryN(i));
			}

			break;
		}
	default:

		break;
	}

}

void CAffineTransform::Transform(double &X, double &Y)
{
	double destX,destY;

	PolynCal1(&destX,&destY,&X,&Y,1,affineCoefX,affineCoefY);

	X = destX;
	Y = destY;

}

void CAffineTransform::Transform(GEOMETRY::geom::Envelope &envelop)
{
	double dx[4],dy[4];

	double xmin,xmax,ymin,ymax;
	xmin = envelop.getMinX();
	xmax = envelop.getMaxX();
	ymin = envelop.getMinY();
	ymax = envelop.getMaxY();

	//左上
	PolynCal1(&dx[0],&dy[0],&xmin,&ymax,1,affineCoefX,affineCoefY);
	//右上
	PolynCal1(&dx[1],&dy[1],&xmax,&ymax,1,affineCoefX,affineCoefY);
	//右下
	PolynCal1(&dx[2],&dy[2],&xmax,&ymin,1,affineCoefX,affineCoefY);
	//左下
	PolynCal1(&dx[3],&dy[3],&xmin,&ymin,1,affineCoefX,affineCoefY);



	xmin =min(min(dx[0],dx[1]),min(dx[2],dx[3]));
	xmax =max(max(dx[0],dx[1]),max(dx[2],dx[3]));

	ymin =min(min(dy[0],dy[1]),min(dy[2],dy[3]));
	ymax =max(max(dy[0],dy[1]),max(dy[2],dy[3]));

	envelop.init(xmin,xmax,ymin,ymax);


}

//逆变换
void  CAffineTransform::TransformN(GEOMETRY::geom::Geometry *pshape)
{
	if(!pshape)
	{
		return;
	}
	double destX,destY;
	GEOMETRY::geom::Coordinate coord;

	switch(pshape->getGeometryTypeId())
	{
	case GEOMETRY::geom::GEOS_POINT:
		{
			coord =pshape->GetPoint(0);

			PolynCal1(&destX,&destY,&coord.x,&coord.y,1,affineNCoefX,affineNCoefY);

			coord.x =destX;
			coord.y =destY;

			pshape->ReplacePoint(0,coord);

			break;
		}
	case GEOMETRY::geom::GEOS_LINESTRING:
	case GEOMETRY::geom::GEOS_LINEARRING:
		{
			const GEOMETRY::geom::CoordinateSequence *cs =((GEOMETRY::geom::LineString*)pshape)->getCoordinatesRO();

			//对数组里的每个点进行转换
			for(long i=0;i<cs->getSize();i++)
			{
				coord =cs->getAt(i);

				PolynCal1(&destX,&destY,&coord.x,&coord.y,1,affineNCoefX,affineNCoefY);

				coord.x =destX;
				coord.y =destY;

				cs->getAt(i) =coord;

			}


			break;
		}

	case GEOMETRY::geom::GEOS_POLYGON:
		{

			long lpart =((GEOMETRY::geom::Polygon*)pshape)->GeometryCount();

			for(long i=0;i<lpart;i++)
			{

				TransformN(((GEOMETRY::geom::Polygon*)pshape)->GetGeometry(i));
			}
			break;
		}
	case GEOMETRY::geom::GEOS_MULTIPOINT:
	case GEOMETRY::geom::GEOS_MULTILINESTRING:
	case GEOMETRY::geom::GEOS_MULTIPOLYGON:
		{
			GEOMETRY::geom::GeometryCollection *pGeoCol = (GEOMETRY::geom::GeometryCollection*)pshape;
			for(int i = 0 ; i < pGeoCol->getNumGeometries() ; i++ )
			{
				TransformN((GEOMETRY::geom::Geometry*)pGeoCol->getGeometryN(i));
			}

			break;
		}
	default:

		break;
	}

}

void  CAffineTransform::TransformN(double &X, double &Y)
{
	double srcX,srcY;

	PolynCal1(&srcX,&srcY,&X,&Y,1,affineNCoefX,affineNCoefY);

	X = srcX;
	Y = srcY;

}

void CAffineTransform::TransformN(GEOMETRY::geom::Envelope &envelop)
{
	double dx[4],dy[4];

	double xmin,xmax,ymin,ymax;
	xmin = envelop.getMinX();
	xmax = envelop.getMaxX();
	ymin = envelop.getMinY();
	ymax = envelop.getMaxY();

	//左上
	PolynCal1(&dx[0],&dy[0],&xmin,&ymax,1,affineNCoefX,affineNCoefY);
	//右上
	PolynCal1(&dx[1],&dy[1],&xmax,&ymax,1,affineNCoefX,affineNCoefY);
	//右下
	PolynCal1(&dx[2],&dy[2],&xmax,&ymin,1,affineNCoefX,affineNCoefY);
	//左下
	PolynCal1(&dx[3],&dy[3],&xmin,&ymin,1,affineNCoefX,affineNCoefY);



	xmin =min(min(dx[0],dx[1]),min(dx[2],dx[3]));
	xmax =max(max(dx[0],dx[1]),max(dx[2],dx[3]));

	ymin =min(min(dy[0],dy[1]),min(dy[2],dy[3]));
	ymax =max(max(dy[0],dy[1]),max(dy[2],dy[3]));

	envelop.init(xmin,xmax,ymin,ymax);

}

bool CAffineTransform::DynaProject(std::string strSrcWkt, std::string strDestWkt,GEOMETRY::geom::Envelope dataEnvelop)
{
	//构造投影转换用的结构体
	Geodatabase::CSpatialReferencePtr pSRSrc =new Geodatabase::CSpatialReference();
	pSRSrc->ImportFromESRI(strSrcWkt.c_str());

	Geodatabase::CSpatialReferencePtr pSRDest =new Geodatabase::CSpatialReference();
	pSRDest->ImportFromESRI(strDestWkt.c_str());


	//将影像范围内打4*4的方格，每个方格中心再取一个控制点，总共41个
	long lptcount =41;

	if (dataEnvelop.getMinX()==0 && dataEnvelop.getMaxX()==0 && dataEnvelop.getMinY()==0 &&dataEnvelop.getMaxY()==0)
		return false;



	std::vector<double> srcx;
	std::vector<double> srcy;
	std::vector<double> destx;
	std::vector<double> desty;
	srcx.resize(lptcount);
	srcy.resize(lptcount);
	destx.resize(lptcount);
	desty.resize(lptcount);

	long lCol,lRow;
	double xcell = (dataEnvelop.getMaxX()-dataEnvelop.getMinX())/4;
	double ycell = (dataEnvelop.getMaxY()-dataEnvelop.getMinY())/4;
	long index =0;
	for (index=0;index<25;index++)
	{
		lCol = index%5;
		lRow = index/5;

		srcx[index] = destx[index] = dataEnvelop.getMinX()+lCol*xcell;
		srcy[index] = desty[index] = dataEnvelop.getMaxY()-lRow*ycell;
	}

	long i =0;
	for (i=0;i<16;i++,index++)
	{
		lCol = i%4;
		lRow = i/4;
		srcx[index] = destx[index] = dataEnvelop.getMinX() + lCol*xcell + 0.5*xcell;
		srcy[index] = desty[index] = dataEnvelop.getMaxY() - lRow*ycell - 0.5*ycell;
	}

	Geodatabase::CProjTransform trans(pSRSrc,pSRDest);

	//计算转换为目标投影后的坐标
	if (!trans.Transform(lptcount,&destx[0], &desty[0]))
	{

		return false;
	}

	std::vector<double> rmsx,rmsy;
	rmsx.resize(lptcount);
	rmsy.resize(lptcount);

	//计算正向投影系数
	PolynCoff1(&destx[0],&desty[0],&srcx[0],&srcy[0],lptcount,affineCoefX,affineCoefY,&rmsx[0],&rmsy[0]);

	//计算反向投影系数
	PolynCoff1(&srcx[0],&srcy[0],&destx[0],&desty[0],lptcount,affineNCoefX,affineNCoefY,&rmsx[0],&rmsy[0]);

	m_bUsed = true;




	return true;

}

}