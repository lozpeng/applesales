#include "stdafx.h"
#include "FeatureLayer.h"
#include "IDisplay.h"
#include "IFeatureClass.h"
#include "SimpleRender.h"
#include "SimpleQuery.h"
#include "SymbolFactory.h"
#include "SelectionSymbol.h"

namespace Carto
{

CFeatureLayer::CFeatureLayer()
{
	m_layerType = FeatureLayer;

	m_bDrawDynamicLabel = false;
}

CFeatureLayer::~CFeatureLayer()
{

}

void CFeatureLayer::serialization(SYSTEM::IArchive &ar)
{
	ILayer::serialization( ar );

	ar & m_bDrawDynamicLabel;

	if( ar.IsRead() )
	{
		BOOL bExist;

		ar & bExist;
		if(bExist)
			m_pRender = IRender::CreateRenderFromStream( ar );
		
		ar & bExist;
		//if(bExist)
		//	m_pSelSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		ar & bExist;
		if(bExist)
		{
			m_pLabelRender = new CLabelRender();
			m_pLabelRender->serialization(ar);
		}
	}
	else
	{
		BOOL bExist = FALSE;
		if(m_pRender)
		{
			bExist = TRUE;
			ar & bExist;
			m_pRender->serialization( ar );
		}
		else
		{
			bExist = FALSE;
			ar & bExist;
		}

		bExist = FALSE;
		if(m_pSelSymbol)
		{
			bExist = TRUE;
			ar & bExist;
			m_pSelSymbol->serialization( ar );
		}
		else
		{
			bExist = FALSE;
			ar & bExist;
		}
		
		bExist = FALSE;
		if(m_pLabelRender)
		{
			bExist = TRUE;
			ar & bExist;
			m_pLabelRender->serialization( ar );
		}
		else
		{
			bExist = FALSE;
			ar & bExist;
		}
	}
}

long CFeatureLayer::GetFeatureType()
{
	//
	Geodatabase::IFeatureClassPtr pFeatureClass =  (Geodatabase::IFeatureClassPtr) m_pDataObject;

	//
	return pFeatureClass->ShapeType();
}

bool CFeatureLayer::SetData(Geodatabase::IGeodataObjectPtr pDataObject)
{
	m_pDataObject = pDataObject;

	m_pRender = IRender::CreateRender( SIMPLERENDER );

	//设置仿射变换参数
	m_pRender->SetAffineTransform(m_pAffineTransform);

	Carto::CSimpleRender *pcRender = dynamic_cast<Carto::CSimpleRender*>(m_pRender.get());

	Display::ISymbolPtr pSymbol,pSelSymbol;

	if( GetFeatureType() == GEOS_POINT || GetFeatureType() == GEOS_MULTIPOINT )
	{
		pSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_MARKER_SYMBOL);

		pSelSymbol =Display::CSelectionSymbol::GetInstance()->GetHighLightPtSymbol();
	}
	else if( GetFeatureType() == GEOS_LINESTRING || GetFeatureType() == GEOS_MULTILINESTRING )
	{
		pSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_LINE_SYMBOL);

		pSelSymbol =Display::CSelectionSymbol::GetInstance()->GetHighLightLineSymbol();
	}
	else if( GetFeatureType() == GEOS_POLYGON || GetFeatureType() == GEOS_MULTIPOLYGON )
	{
		pSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_FILL_SYMBOL);

		pSelSymbol =Display::CSelectionSymbol::GetInstance()->GetHighLightAreaSymbol();
	}
	else if( GetFeatureType() == GEOS_GEOMETRYCOLLECTION )
	{
		// 混合图层
		m_pRender = IRender::CreateRender( MIXSIMPLERENDER );
		pcRender = dynamic_cast<Carto::CSimpleRender*>(m_pRender.get());
		pSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_MARKER_SYMBOL);
		pcRender->SetSymbol( pSymbol );
		pSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_LINE_SYMBOL);
		pcRender->SetSymbol( pSymbol );
		pSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_FILL_SYMBOL);
		pcRender->SetSymbol( pSymbol );
		return true;
	}
	pcRender->SetSymbol( pSymbol );

	SetSelectionSymbol(pSelSymbol);

	return true; 
}


void CFeatureLayer::Draw(Display::IDisplayPtr pDisplay,DRAW_CONTENT content)
{
	if (pDisplay == NULL)	
		return;

	//可见性
	if (!m_bVisible)
	{
		return;
	}

	//显示比例尺范围
	if (m_bScaleRange)
	{
		double scaleValue = pDisplay->GetDisplayTransformation().GetMapScale();

		if (scaleValue < m_dScaleMin)
			return;

		if (scaleValue > m_dScaleMax)
			return;
	}


	if(content==drawGeography)
	{
		GEOMETRY::geom::Envelope env;
		pDisplay->GetDisplayTransformation().GetGeoBound(env);

		//判断是否需要进行动态投影
		if(m_pAffineTransform->GetEnableUsed())
		{
			GEOMETRY::geom::Envelope dataEnv;

			m_pDataObject->GetExtent(&dataEnv);

			//将地图坐标转换到数据坐标
			m_pAffineTransform->TransformN(env);

			//如果读取范围不在数据范围内，返回
			if(!env.intersects(dataEnv))
			{
				return;
			}


		}

		Geodatabase::CSimpleQuery query;
		std::string strFields =((Geodatabase::IFeatureClassPtr)m_pDataObject)->ShapeFieldName();
		if(!m_pRender->GetRendFieldsStr().empty())
		{
			strFields+=",";
			strFields+=m_pRender->GetRendFieldsStr();
		}
		query.AddField(strFields.c_str());
		Geodatabase::ICursorPtr pCursor = ((Geodatabase::IFeatureClassPtr)m_pDataObject)->QueryByExtent(&env,&query);
		// 图层绘制
		if ( m_pRender != NULL )
		{
			BeforeDraw(pDisplay);
			m_pRender->Draw( pDisplay, pCursor );

			//------------绘制Label-----------------------//
			if ( m_pLabelRender && m_bDrawDynamicLabel )
			{
				strFields =((Geodatabase::IFeatureClassPtr)m_pDataObject)->ShapeFieldName();
				if(!m_pLabelRender->GetRendFieldsStr().empty())
				{
					strFields+=",";
					strFields+=m_pLabelRender->GetRendFieldsStr();
				}
				Geodatabase::CSimpleQuery queryLabel;
				queryLabel.AddField( strFields.c_str() );
				Geodatabase::ICursorPtr pCursorLabel = ((Geodatabase::IFeatureClassPtr)m_pDataObject)->QueryByExtent(&env,&queryLabel);

				m_pLabelRender->Draw( pDisplay, pCursorLabel );
			}

			//-------------------------------------------//

			AfterDraw(pDisplay);
		}
	}
	else if(content ==drawGeoSelection)
	{
		BeforeDraw(pDisplay);
		
		//绘制选择集
		m_pRender->HighLightDraw(pDisplay,m_pSelectionset.get());



		AfterDraw(pDisplay);
	}

	//
	ILayer::Draw(pDisplay,drawGeography);
}

void CFeatureLayer::SetFeatureRender(IRenderPtr pRender)
{
	m_pRender = pRender;
	m_pRender->SetHighLightSymbol(m_pSelSymbol);
	m_pRender->SetAffineTransform(m_pAffineTransform);
}

IFeatureLayerPtr CFeatureLayer::CreateFeatureLayer(Geodatabase::IGeodataObjectPtr pDataObject)
{
	CFeatureLayer *player = new  CFeatureLayer();

	if( !player->SetData( pDataObject) )
	{
		return NULL;
	}



	return IFeatureLayerPtr( player);
}

void CFeatureLayer::ClearSelectionSet()
{
    m_pSelectionset.reset();
}

void CFeatureLayer::Select(Geodatabase::CSimpleQuery* query, SELECT_OPTION selectOption)
{
    if(!m_pDataObject)
	{
		return;
	}
	Geodatabase::ISelctionSetPtr pSelection =dynamic_cast<Geodatabase::IFeatureClass*>(m_pDataObject.get())->Select(query);
    
	if(selectOption==SELECT_REPLACE)
	{
		m_pSelectionset =pSelection;
	}
	else if(selectOption==SELECT_ADD)
	{
		if(m_pSelectionset)
		{
           m_pSelectionset->Combine(pSelection.get(),Geodatabase::SetUnion);
		}
		else
		{
			m_pSelectionset =pSelection;
		}
		
	}
}

void CFeatureLayer::SetSelectionSymbol(Display::ISymbolPtr pSymbol)
{
	m_pSelSymbol =pSymbol;
	if(m_pRender)
	{
		m_pRender->SetHighLightSymbol(m_pSelSymbol);
	}
}

void CFeatureLayer::SetSelection(Geodatabase::ISelctionSetPtr pSelection)
{
	m_pSelectionset = pSelection;
}


Display::ISymbolPtr CFeatureLayer::GetSelectionSymbol()
{
	return m_pSelSymbol;
}

std::map<Display::ISymbolPtr, std::string>& CFeatureLayer::GetLabels()
{
	std::map<Display::ISymbolPtr, std::string> labels;
	return labels;
}

std::map<Display::ISymbolPtr, std::string>& CFeatureLayer::GetDecriptions()
{
	std::map<Display::ISymbolPtr, std::string> descriptions;
	return descriptions;
}

CLegendInfoPtr CFeatureLayer::GetLegendInfo()
{
	if(m_pRender)
	{
		return m_pRender->GetLegendInfo();
	}
	return NULL;
}


}

