#include "stdafx.h"
#include "LayoutPrintToImageCmd.h"
//#include "PageOptionDlg.h"
#include "DllResource.h"
#include "DlgPrintImgSet.h"
//#include "tt_pic.h"
//
#include "IWorkspace.h"
//#include "TT_File.h"
#include "RasterWSFactory.h"
namespace Control
{


	void CPrintToImageCmd::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);


		//��ȡ���ͼ�ؼ�
		m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);

	}
	void CPrintToImageCmd::Click()
	{
		ICommand::Click();

		//��ȡ���ͼ�ؼ�
		if(!m_pLayoutCtrl)
			return;

		//��ȡ�����
		Carto::CPageLayoutPtr pPageLayout = m_pLayoutCtrl->GetPageLayout();
		if(!pPageLayout)
			return;


		Element::CPagePtr pPage = pPageLayout->GetPage();
		if(!pPage)
			return;

		//��ӡ�������
		Control::CDllResource hdll;	
		CDlgPrintImgSet dlgimgset;

		double dpi = 96;
		CString csPrintImgPath = "";
		dlgimgset.m_dblDpi=dpi;
		dlgimgset.m_dblSizeX=pPage->GetPageInfo().width ;
		dlgimgset.m_dblSizeY=pPage->GetPageInfo().height ;
		dlgimgset.m_strWidth.Format("%d",INT(dlgimgset.m_dblSizeX*dpi/25.4));
		dlgimgset.m_strHeight.Format("%d",INT(dlgimgset.m_dblSizeY*dpi/25.4));

		if(dlgimgset.DoModal()==IDOK)
		{
			dpi=dlgimgset.m_dblDpi;
			csPrintImgPath=dlgimgset.m_strPrintImgPath; 

			PrintToImg(csPrintImgPath, dpi/25.4);		
		}	

		m_pLayoutCtrl->UpdateControl();
		m_pLayoutCtrl->SetCurTool("SelectFrameElements");

		CWnd *pWnd =dynamic_cast<CWnd*>(m_pLayoutCtrl);
		pWnd->SetFocus();	

	}

static BOOL MakeTempFileName(CString &csTempFileName,CString extType);

static CPrintToImageCmd gPrintToImageCmd;

CPrintToImageCmd::CPrintToImageCmd() : ICommand("PrintToImage")
{
	
}

CPrintToImageCmd::~CPrintToImageCmd()
{

}

//��dc�ϵ�bitmap�����ȥ
bool SaveBmp(HBITMAP hBitmap, CString FileName)
{

	//�豸������
	HDC hDC;
	//��ǰ�ֱ�����ÿ������ռ�ֽ���
	int iBits;
	//λͼ��ÿ������ռ�ֽ���
	WORD wBitCount;
	//�����ɫ���С�� λͼ�������ֽڴ�С ��λͼ�ļ���С �� д���ļ��ֽ��� 
	DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0; 
	//λͼ���Խṹ 
	BITMAP Bitmap;  
	//λͼ�ļ�ͷ�ṹ
	BITMAPFILEHEADER bmfHdr;  
	//λͼ��Ϣͷ�ṹ 
	BITMAPINFOHEADER bi;  
	//ָ��λͼ��Ϣͷ�ṹ  
	LPBITMAPINFOHEADER lpbi;  
	//�����ļ��������ڴ�������ɫ���� 
	HANDLE fh, hDib, hPal,hOldPal=NULL; 

	//����λͼ�ļ�ÿ��������ռ�ֽ��� 
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES); 
	DeleteDC(hDC); 
	if (iBits <= 1) wBitCount = 1; 
	else if (iBits <= 4)  wBitCount = 4; 
	else if (iBits <= 8)  wBitCount = 8; 
	else   wBitCount = 24; 

	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 0;

	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

	//Ϊλͼ���ݷ����ڴ� 
	hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
	*lpbi = bi; 

	// �����ɫ��  
	hPal = GetStockObject(DEFAULT_PALETTE); 
	if (hPal) 
	{ 
		hDC = ::GetDC(NULL); 
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
		RealizePalette(hDC); 
	}

	// ��ȡ�õ�ɫ�����µ�����ֵ 
	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) 
		+dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS); 

	//�ָ���ɫ��  
	if (hOldPal) 
	{ 
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
		RealizePalette(hDC); 
		::ReleaseDC(NULL, hDC); 
	} 

	//����λͼ�ļ�  
	fh = CreateFile(FileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); 

	if (fh == INVALID_HANDLE_VALUE)  return FALSE; 

	// ����λͼ�ļ�ͷ 
	bmfHdr.bfType = 0x4D42; // "BM" 
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize; 
	bmfHdr.bfReserved1 = 0; 
	bmfHdr.bfReserved2 = 0; 
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize; 
	// д��λͼ�ļ�ͷ 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); 
	// д��λͼ�ļ��������� 
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL); 
	//���  
	GlobalUnlock(hDib); 
	GlobalFree(hDib); 
	CloseHandle(fh); 

	return true;
}

//////////////////////////////////////////////////////////////////////////
void CPrintToImageCmd::PrintToImg(CString csPrintImgPath, double dpi)
{
	Framework::ILayoutCtrl* pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	if(!pLayoutCtrl)
		return;

	Carto::CPageLayoutPtr pPageLayout = pLayoutCtrl->GetPageLayout();
	if(!pPageLayout)
		return;

	pPageLayout->GetGraphicLayer()->UnselectAllElements();

	Element::CPagePtr pPage = pPageLayout->GetPage();
	if(!pPage)
		return;

	//��ȡpage��Χ����ӡӰ��Ĵ�С
	GEOMETRY::geom::Envelope PageEnv;
	PageEnv = pPage->GetPageEnvelope();

	long lPrintImgWidth, lPrintImgHeight;
	lPrintImgWidth = long(PageEnv.getWidth()*dpi);
	lPrintImgHeight = long(PageEnv.getHeight()*dpi);

	//�������Ӱ���ļ�
	Geodatabase::RasFileInfo rasInfo;
	//rasInfo.lHeaderLen = 0;
	rasInfo.lWidth = lPrintImgWidth;
	rasInfo.lHeight = lPrintImgHeight;
	rasInfo.lChannelNum = 3;
	//rasInfo.lFormatType = 2;
	rasInfo.lDataType = (long)Geodatabase::BDT_BYTE;
	//rasInfo.lByteOrder = 0;
	rasInfo.lXSize = lPrintImgWidth;
	rasInfo.lYSize = lPrintImgHeight;
	Geodatabase::IRasterDatasetPtr pRasPrintImg = CreatePrintImg(csPrintImgPath, rasInfo);


	//���浱ǰ��ͼλ��
	Display::VIEW_POSITION bakPos = pPageLayout->GetDisplay()->GetDisplayTransformation().GetViewPosition();

	//����Page���趨����
	pPageLayout->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(1.0/dpi);

	//��ȡ��ǰ���ڴ�С�������Ӧ�ĵ���Χ�ߴ�
	Display::VIEW_POSITION curPos = pPageLayout->GetDisplay()->GetDisplayTransformation().GetViewPosition();
	double viewExtWidth, viewExtHeight;
	viewExtWidth = (curPos.GetViewBound().right - curPos.GetViewBound().left)/dpi;
	viewExtHeight = (curPos.GetViewBound().bottom - curPos.GetViewBound().top)/dpi;

	//ȷ���ֿ�Ĵ�С,ÿ��ֻ��1��1һ��������
	long lBlockWidth, lBlockHeight;
	lBlockHeight = pLayoutCtrl->GetSizeY()-100 > 256 ? pLayoutCtrl->GetSizeY()-100:256;
	lBlockWidth = pLayoutCtrl->GetSizeX()-100 > 256 ? pLayoutCtrl->GetSizeX()-100:256;

	//ȷ���ֿ����Ŀ
	long  lHeightNum,lWidthNum;
	if(lPrintImgHeight%lBlockHeight)
		lHeightNum = lPrintImgHeight / lBlockHeight+1;
	else
		lHeightNum=	lPrintImgHeight / lBlockHeight;

	if(lPrintImgWidth%lBlockWidth)
		lWidthNum = lPrintImgWidth / lBlockWidth+1;
	else
		lWidthNum = lPrintImgWidth / lBlockWidth;


	//�����ʾ������ӡ��Ӱ��
	CString csBmpFileName;//bmp��ʱ�ļ�����
	MakeTempFileName (csBmpFileName, ".bmp");
	::DeleteFile(csBmpFileName);
	
	char szBmpFileName[_MAX_PATH] = "";
	strcpy(szBmpFileName, csBmpFileName);

	GEOMETRY::geom::Envelope stDrawExtent;
	double minx, maxx, miny, maxy; 

	long lstartRow = 1;
	long lstartCol = 1;
	long lIndexWidth,lIndexHeight;
	long lProWidth,lProHeight;
	for(lIndexHeight = 0; lIndexHeight < lHeightNum; lIndexHeight ++)
	{
		lProHeight=lBlockHeight;
		if((lIndexHeight+1)*lBlockHeight>lPrintImgHeight)
		{
			lProHeight=(lPrintImgHeight-lIndexHeight*lBlockHeight);
			maxy=PageEnv.getMaxY()-lIndexHeight*lBlockHeight/dpi;
			miny=PageEnv.getMinY();
			lstartRow = 1 +lIndexHeight *  lBlockHeight;
		}
		else
		{
			maxy=PageEnv.getMaxY()-lIndexHeight*lBlockHeight/dpi;
			miny=PageEnv.getMaxY()-(lIndexHeight+1)*lBlockHeight/dpi;
			lstartRow = 1 +lIndexHeight *  lBlockHeight;
		}

		for(lIndexWidth = 0; lIndexWidth < lWidthNum; lIndexWidth ++)
		{
			lProWidth=lBlockWidth;

			if((lIndexWidth+1)*lBlockWidth>lPrintImgWidth)
			{
				lProWidth=(lPrintImgWidth-lBlockWidth * lIndexWidth);
				maxx = PageEnv.getMaxX();
				minx = PageEnv.getMinX() + lIndexWidth * lBlockWidth / dpi;
				lstartCol = 1 + lBlockWidth * lIndexWidth;
			}
			else
			{
				maxx = PageEnv.getMinX() + (lIndexWidth + 1) * lBlockWidth / dpi;
				minx = PageEnv.getMinX() + lIndexWidth * lBlockWidth / dpi;
				lstartCol = 1 + lBlockWidth * lIndexWidth;
			}

			//���µ�ǰ������ʾ
			double centerx = (minx+maxx)/2;
			double centery = (miny+maxy)/2;
			stDrawExtent.init(centerx - viewExtWidth/2, centerx + viewExtWidth/2, centery - viewExtHeight/2, centery + viewExtHeight/2);
			pPageLayout->GetDisplay()->GetDisplayTransformation().FitViewBound(stDrawExtent);
			pLayoutCtrl->UpdateControl();



			//�����ֿ�bitmap����bitmap����bmp��ʽ��ʱ�ļ�
			HDC pageLayoutDC = (HDC)pPageLayout->GetDisplay()->GetDrawDC()->GetSafeHdc();
			HDC tmpDC = ::CreateCompatibleDC(pageLayoutDC);
			CDC* dcWrite = CDC::FromHandle(tmpDC);
			HBITMAP tmpBitmap = ::CreateCompatibleBitmap(pageLayoutDC, lProWidth, lProHeight);
			HBITMAP oldBitmap = (HBITMAP)dcWrite->SelectObject(tmpBitmap);
			long displayMinx, displayMiny;
			pPageLayout->GetDisplay()->GetDisplayTransformation().ConvertGeoToDisplay(minx, maxy,displayMinx, displayMiny);
			::BitBlt(dcWrite->GetSafeHdc(), 0,0,lProWidth,lProHeight,pageLayoutDC,displayMinx,displayMiny,SRCCOPY );

			if(!SaveBmp( (HBITMAP)tmpBitmap,szBmpFileName ))
			{
				::DeleteFile(szBmpFileName);
				return;
			}
			dcWrite->SelectObject(oldBitmap);
			dcWrite->DeleteDC();



			//��bmp��ʽ��ʱ�ļ��������Ӱ���ļ�
			Geodatabase::IWorkspace *pWorkspace =CRasterWSFactory::GetInstance()->OpenFromFile(szBmpFileName);
			if(!pWorkspace)
			{
				MessageBox(NULL,"������ʧ�ܣ�","��ʾ",MB_OK);
				return;
			}

			Geodatabase::IRasterDatasetPtr pRasTmpBmp =pWorkspace->OpenRasterDataset(szBmpFileName);
			if(!pRasTmpBmp)
			{
				MessageBox(NULL,"������ʧ�ܣ�","��ʾ",MB_OK);
				return;
			}

			BYTE *pbyBuffer = new BYTE [lProWidth * lProHeight];	//������
			for(int j = 1; j <= 3; j ++)
			{	
				if(!pRasTmpBmp->DataReadBand(j, 1, 1, lProWidth, lProHeight, lProWidth, lProHeight,pbyBuffer))
				{		
					delete []pbyBuffer;
					return;
				}

				if(!pRasPrintImg->DataWriteBand(j, lstartCol, lstartRow, lProWidth, lProHeight, pbyBuffer))
				{
					delete []pbyBuffer;
					return;
				}
			}

			pRasTmpBmp.reset();
			delete []pbyBuffer;
			::DeleteFile(szBmpFileName);
		}
	}

	pPageLayout->GetDisplay()->GetDisplayTransformation().SetViewPosition(bakPos);
}
Geodatabase::IRasterDatasetPtr CPrintToImageCmd::CreatePrintImg(CString csPrintImgPath, Geodatabase::RasFileInfo rasInfo)
{
	Geodatabase::IWorkspace *pWorkspace =CRasterWSFactory::GetInstance()->OpenFromFile(csPrintImgPath);
	if(!pWorkspace)
	{
		return NULL;
	}

	if(!pWorkspace->CreateRasterDataset(csPrintImgPath,&rasInfo))
		return NULL;

	return pWorkspace->OpenRasterDataset(csPrintImgPath,false);
}


////////////////////////////////////////////////////////////////////////
static BOOL MakeTempFileName(CString &csTempFileName,CString extType)
{
	CString csTempPath = "";

	char szTempPath[_MAX_PATH] = "";
	char szTemp[_MAX_PATH] = "";
	char szDriver[_MAX_DRIVE] = "";
	char szDir[_MAX_DIR] = "";


	GetModuleFileName (::AfxGetApp()->m_hInstance, szTemp, MAX_PATH);
	_splitpath(szTemp, szDriver, szDir, NULL, NULL);
	_makepath(szTempPath, szDriver, szDir, NULL, NULL);

	if(strlen(szTempPath) == 0)
	{
		csTempPath = "c:\\Temp";	
	}
	else
	{
		csTempPath.Format("%s", szTempPath);
		if(csTempPath.ReverseFind('\\') > 0 )
			csTempPath = csTempPath.Left(csTempPath.ReverseFind('\\'));
		csTempPath = csTempPath + "\\Temp";
	}



	//BOOL bExist = FALSE;
	//BOOL bDirectory = FALSE;

	//TT_FileIsExist(csTempPath, &bExist);
	//TT_FileIsDirectory(csTempPath, &bDirectory);
	//if (!bExist || !bDirectory)
	//{
	//	if (!::CreateDirectory(csTempPath, NULL))
	//	{
	//		return FALSE;
	//	}

	//}


	if(csTempPath == "")
	{
		return FALSE;
	}

	char szTempFileName[_MAX_PATH] = "";

//LOOP:
//	if ( !TT_FileGetTempName(csTempPath, "vm", extType, szTempFileName) )
//		return FALSE;
//
//	bExist = TRUE;
//	TT_FileIsExist(szTempFileName, &bExist);
//	if (bExist)
//		goto LOOP;

	csTempFileName = csTempPath;//szTempFileName;
	csTempFileName+=extType;
	return TRUE;
}



}