//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  标绘对象——图片框
//////////////////////////////////////////////////////////////////////

#ifndef CPICTURE_ELEMENT_H
#define CPICTURE_ELEMENT_H

#include "IFrameElementBase.h"
#include "RasterLayer.h"


namespace Element{

	class CARTO_DLL CPictureElement : public IFrameElementBase
	{
	public:
		CPictureElement();
		CPictureElement(const GEOMETRY::geom::Geometry& geometry);
		~CPictureElement(void);

		void serialization(SYSTEM::IArchive &ar);

		//设置关联图层
		void SetLayer(Carto::CRasterLayerPtr pRasLayer);
		
		//获取关联图层
		Carto::CRasterLayerPtr GetLayer();	

		void GeometryChangedEvents();

		void SetPicturePath(std::string picPath);

		std::string GetPicturePath();
		
	protected:	
		void DrawNormal(Display::IDisplayPtr pDisplay);

		void DrawMap(Display::IDisplayPtr pDisplay);

		void ReDrawMap(Display::IDisplayPtr pDisplay);

		void UpdateMapDisplay(Display::IDisplayPtr pDisplay);
		
	
	protected:
		BOOL	m_bMapDCInited;
		BOOL	m_bProperChanged;
		Carto::CMapPtr m_pMap;	//内部用来绘制图片的地图

		std::string m_strPicPath;

		

	};

	typedef SYSTEM::CSmartPtr<CPictureElement> CPictureElementPtr;
}
#endif
