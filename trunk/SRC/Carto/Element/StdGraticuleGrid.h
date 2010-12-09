//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/15
// ������  ��ͼҪ�ء�����׼��ͼ��γ��  
//////////////////////////////////////////////////////////////////////

#ifndef CGROUND_COORD_STDGRATICULEGRID_H
#define CGROUND_COORD_STDGRATICULEGRID_H

#include "IMapGrid.h"
#include "GraticuleGrid.h"

namespace Element{
	

class CARTO_DLL CStdGraticuleGrid :public IMapGrid
{
public:
	CStdGraticuleGrid ();

	CStdGraticuleGrid (CMapFrame* pMapFrame);

	~CStdGraticuleGrid (void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	void Draw(Display::IDisplayPtr pDisplay);

	IGridPtr Clone();

protected:
	void DrawGrid(Display::IDisplayPtr pDisplay);

	void DrawTick(Display::IDisplayPtr pDisplay);

	void DrawSubTick(Display::IDisplayPtr pDisplay);

	void DrawLabel(Display::IDisplayPtr pDisplay);

	void DrawBorder(Display::IDisplayPtr pDisplay);
	
	
	void CalcGridLines(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, double YOrigin, 
		double dXDistanceToBorder, double dYDistanceToBorder, GEOMETRY::geom::Geometry*& pLines);
	
	void CalcGridMarkers(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, double YOrigin, 
		double dXDistanceToBorder, double dYDistanceToBorder, GEOMETRY::geom::Geometry*& pMarkers);
	
	void CalLabels(Display::IDisplayPtr pDisplay, 
		std::vector<stGridLabel>& vecVerticalLabel, 
		std::vector<stGridLabel>& vecHorizontalLabel, 
		Display::CTextSymbol* pVerticalTextSym,
		Display::CTextSymbol* pHorizontalTextSym, 
		double tickSpacePage,
		double labelOffset);

	void DrawNormal(Display::IDisplayPtr pDisplay);

	void RegulateOrigin(BOOL bDynamicXYOrg, double& XOrigin, double& YOrigin, double& XInterval, double& YInterval, GEOMETRY::geom::Envelope& Env);

	//����ͶӰ����
	std::string CaculateProjStrapNode();

	// ת����γ�ȵ���\��\��
	void TransformToGraticuleText(double graticule, std::vector<std::string> &vecDMS );

public:
	void SetGridLabelContent(int enumGridLabelContent);

	int  GetGridLabelContent();

	void SetXDistancetoBorder( long xDistance );
	long GetXDistancetoBorder( void );

	void SetYDistancetoBorder( long yDistance );
	long GetYDistancetoBorder( void );

private:
	GridLabelContent m_gridLabelContent;	

	//�������߽�ľ���
	long m_lXDistanceToBorder;
	long m_lYDistanceToBorder;
		
	//��ֱ����ľ���
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerDegreeLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerMinuteLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerSecondLabels;
	
	//ˮƽ�����γ��	
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorDegreeLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorMinuteLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorSecondLabels;
};

typedef SYSTEM::CSmartPtr<CStdGraticuleGrid > CStdGraticuleGridPtr;
}
#endif
