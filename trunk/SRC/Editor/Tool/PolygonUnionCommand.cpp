#include "stdafx.h"
#include "ActionPolygonUnion.h"
#include "IWorkspace.h"
#include "SimpleQuery.h"
#include "Editor.h"
#include <Geometry/geom/Geometry.h>

namespace otEditor
{

	static CActionPolygonUnion gActionPolygonUnion;

	CActionPolygonUnion::CActionPolygonUnion(void) : IAction("ActionPolygonUnion")
	{
		RegisterAction("ActionPolygonUnion", this);
	}

	CActionPolygonUnion::~CActionPolygonUnion(void)
	{

	}
	
	void CActionPolygonUnion::Triger()
	{
		//获取活动地图控件
		otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
		if(!pMap)
			return;

		//获得编辑类
		otEditor::CEditorPtr pEdit =pMap->GetEditor();
		if(!pEdit)
		{
			return;
		}

		//获得当前编辑层
		otCarto::ILayer *pLayer = pEdit->GetCurLayer();
		if (!pLayer)
		{
			return;
		}

		//判断编辑数据类型是否是矢量数据
		if(pLayer->GetLayerType() != otCarto::eFeatureLayer)
		{
			return;
		}

		//获得当前编辑层图形的类型，判断是否是多边形要素
		GeodataModel::IDataObjectPtr pDataObject = pLayer->GetDataObject();
		if (!pDataObject)
		{
			return;
		}

		GeodataModel::IFeatureClass *pFeatureClass = dynamic_cast<GeodataModel::IFeatureClass*>(pDataObject.get());
		long lshpType = pFeatureClass->ShapeType(); 
		if(lshpType != TT_GEOMETRY::geom::GEOS_POLYGON && lshpType != TT_GEOMETRY::geom::GEOS_MULTIPOLYGON)
		{
			return;
		}

		//获得当前工作空间
		GeodataModel::IWorkspace* pWorkspace = pDataObject->GetWorkspace();
		
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
			GeodataModel::CFeaturePtr pFeature;
			pFeature = pFeatureClass->CreateFeature();
			pFeature->SetShape(pGeometry);
			//pFeature->Update();
			pFeatureClass->AddFeature(pFeature.get());
			//其余图形删除
			for(size_t i = 0; i < m_shapes.size(); i++)
			{
				pFeatureClass->DeleteFeature(m_shapeIds[i]);
			}
		}
		pWorkspace->StopEditOperation();
		
		
		Clear();
		
		pMapCtrl->UpdateControl(drawAll);
	}

	void CActionPolygonUnion::Clear()
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
