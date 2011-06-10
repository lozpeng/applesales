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
//����ȡ���ת��Ϊʸ��
static bool CreateShpResult(Geodatabase::IRasterDataset* pDataset,const char *OutputFileName,int nminSize,SYSTEM::IProgress *pProgress)
{
	using namespace GEOMETRY::geom;

	std::string path =OutputFileName;
	//�õ��ļ�·��
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

	//�������ʸ��
	Geodatabase::IFeatureClassPtr pFeatureClass =pshpWS->CreateFeatureClass(OutputFileName,fdef);

	if(!pFeatureClass)
	{
		return false;
	}

	
	pDataset->CreateBuffer();

	
    
    long lwidth,lheight;
	pDataset->GetSize(&lwidth,&lheight);

	//����ֵ
	unsigned char pixel;

	//���Ӷ�ջ��ָ��
	Seed *Seeds;
	int StackPoint;

	//��ǰ����λ��
	int iCurrentPixelx,iCurrentPixely;

	//��ǰɨ��������������
	const unsigned int nPixelCount=lwidth*lheight;
	//��־λ
	boost::dynamic_bitset<> sbitset;
	boost::dynamic_bitset<> processbitset;
	boost::dynamic_bitset<> srcbitset;
	srcbitset.resize(nPixelCount);
	sbitset.resize(nPixelCount);
	processbitset.resize(nPixelCount);

	Seeds = new Seed[nPixelCount];

	unsigned char *lpSrc=0;

	long lpt1,lpt2,drawPt;//���ڱ�־λ�е�λ��
	bool bStartPoint=false; //�Ƿ���ʼ��
	bool bPointfind=false;  //�Ƿ��ҵ��߽��
	IntPoint StartPoint; //��ʼ������
	IntPoint CurPoint,RecordPt; //��ǰ������

	//ɨ�跽��,����Ϊ0������ʱ�뷽������

	int Direction[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
	//��ʼ����
	int BeginDirect;

	//����һ���յĶ����Ҫ��
	GEOMETRY::geom::Geometry* pGeometry =NULL;
	Coordinate coord;

	//��ʼ�༭
	pshpWS->StartEdit();
	pshpWS->StartEditOperation();

	Geodatabase::CFeaturePtr pFeature;

	long i,j;
	long ltotal;
	std::vector<IntPoint> points;

	//����ֵͼת��Ϊ����ͼ
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
			//��ȡ�õ�����ֵ
             //pDataset->PixelIO(1,i+1,j+1,&pixel,true);
			 //����õ�û�д�������Ϊ���ӵ�
			 if(srcbitset.test(lwidth*j+i) && (!processbitset.test(lwidth*j+i)))
			 {
 
				 ltotal =1;
				 sbitset.reset();
				 //��ʼ������
				 
				 Seeds[0].Height = j+1;
				 Seeds[0].Width = i+1;
				 StackPoint = 0;
				 sbitset.set(lwidth*j+i);

				 while( StackPoint != -1)
				 {
					 //ȡ������
					 iCurrentPixelx = Seeds[StackPoint].Width;
					 iCurrentPixely = Seeds[StackPoint].Height;
					 StackPoint--;

					 processbitset.set(lwidth*j+i);
                  
					 //ȡ�õ�ǰָ�봦������ֵ
					  /*pDataset->PixelIO(1,iCurrentPixelx,iCurrentPixely,&pixel,true);*/
					 
					 //�ж�����ĵ㣬����ڷ�Χ�ڣ�����û�����ջ����ѹ���ջ

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
								 //��־λ��Ϊ1
								 sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2);
								 processbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2);

								 ltotal++;

							 }
						 }

					 }

					 //�ж�����ĵ㣬����ڷ�Χ�ڣ�����û�����ջ����ѹ���ջ
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
								 //��־λ��Ϊ1
								 sbitset.set(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1);

								 processbitset.set(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1);
								 ltotal++;

							 }
						 }
					 }

					 //�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ

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
								 //��־λ��Ϊ1
								 sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx);
								 processbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx);

								 ltotal++;

							 }
						 }

					 }

					 //�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ

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
								 //��־λ��Ϊ1
								 sbitset.set(lwidth * iCurrentPixely + iCurrentPixelx-1);
								 processbitset.set(lwidth * iCurrentPixely + iCurrentPixelx-1);

								 ltotal++;

							 }
						 }

					 }
				 }

				 //�ж������������ĵ���Ŀ�Ƿ�С����С��ֵ
				 if(ltotal>=nminSize)
				 {
					 bStartPoint =false;
					 
					 //��������ʸ����
					 points.clear();
					 //�ҵ����Ͻǵ�һ���߽��
					 for(n=0;n<lheight;n++)
					 {
						 for(m=0;m<lwidth;m++)
						 {
							 //����ҵ��߽��
							 if(sbitset.test(lwidth*n+m))
							 {
								 //����Ϊ��ʼ������
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
						 //�赱ǰ��Ϊ��ʼ������
						 CurPoint.x=StartPoint.x;
						 CurPoint.y=StartPoint.y;
						 points.push_back(CurPoint);

						 //��ʼɨ�跽��Ϊ�·�
						 BeginDirect=3;
						 bStartPoint=false;


						 while(!bStartPoint)
						 {
							 bPointfind=false;
							 while(!bPointfind)
							 {
								 //���ɨ�跽����
								 if(3==BeginDirect)
								 {
									 lpt1=lwidth*CurPoint.y+CurPoint.x-1;
									 lpt2=lwidth*CurPoint.y+CurPoint.x;
								 }
								 //ɨ�跽����
								 else if(1==BeginDirect)
								 {
									 lpt1=lwidth*(CurPoint.y-1)+CurPoint.x-1;
									 lpt2=lwidth*(CurPoint.y-1)+CurPoint.x;
								 }
								 //ɨ�跽����
								 else if(0==BeginDirect)
								 {
									 lpt1=lwidth*(CurPoint.y-1)+CurPoint.x;
									 lpt2=lwidth*CurPoint.y+CurPoint.x;
								 }
								 //ɨ�跽����
								 else if(2==BeginDirect)
								 {
									 lpt1=lwidth*(CurPoint.y-1)+CurPoint.x-1;
									 lpt2=lwidth*CurPoint.y+CurPoint.x-1;
								 }


								 //���Ǹ�������ͼ��߽�����
								 //����������߽�㣬����ɨ�跽�������·���
								 if(CurPoint.x==0 && (1==BeginDirect || 3==BeginDirect))
								 {

									 if(sbitset.test(lpt2))
									 {
										 bPointfind=true;
										 drawPt=lpt2;
									 }

								 }
								 //���������ұ߽��,����ɨ�跽�������·���
								 else if(CurPoint.x==lwidth-1 &&(1==BeginDirect || 3==BeginDirect))
								 {

									 if(sbitset.test(lpt1))
									 {
										 bPointfind=true;
										 drawPt=lpt1;
									 }

								 }
								 //���������ϱ߽��,����ɨ�跽�������ҷ���
								 else if(CurPoint.y==0 &&(0==BeginDirect || 2==BeginDirect))
								 {
									 if(sbitset.test(lpt2))
									 {
										 bPointfind=true;
										 drawPt=lpt2;
									 }
								 }
								 //���������±߽��,����ɨ�跽�������ҷ���
								 else if(CurPoint.y==lheight-1 &&(0==BeginDirect || 2==BeginDirect))
								 {
									 if(sbitset.test(lpt1))
									 {
										 bPointfind=true;
										 drawPt=lpt1;
									 }
								 }
								 //����������ͨ���
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
								 //����Ǳ߽��
								 if(bPointfind)
								 {
									 CurPoint.x=CurPoint.x+Direction[BeginDirect][0];
									 CurPoint.y=CurPoint.y+Direction[BeginDirect][1];
									 //����ص���ʼ�㣬�˳�ѭ��
									 if(CurPoint.x==StartPoint.x && CurPoint.y==StartPoint.y)
									 {
										 bStartPoint=true; 

									 }
									 //��¼�߽��
									 /* RecordPt.x =drawPt%lwidth;
									 RecordPt.y =drawPt/lwidth;*/
									 points.push_back(CurPoint);


									 //��ʱ�뷽����ת1��
									 BeginDirect++;
									 if(BeginDirect==4)
									 {
										 BeginDirect=0;
									 }


								 }
								 //�����һ����û���ҵ�����ı�ɨ�跽��
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

							 //����һ���µ�Ҫ��
							 pFeature =pFeatureClass->CreateFeature();
							 pFeature->SetShape( pGeometry);

							 //�ύҪ��
							 pFeatureClass->AddFeature(pFeature.get());
						 }

					 }
				 }
					

				 //������ĵ��־Ϊ�Ѿ�����
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
		std::vector<double> mean; //��ֵ
		std::vector<double> stdval; //��׼��
		long   numpoints; //������Ŀ

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
	//��ԭ�ļ�
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(InputFileName);
	if(!pSrcRS)
	{
		return false;
	}

	//����������
	if(pProgress)
	{
		pProgress->Create("������",SYSTEM::IProgress::Percent,100);
		pProgress->UpdateProgress("",0.01);

	}

	long lFileWidth,lFileHeight;
	pSrcRS->GetSize(&lFileWidth,&lFileHeight);

	std::string syspath =SYSTEM::CSystemPath::GetSystemPath();
	syspath+="temp";

	std::string tempfile =syspath+"\\Extract.tif";
	//������Ӱ��·��
	std::string path =tempfile;
	
	//ɾ�����ڵ���ʱ�ļ�
	_unlink(tempfile.c_str());
	
	path =path.substr(0,path.rfind('\\'));
	Geodatabase::IWorkspace *pdestWS =CRasterWSFactory::GetInstance()->OpenFolder(path.c_str());
	if(!pdestWS)
	{
		return false;
	}

	//����Ӱ����
	Geodatabase::RasFileInfo rasfileInfoDes;
	rasfileInfoDes.lWidth = lFileWidth;			//ͼ��Ŀ��
	rasfileInfoDes.lHeight = lFileHeight;			//ͼ��ĸ߶�
	rasfileInfoDes.lChannelNum = 1;	//ͼ���ͨ����
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
	//�����������ת��ΪRgn
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
		//��ʼ��ÿ��������Ϣ
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
		//����ÿ�����ı�׼��
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

	//��������ƽ��ֵ
	for(i=0;i<sinfos.size();i++)
	{
		
		sinfos[i].numpoints /=lband;
		for(long bandid=0;bandid<lband;bandid++)
		{
           sinfos[i].mean[bandid]/=sinfos[i].numpoints;
		}
        
	}
    double dstd,dmean;
	//����������׼��
	for(long bandid=0;bandid<lband;bandid++)
	{
		for(k=0;k<nclass;k++)
		{
			dstd =0.0;
			dmean =sinfos[k].mean[bandid];
			//����ÿ�����ı�׼��
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
			//�ж��������ĸ�������
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
					//�ж�����ֵ��ƽ��ֵ�Ĳ���Ƿ�С�ڱ�׼������
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
    
   
	
	//ɾ��rgn
	for(int i=0;i<rgns.size();i++)
	{
		::DeleteObject(rgns[i]);
	}
	if(pProgress)
	{
		pProgress->UpdateProgress("",0.1);
	}
    //����shp
    bool bret =CreateShpResult(rasDestDS.get(),OutputFileName,nminsize,pProgress);

	if(pProgress)
	{
		pProgress->UpdateProgress("",1.0);
		pProgress->Close();
	}

	return bret;
}




}