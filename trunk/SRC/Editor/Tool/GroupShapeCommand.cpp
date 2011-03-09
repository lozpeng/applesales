#include "stdafx.h"
#include "GroupShapeCommand.h"
#include "IWorkspace.h"
#include "IMapCtrl.h"
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/GeometryFactory.h>
using  namespace GEOMETRY::geom;



namespace Editor
{
	static CActionGroupShape gActionGroupShape;

	CActionGroupShape::CActionGroupShape(void) : ICommand("ActionGroupShape")
	{
		
	}

	CActionGroupShape::~CActionGroupShape(void)
	{
		
	}
	void CActionGroupShape::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);
	}
	void CActionGroupShape::Click()
	{
		//获取活动地图控件
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
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
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;

		CEditorPtr pEdit = pMap->GetEditor();
		if (!pEdit)
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

		//获得数据集
		Geodatabase::IGeodataObjectPtr pDataObject = pLayer->GetDataObject();
		if (!pDataObject)
		{
			return;
		}
		
		//获得当前工作空间
		Geodatabase::IWorkspace* pWorkspace = pDataObject->GetWorkspace();

		//获得数据集
		Geodatabase::IFeatureClass *pFeatureClass = dynamic_cast<Geodatabase::IFeatureClass*>(pDataObject.get());
		long lshpType = pFeatureClass->ShapeType(); 

		Geometry *pGeometry = NULL;		   //被组合的图形
		Geometry *pGroupGeometry = NULL;  //组合后的图形
		Geometry *pPartGeometry = NULL;	  //组成图形的部分
		
		switch(lshpType)
		{
			case GEOMETRY::geom::GEOS_POLYGON: 
				 {
					pGroupGeometry = m_shapes[0]->clone();
					GEOMETRY::geom::Polygon *pGroupPolygon = dynamic_cast<GEOMETRY::geom::Polygon*> (pGroupGeometry);
					
					for (int i = 1; i < m_shapes.size(); i++)
					{
						pGeometry = m_shapes[i];
						GEOMETRY::geom::Polygon *pPolygon = dynamic_cast<GEOMETRY::geom::Polygon*> (pGeometry);
						
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
			case GEOMETRY::geom::GEOS_MULTIPOINT:
				 {
					 pGroupGeometry = m_shapes[0]->clone();
					 GEOMETRY::geom::MultiPoint *pGroupPoint = dynamic_cast<GEOMETRY::geom::MultiPoint*> (pGroupGeometry);

					for (int i = 1; i < m_shapes.size(); i++)
					{
						pGeometry = m_shapes[i];
						GEOMETRY::geom::MultiPoint *pMultiPoint = dynamic_cast<GEOMETRY::geom::MultiPoint*> (pGeometry);

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
			case GEOMETRY::geom::GEOS_MULTILINESTRING:
				 {
					 pGroupGeometry = m_shapes[0]->clone();
					 GEOMETRY::geom::MultiLineString *pGroupLineString = dynamic_cast<GEOMETRY::geom::MultiLineString*> (pGroupGeometry);

					 for (int i = 1; i < m_shapes.size(); i++)
					 {
						 pGeometry = m_shapes[i];
						 GEOMETRY::geom::MultiLineString *pMultiLineString = dynamic_cast<GEOMETRY::geom::MultiLineString*> (pGeometry);

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
			Geodatabase::CFeaturePtr pFeature;
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


