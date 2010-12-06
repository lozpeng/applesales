#include "stdafx.h"
#include "SimpleRender.h"
#include "ICursor.h"
#include "Feature.h"
#include "IFeatureSelection.h"
#include "IFeatureClass.h"
#include "SymbolFactory.h"

namespace Carto
{

CSimpleRender::CSimpleRender()
{
    m_type =SIMPLERENDER;
}

CSimpleRender::~CSimpleRender()
{

}

void CSimpleRender::SetSymbol( Display::ISymbolPtr pSymbol )
{
	m_pSymbol = pSymbol;
}

void CSimpleRender::Draw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor )
{
	
	if( pCursor == NULL )
	{
		//OTTRACE("pdatarecordset = NULL");
		return;
	}

	pDisplay->SetSymbol( m_pSymbol.get() );

	pDisplay->Begin();

	Geodatabase::CFeaturePtr pFeature;
    
	long nshape =0;

	//�Ƿ���ж�̬ͶӰ
	if(m_pAffineTransform && m_pAffineTransform->GetEnableUsed())
	{
		while(!pCursor->IsEOF())
		{
			pFeature = pCursor->NextRow();

			nshape++;

			GEOMETRY::geom::Geometry* pShape = pFeature->GetShape();

			m_pAffineTransform->Transform(pShape);
			if( pShape )
				pDisplay->Draw( pShape );

			if(nshape%MAX_DISPLAY_SHAPE==0)
			{
				pDisplay->UpdateGeography();
			}
		}
	}
	else
	{
		while(!pCursor->IsEOF())
		{
			pFeature = pCursor->NextRow();

			nshape++;

			GEOMETRY::geom::Geometry* pShape = pFeature->GetShape();
			if( pShape )
				pDisplay->Draw( pShape );

			if(nshape%MAX_DISPLAY_SHAPE==0)
			{
				pDisplay->UpdateGeography();
			}
		}
	}
	

	pDisplay->End();
}

void CSimpleRender::HighLightDraw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor )
{
	if( pCursor == NULL )
	{
		//OTTRACE("pdatarecordset = NULL");
		return;
	}

	// ����ѡ����ŵ���ɫ
	Display::ISymbolPtr copySymbol = m_pSymbol->Clone();
	m_pSymbol->SetColor( m_HighLightColor );

	//
	Draw( pDisplay , pCursor );

	// ��ԭ��ɫ
	m_pSymbol = copySymbol;
}

void CSimpleRender::HighLightDraw(Display::IDisplayPtr pDisplay, Geodatabase::ISelctionSet* pSelections)
{
	if(!pDisplay || !pSelections)
	{
		return;
	}
	//�õ�ʸ������Դ
	Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pSelections->GetTable());
	if(!pFeatureClass)
	{
		return;
	}

	// ����ѡ����ŵ���ɫ
	Display::ISymbolPtr copySymbol;
	//������ڸ������ţ���ʹ�ø�������
	if(m_pHighLightSymbol)
	{
        copySymbol =m_pHighLightSymbol;
	}
	else
	{
		copySymbol =m_pSymbol->Clone();
		copySymbol->SetColor( m_HighLightColor );
	}
	

    long index;
	pSelections->ResetIndex();
	GEOMETRY::geom::Geometry *pShape =NULL;
    GEOMETRY::geom::Envelope envelop;
    pDisplay->GetDisplayTransformation().GetGeoBound(envelop);

	//��̬ͶӰ
	if(m_pAffineTransform && m_pAffineTransform->GetEnableUsed())
	{
        m_pAffineTransform->TransformN(envelop);
	}

	pDisplay->SetSymbol( copySymbol.get() );

	pDisplay->Begin();

	Geodatabase::IFeatureSelection* pFeatureSelection =dynamic_cast<Geodatabase::IFeatureSelection*>(pSelections);

	if(pFeatureSelection!=NULL)
	{
		while(!pFeatureSelection->IsEOF())
		{
			
			pShape =(GEOMETRY::geom::Geometry*)pFeatureSelection->NextShape();
			if(pShape)
			{
				//�ж��Ƿ�����ͼ��Χ��
				if(envelop.intersects(pShape->getEnvelopeInternal()))
				{
					//�Ƿ���ж�̬ͶӰ
					if(m_pAffineTransform && m_pAffineTransform->GetEnableUsed())
					{
						m_pAffineTransform->Transform(pShape);
					}
					pDisplay->Draw( pShape );
				}
			}
		}
	}
	else
	{
		while(!pSelections->IsEOF())
		{
			index =pSelections->NextID();
			pShape =pFeatureClass->GetFeatureShape(index);
			if(pShape)
			{
				//�ж��Ƿ�����ͼ��Χ��
				if(envelop.intersects(pShape->getEnvelopeInternal()))
				{
					//�Ƿ���ж�̬ͶӰ
					if(m_pAffineTransform && m_pAffineTransform->GetEnableUsed())
					{
						m_pAffineTransform->Transform(pShape);
					}
					pDisplay->Draw( pShape );
				}
				delete pShape;
			}
		}
	}
	

	pDisplay->End();


}

std::string CSimpleRender::GetRendFieldsStr()
{
	return "";
}

Display::ISymbolPtr CSimpleRender::GetSymbol()
{
	return m_pSymbol;
}

void CSimpleRender::serialization(SYSTEM::IArchive &ar)
{
	IRender::serialization( ar );

	if( ar.IsRead() )
	{
		m_pSymbol = Display::CSymbolFactory::CreateSymbolFromStream( ar );
	}
	else
		m_pSymbol->serialization( ar );
}

CLegendInfoPtr CSimpleRender::GetLegendInfo()
{
	CLegendInfoPtr pLegendInfo(new CLegendInfo());

	//ֻ��һ��Gruop
	CLegendGroupPtr pGroup(new CLegendGroup());

	LegendItem item;

	item.pSymbol =m_pSymbol;
	pGroup->AddItem(item);
	
	pLegendInfo->AddGroup(pGroup);

	return pLegendInfo;
}

}
