//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/15
// ������  �����󡪡�ͼƬ��
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

		//���ù���ͼ��
		void SetLayer(Carto::CRasterLayerPtr pRasLayer);
		
		//��ȡ����ͼ��
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
		Carto::CMapPtr m_pMap;	//�ڲ���������ͼƬ�ĵ�ͼ

		std::string m_strPicPath;

		

	};

	typedef SYSTEM::CSmartPtr<CPictureElement> CPictureElementPtr;
}
#endif
