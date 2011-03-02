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
		//��ȡ���ͼ�ؼ�
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//��ȡ�����
		Carto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
		if(!pMap)
			return;

		//��ñ༭��
		Editor::CEditorPtr pEdit =pMap->GetEditor();
		if(!pEdit)
		{
			return;
		}

		//��õ�ǰ�༭��
		Carto::ILayer *pLayer = pEdit->GetCurLayer();
		if (!pLayer)
		{
			return;
		}

		//�жϱ༭���������Ƿ���ʸ������
		if(pLayer->GetLayerType() != Carto::eFeatureLayer)
		{
			return;
		}

		//��õ�ǰ�༭��ͼ�ε����ͣ��ж��Ƿ��Ƕ����Ҫ��
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

		//��õ�ǰ�����ռ�
		GeodataModel::IWorkspace* pWorkspace = pDataObject->GetWorkspace();

		//��õ�ǰ�༭���ѡ��
		Clear();
		pEdit->GetCurLayerSelection(m_shapes, m_shapeIds, m_players);

		//�����Ҫ�ظ����������2
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
			//��ӵ�һ��ͼ��
			GeodataModel::CFeaturePtr pFeature;
			pFeature = pFeatureClass->CreateFeature();
			pFeature->SetShape(pGeometry);
			//pFeature->Update();
			pFeatureClass->AddFeature(pFeature.get());
			//����ͼ��ɾ��
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
