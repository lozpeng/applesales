#include "StdAfx.h"
#include "DistrictRelationTable.h"
#include "TextSymbol.h"
#include "EnvelopeTracker.h"
//#include "UnitConverter.h"
#include "SymbolFactory.h"
#include "MapFrame.h"

#define  D_ZERO 0.00001

namespace Element{
	CDistrictRelationTable::CDistrictRelationTable()
	{
		m_pTableLineStyle = NULL;

		m_pTextSym = NULL;

		m_enumElementType = ET_RELATIONDISTRICT_TABLE;

		m_bCanSetWHRMode = FALSE;

		m_strName = "接边表";

		m_coordOrg.x = 0.0;
		m_coordOrg.y = 0.0;
		
		m_vColWidths.clear();
		m_vRowHeights.clear();
		m_vRelationDistrict.clear();
		
		m_vColWidths.push_back( 0.0 );
		m_vColWidths.push_back( 20.0 );
		m_vColWidths.push_back( 60.0 );
		m_vColWidths.push_back( 80.0 );

		m_vColWidths.push_back( 0.0 );
		m_vRowHeights.push_back( 15.0 );
		m_vRowHeights.push_back( 45.0 );
		m_vRowHeights.push_back( 60.0 );

		for ( int i = 0; i < 9; i++ )
		{
			std::pair<std::string, std::string> disRelationItem;
			disRelationItem.first = "XX";
			disRelationItem.second = "XX";
			m_vRelationDistrict.push_back( disRelationItem );
		}

		m_bIsResetGeometry = FALSE;
	}

	CDistrictRelationTable::CDistrictRelationTable(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame)
		:IMapSurround(geometry, pMapFrame)
	{
		m_pTableLineStyle = NULL;

		m_pTextSym = NULL;

		m_enumElementType = ET_RELATIONDISTRICT_TABLE;
		
		m_bCanSetWHRMode = FALSE;

		m_strName = "接边表";

		m_coordOrg.x = geometry.getEnvelopeInternal()->getMinX();
		m_coordOrg.y = geometry.getEnvelopeInternal()->getMinY();
		
		m_vColWidths.clear();
		m_vRowHeights.clear();
		m_vRelationDistrict.clear();

		m_vColWidths.push_back( 0.0 );
		m_vColWidths.push_back( 20.0 );
		m_vColWidths.push_back( 60.0 );
		m_vColWidths.push_back( 80.0 );

		m_vRowHeights.push_back( 0.0 );
		m_vRowHeights.push_back( 15.0 );
		m_vRowHeights.push_back( 45.0 );
		m_vRowHeights.push_back( 60.0 );

		for ( int i = 0; i < 9; i++ )
		{
			std::pair<std::string, std::string> disRelationItem;
			disRelationItem.first = "XX";
			disRelationItem.second = "XX";
			m_vRelationDistrict.push_back( disRelationItem );
		}

		m_bIsResetGeometry = FALSE;
	}


	CDistrictRelationTable::~CDistrictRelationTable(void)
	{
	}

	void CDistrictRelationTable::serialization(SYSTEM::IArchive &ar)
	{
		IMapSurround::serialization( ar );

		/**/
		if ( ar.IsRead() )
		{
			m_vRowHeights.clear();
			m_vColWidths.clear();
			m_vRelationDistrict.clear();

			long nRows;
			ar & nRows;
			for ( long i = 0; i < nRows; ++i )
			{
				double dHeight;
				ar & dHeight;
				m_vRowHeights.push_back( dHeight );
			}

			long nCols;
			ar & nCols;
			for ( long i = 0; i < nCols; ++i )
			{
				double dWidth;
				ar & dWidth;
				m_vColWidths.push_back( dWidth );
			}

			long nCells;
			ar & nCells;
			for ( long i = 0; i < nCells; ++i )
			{
				std::string szName;
				std::string szCode;
				std::pair<std::string, std::string> itemDisRelation;
				ar & szName;
				ar & szCode;
				itemDisRelation.first = szName;
				itemDisRelation.second = szCode;
				m_vRelationDistrict.push_back( itemDisRelation );
			}

			m_pTextSym = Display::CSymbolFactory::CreateSymbolFromStream( ar );
			
			m_pTableLineStyle = Display::CSymbolFactory::CreateSymbolFromStream( ar );
		}
		else
		{
			long nRows = m_vRowHeights.size();
			long nCols = m_vColWidths.size();
			long nCells = m_vRelationDistrict.size();
			
			ar & nRows;

			for ( long i = 0; i < nRows; ++i )
			{
				ar & m_vRowHeights[i];
			}

			ar & nCols;
			
			for ( long i = 0; i < nCols; ++i )
			{
				ar & m_vColWidths[i];
			}

			ar & nCells;
			
			for ( long i = 0; i < nCells; ++i )
			{
				ar & m_vRelationDistrict[i].first;
				ar & m_vRelationDistrict[i].second;
			}
			
			m_pTextSym->serialization( ar );

			m_pTableLineStyle->serialization( ar );
		}
		

		ar & m_coordOrg.x;

		ar & m_coordOrg.y;

		ar & m_bIsResetGeometry;
	}

	void CDistrictRelationTable::Move(double dx, double dy)
	{
		if(!m_pGeometry)
			return;

		m_pGeometry->Move(dx,dy);

		m_coordOrg.x += dx;
		m_coordOrg.y += dy;

		IFrameElementBase::GeometryChangedEvents();
	}

	void CDistrictRelationTable::DrawNormal(Display::IDisplayPtr pDisplay)
	{
		//重新计算geometry大小
		RecalcGeometry( pDisplay );

		//重新计算单元格的宽度和高度
		Scale( pDisplay );

		//绘制背景
		DrawBackground( pDisplay );

		//绘制表格线
		DrawTableLines( pDisplay );

		//绘制缩略图
		DrawBrevaryPic( pDisplay );

		//绘制接边表的内容
		DrawRelationDistrict( pDisplay );

		//绘制前景
		DrawForeground( pDisplay );
	}

	

	void CDistrictRelationTable::DrawTableLines( Display::IDisplayPtr pDisplay )
	{
		/*------------------计算表格中线的位置---------------------*/
		double dWidth = m_vColWidths[m_vColWidths.size() - 1];
		double dHeight = m_vRowHeights[m_vRowHeights.size() -1 ];
		
		GEOMETRY::geom::Geometry  *pLines;
		pLines =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();

		GEOMETRY::geom::Geometry* pLine = NULL;
		GEOMETRY::geom::CoordinateSequence* coords = NULL;
		GEOMETRY::geom::Coordinate coordStart, coordEnd;

		//竖线
		for ( int i = 0; i < m_vColWidths.size(); ++i )
		{
			coordStart.x = m_coordOrg.x + MillimeterToGeo( pDisplay, m_vColWidths[i] );
			coordStart.y = m_coordOrg.y;
			coordEnd.x = m_coordOrg.x + MillimeterToGeo( pDisplay, m_vColWidths[i] );
			coordEnd.y = m_coordOrg.y + MillimeterToGeo( pDisplay, dHeight );
 
			coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
			coords->add(coordStart);
			coords->add(coordEnd);

			pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
			((MultiLineString*)pLines)->AddGeometry(pLine);
		}

		//横线
		for ( int i = 0; i < m_vColWidths.size(); ++i )
		{
			coordStart.x = m_coordOrg.x;
			coordStart.y = m_coordOrg.y + MillimeterToGeo( pDisplay, m_vRowHeights[i] );
			coordEnd.x = m_coordOrg.x + MillimeterToGeo( pDisplay, dWidth );
			coordEnd.y = m_coordOrg.y + MillimeterToGeo( pDisplay, m_vRowHeights[i] );

			coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
			coords->add(coordStart);
			coords->add(coordEnd);

			pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
			((MultiLineString*)pLines)->AddGeometry(pLine);
		}
		
		/*----------------------绘制表格线-------------------------*/
		if ( !m_pTableLineStyle )
			m_pTableLineStyle.reset( new Display::CSimpleLineSymbol );
		
		pDisplay->SetSymbol( m_pTableLineStyle.get() );

		pDisplay->Begin();

		pDisplay->Draw( pLines );

		pDisplay->End();

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry( pLines );
	}

	void CDistrictRelationTable::DrawRelationDistrict( Display::IDisplayPtr pDisplay )
	{
		if ( !m_pTextSym )
		{
			m_pTextSym.reset( new Display::CTextSymbol);
		}
		
		for ( int i = 1; i < m_vRowHeights.size(); ++i )
		{
			for ( int j = 1; j < m_vColWidths.size(); ++j)
			{
				
				//中心单元格的不绘 用来显示缩略图
				if ( i == 2 && j == 2)
					continue;

				DIS_RECT rectDisNameSize;
				DIS_RECT rectDisCodeSize;
				
				std::string szDisName = m_vRelationDistrict[3*(i-1) + (j-1)].first;
				std::string szDisCode = m_vRelationDistrict[3*(i-1) + (j-1)].second;

				GEOMETRY::geom::Coordinate coord;
				coord.x = m_coordOrg.x + MillimeterToGeo( pDisplay, (m_vColWidths[j] - m_vColWidths[j-1])/2 + m_vColWidths[j-1] );
				coord.y = m_coordOrg.y + MillimeterToGeo( pDisplay, (m_vRowHeights[i] - m_vRowHeights[i-1])/2 + m_vRowHeights[i-1] );
				
				//计算位置与大小
				rectDisNameSize.left = 0;
				rectDisNameSize.right = 1;
				rectDisNameSize.top = 0;
				rectDisNameSize.bottom = 1;
				rectDisCodeSize.left = 0;
				rectDisCodeSize.right = 1;
				rectDisCodeSize.top = 0;
				rectDisCodeSize.bottom = 1;
				
				pDisplay->SetSymbol( m_pTextSym.get() );
				pDisplay->Begin();
				rectDisNameSize = pDisplay->Draw( &rectDisNameSize, szDisName, TRUE, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP );
				rectDisCodeSize = pDisplay->Draw( &rectDisCodeSize, szDisCode, TRUE, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP );
				pDisplay->End();
				
				
				GEOMETRY::geom::Envelope envDisName;
				GEOMETRY::geom::Envelope envDisCode;
				envDisName.init( coord.x,
					coord.x,
					coord.y + pDisplay->GetDisplayTransformation().TransformToGeo( rectDisNameSize.Height()/2 ),
					coord.y + pDisplay->GetDisplayTransformation().TransformToGeo( rectDisNameSize.Height()/2 ) );
				envDisCode.init( coord.x,
					coord.x,
					coord.y - pDisplay->GetDisplayTransformation().TransformToGeo( rectDisCodeSize.Height()/2 ),
					coord.y - pDisplay->GetDisplayTransformation().TransformToGeo( rectDisCodeSize.Height()/2 ) );

				pDisplay->SetSymbol( m_pTextSym.get() );
				pDisplay->Begin();
				pDisplay->Draw( &envDisName, szDisName, TRUE );
				pDisplay->Draw( &envDisCode, szDisCode, TRUE );
				pDisplay->End();
			}
		}
	}

	void CDistrictRelationTable::DrawBrevaryPic( Display::IDisplayPtr pDisplay )
	{
		if ( !m_pMapFrame)
			return;

		GEOMETRY::geom::Envelope env;
		env.init( m_coordOrg.x + MillimeterToGeo( pDisplay, m_vColWidths[1] ),
			m_coordOrg.x + MillimeterToGeo( pDisplay, m_vColWidths[2] ),
			m_coordOrg.y + MillimeterToGeo( pDisplay, m_vRowHeights[1] ),
			m_coordOrg.y + MillimeterToGeo( pDisplay, m_vRowHeights[2] ) );

		DIS_RECT *pRect = pDisplay->GetDisplayTransformation().TransformToDisplay( &env );
		StretchBlt((HDC)pDisplay->GetDrawDC()->GetSafeHdc(),
			pRect->left + 2 ,
			pRect->top + 2, 
			pRect->Width() - 4, 
			pRect->Height() - 4,
			(HDC)(m_pMapFrame->GetMap()->GetDisplay()->GetDrawDC()->GetSafeHdc()),
			0, 
			0,
			m_pMapFrame->GetMap()->GetDisplay()->GetDrawDC()->GetDCWidth(),
			m_pMapFrame->GetMap()->GetDisplay()->GetDrawDC()->GetDCHeight(),
			SRCCOPY);

		FreeDisplayObj( pRect );
	}

	double CDistrictRelationTable::MillimeterToGeo( Display::IDisplayPtr pDisplay, double dmil )
	{
		double dGeo = SYSTEM::UnitConverter::ConvertUnits( dmil, SYSTEM::SYS_UNIT_MILLIMETER, pDisplay->GetDisplayTransformation().GetUnit() );
		
		return dGeo;
	}

	void CDistrictRelationTable::RecalcGeometry(Display::IDisplayPtr pDisplay)
	{
		//初始化m_pSelectionHandle
		double dWidth = m_vColWidths[m_vColWidths.size() - 1];
		double dHeight = m_vRowHeights[m_vRowHeights.size() -1 ];
		GEOMETRY::geom::Envelope newEnv;
		newEnv.init( m_coordOrg.x,
			m_coordOrg.x + MillimeterToGeo( pDisplay, dWidth ),
			m_coordOrg.y,
			m_coordOrg.y + MillimeterToGeo( pDisplay, dHeight ) );
		if ( !m_pSelectionHandle || m_bIsResetGeometry )
		{
			m_pSelectionHandle.reset( new CEnvelopeTracker( newEnv, HT_FOUR ) );
			m_bIsResetGeometry = false;
		}

		GEOMETRY::geom::Envelope trackEnv = m_pSelectionHandle->GetEnvelope();
		
		m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry( &trackEnv );

		GeometryChangedEvents();
	}

	void CDistrictRelationTable::Scale( Display::IDisplayPtr pDisplay )
	{
		GEOMETRY::geom::Envelope trackEnv = m_pSelectionHandle->GetEnvelope();
		if ( trackEnv.getWidth() <  D_ZERO || trackEnv.getHeight() < D_ZERO )
			return;

		double dWidth = MillimeterToGeo( pDisplay, m_vColWidths[m_vColWidths.size() - 1] );
		double dHeight = MillimeterToGeo( pDisplay, m_vRowHeights[m_vRowHeights.size() -1 ] );

		double dHradio = trackEnv.getWidth() / dWidth;
		double dVradio = trackEnv.getHeight() / dHeight;

		//调整左下角点位置
		m_coordOrg.x = trackEnv.getMinX();
		m_coordOrg.y = trackEnv.getMinY();

		//调整水平单元格宽度
		for ( int i = 0; i < m_vColWidths.size(); ++i )
			m_vColWidths[i] = m_vColWidths[i] * dHradio;
		
		//调整垂直单元格高度
		for ( int i = 0; i < m_vRowHeights.size(); ++i )
			m_vRowHeights[i] = m_vRowHeights[i] * dVradio;
	}

	void CDistrictRelationTable::SetRelationDistricts( const std::vector<std::pair<std::string, std::string>> &vRelationDistrict )
	{
		m_vRelationDistrict.clear();

		for( int i = 0; i < vRelationDistrict.size(); ++i )
		{
			m_vRelationDistrict.push_back( vRelationDistrict[i] );
		}
	}
	
	void CDistrictRelationTable::GetRelationDistricts( std::vector<std::pair<std::string, std::string>> &vRelationDistrict )
	{
		vRelationDistrict.clear();

		for( int i = 0; i < m_vRelationDistrict.size(); ++i )
		{
			vRelationDistrict.push_back( m_vRelationDistrict[i] );
		}
	}

	void CDistrictRelationTable::SetColWidths( const std::vector<double> &vColWidths )
	{
		m_vColWidths.clear();

		for ( int i = 0; i < vColWidths.size(); ++i )
			m_vColWidths.push_back( vColWidths[i] );
	}

	void CDistrictRelationTable::GetColWidths( std::vector<double> &vColWidths )
	{	
		vColWidths.clear();

		for ( int i = 0; i < m_vColWidths.size(); ++i )
			vColWidths.push_back( m_vColWidths[i] );
	}

	void CDistrictRelationTable::SetRowHeights( const std::vector<double> &vRowHeights )
	{
		m_vRowHeights.clear();

		for ( int i = 0; i < vRowHeights.size(); ++i )
			m_vRowHeights.push_back( vRowHeights[i] );
	}

	void CDistrictRelationTable::GetRowHeights(  std::vector<double> &vRowHeights )
	{
		vRowHeights.clear();

		for ( int i = 0; i < m_vRowHeights.size(); ++i )
			vRowHeights.push_back( m_vRowHeights[i] );
	}

	void CDistrictRelationTable::SetOriginCoord( const GEOMETRY::geom::Coordinate &coordOrg )
	{
		m_coordOrg.x = coordOrg.x;
		m_coordOrg.y = coordOrg.y;
	}

	GEOMETRY::geom::Coordinate CDistrictRelationTable::GetOriginCoord( void )
	{
		return m_coordOrg;
	}

	void CDistrictRelationTable::SetLineSymbol( Display::ILineSymbolPtr pTableLineSymbol )
	{
		m_pTableLineStyle = pTableLineSymbol;
	}

	Display::ILineSymbolPtr CDistrictRelationTable::GetLineSymbol( void )
	{
		return m_pTableLineStyle;
	}

	void CDistrictRelationTable::SetTextSymbol( Display::CTextSymbolPtr pTextSymbol )
	{
		m_pTextSym =  pTextSymbol;
	}

	Display::CTextSymbolPtr CDistrictRelationTable::GetTextSymbol( void )
	{
		return m_pTextSym;
	}
	
	void CDistrictRelationTable::ResetGeometry( bool bIsReset  )
	{
		m_bIsResetGeometry = bIsReset;
	}
}
