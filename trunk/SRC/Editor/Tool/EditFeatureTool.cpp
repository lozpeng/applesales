#include "stdafx.h"
#include "EditFeatureTool.h"
#include "IMapCtrl.h"
#include "CEditor.h"
#include "FeatureLayer.h"
#include "IWorkspace.h"
#include "resource.h"
//#include "EditorRes.h"
#include "Editor.h"
extern CEditorApp theApp;

namespace Editor
{

static CEditFeatureTool gEditFeatureTool;

CEditFeatureTool::CEditFeatureTool() : ITool("EditFeatureTool")
{
	

	//判断是否在点上或者线上的误差距离,单位是像素
	m_dTolerance =3;

	m_curPart =0;

	m_curVertexIndex =0;

	m_bMoved =false;

	m_bContain =false;

	m_nStatus = On_None;

	cursorOnVertix = NULL;
	cursorOnLine = NULL;
	cursorModifyShape = NULL;
	cursorSizeAll = NULL;
}

CEditFeatureTool::~CEditFeatureTool()
{
   ClearMoveGeometrys();
}

void CEditFeatureTool::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);

	//初始化光标
	if(cursorOnVertix == NULL)
		cursorOnVertix =::LoadCursor( theApp.m_hInstance , ATL_MAKEINTRESOURCE( IDC_ON_VERTIX));
	if(cursorSizeAll == NULL)
		cursorSizeAll =::LoadCursor( theApp.m_hInstance , ATL_MAKEINTRESOURCE( IDC_SIZE_ALL));
	if(cursorOnLine == NULL)
		cursorOnLine =::LoadCursor( theApp.m_hInstance , ATL_MAKEINTRESOURCE( IDC_VERTIX_MOVE));
	if(cursorModifyShape == NULL)
		cursorModifyShape =::LoadCursor( theApp.m_hInstance , ATL_MAKEINTRESOURCE( IDC_ModifyShape));

	//判断一下现在是否选择了图形，如果选择了图形，则进入移动多个图形的状态
	ClearMoveGeometrys();

	if(GetSelectGeometrys())
	{
		m_nStatus =On_SelectMoreShape;
	}
}

void CEditFeatureTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}

	if(m_nStatus==On_SelectMoreShape||m_nStatus == On_Selection)
	{
		//如果在选择图形的范围之外，结束移动状态
		if(!m_bContain)
		{
			m_nStatus = On_None;
	
			//将提交
			pEdit->CommitModifyShape();
			//清空选择集
			ClearMoveGeometrys();

			pMapCtrl->UpdateControl(drawAll);

			return;
		}
	}

	if(m_nStatus == On_None )
	{

		Framework::ITool *pTool = Framework::ITool::FindTool("SelectbyPoint");
		//用点选取要素
		pTool->LButtonDownEvent(nFlags, point);
		InstanceEditObject();		
	}

	else if(m_nStatus == On_Vertex)
	{
		//点击节点，则会选中该节点，然后可以移动
		m_nStatus = On_VertexMove;

	}
	else if(m_nStatus == On_VertexMove)
	{
		m_nStatus =On_Selection;
		//把图形压入回滚堆栈

		GEOMETRY::geom::Geometry *pGeometry= pEdit->m_modifyGeometrys[0]->clone();

		pEdit->PushGeometry2Undo(pGeometry);
	}
	else if(m_nStatus == On_Line||m_nStatus == On_Inside)
	{
		m_nStatus = On_ShapeMove;

		m_lastmovePt =point;
	}
	else if(m_nStatus==On_SelectMoreShape)
	{
		if(m_bContain)
		{
			m_nStatus =On_MoveMoreShape;
			m_lastmovePt =point;
		}
	}

}

void CEditFeatureTool::MouseMoveEvent (UINT nFlags, CPoint point)
{
	
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}

	if(m_nStatus == On_None)
	{
		pMapCtrl->SetCursor(cursorModifyShape);
		return;
	}



	//如果现在图形是空的，则进入选择状态
	if(pEdit->m_modifyGeometrys.empty() 
		&& m_nStatus!=On_SelectMoreShape
		&&  m_nStatus!=On_MoveMoreShape)
	{
		m_nStatus = On_None ;   
		return ;
	}

	//如果有选择图形的情况
	if(m_nStatus == On_Selection || m_nStatus == On_Vertex || m_nStatus == On_Line||m_nStatus == On_Inside)
	{
		if(pEdit->m_modifyGeometrys.empty())
		{
			return ;
		}
		double dblTol;
		long ltol =(double)m_dTolerance;

		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(ltol,dblTol);

		GEOMETRY::geom::Coordinate pt;
		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,pt.x,pt.y);

		GEOMETRY::geom::Coordinate coord;

		GEOMETRY::geom::Coordinate outpt;
		double  distance;
		long lpart,lverindex;
		//鼠标是否在节点上
		for(size_t i=0;i<pEdit->m_modifyGeometrys.size();i++)
		{
			coord.x = pt.x;
			coord.y = pt.y;
			if(pEdit->m_modifyGeometrys[i]->SnapVertex(&coord,dblTol,&outpt,&distance,&lpart,&lverindex))
			{
				
				m_nStatus =On_Vertex;
				pMapCtrl->SetCursor(cursorOnVertix);

				m_curPart =lpart;
				m_curVertexIndex =lverindex;

				m_curVertex =outpt;
				return;
			}

			//是否在线上
			if(pEdit->m_modifyGeometrys[i]->SnapEdgePoint(&coord,dblTol,&outpt,&distance,&lpart,&lverindex))
			{
				m_nStatus=On_Line;
				
				pMapCtrl->SetCursor(cursorOnLine);

				m_insertPt.x =outpt.x;
				m_insertPt.y =outpt.y;

				m_curPart =lpart;
				m_curVertexIndex =lverindex;
				return;
			}
			//如果是多边形，则判断是否在图形内
			long type =pEdit->m_modifyGeometrys[i]->getGeometryTypeId();

			if(type==GEOS_POLYGON || type==GEOS_MULTIPOLYGON)
			{
				Geometry *pPoint =(Geometry*)GeometryFactory::getDefaultInstance()->createPoint(Coordinate(pt.x,pt.y));

				m_bContain =false;

				if(pEdit->m_modifyGeometrys[i]->contains(pPoint))
				{
					m_bContain =true;

				}


				if(m_bContain)
				{
					m_nStatus=On_Inside;
					pMapCtrl->SetCursor(cursorSizeAll);
					delete pPoint;
					return;
				}

				delete pPoint;
			}

		}
		//如果鼠标不在节点上或者线上，则重新把状态设为On_Selection
		m_nStatus=On_Selection;
		
		pMapCtrl->SetCursor(cursorModifyShape);
	}
	else if(m_nStatus ==On_VertexMove )
	{
		pMapCtrl->SetCursor(cursorOnVertix);

		//移动当前节点
		GEOMETRY::geom::Coordinate pt;
		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,pt.x,pt.y);

		GEOMETRY::geom::Coordinate outPt;
		//捕捉
		pEdit->Snap(pt,outPt);


		GEOMETRY::geom::Geometry *pGeometry =pEdit->m_modifyGeometrys[0];

		long ltype =pGeometry->getGeometryTypeId();

		switch(ltype)
		{
		case GEOS_POINT:
		case GEOS_LINESTRING:

			pGeometry->ReplacePoint(m_curVertexIndex,outPt);
			break;

		case GEOS_MULTIPOINT:
		case GEOS_MULTILINESTRING:
			{
				//找到编辑的哪一部分的图形
				GEOMETRY::geom::Geometry *pMoveGeometry =const_cast<Geometry*>(((GeometryCollection*)pGeometry)->getGeometryN(m_curPart));
				if(pMoveGeometry!=NULL)
				{
					pMoveGeometry->ReplacePoint(m_curVertexIndex,outPt);
				}
				break;
			}
		case GEOS_POLYGON:
			{
				//找到编辑的哪一部分的图形
				GEOMETRY::geom::Geometry *pMoveGeometry =((GEOMETRY::geom::Polygon *)pGeometry)->GetGeometry(m_curPart);
				if(pMoveGeometry!=NULL)
				{
					pMoveGeometry->ReplacePoint(m_curVertexIndex,outPt);
				}
			}
			break;

		default:
			break;
		}


		pMapCtrl->UpdateControl(drawEdit);

	}
	//shape移动
	else if(m_nStatus == On_ShapeMove)
	{
		pMapCtrl->SetCursor(cursorSizeAll);

		if(m_lastmovePt!=point)
		{

			double dx ,dy;
			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x-m_lastmovePt.x,dx);

			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_lastmovePt.y-point.y,dy);
			
			GEOMETRY::geom::Geometry *pGeometry =pEdit->m_modifyGeometrys[0];

			pGeometry->Move(dx,dy);

			pMapCtrl->UpdateControl(drawEdit);
			m_lastmovePt =point;

			m_bMoved =true;
		}



	}
	//选中了多个图形
	else if(m_nStatus == On_SelectMoreShape)
	{
		
		GEOMETRY::geom::Coordinate pt;
		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,pt.x,pt.y);

		GEOMETRY::geom::Geometry *pPoint =(GEOMETRY::geom::Geometry*)
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(pt);

		m_bContain =false;
		for(size_t i=0;i<m_moveGeometrys.size();i++)
		{
			//点是否在要素之内
			if(m_moveGeometrys[i]->contains(pPoint))
			{
				m_bContain =true;
				break;
			}


		}

		if(m_bContain)
		{
			pMapCtrl->SetCursor(cursorSizeAll);
		}
		else
		{
			pMapCtrl->SetCursor(cursorModifyShape);
		}


	}
	//移动多个图形
	else if(m_nStatus == On_MoveMoreShape)
	{
		pMapCtrl->SetCursor(cursorSizeAll);

		if(m_lastmovePt!=point)
		{

			double dx=0 ,dy=0;
			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x-m_lastmovePt.x,dx);

			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_lastmovePt.y-point.y,dy);
			for(size_t i=0;i<m_moveGeometrys.size();i++)
			{
				//对每个图形进行移动
				m_moveGeometrys[i]->Move(dx,dy);
			}

			DrawMovedGeometrys();

			m_lastmovePt =point;

			m_bMoved =true;
		}

	}

}

void CEditFeatureTool::LButtonUpEvent (UINT nFlags, CPoint point)
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}

	if(m_nStatus == On_None)
		return;

	//如果现在是鼠标拖动Shape,则抬起鼠标左键，会释放这种状态
	if(m_nStatus == On_ShapeMove)
	{
		//
		m_nStatus =On_Selection;
		
		pMapCtrl->SetCursor(cursorModifyShape);

		if(m_bMoved)
		{
			//如果要素移动了，则保存进回滚堆栈

			GEOMETRY::geom::Geometry *pGeometry =pEdit->m_modifyGeometrys[0]->clone();

			pEdit->PushGeometry2Undo(pGeometry);
		}

		m_bMoved =false;

		//将提交
		pEdit->CommitModifyShape();
		m_nStatus = On_None;
		//清空选择集
		ClearMoveGeometrys();

	}
	else if(m_nStatus == On_MoveMoreShape)
	{
		m_nStatus =On_SelectMoreShape;

		if(m_bMoved)
		{
			//如果要素移动了，则提交修改结果

			std::vector<Carto::ILayer*> vecMapLayers;
			long fid;
			Geodatabase::CFeaturePtr pFeature;
			Geodatabase::IFeatureClass *pFeatureClass =NULL;
			Geodatabase::IWorkspace *pWorkspace =NULL;

			for(int i=0; i<m_moveGeometrys.size(); i++)
			{
				fid =m_shpIds[i];
				pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(m_layers[i]->GetDataObject().get());

				pWorkspace =pFeatureClass->GetWorkspace();
				pFeature = pFeatureClass->GetFeature(fid);

				if(!pFeature)
				{
					continue;
				}

				pWorkspace->StartEditOperation();
				pFeature->SetShape(m_moveGeometrys[i]->clone());
				pFeature->Update();

				pWorkspace->StopEditOperation();


				vecMapLayers.push_back(m_layers[i]);

			}
			if(!vecMapLayers.empty())
			{
				//加入回滚列表
				pEdit->AddToCircle(vecMapLayers);


			}
			

		}

		m_bMoved =false;

		//将提交
		pEdit->CommitModifyShape();
		m_nStatus = On_None;
		//清空选择集
		ClearMoveGeometrys();
	}

	pMapCtrl->UpdateControl(drawAll);
}

void CEditFeatureTool::LButtonDblClkEvent(UINT nFlags, CPoint point)
{
	if(m_nStatus == On_None)
		return;

	if(m_nStatus==On_SelectMoreShape)
	{
		//如果在选择图形的范围之外，双击会结束移动状态
		if(!m_bContain)
		{
			m_nStatus = On_None;

			//清空选择集
			ClearMoveGeometrys();


		}
		return;
	}

	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}


	//将提交放到下面

	pEdit->CommitModifyShape();
	m_nStatus = On_None;

	pMapCtrl->UpdateControl(drawAll);
}

void CEditFeatureTool::ClearMoveGeometrys()
{
	for(size_t i=0;i<m_moveGeometrys.size();i++)
	{
		delete m_moveGeometrys[i];
	}

	m_moveGeometrys.clear();
	m_shpIds.clear();
	m_layers.clear();
}

BOOL CEditFeatureTool::GetSelectGeometrys()
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return FALSE;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return FALSE;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return FALSE;
	}

	
	BOOL				bSelected,bSearch = FALSE;
	
	std::vector<Carto::ILayer*> alllayers;
	pEdit->GetEditLayers(alllayers);


	GEOMETRY::geom::Geometry *pGeometry =NULL;

	Geodatabase::ISelctionSet *pSelction =NULL;
	long fid;
    
	Carto::CFeatureLayer* pFeatureLayer =NULL;
	Geodatabase::IFeatureClass *pFeatureClass =NULL;
	//将各个图层中选择集中的图形加入到m_moveGeometrys中
    for(size_t i=0;i<alllayers.size();i++)
	{
		//如果图层不可见，则不进行编辑
		if(!alllayers[i]->GetVisible())
		{
			continue;
		}
		pFeatureLayer =dynamic_cast<Carto::CFeatureLayer*>(alllayers[i]);
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

			m_moveGeometrys.push_back(pGeometry);

			m_shpIds.push_back(fid);
			m_layers.push_back(alllayers[i]);
			bSearch=TRUE;

		}

	}


	return bSearch;  
}

BOOL CEditFeatureTool::InstanceEditObject()
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return FALSE;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return FALSE;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return FALSE;
	}

	//将选择集中的图形加入到修改图形数组
	if(!pEdit->SearchEditGeometry())
	{
		pMapCtrl->UpdateControl(drawEdit);
		return FALSE;
	}
	if(pEdit->m_modifyGeometrys.size()>1)
		m_nStatus = On_SelectMoreShape;
		else m_nStatus = On_Selection;
	GetSelectGeometrys();
	pMapCtrl->UpdateControl(drawEdit);


	return TRUE;
}

void CEditFeatureTool::DrawMovedGeometrys()
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}

	//更新显示
	Display::IDisplayPtr dispaly = pMap->GetDisplay();
	dispaly->SetDrawBuffer(drawGeoSelection);
	dispaly->DrawBackgroud();

	for(size_t i=0;i<m_moveGeometrys.size();i++)
	{
		pEdit->DrawEditShape(dispaly,m_moveGeometrys[i]);
	}
	pMapCtrl->RefreshScreen();
}

void CEditFeatureTool::RButtonDownEvent(UINT nFlags, CPoint point)
{
	//右键菜单
	if(m_nStatus ==On_None)
	{
		return;
	}

	if(m_nStatus == On_SelectMoreShape || m_nStatus == On_MoveMoreShape)
	{
		return;
	}

	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}

	//CDllResource dllRes;
	//CMenu Menu;


	//if (Menu.LoadMenu(IDR_MENU_MODIFY_TOOL))
	//{
	//	CMenu* pPopup = NULL;
	//	pPopup = Menu.GetSubMenu(0);
	//	if (pPopup!=NULL)
	//	{
	//		CPoint srnPoint = point;
	//		CWnd *pWnd =dynamic_cast<CWnd*>(pMapCtrl);
	//		pWnd->ClientToScreen(&srnPoint);

	//		//如果点的数目小于等于1，则不能删除节点
	//		GEOMETRY::geom::Geometry *pGeometry= pEdit->m_modifyGeometrys[0];
	//		if(pGeometry->PointCount()<=1)
	//		{
	//			pPopup->EnableMenuItem( ID_MT_DEL_VERTEX,MF_GRAYED);
	//		}

	//		//如果鼠标在节点上
	//		if(m_nStatus ==On_Vertex || m_nStatus==On_VertexMove )
	//		{
	//			//使插入节点按钮无效
	//			pPopup->EnableMenuItem( ID_MT_INSERT_VERTEX,MF_GRAYED);

	//		}
	//		else if(m_nStatus==On_Line)
	//		{
	//			//使删除、移动节点按钮无效
	//			pPopup->EnableMenuItem( ID_MT_DEL_VERTEX,MF_GRAYED);
	//			pPopup->EnableMenuItem( ID_MT_MOVE_VERTEX,MF_GRAYED);

	//		}
	//		else if(m_nStatus==On_Selection)
	//		{
	//			//使插入节点按钮无效
	//			pPopup->EnableMenuItem( ID_MT_INSERT_VERTEX,MF_GRAYED);
	//			//使删除、移动节点按钮无效
	//			pPopup->EnableMenuItem( ID_MT_DEL_VERTEX,MF_GRAYED);
	//			pPopup->EnableMenuItem( ID_MT_MOVE_VERTEX,MF_GRAYED);

	//		}
	//		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,srnPoint.x,srnPoint.y,pWnd);
	//	}
	//}
}

//插入节点
void CEditFeatureTool::InsertVertex()
{

	using namespace GEOMETRY::geom;

	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}

	if(pEdit->m_modifyGeometrys.empty())
	{
		return;
	}
	Geometry *pGeometry = pEdit->m_modifyGeometrys[0];

	long ltype =pGeometry->getGeometryTypeId();

	Coordinate newpt;
	newpt.x = m_insertPt.x;
	newpt.y = m_insertPt.y;

	bool bdone =false;
	switch(ltype)
	{
	case GEOS_LINESTRING:

		pGeometry->InsertPoint(m_curVertexIndex,newpt);

		bdone =true;
		break;

	case GEOS_MULTILINESTRING:
		{
			//找到编辑的哪一部分的图形
			Geometry *pMoveGeometry =const_cast<Geometry*>(((GeometryCollection*)pGeometry)->getGeometryN(m_curPart));
			if(pMoveGeometry!=NULL)
			{
				pMoveGeometry->InsertPoint(m_curVertexIndex,newpt);
			}
			bdone =true;
			break;
		}
	case GEOS_POLYGON:
		{
			//找到编辑的哪一部分的图形
			Geometry *pMoveGeometry =((GEOMETRY::geom::Polygon *)pGeometry)->GetGeometry(m_curPart);
			if(pMoveGeometry!=NULL)
			{
				pMoveGeometry->InsertPoint(m_curVertexIndex,newpt);
			}
			bdone =true;
		}
		break;

	default:
		break;
	}

	if(bdone)
	{
		//把图形压入回滚堆栈
		Geometry *pCurGeometry =pGeometry->clone();

		pEdit->PushGeometry2Undo(pCurGeometry);
	}


	pMapCtrl->UpdateControl(drawEdit);
}

void CEditFeatureTool::DelVertex()
{
	using namespace GEOMETRY::geom;

	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}

	if(pEdit->m_modifyGeometrys.empty())
	{
		return;
	}
	Geometry *pGeometry =pEdit->m_modifyGeometrys[0];

	long ltype =pGeometry->getGeometryTypeId();

	Coordinate newpt;
	newpt.x = m_insertPt.x;
	newpt.y = m_insertPt.y;

	bool bdone =false;
	switch(ltype)
	{

	case GEOS_POINT:
	case GEOS_LINESTRING:

		pGeometry->RemovePoint(m_curVertexIndex);
		bdone =true;
		break;

	case GEOS_MULTIPOINT:
	case GEOS_MULTILINESTRING:
		{
			//找到编辑的哪一部分的图形
			Geometry *pMoveGeometry =const_cast<Geometry*>(((GeometryCollection*)pGeometry)->getGeometryN(m_curPart));
			if(pMoveGeometry!=NULL)
			{
				pMoveGeometry->RemovePoint(m_curVertexIndex);
			}
			bdone =true;
			break;
		}
	case GEOS_POLYGON:
		{
			//找到编辑的哪一部分的图形
			Geometry *pMoveGeometry =((GEOMETRY::geom::Polygon *)pGeometry)->GetGeometry(m_curPart);
			if(pMoveGeometry!=NULL)
			{
				pMoveGeometry->RemovePoint(m_curVertexIndex);
			}
		}
		bdone =true;
		break;

	default:
		break;
	}

	if(bdone)
	{
		//把图形压入回滚堆栈
		Geometry *pCurGeometry =pGeometry->clone();

		pEdit->PushGeometry2Undo(pCurGeometry);
	}

	if(m_nStatus==On_VertexMove )
	{
		m_nStatus =On_Selection;
	}

	pMapCtrl->UpdateControl(drawEdit);
}

//通过输入坐标移动节点
void CEditFeatureTool::MoveVertex()
{
	//CExtDllResource dllRes;

	//Ctv2DMap *ptvMap = mg_pteDoc->GetCurrentMap();
	//if(ptvMap == NULL)
	//	return;

	//if(ptvMap->mg_ptvEditSpace->m_modifyGeometrys.empty())
	//{
	//	return;
	//}
	//Geometry *pGeometry =ptvMap->mg_ptvEditSpace->m_modifyGeometrys[0];

	//long ltype =pGeometry->getGeometryTypeId();


	//STPoint stNewPoint;
	//CPoint newPoint;
	//STKeyboardInputPoint stInputPoint;

	//CDlgKeyboardInput dlg(&stInputPoint);

	//dlg.mg_csTitle="坐标输入(X,Y,Z,M)";
	//dlg.mg_dblX = m_curVertex.x;
	//dlg.mg_dblY = m_curVertex.y;

	//if(pGeometry->HasZ())
	//{
	//	dlg.mg_bHasZ =TRUE;
	//	dlg.mg_dblZ =m_curVertex.z;
	//}
	//if(pGeometry->HasM())
	//{
	//	dlg.mg_bHasM =TRUE;
	//	dlg.mg_dblM = m_curVertex.m;
	//}



	//if(dlg.DoModal()==IDOK)
	//{
	//	stNewPoint.x = stInputPoint.dblX;
	//	stNewPoint.y = stInputPoint.dblY;

	//	Coordinate newcoord(stNewPoint.x,stNewPoint.y,stInputPoint.dblZ,stInputPoint.dblM);
	//	switch(ltype)
	//	{
	//	case GEOS_POINT:
	//	case GEOS_LINESTRING:

	//		pGeometry->ReplacePoint(m_curVertexIndex,newcoord);
	//		break;

	//	case GEOS_MULTIPOINT:
	//	case GEOS_MULTILINESTRING:
	//		{
	//			//找到编辑的哪一部分的图形
	//			Geometry *pMoveGeometry =const_cast<Geometry*>(((GeometryCollection*)pGeometry)->getGeometryN(m_curPart));
	//			if(pMoveGeometry!=NULL)
	//			{
	//				pMoveGeometry->ReplacePoint(m_curVertexIndex,newcoord);
	//			}
	//			break;
	//		}
	//	case GEOS_POLYGON:
	//		{
	//			//找到编辑的哪一部分的图形
	//			Geometry *pMoveGeometry =((GEOMETRY::geom::Polygon *)pGeometry)->GetGeometry(m_curPart);
	//			if(pMoveGeometry!=NULL)
	//			{
	//				pMoveGeometry->ReplacePoint(m_curVertexIndex,newcoord);
	//			}
	//		}
	//		break;

	//	default:
	//		break;
	//	}
	//	ptvMap->mg_ptvEditSpace->UpdateView();

	//	//把图形压入回滚堆栈

	//	Geometry *pushGeometry =pGeometry->clone();

	//	ptvMap->mg_ptvEditSpace->PushGeometry2Undo(pushGeometry);
	//}
}

void CEditFeatureTool::ShowAttribute()
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}


	pEdit->EditAttribute();
}

} //namespace Editor