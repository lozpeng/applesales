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

		//捕捉距离为10个像素
		m_screenTolerance =10;

		//初始化所有的任务
		InitEditTask();
	}

	CEditor::~CEditor()
	{
		if(m_bEditing)
		{
			StopEdit(false);
		}

		//删除编辑任务
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
		//对地图中的矢量层设置编辑状态
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
			//目前只支持对文件进行编辑
			/*if(pWorkspace->GetType()!=Geodatabase::WT_FileSystem)
			{
			continue;
			}*/
			//工作空间开始编辑状态
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
			if(names[i] =="创建新要素")
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


		//结束编辑
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

			//目前只支持对文件进行编辑
			/*if(pWorkspace->GetType()!=Geodatabase::WT_FileSystem)
			{
			continue;
			}*/
			//工作空间结束编辑状态
			pWorkspace->StopEdit(bSave);


		}
		m_bEditing =false;

		OnEndEdit();

		//刷新视图
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

		//保存编辑
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

			//工作空间结束编辑状态
			pWorkspace->Commit();


		}

		//删除回滚列表
		ClearMemUndo();

		mg_undoCircles.clear();
		mg_undoIndex = -1;


		ClearModifyGeometry();

		//刷新视图
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
				//调用工作空间的undo
				pFeatureClass->GetWorkspace()->UndoEdit();


			}

			mg_undoIndex--;
		}


		//刷新视图
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

		//刷新视图
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

		//绘制正在编辑的图形
		if(!m_modifyGeometrys.empty())
		{
			for(int i=0; i<m_modifyGeometrys.size(); i++)
				DrawEditShape(pDisplay, m_modifyGeometrys[i]);
		}
		//绘制画笔中的图形
		if(m_pSketch)
		{
			if(!m_pSketch->IsEmpty())
			{
				DrawEditShape(pDisplay,m_pSketch->GetGeometry());
				
				//绘制鼠标移动的下一个点
				DrawMousePoint(pDisplay);     
			}
		}

		if(m_bSketch)
		 DrawSnapCursor(pDisplay);


		pDisplay->End();
	}

	/****************************************************************************************
	*画笔操作的函数
	*****************************************************************************************/

	//创造一个和要编辑图层相符的画笔
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


		//如果是第一个点，则将原来空的Geometry加入回滚
		if(m_pSketch->IsEmpty() && m_memUndoStack.empty())
		{
			GEOMETRY::geom::Geometry *pg =m_pSketch->GetGeometry()->clone();

			this->PushGeometry2Undo(pg,m_pSketch->m_icurPart,m_pSketch->m_bCurPartFinish);

			m_memUndoIndex--;
		}

		m_pSketch->AddPoint(point);

		//将画笔当前图形加入回滚
		Geometry *pg =m_pSketch->GetGeometry()->clone();

		PushGeometry2Undo(pg,m_pSketch->m_icurPart,m_pSketch->m_bCurPartFinish);

		//m_bSetLength =m_bSetDirection =false;


	}

	//结束绘制当前图形，并把绘制的图形交给编辑任务处理
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

		//将回滚堆栈制空
		m_bSketch =false;
		m_bInVertexEdit =false;
		ClearMemUndo();

		m_pSketch->SetEmpty();

		//刷新视图
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
	*以下为节点捕捉相关的函数
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
		//在捕捉列表中查找该图层，如果没有，则返回没有捕捉
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
	*以下为设置和获取当前编辑图层的函数
	*****************************************************************************************/

	void CEditor::ChangeCurLayer(std::string layername)
	{
		std::string name;
		int index;

		if(m_curLayer)
		{

			//如果和当前层相同，返回
			if(layername ==m_curLayer->GetName())
			{
				return;
			}
		}

		bool bfind =false;

		Carto::ILayer* pLayer = NULL;

		Carto::CLayerArray &layers =m_pGeoMap->GetLayers();
		int num =layers.GetSize();

		//对地图中的矢量层设置编辑状态
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
			//设为当前编辑层
			m_curLayer =pLayer;
			//通知目标层已经发生改变
			OnTagetLayerChanged();
		}
	}

	void CEditor::OnTagetLayerChanged()
	{
		//如果当前任务是创建新要素
		if(m_curTask->GetType()==CreateNewFeatrue )
		{
			//创建一个和当前层相符的画笔
			CreateEditSketch(m_curLayer);
		}
	}

	/****************************************************************************************
	*以下为设置和获取编辑任务的函数
	*****************************************************************************************/


	void CEditor::InitEditTask()
	{
		//创建要素对象
		IEditTask *pTask =new CCreateFeatureTask(this);
		m_allTasks.push_back(pTask);
		m_curTask =pTask;

		//线的延长、裁剪
		//pTask =new CExtendTrimTask(this);
		//m_allTasks.push_back(pTask);

		////线打断
		//pTask =new CLineSplitTask(this);
		//m_allTasks.push_back(pTask);

		////多边形打断
		//pTask =new CPolygonSplitTask(this);
		//m_allTasks.push_back(pTask);

		////镜像
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

		//通知当前编辑任务发生改变
		OnEditTaskChanged();
	}

	void CEditor::OnEditTaskChanged()
	{
		long ltype =m_curTask->GetType();
		if(ltype==CreateNewFeatrue)
		{
			//创建一个和当前层相符的画笔
			CreateEditSketch(m_curLayer);
		}
		else if(ltype ==ExtendTrimLine || ltype ==LineSplit 
			|| ltype ==PolygonSplit || ltype==MirrorFeature)
		{
			//创建一个线画笔

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
	*绘制编辑图形的函数
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
		//最后一个点的画刷
		DISPLAY_HANDLE EndPtBrush =pDC->CreateBrush(bs);

		int nSize =4;
		IntPoint pt;
		DIS_RECT rect;

		GEOMETRY::geom::Coordinate coord;

		DISPLAY_HANDLE pOld =pDC->SelectObject(pnewBrush);

		for( int i = 0;i < lNumPoints-1;i++ )
		{
			coord =pGeometry->GetPoint(i);

			//转换为屏幕坐标
			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);

			rect.left = pt.x - nSize;
			rect.right = pt.x + nSize;
			rect.top = pt.y - nSize;
			rect.bottom = pt.y + nSize;
			pDC->FillRect(rect);

		}


		//绘制最后一个点
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
		//如果只有一个点，则画点
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

			//构造一个线
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

		//如果只有一个点，则画点
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

			//有几条线
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
		//如果只有一个点，则画点
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
			//有几个环
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
		//最后一个点的画刷
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


		//绘制最后一个点
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
		//构造一个线对象 
		CreateDisplayLine(pline,num);
		for(i=0;i<num;i++)
		{
			pline->ps[i] =pts[i];
		}

		//先画线
		pDC->DrawPolyLines(*pline);

		FreeDisplayObj(pline);

		BRUSH_STYLE bs;
		bs.lColor = RGB(0,128,0);
		bs.Style = SOLID_BRUSH;
		DISPLAY_HANDLE pnewBrush =pDC->CreateBrush(bs);

		bs.lColor =RGB(255,0,0);
		//最后一个点的画刷
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


		//绘制最后一个点
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


				//转换为屏幕坐标
				pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);



				pDC->MoveTo(pt);
				pDC->LineTo(curPt.x,curPt.y);

			}
			break;
		case GEOS_POLYGON:
			{
				//得到当前环的第一个点和最后一个点
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

		//将当前捕捉点转换为视图坐标
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
	*回退相关的函数
	*****************************************************************************************/

	void CEditor::AddToCircle(std::vector<Carto::ILayer*> &layers)
	{
		//加入回滚列表
		STCircle circle;

		//将回滚点之后的记录删除
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
		//判断现在是在画图形还是在编辑图形
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
		//删除捕捉器
		RemoveAllSnapAgent();

		//删除画笔对象
		m_pSketch.reset();


		m_curLayer =NULL;
		//删除回滚列表
		ClearMemUndo();

		mg_undoCircles.clear();
		mg_undoIndex = -1;


		ClearModifyGeometry();

		//清空编辑图层列表
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
	* 菜单响应函数
	****************************************************************************************/

	void CEditor::OnSketchAbsXY()
	{
		//CDllResource hdll;

		//GEOMETRY::geom::Coordinate stNewPoint;
		//CPoint newPoint;
		//STKeyboardInputPoint stInputPoint;

		//CDlgKeyboardInput dlg(&stInputPoint);

		//dlg.mg_csTitle="绝对坐标输入(X,Y,Z,M)";
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

		//	//将输入的点加入到画笔中
		//	AddSketchPoint(stNewPoint,dlg.mg_dblZ,dlg.mg_dblM);

		//	//刷新视图
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

		//dlg.m_title ="输入相对坐标(X,Y)";
		//dlg.SetParam(dx,dy);
		//if(dlg.DoModal() ==IDOK)
		//{
		//	dx =dlg.m_direction;
		//	dy=dlg.m_length;

		//	GEOMETRY::geom::Coordinate stNewPoint;
		//	stNewPoint.x = lastPt.x + dx;
		//	stNewPoint.y = lastPt.y + dy;

		//	//将输入的点加入到画笔中
		//	AddSketchPoint(stNewPoint);

		//	//刷新视图
		//	Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		//	pActiveMapCtrl->UpdateControl(drawEdit);

		//}
	}

	void CEditor::OnSketchDirLen()
	{

	}



	/****************************************************************************************
	*操作当前编辑图层的函数，包括添加、修改和删除图形等
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

		//加入回滚列表
		std::vector<Carto::ILayer*> vecMapLayer;
		vecMapLayer.push_back(m_curLayer);

		AddToCircle(vecMapLayer);

		//结束顶点编辑状态
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


		////对地图中的矢量层设置编辑状态
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
		//	//目前只支持对文件进行编辑
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
			//清空回滚堆栈

			ClearMemUndo();

			//现将原来的图形加入回滚
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
			//加入回滚列表
			AddToCircle(vecMapLayerId);


		}
		//结束顶点编辑状态
		m_bInVertexEdit = false;
		m_bSketch =false;
		m_bEditFeature =false;

		ClearMemUndo();

		//清空
		ClearModifyGeometry();
	}

	//删除选中的要素
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

				//加入回滚
				delLayers.push_back(m_EditLayers[i]);

			}
			//将选择集制空
			pFeatureLayer->ClearSelectionSet();

		}


		//清空编辑图形
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


		//加入回滚
		if(!delLayers.empty())
		{
			AddToCircle(delLayers);

			//结束顶点编辑状态
			m_bInVertexEdit = false;
			m_bSketch =false;
			m_bEditFeature =false;

			ClearMemUndo();

			//刷新视图
			Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
			pActiveMapCtrl->UpdateControl(drawAll);

		}



	}

	//复制选中的要素
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

	//粘贴要素
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

		//得到当前图层的要素类型
		long lshapeType =pFeatureClass->ShapeType();

		long ltype;
		GEOMETRY::geom::Geometry *pGeometry =NULL;
		Geodatabase::IWorkspace *pWorkspace =pFeatureClass->GetWorkspace();

		pWorkspace->StartEditOperation();

		Geodatabase::CFeaturePtr pFeature;
		//将每个要素拷入到当前图层
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

			//这就是新加一个要素的步骤，首先创建一个空要素
			pFeature =pFeatureClass->CreateFeature();
			if(!pFeature)
				continue;

			//然后对这个要素设置图形，和属性
			pFeature->SetShape(pGeometry->clone());

			// pFeature->Update();

			pFeatureClass->AddFeature(pFeature.get());


		}
		pWorkspace->StopEditOperation();


		std::vector<Carto::ILayer*> layers;
		layers.push_back(m_curLayer);
		AddToCircle(layers);

		//结束顶点编辑状态
		m_bInVertexEdit = false;

		m_bSketch =false;
		m_bEditFeature =false;

		//刷新视图
		Framework::IMapCtrl *pActiveMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		pActiveMapCtrl->UpdateControl(drawAll);
	}

	// 剪切要素
	void CEditor::CutFeature()
	{
		//首先复制选中的要素
		CopyFeature();
		//然后删除选中的要素
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


			//清空图层选择集
			vecLayers[i]->ClearSelectionSet();


		}


		if(!vecLayers.empty())
		{
			//加入回滚列表
			AddToCircle(vecLayers);


		}
		//结束顶点编辑状态
		m_bInVertexEdit = false;
		m_bSketch =false;
		m_bEditFeature =false;

		ClearMemUndo();

		//清空
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

		//获取活动地图控件
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;


		//获得编辑图层
		Carto::CFeatureLayer *pFeatureLayer = dynamic_cast<Carto::CFeatureLayer*>(m_curLayer);
		if(!pFeatureLayer)
		{
			return;
		}

		//获得编辑图层的选择集
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