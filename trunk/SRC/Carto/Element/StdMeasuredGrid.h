//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/15
// ������  ��ͼҪ�ء�����׼��ͼ������  
//////////////////////////////////////////////////////////////////////


#ifndef CGROUND_COORD_STDMAPGRID_H
#define CGROUND_COORD_STDMAPGRID_H

#include "IMapGrid.h"

namespace Element{



class CARTO_DLL CStdMeasuredGrid :public IMapGrid
{
public:
	CStdMeasuredGrid ();
	CStdMeasuredGrid (CMapFrame* pMapFrame);
	~CStdMeasuredGrid (void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	void Draw(Display::IDisplayPtr pDisplay);

	IGridPtr Clone();

protected:
	void DrawGrid(Display::IDisplayPtr pDisplay);
	void DrawTick(Display::IDisplayPtr pDisplay);
	void DrawSubTick(Display::IDisplayPtr pDisplay);
	void DrawLabel(Display::IDisplayPtr pDisplay);
	void DrawBorder(Display::IDisplayPtr pDisplay);
	
	
	void CalcGridLines(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, double XOrigin, double YOrigin, 
		double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pLines);
	void CalcGridMarkers(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, double XOrigin, double YOrigin, 
		double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pMarkers);
	void CalLabels(Display::IDisplayPtr pDisplay, std::vector<stGridLabel>& vecVerticalLabel, std::vector<stGridLabel>& vecHorizontalLabel, 
		std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecVerLabels, std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecHorLabels,
		double labelOffset, Display::CTextSymbol* pVerticalTextSym,
		Display::CTextSymbol* pHorizontalTextSym, double tickSpacePage);
	
	void DrawNormal(Display::IDisplayPtr pDisplay);

	void RegulateOrigin(BOOL bDynamicXYOrg, double& XOrigin, double& YOrigin, double& XInterval, double& YInterval, GEOMETRY::geom::Envelope& Env);

	//����ͶӰ����
	std::string CaculateProjStrapNode();

public:
	bool GetProjStrapCodeVisible( void );
	void SetProjStrapCodeVisible( bool bVisible );

	bool GetHundredKmVisible( void );
	void SetHundredKmVisible( bool bVisible );

	bool GetKmVisible( void );
	void SetKmVisible( bool bVisible );

	Display::CTextSymbolPtr GetHundredLabelSymbol( void );
	void SetHundredLabelSymbol( Display::CTextSymbolPtr pTextSymbol );

	Display::CTextSymbolPtr GetProjLabelSymbol( void );
	void SetProjLabelSymbol( Display::CTextSymbolPtr pTextSymbol );

private:
	//��ʾ�Ƿ����ͼ������ͶӰ���ı��
	bool m_bIsDrawProjStrapCode;

	//��ʾ�Ƿ���ưٹ�����
	bool m_bIsDrawHundredKm;
	
	//��ʾ�Ƿ���Ƹ�ʮ������
	bool m_bIsDrawKm;
	
	//�ٹ������ֵķ���
	Display::CTextSymbolPtr m_pHundredLabelSymbol;

	//ͼ������ͶӰ���ı��
	Display::CTextSymbolPtr m_pProjStrapLabelSymbol;
	
	//�ٹ������ּ���
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerHundredKmLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorHundredKmLabels;
	
	//�ٹ������¹������ּ���	
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerKmLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorKmLabels;
};

typedef SYSTEM::CSmartPtr<CStdMeasuredGrid > CStdMeasuredGridPtr;
}
#endif
