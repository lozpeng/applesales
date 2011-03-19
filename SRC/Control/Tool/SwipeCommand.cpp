#include "StdAfx.h"
#include "DlgSwipeSld.h"
#include "LayerArray.h"
#include "SwipeCommand.h"
#include "IMapCtrl.h"
#include "RasterLayer.h"
#include "RasterRGBRender.h"
#include "DllResource.h"



namespace Control
{
	
static CSwipeCommand gActionSwipe;

CSwipeCommand::CSwipeCommand(void):Framework::ICommand("SwipeEnhance")
{

}

CSwipeCommand::~CSwipeCommand(void)
{
}

void CSwipeCommand::Click()
{
	Control::CDllResource hdll;
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;



	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();

	if(!pMap)
		return;

	CEnhanceSld *enhangceDlg= new CEnhanceSld();
	if (enhangceDlg!=NULL)
	{
		GEOMETRY::geom::Envelope rect=pMap->GetViewEnvelope();
		Display::IDisplayPtr m_display=pMap->GetDisplay();

		RECT viewrect = m_display->GetDisplayTransformation().GetViewPosition().GetViewBound().GetRect();

		CRect m_rect(viewrect.left,viewrect.top,viewrect.right,viewrect.bottom);

		Carto::CLayerArray m_MapLayers=pMap->GetLayers();

         
		CDC *bakDC =new CDC();//定义显示设备对象
		HDC hdc =(HDC)pMap->GetDisplay()->GetDrawDC()->GetSafeHdc();
		bakDC->Attach(hdc);

		CDC pTempDC1, pTempDC2;//定义显示设备对象
		CBitmap bmp1,bmp2;
		CBitmap *oldBmp1, *oldBmp2;

         //创建与屏幕DC兼容的内存DC
		pTempDC1.CreateCompatibleDC(bakDC);
		pTempDC2.CreateCompatibleDC(bakDC);

        //创建与屏幕DC兼容的位图，进行图形绘制
		bmp1.CreateCompatibleBitmap(bakDC,m_rect.Width(), m_rect.Height());
		bmp2.CreateCompatibleBitmap(bakDC,m_rect.Width(), m_rect.Height());

        //将位图选入内存DC
		oldBmp1 = pTempDC1.SelectObject(&bmp1);
		oldBmp2 = pTempDC2.SelectObject(&bmp2);

		//将屏幕内存DC上的图形拷贝到临时内存pTempDC1
		pTempDC1.BitBlt(0,0,m_rect.Width(), m_rect.Height(),bakDC,0,0, SRCCOPY);

		//用背景色将位图清除干净，这里选择白色为背景。
		FloodFill(pTempDC2.GetSafeHdc(), 0,0,RGB(255,255,255));

		//将n-1层影像绘制到屏幕内存DC中的，drawTempObj临时位图中

		//选择临时位图
		pMap->GetDisplay()->SetDrawBuffer(drawTempObj);

		long lMapLayerCount=m_MapLayers.GetSize();
		if (lMapLayerCount>=2)
		{
			for (int i=0 ; i<m_MapLayers.GetSize()-1 ; i++ )
			{
				m_MapLayers[i]->Draw( m_display , drawGeography );
			}
			//将屏幕内存DC上的图形拷贝到临时内存pTempDC2
			::BitBlt(pTempDC2.GetSafeHdc(),0,0,m_rect.Width(), m_rect.Height(),hdc,0,0,SRCCOPY);
		}


		enhangceDlg->SetGeoMap(&pMap,m_display,pMapCtrl);
		enhangceDlg->SetGeoMapDCs(&pTempDC1,&pTempDC2,m_rect,hdc);
		enhangceDlg->DoModal();


		pTempDC1.SelectObject(oldBmp1);
		pTempDC2.SelectObject(oldBmp2);
		//绘制完成后的清理
       bmp1.DeleteObject();
		bmp2.DeleteObject();

		pTempDC1.DeleteDC( );
		pTempDC2.DeleteDC( );

		pMap->GetDisplay()->SetDrawBuffer(drawAll);
  
		bakDC->Detach();
		delete bakDC;
	}
}
}