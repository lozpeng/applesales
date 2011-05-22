#include "stdafx.h"

#include "ILayer.h"
#include "FeatureLayer.h"
#include "RasterLayer.h"
//#include "GraphicLayer.h"
//#include "IDataObject.h"
#include "ShapefileWorkspaceFactory.h"
#include "RasterWSFactory.h"
#include "RelativePath.h"
#include "IWorkspace.h"
namespace Carto
{

	ILayer::ILayer()
	{
		m_bVisible = true;
		m_TransparentAlphaValue = 0;

		m_bScaleRange = false;
		m_dScaleMax = 1000;
		m_dScaleMin = 100;
		m_layerType = UnknownLayer;

		m_pDataObject.reset();
		m_Name = "";
		m_csDescription = "";

		m_pAffineTransform = new CAffineTransform();

		m_bCached = true;
		m_sCachedId = -1;

	}

	ILayer::~ILayer()
	{

	}

	bool ILayer::SetData(Geodatabase::IGeodataObjectPtr pDataObject)
	{
		m_pDataObject = pDataObject;

		if(pDataObject)
			SetName( pDataObject->Getname().c_str() );

		return true;
	}

	GEOMETRY::geom::Envelope ILayer::GetEnvelope()
	{
		GEOMETRY::geom::Envelope envelop;
		envelop.setToNull();

		if(m_pDataObject.get() != NULL)
			m_pDataObject->GetExtent(&envelop);


		//����Ƕ�̬ͶӰ�������ݷ�Χת����Ŀ��ͶӰ����ϵ��
		if(m_pAffineTransform->GetEnableUsed())
		{
			GEOMETRY::geom::Envelope transEnvelop = envelop;
			m_pAffineTransform->Transform(transEnvelop);
			envelop = transEnvelop;
		}

		return envelop;
	}

	void ILayer::serialization(SYSTEM::IArchive &ar)
	{
		SYSTEM::ISerialization::serialization( ar );

		long type = (long)m_layerType;
		ar & type;

		ar & m_Name;
		ar & m_bVisible;

		ar & m_bScaleRange;
		ar & m_dScaleMax;
		ar & m_dScaleMin;

		ar & m_TransparentAlphaValue;

		if( ar.IsRead() )
		{
			if(type != GraphicLayer)
			{

				std::string type;
				ar&type;
				if(type=="ShpDriver")
				{
					std::string filename;
					ar&filename;

					//ͨ�����·���������·��
					filename =SYSTEM::CRelativePath::FullPath(filename.c_str());

					Geodatabase::IWorkspace *pWorkspace =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(filename.c_str());
					if(pWorkspace)
					{
						m_pDataObject =pWorkspace->OpenFeatureClass(filename.c_str());

					}

				}
				else if(type=="GDALDriver")
				{
					std::string filename;
					ar&filename;

					//ͨ�����·���������·��
					filename =SYSTEM::CRelativePath::FullPath(filename.c_str());

					Geodatabase::IWorkspace *pWorkspace =CRasterWSFactory::GetInstance()->OpenFromFile(filename.c_str());
					if(pWorkspace)
					{
						m_pDataObject =pWorkspace->OpenRasterDataset(filename.c_str());
					}


				}

			}

			long lAuxiLayerCnt;
			ar & lAuxiLayerCnt;
			for (long i = 0 ; i < lAuxiLayerCnt ; i++ )
			{
				ILayerPtr player = ILayer::CreateLayerFromStream( ar );
				if( player != NULL )
					m_auxiliaryLayers.push_back( player );
			}
		}
		else
		{
			if(type != GraphicLayer)
				m_pDataObject->serialization(ar);

			long lAuxiLayerCnt = m_auxiliaryLayers.size();
			ar & lAuxiLayerCnt;
			for(int i=0; i<lAuxiLayerCnt; i++)
				m_auxiliaryLayers[i]->serialization(ar);
		}
	}

	ILayerPtr ILayer::CreateLayer(Geodatabase::IGeodataObjectPtr pDataObject)
	{
		ILayerPtr player;
		switch ( pDataObject->GetType() )
		{
		case Geodatabase::GDT_FEATURECLASS:
			return CFeatureLayer::CreateFeatureLayer( pDataObject );
		case Geodatabase::GDT_RASTERDATASET:
			return CRasterLayer::CreateRasterLayer(pDataObject);
			//case GDT_TINDATASET:
			//return CTinLayer::CreateTinLayer(pDataObject);
		default:
			return NULL;
		}
		return NULL;
	}

	ILayerPtr ILayer::CreateLayerFromStream( SYSTEM::IArchive &ar )
	{
		int startpos = ar.GetCurrentPos();

		int type;
		ar & type;

		ar.GetCurrentPos() = startpos; 

		switch((LAYER_TYPE)type)
		{
		case  Carto::FeatureLayer:
			{
				ILayerPtr player( new CFeatureLayer() );
				if( player == NULL )
					return NULL;

				player->serialization( ar );
				return player;
			}		
			break;
		case Carto::RasterLayer:
			{
				ILayerPtr player( new CRasterLayer() );
				if( player == NULL )
					return NULL;

				player->serialization( ar );
				return player;
			}		
			break;
		case  Carto::GraphicLayer:
			{
				ILayerPtr player( new CGraphicLayer() );
				if( player == NULL )
					return NULL;
				player->serialization( ar );
				return player;
			}		
			break;

		}


		return NULL;
	}


	void ILayer::BeforeDraw(Display::IDisplayPtr pDisplay)
	{
	}


	void ILayer::AfterDraw(Display::IDisplayPtr pDisplay)
	{
	}

	void ILayer::SetLayerPosition(LAYER_POSITION pos)
	{
		m_Position = pos;
	}

	LAYER_POSITION ILayer::GetLayerPostion()
	{
		return m_Position;
	}

	void ILayer::AddAuxiliaryLayer(ILayerPtr ptrLayer)
	{
		if(IsAuxiliaryLayerExist(ptrLayer))
			return;
		m_auxiliaryLayers.push_back(ptrLayer);
	}

	bool ILayer::RemoveAuxiliaryLayer(ILayerPtr ptrLayer)
	{
		std::vector<ILayerPtr>::iterator it = std::find(m_auxiliaryLayers.begin(), m_auxiliaryLayers.end(), ptrLayer);
		if(it == m_auxiliaryLayers.end())
			return false;
		m_auxiliaryLayers.erase(it);
		return true;
	}

	bool ILayer::IsAuxiliaryLayerExist(ILayerPtr ptrLayer)
	{
		return (std::find(m_auxiliaryLayers.begin(), m_auxiliaryLayers.end(), ptrLayer) != m_auxiliaryLayers.end());
	}

	ILayerPtr ILayer::GetAuxiliaryLayer(long index)
	{
		if(index < 0 || index >= long(m_auxiliaryLayers.size()))
			return NULL;
		return m_auxiliaryLayers[index];
	}

	long ILayer::GetAuxiliaryLayerCount()
	{
		return long(m_auxiliaryLayers.size());
	}

	void ILayer::Draw(Display::IDisplayPtr pDisplay,DRAW_CONTENT content)
	{
		size_t count = GetAuxiliaryLayerCount();
		for(size_t i=0; i<count; ++i)
			GetAuxiliaryLayer(i)->Draw(pDisplay,content);
	}

	void ILayer::Select(Geodatabase::CSimpleQuery* query, SELECT_OPTION selectOption)
	{

	}

	CLegendInfoPtr ILayer::GetLegendInfo()
	{
		return NULL;
	}
	void ILayer::get_Cached(bool& bCached)
	{
		bCached = m_bCached;
	}
	void ILayer::set_Cached(bool bCached)
	{
		m_bCached = bCached;
	}
	void ILayer::get_CacheId(short& sId)
	{
		sId = m_sCachedId;
	}
	void ILayer::set_CacheId(short sId)
	{
		m_sCachedId = sId;
	}
}