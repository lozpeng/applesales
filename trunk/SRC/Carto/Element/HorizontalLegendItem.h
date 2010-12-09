//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/10
// ������  ��ͼҪ�ء���ˮƽͼ����
//////////////////////////////////////////////////////////////////////

#ifndef CHORIZONTAL_LEGEND_ITEM_H
#define CHORIZONTAL_LEGEND_ITEM_H

#include "ILegendItem.h"
#include "LegendInfo.h"

namespace Element{


class CARTO_DLL CHorizontalLegendItem :public ILegendItem
{
public:
	CHorizontalLegendItem();
	CHorizontalLegendItem(Carto::ILayerPtr	pLayer);
	~CHorizontalLegendItem(void);

	void serialization(SYSTEM::IArchive &ar);

	void Draw(Display::IDisplayPtr pDisplay, DIS_RECT& rect);

	ILegendItemPtr Clone();

protected:
	void DrawLayerName(Display::IDisplayPtr pDisplay, DIS_RECT& rect, std::string strLayerName);
	void DrawHeading(Display::IDisplayPtr pDisplay, DIS_RECT& rect, std::string strHeading);
	void DrawPatchLabelDesc(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup);
	void DrawPatchDescLabel(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup);
	void DrawLabelPatchDesc(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup);
	void DrawLabelDescPatch(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup);
	void DrawDescPatchLabel(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup);
	void DrawDescLabelPatch(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup);

protected:
	LegendItemArrangement	m_Arrange;
};

typedef SYSTEM::CSmartPtr<CHorizontalLegendItem> CHorizontalLegendItemPtr;
}


#endif