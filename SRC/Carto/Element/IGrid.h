//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/10
// ������  ��ͼҪ�ء�������  ���������Ļ���
//////////////////////////////////////////////////////////////////////

#ifndef IGRID_H
#define IGRID_H
#include "SimpleBorder.h"
#include "ILineSymbol.h"
#include "TextSymbol.h"
#include "ISelectionTracker.h"

namespace Element{

	class CMapFrame;

	enum MapGridLineStyle
	{
		MGLS_LINE,
		MGLS_MARKER,
		MGLS_NONE
	};

	enum GridType
	{
		GT_GRATICULE_GRID,
		GT_MEASURED_GRID,
		GT_STANDARD_MAPPING_GRID,
		GT_STANDARD_GRATICULE_GRID
	};

	struct stGridLabel
	{
		BOOL bStartValid;

		BOOL bEndValid;

		GEOMETRY::geom::Coordinate geoCoordStart;

		GEOMETRY::geom::Coordinate geoCoordEnd;

		GEOMETRY::geom::Coordinate pageCoordStart;

		GEOMETRY::geom::Coordinate pageCoordEnd;

		stGridLabel(){bStartValid = TRUE;bEndValid = TRUE;};
	};

	static DIS_RECT CalculateTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbol* pTextSymbol, std::string text)
	{
		DIS_RECT textSize;
		textSize.left = 0; textSize.right = 1;
		textSize.top = 0; textSize.bottom = 1;

		pDisplay->SetSymbol(pTextSymbol);

		pDisplay->Begin();

		textSize = pDisplay->Draw(&textSize, text, TRUE, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

		pDisplay->End();

		return textSize;
	}

	class CARTO_DLL IGrid : public SYSTEM::ISerialization
	{
	public:
		IGrid();
		~IGrid(void);

		virtual void serialization(SYSTEM::IArchive &ar);  

		virtual SYSTEM::CSmartPtr<IGrid> Clone()=0;

		static SYSTEM::CSmartPtr<IGrid> CreateGridFromStream(SYSTEM::IArchive &ar);

		static SYSTEM::CSmartPtr<IGrid> CreateGrid( GridType type);


		void SetRecalcGrid();

		void SetGridActive(BOOL bActive);
		BOOL GetGridActive();

		void SetGridName(std::string name);
		std::string GetGridName();

		void SetGridVisibility(BOOL bVisible);
		BOOL GetGridVisibility();

		void SetGridLineSymbol(Display::ILineSymbolPtr pLineSymbol);
		Display::ILineSymbolPtr GetGridLineSymbol();

		void SetGridMarkerSymbol(Display::IMarkerSymbolPtr pGridMarkerSymbol);
		Display::IMarkerSymbolPtr GetGridMarkerSymbol();

		void SetUseDynamicXYOrigin(BOOL bDyn);
		BOOL GetUseDynamicXYOrigin();

		void SetXOrigin(double XOrg);
		double GetXOrigin();

		void SetYOrigin(double XOrg);
		double GetYOrigin();

		void SetXInterval(double XInter);
		double GetXInterval();

		void SetYInterval(double XInter);
		double GetYInterval();

		void SetBorderVisibility(BOOL bVisible);
		BOOL GetBorderVisibility();

		void SetBorderLineSymbol(Display::ILineSymbolPtr pLineSymbol);
		Display::ILineSymbolPtr GetBorderLineSymbol();

		void SetBorderExpandX(float x);
		float GetBorderExpandX();

		void SetBorderExpandY(float y);
		float GetBorderExpandY();

		void SetLabelVisibility(BOOL bVisible);
		BOOL GetLabelVisibility();

		void SetTickVisibility(BOOL bVisible);
		BOOL GetTickVisibility();

		void SetTickCount(int nCount);
		int GetTickCount();

		void SetTickLength(double dbLen);
		double GetTickLength();

		void SetTickOffset(double dbOffset);
		double GetTickOffset();

		void SetTickLineSymbol(Display::ILineSymbolPtr pLineSym);
		Display::ILineSymbolPtr GetTickLineSymbol();

		void SetSubTickVisibility(BOOL bVisible);
		BOOL GetSubTickVisibility();

		void SetSubTickCount(int nCount);
		int GetSubTickCount();

		void SetSubTickLength(double dbLen);
		double GetSubTickLength();

		void SetSubTickLineSymbol(Display::ILineSymbolPtr pLineSym);
		Display::ILineSymbolPtr GetSubTickLineSymbol();

		void SetTextSymbol(Display::CTextSymbolPtr pTextSym);
		Display::CTextSymbolPtr GetTextSymbol();

		void SetLabelOffset(float fLabelOffset);
		float GetLabelOffset();

		void SetLabelTop(BOOL bLabel);
		BOOL GetLabelTop();

		void SetLabelBottom(BOOL bLabel);
		BOOL GetLabelBottom();

		void SetLabelLeft(BOOL bLabel);
		BOOL GetLabelLeft();

		void SetLabelRight(BOOL bLabel);
		BOOL GetLabelRight();

		void SetVertTopBottom(BOOL bVert);
		BOOL GetVertTopBottom();

		void SetVertLeftRight(BOOL bVert);
		BOOL GetVertLeftRight();

		void SetMapGridLineStyle(int nStyle);
		int GetMapGridLineStyle();

		GridType GetGridType();

	public:
		virtual void Draw(Display::IDisplayPtr pDisplay);


	protected:
		void CalTickLines(Display::IDisplayPtr pDisplay, std::vector<stGridLabel>& vecVerticalLabel, std::vector<stGridLabel>& vecHorizontalLabel,
			GEOMETRY::geom::Geometry*& pTickLines, double tickOffset, double tickLength);

		void CalSubTickLines();


	protected:
		//���������Ƿ�ɼ�
		BOOL				m_bActive;
		
		/*
		//Grid
		*/
		//��������
		GridType			m_GridType;
		//��������
		std::string			m_strGridName;
		//������/���Ƿ�ɼ�
		BOOL				m_bGridVisibility;
		//���������Ƿ�䶯
		BOOL				m_bGridDirty;
		//����������ͣ���/��
		MapGridLineStyle			m_gridLineStyle;
		//�����߷���
		Display::ILineSymbolPtr		m_pGridLineSymbol;//line
		//������ͼ�μ�multiline
		GEOMETRY::geom::Geometry*	m_pLines; 	
		//�����Ƿ���
		Display::IMarkerSymbolPtr		m_pGridMarkerSymbol; //Marker
		//������ͼ�μ�multipoint
		GEOMETRY::geom::Geometry*	m_pMarkers;

		/*
		//Axis
		*/
		//�Ƿ�ʹ�õ�ͼԭ����Ϊ������ʼ��
		BOOL				m_bDynamicXYOrg;
		//�û����õ���ʼ������(��λ�����������Ͷ�������γ����������Ϊ��γ�ȣ���ͼ�����������ͼ���굥λ��ͬ)
		double				m_XOrigin;
		double				m_YOrigin;
		//ʵ����ʼ�������
		double				m_ActualXOrigin;
		double				m_ActualYOrigin;
		//�����϶
		double				m_XInterval;
		double				m_YInterval;

		/*
		//Border
		*/	
		//�߿��Ƿ�ɼ�
		BOOL				m_bBorderVisibility;
		//�߿������Ƿ����
		BOOL				m_bBorderDirty;
		//�߿�����
		double				m_borderExpandX;//mm
		double				m_borderExpandY;//mm
		double				m_borderExpandXPage;//Page unit
		double				m_borderExpandYPage;//Page unit
		//�߿���Ʒ���
		Display::ILineSymbolPtr		m_pBorderLineSymbol;
		//�߿�Χ����λ��ֽ�ŵ�λ��
		GEOMETRY::geom::Envelope		m_envBorder;
		//�߿�ͼ��
		GEOMETRY::geom::Geometry*	m_pBorderLine;

		/*
		//Label
		*/	
		//��ע�Ƿ�ɼ�
		BOOL				m_bLabelVisibility;
		//��ע�Ƿ�䶯
		BOOL				m_bLabelDirty;
		//��ע��ƫ�ƾ���
		double				m_labelOffset;//mm
		//�Ƿ�����϶˱�ע
		BOOL				m_bLabelTop;
		//�Ƿ�����¶˱�ע
		BOOL				m_bLabelBottom;
		//�Ƿ��������ע	
		BOOL				m_bLabelLeft;
		//�Ƿ�����Ҳ��ע
		BOOL				m_bLabelRight;
		//���¶˱�ע�����Ƿ�ֱ����
		BOOL				m_bVertTopBottom;
		//���Ҳ��ע�����Ƿ�ֱ����
		BOOL				m_bVertLeftRight;
		//���ֻ��Ʒ���
		Display::CTextSymbolPtr		m_pTextSym;
		//���¶�����λ�ü��������ݼ���
		std::vector<stGridLabel>		m_vecVerticalLabel;
		//���Ҳ�����λ�ü��������ݼ���
		std::vector<stGridLabel>		m_vecHorizontalLabel;
		//���¶����ּ���
		std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerLabels;
		//���Ҳ����ּ���	
		std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorLabels;

		/*
		//Tick
		*/	
		//�̶��Ƿ�ɼ�
		BOOL				m_bTickVisibility;
		//�̶������Ƿ�ı�
		BOOL				m_bTickDirty;
		//�̶���Ŀ
		int					m_tickCount;
		//�̶ȳ���
		double				m_tickLength;//mm
		//�̶ȳ���
		double				m_tickLengthPage;//page unit
		//�̶�ƫ��
		double				m_tickOffset;//mm
		//�̶�ƫ��
		double				m_tickOffsetPage;//page unit
		//�̶Ȼ��Ʒ���
		Display::ILineSymbolPtr		m_pTickLineSymbol;
		//�̶��ּ���multiline
		GEOMETRY::geom::Geometry* m_pTickLines;

		/*
		//sub Tick
		*/
		//�̶ֿ��Ƿ�ɼ�
		BOOL				m_bSubTickVisibility;
		//�̶������Ƿ�ı�
		BOOL				m_bSubTickDirty;
		//�̶ֿ���Ŀ
		int					m_subTickCount;
		//�̶ֿȳ���
		double				m_subTickLength;//mm
		//�̶ֿȳ���
		double				m_subTickLengthPage;//page unit
		//�̶ֿ��߷���
		Display::ILineSymbolPtr		m_pSubTickLineSymbol;
		//�̶��ּ���multiline
		GEOMETRY::geom::Geometry* m_pSubTickLines;
	};

	typedef SYSTEM::CSmartPtr<IGrid> IGridPtr;
}
#endif
