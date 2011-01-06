#ifndef _ILayoutCtrl_h
#define _ILayoutCtrl_h

#include "IUIObject.h"
#include "PageLayout.h"
#include "IDisplay.h"
#include "ElementCollection.h"
#include "ITool.h"
#include "ICommand.h"

namespace Framework
{

	class FRAMEWORK_DLL ILayoutCtrl : public IUIObject
	{
	public:
		ILayoutCtrl();
		virtual ~ILayoutCtrl();

		void serialization(SYSTEM::IArchive &ar);

		void Initialize();

		BOOL Initialized();

		void ClearCtrl();

		static ILayoutCtrl* GetActiveLayoutCtrl();

		//更新制图内容
		virtual void UpdateControl(long content = (drawElement | drawEdit));

		void ReDraw(long content);

		void RefreshScreen();


		void OffsetClient(long offset_x, long offset_y);

		Carto::CPageLayoutPtr GetPageLayout();

		void SetPageLayout(Carto::CPageLayoutPtr pLayout);

		Element::CElementCollection* GetElementCopyBoard(){return &m_ElementCopyBoard;};

		void OnPrint(CDC* pDC);

		void OnBeginPrinting(CDC* pDC);

		void OnEndPrinting(CDC* pDC);

		COLORREF GetBgColor(){return m_BgColor;};

		HDC GetClientDC() {return m_hClientDC;}

		HDC GetMemDC() {return m_hMemDC;}

		//得到控件的大小
		long GetSizeX() { return m_lSizeX;}
		long GetSizeY() {return m_lSizeY;}

		void ControlResize(UINT nType, int cx, int cy);

	protected:
		Carto::CPageLayoutPtr	m_pPageLayout;	
		BOOL m_bInitialized;

		Element::CElementCollection m_ElementCopyBoard;


		HDC m_hClientDC,m_hMemDC;

		long m_lSizeX,m_lSizeY;

		COLORREF m_BgColor;

		long m_bakDCWidth;
		long m_bakDCHeight;
		long m_bakHdc;
		GEOMETRY::geom::Envelope m_bakEnv;

		std::string m_curToolname;

		HCURSOR m_cursor;

		HWND m_hCtrlWnd; 


	};



}
#endif