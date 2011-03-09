#include "stdafx.h"
#include "EditDrawEllipseTool.h"
#include "IMapCtrl.h"
#include "SpatialQuery.h"
#include "SymbolFactory.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"
#include "ISymbol.h"
#include "DisplayDef.h"
#include "ILayer.h"
#include "IGeoDataObject.h"
#include "IWorkspace.h"
//#include "Shape.hxx"
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>

namespace Editor
{

	static CActionEditDrawEllipse gActionEditDrawEllipse;

	CActionEditDrawEllipse::CActionEditDrawEllipse(void) : ITool("ActionEditDrawEllipse")
	{
		
	}

	CActionEditDrawEllipse::~CActionEditDrawEllipse(void)
	{

	}

	//��ʼ��

	void CActionEditDrawEllipse::Initialize(Framework::IUIObject *pTargetControl)
	{
		ITool::Initialize(pTargetControl);
	}
	void CActionEditDrawEllipse::LButtonDownEvent(UINT nFlags, CPoint point)
	{
		if (!m_bStartDraw)
		{
			m_ulPt = point;

			m_bStartDraw = true;
		}
		else
		{
			m_lrPt = point;

			m_bStartDraw = false;

			ActionDraw();

			AddEllipse(m_ulPt, m_lrPt);
		}
	}

	void CActionEditDrawEllipse::MouseMoveEvent(UINT nFlags, CPoint point)
	{	
		if (m_bStartDraw)
		{
			m_lrPt = point;

			ActionDraw();
		}
	}

	/*--------------------�����Ƶľ�����ӵ�Ŀ��ͼ����---------------------*/
	void CActionEditDrawEllipse::AddEllipse(CPoint ulPt, CPoint lrPt)
	{
		//��ȡ���ͼ�ؼ�
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//��ȡ�����
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;

		//Editor::CEditorPtr pEdit =pMap->GetEditor();
		//if(!pEdit)
		//{
		//	return;
		//}

		//��ñ༭ͼ��Ĺ����ռ�
		Carto::ILayer *pLayer ;//= pEdit->GetCurLayer();
		if (!pLayer)
		{
			return;
		}

		Geodatabase::IGeodataObjectPtr pDataObject = pLayer->GetDataObject();
		if (!pDataObject)
		{
			return;
		}

		Geodatabase::IWorkspace* pWorkspace = pDataObject->GetWorkspace();
		if (!pWorkspace)
		{
			return;
		}

		//Ŀǰֻ֧�ֶ��ļ����б༭
		if(pWorkspace->GetType()!=Geodatabase::WT_FileSystem)
		{
			return;
		}

		bool bz,bm;
		Geodatabase::IFeatureClass *pFeatureClass = dynamic_cast<Geodatabase::IFeatureClass*>(pDataObject.get());
		bz =pFeatureClass->HasZ();
		bm =pFeatureClass->HasM();

		//Ҫ��ӵļ���ͼ��
		Geometry *pGeometry = NULL;

		long lShapeType= pFeatureClass->ShapeType();

		switch (lShapeType)
		{

		case GEOMETRY::geom::GEOS_LINESTRING:	
			{

				pGeometry = (Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
				pGeometry->SetbZ(bz);
				pGeometry->SetbM(bm);

				SplitEllipse(pGeometry);

			}
			break;
		case GEOMETRY::geom::GEOS_MULTILINESTRING:
			{


				pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();
				pGeometry->SetbZ(bz);
				pGeometry->SetbM(bm);

				Geometry *pg =NULL;
				pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();

				SplitEllipse(pg);
				((MultiLineString*)pGeometry)->AddGeometry(pg);

			}
			break;

		case GEOMETRY::geom::GEOS_POLYGON:
			{

				pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();
				pGeometry->SetbZ(bz);
				pGeometry->SetbM(bm);

				Geometry *pg =NULL;
				pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLinearRing();

				SplitEllipse(pg);
				((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry(pg);
			}

			break;

		default:
			return;
			break;
		}

		//pEdit->AppendGeometry(pGeometry);

		delete pGeometry;
		pGeometry =NULL;

		pMapCtrl->UpdateControl(drawAll);
	}

	/*--------------------�ڿռ��ϻ�����ʱͼ��---------------------*/
	void CActionEditDrawEllipse::ActionDraw()
	{
		//��ȡ���ͼ�ؼ�
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;


		//��ȡ�����
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;

		//������ʾ
		Display::IDisplayPtr dispaly = pMap->GetDisplay();
		dispaly->SetDrawBuffer(drawEdit);
		dispaly->DrawBackgroud();

		//������Բ
		long left = m_ulPt.x;
		long top  = m_ulPt.y;
		long right = m_lrPt.x;
		long bottom = m_lrPt.y;

		DIS_RECT *pEllipse;
		CreateDisplayRect(pEllipse);
		pEllipse->left = left;
		pEllipse->right = right;
		pEllipse->top = top;
		pEllipse->bottom = bottom;

		//������Բ
		Display::CDC *pDC =dispaly->GetDrawDC();

		LINE_STYLE pLineStyle;
		pLineStyle.lColor = RGB(0, 0, 0);
		pLineStyle.lWidth = 0.6f;
		pLineStyle.eStyle = SOLID;
		DISPLAY_HANDLE pnewPen = pDC->CreatePen(pLineStyle);

		DISPLAY_HANDLE pold = pDC->SelectObject(pnewPen);

		pDC->DrawEllipse(*pEllipse);

		delete pEllipse;
		pEllipse = NULL;

		pDC->SelectObject(pold);
		pDC->RemoveHandle(pnewPen);

		pMapCtrl->RefreshScreen();
	}
	
	/*------------------------�ָ���Բ---------------------*/
	void CActionEditDrawEllipse::SplitEllipse(GEOMETRY::geom::Geometry *pGeometry)
	{
		//CttShape cShape;
		//cShape.Create();
		//

		//STPoint centerPt;			//���ĵ�	
		//STPoint ulPt;				//���Ͻǵ�
		//STPoint lrPt;				//���½ǵ�

		////��ȡ���ͼ�ؼ�
		//Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		//if(!pMapCtrl)
		//	return;

		////��ȡ�����
		//Carto::CMapPtr pMap = pMapCtrl->GetMap();
		//if(!pMap)
		//	return;

		////ת��Բ��Ϊ��������
		//pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_ulPt.x, m_ulPt.y, ulPt.x, ulPt.y);
		//pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_lrPt.x, m_lrPt.y, lrPt.x, lrPt.y);

		//centerPt.x =(ulPt.x + lrPt.x) * 0.5;
		//centerPt.y =(ulPt.y + lrPt.y) * 0.5;
		//

		//double dmajor = (lrPt.x - ulPt.x) * 0.5;
		//double dminor = (ulPt.y - lrPt.y) * 0.5;


		//cShape.MakeEllipse(centerPt, dmajor, dminor, 720, NULL, NULL);

		////��������Geometry
		//PSTPoint pstPoint = NULL;
		//cShape.GetAllPointsPtr(NULL,&pstPoint,NULL,NULL,NULL);
		//long lptnum;
		//cShape.GetNumPoints(&lptnum);

		//Coordinate coord;
		//for(long i=0;i<lptnum;i++)
		//{
		//	coord.x =pstPoint[i].x;
		//	coord.y =pstPoint[i].y;

		//	pGeometry->AddPoint(coord);
		//}

		//cShape.Free();
	}	
}