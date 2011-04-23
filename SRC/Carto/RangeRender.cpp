#include "stdafx.h"
#include "RangeRender.h"
#include "IArchive.h"
#include "Feature.h"
#include "IFeatureCursor.h"
#include "SymbolFactory.h"
#include "IFeatureClass.h"
#include "IFeatureSelection.h"

namespace Carto
{
CRangeRender::CRangeRender()
{
	m_type = RANGERENDER;

	m_dminValue =0.0;

}

CRangeRender::~CRangeRender()
{

}

void CRangeRender::Draw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor )
{
	Geodatabase::IFeatureCursorPtr pFeatureCursor = pCursor;
	if( pCursor == NULL )
	{
		return;
	}

	long RangeFieldIndex = -1;
	
	Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pFeatureCursor->GetTable());

	RangeFieldIndex =pFeatureClass->FindField(m_RendFieldsStr.c_str());


	if( RangeFieldIndex <=0)
	{
		
		return;
	}

	for (size_t i=0;i<m_Classes.size();i++)
	{
		pDisplay->SetSymbolInStack( m_Classes[i].pSymbol.get());
	}

	
	Geodatabase::CFeaturePtr pfeature;
	long lSelSymbol = 0;
	Display::ISymbolPtr pSymbol;

	pDisplay->Begin();

	long nshape =0;

	//动态投影
	if(m_pAffineTransform && m_pAffineTransform->GetEnableUsed())
	{
		GEOMETRY::geom::Geometry *pShape;
		// 字符传类型
		while(!pFeatureCursor->IsEOF())
		{
			pfeature = pFeatureCursor->NextRow();

			nshape++;

			lSelSymbol = GetIndex(pfeature->GetValue(RangeFieldIndex).GetAsDouble());

			if(lSelSymbol==-1)
			{
				continue;
			}

			pDisplay->SelectStackSymbol( lSelSymbol );

			pShape =pfeature->GetShape();
			
			m_pAffineTransform->Transform(pShape);
			pDisplay->Draw(pShape);

			if(nshape%MAX_DISPLAY_SHAPE==0)
			{
				pDisplay->UpdateGeography();
			}
			

		}
	}
	else
	{
		// 字符传类型
		while(!pFeatureCursor->IsEOF())
		{
			pfeature = pFeatureCursor->NextRow();

			nshape++;

			lSelSymbol = GetIndex(pfeature->GetValue(RangeFieldIndex).GetAsDouble());

			if(lSelSymbol==-1)
			{
				continue;
			}


			pDisplay->SelectStackSymbol( lSelSymbol );
			pDisplay->Draw( pfeature->GetShape() );

			if(nshape%MAX_DISPLAY_SHAPE==0)
			{
				pDisplay->UpdateGeography();
			}

		}
	}
	

	pDisplay->End();
}



std::string CRangeRender::GetRendFieldsStr()
{

	return m_RendFieldsStr;

}

void CRangeRender::SetClassField(std::string strField)
{
	m_RendFieldsStr =strField;
}

double CRangeRender::GetBreakValue(long index)
{
	if(index<0 || index>=m_Classes.size())
	{
		return 0.0;
	}
	return m_Classes[index].dvalue;
}

void CRangeRender::SetBreakValue(long index,double value)
{
	if(index<0 || index>=m_Classes.size())
	{
		return;
	}
    
	m_Classes[index].dvalue =value;

}

double CRangeRender::GetminBreakValue()
{
	return m_dminValue;
}

void   CRangeRender::SetminBreakValue(double value)
{
	m_dminValue =value;
}

Display::ISymbolPtr CRangeRender::GetSymbolByValue(double Value)
{
	//判断该值落在哪个分段中
	if(Value<m_Classes[0].dvalue)
	{
		return m_Classes[0].pSymbol;
	}
	for(size_t i=1;i<m_Classes.size();i++)
	{
		if(Value<m_Classes[i].dvalue && Value>=m_Classes[i-1].dvalue)
		{
			return m_Classes[i].pSymbol;
		}
	}
	return NULL;

}

Display::ISymbolPtr CRangeRender::GetSymbol(long index)
{
	if(index<0 || index>=m_Classes.size())
	{
		return NULL;
	}
	return m_Classes[index].pSymbol;

}

void CRangeRender::SetSymbol(long index,Display::ISymbolPtr pSymbol)
{
	assert(index>=0 && index<m_Classes.size());
    
    m_Classes[index].pSymbol =pSymbol;
}

long CRangeRender::GetCount()
{
	return m_Classes.size();
}

void CRangeRender::SetClassCount(long num)
{
	m_Classes.resize(num);
}


std::string CRangeRender::GetLabel(long index)
{
   	assert(index>=0 && index<m_Classes.size());

	return m_Classes[index].strLable;
}

void CRangeRender::SetLabel(long index, std::string strLabel)
{
    assert(index>=0 && index<m_Classes.size());

    m_Classes[index].strLable =strLabel;
}

void CRangeRender::SetHeading(std::string strHeading)
{
	m_strHeading =strHeading;
}

std::string CRangeRender::GetHeading()
{
	return m_strHeading;
}

void CRangeRender::clear()
{
	m_Classes.clear();
}


void CRangeRender::serialization(SYSTEM::IArchive &ar)
{
	IRender::serialization( ar );

	ar & m_RendFieldsStr;
    ar & m_strHeading;

	//最小值
	ar & m_dminValue;

	int nCount;
	if( ar.IsRead() )
	{	
		
		std::string strLable;
		double dvalue;
		Display::ISymbolPtr pSymbol;

		BreakClass bc;

        ar &nCount;
		for(int i=0;i<nCount;i++)
		{
            ar & dvalue;
			ar & strLable;

			pSymbol = Display::CSymbolFactory::CreateSymbolFromStream( ar ); 

			bc.dvalue =dvalue;
			bc.strLable =strLable;
			bc.pSymbol =pSymbol;

			m_Classes.push_back(bc);

		}
	}
	else
	{
        nCount =m_Classes.size();
		ar & nCount;
		for(int i=0;i<nCount;i++)
		{
			//范围值
			ar & m_Classes[i].dvalue;
            
			//标签
			ar & m_Classes[i].strLable;

			//符号
			m_Classes[i].pSymbol->serialization( ar );
		}
	}

}

long CRangeRender::GetIndex(double Value)
{
	if(Value<m_Classes[0].dvalue)
	{
		return 0;
	}
	for(size_t i=1;i<m_Classes.size();i++)
	{
		if(Value<m_Classes[i].dvalue && Value>=m_Classes[i-1].dvalue)
		{
			return i;
		}
	}
	return -1;
}

CLegendInfoPtr CRangeRender::GetLegendInfo()
{
	CLegendInfoPtr pLegendInfo(new CLegendInfo());

	//只有一个Gruop
	CLegendGroupPtr pGroup(new CLegendGroup());

	pGroup->SetHeading(m_strHeading);
	LegendItem item;

	for(int i=0;i<m_Classes.size();i++)
	{
		item.pSymbol =m_Classes[i].pSymbol;
		item.strLabel =m_Classes[i].strLable;
		pGroup->AddItem(item);
	}

	pLegendInfo->AddGroup(pGroup);

	return pLegendInfo;
}

void  CRangeRender::HighLightDraw(Display::IDisplayPtr pDisplay, Geodatabase::ISelctionSet *pSelections)
{
	if(!pDisplay || !pSelections)
	{
		return;
	}

	if(!m_pHighLightSymbol)
	{
		return;
	}
	//得到矢量数据源
	Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pSelections->GetTable());
	if(!pFeatureClass)
	{
		return;
	}

	
	// 设置选择符号的颜色
	Display::ISymbolPtr copySymbol;
	//如果存在高亮符号，则使用高亮符号
	
	copySymbol =m_pHighLightSymbol;



	long index;
	pSelections->ResetIndex();
	GEOMETRY::geom::Geometry *pShape =NULL;
	GEOMETRY::geom::Envelope envelop;
	pDisplay->GetDisplayTransformation().GetGeoBound(envelop);

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
				//判断是否在视图范围内
				if(envelop.intersects(pShape->getEnvelopeInternal()))
				{
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
				//判断是否在视图范围内
				if(envelop.intersects(pShape->getEnvelopeInternal()))
				{
					pDisplay->Draw( pShape );
				}
				delete pShape;
			}
		}
	}
	

	pDisplay->End();
}

} //namespace Carto
