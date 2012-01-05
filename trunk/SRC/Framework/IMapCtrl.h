#ifndef _IMapCtrl_h
#define _IMapCtrl_h

#include "IUIObject.h"
#include "Map.h"
#include "IDisplay.h"
#include "ITool.h"
#include "ICommand.h"
using namespace Element;

namespace Framework
{
	class FRAMEWORK_DLL IMapCtrl : public IUIObject
	{
	public:
		IMapCtrl();
		virtual ~IMapCtrl();

	public:

		virtual void ReDraw(long content);

		//�ؼ��ͻ�����С�ı��¼�
		virtual void ControlResize(UINT nType, int cx, int cy);

		//���õ�ͼ����
		virtual void SetMap(Carto::CMapPtr pGeoMap);

		//�õ���ͼ����
		virtual Carto::CMapPtr GetMap();

		//���µ�ͼ����
		virtual void UpdateControl(long content);

		//ˢ�µ�ͼ����
		virtual void RefreshScreen();

		//�ƶ���ͼ����
		virtual void OffsetClient(long offset_x, long offset_y);

		COLORREF GetBgColor(){return m_BgColor;};

		HDC GetClientDC() {return m_hClientDC;}

		HDC GetMemDC() {return m_hMemDC;}

		//�õ��ؼ��Ĵ�С
		long GetSizeX() { return m_lSizeX;}
		long GetSizeY() {return m_lSizeY;}

		//���������
		void SetCursor(HCURSOR cursor);

		//�õ�������
		HWND GetHWnd();

		//���õ�ǰ����
		void SetCurTool(std::string toolname) {m_curToolname =toolname;}

		std::string GetCurToolName() {return m_curToolname;}

		void SetMapFramedStatus(BOOL bFramed);


		Element::CElementCollection* GetElementCopyContainer(){return &m_ElementCopyContainer;};

		static IMapCtrl* GetActiveMapCtrl();

		//��˸ͼ��
		void FlashShape(GEOMETRY::geom::Geometry* pShape,long nFlashes=1,long flashInterval=300,Display::ISymbol* symbol=NULL);

	protected:
		//����������������Ļ��
		void RefreshGeography();

	protected:


		Carto::CMapPtr m_pGeoMap;


		BOOL m_bInitialized;

		HDC m_hClientDC,m_hMemDC;

		long m_lSizeX,m_lSizeY;

		COLORREF m_BgColor;

		std::string m_curToolname;

		HCURSOR m_cursor;

		HWND m_hCtrlWnd; 

		CElementCollection  m_ElementCopyContainer;//�����Ҫcopy�Ķ���


	};

}
#endif