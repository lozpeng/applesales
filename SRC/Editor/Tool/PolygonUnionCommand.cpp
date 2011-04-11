#include "stdafx.h"
#include "PolygonUnionCommand.h"
#include "IWorkspace.h"
#include "SimpleQuery.h"
#include "CEditor.h"
#include <Geometry/geom/Geometry.h>
#include "IMapCtrl.h"
#include "IGeoDataObject.h"
#include "EditFeatureTool.h"
#include "FeatureLayer.h"
namespace Editor
{

	static CPolygonUnionTool gPolygonUnionCommand;

	CPolygonUnionTool::CPolygonUnionTool(void) : ICommand("PolygonUnionCmd")
	{
		
	}

	CPolygonUnionTool::~CPolygonUnionTool(void)
	{

	}
		//初始化
	void CPolygonUnionTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);
	}
	void CPolygonUnionTool::Click()
	{
		//获取活动地图控件
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;

		//获得编辑类
		Editor::CEditorPtr pEdit =pMap->GetEditor();
		if(!pEdit)
		{
			return;
		}

		//获得当前编辑层
		Carto::ILayer *pLayer = pEdit->GetCurLayer();
		if (!pLayer)
		{
			return;
		}

		//判断编辑数据类型是否是矢量数据
		if(pLayer->GetLayerType() != Carto::FeatureLayer)
		{
			return;
		}

		//获得当前编辑层图形的类型，判断是否是多边形要素
		Geodatabase::IGeodataObjectPtr  pDataObject = pLayer->GetDataObject();
		if (!pDataObject)
		{
			return;
		}

		Geodatabase::IFeatureClass *pFeatureClass = dynamic_cast<Geodatabase::IFeatureClass*>(pDataObject.get());
		long lshpType = pFeatureClass->ShapeType(); 
		if(lshpType != GEOMETRY::geom::GEOS_POLYGON && lshpType != GEOMETRY::geom::GEOS_MULTIPOLYGON)
		{
			return;
		}

		//获得当前工作空间
		Geodatabase::IWorkspace* pWorkspace = pDataObject->GetWorkspace();
		
		//获得当前编辑层的选择集
		Clear();
 		pEdit->GetCurLayerSelection(m_shapes, m_shapeIds, m_players);

		//多边形要素个数必须大于2
		if(m_shapes.size() < 2)
		{
			Clear();
			return;
		}
		
		Geometry *pGeometry = m_shapes[0];
		for (int i = 1; i < m_shapes.size(); i++)
		{
			pGeometry = pGeometry->Union(m_shapes[i]);
		}

		pWorkspace->StartEditOperation();
		{
			//添加第一个图形
			Geodatabase::CFeaturePtr pFeature;
			pFeature = pFeatureClass->CreateFeature();
			pFeature->SetShape(pGeometry);
			//pFeature->Update();
			pFeatureClass->AddFeature(pFeature.get());
			//其余图形删除
			for(size_t i = 0; i < m_shapes.size(); i++)
			{
				pFeatureClass->DeleteFeature(m_shapeIds[i]);
			}

			//add selection
			//Carto::ILayerPtr ipLayer = pLayer;
			pMap->ClearSelection();
			pMap->SelectFeature(pLayer,pFeature);
			
		}
		pWorkspace->StopEditOperation();
		
		
		Clear();
		
		
		//
		Framework::ITool *pTool = Framework::ITool::FindTool("EditFeatureTool");
		CEditFeatureTool *ipEditorFeatureTool = (CEditFeatureTool*)pTool;
		if(ipEditorFeatureTool)
			ipEditorFeatureTool->ClearMoveGeometrys();
		pMapCtrl->UpdateControl(drawAll);
	}

	void CPolygonUnionTool::Clear()
	{
		for(size_t i=0;i<m_shapes.size();i++)
		{
			delete m_shapes[i];
			m_shapes[i] = NULL;
		}

		m_shapes.clear();
		m_shapeIds.clear();
		m_players.clear();
	}


}
