// IW_DrawGraphObj.h - interface for CiwDrawGraphObj
//

#ifndef __DICTRICTRELATION_TABLE_H__
#define __DICTRICTRELATION_TABLE_H__

#include "IMapSurround.h"

/////////////////////////////////////////////////////////////////////////////
// CDrawRectangleObj - �򵥴�ӡ����
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


	//��������
	void DrawTableLines( Display::IDisplayPtr pDisplay );

	//���������������ĵ����ͷַ���
	void DrawRelationDistrict( Display::IDisplayPtr pDisplay );

	//������е�����ͼ
	void DrawBrevaryPic( Display::IDisplayPtr pDisplay );

	
	void Move(double dx, double dy);

	//���µ���Geometry�Ĵ�С
	void RecalcGeometry(Display::IDisplayPtr pDisplay);

	//���ű���С
	void Scale( Display::IDisplayPtr pDisplay );

public:
	// ���ýӱ߱������
	void SetRelationDistricts( const std::vector<std::pair<std::string, std::string>> &vRelationDistrict );
	
	//��ýӱ߱������
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

	//����ת��Ϊ��������
	double MillimeterToGeo( Display::IDisplayPtr pDispaly, double dmil );

	//����Geometry
	void ResetGeometry( bool bIsReset = true );
private:
	//����и��и��еĿ�Ⱥ͸߶�
	std::vector<double> m_vColWidths;
	std::vector<double> m_vRowHeights;

	//����и���Ԫ���е�����
	std::vector<std::pair<std::string, std::string>> m_vRelationDistrict;

	//������½ǵ�
	GEOMETRY::geom::Coordinate m_coordOrg;

	//����ʽ
	Display::ILineSymbolPtr m_pTableLineStyle;
	//������ʽ
	Display::CTextSymbolPtr m_pTextSym;

	//�Ƿ�����Geometry
	bool m_bIsResetGeometry;
};

typedef SYSTEM::CSmartPtr<CDistrictRelationTable> CDistrictRelationTablePtr;
}

#endif // __DICTRICTRELATION_TABLE_H__
