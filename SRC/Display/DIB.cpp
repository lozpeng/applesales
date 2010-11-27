#include "StdAfx.h"
#include "DIB.h"

namespace otDisplay
{

#define RECTWIDTH(rctRect)		(rctRect.right - rctRect.left)
#define RECTHEIGHT(rctRect)		(rctRect.bottom - rctRect.top)

static DWORD  DIBHeight(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;  // pointer to a Win 3.0-style DIB
	LPBITMAPCOREHEADER lpbmc;  // pointer to an other-style DIB

	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	if (IS_WIN30_DIB(lpDIB))
		return lpbmi->biHeight;
	else
		return (DWORD)lpbmc->bcHeight;
}

static WORD  DIBNumColors(LPSTR lpbi)
{
	WORD wBitCount;  // DIB bit count

	if (IS_WIN30_DIB(lpbi))
	{
		DWORD dwClrUsed;

		dwClrUsed = ((LPBITMAPINFOHEADER)lpbi)->biClrUsed;
		if (dwClrUsed != 0)
			return (WORD)dwClrUsed;
	}

	if (IS_WIN30_DIB(lpbi))
		wBitCount = ((LPBITMAPINFOHEADER)lpbi)->biBitCount;
	else
		wBitCount = ((LPBITMAPCOREHEADER)lpbi)->bcBitCount;

	switch (wBitCount)
	{
	case 1:
		return 2;

	case 4:
		return 16;

	case 8:
		return 256;

	default:
		return 0;
	}
}

static WORD  PaletteSize(LPSTR lpbi)
{
	if (IS_WIN30_DIB (lpbi))
		return (WORD)(DIBNumColors(lpbi) * sizeof(RGBQUAD));
	else
		return (WORD)(DIBNumColors(lpbi) * sizeof(RGBTRIPLE));
}

static LPSTR  FindDIBBits(LPSTR lpbi)
{
	return (lpbi + *(LPDWORD)lpbi + PaletteSize(lpbi));
}

CDIB::CDIB(void)
{
    m_lwidth =0;
	m_lheight =0;
	m_lColors =0;
	m_pHeader =NULL;
}

CDIB::~CDIB(void)
{
	Free();
}

bool CDIB::Create(long lWidth, long lHeight, long lColors)
{

	long lDibHeadSize;	// Dib 头大小
	long lDibDataSize;	// Dib 数据大小

	long lBitCount;		// 颜色位面
	long lRowBytes;		// 每一行字节数

	if (0 == lColors)
		lBitCount = 24;
	else if (256 == lColors)
		lBitCount = 8;
	else 
		return false;

	lRowBytes = WIDTHBYTES(lWidth * lBitCount);

	lDibHeadSize = sizeof(BITMAPINFOHEADER) + lColors * sizeof(RGBQUAD);
	lDibDataSize = lRowBytes * lHeight;

	//申请位图大小的内存
	m_pHeader = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT, lDibHeadSize + lDibDataSize);

	LPSTR pDIB;
	pDIB = (LPSTR)::GlobalLock(m_pHeader);

	PBITMAPINFO pDibInfo = (PBITMAPINFO)pDIB;
	pDibInfo->bmiHeader.biSize = (LONG) sizeof(BITMAPINFOHEADER);
	pDibInfo->bmiHeader.biWidth = lWidth;
	pDibInfo->bmiHeader.biHeight = lHeight;
	pDibInfo->bmiHeader.biPlanes = 1;  // It must be 1
	pDibInfo->bmiHeader.biBitCount = (unsigned short)lBitCount;     
	pDibInfo->bmiHeader.biCompression = 0L;
	pDibInfo->bmiHeader.biSizeImage = lDibDataSize;
	pDibInfo->bmiHeader.biXPelsPerMeter = 0L;
	pDibInfo->bmiHeader.biYPelsPerMeter = 0L;
	pDibInfo->bmiHeader.biClrUsed = 0L;
	pDibInfo->bmiHeader.biClrImportant = 0L;

	for (int i = 0; i < lColors; i++)
	{
		pDibInfo->bmiColors[i].rgbRed = (BYTE)i;
		pDibInfo->bmiColors[i].rgbGreen = (BYTE)i;
		pDibInfo->bmiColors[i].rgbBlue = (BYTE)i;
	}

	::GlobalUnlock(m_pHeader);

	m_lColors = lColors;
	m_lwidth = lWidth;
	m_lheight = lHeight;

	return true;
}

bool CDIB::CreateFromBitmap(HBITMAP hBitmap)
{
    Free();

	HDC hdc = ::GetDC (NULL);
	BITMAPINFO * pBMI;
	pBMI = (BITMAPINFO *)malloc (sizeof (BITMAPINFOHEADER)+256*4);
	BITMAPINFOHEADER * pBIH = (BITMAPINFOHEADER *)pBMI;
	pBIH->biSize = sizeof (BITMAPINFOHEADER);
	pBIH->biBitCount = 0;
	pBIH->biPlanes = 1;
	pBIH->biSizeImage = 0;
	pBIH->biXPelsPerMeter = 0;
	pBIH->biYPelsPerMeter = 0;
	pBIH->biClrUsed = 0; 
	pBIH->biClrImportant = 0;

	//获得位图的信息
	int rc = ::GetDIBits(hdc, hBitmap, 0, 0, NULL, pBMI, DIB_RGB_COLORS);
	
	pBIH->biCompression = BI_RGB;   // No compression



	long lDibHeadSize;	// Dib 头大小
	long lDibDataSize;	// Dib 数据大小

	long lBitCount;		// 颜色位面
	long lRowBytes;		// 每一行字节数

	if(pBIH->biBitCount==24 || pBIH->biBitCount==32)
	{
       m_lColors =0;
	}
	else if(pBIH->biBitCount==8)
	{
       m_lColors =256;
	}
	else
	{
		free (pBMI);
		::ReleaseDC(NULL, hdc);
		return false;
	}

	lRowBytes = WIDTHBYTES(pBIH->biWidth * pBIH->biBitCount);

	lDibHeadSize = sizeof(BITMAPINFOHEADER) + m_lColors * sizeof(RGBQUAD);
	lDibDataSize = lRowBytes * pBIH->biHeight;

	//申请位图大小的内存
	m_pHeader = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT, lDibHeadSize + lDibDataSize);

	LPSTR pDIB;
	pDIB = (LPSTR)::GlobalLock(m_pHeader);

	PBITMAPINFO pDibInfo = (PBITMAPINFO)pDIB;
	pDibInfo->bmiHeader.biSize = (LONG) sizeof(BITMAPINFOHEADER);
	pDibInfo->bmiHeader.biWidth = pBIH->biWidth;
	pDibInfo->bmiHeader.biHeight = pBIH->biHeight;
	pDibInfo->bmiHeader.biPlanes = 1;  
	pDibInfo->bmiHeader.biBitCount = pBIH->biBitCount;     
	pDibInfo->bmiHeader.biCompression = 0L;
	pDibInfo->bmiHeader.biSizeImage = lDibDataSize;
	pDibInfo->bmiHeader.biXPelsPerMeter = 0L;
	pDibInfo->bmiHeader.biYPelsPerMeter = 0L;
	pDibInfo->bmiHeader.biClrUsed = 0L;
	pDibInfo->bmiHeader.biClrImportant = 0L;

	for (int i = 0; i < m_lColors; i++)
	{
		pDibInfo->bmiColors[i].rgbRed = (BYTE)i;
		pDibInfo->bmiColors[i].rgbGreen = (BYTE)i;
		pDibInfo->bmiColors[i].rgbBlue = (BYTE)i;
	}

	::GlobalUnlock(m_pHeader);
    
	LPSTR lpData = (LPSTR)::GlobalLock(m_pHeader) + lDibHeadSize;

    //获得位图的数据
	rc = ::GetDIBits (hdc, hBitmap, 0,pBIH->biHeight,lpData,
		pDibInfo, DIB_RGB_COLORS);

	m_lwidth = pBIH->biWidth;
	m_lheight = pBIH->biHeight;

	free (pBMI);
	::ReleaseDC(NULL, hdc);

	return true;

}

bool CDIB::GetImgDataBW(long lChannelNum, long lRow, long lCol, long lWidth, long lHeight, unsigned char *pData)
{
	
	if (lChannelNum <= 0 || lRow <= 0 || lCol <= 0 || lWidth <= 0 || lHeight <= 0)
	{
		
		return false;
	}
	if (NULL == pData)
	{
		
		return false;
	}
	long lIndex = 0;
	LPSTR lpData = NULL;

	long lDibHeadSize;	// Dib 头大小
	long lBitCount;		// 颜色位面
	long lRowBytes;		// 每一行字节数


	LPSTR pDIB;
	pDIB = (LPSTR)::GlobalLock(m_pHeader);

	PBITMAPINFO pDibInfo = (PBITMAPINFO)pDIB;

	lBitCount =pDibInfo->bmiHeader.biBitCount;


	lRowBytes = WIDTHBYTES(m_lwidth * lBitCount);
	lDibHeadSize = sizeof(BITMAPINFOHEADER) + m_lColors * sizeof(RGBQUAD);

	lpData = pDIB + lDibHeadSize;

	int lbyte =3;
	if(lBitCount==32)
	{
		lbyte =4;
	}

	if (256 == m_lColors)
	{
		for (int i = lRow; i < lRow + lHeight; i ++)
		{
			for (int j = lCol; j < lCol + lWidth; j ++)
			{
				pData[lIndex ++] = lpData[lRowBytes * (m_lheight-i) + j - 1];
			}
		}
	}
	else if (0 == m_lColors)
	{
		for (int i = lRow; i < lRow + lHeight; i ++)
		{
			for (int j = lCol; j < lCol + lWidth; j ++)
			{
				pData[lIndex ++] = lpData[lRowBytes * (m_lheight - i) + (j - 1) * lbyte + (lbyte - lChannelNum)];
			}
		}
	}
	::GlobalUnlock((HGLOBAL)m_pHeader);
	return true;
}

void CDIB::Free()
{
	if(m_pHeader)
	{
		::GlobalFree(m_pHeader);
		m_pHeader = NULL;
	}
	m_lwidth =0;
	m_lheight =0;
	m_lColors =0;
}

void CDIB::SetImgDataBW(long lChannelNum, long lRow, long lCol, long lWidth, long lHeight, unsigned char *pData)
{
	if(m_pHeader==NULL)
	{
		return ;
	}
	
	if (lChannelNum <= 0 || lRow <= 0 || lCol <= 0 || lWidth <= 0 || lHeight <= 0)
	{
		return;
	}
	if (NULL == pData)
	{
		return ;
	}
	long lIndex = 0;
	LPSTR lpData = NULL;

	long lDibHeadSize;	// Dib 头大小
	long lBitCount;		// 颜色位面
	long lRowBytes;		// 每一行字节数

	if (0 == m_lColors)
		lBitCount = 24;
	else if (256 == m_lColors)
		lBitCount = 8;
	else 
		return ;
	lRowBytes = WIDTHBYTES(m_lwidth * lBitCount);
	lDibHeadSize = sizeof(BITMAPINFOHEADER) + m_lColors * sizeof(RGBQUAD);

	lpData = (LPSTR)::GlobalLock(m_pHeader) + lDibHeadSize;

	int i,j;
	if (256 == m_lColors)
	{
		for ( i = lRow; i < lRow + lHeight; i ++)
		{
			for ( j = lCol; j < lCol + lWidth; j ++)
			{
				lpData[lRowBytes * (m_lheight- i) + j - 1] = pData[lIndex ++];
			}
		}
	}
	else if (0 ==m_lColors)
	{
		for ( i = lRow; i < lRow + lHeight; i ++)
		{
			for ( j = lCol; j < lCol + lWidth; j ++)
			{
				lpData[lRowBytes * (m_lheight - i) + (j - 1) * 3 + (3 - lChannelNum)] = pData[lIndex ++];
			}
		}
	}
	::GlobalUnlock(m_pHeader);
}

bool CDIB::Draw(long hDC, long lRow, long lCol, long lWidth, long lHeight, RECT rctDest)
{
	if(m_pHeader==NULL)
	{
		return false;
	}
	if (lRow <=0 || lCol <= 0 || lWidth <= 0 || lHeight <= 0)
	{
		
		return false;
	}

	HDC hdc =(HDC)hDC;


	RECT rctSrc;
	rctSrc.left = lCol - 1;  //图象数据的左上角： 列
	rctSrc.top = m_lheight - lRow - lHeight + 1;	 //图象数据的左上角： 行
	rctSrc.right = lCol -1 + lWidth;
	rctSrc.bottom = rctSrc.top + lHeight;

	if ((rctSrc.left > m_lwidth) || (rctSrc.top >m_lheight) || (rctSrc.right >m_lwidth) || (rctSrc.bottom >m_lheight))
	{
		
		return false;
	}

	LPSTR    lpDIBHdr;            // Pointer to BITMAPINFOHEADER
	LPSTR    lpDIBBits;           // Pointer to DIB bits
	BOOL     bSuccess=FALSE;      // Success/fail flag
	HPALETTE hPal=NULL;           // Our DIB's palette
	HPALETTE hOldPal=NULL;        // Previous palette

	
	lpDIBHdr  = (LPSTR)::GlobalLock(m_pHeader);
	lpDIBBits = FindDIBBits(lpDIBHdr);


	::SetStretchBltMode(hdc, COLORONCOLOR);

	//	Determine whether to call StretchDIBits() or SetDIBitsToDevice()
	if ((RECTWIDTH(rctSrc) == RECTWIDTH(rctDest)) && (RECTHEIGHT(rctSrc) == RECTHEIGHT(rctDest)))
		bSuccess = ::SetDIBitsToDevice(hdc,							// hDC
		rctDest.left,					// DestX
		rctDest.top,					// DestY
		RECTWIDTH(rctDest),				// nDestWidth
		RECTHEIGHT(rctDest),			// nDestHeight
		rctSrc.left,					// SrcX
		(int)DIBHeight(lpDIBHdr) -
		rctSrc.top -
		RECTHEIGHT(rctSrc),				// SrcY
		0,								// nStartScan
		(WORD)DIBHeight(lpDIBHdr),		// nNumScans
		lpDIBBits,						// lpBits
		(LPBITMAPINFO)lpDIBHdr,			// lpBitsInfo
		DIB_RGB_COLORS);				// wUsage
	else
		bSuccess = ::StretchDIBits(hdc,						// hDC
		rctDest.left,				// DestX
		rctDest.top,					// DestY
		RECTWIDTH(rctDest),			// nDestWidth
		RECTHEIGHT(rctDest),			// nDestHeight
		rctSrc.left,					// SrcX
		rctSrc.top,					// SrcY
		RECTWIDTH(rctSrc),			// wSrcWidth
		RECTHEIGHT(rctSrc),			// wSrcHeight
		lpDIBBits,					// lpBits
		(LPBITMAPINFO)lpDIBHdr,		// lpBitsInfo
		DIB_RGB_COLORS,				// wUsage
		SRCCOPY);					// dwROP

	::GlobalUnlock(m_pHeader);
	return bSuccess;
}

bool CDIB::GetColors(long *plColors)
{
	if(NULL == plColors)
		return false;

	*plColors = m_lColors;

	return true;

}

bool CDIB::SetPalette(unsigned char *pucRed, unsigned char *pucGreen, unsigned char *pucBlue)
{
	LPSTR pDIB;
	pDIB = (LPSTR)::GlobalLock(m_pHeader);
	PBITMAPINFO pDibInfo = (PBITMAPINFO)pDIB;

	long lColor;
	GetColors(&lColor);

	for (int i=0; i<lColor;i++)
	{
		pDibInfo->bmiColors[i].rgbRed = pucRed[i];
		pDibInfo->bmiColors[i].rgbGreen = pucGreen[i];
		pDibInfo->bmiColors[i].rgbBlue = pucBlue[i];
	}

	::GlobalUnlock(m_pHeader);

	return true;

}


bool CDIB::GetPalette(unsigned char *pucRed, unsigned char *pucGreen, unsigned char *pucBlue)
{
	LPSTR pDIB;
	pDIB = (LPSTR)::GlobalLock(m_pHeader);
	PBITMAPINFO pDibInfo = (PBITMAPINFO)pDIB;

	long lColor;
	GetColors(&lColor);

	for (int i = 0; i < lColor; i++)
	{
		pucRed[i] = pDibInfo->bmiColors[i].rgbRed;
		pucGreen[i] = pDibInfo->bmiColors[i].rgbGreen;
		pucBlue[i] = pDibInfo->bmiColors[i].rgbBlue;
	}

	::GlobalUnlock(m_pHeader);

	return true;

}

}//namespace otDisplay
