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
	//��ȡ���ͼ�ؼ�
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;



	//��ȡ�����
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

         
		CDC *bakDC =new CDC();//������ʾ�豸����
		HDC hdc =(HDC)pMap->GetDisplay()->GetDrawDC()->GetSafeHdc();
		bakDC->Attach(hdc);

		CDC pTempDC1, pTempDC2;//������ʾ�豸����
		CBitmap bmp1,bmp2;
		CBitmap *oldBmp1, *oldBmp2;

         //��������ĻDC���ݵ��ڴ�DC
		pTempDC1.CreateCompatibleDC(bakDC);
		pTempDC2.CreateCompatibleDC(bakDC);

        //��������ĻDC���ݵ�λͼ������ͼ�λ���
		bmp1.CreateCompatibleBitmap(bakDC,m_rect.Width(), m_rect.Height());
		bmp2.CreateCompatibleBitmap(bakDC,m_rect.Width(), m_rect.Height());

        //��λͼѡ���ڴ�DC
		oldBmp1 = pTempDC1.SelectObject(&bmp1);
		oldBmp2 = pTempDC2.SelectObject(&bmp2);

		//����Ļ�ڴ�DC�ϵ�ͼ�ο�������ʱ�ڴ�pTempDC1
		pTempDC1.BitBlt(0,0,m_rect.Width(), m_rect.Height(),bakDC,0,0, SRCCOPY);

		//�ñ���ɫ��λͼ����ɾ�������ѡ���ɫΪ������
		FloodFill(pTempDC2.GetSafeHdc(), 0,0,RGB(255,255,255));

		//��n-1��Ӱ����Ƶ���Ļ�ڴ�DC�еģ�drawTempObj��ʱλͼ��

		//ѡ����ʱλͼ
		pMap->GetDisplay()->SetDrawBuffer(drawTempObj);

		long lMapLayerCount=m_MapLayers.GetSize();
		if (lMapLayerCount>=2)
		{
			for (int i=0 ; i<m_MapLayers.GetSize()-1 ; i++ )
			{
				m_MapLayers[i]->Draw( m_display , drawGeography );
			}
			//����Ļ�ڴ�DC�ϵ�ͼ�ο�������ʱ�ڴ�pTempDC2
			::BitBlt(pTempDC2.GetSafeHdc(),0,0,m_rect.Width(), m_rect.Height(),hdc,0,0,SRCCOPY);
		}


		enhangceDlg->SetGeoMap(&pMap,m_display,pMapCtrl);
		enhangceDlg->SetGeoMapDCs(&pTempDC1,&pTempDC2,m_rect,hdc);
		enhangceDlg->DoModal();


		pTempDC1.SelectObject(oldBmp1);
		pTempDC2.SelectObject(oldBmp2);
		//������ɺ������
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