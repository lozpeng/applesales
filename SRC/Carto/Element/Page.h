//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/10
// ������  ��ͼҪ�ء�����ͼҳ
//////////////////////////////////////////////////////////////////////
#ifndef _CARTO_ELEMENT_PAGE_H
#define _CARTO_ELEMENT_PAGE_H
#include "IFrameProperty.h"
#include "IDisplay.h"
#include "PageGrid.h"

namespace Element{

class CARTO_DLL CPage : public IFrameProperty, public SYSTEM::ISerialization
{
public:
	CPage(void);
	CPage(int nPrintPageNumX, int nPagePrintNumY, double dbOnePrintPageWidth, double dbOnePrintPageHeight);
	~CPage(void);

	virtual void serialization(SYSTEM::IArchive& ar);

	SYSTEM::CSmartPtr<CPage> Clone();

	void SetPageEnvelope(GEOMETRY::geom::Envelope& PageEnvelope);	
	const GEOMETRY::geom::Envelope& GetPageEnvelope();
	
	const GEOMETRY::geom::Envelope& GetPageMarginEnvelope();

	void Draw( Display::IDisplayPtr pDisplay , bool bPrint = false);

	/**
	* ��õ�ͼ�ĵ�λ
	* @return ��ͼ�ĵ�λ
	*/
	void SetUnit(SYSTEM::SYS_UNIT_TYPE unit);
	SYSTEM::SYS_UNIT_TYPE GetUnit(){return m_unit;};

	void SetDrawPageGrid(BOOL bDraw);
	BOOL GetDrawPageGrid();

	void SetPageGridIntervalX(double x);
	double GetPageGridIntervalX();

	void SetPageGridIntervalY(double y);
	double GetPageGridIntervalY();

	void SetDrawPageDiv(BOOL bDraw);
	BOOL GetDrawPageDiv();

	void SetPrintPageNumX(int nNum);
	int GetPrintPageNumX();

	void SetPrintPageNumY(int nNum);
	int GetPrintPageNumY();

	/*void SetOnePrintPageWidth(double dbWidth);
	double GetOnePrintPageWidth();*/

	/*void SetOnePrintPageHeight(double dbHeight);
	double GetOnePrintPageHeight();*/


	CPageGridPtr GetGrid();

	PAGE_INFO GetPageInfo(){return m_pageInfo;}

	void SetPageInfo(PAGE_INFO pageInfo);


protected:
	void PageSizeChangedEvents();
	void Init( );

protected:
	//ֽ�ŵĵ�λ
	SYSTEM::SYS_UNIT_TYPE m_unit;
	//Page�ĳߴ�
	int				m_nPrintPageNumX;
	int				m_nPrintPageNumY;

	double			m_dbOnePrintPageWidth;//mm
	double			m_dbOnePrintPageHeight;//mm

	GEOMETRY::geom::Envelope m_PageEnvelope;

	//Page�ɴ�ӡ�ĳߴ�
	GEOMETRY::geom::Envelope m_PrintableEnvelope;
	//Page�����հ׵ĳߴ�
	GEOMETRY::geom::Envelope m_MarginEnvelope;
	//ֽ������ͼ����ı߽����
	double m_dbMargin;
	//ֽ�ŷ���0Ϊ��(landscape()��>=��)��1Ϊ����portrait:��<�ߣ�
	BOOL m_bOrientation;
	//��ӡ�����Ƿ�ɼ�
	BOOL m_bPrintAreaVisible;

	//����ͼ��
	GEOMETRY::geom::Geometry* m_pGeometry;

	//ֽ������
	CPageGridPtr	m_pPageGrid;

	//��ҳ��
	BOOL			m_bDrawPageDiv;

	PAGE_INFO		m_pageInfo;	
};

typedef SYSTEM::CSmartPtr<CPage> CPagePtr;
}
#endif

