//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/15
// ������  ��ͼҪ�ء�����״������
//////////////////////////////////////////////////////////////////////

#ifndef CSCALE_LINE_H
#define CSCALE_LINE_H
#include "IScaleBar.h"
namespace Element{

class CARTO_DLL CScaleLine :public IScaleBar
{
public:
	CScaleLine();
	CScaleLine(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);
	~CScaleLine(void);

	virtual void serialization(SYSTEM::IArchive &ar);   

//	IElementPtr Clone();

protected:

	void ConvertMillimeterToPixel(Display::IDisplayPtr pDisplay);

	void DrawNormal(Display::IDisplayPtr pDisplay);

	void DrawBar(Display::IDisplayPtr pDisplay, DIS_RECT rect);



	/**
	* ��������:��¡����
	* @return _ptr_t<IElement> Element����ָ��
	*/
	//IElementPtr Clone();

};

typedef SYSTEM::CSmartPtr<CScaleLine> CScaleLinePtr;
}
#endif
