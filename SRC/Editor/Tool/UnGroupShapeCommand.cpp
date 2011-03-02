#include "stdafx.h"
#include "UnGroupShapeCommand.h"
#include "PlgOPInterface.h"
#include "ActionPolygonUnion.h"
#include "IWorkspace.h"
#include "SnapAgent.h"

#include  <Geometry/geom/Geometry.h>

namespace Editor
{
	static CActionUnGroupShape gActionUnGroupShape;

	CActionUnGroupShape::CActionUnGroupShape(void) : IAction("ActionUnGroupShape")
	{
		RegisterAction("ActionUnGroupShape", this);
	}

	CActionUnGroupShape::~CActionUnGroupShape(void)
	{
		
	}

	void CActionUnGroupShape::Triger()
	{
		//获取活动地图控件
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		Carto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
		if(!pMap)
			return;

		CEditorPtr pEdit = pMap->GetEditor();
		if (!pEdit)
		{
			return;
		}

		pEdit->GetCurLayerSelection(m_shapes, m_shapeIds, m_players);
		if(m_shapes.size( )< 1)
		{
			return;
		}

		//图形成组
		UnGroupShape();

		Clear();
	}

	void CActionUnGroupShape::Clear()
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

	void CActionUnGroupShape::UnGroupShape()
	{
		//获取活动地图控件
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		Carto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
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
		if(pLayer->GetLayerType() != Carto::eFeatureLayer)
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

		vector<Geometry*> vUngroupGeo;	   //打散后的结果
		Geometry *pGeometry = NULL;		   //被打散的图形
		Geometry *pPartGeometry = NULL;	  //组成图形的部分
		
		switch(lshpType)
		{
		case TT_GEOMETRY::geom::GEOS_POLYGON: 
			{
				for (int i = 0; i < m_shapes.size(); i++)
				{
					pGeometry = m_shapes[i];
					TT_GEOMETRY::geom::Polygon *pPolygon = dynamic_cast<TT_GEOMETRY::geom::Polygon*> (pGeometry);

					//获得多边形包含的环
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

						vUngroupGeo.push_back(pPartGeometry);
					}
				}
			}
			break;
		case TT_GEOMETRY::geom::GEOS_MULTIPOINT:
			{
				for (int i = 0; i < m_shapes.size(); i++)
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

						vUngroupGeo.push_back(pPartGeometry);
					}
				}
			}	
			break;
		case TT_GEOMETRY::geom::GEOS_MULTILINESTRING:
			{
				for (int i = 0; i < m_shapes.size(); i++)
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

						vUngroupGeo.push_back(pPartGeometry);
					}
				}
			}
			break;
		default:
			break;

		}

		pWorkspace->StartEditOperation();
		{
			//其余图形删除
			for(size_t i = 0; i < m_shapeIds.size(); i++)
			{
				pFeatureClass->DeleteFeature(m_shapeIds[i]);
			}
		}

		//添加打散的图形 
		for (size_t i = 0; i < vUngroupGeo.size(); i++)
		{
			TT_GEOMETRY::geom::Polygon *pPolygon = GeometryFactory::getDefaultInstance()->createPolygon();;
			pPolygon->AddGeometry(vUngroupGeo[i]);
			
			GeodataModel::CFeaturePtr pnewFeature =pFeatureClass->CreateFeature();
			pnewFeature->SetShape(((Geometry*)pPolygon)->clone());
			//pnewFeature->Update();
			pFeatureClass->AddFeature(pnewFeature.get());

			delete pPolygon;
			pPolygon = NULL;
		}
		pWorkspace->StopEditOperation();
		
		Clear();

		pMapCtrl->UpdateControl(drawAll);		
	}
}