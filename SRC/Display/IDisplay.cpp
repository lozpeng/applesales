#include "stdafx.h"
#include "IDisplay.h"
#include "ISymbol.h"
#include "CDC.h"
//#include "TextSymbol.h"

namespace Display
{

static boost::signal<void ()> gCallbackUpdteGeography;

IDisplay::IDisplay()
{
	m_BgColor = RGB(255,255,255);

	m_pDC = new CDC;
	m_pSymbol = NULL;
	bDraw = FALSE;

	m_pDC->SetBGColor(m_BgColor);

	m_bLayoutDis = FALSE;

	m_bPrint = FALSE;
}



IDisplay::~IDisplay()
{
	if(m_pDC)
	{
		delete m_pDC;
		m_pDC = NULL;
	}	
}

SYSTEM::CSmartPtr<IDisplay> IDisplay::Clone()
{
	IDisplay* pDisplay = new IDisplay;
	*pDisplay = *this;

	return IDisplayPtr(pDisplay);
}

void IDisplay::SetLayoutDisplay(BOOL bLayoutDis)
{
	m_bLayoutDis = bLayoutDis;
}

BOOL IDisplay::GetBeLayoutDisplay()
{
	return m_bLayoutDis;
}

Display::CDisplayTransformation& IDisplay::GetDisplayTransformation()
{
	return m_cDisplayTransformation;
}

/**
* ����ͼ��
* @param pSymbol ����
* @param rect ��������
* @param nFlag �ж���ʾ��ʽ��ֱ�߻����ߣ�
*/
void IDisplay::DrawLegend(ISymbol* pSymbol, DIS_RECT * rect, int nFlag)
{
	SetSymbol( pSymbol );

	Begin();

	m_pSymbol->DrawLegend( rect ,  nFlag );

	End();
}

/**
* ����ͼ��
* @param pSymbol ����
* @param lPosx ����������ʼλ��x
* @param lPosy ����������ʼλ��y
* @param lWidth ����������
* @param lHeight ��������߶�
* @param nFlag �ж���ʾ��ʽ��ֱ�߻����ߣ�
*/
void IDisplay::DrawLegend(ISymbol* pSymbol,long lPosx,long lPosy,long lWidth,long lHeight, int nFlag)
{
	DIS_RECT  rect;
	rect.left = lPosx;
	rect.top = lPosy;
	rect.right = lPosx + lWidth;
	rect.bottom = lPosy + lHeight;

	DrawLegend(pSymbol,&rect,nFlag);
}

/**
* ƫ����Ļ����
* @param offset_x ƫ��λ��X
* @param offset_y ƫ��λ��Y
*/
void IDisplay::OffsetScreen(long offset_x,long offset_y)
{

}

/**
* ���ñ���ɫ
* @param color ��ɫֵ
*/
void IDisplay::SetBgColor( COLORREF color)
{
	m_BgColor = color;
}

/**
* �����ɫֵ
* @return ������ɫֵ
*/
COLORREF IDisplay::GetBgColor()
{
	return m_BgColor;
}

/**
* ���Ʊ���
*/
void IDisplay::DrawBackgroud()
{
	if( CheckNoColor(m_BgColor) != 0xff )
	{
		HDC hDC = (HDC)m_pDC->GetSafeHdc();
		HBRUSH hbrush = ::CreateSolidBrush( m_BgColor );
		RECT rc = m_cDisplayTransformation.GetViewBound().GetRect();

		::FillRect( (HDC)hDC , &rc , hbrush );
		::DeleteObject( hbrush );
	}
}


void IDisplay::SetDC(long hDC, long lWidth, long lHeight )
{
	//OTBEGIN
		if(hDC == NULL)
			m_pDC->CreateExDC( lWidth , lHeight );
		else
			m_pDC->SetDC( hDC , lWidth , lHeight );
	m_cDisplayTransformation.SetViewBound(0, lWidth, 0, lHeight);

	////OTEND_NORET
}

/**
* ��û���DC
* @return ����óɹ�����CDC
*/
Display::CDC* IDisplay::GetDrawDC()
{
	return m_pDC;
}



BOOL IDisplay::SetSymbol(Display::ISymbol* pSymbol)
{
	//OTBEGIN
		if( bDraw )
			//OTFALSERETURN(FALSE,"Υ���˵��ù��򣺲�������BEGINE-END�ķ�Χ�е���");

	if(pSymbol == NULL || m_pDC->GetSafeHdc() == NULL )
		//OTFALSERETURN2(FALSE,"Symbol == %ld || m_pDC.hDC == %ld", pSymbol, m_pDC->GetSafeHdc() );


	//�Է��Ž�������
	if(m_bLayoutDis)
	{
		float fScale =  1/m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			if( pSymbol != NULL )
				pSymbol->Zoom( fScale );		
			//������2008.1.25Ϊ��ӡ���ű�����ΪΨһֵר����ȷ��ʾ�����޸�
		}
	}
	else if(m_cDisplayTransformation.GetReferenceScale() != 0)
	{
		float fScale =  m_cDisplayTransformation.GetReferenceScale()/m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			if( pSymbol != NULL)
				pSymbol->Zoom( fScale );	
		}
	}
	
	m_pSymbol = pSymbol;
	m_pSymbol->SelectDC( m_pDC );


	m_stackpSymbol.push_back(m_pSymbol);

	//OTEND(TRUE,FALSE)
		return TRUE;
}


int IDisplay::SetSymbolInStack(ISymbol* pSymbol)
{
	if(pSymbol == NULL || m_pDC->GetSafeHdc() == NULL )
		//OTFALSERETURN(FALSE,"Symbol or DC is Null" );

	//�Է��Ž�������
	if(m_bLayoutDis)
	{
		float fScale =  1/m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			if( pSymbol != NULL )
				pSymbol->Zoom( fScale );		
			//������2008.1.25Ϊ��ӡ���ű�����ΪΨһֵר����ȷ��ʾ�����޸�
		}
	}
	else if(m_cDisplayTransformation.GetReferenceScale() != 0)
	{
		float fScale =  m_cDisplayTransformation.GetReferenceScale()/m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			if( pSymbol != NULL)
				pSymbol->Zoom( fScale );	
		}
	}

	pSymbol->SelectDC( m_pDC ); // ����з���BOOL������GDIHANDLE�ﵽ���������

	m_stackpSymbol.push_back( pSymbol );

	return m_stackpSymbol.size()-1;
}

BOOL IDisplay::Begin()
{
	//OTBEGIN
		if( m_pDC->GetSafeHdc() == NULL )
			//OTFALSERETURN1(FALSE,"NOTREADY: m_pDC.hDC == %ld", m_pDC->GetSafeHdc() );

	////////////////////
	OnBeginDraw( m_pDC->GetSafeHdc() );

	m_pDC->BeginDisplay();

	if( m_pSymbol != NULL )
		m_pSymbol->SetReadyDraw();

	bDraw = TRUE;

	return bDraw;
	//IRasterSymbolPtr pRsSym = m_pSymbol;
	//if( pRsSym != NULL )
	//	pRsSym->BeginDrawRaster();

	//OTEND(TRUE,FALSE)
}

void IDisplay::End()
{
	/*IRasterSymbolPtr pRsSym = m_pSymbol;
	if( pRsSym != NULL )
		pRsSym->FinishDrawRaster();*/

	if(m_bLayoutDis)
	{
		float fScale =  m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			/*if( m_pSymbol != NULL )
				m_pSymbol->Zoom( fScale );	*/	
			//������2008.1.25Ϊ��ӡ���ű�����ΪΨһֵר����ȷ��ʾ�����޸�
			for( int i = 0 ;i < m_stackpSymbol.size();i++ )
			{
				if(m_stackpSymbol[i] != NULL )
					m_stackpSymbol[i]->Zoom( fScale );
			}
		}
	}
	else if(m_cDisplayTransformation.GetReferenceScale() != 0)
	{
		float fScale =  m_cDisplayTransformation.GetMapScale()/m_cDisplayTransformation.GetReferenceScale();
		if (fScale != 1.000000)
		{
			/*if( m_pSymbol != NULL )
				m_pSymbol->Zoom( fScale );		*/
			//������2008.1.25Ϊ��ӡ���ű�����ΪΨһֵר����ȷ��ʾ�����޸�
			for( int i = 0 ;i < m_stackpSymbol.size();i++ )
			{
				if(m_stackpSymbol[i] != NULL )
					m_stackpSymbol[i]->Zoom( fScale );
			}
		}
	}

	//m_cDisplayTransformation.GetViewPosition().m_PrintScale = 1.0;
	if( m_pSymbol != NULL )
		m_pSymbol->ClearDC();

	m_pSymbol = NULL;

	m_pDC->EndDisplay();

	bDraw = FALSE;
	for (int i = 0 ; i < m_stackpSymbol.size() ; i++ )
	{
		m_stackpSymbol[i]->ClearDC();
	}
	m_stackpSymbol.clear();

	OnEndDraw( m_pDC->GetSafeHdc() );
}

void IDisplay::Draw(const GEOMETRY::geom::Geometry* pGeometry)
{
	void *p = NULL;
	if( pGeometry == NULL )
		return;

	//ʸ���и�
	BOOL bNewGeo = FALSE;
	GEOMETRY::geom::Geometry *pDrawGeometry = NULL;	
	if(m_bPrint)
	{
		GEOMETRY::geom::GeometryTypeId typeId = pGeometry->getGeometryTypeId();
		if(typeId != GEOM_CIRCLE && typeId != GEOM_ELLIPSE && typeId != GEOM_BEZIERSPLINE)
		{
			RECT rect; 
			DIS_RECT disrect;
			GEOMETRY::geom::Envelope viewEnv;
			GEOMETRY::geom::Geometry* pViewGeo = NULL;

			rect = m_cDisplayTransformation.GetViewBound().GetRect();
			disrect.left = rect.left;
			disrect.right = rect.right;
			disrect.top = rect.top;
			disrect.bottom = rect.bottom;
			m_cDisplayTransformation.TransformToGeo(disrect, &viewEnv);
			pViewGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&viewEnv);
			if(!pViewGeo->intersects(pGeometry))
				return;

			pDrawGeometry = pViewGeo->intersection(pGeometry);	
			bNewGeo = TRUE;
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pViewGeo);
		}
		else
		{
			pDrawGeometry =  (GEOMETRY::geom::Geometry*)pGeometry;
		}
	}
	else
	{
		pDrawGeometry =  (GEOMETRY::geom::Geometry*)pGeometry;
	}


	//������ʾͼ��
	GEOMETRY::geom::GeometryTypeId GTypeID = pDrawGeometry->getGeometryTypeId();
	if(GTypeID == GEOMETRY::geom::GEOS_POINT)
	{
		GEOMETRY::geom::Point* pPoint= (GEOMETRY::geom::Point*)pDrawGeometry;
		p = (void*)m_cDisplayTransformation.TransformToDisplay( pPoint );
	}
	else if(GTypeID == GEOMETRY::geom::GEOS_LINESTRING|| GTypeID == GEOMETRY::geom::GEOS_LINEARRING)
	{
		GEOMETRY::geom::LineString* pLine = (GEOMETRY::geom::LineString*)pDrawGeometry;
		p = (void*)m_cDisplayTransformation.TransformToDisplay( pLine );
	}
	else if(GTypeID == GEOMETRY::geom::GEOS_POLYGON)
	{
		GEOMETRY::geom::Polygon* pPoly = (GEOMETRY::geom::Polygon*)pDrawGeometry;
		p = (void*)m_cDisplayTransformation.TransformToDisplay( pPoly );
	}
	else if(GTypeID ==GEOMETRY::geom::GEOM_CIRCLE)
	{
		GEOMETRY::geom::Circle *pc =(GEOMETRY::geom::Circle*)pDrawGeometry;
		p =(void*)m_cDisplayTransformation.TransformToDisplay(pc);	
	}
	else if(GTypeID ==GEOMETRY::geom::GEOM_ELLIPSE)
	{
		GEOMETRY::geom::Ellipse *pe =(GEOMETRY::geom::Ellipse*)pDrawGeometry;
		p =(void*)m_cDisplayTransformation.TransformToDisplay(pe);
	}
	else if(GTypeID == GEOMETRY::geom::GEOM_BEZIERSPLINE)
	{
		GEOMETRY::geom::BezierSpline *pb =(GEOMETRY::geom::BezierSpline*)pDrawGeometry;
		p =(void*)m_cDisplayTransformation.TransformToDisplay(pb);
	}
	else if(GTypeID == GEOMETRY::geom::GEOS_MULTIPOINT
		|| GTypeID == GEOMETRY::geom::GEOS_MULTILINESTRING || 
		GTypeID == GEOMETRY::geom::GEOS_MULTIPOLYGON )
	{
		GEOMETRY::geom::GeometryCollection *pGeoCol = (GEOMETRY::geom::GeometryCollection*)pDrawGeometry;
		for(int i = 0 ; i < pGeoCol->getNumGeometries() ; i++ )
			IDisplay::Draw( pGeoCol->getGeometryN(i) );

		return;
	}

	if(m_bPrint)
	{
		//����DC�иΧ
		RECT rect = m_cDisplayTransformation.GetViewBound().GetRect();
		DIS_RECT rc;
		rc.left = rect.left;
		rc.right = rect.right;
		rc.top = rect.top;
		rc.bottom = rect.bottom;
		m_pDC->SelectPrintClipRgn(&rc);
	}
	
	//����
	if(m_pSymbol != NULL && p)
		m_pSymbol->Draw( p );
	else
		//OTTRACE("Symbol is NULL in IDisplay Draw");

	////�ͷŻ��ƶ���
	if(p)
	{
        FreeDisplayObj(p);
	}

	if(m_bPrint)
	{
		//DC�ָ������ڷ�Χ
		m_pDC->SelectPrintClipRgn(NULL);
	}

	if(bNewGeo)
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pDrawGeometry);
}

/**
* ����
* @param pEnvelope ����
*/
void IDisplay::Draw(const GEOMETRY::geom::Envelope* pEnvelope)
{
	void *p = NULL;
	p = (void*)m_cDisplayTransformation.TransformToDisplay( pEnvelope);
	if(m_pSymbol != NULL)
		m_pSymbol->Draw( p);
	else
		//OTTRACE("Symbol is NULL in IDisplay Draw");

	FreeDisplayObj(p);
}
DIS_RECT IDisplay::Draw(const GEOMETRY::geom::Envelope* pEnvelope,  const std::string strText, BOOL bScaleWithMap, unsigned int dwDTFormat)
{
	//DIS_TEXT* pTextObj = m_cDisplayTransformation.TransformToDisplay( pEnvelope, strText );
	//CTextSymbol* pTextSymbol = (CTextSymbol*)m_pSymbol; 

	//
	//if(pTextSymbol != NULL)
	//{
	//	pTextSymbol->SetDrawFormat(dwDTFormat);
	//	pTextSymbol->Draw( pTextObj);
	//
	//	DIS_RECT rect = pTextObj->textPos;
	//	FreeDisplayObj(pTextObj);

	//	return rect;
	//}
	//else
	//{
	//	//OTTRACE("Symbol is NULL in IDisplay Draw");
	//}


	//if(pTextObj)
	//{
	//	FreeDisplayObj(pTextObj);
	//}
	DIS_RECT rectDis;
	return rectDis;
}

DIS_RECT IDisplay::Draw(const DIS_RECT* rect,  const std::string strText, BOOL bScaleWithMap, unsigned int dwDTFormat)
{
	//CTextSymbol* pTextSymbol = (CTextSymbol*)m_pSymbol; 

	//DIS_TEXT* pTextObj = NULL;
	//CreateDisplayText(pTextObj, strText.size());
	//pTextObj->textPos = *rect;
	//strcpy(pTextObj->cText, strText.c_str());

	//if(pTextSymbol != NULL)
	//{
	//	pTextSymbol->SetDrawFormat(dwDTFormat);
	//	pTextSymbol->Draw( pTextObj);

	//	DIS_RECT rect = pTextObj->textPos;
	//	FreeDisplayObj(pTextObj);
	//	return rect;
	//}
	//else
	//{
	//	//OTTRACE("Symbol is NULL in IDisplay Draw");
	//}

	//if(pTextObj)
	//{
	//	FreeDisplayObj(pTextObj);
	//}
	DIS_RECT rectDis;
	return rectDis;
}

void IDisplay::Draw(void* pObject)
{
	if(m_pSymbol != NULL)
		m_pSymbol->Draw( pObject );
}



BOOL IDisplay::SelectStackSymbol(int index)
{
	if( index > m_stackpSymbol.size() - 1 )
		//OTFALSERETURN(FALSE,"index is out of range");

	m_pSymbol = m_stackpSymbol[index];

	m_pSymbol->SetReadyDraw();

	return TRUE;
}

void IDisplay::OnBeginDraw( long hDC )
{

}

void IDisplay::OnEndDraw( long hDC )
{

}

//���û��ƻ�����
void IDisplay::SetDrawBuffer(DRAW_CONTENT content)
{
	if(m_bPrint)
		return;
	m_pDC->SelectBitmap(content);
}

//ˢ����ʾ�ڴ�
void IDisplay::RefreshDisplay(long content)
{
	if(m_bPrint)
		return;
	m_pDC->BuildBitmap(content);
}

//����������ʾ�����С
void IDisplay::CacheBuffer(long lWidth, long lHeight)
{
	m_pDC->CacheBitmap(lWidth,lHeight);
}

void IDisplay::SetPrinting(BOOL bPrint)
{
	m_bPrint = bPrint;
}

void IDisplay::UpdateGeography()
{
    gCallbackUpdteGeography();
}

boost::signals::connection IDisplay::RegisterUpdateGeography(boost::function<void ()> fun)
{
    return gCallbackUpdteGeography.connect(fun);
}

}
