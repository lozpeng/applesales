#include "stdafx.h"
#include "UnGroupShapeCommand.h"
//#include "PlgOPInterface.h"
#include "PolygonUnionCommand.h"
#include "IWorkspace.h"
//#include "SnapAgent.h"
#include "IMapCtrl.h"

#include  <Geometry/geom/Geometry.h>

namespace Editor
{
	static CActionUnGroupShape gActionUnGroupShape;

	CActionUnGroupShape::CActionUnGroupShape(void) : ICommand("ActionUnGroupShape")
	{
		
	}

	CActionUnGroupShape::~CActionUnGroupShape(void)
	{
		
	}
	//��ʼ��
	void CActionUnGroupShape::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);
	}
	void CActionUnGroupShape::Click()
	{
		//��ȡ���ͼ�ؼ�
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//��ȡ�����
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;

		//CEditorPtr pEdit = pMap->GetEditor();
		//if (!pEdit)
		//{
		//	return;
		//}

		//pEdit->GetCurLayerSelection(m_shapes, m_shapeIds, m_players);
		if(m_shapes.size( )< 1)
		{
			return;
		}

		//ͼ�γ���
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
		//��ȡ���ͼ�ؼ�
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//��ȡ�����
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;

		//CEditorPtr pEdit = pMap->GetEditor();
		//if (!pEdit)
		//{
		//	return;
		//}

		//��õ�ǰ�༭��
		Carto::ILayer *pLayer ;//= pEdit->GetCurLayer();
		if (!pLayer)
		{
			return;
		}

		//�жϱ༭���������Ƿ���ʸ������
		if(pLayer->GetLayerType() != Carto::FeatureLayer)
		{
			return;
		}

		//������ݼ�
		Geodatabase::IGeodataObjectPtr pDataObject = pLayer->GetDataObject();
		if (!pDataObject)
		{
			return;
		}

		//��õ�ǰ�����ռ�
		Geodatabase::IWorkspace* pWorkspace = pDataObject->GetWorkspace();

		//������ݼ�
		Geodatabase::IFeatureClass *pFeatureClass = dynamic_cast<Geodatabase::IFeatureClass*>(pDataObject.get());
		long lshpType = pFeatureClass->ShapeType(); 

		vector<Geometry*> vUngroupGeo;	   //��ɢ��Ľ��
		Geometry *pGeometry = NULL;		   //����ɢ��ͼ��
		Geometry *pPartGeometry = NULL;	  //���ͼ�εĲ���
		
		switch(lshpType)
		{
		case GEOMETRY::geom::GEOS_POLYGON: 
			{
				for (int i = 0; i < m_shapes.size(); i++)
				{
					pGeometry = m_shapes[i];
					GEOMETRY::geom::Polygon *pPolygon = dynamic_cast<GEOMETRY::geom::Polygon*> (pGeometry);

					//��ö���ΰ����Ļ�
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
		case GEOMETRY::geom::GEOS_MULTIPOINT:
			{
				for (int i = 0; i < m_shapes.size(); i++)
				{
					pGeometry = m_shapes[i];
					GEOMETRY::geom::MultiPoint *pMultiPoint = dynamic_cast<GEOMETRY::geom::MultiPoint*> (pGeometry);

					//��õ�
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
		case GEOMETRY::geom::GEOS_MULTILINESTRING:
			{
				for (int i = 0; i < m_shapes.size(); i++)
				{
					pGeometry = m_shapes[i];
					GEOMETRY::geom::MultiLineString *pMultiLineString = dynamic_cast<GEOMETRY::geom::MultiLineString*> (pGeometry);

					//�����
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
			//����ͼ��ɾ��
			for(size_t i = 0; i < m_shapeIds.size(); i++)
			{
				pFeatureClass->DeleteFeature(m_shapeIds[i]);
			}
		}

		//��Ӵ�ɢ��ͼ�� 
		for (size_t i = 0; i < vUngroupGeo.size(); i++)
		{
			GEOMETRY::geom::Polygon *pPolygon = GeometryFactory::getDefaultInstance()->createPolygon();;
			pPolygon->AddGeometry(vUngroupGeo[i]);
			
			Geodatabase::CFeaturePtr pnewFeature =pFeatureClass->CreateFeature();
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