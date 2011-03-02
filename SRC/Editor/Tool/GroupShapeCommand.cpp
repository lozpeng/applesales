#include "stdafx.h"
#include "ActionGroupShape.h"
#include "IWorkspace.h"
#include "Editor.h"
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/GeometryFactory.h>
using  namespace TT_GEOMETRY::geom;



namespace otEditor
{
	static CActionGroupShape gActionGroupShape;

	CActionGroupShape::CActionGroupShape(void) : IAction("ActionGroupShape")
	{
		RegisterAction("ActionGroupShape", this);
	}

	CActionGroupShape::~CActionGroupShape(void)
	{
		
	}

	void CActionGroupShape::Triger()
	{
		//获取活动地图控件
		otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
		if(!pMap)
			return;

		CEditorPtr pEdit = pMap->GetEditor();
		if (!pEdit)
		{
			return;
		}
	
		pEdit->GetCurLayerSelection(m_shapes, m_shapeIds, m_players);
		if(m_shapes.size( )<= 1)
		{
			return;
		}
			
		//图形成组
		GroupShape();

		Clear();
	}

	void CActionGroupShape::Clear()
	{
		for(size_t i=0;i<m_shapes.size();i++)
		{
			delete m_shapes[i];
			m_shapeIds[i] = NULL;
		}

		m_shapes.clear();
		m_shapeIds.clear();
		m_players.clear();
	}
	
	void CActionGroupShape::GroupShape()
	{
		//获取活动地图控件
		otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
		if(!pMap)
			return;

		CEditorPtr pEdit = pMap->GetEditor();
		if (!pEdit)
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

		//获得数据集
		GeodataModel::IDataObjectPtr pDataObject = pLayer->GetDataObject();
		if (!pDataObject)
		{
			return;
		}
		
		//获得当前工作空间
		GeodataModel::IWorkspace* pWorkspace = pDataObject->GetWorkspace();

		//获得数据集
		GeodataModel::IFeatureClass *pFeatureClass = dynamic_cast<GeodataModel::IFeatureClass*>(pDataObject.get());
		long lshpType = pFeatureClass->ShapeType(); 

		Geometry *pGeometry = NULL;		   //被组合的图形
		Geometry *pGroupGeometry = NULL;  //组合后的图形
		Geometry *pPartGeometry = NULL;	  //组成图形的部分
		
		switch(lshpType)
		{
			case TT_GEOMETRY::geom::GEOS_POLYGON: 
				 {
					pGroupGeometry = m_shapes[0]->clone();
					TT_GEOMETRY::geom::Polygon *pGroupPolygon = dynamic_cast<TT_GEOMETRY::geom::Polygon*> (pGroupGeometry);
					
					for (int i = 1; i < m_shapes.size(); i++)
					{
						pGeometry = m_shapes[i];
						TT_GEOMETRY::geom::Polygon *pPolygon = dynamic_cast<TT_GEOMETRY::geom::Polygon*> (pGeometry);
						
						//获得多变形包含的环
						long nRingcount = pPolygon->GeometryCount();
						if (nRingcount < 1)
						{
							continue;
						}

						for (int i = 0; i < nRingcount; i++ )
						{
							pPartGeometry = pPolygon->GetGeometry(i)->clone();
							if (!pPartGeometry)
							{
								continue;
							}

							pGroupPolygon->AddGeometry(pPartGeometry);
						}
					}
				 }
				 break;
			case TT_GEOMETRY::geom::GEOS_MULTIPOINT:
				 {
					 pGroupGeometry = m_shapes[0]->clone();
					 TT_GEOMETRY::geom::MultiPoint *pGroupPoint = dynamic_cast<TT_GEOMETRY::geom::MultiPoint*> (pGroupGeometry);

					for (int i = 1; i < m_shapes.size(); i++)
					{
						pGeometry = m_shapes[i];
						TT_GEOMETRY::geom::MultiPoint *pMultiPoint = dynamic_cast<TT_GEOMETRY::geom::MultiPoint*> (pGeometry);

						//获得点
						long nPtcount = pMultiPoint->GeometryCount();
						if (nPtcount < 1)
						{
							continue;
						}

						for (int i = 0; i < nPtcount; i++ )
						{
							pPartGeometry = pMultiPoint->GetGeometry(i)->clone();
							if (!pPartGeometry)
							{
								continue;
							}

							pGroupPoint->AddGeometry(pGeometry);
						}
					}
				 }
				 break;
			case TT_GEOMETRY::geom::GEOS_MULTILINESTRING:
				 {
					 pGroupGeometry = m_shapes[0]->clone();
					 TT_GEOMETRY::geom::MultiLineString *pGroupLineString = dynamic_cast<TT_GEOMETRY::geom::MultiLineString*> (pGroupGeometry);

					 for (int i = 1; i < m_shapes.size(); i++)
					 {
						 pGeometry = m_shapes[i];
						 TT_GEOMETRY::geom::MultiLineString *pMultiLineString = dynamic_cast<TT_GEOMETRY::geom::MultiLineString*> (pGeometry);

						 //获得线
						 long nLineStringcount = pMultiLineString->GeometryCount();
						 if (nLineStringcount < 1)
						 {
							 continue;
						 }

						 for (int i = 0; i < nLineStringcount; i++ )
						 {
							 pPartGeometry = pMultiLineString->GetGeometry(i)->clone();
							 if (!pPartGeometry)
							 {
								 continue;
							 }

							 pMultiLineString->AddGeometry(pGeometry);
						 }
					 }
				 }
				 break;
			default:
				break;

		}
		
		pWorkspace->StartEditOperation();
		{
			//添加第一个图形
			GeodataModel::CFeaturePtr pFeature;
			pFeature = pFeatureClass->GetFeature(m_shapeIds[0]);
			pFeature->SetShape(pGroupGeometry);
			pFeature->Update();

			//其余图形删除
			for(size_t i = 1; i < m_shapes.size(); i++)
			{
				pFeatureClass->DeleteFeature(m_shapeIds[i]);
			}
		}
		pWorkspace->StopEditOperation();
		
		Clear();

		pMapCtrl->UpdateControl(drawAll);
	}
	
}


