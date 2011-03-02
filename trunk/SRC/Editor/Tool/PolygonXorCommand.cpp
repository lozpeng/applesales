#include "stdafx.h"

#include "PolygonUnionCOmmand.h"
#include "ActionPolygonXor.h"
#include "TT_PlgOPInterface.h"
#include "IWorkspace.h"
#include <Geometry/geom/Geometry.h>

namespace Editor
{

	static CActionPolygonXor gActionPolygonXor;

	CActionPolygonXor::CActionPolygonXor(void) : IAction("ActionPolygonXor")
	{
		RegisterAction("ActionPolygonXor", this);
	}

	CActionPolygonXor::~CActionPolygonXor(void)
	{

	}

	void CActionPolygonXor::Triger()
	{
		//获取活动地图控件
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		Carto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
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
		if(pLayer->GetLayerType() != Carto::eFeatureLayer)
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

			pGeometry = pGeometry->symDifference(m_shapes[i]);
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

	void CActionPolygonXor::Clear()
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
