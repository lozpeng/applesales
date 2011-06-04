#include "stdafx.h"
#include "CEditor.h"
#include "FeatureLayer.h"
#include "IWorkspace.h"
#include "ITable.h"
#include "LayerArray.h"
#include "Feature.h"
#include "IFeatureClass.h"
#include "CreateFeatureTask.h"
//#include "ExtendTrimTask.h"
//#include "LineSplitTask.h"
//#include "PolygonSplitTask.h"
//#include "MirrorFeatureTask.h"
//#include "IEditorListener.h"
#include "IMapCtrl.h"
//#include "SnapAgent.h"
//#include "DlgsnapOption.h"
//#include "EditorRes.h"
//#include "DlgFeatureAttriEdit.h"
//#include "DlgKeyboardinput.h"
//#include "DlgInputSketchCoord.h"
#include "ShapefileWorkspace.h"

#include <geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>

namespace Editor
{


	CEditor::CEditor(Carto::CMap *pMap)
	{
		m_pGeoMap =pMap;
		m_bEditing =false;    

		m_bInVertexEdit =false;

		m_bSketch =false;

		m_bEditFeature =false;

		mg_undoIndex = -1;


		m_memUndoIndex =-1;

		m_curLayer =NULL;

		//��׽����Ϊ10������
		m_screenTolerance =10;

		//��ʼ�����е�����
		InitEditTask();
	}

	CEditor::~CEditor()
	{
		if(m_bEditing)
		{
			StopEdit(false);
		}

		//ɾ���༭����
		DeleteAllTask();
	}

	bool CEditor::IsEditing()
	{
		return m_bEditing;
	}

	void CEditor::StartEdit()
	{
		if(!m_pGeoMap)
		{
			return;
		}
		Carto::CLayerArray &layers =m_pGeoMap->GetLayers();
		int num =layers.GetSize();
		Carto::ILayerPtr pLayer;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;
		Geodatabase::IWorkspace *pWorkspace =NULL;

		std::vector<std::string> names;
		//�Ե�ͼ�е�ʸ�������ñ༭״̬
		for(int i=0;i<num;i++)
		{
			pLayer =layers.GetAt(i);
			if(pLayer->GetLayerType()!=Carto::FeatureLayer)
			{
				continue;
			}

			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());
			if(!pFeatureClass)
			{
				continue;
			}

			pWorkspace =pFeatureClass->GetWorkspace();
			//Ŀǰֻ֧�ֶ��ļ����б༭
			/*if(pWorkspace->GetType()!=Geodatabase::WT_FileSystem)
			{
			continue;
			}*/
			//�����ռ俪ʼ�༭״̬
			pWorkspace->StartEdit();

			names.push_back(pLayer->GetName());

			m_EditLayers.push_back(pLayer.get());

		}
		if(!names.empty())
		{
			ChangeCurLayer(names[0]);
		}

		//for(int i=0;i<IEditorListener::allListeners.size();i++)
		//{
		//	IEditorListener::allListeners[i]->OnUpdateTagetLayers(names,0);
		//}

		int curtaskId =0;
		names.clear();

		for(int i=0;i<m_allTasks.size();i++)
		{
			names.push_back(m_allTasks[i]->GetName());
			if(names[i] =="������Ҫ��")
			{
				curtaskId =i;
			}
		}

		//for(int i=0;i<IEditorListener::allListeners.size();i++)
		//{
		//	IEditorListener::allListeners[i]->OnUpdateEditTasks(names,curtaskId);
		//}

		if(!names.empty())
		{
			SetEditTask(names[curtaskId]);
		}


		m_bEditing =true;
	}

	void CEditor::StopEdit(bool bSave)
	{
		Carto::CLayerArray &layers =m_pGeoMap->GetLayers();
		int num =layers.GetSize();
		Carto::ILayerPtr pLayer;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;
		Geodatabase::IWorkspace *pWorkspace =NULL;


		//�����༭
		for(int i=0;i<num;i++)
		{
			pLayer =layers.GetAt(i);
			if(pLayer->GetLayerType()!=Carto::FeatureLayer)
			{
				continue;
			}

			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());
			if(!pFeatureClass)
			{
				continue;
			}

			pWorkspace =pFeatureClass->GetWorkspace();

			//Ŀǰֻ֧�ֶ��ļ����б༭
			/*if(pWorkspace->GetType()!=Geodatabase::WT_FileSystem)
			{
			continue;
			}*/
			//�����ռ�����༭״̬
			pWorkspace->StopEdit(bSave);


		}
		m_bEditing =false;

		OnEndEdit();

		//ˢ����ͼ
		Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(pActiveMapCtrl)
		{
			pActiveMapCtrl->UpdateControl(drawAll);
		}


	}

	void CEditor::SaveEdit()
	{
		Carto::CLayerArray &layers =m_pGeoMap->GetLayers();
		int num =layers.GetSize();
		Carto::ILayerPtr pLayer;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;
		Geodatabase::IWorkspace *pWorkspace =NULL;

		//����༭
		for(int i=0;i<num;i++)
		{
			pLayer =layers.GetAt(i);
			if(pLayer->GetLayerType()!=Carto::FeatureLayer)
			{
				continue;
			}

			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());
			if(!pFeatureClass)
			{
				continue;
			}

			pWorkspace =pFeatureClass->GetWorkspace();

			//�����ռ�����༭״̬
			pWorkspace->Commit();


		}

		//ɾ���ع��б�
		ClearMemUndo();

		mg_undoCircles.clear();
		mg_undoIndex = -1;


		ClearModifyGeometry();

		//ˢ����ͼ
		Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(pActiveMapCtrl)
		{
			pActiveMapCtrl->UpdateControl(drawAll);
		}
	}

	void CEditor::Undo()
	{
		if(m_bInVertexEdit)
		{
			VertexUndo();
		}
		else
		{
			if(mg_undoIndex<0)
				return;



			STCircle circle = mg_undoCircles[mg_undoIndex];

			Geodatabase::IFeatureClass *pFeatureClass =NULL;

			for(int i=0; i<circle.layers.size(); i++)
			{
				pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(circle.layers[i]->GetDataObject().get());
				if(!pFeatureClass)
				{
					continue;
				}
				//���ù����ռ��undo
				pFeatureClass->GetWorkspace()->UndoEdit();


			}

			mg_undoIndex--;
		}


		//ˢ����ͼ
		Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		pActiveMapCtrl->UpdateControl(drawAll);
	}

	void CEditor::Redo()
	{
		if(m_bInVertexEdit)
		{
			VertexRedo();
		}
		else
		{
			long lCircleCount = mg_undoCircles.size();
			if( (mg_undoIndex+1) >(lCircleCount-1))
				return;


			STCircle circle = mg_undoCircles[mg_undoIndex+1];
			Geodatabase::IFeatureClass *pFeatureClass =NULL;
			for(int i=0; i<circle.layers.size(); i++)
			{
				pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(circle.layers[i]->GetDataObject().get());
				if(!pFeatureClass)
				{
					continue;
				}
				pFeatureClass->GetWorkspace()->RedoEdit();

			}

			mg_undoIndex++;	
		}

		//ˢ����ͼ
		Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		pActiveMapCtrl->UpdateControl(drawAll);

	}

	bool CEditor::CanUndo()
	{
		if(m_bInVertexEdit)
		{
			return VertexCanUndo();
		}
		else
		{
			if(mg_undoIndex<0)
				return false;

			return true;
		}
	}

	bool CEditor::CanRedo()
	{
		if(m_bInVertexEdit)
		{
			return VertexCanRedo();
		}
		else
		{
			long lCircleCount = mg_undoCircles.size();
			if( (mg_undoIndex+1) >(lCircleCount-1))
				return false;

			return true;
		}
	}

	void CEditor::DrawEdit(Display::IDisplayPtr pDisplay)
	{
		pDisplay->Begin();

		//�������ڱ༭��ͼ��
		if(!m_modifyGeometrys.empty())
		{
			for(int i=0; i<m_modifyGeometrys.size(); i++)
				DrawEditShape(pDisplay, m_modifyGeometrys[i]);
		}
		//���ƻ����е�ͼ��
		if(m_pSketch)
		{
			if(!m_pSketch->IsEmpty())
			{
				DrawEditShape(pDisplay,m_pSketch->GetGeometry());
				
				//��������ƶ�����һ����
				DrawMousePoint(pDisplay);     
			}
		}

		if(m_bSketch)
		 DrawSnapCursor(pDisplay);


		pDisplay->End();
	}

	/****************************************************************************************
	*���ʲ����ĺ���
	*****************************************************************************************/

	//����һ����Ҫ�༭ͼ������Ļ���
	void CEditor::CreateEditSketch(Carto::ILayer *pmapLayer)
	{

		if(pmapLayer->GetLayerType()!=Carto::FeatureLayer)
		{
			return;
		}
		Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pmapLayer->GetDataObject().get());

		int type =pFeatureClass->ShapeType();

		bool bz =pFeatureClass->HasZ();
		bool bm =pFeatureClass->HasM();

		m_pSketch.reset(new Display::CGeometrySketch(type,bz,bm));
	}

	void CEditor::AddSketchPoint(GEOMETRY::geom::Coordinate &point,double dz /* =0.0 */,double dm /* =0.0 */)
	{
		if(!m_pSketch)
		{
			return;
		}

		point.z =dz;
		point.m =dm;


		//����ǵ�һ���㣬��ԭ���յ�Geometry����ع�
		if(m_pSketch->IsEmpty() && m_memUndoStack.empty())
		{
			GEOMETRY::geom::Geometry *pg =m_pSketch->GetGeometry()->clone();

			this->PushGeometry2Undo(pg,m_pSketch->m_icurPart,m_pSketch->m_bCurPartFinish);

			m_memUndoIndex--;
		}

		m_pSketch->AddPoint(point);

		//�����ʵ�ǰͼ�μ���ع�
		Geometry *pg =m_pSketch->GetGeometry()->clone();

		PushGeometry2Undo(pg,m_pSketch->m_icurPart,m_pSketch->m_bCurPartFinish);

		//m_bSetLength =m_bSetDirection =false;


	}

	//�������Ƶ�ǰͼ�Σ����ѻ��Ƶ�ͼ�ν����༭������
	void CEditor::FinishSketch()
	{
		if(!m_pSketch)
		{
			return;
		}
		m_pSketch->FinishPart();
		if(!m_pSketch->IsRightGeometry())
		{
			return;
		}


		if(m_curTask!=NULL)
		{
			m_curTask->DoWork();
		}

		//���ع���ջ�ƿ�
		m_bSketch =false;
		m_bInVertexEdit =false;
		ClearMemUndo();

		m_pSketch->SetEmpty();

		//ˢ����ͼ
		Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		pActiveMapCtrl->UpdateControl(drawAll);


	}

	void CEditor::FinishSketchPart()
	{

		if(!m_pSketch)
		{
			return;
		}

		m_pSketch->FinishPart();
	}

	void CEditor::SetSketchEmpty()
	{
		if(!m_pSketch)
		{
			return;
		}
		m_pSketch->SetEmpty();
	}

	GEOMETRY::geom::Geometry* CEditor::GetSketchGeometry() const
	{
		if(!m_pSketch)
		{
			return NULL;
		}
		return m_pSketch->GetGeometry();

	}

	/****************************************************************************************
	*����Ϊ�ڵ㲶׽��صĺ���
	*****************************************************************************************/

	void CEditor::Snap(GEOMETRY::geom::Coordinate inPoint, GEOMETRY::geom::Coordinate &outPoint)
	{
		outPoint =inPoint;

		m_curSketchCoord =outPoint;

		Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();

		Carto::CMapPtr pMap =pActiveMapCtrl->GetMap();

		long sc =m_screenTolerance;
		double dtolerance;
		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(sc,dtolerance);


		CSnapAgent *pAgent =NULL;

		bool bsnaped =false;

		GEOMETRY::geom::Coordinate tempPt =inPoint;

		for(size_t i=0;i<m_snaplist.size();i++)
		{
			tempPt =inPoint;
			//pAgent =m_snaplist[i];
			//if(pAgent->Snap(&tempPt,dtolerance))
			//{
			//	bsnaped =true;
			//	break;
			//}

		}

		if(bsnaped)
		{
			m_curSketchCoord =outPoint =tempPt;

		}
		else
		{

			m_curSketchCoord = outPoint =inPoint;

		}
	}

	void CEditor::ShowSnapDlg()
	{
		//CDllResource hdll;
		//CDlgSnapOption dlg;
		//dlg.SetEdit(this);

		//dlg.DoModal();
	}
	double CEditor::GetSnapTolerance()
	{
		return m_screenTolerance;
	}

	void CEditor::SetSnapTolerance(double d)
	{
		m_screenTolerance =d;
	}

	void CEditor::AddSnapAgent(Carto::ILayer *pLayer, unsigned long snaptype)
	{
		//CSnapAgent *pAgent =NULL;
		//for(size_t i=0;i<m_snaplist.size();i++)
		//{
		//	if(m_snaplist[i]->GetFeatureLayer()==pLayer)
		//	{
		//		pAgent =m_snaplist[i];
		//		break;
		//	}
		//}
		//if(pAgent==NULL)
		//{
		//	pAgent =new CSnapAgent(pLayer);
		//	m_snaplist.push_back(pAgent);
		//	pAgent->SetSnaptype(snaptype);

		//}
		//else
		//{
		//	pAgent->SetSnaptype(snaptype);
		//}
	}

	unsigned long CEditor::GetLayerSnaptype(Carto::ILayer *pmapLayer)
	{
		//�ڲ�׽�б��в��Ҹ�ͼ�㣬���û�У��򷵻�û�в�׽
		//CSnapAgent *pAgent =NULL;
		//for(size_t i=0;i<m_snaplist.size();i++)
		//{
		//	if(m_snaplist[i]->GetFeatureLayer()==pmapLayer)
		//	{
		//		pAgent =m_snaplist[i];
		//		break;
		//	}
		//}
		//if(pAgent==NULL)
		//{
		//	return 0;

		//}
		//else
		//{
		//	return pAgent->GetSnaptype();
		//}
		return 0;
	}

	void CEditor::RemoveSnapAgent(Carto::ILayer *pmapLayer)
	{

	}

	void CEditor::RemoveAllSnapAgent()
	{
		if(m_snaplist.empty())
		{
			return;
		}
		for(size_t i=0; i<m_snaplist.size();i++)
		{
			delete m_snaplist[i];
		}

		m_snaplist.clear();
	}

	/****************************************************************************************
	*����Ϊ���úͻ�ȡ��ǰ�༭ͼ��ĺ���
	*****************************************************************************************/

	void CEditor::ChangeCurLayer(std::string layername)
	{
		std::string name;
		int index;

		if(m_curLayer)
		{

			//����͵�ǰ����ͬ������
			if(layername ==m_curLayer->GetName())
			{
				return;
			}
		}

		bool bfind =false;

		Carto::ILayer* pLayer = NULL;

		Carto::CLayerArray &layers =m_pGeoMap->GetLayers();
		int num =layers.GetSize();

		//�Ե�ͼ�е�ʸ�������ñ༭״̬
		for(int i=0;i<num;i++)
		{
			pLayer =layers.GetAt(i).get();
			if(pLayer->GetLayerType()!=Carto::FeatureLayer)
			{
				continue;
			}

			if(pLayer->GetName()==layername)
			{
				bfind =true;
				break;
			}

		}


		if(bfind)
		{
			//��Ϊ��ǰ�༭��
			m_curLayer =pLayer;
			//֪ͨĿ����Ѿ������ı�
			OnTagetLayerChanged();
		}
	}

	void CEditor::OnTagetLayerChanged()
	{
		//�����ǰ�����Ǵ�����Ҫ��
		if(m_curTask->GetType()==CreateNewFeatrue )
		{
			//����һ���͵�ǰ������Ļ���
			CreateEditSketch(m_curLayer);
		}
	}

	/****************************************************************************************
	*����Ϊ���úͻ�ȡ�༭����ĺ���
	*****************************************************************************************/


	void CEditor::InitEditTask()
	{
		//����Ҫ�ض���
		IEditTask *pTask =new CCreateFeatureTask(this);
		m_allTasks.push_back(pTask);
		m_curTask =pTask;

		//�ߵ��ӳ����ü�
		//pTask =new CExtendTrimTask(this);
		//m_allTasks.push_back(pTask);

		////�ߴ��
		//pTask =new CLineSplitTask(this);
		//m_allTasks.push_back(pTask);

		////����δ��
		//pTask =new CPolygonSplitTask(this);
		//m_allTasks.push_back(pTask);

		////����
		//pTask =new CMirrorFeatureTask(this);
		//m_allTasks.push_back(pTask);
	}

	void CEditor::SetEditTask(std::string &taskname)
	{
		if(m_allTasks.empty())
		{
			return;
		}
		if(m_curTask)
		{
			if(m_curTask->GetName()==taskname)
			{
				return;
			}
		}

		for(size_t i =0;i<m_allTasks.size();i++)
		{
			if(m_allTasks[i]->GetName()==taskname)
			{
				m_curTask = m_allTasks[i];
				break;
			}
		}

		//֪ͨ��ǰ�༭�������ı�
		OnEditTaskChanged();
	}

	void CEditor::OnEditTaskChanged()
	{
		long ltype =m_curTask->GetType();
		if(ltype==CreateNewFeatrue)
		{
			//����һ���͵�ǰ������Ļ���
			CreateEditSketch(m_curLayer);
		}
		else if(ltype ==ExtendTrimLine || ltype ==LineSplit 
			|| ltype ==PolygonSplit || ltype==MirrorFeature)
		{
			//����һ���߻���

			m_pSketch =new Display::CGeometrySketch(GEOS_LINESTRING);


		}
	}

	void CEditor::DeleteAllTask()
	{
		if(m_allTasks.empty())
		{
			return;
		}
		for(size_t i =0;i<m_allTasks.size();i++)
		{
			delete m_allTasks[i];
		}

		m_allTasks.clear();
	}

	std::string CEditor::GetCurTaskName() const
	{
		if(m_curTask==NULL)
		{
			return std::string();
		}
		else
		{
			return m_curTask->GetName();
		}
	}



	/****************************************************************************************
	*���Ʊ༭ͼ�εĺ���
	*****************************************************************************************/
	void CEditor::DrawEditShape(Display::IDisplayPtr &pDisplay, GEOMETRY::geom::Geometry *pGeometry)
	{
		using namespace GEOMETRY::geom;

		int type =pGeometry->getGeometryTypeId();
		switch (type)
		{
		case GEOS_MULTIPOINT:
		case GEOS_POINT:
			return DrawEditPoints(pDisplay,pGeometry);
			break;

		case GEOS_LINESTRING:
			return DrawEditPolyline(pDisplay,pGeometry);
			break;

		case GEOS_MULTILINESTRING:

			return DrawEditMultiPolyline(pDisplay,pGeometry);
			break;

		case GEOS_POLYGON:
			return DrawEditPolygon(pDisplay,pGeometry);
			break;

		case GEOS_MULTIPOLYGON:

			break;

		default:
			return ;
			break;

		}

	}

	void CEditor::DrawEditPoints(Display::IDisplayPtr &pDisplay, GEOMETRY::geom::Geometry *pGeometry)
	{
		long lNumPoints =pGeometry->PointCount();
		if(lNumPoints<=0)
		{
			return;
		}

		Display::CDC *pDC =pDisplay->GetDrawDC();


		BRUSH_STYLE bs;
		bs.lColor = RGB(0,128,0);
		bs.Style = SOLID_BRUSH;
		DISPLAY_HANDLE pnewBrush =pDC->CreateBrush(bs);

		bs.lColor =RGB(255,0,0);
		//���һ����Ļ�ˢ
		DISPLAY_HANDLE EndPtBrush =pDC->CreateBrush(bs);

		int nSize =4;
		IntPoint pt;
		DIS_RECT rect;

		GEOMETRY::geom::Coordinate coord;

		DISPLAY_HANDLE pOld =pDC->SelectObject(pnewBrush);

		for( int i = 0;i < lNumPoints-1;i++ )
		{
			coord =pGeometry->GetPoint(i);

			//ת��Ϊ��Ļ����
			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);

			rect.left = pt.x - nSize;
			rect.right = pt.x + nSize;
			rect.top = pt.y - nSize;
			rect.bottom = pt.y + nSize;
			pDC->FillRect(rect);

		}


		//�������һ����
		pDC->SelectObject(EndPtBrush);

		coord =pGeometry->GetPoint(lNumPoints-1);

		pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);

		rect.left = pt.x - nSize;
		rect.right = pt.x + nSize;
		rect.top = pt.y - nSize;
		rect.bottom = pt.y + nSize;
		pDC->FillRect(rect);

		pDC->SelectObject(pOld);
		pDC->RemoveHandle(pnewBrush);
		pDC->RemoveHandle(EndPtBrush);


	}


	void CEditor::DrawEditPolyline(Display::IDisplayPtr &pDisplay, GEOMETRY::geom::Geometry *pGeometry)
	{
		long lNumPoints =pGeometry->PointCount();
		if(lNumPoints<=0)
		{
			return ;
		}
		GEOMETRY::geom::Coordinate coord;
		//���ֻ��һ���㣬�򻭵�
		if(lNumPoints==1)
		{
			INT_POINT pt;


			coord =pGeometry->GetPoint(0);

			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);
			DrawEditPoints(pDisplay,&pt,1);



		}
		else
		{

			INT_POINT*	pPoints = NULL;

			pPoints = new INT_POINT[lNumPoints];
			INT_POINT pt;

			//����һ����
			for( int j = 0;j < lNumPoints;j++ )
			{
				coord =pGeometry->GetPoint(j);

				pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);
				pPoints[j] = pt;	

			}


			DrawEditPolyline(pDisplay,pPoints,lNumPoints);

			delete []pPoints;
		}
	}

	void CEditor::DrawEditMultiPolyline(Display::IDisplayPtr &pDisplay, GEOMETRY::geom::Geometry *pGeometry)
	{
		using namespace GEOMETRY::geom;

		long lNumPoints =pGeometry->PointCount();
		if(lNumPoints<=0)
		{
			return;
		}

		GEOMETRY::geom::Coordinate coord;
		INT_POINT pt;

		//���ֻ��һ���㣬�򻭵�
		if(lNumPoints==1)
		{


			Geometry *pg =NULL;
			pg =const_cast<Geometry*>(((MultiLineString*)pGeometry)->getGeometryN(0));

			coord =pg->GetPoint(0);



			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);
			DrawEditPoints(pDisplay,&pt,1);


		}
		else
		{

			INT_POINT*	pPoints = NULL;

			//�м�����
			long    lpartnum =((MultiLineString*)pGeometry)->getNumGeometries();

			long    lptnum;

			Geometry *pg =NULL;
			for(long i=0;i<lpartnum;i++)
			{
				pg =const_cast<Geometry*>(((MultiLineString*)pGeometry)->getGeometryN(i));
				lptnum =pg->PointCount();

				pPoints = new INT_POINT[lptnum];

				for( long j = 0;j < lptnum;j++ )
				{
					coord =pg->GetPoint(j);

					pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);
					pPoints[j] = pt;		

				}


				DrawEditPolyline(pDisplay,pPoints,lptnum);

				delete []pPoints;
			}
		}
	}

	void CEditor::DrawEditPolygon(Display::IDisplayPtr &pDisplay, GEOMETRY::geom::Geometry *pGeometry)
	{
		using namespace GEOMETRY::geom;

		long lNumPoints =pGeometry->PointCount();
		if(lNumPoints<=0)
		{
			return;
		}

		GEOMETRY::geom::Coordinate coord;
		INT_POINT pt;

		IGeometryCollection *pGeoCollection =NULL;
		//���ֻ��һ���㣬�򻭵�
		if(lNumPoints==1)
		{

			pGeoCollection =dynamic_cast<IGeometryCollection*>(pGeometry);
			if(pGeoCollection==NULL)
			{
				return;
			}
			Geometry *pg =pGeoCollection->GetGeometry(0);

			coord=pg->GetPoint(0);	

			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);
			DrawEditPoints(pDisplay,&pt,1);



		}
		else
		{
			INT_POINT*	pPoints = NULL;

			pGeoCollection =dynamic_cast<IGeometryCollection*>(pGeometry);
			if(pGeoCollection==NULL)
			{
				return;
			}
			//�м�����
			long    lpartnum =pGeoCollection->GeometryCount();

			long    lptnum;

			Geometry *pg =NULL;
			for(long i=0;i<lpartnum;i++)
			{
				pg =pGeoCollection->GetGeometry(i);
				lptnum =pg->PointCount();

				pPoints = new INT_POINT[lptnum];

				for( long j = 0;j < lptnum;j++ )
				{
					coord =pg->GetPoint(j);

					pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);
					pPoints[j] = pt;	

				}


				if(lptnum==1)
				{
					DrawEditPoints(pDisplay,pPoints,1);
				}
				else
				{

					DrawEditPolyline(pDisplay,pPoints,lptnum);
				}
				delete []pPoints;
			}
		}
	}

	void CEditor::DrawEditPoints(Display::IDisplayPtr &pDisplay, INT_POINT *pts, long num)
	{
		Display::CDC *pDC =pDisplay->GetDrawDC();


		BRUSH_STYLE bs;
		bs.lColor = RGB(0,128,0);
		bs.Style = SOLID_BRUSH;
		DISPLAY_HANDLE pnewBrush =pDC->CreateBrush(bs);

		bs.lColor =RGB(255,0,0);
		//���һ����Ļ�ˢ
		DISPLAY_HANDLE EndPtBrush =pDC->CreateBrush(bs);

		int nSize =4;
		DIS_RECT rect;

		DISPLAY_HANDLE pOld =pDC->SelectObject(pnewBrush);

		for( int i = 0;i < num-1;i++ )
		{

			rect.left = pts[i].x - nSize;
			rect.right = pts[i].x + nSize;
			rect.top = pts[i].y - nSize;
			rect.bottom = pts[i].y + nSize;
			pDC->FillRect(rect);

		}


		//�������һ����
		pDC->SelectObject(EndPtBrush);

		rect.left = pts[num-1].x - nSize;
		rect.right = pts[num-1].x + nSize;
		rect.top = pts[num-1].y - nSize;
		rect.bottom = pts[num-1].y + nSize;
		pDC->FillRect(rect);

		pDC->SelectObject(pOld);
		pDC->RemoveHandle(pnewBrush);
		pDC->RemoveHandle(EndPtBrush);
	}

	void CEditor::DrawEditPolyline(Display::IDisplayPtr &pDisplay,INT_POINT *pts,long num)
	{
		Display::CDC *pDC =pDisplay->GetDrawDC();

		int i;
		DIS_LINE *pline;
		//����һ���߶��� 
		CreateDisplayLine(pline,num);
		for(i=0;i<num;i++)
		{
			pline->ps[i] =pts[i];
		}

		//�Ȼ���
		pDC->DrawPolyLines(*pline);

		FreeDisplayObj(pline);

		BRUSH_STYLE bs;
		bs.lColor = RGB(0,128,0);
		bs.Style = SOLID_BRUSH;
		DISPLAY_HANDLE pnewBrush =pDC->CreateBrush(bs);

		bs.lColor =RGB(255,0,0);
		//���һ����Ļ�ˢ
		DISPLAY_HANDLE EndPtBrush =pDC->CreateBrush(bs);

		int nSize =4;
		DIS_RECT rect;

		DISPLAY_HANDLE pOld =pDC->SelectObject(pnewBrush);



		for( int i = 0;i < num-1;i++ )
		{

			rect.left = pts[i].x - nSize;
			rect.right = pts[i].x + nSize;
			rect.top = pts[i].y - nSize;
			rect.bottom = pts[i].y + nSize;
			pDC->FillRect(rect);

		}


		//�������һ����
		pDC->SelectObject(EndPtBrush);

		rect.left = pts[num-1].x - nSize;
		rect.right = pts[num-1].x + nSize;
		rect.top = pts[num-1].y - nSize;
		rect.bottom = pts[num-1].y + nSize;
		pDC->FillRect(rect);

		pDC->SelectObject(pOld);
		pDC->RemoveHandle(pnewBrush);
		pDC->RemoveHandle(EndPtBrush);
	}

	void CEditor::DrawMousePoint(Display::IDisplayPtr &pDisplay)
	{
		using namespace GEOMETRY::geom;

		if(!m_pSketch)
		{
			return;
		}

		if(m_pSketch->IsEmpty())
		{
			return;
		}
		if(m_pSketch->IsCurPartFinish())
		{
			return;
		}
		Display::CDC *pDC =pDisplay->GetDrawDC();

		long ltype = m_pSketch->GetGeometryType();

		INT_POINT pt,curPt;

		pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(m_curSketchCoord.x,m_curSketchCoord.y,curPt.x,curPt.y);

		switch(ltype)
		{
		case GEOS_LINESTRING:
		case GEOS_MULTILINESTRING:
			{
				Coordinate coord =m_pSketch->GetlastPoint();


				//ת��Ϊ��Ļ����
				pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);



				pDC->MoveTo(pt);
				pDC->LineTo(curPt.x,curPt.y);

			}
			break;
		case GEOS_POLYGON:
			{
				//�õ���ǰ���ĵ�һ��������һ����
				Coordinate pt1 =m_pSketch->GetCurPartFirstPt();

				Coordinate pt2 =m_pSketch->GetlastPoint();


				INT_POINT fpt,ept;
				pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(pt1.x,pt1.y,fpt.x,fpt.y);
				pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(pt2.x,pt2.y,ept.x,ept.y);



				pDC->MoveTo(fpt);
				pDC->LineTo(curPt.x,curPt.y);

				pDC->MoveTo(ept);
				pDC->LineTo(curPt.x,curPt.y);

			}
			break;

		default:
			break;

		}
	}

	void CEditor::DrawSnapCursor(Display::IDisplayPtr &pDisplay)
	{
		Display::CDC *pDC =pDisplay->GetDrawDC();
		long x,y;

		//����ǰ��׽��ת��Ϊ��ͼ����
		pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(m_curSketchCoord.x,m_curSketchCoord.y,x,y);


		DIS_RECT rect;

		rect.left =x-7;
		rect.right =x+7;
		rect.top =y-7;
		rect.bottom = y+7;

		pDC->DrawEllipse(rect);
		pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
		pDC->LineTo(rect.right,rect.top+rect.Height()/2);
		pDC->MoveTo(rect.left+rect.Width()/2,rect.top);
		pDC->LineTo(rect.left+rect.Width()/2,rect.bottom);
	}

	/****************************************************************************************
	*������صĺ���
	*****************************************************************************************/

	void CEditor::AddToCircle(std::vector<Carto::ILayer*> &layers)
	{
		//����ع��б�
		STCircle circle;

		//���ع���֮��ļ�¼ɾ��
		while ((mg_undoIndex+1)<mg_undoCircles.size())
		{
			std::vector<STCircle>::iterator iter;
			iter = mg_undoCircles.begin() + (mg_undoIndex+1);
			mg_undoCircles.erase(iter);		
		}

		circle.layers =layers;

		mg_undoCircles.push_back(circle);
		mg_undoIndex++;



	}

	void CEditor::VertexUndo()
	{
		//�ж��������ڻ�ͼ�λ����ڱ༭ͼ��
		if(m_memUndoIndex<0)
			return;

		STMemUndoCycle *pCycle =m_memUndoStack[m_memUndoIndex];
		if(m_bSketch)
		{

			m_pSketch->ReplaceGeometry(pCycle->pGeometry,pCycle->lcurPart,pCycle->bcurPartFinish);
			m_memUndoIndex--;
		}
		else if(m_bEditFeature)
		{
			delete m_modifyGeometrys[0];
			Geometry *pg =pCycle->pGeometry->clone();
			m_modifyGeometrys[0] =pg;
			m_memUndoIndex--;
		}
	}

	void CEditor::VertexRedo()
	{
		if(m_memUndoIndex>=(long(m_memUndoStack.size())-1))
			return;

		m_memUndoIndex++;
		STMemUndoCycle *pCycle =m_memUndoStack[m_memUndoIndex];
		if(m_bSketch)
		{

			m_pSketch->ReplaceGeometry(pCycle->pGeometry,pCycle->lcurPart,pCycle->bcurPartFinish);

		}
		else if(m_bEditFeature)
		{
			delete m_modifyGeometrys[0];
			Geometry *pg =pCycle->pGeometry->clone();
			m_modifyGeometrys[0] =pg;
		}
	}

	bool CEditor::VertexCanUndo()
	{
		if(m_memUndoIndex<0)
		{
			return false;
		}
		return true;
	}

	bool CEditor::VertexCanRedo()
	{
		if(m_memUndoIndex>=(long(m_memUndoStack.size())-1))
		{
			return false;
		}
		return true;
	}

	void CEditor::PushGeometry2Undo(GEOMETRY::geom::Geometry *pGeometry, long lcurPart, bool bpartFinish )
	{
		while ((m_memUndoIndex+2)<m_memUndoStack.size())
		{
			std::vector<STMemUndoCycle*>::iterator iter;
			iter = m_memUndoStack.begin() +(m_memUndoIndex+2);

			delete (*iter);
			m_memUndoStack.erase(iter);
		}

		STMemUndoCycle *pCycle =new STMemUndoCycle();

		pCycle->pGeometry =pGeometry;
		pCycle ->lcurPart =lcurPart;
		pCycle->bcurPartFinish =bpartFinish;

		m_memUndoStack.push_back(pCycle);

		m_memUndoIndex++;
	}

	void CEditor::ClearMemUndo()
	{
		for(size_t i=0;i<m_memUndoStack.size();i++)
		{
			delete m_memUndoStack[i];
		}
		m_memUndoStack.clear();
		m_memUndoIndex =-1;
	}

	void CEditor::OnEndEdit()
	{
		m_bEditing = false;
		//ɾ����׽��
		RemoveAllSnapAgent();

		//ɾ�����ʶ���
		m_pSketch.reset();


		m_curLayer =NULL;
		//ɾ���ع��б�
		ClearMemUndo();

		mg_undoCircles.clear();
		mg_undoIndex = -1;


		ClearModifyGeometry();

		//��ձ༭ͼ���б�
		m_EditLayers.clear();

		ClearCopyFeatures();

		//m_bSetLength =m_bSetDirection =false;
	}

	void CEditor::ClearModifyGeometry()
	{

		if(!m_modifyGeometrys.empty())
		{
			for(size_t i=0; i<m_modifyGeometrys.size(); i++)
			{
				if(m_modifyGeometrys[i])
				{
					delete m_modifyGeometrys[i];
				}
			}

		}
		m_modifyGeometrys.clear();
		m_modifyLayers.clear();
		m_modifyShapeId.clear();
	}

	/***************************************************************************************
	* �˵���Ӧ����
	****************************************************************************************/

	void CEditor::OnSketchAbsXY()
	{
		//CDllResource hdll;

		//GEOMETRY::geom::Coordinate stNewPoint;
		//CPoint newPoint;
		//STKeyboardInputPoint stInputPoint;

		//CDlgKeyboardInput dlg(&stInputPoint);

		//dlg.mg_csTitle="������������(X,Y,Z,M)";
		//dlg.mg_dblX = m_curSketchCoord.x;
		//dlg.mg_dblY = m_curSketchCoord.y;

		//if(m_pSketch->GetGeometry()->HasZ())
		//{
		//	dlg.mg_bHasZ =TRUE;
		//	dlg.mg_dblZ = 0.0;
		//}
		//if(m_pSketch->GetGeometry()->HasM())
		//{
		//	dlg.mg_bHasM =TRUE;
		//	dlg.mg_dblM =0.0;
		//}



		//if(dlg.DoModal()==IDOK)
		//{
		//	stNewPoint.x = stInputPoint.dblX;
		//	stNewPoint.y = stInputPoint.dblY;

		//	//������ĵ���뵽������
		//	AddSketchPoint(stNewPoint,dlg.mg_dblZ,dlg.mg_dblM);

		//	//ˢ����ͼ
		//	Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		//	pActiveMapCtrl->UpdateControl(drawEdit);

		//}
	}

	void CEditor::OnSketchDeltaXY()
	{
		//if(!m_pSketch)
		//{
		//	return;
		//}

		//if(m_pSketch->IsEmpty())
		//{
		//	return;
		//}
		//if(m_pSketch->IsCurPartFinish())
		//{
		//	return;
		//}

		//GEOMETRY::geom::Coordinate lastPt =m_pSketch->GetlastPoint();

		//double dx = m_curSketchCoord.x - lastPt.x;
		//double dy = m_curSketchCoord.y - lastPt.y;


		//CDllResource dllRes;

		//CDlgInputSketchCoord dlg;

		//dlg.m_title ="�����������(X,Y)";
		//dlg.SetParam(dx,dy);
		//if(dlg.DoModal() ==IDOK)
		//{
		//	dx =dlg.m_direction;
		//	dy=dlg.m_length;

		//	GEOMETRY::geom::Coordinate stNewPoint;
		//	stNewPoint.x = lastPt.x + dx;
		//	stNewPoint.y = lastPt.y + dy;

		//	//������ĵ���뵽������
		//	AddSketchPoint(stNewPoint);

		//	//ˢ����ͼ
		//	Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		//	pActiveMapCtrl->UpdateControl(drawEdit);

		//}
	}

	void CEditor::OnSketchDirLen()
	{

	}



	/****************************************************************************************
	*������ǰ�༭ͼ��ĺ�����������ӡ��޸ĺ�ɾ��ͼ�ε�
	*****************************************************************************************/

	void CEditor::AppendGeometry(GEOMETRY::geom::Geometry *pGeometry)
	{
		if(m_curLayer ==NULL)
		{
			return;
		}
		if(!pGeometry)
		{
			return;
		}

		Geodatabase::IFeatureClassPtr pFeatureClass =m_curLayer->GetDataObject();

		if(!pFeatureClass)
			return;

		pFeatureClass->GetWorkspace()->StartEditOperation();
		Geodatabase::CFeaturePtr pnewFeature =pFeatureClass->CreateFeature();

		pnewFeature->SetShape(pGeometry->clone());

		//pnewFeature->Update();

		pFeatureClass->AddFeature(pnewFeature.get());

		pFeatureClass->GetWorkspace()->StopEditOperation();

		//����ع��б�
		std::vector<Carto::ILayer*> vecMapLayer;
		vecMapLayer.push_back(m_curLayer);

		AddToCircle(vecMapLayer);

		//��������༭״̬
		m_bInVertexEdit = false;

		m_bSketch =false;
		m_bEditFeature =false;
	}

	void CEditor::EditAttribute()
	{
		//if(!m_bEditing)
		//{
		//	return;
		//}

		//CDllResource dllRes;
		//std::vector<Carto::ILayer*> alllayers;


		//Carto::CLayerArray &layers =m_pGeoMap->GetLayers();
		//int num =layers.GetSize();
		//Carto::IFeatureLayerPtr pLayer;
		//Geodatabase::IFeatureClass *pFeatureClass =NULL;
		//Geodatabase::IWorkspace *pWorkspace =NULL;


		////�Ե�ͼ�е�ʸ�������ñ༭״̬
		//for(int i=0;i<num;i++)
		//{
		//	pLayer =layers.GetAt(i);
		//	if(!pLayer)
		//	{
		//		continue;
		//	}

		//	pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());
		//	if(!pFeatureClass)
		//	{
		//		continue;
		//	}

		//	pWorkspace =pFeatureClass->GetWorkspace();
		//	//Ŀǰֻ֧�ֶ��ļ����б༭
		//	/*if(pWorkspace->GetType()!=Geodatabase::WT_FileSystem)
		//	{
		//	continue;
		//	}*/
		//	if(!pLayer->GetSelection())
		//	{
		//		continue;
		//	}
		//	alllayers.push_back(pLayer.get());

		//}

		//CDlgFeatureAttriEdit dlg;
		//dlg.SetFeatures(alllayers);
		//dlg.DoModal();
	}

	void CEditor::GetEditLayers(std::vector<Carto::ILayer*> &layers)
	{
		layers =m_EditLayers;
	}

	bool CEditor::SearchEditGeometry()
	{


		ClearModifyGeometry();

		bool bSearch =false;
		GEOMETRY::geom::Geometry *pGeometry =NULL;

		Geodatabase::ISelctionSet *pSelction =NULL;
		long fid;

		Carto::CFeatureLayer* pFeatureLayer =NULL;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;
		for(int i=0;i<m_EditLayers.size();i++)
		{
			if(!m_EditLayers[i]->GetVisible())
			{
				continue;
			}

			pFeatureLayer =dynamic_cast<Carto::CFeatureLayer*>(m_EditLayers[i]);
			if(!pFeatureLayer)
			{
				continue;
			}
			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pFeatureLayer->GetDataObject().get());
			pSelction =pFeatureLayer->GetSelection().get();
			if(!pSelction)
			{
				continue;
			}
			pSelction->ResetIndex();
			while(!pSelction->IsEOF())
			{
				fid =pSelction->NextID();
				pGeometry =pFeatureClass->GetFeatureShape(fid);

				m_modifyGeometrys.push_back(pGeometry);

				m_modifyShapeId.push_back(fid);
				m_modifyLayers.push_back(m_EditLayers[i]);
				bSearch=true;

			}

		}


		m_bInVertexEdit = bSearch;
		if(bSearch)
		{
			m_bSketch =false;
			m_bEditFeature =true;
			//��ջع���ջ

			ClearMemUndo();

			//�ֽ�ԭ����ͼ�μ���ع�
			PushGeometry2Undo(m_modifyGeometrys[0]->clone());
			m_memUndoIndex--;
		}


		return bSearch;    
	}

	void CEditor::CommitModifyShape()
	{
		std::vector<Carto::ILayer*> vecMapLayerId;
		long fid;
		Geodatabase::CFeaturePtr pFeature;
		Geodatabase::IWorkspace *pWorkspace =NULL;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;

		for(int i=0; i<m_modifyGeometrys.size(); i++)
		{
			fid =m_modifyShapeId[i];

			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(m_modifyLayers[i]->GetDataObject().get());

			pWorkspace =pFeatureClass->GetWorkspace();
			pFeature = pFeatureClass->GetFeature(fid);

			if(!pFeature)
			{
				continue;
			}

			pWorkspace->StartEditOperation();
			pFeature->SetShape(m_modifyGeometrys[i]->clone());
			pFeature->Update();

			pWorkspace->StopEditOperation();

			vecMapLayerId.push_back(m_modifyLayers[i]);

		}
		if(!vecMapLayerId.empty())
		{
			//����ع��б�
			AddToCircle(vecMapLayerId);


		}
		//��������༭״̬
		m_bInVertexEdit = false;
		m_bSketch =false;
		m_bEditFeature =false;

		ClearMemUndo();

		//���
		ClearModifyGeometry();
	}

	//ɾ��ѡ�е�Ҫ��
	void CEditor::DeleteFeature()
	{

		std::vector<Carto::ILayer*> delLayers;
		bool bSearch =false;
		GEOMETRY::geom::Geometry *pGeometry =NULL;

		Geodatabase::ISelctionSet *pSelction =NULL;
		long fid;

		Geodatabase::IWorkspace *pWorkspace =NULL;
		Carto::CFeatureLayer* pFeatureLayer =NULL;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;
		for(int i=0;i<m_EditLayers.size();i++)
		{
			if(!m_EditLayers[i]->GetVisible())
			{
				continue;
			}

			pFeatureLayer =dynamic_cast<Carto::CFeatureLayer*>(m_EditLayers[i]);
			if(!pFeatureLayer)
			{
				continue;
			}
			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pFeatureLayer->GetDataObject().get());
			pWorkspace =pFeatureClass->GetWorkspace();
			pSelction =pFeatureLayer->GetSelection().get();
			if(!pSelction)
			{
				continue;
			}
			pSelction->ResetIndex();
			while(!pSelction->IsEOF())
			{
				fid =pSelction->NextID();
				pWorkspace->StartEditOperation();

				pFeatureClass->DeleteFeature(fid);
				pWorkspace->StopEditOperation();

				//����ع�
				delLayers.push_back(m_EditLayers[i]);

			}
			//��ѡ���ƿ�
			pFeatureLayer->ClearSelectionSet();

		}


		//��ձ༭ͼ��
		for(size_t i=0; i<m_modifyGeometrys.size(); i++)
		{
			if(m_modifyGeometrys[i])
			{
				delete m_modifyGeometrys[i];
			}
		}
		m_modifyGeometrys.clear();
		m_modifyLayers.clear();
		m_modifyShapeId.clear();


		//����ع�
		if(!delLayers.empty())
		{
			AddToCircle(delLayers);

			//��������༭״̬
			m_bInVertexEdit = false;
			m_bSketch =false;
			m_bEditFeature =false;

			ClearMemUndo();

			//ˢ����ͼ
			Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
			pActiveMapCtrl->UpdateControl(drawAll);

		}



	}

	//����ѡ�е�Ҫ��
	void CEditor::CopyFeature()
	{
		ClearCopyFeatures();


		GEOMETRY::geom::Geometry *pGeometry =NULL;

		Geodatabase::ISelctionSet *pSelction =NULL;
		long fid;

		Geodatabase::IWorkspace *pWorkspace =NULL;
		Carto::CFeatureLayer* pFeatureLayer =NULL;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;

		Geodatabase::CFeaturePtr pFeature;
		for(int i=0;i<m_EditLayers.size();i++)
		{
			if(!m_EditLayers[i]->GetVisible())
			{
				continue;
			}

			pFeatureLayer =dynamic_cast<Carto::CFeatureLayer*>(m_EditLayers[i]);
			if(!pFeatureLayer)
			{
				continue;
			}
			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pFeatureLayer->GetDataObject().get());
			pWorkspace =pFeatureClass->GetWorkspace();
			pSelction =pFeatureLayer->GetSelection().get();
			if(!pSelction)
			{
				continue;
			}
			pSelction->ResetIndex();
			while(!pSelction->IsEOF())
			{
				fid =pSelction->NextID();

				pFeature =pFeatureClass->GetFeature(fid);

				if(pFeature)
				{
					m_copyFeatures.push_back(pFeature->Clone());
				}


			}

		}

	}

	//ճ��Ҫ��
	void CEditor::PasteFeature()
	{
		if(m_copyFeatures.empty())
		{
			return;
		}

		if(m_curLayer==NULL)
		{
			return;
		}
		Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(m_curLayer->GetDataObject().get());

		if(!pFeatureClass)
		{
			return;
		}

		//�õ���ǰͼ���Ҫ������
		long lshapeType =pFeatureClass->ShapeType();

		long ltype;
		GEOMETRY::geom::Geometry *pGeometry =NULL;
		Geodatabase::IWorkspace *pWorkspace =pFeatureClass->GetWorkspace();

		pWorkspace->StartEditOperation();

		Geodatabase::CFeaturePtr pFeature;
		//��ÿ��Ҫ�ؿ��뵽��ǰͼ��
		for(size_t i=0;i<m_copyFeatures.size();i++)
		{
			pGeometry =m_copyFeatures[i]->GetShape();

			if(!pGeometry)
			{
				continue;
			}
			ltype =pGeometry->getGeometryTypeId();

			if(ltype!=lshapeType)
			{
				continue;
			}

			//������¼�һ��Ҫ�صĲ��裬���ȴ���һ����Ҫ��
			pFeature =pFeatureClass->CreateFeature();
			if(!pFeature)
				continue;

			//Ȼ������Ҫ������ͼ�Σ�������
			pFeature->SetShape(pGeometry->clone());

			// pFeature->Update();

			pFeatureClass->AddFeature(pFeature.get());


		}
		pWorkspace->StopEditOperation();


		std::vector<Carto::ILayer*> layers;
		layers.push_back(m_curLayer);
		AddToCircle(layers);

		//��������༭״̬
		m_bInVertexEdit = false;

		m_bSketch =false;
		m_bEditFeature =false;

		//ˢ����ͼ
		Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		pActiveMapCtrl->UpdateControl(drawAll);
	}

	// ����Ҫ��
	void CEditor::CutFeature()
	{
		//���ȸ���ѡ�е�Ҫ��
		CopyFeature();
		//Ȼ��ɾ��ѡ�е�Ҫ��
		DeleteFeature();
	}

	void CEditor::ClearCopyFeatures()
	{
		if(!m_copyFeatures.empty())
		{
			for(size_t i=0;i<m_copyFeatures.size();i++)
			{
				delete m_copyFeatures[i];
			}
			m_copyFeatures.clear();
		}
	}

	void CEditor::CommitModifyShapes(std::vector<GEOMETRY::geom::Geometry*> &vecShp, std::vector<long> &vecShapeId, std::vector<Carto::ILayer*> &vecLayers)
	{


		GEOMETRY::geom::Geometry *pGeometry =NULL;
		Geodatabase::IWorkspace *pWorkspace =NULL;
		Geodatabase::IFeatureClass *pFeatureClass;
		Geodatabase::CFeaturePtr pFeature;

		for(int i=0; i<vecShp.size(); i++)
		{


			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(vecLayers[i]->GetDataObject().get());
			pWorkspace =pFeatureClass->GetWorkspace();




			pFeature =pFeatureClass->GetFeature(vecShapeId[i]);
			if(!pFeature)
			{
				continue;
			}
			pGeometry =vecShp[i];
			pWorkspace->StartEditOperation();

			pFeature->SetShape(pGeometry);
			pFeature->Update();

			pWorkspace->StopEditOperation();


			//���ͼ��ѡ��
			vecLayers[i]->ClearSelectionSet();


		}


		if(!vecLayers.empty())
		{
			//����ع��б�
			AddToCircle(vecLayers);


		}
		//��������༭״̬
		m_bInVertexEdit = false;
		m_bSketch =false;
		m_bEditFeature =false;

		ClearMemUndo();

		//���
		for(int i=0; i<m_modifyGeometrys.size(); i++)
		{
			if(m_modifyGeometrys[i])
			{
				delete m_modifyGeometrys[i];
			}
		}
		m_modifyGeometrys.clear();
		m_modifyLayers.clear();
		m_modifyShapeId.clear();
	}

	void CEditor::GetCurLayerSelection(vector<Geometry*> &shapes, vector<long> &shapeIds, vector<Carto::ILayer*> &players)
	{

		if(!m_curLayer)
		{
			return;
		}

		//��ȡ���ͼ�ؼ�
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//��ȡ�����
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;


		//��ñ༭ͼ��
		Carto::CFeatureLayer *pFeatureLayer = dynamic_cast<Carto::CFeatureLayer*>(m_curLayer);
		if(!pFeatureLayer)
		{
			return;
		}

		//��ñ༭ͼ���ѡ��
		Geodatabase::ISelctionSet *pSelction = pFeatureLayer->GetSelection().get();
		if(!pSelction)
		{
			return;
		}

		Geodatabase::ITable *pTable = pSelction->GetTable();

		Geodatabase::IFeatureClass *pFeatureClass = dynamic_cast<Geodatabase::IFeatureClass*>(pTable);

		pSelction->ResetIndex();
		while(!pSelction->IsEOF())
		{		
			long fid =pSelction->NextID();
			Geodatabase::CFeaturePtr pFeature = pFeatureClass->GetFeature(fid);
			if (!pFeature)
			{
				continue;
			}

			shapes.push_back(pFeature->GetShapeClone());
			shapeIds.push_back(fid);
			players.push_back(m_curLayer);
		}
	}

} //namespace Editor