#include "stdafx.h"
#include "GeometrySketch.h"
#include "SymbolFactory.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>



namespace Display
{
	CGeometrySketch::CGeometrySketch(int GeometryType,bool bhasZ ,bool bhasM)
	{

		m_bMultiPart =false;

		m_bMouseMove =false;
		switch(GeometryType)
		{
			//��
		case GEOMETRY::geom::GEOS_POINT:
			m_pGeometry=(Geometry*)GeometryFactory::getDefaultInstance()->createPoint();
			break;
			//��
		case GEOMETRY::geom::GEOS_LINESTRING:

			m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
			break;
			//��Ȧ
		case GEOMETRY::geom::GEOS_LINEARRING:

			m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createLinearRing();
			break;

			//����
		case GEOMETRY::geom::GEOS_MULTILINESTRING:

			m_pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();



			m_bMultiPart =TRUE;
			break;

			//�����
		case GEOMETRY::geom::GEOS_POLYGON:

			m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createPolygon();

			m_bMultiPart =TRUE;
			break;

			//���
		case GEOMETRY::geom::GEOS_MULTIPOINT:

			m_pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiPoint();

			m_bMultiPart =TRUE;
			break;

			//������
		case GEOMETRY::geom::GEOS_MULTIPOLYGON:

			m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createMultiPolygon();

			m_bMultiPart =TRUE;
			break;

		default:
			m_pGeometry =NULL;
			break;

		}

		//�����Ƿ����Zֵ��Mֵ
		if(m_pGeometry)
		{
			m_pGeometry->SetbZ(bhasZ);
			m_pGeometry->SetbM(bhasM);
		}
		m_icurPart=0;

		m_bCurPartFinish =FALSE;

		InitSymbol();


	}

	void CGeometrySketch::Draw(Display::IDisplayPtr pDisplay)
	{
		if(IsEmpty())
		{
			return;
		}

		int type =GetGeometryType();
		switch (type)
		{
			//����ǵ㣬���߶�㣬��ֱ�ӻ�
		case GEOS_POINT:
		case GEOS_MULTIPOINT:
			{
				pDisplay->SetSymbol(m_ptSymbol.get());
				pDisplay->Begin();
				pDisplay->Draw(m_pGeometry);
				pDisplay->End();
				break;
			}
		case GEOS_LINESTRING:
		case GEOS_LINEARRING:
			{
				if(m_bMouseMove)
				{
					//����ǰ������ͼ����
					m_pGeometry->AddPoint(m_MousePt);

				}

				if(m_pGeometry->PointCount()==1)
				{
					//���ֻ��һ���㣬��ֻ����
					Geometry *pPoint =GeometryFactory::getDefaultInstance()->createPoint(m_pGeometry->GetPoint(0));
					pDisplay->SetSymbol(m_ptSymbol.get());
					pDisplay->Begin();
					pDisplay->Draw(pPoint);
					pDisplay->End();
					delete pPoint;

				}
				else
				{
					pDisplay->SetSymbol(m_lineSymbol.get());
					pDisplay->Begin();
					pDisplay->Draw(m_pGeometry);
					pDisplay->End();
				}
				if(m_bMouseMove)
				{
					//����ǰ�����Ƴ�
					m_pGeometry->RemovePoint(m_pGeometry->PointCount()-1);

				}

				break;
			}
		case GEOS_MULTILINESTRING:
			{
				if(!m_bCurPartFinish && m_bMouseMove)
				{
					const_cast<Geometry*>(((MultiLineString*)m_pGeometry)->getGeometryN(m_icurPart))->AddPoint(m_MousePt);
				}
				pDisplay->SetSymbol(m_lineSymbol.get());
				pDisplay->Begin();
				pDisplay->Draw(m_pGeometry);
				pDisplay->End();

				if(!m_bCurPartFinish && m_bMouseMove)
				{
					Geometry *pline =const_cast<Geometry*>(((MultiLineString*)m_pGeometry)->getGeometryN(m_icurPart));
					pline->RemovePoint(pline->PointCount()-1);
				}

				break;
			}
		case GEOS_POLYGON:
			{
				//����ò��ֻ�û�н���,����������㣬һ��������ƶ��㣬һ�����߻��ıպϵ�
				if(!m_bCurPartFinish && m_bMouseMove)
				{

					GEOMETRY::geom::Geometry *pg =((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart);
					if(m_pGeometry->PointCount()==1)
					{
						//����պϵ�
						pg->AddPoint(pg->GetPoint(0));
					}

					pg->InsertPoint(pg->PointCount()-2,m_MousePt);
				}

				if(m_pGeometry->PointCount()==1)
				{
					//���ֻ��һ���㣬��ֻ����
					GEOMETRY::geom::Geometry *pg =((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart);
					GEOMETRY::geom::Geometry *pPoint =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(pg->GetPoint(0));
					pDisplay->SetSymbol(m_ptSymbol.get());
					pDisplay->Begin();
					pDisplay->Draw(pPoint);
					pDisplay->End();
					delete pPoint;
				}
				else
				{
					GEOMETRY::geom::Geometry *pg =((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart);
					pDisplay->SetSymbol(m_lineSymbol.get());
					pDisplay->Begin();
					long l = pg->PointCount();
					pDisplay->Draw(pg);
					pDisplay->End();
				}

				if(!m_bCurPartFinish && m_bMouseMove)
				{
					GEOMETRY::geom::Geometry *pg =((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart);
					if(m_pGeometry->PointCount()==3)
					{
						//�Ƴ��պϵ�
						pg->RemovePoint(pg->PointCount()-1);
						pg->RemovePoint(pg->PointCount()-1);
					}
					else
					{
						pg->RemovePoint(pg->PointCount()-2);
					}
				}
				break;
			}
		default:
			break;
		}
	}


	CGeometrySketch::~CGeometrySketch(void)
	{
		if(m_pGeometry)
		{
			delete m_pGeometry;
		}
	}

	bool CGeometrySketch::IsMultiPart() const
	{
		return m_bMultiPart;
	}

	//�õ�ͼ�ε�����
	int  CGeometrySketch::GetGeometryType() const
	{
		if(m_pGeometry==NULL)
		{
			return -1;
		}

		return m_pGeometry->getGeometryTypeId();

	}
	//������ǰ���֣���ʼ�༭��һ����
	void CGeometrySketch::FinishPart()
	{
		if(!IsMultiPart())
		{
			return;
		}

		//�����һ�����Ѿ��������˲��ֻ�û�е㣬�򷵻�
		if(m_bCurPartFinish)
		{
			return;
		}

		int type =GetGeometryType();
		switch (type)
		{



		case GEOS_MULTILINESTRING:

			break;

			//�����
		case GEOS_POLYGON:
			{
				//��������ǰPartʱ��Ҫ���û��ĵ�һ������ӵ����
				Geometry* pGeometry =(((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart));
				//�������ĿС��2���򲻽�����ǰPart
				if(pGeometry->PointCount()<=2)
				{
					return;
				}
				pGeometry->AddPoint(pGeometry->GetPoint(0));


			}
			break;

		default:
			break;
		}

		m_icurPart++;

		m_bCurPartFinish =TRUE;
	}

	//���һ���ڵ�
	void CGeometrySketch::AddPoint(GEOMETRY::geom::Coordinate &coord)
	{
		if(m_pGeometry==NULL)
		{
			return ;
		}

		int type =GetGeometryType();
		switch (type)
		{
		case GEOS_POINT:
		case GEOS_MULTIPOINT:
		case GEOS_LINESTRING:
			m_pGeometry->AddPoint(coord);
			break;


			//���ж�����ֵ�ͼ��,��ӵ�ʱ��Ҫȷ�����ĸ��������
		case GEOS_MULTILINESTRING:
			//�����һ�����Ѿ��������ƣ����ߵ�ǰͼ���ǿ�ͼ�Σ���ʼһ���µ�part
			if(m_bCurPartFinish || IsEmpty())
			{
				Geometry *pg =NULL;
				pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();

				((MultiLineString*)m_pGeometry)->AddGeometry(pg);
			}

			const_cast<Geometry*>(((MultiLineString*)m_pGeometry)->getGeometryN(m_icurPart))->AddPoint(coord);
			break;

			//�����
		case GEOS_POLYGON:
			{
				//�����һ�����Ѿ���������,��ʼһ���µ�part
				if(m_bCurPartFinish || IsEmpty())
				{
					GEOMETRY::geom::Geometry *pg =NULL;
					pg =(GEOMETRY::geom::Geometry*) GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLinearRing();

					((GEOMETRY::geom::Polygon*)m_pGeometry)->AddGeometry(pg);
				}

				//����αȽ�����,Ҫ����������
				GEOMETRY::geom::Geometry *pg =((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart);

				if(pg->PointCount()==0)
				{
					//��������ֻ��һ���㣬��ֻ��һ����
					pg->AddPoint(coord);

				}
				else if(pg->PointCount()==1)
				{
					//����������
					pg->AddPoint(coord);
					//����պϵ�
					//pg->AddPoint(pg->GetPoint(0));//hhzhao �޸�


				}
				else
				{
					//����һ����
					//pg->InsertPoint(pg->PointCount()-2,coord);
					pg->InsertPoint(pg->PointCount()-1,coord);

				}
			}
			break;

		default:
			break;
		}

		m_bCurPartFinish =FALSE;

	}

	//һ���ڽ������ʺ����,��յ�ǰ������ͼ�Σ�׼������һ��ͼ��
	void CGeometrySketch::SetEmpty()
	{
		if(m_pGeometry)
		{
			m_pGeometry->SetEmpty();
		}

		m_icurPart =0;

		m_bMouseMove =false;
	}



	//��ǰ�����е�ͼ���Ƿ��������Ҫ���Ƶ�ͼ������
	bool CGeometrySketch::IsRightGeometry() const
	{
		if(m_pGeometry->isEmpty())
		{
			return false;
		}
		int type =GetGeometryType();

		long ltotal =m_pGeometry->PointCount();
		switch (type)
		{
		case GEOS_LINESTRING:
			{
				if(ltotal<2)
				{
					return false;
				}
			}
			break;



		case GEOS_MULTILINESTRING:

			break;

			//�����
		case GEOS_POLYGON:
			{
				//Geometry* pGeometry =(((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart));
				////�������ĿС��2���򲻽�����ǰPart
				//if(pGeometry->PointCount()<=2)
				//{
				//	return;
				//}
			}
			break;

		default:
			break;
		}
		return true;
	}

	bool CGeometrySketch::IsEmpty() const
	{
		if(m_pGeometry)
		{
			if(m_pGeometry->PointCount()>0)
			{
				return false;
			}
		}
		return true;
	}

	//�õ����һ����
	Coordinate CGeometrySketch::GetlastPoint() const
	{
		Coordinate coord;

		if(IsEmpty())
		{
			return coord;
		}

		long pointnum;

		int type =GetGeometryType();
		//���ͼ���жಿ��
		if(m_bMultiPart)
		{
			//����Ƕ������
			if(type==GEOS_MULTIPOINT || type==GEOS_MULTILINESTRING)
			{
				Geometry *pGeometry =const_cast<Geometry*>(((GeometryCollection*)m_pGeometry)->getGeometryN(m_icurPart));

				pointnum =pGeometry->PointCount();
				if(pointnum>0)
				{
					coord =pGeometry->GetPoint(pointnum-1);
				}
			}
			//����ε����
			else if(type ==GEOS_POLYGON)
			{
				//�⻷
				if(m_icurPart==0)
				{
					Geometry *pGeometry =const_cast<Geometry*>( (Geometry*)(((GEOMETRY::geom::Polygon*)m_pGeometry)->getExteriorRing()));

					pointnum =pGeometry->PointCount();
					if(pointnum>0)
					{
						coord =pGeometry->GetPoint(pointnum-1);
					}
				}
				else
				{
					Geometry *pGeometry =const_cast<Geometry*>( (Geometry*)(((GEOMETRY::geom::Polygon*)m_pGeometry)->getInteriorRingN(m_icurPart-1)));

					pointnum =pGeometry->PointCount();
					if(pointnum>0)
					{
						coord =pGeometry->GetPoint(pointnum-1);
					}  
				}
			}
		}
		//�����ֵ����
		else
		{
			Geometry *pGeometry =m_pGeometry;

			pointnum =pGeometry->PointCount();
			if(pointnum>0)
			{
				coord =pGeometry->GetPoint(pointnum-1);
			}
		}

		return coord;

	}

	//�õ���ǰPart�ĵ�һ����
	Coordinate CGeometrySketch::GetCurPartFirstPt() const
	{
		Coordinate coord;
		if(m_bMultiPart)
		{
			IGeometryCollection *pCollection =NULL;
			pCollection = dynamic_cast<IGeometryCollection*>(m_pGeometry);

			if(pCollection!=NULL)
			{
				Geometry *pg =pCollection->GetGeometry(m_icurPart);
				if(!pg->isEmpty())
				{
					coord =pg->GetPoint(0);
				}
			}
		}
		else
		{
			if(m_pGeometry->PointCount()>0)
			{
				coord =m_pGeometry->GetPoint(0);
			}
		}

		return coord;
	}

	//�滻�����ʵ�ǰͼ�Σ���������Ϣ
	void CGeometrySketch::ReplaceGeometry(GEOMETRY::geom::Geometry *pGeometry, long &curPart, bool &bpartFinish)
	{
		if(m_pGeometry)
		{
			delete m_pGeometry;
		}
		Geometry *pg =pGeometry->clone();

		m_pGeometry =pg;

		m_icurPart= curPart;
		m_bCurPartFinish =bpartFinish;

	}

	void CGeometrySketch::InitSymbol()
	{
		COLORREF color =RGB(0,0,0);
		//�����
		m_ptSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_MARKER_SYMBOL);
		m_ptSymbol->SetColor(color);
		dynamic_cast<CSimpleMarkerSymbol*>(m_ptSymbol.get())->SetMarkerSize(1.0f);

		//�߷���
		m_lineSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_LINE_SYMBOL);
		m_lineSymbol->SetColor(color);
		dynamic_cast<CSimpleLineSymbol*>(m_lineSymbol.get())->SetLineWidth(0.3f);
	}

	void CGeometrySketch::MouseMove(GEOMETRY::geom::Coordinate &coord)
	{

		if(!IsEmpty())
		{
			m_MousePt =coord;
			m_bMouseMove =true;
		}
	}



}