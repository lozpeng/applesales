// IW_DrawGraphObj.h - interface for CiwDrawGraphObj
//

#ifndef __DICTRICTRELATION_TABLE_H__
#define __DICTRICTRELATION_TABLE_H__

#include "IMapSurround.h"

/////////////////////////////////////////////////////////////////////////////
// CDrawRectangleObj - 简单打印对象
namespace Carto
{
	class CMap;
}

namespace Element{

class CARTO_DLL CDistrictRelationTable : public IMapSurround
{
public:
	CDistrictRelationTable();

	CDistrictRelationTable(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);

	~CDistrictRelationTable( void );
		
	virtual void serialization(SYSTEM::IArchive &ar); 

	// Implementation
protected:
	virtual void DrawNormal(Display::IDisplayPtr pDisplay);


	//画表格的线
	void DrawTableLines( Display::IDisplayPtr pDisplay );

	//画表格中相邻区域的地名和分幅号
	void DrawRelationDistrict( Display::IDisplayPtr pDisplay );

	//画表格中的缩略图
	void DrawBrevaryPic( Display::IDisplayPtr pDisplay );

	
	void Move(double dx, double dy);

	//重新调整Geometry的大小
	void RecalcGeometry(Display::IDisplayPtr pDisplay);

	//缩放表格大小
	void Scale( Display::IDisplayPtr pDisplay );

public:
	// 设置接边表的内容
	void SetRelationDistricts( const std::vector<std::pair<std::string, std::string>> &vRelationDistrict );
	
	//获得接边表的内容
	void GetRelationDistricts( std::vector<std::pair<std::string, std::string>> &vRelationDistrict );
	
	void SetOriginCoord( const GEOMETRY::geom::Coordinate &m_coordOrg );
	GEOMETRY::geom::Coordinate GetOriginCoord( void );

	void SetColWidths( const std::vector<double> &vColWidths );
	void GetColWidths( std::vector<double> &vColWidths );

	void SetRowHeights( const std::vector<double> &vRowHeights );
	void GetRowHeights(  std::vector<double> &vRowHeights );

	void SetLineSymbol( Display::ILineSymbolPtr pTableLineSymbol );
	Display::ILineSymbolPtr GetLineSymbol( void );

	void SetTextSymbol( Display::CTextSymbolPtr pTextSymbol );
	Display::CTextSymbolPtr GetTextSymbol( void );

	//毫米转换为地理坐标
	double MillimeterToGeo( Display::IDisplayPtr pDispaly, double dmil );

	//重置Geometry
	void ResetGeometry( bool bIsReset = true );
private:
	//表格中各列各行的宽度和高度
	std::vector<double> m_vColWidths;
	std::vector<double> m_vRowHeights;

	//表格中各单元格中的内容
	std::vector<std::pair<std::string, std::string>> m_vRelationDistrict;

	//表格左下角点
	GEOMETRY::geom::Coordinate m_coordOrg;

	//线样式
	Display::ILineSymbolPtr m_pTableLineStyle;
	//文字样式
	Display::CTextSymbolPtr m_pTextSym;

	//是否重设Geometry
	bool m_bIsResetGeometry;
};

typedef SYSTEM::CSmartPtr<CDistrictRelationTable> CDistrictRelationTablePtr;
}

#endif // __DICTRICTRELATION_TABLE_H__
