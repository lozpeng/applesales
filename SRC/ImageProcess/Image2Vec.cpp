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
	//��ԭ�ļ�
	Geodatabase::IRasterDatasetPtr pDataset =pSrcWp->OpenRasterDataset(infile);
	if(!pDataset)
	{
		return false;
	}

	std::string path =outfile;
	//�õ��ļ�·��
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

	//�������ʸ��
	Geodatabase::IFeatureClassPtr pFeatureClass =pshpWS->CreateFeatureClass(outfile,fdef);

	if(!pFeatureClass)
	{
		return false;
	}
    

	pDataset->CreateBuffer();



	long lwidth,lheight;
	pDataset->GetSize(&lwidth,&lheight);
    
	//��Сʸ��������Ĵ�С
	int nminSize=10;
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

	//��ԭʼ���ͼ��ת��Ϊ����ͼ
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