//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/10
// ������  ��ͼҪ�ء���ͼ����
//////////////////////////////////////////////////////////////////////


#ifndef ILEGEND_ITEM_H
#define ILEGEND_ITEM_H

#include "TextSymbol.h"
#include "ElementDefine.h"
#include "ISelectionTracker.h"
#include "ISerialization.h"

namespace Element{

	enum Legend_Item_Type
	{
		LIT_HORIZONTAL,
		LIT_VERTICAL
	};
	
class CARTO_DLL ILegendItem : public SYSTEM::ISerialization
{
public:
	ILegendItem();
	ILegendItem(Carto::ILayerPtr	pLayer);
	~ILegendItem(void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	static SYSTEM::CSmartPtr<ILegendItem> CreateLegendItemFromStream(SYSTEM::IArchive &ar);

	static SYSTEM::CSmartPtr<ILegendItem> CreateLegendItem(Legend_Item_Type type);


	virtual void Draw(Display::IDisplayPtr pDisplay, DIS_RECT& rect);

	virtual SYSTEM::CSmartPtr<ILegendItem> Clone()=0;

	void SetLayer(Carto::ILayerPtr pLayer);

	Carto::ILayerPtr GetLayer(){return m_pLayer;};

	void SetLayerID(long lID);

	long GetLayerID();

	 void SetLayerNameSymbol(Display::CTextSymbolPtr pTextSymbol);
	 Display::CTextSymbolPtr GetLayerNameSymbol();

	 void SetHeadingSymbol(Display::CTextSymbolPtr pTextSymbol);
	 Display::CTextSymbolPtr GetHeadingSymbol();

	 void SetLabelSymbol(Display::CTextSymbolPtr pTextSymbol);
	 Display::CTextSymbolPtr GetLabelSymbol();

	 void SetDescSymbol(Display::CTextSymbolPtr pTextSymbol);
	 Display::CTextSymbolPtr GetDescSymbol();


	 BOOL GetStartCol(){return m_bStartCol;};
	 void SetStartCol(BOOL bStartCol){m_bStartCol = bStartCol;};

	 int GetColCount(){return  m_nColumns;};
	 void SetColCount(int nColCount){m_nColumns = nColCount;};

	void SetReadDirection(BOOL bRightToLeft);
	BOOL GetReadDirection();

	void SetPatchWidth(float fWidth);
	float GetPatchWidth();

	void SetPatchHeight(float fHeight);
	float GetPatchHeight();

	void SetPatchMarkerSymbolStyle(MarkerSymbolLegendStyle markerStyle);
	MarkerSymbolLegendStyle GetPatchMarkerSymbolStyle();

	void SetPatchLineSymbolStyle(LineSymbolLegendStyle lineStyle);
	LineSymbolLegendStyle GetPatchLineSymbolStyle();

	void SetPatchAreaSymbolStyle(FillSymbolLegendStyle areaStyle);
	FillSymbolLegendStyle GetPatchAreaSymbolStyle();

	void SetLayerNameAndGroup(float fSpace);
	float GetLayerNameAndGroup();

	void SetHeadingAndClasses(float fSpace);
	float GetHeadingAndClasses();

	void SetClassesSpace(float fSpace);
	float GetClassesSpace();

	void SetPatchAndOther(float fSpace);
	float GetPatchAndOther();

	void SetLabelAndOther(float fSpace);
	float GetLabelAndOther();

protected:
	virtual void ConvertPointToDisplay(Display::IDisplayPtr pDisplay);	

	virtual DIS_RECT GetPatchSize();

	virtual DIS_RECT GetTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text);


	virtual void DrawText(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, DIS_RECT& rect, std::string text, unsigned int dwDTFormat);

protected:

	Legend_Item_Type m_type;

	Carto::ILayerPtr	m_pLayer;	//��item��ص�layer

	BOOL			m_bRightToLeft;	//
	BOOL			m_bStartCol;	//�Ƿ�ΪLegend��һ�е���ʼͼ����

	BOOL			m_bCanDisplay;	//�Ƿ����
	int				m_nColumns;		//item������
	int				m_nHeight;		//item�ĸ߶ȣ�mm��
	int				m_nWidth;		//item�Ŀ�ȣ�mm��
	long			m_lHeightPixel;	//pixel
	long			m_lWidthPixel;	//pixel

	int				m_LayerNameAndGroup;	//layer name�������ľ��루mm��
	int				m_HeadingAndClasses;	//Head�͸����ͼ���ľ��루mm��
	int				m_ClassesSpaces;			//�����֮��ľ��루mm��
	int				m_PatchAndOther;		//��������������ע/����/layer name�����루mm��
	int				m_LabelAndOther;		//��ע�������ľ��루mm��
	long			m_LayerNameAndGroupPixel;//pixel	
	long			m_HeadingAndClassesPixel;//pixel
	long			m_ClassesSpacesPixel;			//pixel
	long			m_PatchAndOtherPixel;	//pixel
	long			m_LabelAndOtherPixel;	//pixel	


	LegendItemStyle	m_itemStyle;	//item����ʾ���

	BOOL			m_bShowHeading;
	BOOL			m_bShowLayerName;
	BOOL			m_bShowLabels;
	BOOL			m_bShowDescriptions;
	
	Display::CTextSymbolPtr	m_pLayerNameSymbol;
	Display::CTextSymbolPtr	m_pHeadingSymbol;	
	Display::CTextSymbolPtr	m_pLabelSymbol;
	Display::CTextSymbolPtr	m_pDescriptionSymbol;

	int				m_patchWidth;
	int				m_patchHeight;
	long			m_patchWidthPixel;
	long			m_patchHeightPixel;
	LineSymbolLegendStyle	m_patchLineStyle;
	FillSymbolLegendStyle	m_patchAreaStyle;
	MarkerSymbolLegendStyle	m_patchMarkerStyle;

	//Display::IMarkerSymbolPtr	m_patchMarkerSymbol;


protected:
	long	m_LayerID;//ֻ�����л�����ʱ��ʱ����ͼ�����ʱʹ��


};

typedef SYSTEM::CSmartPtr<ILegendItem> ILegendItemPtr;
}
#endif
