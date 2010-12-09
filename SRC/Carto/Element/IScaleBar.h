//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/14
// ������  ��ͼҪ�ء���������
//////////////////////////////////////////////////////////////////////


#ifndef ISCALE_BAR_H
#define ISCALE_BAR_H
#include "IMapSurround.h"
#include "TextSymbol.h"
#include "DisRectSet.h"

#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
typedef boost::signals::connection  connection_t;


namespace Element{

class CARTO_DLL IScaleBar :public IMapSurround
{
public:
	IScaleBar();
	IScaleBar(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);
	~IScaleBar(void);

	void MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord);

	virtual void serialization(SYSTEM::IArchive &ar); 

	static SYSTEM::CSmartPtr<IScaleBar> CreateScaleBarFromStream(SYSTEM::IArchive &ar);

	static SYSTEM::CSmartPtr<IScaleBar> CreateScaleBar(ELEMENT_TYPE type);

	void UnitChanged(SYSTEM::SYS_UNIT_TYPE newUnit);

	//bar
	void SetTextSymbol(Display::CTextSymbolPtr pTextSymbol);
	Display::CTextSymbolPtr GetTextSymbol();

	void SetForeSymbol(Display::ISymbolPtr pBarSymbol);
	Display::ISymbolPtr GetForeSymbol();

	void SetBackSymbol(Display::ISymbolPtr pBarSymbol);
	Display::ISymbolPtr GetBackSymbol();

	void SetDivisionLen(double len);
	double GetDivisionLen();

	void SetDivisionNum(int num);
	int GetDivisionNum();

	void SetSubDivisionNum(int num);
	int GetSubDivisionNum();

	void SetDrawDivisionBeforZero(BOOL isDraw);
	BOOL GetDrawDivisionBeforZero();

	//mark
	void SetDivMarkHeight(double markHeight);
	double GetDivMarkHeight();

	void SetSubDivMarkHeight(double markHeight);
	double GetSubDivMarkHeight();

	void SetMarkPos(MarkPosition pos);
	MarkPosition GetMarkPos();

	void SetMarkFreq(LabelFrequency freq);
	LabelFrequency GetMarkFreq();

	void SetMarkLineSymbol(Display::ILineSymbolPtr pLineSymbol);
	Display::ILineSymbolPtr GetMarkLineSymbol();

	//num label
	void SetNumGap(double gap);
	double GetNumGap();

	void SetNumFreq(LabelFrequency freq);
	LabelFrequency GetNumFreq();

	void SetNumPos(NumPosition pos);
	NumPosition GetNumPos();


	void SetNumTextSymbol(Display::CTextSymbolPtr pSymbol);
	Display::CTextSymbolPtr GetNumTextSymbol();

	//unit
	void SetUnit(SYSTEM::SYS_UNIT_TYPE unit);
	SYSTEM::SYS_UNIT_TYPE	GetUnit();

	void SetUnitGap(double gap);
	double GetUnitGap();

	void SetUnitPos(UnitPosition pos);
	UnitPosition GetUnitPos();

	void SetUnitTextSymbol(Display::CTextSymbolPtr pSymbol);
	Display::CTextSymbolPtr GetUnitTextSymbol();

	
protected:
	void DrawNormal(Display::IDisplayPtr pDisplay);

protected:
	virtual void DrawBar(Display::IDisplayPtr pDisplay, DIS_RECT rect)=0;

	virtual void DrawMark(Display::IDisplayPtr pDisplay, DIS_RECT rect);

	virtual void DrawUnitLabel(Display::IDisplayPtr pDisplay, DIS_RECT rect);

	virtual void DrawNumLabel(Display::IDisplayPtr pDisplay, DIS_RECT rect);

protected:
	void RecalcGeometry(Display::IDisplayPtr pDisplay);

	void CalculateScalebarRectSet(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet);
	
	DIS_RECT CalcUnitSize(Display::IDisplayPtr pDisplay);

	DIS_RECT CalcBarSize(Display::IDisplayPtr pDisplay);

	DIS_RECT CalcMarkSize(Display::IDisplayPtr pDisplay, DIS_RECT barRect);

	DIS_RECT CalcNumSize(Display::IDisplayPtr pDisplay, DIS_RECT barRect);

	void NormalizeRect(Display::IDisplayPtr pDisplay, DIS_RECT& rect);

	void TransferNumToDisplay(double number, char* cNum);

	DIS_RECT CalculateTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol,  std::string str);

	void AddBarRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT barRect);

	void AddMarkRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT markRect);

	void AddNumRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT numRect);

	void AddUnitRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT unitRect);

	void DrawText(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text, DIS_RECT rect, unsigned int dwDTFormat);

	void ConvertMillimeterToPixel(Display::IDisplayPtr pDisplay);


protected:

	connection_t m_ConnectionMapFrameProperChanged;

	void CallbackMapFrameProperChangedFun(CMapFrame* pMapFram);

protected:
	//GEOMETRY::geom::Envelope m_env;  //legend���������Χ������legend���Ͽ����ţ�
	//ÿ��legend�����ڲ����ݡ�����ȱ仯�����ʵ��Χ�仯ʱ������

	BOOL						m_contentChanged;	//��־�����Ƿ�ı�

	double						m_mapScale;			//��ͼ������
	
	//bar
	Display::CTextSymbolPtr	m_pTextSymbol;		//����������
	Display::ISymbolPtr		m_pForeSymbol;		//������ǰ��ɫ
	Display::ISymbolPtr		m_pBackSymbol;		//�����߱���ɫ
	double						m_BarHeight;		//�����ߵĸ߶�(��λ��mm)
	long						m_BarHeightPixel;	//�����ߵĸ߶�(��λ��Pixel)
	double						m_DivisionLen;		//���ֶεĳ���
	int							m_DivisionNum;		//���ֶε���Ŀ
	int							m_SubDivisionNum;	//�ӷֶε���Ŀ
	BOOL						m_DrawDivBeforZero;	//�����Ƿ���0ֵǰ����һ���ֶ�

	//mark
	double						m_DivisionMarkHeight;//���ֶο̶ȸ߶�(��λ��mm)
	long						m_DivisionMarkHeightPixel;//���ֶο̶ȸ߶�(��λ��pixel)
	double						m_SubDivisionMarkHeight;//�ӷֶο̶ȸ߶�(��λ��mm)
	long						m_SubDivisionMarkHeightPixel;//�ӷֶο̶ȸ߶�(��λ��Pixel)
	MarkPosition				m_MarkPos;			//�̶ȵ�λ��
	LabelFrequency				m_MarkFreq;			//�̶Ȼ��ƵĹ���
	Display::ILineSymbolPtr	m_pMarkLineSymbol;		//�̶ȵ��߷���

	//num label
	Display::CTextSymbolPtr	m_NumTextSymbol;	//���ֱ�ע������
	double						m_NumLabelGap;		//���ֱ�ע������ߵľ���(��λ��mm)
	long						m_NumLabelGapPixel;	//���ֱ�ע������ߵľ���(��λ��Pixel)
	LabelFrequency				m_NumLabelFreq;		//���ֱ�ע���ƵĹ���
	NumPosition					m_NumLabelPos;		//���ֱ�ע����ڱ����ߵ�λ��

	//unit label
	Display::CTextSymbolPtr	m_UnitTextSymbol;	//��λ��ע������
	SYSTEM::SYS_UNIT_TYPE		m_Unit;				//��λ
	double						m_UnitLabelGap;		//��λ��ע������ߵľ���(��λ��mm)
	long						m_UnitLabelGapPixel;//��λ��ע������ߵľ���(��λ��Pixel)
	UnitPosition				m_UnitLabelPos;		//��λ��ע��Ա����ߵķ�λ

	
};
typedef SYSTEM::CSmartPtr<IScaleBar> IScaleBarPtr;
}
#endif