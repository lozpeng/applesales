//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  制图要素——标题  
//////////////////////////////////////////////////////////////////////

#ifndef IMAP_TITLE_H
#define IMAP_TITLE_H
#include "IMapSurround.h"


namespace Carto
{
	class CMap;
}

namespace Element{

class CARTO_DLL CMapTitle :public IMapSurround
{
public:
	CMapTitle();
	CMapTitle(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);
	~CMapTitle(void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	void Move(double dx, double dy);

	virtual void DrawNormal(Display::IDisplayPtr pDisplay);

	void ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope);


	std::string GetText(){return m_strTitle;};
	void SetText(std::string text){m_strTitle = text;};

protected:
	std::string m_strTitle;
	GEOMETRY::geom::Coordinate m_coordOrg;//文字0度时envelope的左下角坐标



};
typedef SYSTEM::CSmartPtr<CMapTitle> CMapTitlePtr;
}
#endif