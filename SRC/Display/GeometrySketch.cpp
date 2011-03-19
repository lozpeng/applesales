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
			//点
		case GEOMETRY::geom::GEOS_POINT:
			m_pGeometry=(Geometry*)GeometryFactory::getDefaultInstance()->createPoint();
			break;
			//线
		case GEOMETRY::geom::GEOS_LINESTRING:

			m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
			break;
			//线圈
		case GEOMETRY::geom::GEOS_LINEARRING:

			m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createLinearRing();
			break;

			//多线
		case GEOMETRY::geom::GEOS_MULTILINESTRING:

			m_pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();



			m_bMultiPart =TRUE;
			break;

			//多边形
		case GEOMETRY::geom::GEOS_POLYGON:

			m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createPolygon();

			m_bMultiPart =TRUE;
			break;

			//多点
		case GEOMETRY::geom::GEOS_MULTIPOINT:

			m_pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiPoint();

			m_bMultiPart =TRUE;
			break;

			//多多边形
		case GEOMETRY::geom::GEOS_MULTIPOLYGON:

			m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createMultiPolygon();

			m_bMultiPart =TRUE;
			break;

		default:
			m_pGeometry =NULL;
			break;

		}

		//设置是否具有Z值或M值
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
			//如果是点，或者多点，则直接画
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
					//将当前鼠标点添到图形中
					m_pGeometry->AddPoint(m_MousePt);

				}

				if(m_pGeometry->PointCount()==1)
				{
					//如果只有一个点，则只画点
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
					//将当前鼠标点移除
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
				//如果该部分还没有结束,则加入两个点，一个是鼠标移动点，一个是线环的闭合点
				if(!m_bCurPartFinish && m_bMouseMove)
				{

					GEOMETRY::geom::Geometry *pg =((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart);
					if(m_pGeometry->PointCount()==1)
					{
						//加入闭合点
						pg->AddPoint(pg->GetPoint(0));
					}

					pg->InsertPoint(pg->PointCount()-2,m_MousePt);
				}

				if(m_pGeometry->PointCount()==1)
				{
					//如果只有一个点，则只画点
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
						//移除闭合点
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

	//得到图形的类型
	int  CGeometrySketch::GetGeometryType() const
	{
		if(m_pGeometry==NULL)
		{
			return -1;
		}

		return m_pGeometry->getGeometryTypeId();

	}
	//结束当前部分，开始编辑下一部分
	void CGeometrySketch::FinishPart()
	{
		if(!IsMultiPart())
		{
			return;
		}

		//如果上一部分已经结束，此部分还没有点，则返回
		if(m_bCurPartFinish)
		{
			return;
		}

		int type =GetGeometryType();
		switch (type)
		{



		case GEOS_MULTILINESTRING:

			break;

			//多边形
		case GEOS_POLYGON:
			{
				//当结束当前Part时，要将该环的第一个点添加到最后
				Geometry* pGeometry =(((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart));
				//如果点数目小于2，则不结束当前Part
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

	//添加一个节点
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


			//具有多个部分的图形,添加点时，要确定在哪个部分添加
		case GEOS_MULTILINESTRING:
			//如果上一部分已经结束绘制，或者当前图形是空图形，则开始一个新的part
			if(m_bCurPartFinish || IsEmpty())
			{
				Geometry *pg =NULL;
				pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();

				((MultiLineString*)m_pGeometry)->AddGeometry(pg);
			}

			const_cast<Geometry*>(((MultiLineString*)m_pGeometry)->getGeometryN(m_icurPart))->AddPoint(coord);
			break;

			//多边形
		case GEOS_POLYGON:
			{
				//如果上一部分已经结束绘制,则开始一个新的part
				if(m_bCurPartFinish || IsEmpty())
				{
					GEOMETRY::geom::Geometry *pg =NULL;
					pg =(GEOMETRY::geom::Geometry*) GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLinearRing();

					((GEOMETRY::geom::Polygon*)m_pGeometry)->AddGeometry(pg);
				}

				//多边形比较特殊,要加入两个点
				GEOMETRY::geom::Geometry *pg =((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart);

				if(pg->PointCount()==0)
				{
					//如果这个环只有一个点，则只加一个点
					pg->AddPoint(coord);

				}
				else if(pg->PointCount()==1)
				{
					//加入两个点
					pg->AddPoint(coord);
					//加入闭合点
					//pg->AddPoint(pg->GetPoint(0));//hhzhao 修改


				}
				else
				{
					//插入一个点
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

	//一般在结束画笔后调用,清空当前所画的图形，准备画下一个图形
	void CGeometrySketch::SetEmpty()
	{
		if(m_pGeometry)
		{
			m_pGeometry->SetEmpty();
		}

		m_icurPart =0;

		m_bMouseMove =false;
	}



	//当前画笔中的图形是否符合它所要绘制的图形类型
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

			//多边形
		case GEOS_POLYGON:
			{
				//Geometry* pGeometry =(((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(m_icurPart));
				////如果点数目小于2，则不结束当前Part
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

	//得到最后一个点
	Coordinate CGeometrySketch::GetlastPoint() const
	{
		Coordinate coord;

		if(IsEmpty())
		{
			return coord;
		}

		long pointnum;

		int type =GetGeometryType();
		//如果图形有多部分
		if(m_bMultiPart)
		{
			//如果是多点或多线
			if(type==GEOS_MULTIPOINT || type==GEOS_MULTILINESTRING)
			{
				Geometry *pGeometry =const_cast<Geometry*>(((GeometryCollection*)m_pGeometry)->getGeometryN(m_icurPart));

				pointnum =pGeometry->PointCount();
				if(pointnum>0)
				{
					coord =pGeometry->GetPoint(pointnum-1);
				}
			}
			//多边形的情况
			else if(type ==GEOS_POLYGON)
			{
				//外环
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
		//单部分的情况
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

	//得到当前Part的第一个点
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

	//替换掉画笔当前图形，并更新信息
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
		//点符号
		m_ptSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_MARKER_SYMBOL);
		m_ptSymbol->SetColor(color);
		dynamic_cast<CSimpleMarkerSymbol*>(m_ptSymbol.get())->SetMarkerSize(1.0f);

		//线符号
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