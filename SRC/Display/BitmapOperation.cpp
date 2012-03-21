#include "StdAfx.h"
#include "BitmapOperation.h"
//#include "alm.h"
Display::CBitmapOperation::CBitmapOperation(void)
{
}

Display::CBitmapOperation::~CBitmapOperation(void)
{
}
bool Display::CBitmapOperation::SetFGColor( HBITMAP &bitmap, BYTE r, BYTE g, BYTE b )
{
	
			if( bitmap == NULL )
			{
				//OTLOG(eLog,"Error: Handle to bitmap is invalid");
				return false;
			}

			HANDLE hImg ;
			hImg = DIBSectionToDIB( bitmap );//通过HBITMAP句柄得到位图数据
			LPBYTE m_lp = ( LPBYTE ) hImg;
			LPBITMAPINFO lpbitmap = (LPBITMAPINFO) m_lp;//转换成LPBITMAPINFO结构

			if( lpbitmap->bmiHeader.biBitCount != 1)
			{
				//OTLOG(eLog,"Error: not 2 bit ");
				return false;
			}

			//修改调色板
			LPBYTE lp=(LPBYTE)lpbitmap;
			lpbitmap->bmiColors[0].rgbRed = r;
			lpbitmap->bmiColors[0].rgbGreen = g;
			lpbitmap->bmiColors[0].rgbBlue = b;
			lpbitmap->bmiColors[0].rgbReserved = 0;

			//把修改过的数据转换成新的HBITMAP
			bitmap = DIBToDIBSection( m_lp );
			return true;
}
bool Display::CBitmapOperation::SetBGColor( HBITMAP &bitmap, BYTE r, BYTE g, BYTE b )
{
	
		if( bitmap == NULL )
		{
			//OTLOG(eLog,"Error: Handle to bitmap is invalid");
			return false;
		}

		HANDLE hImg ;
		hImg = DIBSectionToDIB( bitmap );//通过HBITMAP句柄得到位图数据
		LPBYTE m_lp = ( LPBYTE ) hImg;
		LPBITMAPINFO lpbitmap = (LPBITMAPINFO) m_lp;//转换成LPBITMAPINFO结构


		if( lpbitmap->bmiHeader.biBitCount != 1)
		{
			//OTLOG(eLog,"Error: not 2 bit ");
			return false;
		}

		//修改调色板
		LPBYTE lp=(LPBYTE)lpbitmap;
			lpbitmap->bmiColors[1].rgbRed=r;
			lpbitmap->bmiColors[1].rgbGreen=g;
			lpbitmap->bmiColors[1].rgbBlue=b;
			lpbitmap->bmiColors[1].rgbReserved=0;

		//把修改过的数据转换成新的HBITMAP
			bitmap = DIBToDIBSection( m_lp );
			return true;
}

HPALETTE Display::CBitmapOperation::CreateDIBPalette(LPBYTE lpbi) 
{ 
	
		LPLOGPALETTE        lpPal;        
	HANDLE              hLogPal = NULL;        
	HPALETTE            hPal = NULL;   
	int                 i, wNumColors;
	LPBITMAPINFO        lpbmi;          
	LPBITMAPCOREINFO    lpbmc;      
	BOOL                bWinStyleDIB;   
	if (! lpbi) 
	{
		//OTLOG(eLog,"Error:Handle to DIB is invalid");
		return NULL;
	}
	lpbmi = (LPBITMAPINFO)lpbi; 

	lpbmc = (LPBITMAPCOREINFO)lpbi; 

	wNumColors = DIBNumColors(lpbi); //通过数据得到位深度

	bWinStyleDIB = IS_WIN30_DIB(lpbi); 
	if (wNumColors) 
	{
		hLogPal = (HANDLE)malloc( sizeof(LOGPALETTE) + 
			sizeof(PALETTEENTRY) * wNumColors); //分配调色板数据空间

		if (!hLogPal) 
		{
			free(hLogPal);				//释放空间
			hLogPal = NULL;
			//OTLOG(eLog,"Error: not enough memory");
			return NULL;
		}	

		lpPal = (LPLOGPALETTE)hLogPal; 

		lpPal->palVersion = VERSION; 
		lpPal->palNumEntries = wNumColors; 
		
		for (i = 0; i < wNumColors; i++) 
		{ 
			if (bWinStyleDIB)//选择BITMAPINFO结构或BITMAPCOREINFO结构
			{ 
				lpPal->palPalEntry[i].peRed = lpbmi->bmiColors[i].rgbRed; 
				lpPal->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen; 
				lpPal->palPalEntry[i].peBlue = lpbmi->bmiColors[i].rgbBlue; 
				lpPal->palPalEntry[i].peFlags = lpbmi->bmiColors[i].rgbReserved; 
			} 
			else 
			{ 
				lpPal->palPalEntry[i].peRed = lpbmc->bmciColors[i].rgbtRed; 
				lpPal->palPalEntry[i].peGreen = lpbmc->bmciColors[i].rgbtGreen; 
				lpPal->palPalEntry[i].peBlue = lpbmc->bmciColors[i].rgbtBlue; 
				lpPal->palPalEntry[i].peFlags = 0; 
			} 
		} 

		hPal = CreatePalette(lpPal); //创建调色板句柄
		free(hLogPal);				//释放空间
	} 
	return hPal;
} 

HBITMAP Display::CBitmapOperation::DIBToBitmap(HANDLE hDIB, HPALETTE hPal) 
{ 
	
		LPBYTE      lpDIBHdr, lpDIBBits; 
	HBITMAP     hBitmap;            
	HDC         hDC;              
	HPALETTE    hOldPal = NULL;



	if (!hDIB) 
	{
		//OTLOG(eLog,"Error:Handle to DIB is invalid");
		return NULL;
	}



	lpDIBHdr = (LPBYTE)hDIB; 



	lpDIBBits = FindDIBBits(lpDIBHdr); //找到位图数据开始位置



	hDC = GetDC(NULL);  //得到DC
	if (!hDC) 
	{ 
		//OTLOG(eLog,"Error:Handle to DC is invalid");
		return NULL;
	} 



	if (hPal) 
	{
		hOldPal = SelectPalette(hDC, hPal, FALSE); 
		RealizePalette(hDC); 
	}


	hBitmap = CreateDIBitmap(hDC, 
		(LPBITMAPINFOHEADER)lpDIBHdr, 
		CBM_INIT, 
		lpDIBBits, 
		(LPBITMAPINFO)lpDIBHdr, 
		DIB_RGB_COLORS);//创建与设备无关位图


	if (hOldPal) 
		SelectPalette(hDC, hOldPal, FALSE); 

	ReleaseDC(NULL, hDC); 
} 

HANDLE Display::CBitmapOperation::DIBSectionToDIB(HBITMAP hBitmap)
{
	
	HDC			 hDC = NULL, hSourceDC; 
	HBITMAP		 hOldSourceBitmap;
	HANDLE		 hNewDIB= NULL;
	LPBITMAPINFO lpbmi = NULL; 
	DWORD		 dwSize;
	DIBSECTION   ds;
	DWORD		 dwColorNum; 


	int fails = GetObject(hBitmap, sizeof(DIBSECTION), &ds);//得到与hBitmap相关DIBSECTION结构
	if( fails == NULL)
	{
		//OTLOG(eLog,"Error:Handle to Picture is invalid");
		return NULL;
	}
	dwColorNum = ds.dsBmih.biClrUsed; 
	if (dwColorNum == 0 && ds.dsBmih.biBitCount <= 8) 
		dwColorNum = 1 << ds.dsBmih.biBitCount;


	dwSize = sizeof(BITMAPINFOHEADER) + (dwColorNum * sizeof(RGBQUAD)) + ds.dsBmih.biSizeImage;//计算位图数据大小
	hNewDIB = ( HANDLE )malloc( dwSize );
	if (! hNewDIB)
	{
	   //	free(hNewDIB);				//释放空间
	   //	hNewDIB = NULL;
		//OTLOG(eLog,"Error:Handle to Picture is invalid");
		return NULL;
	}
	lpbmi = (LPBITMAPINFO)hNewDIB;
	if (! lpbmi)
	{	
		free(hNewDIB);				//释放空间
		hNewDIB = NULL;
		//OTLOG(eLog,"Error:Handle to Picture Info  is invalid");
		return NULL;
	}
	//设置位图头信息
	lpbmi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER ); 
	lpbmi->bmiHeader.biWidth = ds.dsBm.bmWidth; 
	lpbmi->bmiHeader.biHeight = ds.dsBm.bmHeight; 
	lpbmi->bmiHeader.biPlanes = 1; 
	lpbmi->bmiHeader.biBitCount = ds.dsBmih.biBitCount; 
	lpbmi->bmiHeader.biCompression = ds.dsBmih.biCompression; 
	lpbmi->bmiHeader.biSizeImage = ds.dsBmih.biSizeImage; 
	lpbmi->bmiHeader.biXPelsPerMeter = ds.dsBmih.biXPelsPerMeter; 
	lpbmi->bmiHeader.biYPelsPerMeter = ds.dsBmih.biYPelsPerMeter; 
	lpbmi->bmiHeader.biClrUsed = ds.dsBmih.biClrUsed; 
	lpbmi->bmiHeader.biClrImportant = ds.dsBmih.biClrImportant; 


	hDC = GetDC( NULL ); 


	if (! GetDIBits(hDC,
		hBitmap,
		0L,
		(DWORD)ds.dsBm.bmHeight,
		(LPBYTE)lpbmi + (WORD)lpbmi->bmiHeader.biSize + (dwColorNum*sizeof(RGBQUAD)),
		(LPBITMAPINFO)lpbmi, 
		(DWORD)DIB_RGB_COLORS))//得到数据
	{
		free(hNewDIB);				//释放空间
		hNewDIB = NULL;
		ReleaseDC(NULL,hDC);
		//OTLOG( eLog,"Error:Handle to Picture Info is invalid");
		return NULL;
	}


	hSourceDC = CreateCompatibleDC( hDC ); //创建与设备相关DC

	hOldSourceBitmap = (HBITMAP)::SelectObject( hSourceDC, hBitmap ); 


	if( lpbmi->bmiHeader.biBitCount <= 8 ) 
		GetDIBColorTable( hSourceDC, 0, 1 << lpbmi->bmiHeader.biBitCount, lpbmi->bmiColors ); //得到颜色表


	::SelectObject( hSourceDC, hOldSourceBitmap ); 
	DeleteDC( hSourceDC ); 
	ReleaseDC( NULL, hDC );
	return hNewDIB;
}

WORD Display::CBitmapOperation::DIBNumColors(HANDLE hDIB) 
{ 
	LPBYTE lpDIB = (LPBYTE)hDIB;
	WORD wSize = DIBNumColors(lpDIB);
	return wSize;
} 
bool Display::CBitmapOperation::CopyColorTable( LPBITMAPINFO lpTarget, LPBITMAPINFO lpSource, HPALETTE hPalSrc ) 
{ 
	
		switch( lpTarget->bmiHeader.biBitCount ) 
	{ 

		case 8: //八位位图处理方式
			if (hPalSrc)
			{ 
				PALETTEENTRY    pe[256]; 
				UINT            i; 

				GetPaletteEntries( hPalSrc, 0, 256, pe ); //得到调色板数组
				for(i=0;i<256;i++) //循环负值
				{ 
					lpTarget->bmiColors[i].rgbRed = pe[i].peRed; 
					lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen; 
					lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue; 
					lpTarget->bmiColors[i].rgbReserved = 0; 
				} 
			}
			else
			{ 
				if( lpSource->bmiHeader.biBitCount == 8 ) 
				{ 
					memcpy( lpTarget->bmiColors, lpSource->bmiColors, 256*sizeof(RGBQUAD) ); //COPY调色板数据
				} 
				else 
				{ 
					HPALETTE        hPal; 
					HDC            hDC = GetDC( NULL ); 
					PALETTEENTRY    pe[256]; 
					UINT            i; 

					hPal = CreateOctreePalette((LPBYTE)lpSource, 236, 8);//通过八叉树量化算法创建调色板，使图片不失真
					if (! hPal)	            //如果Windowsapi创建调色板
						hPal = CreateHalftonePalette( hDC ); 
					ReleaseDC( NULL, hDC ); 

					GetPaletteEntries( hPal, 0, 256, pe ); 
					DeleteObject( hPal ); //得到调色板数组
					for(i=0;i<256;i++) //循环负值
					{ 
						lpTarget->bmiColors[i].rgbRed = pe[i].peRed; 
						lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen; 
						lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue; 
						lpTarget->bmiColors[i].rgbReserved = pe[i].peFlags; 
					} 
				}
			}
			break; 

		case 4: //四位位图处理方式
			if (hPalSrc)
			{ 
				PALETTEENTRY    pe[16]; 
				UINT            i; 

				GetPaletteEntries( hPalSrc, 0, 16, pe );  //得到调色板数组
				for(i=0;i<16;i++) //循环负值
				{ 
					lpTarget->bmiColors[i].rgbRed = pe[i].peRed; 
					lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen; 
					lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue; 
					lpTarget->bmiColors[i].rgbReserved = 0; 
				} 
			}
			else
			{ 
				if( lpSource->bmiHeader.biBitCount == 4 ) 
				{ 
					memcpy( lpTarget->bmiColors, lpSource->bmiColors, 16*sizeof(RGBQUAD) ); 
				} 
				else 
				{ 
					HPALETTE        hPal; 
					PALETTEENTRY    pe[256]; 
					UINT            i; 

					hPal = (HPALETTE)GetStockObject( DEFAULT_PALETTE ); //得到调色板句柄
					GetPaletteEntries( hPal, 0, 16, pe ); //得到调色板数组
					for(i=0;i<16;i++) //循环负值
					{ 
						lpTarget->bmiColors[i].rgbRed = pe[i].peRed; 
						lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen; 
						lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue; 
						lpTarget->bmiColors[i].rgbReserved = pe[i].peFlags; 
					}
				} 
			}
			break; 
		case 1: //二值处理方式默认是黑白色位图
			lpTarget->bmiColors[0].rgbRed = 0; 
			lpTarget->bmiColors[0].rgbGreen = 0; 
			lpTarget->bmiColors[0].rgbBlue = 0; 
			lpTarget->bmiColors[0].rgbReserved = 0; 
			lpTarget->bmiColors[1].rgbRed = 255; 
			lpTarget->bmiColors[1].rgbGreen = 255; 
			lpTarget->bmiColors[1].rgbBlue = 255; 
			lpTarget->bmiColors[1].rgbReserved = 0; 
			break; 
		case 32: 
		case 24: 
		case 16: 
		default: 
			break; 
	}
	return true;
} 
HANDLE Display::CBitmapOperation::ConvertDIBFormat(HANDLE hDIB, UINT nbpp, HPALETTE hPalSrc=NULL)
{
	
		LPBITMAPINFO lpbmi = NULL; 
	LPBYTE       lpSourceBits, lpTargetBits, lpResult; 
	HDC			 hDC = NULL, hSourceDC, hTargetDC; 
	HBITMAP      hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap; 
	DWORD        dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize, dwColorNum; 
	HANDLE		 hNewDIB;
	DWORD		 dwSize;
	int			 nWidth, nHeight;

	if (! hDIB)
	{
		//OTLOG(eLog,"Error:Handle is invalid");
		return NULL;
	}
	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)hDIB;
	if (! lpSrcDIB)
	{
		//OTLOG(eLog,"Error:Handle is invalid");
		return NULL;
	}
	nWidth = lpSrcDIB->bmiHeader.biWidth;
	nHeight = lpSrcDIB->bmiHeader.biHeight;
	if(nbpp==0)
	{
		nbpp=24;

	}
	if (nbpp <= 8) 
		dwColorNum = 1 << nbpp;
	else
		dwColorNum = 0;
	//设置位图头信息
	dwTargetHeaderSize = sizeof( BITMAPINFO ) + ( dwColorNum * sizeof( RGBQUAD ) ); 
	lpbmi = (LPBITMAPINFO)malloc( dwTargetHeaderSize ); 
	lpbmi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER ); 
	lpbmi->bmiHeader.biWidth = nWidth; 
	lpbmi->bmiHeader.biHeight = nHeight; 
	lpbmi->bmiHeader.biPlanes = 1; 
	lpbmi->bmiHeader.biBitCount = nbpp; 
	lpbmi->bmiHeader.biCompression = BI_RGB; 
	lpbmi->bmiHeader.biSizeImage = 0; 
	lpbmi->bmiHeader.biXPelsPerMeter = 0; 
	lpbmi->bmiHeader.biYPelsPerMeter = 0; 
	lpbmi->bmiHeader.biClrUsed = 0; 
	lpbmi->bmiHeader.biClrImportant = 0; 

	if( ! CopyColorTable( lpbmi, (LPBITMAPINFO)lpSrcDIB, hPalSrc ) ) //复制颜色表
	{ 
		free(lpbmi);
		//OTLOG(eLog,"Error:to Copy ColorTable is invalid");
		return NULL;
	} 


	hDC = ::GetDC( NULL ); 
	hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); //创建与设备无关位图
	hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); //创建与设备无关位图
	hSourceDC = CreateCompatibleDC( hDC ); 
	hTargetDC = CreateCompatibleDC( hDC ); 

	dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); //得到原数据大小
	dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); //目标数据大小
	memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); //复制原数据到目标数据
	lpbmi->bmiHeader.biSizeImage = dwTargetBitsSize; 

	hOldSourceBitmap = (HBITMAP)::SelectObject( hSourceDC, hSourceBitmap ); 
	hOldTargetBitmap = (HBITMAP)::SelectObject( hTargetDC, hTargetBitmap ); 

	if( lpSrcDIB->bmiHeader.biBitCount <= 8 ) 
		SetDIBColorTable( hSourceDC, 0, 1 << lpSrcDIB->bmiHeader.biBitCount, lpSrcDIB->bmiColors ); //设置原数据颜色表
	if( lpbmi->bmiHeader.biBitCount <= 8 ) 
		SetDIBColorTable( hTargetDC, 0, 1 << lpbmi->bmiHeader.biBitCount, lpbmi->bmiColors ); //设置目标数据颜色表

	::BitBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY ); 

	::SelectObject( hSourceDC, hOldSourceBitmap ); 
	::SelectObject( hTargetDC, hOldTargetBitmap ); 
	DeleteDC( hSourceDC ); 
	DeleteDC( hTargetDC ); 
	ReleaseDC( NULL, hDC ); 

	GdiFlush(); //刷新GDI

	dwSize = dwTargetHeaderSize + dwTargetBitsSize;//得到目标数据大小

	hNewDIB = ( HANDLE )malloc(dwSize);
	lpResult = (LPBYTE)hNewDIB;
	memcpy( lpResult, lpbmi, dwTargetHeaderSize ); 
	memcpy( FindDIBBits( (LPBYTE)lpResult ), lpTargetBits, dwTargetBitsSize ); 


	DeleteObject( hTargetBitmap ); 
	DeleteObject( hSourceBitmap );  
	free(lpbmi);
	//(hNewDIB,0,"Error:Handle to Picture  is invalid") 
	return hNewDIB;
}
WORD Display::CBitmapOperation::DIBNumColors(LPBYTE lpDIB) 
{ 
	
		WORD wBitCount;  

	wBitCount = ((LPBITMAPINFOHEADER)lpDIB)->biBitCount; 
//从位数转换成颜色数（除256以上）
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
	return 0;

} 

DWORD Display::CBitmapOperation::BytesPerLine(LPBYTE lpDIB) 
{ 
	
	//得到一个扫描线的大小
	return WIDTHBYTES(((LPBITMAPINFOHEADER)lpDIB)->biWidth * ((LPBITMAPINFOHEADER)lpDIB)->biPlanes * ((LPBITMAPINFOHEADER)lpDIB)->biBitCount);
	//(WIDTHBYTES(((LPBITMAPINFOHEADER)lpDIB)->biWidth * ((LPBITMAPINFOHEADER)lpDIB)->biPlanes * ((LPBITMAPINFOHEADER)lpDIB)->biBitCount),0,"Error: not scan line") 

} 
LPBYTE Display::CBitmapOperation::FindDIBBits(LPBYTE lpDIB) 
{ 
	
	//查找位图实际数据位置
	return lpDIB + *(LPDWORD)lpDIB + PaletteSize(lpDIB);
	//(lpDIB + *(LPDWORD)lpDIB + PaletteSize(lpDIB),0,"Error:Handle to DIB is invalid") 
} 
WORD Display::CBitmapOperation::PaletteSize(LPBYTE lpDIB) 
{ 
	
		if (IS_WIN30_DIB (lpDIB)) 
		{
			WORD w=(DIBNumColors(lpDIB) * sizeof(RGBQUAD));//计算调色板大小
			return w;
		}
		else 
		{
			WORD w=(DIBNumColors(lpDIB) * sizeof(RGBQUAD));//计算调色板大小
			return w;
		}
		return 0;
		//(0,0,"Error:Handle to DIB is invalid")
} 
HBITMAP Display::CBitmapOperation::DIBToDIBSection(LPBYTE lpDIB) 
{
	
	LPBYTE       lpSourceBits; 
	HDC			 hDC = NULL, hSourceDC; 
	HBITMAP      hSourceBitmap, hOldSourceBitmap; 
	DWORD        dwSourceBitsSize; 

	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)lpDIB;
	if (! lpSrcDIB)
	{
		//OTLOG(eLog,"Error:Handle to Picture Info is invalid");
		return NULL;
	}


	hDC = GetDC( NULL ); 
	hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); //创建与设备无关位图

	if (lpSourceBits == NULL)
	{
		ReleaseDC( NULL, hDC ); 
		return NULL;
	}

	hSourceDC = CreateCompatibleDC( hDC ); 


	dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
	memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 


	hOldSourceBitmap = (HBITMAP)::SelectObject( hSourceDC, hSourceBitmap ); 


	if( lpSrcDIB->bmiHeader.biBitCount <= 8 ) 
		SetDIBColorTable( hSourceDC, 0, 1 << lpSrcDIB->bmiHeader.biBitCount, lpSrcDIB->bmiColors ); //设置原数据颜色表


	::SelectObject( hSourceDC, hOldSourceBitmap ); 
	DeleteDC( hSourceDC ); 
	ReleaseDC( NULL, hDC ); 


	GdiFlush(); 


	//(hSourceBitmap,0,"Error:Handle to DIB is invalid")
	return hSourceBitmap;

} 



HPALETTE Display::CBitmapOperation::CreateOctreePalette(LPBYTE lpDIB, UINT nMaxColors, UINT nColorBits)
{
	
		HANDLE hImage;

	hImage = DIBToDIBSection(lpDIB);//从数据到位图句柄
	if (! hImage)
	{
		DeleteObject( hImage );
		//OTLOG(eLog,"Error:Handle to Picture is invalid");
		return NULL;
	}
	//建立8叉树调色板
	return BuildOctreePalette(hImage, nMaxColors, nColorBits);//,0,"Error:Handle to Palette is invalid")
}


HPALETTE Display::CBitmapOperation::BuildOctreePalette(HANDLE hImage, UINT nMaxColors, UINT nColorBits)
{
	
		DIBSECTION ds;
	int i, j, nPad;
	BYTE* pbBits;
	WORD* pwBits;
	DWORD* pdwBits;
	DWORD rmask, gmask, bmask;
	int rright, gright, bright;
	int rleft, gleft, bleft;
	BYTE r, g, b;
	WORD wColor;
	DWORD dwColor, dwSize;
	LOGPALETTE* plp;
	HPALETTE hPalette;
	NODE* pTree;
	UINT nLeafCount, nIndex;
	NODE* pReducibleNodes[9];
	HDC hdc;    
	BYTE* pBuffer;    
	BITMAPINFO bmi;


	pTree = NULL;
	nLeafCount = 0;
	if (nColorBits > 8) 
	{
		//OTLOG(eLog,"Error:Colorbits > 8 is invalid");
		return NULL;
	}
	for (i=0; i<=(int) nColorBits; i++)
		pReducibleNodes[i] = NULL;


	GetObject (hImage, sizeof (ds), &ds);
	nPad = ds.dsBm.bmWidthBytes - (((ds.dsBmih.biWidth *
		ds.dsBmih.biBitCount) + 7) / 8);

	switch (ds.dsBmih.biBitCount) {

	case 1: 
	case 4: 
	case 8: 
		hdc = GetDC (NULL);        
		pBuffer = new BYTE[ds.dsBmih.biWidth * 3];
		ZeroMemory (&bmi, sizeof (bmi));
		bmi.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = ds.dsBmih.biWidth;
		bmi.bmiHeader.biHeight = ds.dsBmih.biHeight;
		bmi.bmiHeader.biPlanes = 1;        
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;
		for (i=0; i<ds.dsBmih.biHeight; i++) 
		{
			GetDIBits (hdc, (HBITMAP) hImage, i, 1, pBuffer, &bmi,
				DIB_RGB_COLORS);            
			pbBits = pBuffer;
			for (j=0; j<ds.dsBmih.biWidth; j++) 
			{                
				b = *pbBits++;
				g = *pbBits++;                
				r = *pbBits++;
				AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
					pReducibleNodes);
				while (nLeafCount > nMaxColors)
					ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);            
			}        
		}
		delete pBuffer;        
		ReleaseDC (NULL, hdc);        
		break;    

	case 16: 
		if (ds.dsBmih.biCompression == BI_BITFIELDS) {
			rmask = ds.dsBitfields[0];
			gmask = ds.dsBitfields[1];
			bmask = ds.dsBitfields[2];
		}
		else {
			rmask = 0x7C00;
			gmask = 0x03E0;
			bmask = 0x001F;
		}

		rright = GetRightShiftCount (rmask);
		gright = GetRightShiftCount (gmask);
		bright = GetRightShiftCount (bmask);

		rleft = GetLeftShiftCount (rmask);
		gleft = GetLeftShiftCount (gmask);
		bleft = GetLeftShiftCount (bmask);

		pwBits = (WORD*) ds.dsBm.bmBits;
		for (i=0; i<ds.dsBmih.biHeight; i++) {
			for (j=0; j<ds.dsBmih.biWidth; j++) {
				wColor = *pwBits++;
				b = (BYTE) (((wColor & (WORD) bmask) >> bright) << bleft);
				g = (BYTE) (((wColor & (WORD) gmask) >> gright) << gleft);
				r = (BYTE) (((wColor & (WORD) rmask) >> rright) << rleft);
				AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
					pReducibleNodes);
				while (nLeafCount > nMaxColors)
					ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
			}
			pwBits = (WORD*) (((BYTE*) pwBits) + nPad);
		}
		break;

	case 24:
		pbBits = (BYTE*) ds.dsBm.bmBits;
		for (i=0; i<ds.dsBmih.biHeight; i++) {
			for (j=0; j<ds.dsBmih.biWidth; j++) {
				b = *pbBits++;
				g = *pbBits++;
				r = *pbBits++;
				AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
					pReducibleNodes);
				while (nLeafCount > nMaxColors)
					ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
			}
			pbBits += nPad;
		}
		break;

	case 32: 
		if (ds.dsBmih.biCompression == BI_BITFIELDS) {
			rmask = ds.dsBitfields[0];
			gmask = ds.dsBitfields[1];
			bmask = ds.dsBitfields[2];
		}
		else {
			rmask = 0x00FF0000;
			gmask = 0x0000FF00;
			bmask = 0x000000FF;
		}

		rright = GetRightShiftCount (rmask);
		gright = GetRightShiftCount (gmask);
		bright = GetRightShiftCount (bmask);

		pdwBits = (DWORD*) ds.dsBm.bmBits;
		for (i=0; i<ds.dsBmih.biHeight; i++) {
			for (j=0; j<ds.dsBmih.biWidth; j++) {
				dwColor = *pdwBits++;
				b = (BYTE) ((dwColor & bmask) >> bright);
				g = (BYTE) ((dwColor & gmask) >> gright);
				r = (BYTE) ((dwColor & rmask) >> rright);
				AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
					pReducibleNodes);
				while (nLeafCount > nMaxColors)
					ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
			}
			pdwBits = (DWORD*) (((BYTE*) pdwBits) + nPad);
		}
		break;

	default:
		{
			//OTLOG(eLog,"Error:DIB must be 16, 24, or 32-bit");
			return NULL;
		}
	}

	if (nLeafCount > nMaxColors) { 
		DeleteTree (&pTree);
		//OTLOG(eLog,"Error:nLeafCount less than nMaxColors");
		return NULL;
	}


	dwSize = sizeof (LOGPALETTE) + ((nLeafCount - 1) * sizeof (PALETTEENTRY));
	if ((plp = (LOGPALETTE*) HeapAlloc (GetProcessHeap (), 0,
		dwSize)) == NULL) {
			DeleteTree (&pTree);
			//OTLOG(eLog,"Error: not enough memory");
			return NULL;
	}

	plp->palVersion = 0x300;
	plp->palNumEntries = (WORD) nLeafCount;
	nIndex = 0;
	GetPaletteColors (pTree, plp->palPalEntry, &nIndex);
	hPalette = CreatePalette (plp);

	HeapFree (GetProcessHeap (), 0, plp);
	DeleteTree (&pTree);
	return hPalette;//,0,"Error:Handle to Palette is invalid") 
}


void Display::CBitmapOperation::AddColor (NODE** ppNode, BYTE r, BYTE g, BYTE b, UINT nColorBits,
							   UINT nLevel, UINT* pLeafCount, NODE** pReducibleNodes)
{
	
		int nIndex, shift;
	static BYTE mask[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };


	if (*ppNode == NULL)
		*ppNode = CreateNode (nLevel, nColorBits, pLeafCount,
		pReducibleNodes);


	if ((*ppNode)->bIsLeaf) {
		(*ppNode)->nPixelCount++;
		(*ppNode)->nRedSum += r;
		(*ppNode)->nGreenSum += g;
		(*ppNode)->nBlueSum += b;
	}


	else {
		shift = 7 - nLevel;
		nIndex = (((r & mask[nLevel]) >> shift) << 2) |
			(((g & mask[nLevel]) >> shift) << 1) |
			((b & mask[nLevel]) >> shift);
		AddColor (&((*ppNode)->pChild[nIndex]), r, g, b, nColorBits,
			nLevel + 1, pLeafCount, pReducibleNodes);
	}
	
}


NODE* Display::CBitmapOperation::CreateNode (UINT nLevel, UINT nColorBits, UINT* pLeafCount,
								  NODE** pReducibleNodes)
{
	
		NODE* pNode;

	if ((pNode = (NODE*) HeapAlloc (GetProcessHeap (), HEAP_ZERO_MEMORY,
		sizeof (NODE))) == NULL)
	{
		//OTLOG(eLog,"Error: not enough memory");
		return NULL;
	}

	pNode->bIsLeaf = (nLevel == nColorBits) ? TRUE : FALSE;
	if (pNode->bIsLeaf)
		(*pLeafCount)++;
	else { 
		pNode->pNext = pReducibleNodes[nLevel];
		pReducibleNodes[nLevel] = pNode;
	}
	return pNode;//,0,"Error:Pointer to Node is invalid") 
}


void Display::CBitmapOperation::ReduceTree (UINT nColorBits, UINT* pLeafCount, NODE** pReducibleNodes)
{
	
		int i;
	NODE* pNode;
	UINT nRedSum, nGreenSum, nBlueSum, nChildren;


	for (i=nColorBits - 1; (i>0) && (pReducibleNodes[i] == NULL); i--);


	pNode = pReducibleNodes[i];
	pReducibleNodes[i] = pNode->pNext;

	nRedSum = nGreenSum = nBlueSum = nChildren = 0;
	for (i=0; i<8; i++) {
		if (pNode->pChild[i] != NULL) {
			nRedSum += pNode->pChild[i]->nRedSum;
			nGreenSum += pNode->pChild[i]->nGreenSum;
			nBlueSum += pNode->pChild[i]->nBlueSum;
			pNode->nPixelCount += pNode->pChild[i]->nPixelCount;
			HeapFree (GetProcessHeap (), 0, pNode->pChild[i]);
			pNode->pChild[i] = NULL;
			nChildren++;
		}
	}

	pNode->bIsLeaf = TRUE;
	pNode->nRedSum = nRedSum;
	pNode->nGreenSum = nGreenSum;
	pNode->nBlueSum = nBlueSum;
	*pLeafCount -= (nChildren - 1);
	
}


void Display::CBitmapOperation::DeleteTree (NODE** ppNode)
{
	
		int i;

	for (i=0; i<8; i++) {
		if ((*ppNode)->pChild[i] != NULL)
			DeleteTree (&((*ppNode)->pChild[i]));
	}
	HeapFree (GetProcessHeap (), 0, *ppNode);
	*ppNode = NULL;
	
}

void Display::CBitmapOperation::GetPaletteColors (NODE* pTree, PALETTEENTRY* pPalEntries, UINT* pIndex)
{
	
		int i;

	if (pTree->bIsLeaf) {
		pPalEntries[*pIndex].peRed =
			(BYTE) ((pTree->nRedSum) / (pTree->nPixelCount));
		pPalEntries[*pIndex].peGreen =
			(BYTE) ((pTree->nGreenSum) / (pTree->nPixelCount));
		pPalEntries[*pIndex].peBlue =
			(BYTE) ((pTree->nBlueSum) / (pTree->nPixelCount));
		(*pIndex)++;
	}
	else {
		for (i=0; i<8; i++) {
			if (pTree->pChild[i] != NULL)
				GetPaletteColors (pTree->pChild[i], pPalEntries, pIndex);
		}
	}
	
}


int Display::CBitmapOperation::GetRightShiftCount (DWORD dwVal)
{
	
		int i;

	for (i=0; i<sizeof (DWORD) * 8; i++) {
		if (dwVal & 1)
			return i;
		dwVal >>= 1;
	}
	return -1;//(-1,0,"Error: Righ Node is invalid") 
}

int Display::CBitmapOperation::GetLeftShiftCount (DWORD dwVal)
{
	
		int nCount, i;

	nCount = 0;
	for (i=0; i<sizeof (DWORD) * 8; i++) {
		if (dwVal & 1)
			nCount++;
		dwVal >>= 1;
	}
	return (8 - nCount);//,0,"Error: Left Node is invalid")
}

void * Display::CBitmapOperation::GetBitmapColor( void * Bitmapdata )
{
	
	int size = 0;
	PALETTEENTRY pe1[256];
	memset(pe1,204,sizeof(PALETTEENTRY)*256);
	std::vector < unsigned long > arraype;
	LPBYTE m_lp = ( LPBYTE )Bitmapdata;
	if( !m_lp )
	{
		////OTLOG( 0, "Error:Handle to Picture is invalid" )
		return NULL;
	}

	LPBITMAPINFO lpbmi;
	long temp[256];
	long temp1[16];
	
	lpbmi = ( LPBITMAPINFO )m_lp;
	WORD  m_Bitmapbits = lpbmi->bmiHeader.biBitCount;
	HPALETTE m_hPalette;
	DWORD dFAddress = sizeof( BITMAPINFOHEADER ) + ( m_Bitmapbits* sizeof( RGBQUAD ) );
	m_hPalette = CreateDIBPalette( m_lp );

	switch( m_Bitmapbits )
	{

	case 4:
		{
			GetPaletteEntries( m_hPalette, 0, 15, pe1 );

			for( int l = 0; l < 16; l++ )
			{
				temp1[l] = 0;
			}

			for( DWORD i = 0; i < lpbmi->bmiHeader.biSizeImage ;i++ )
			{
				int  b = ( int )*(( m_lp + dFAddress + i ));
				if( b >= 16 )
					b = b >> 4;
				if( b >= 0 )
					temp1[b] += 1;
			}

			for( int j = 0; j < 16; j++ )
			{
				if( temp1[j] == 0 )
				{

					pe1[j].peBlue = pe1[j].peFlags = pe1[j].peGreen = pe1[j].peRed = 204;
				}
			}

			break;
		}
	case 8:
		{
				GetPaletteEntries( m_hPalette, 0, 256, pe1 );
				for( int l = 0; l < 256; l++ )
				 {
					 temp[l] = 0;
				 }
				for( DWORD i = 0;i <= lpbmi->bmiHeader.biSizeImage; i += 8 )
				 {
					 int  b = (int ) * (( m_lp+dFAddress + i ));

					 if( b >= 0 ) 
					 {
						 temp[b] += 1;
					 }

				 }
				int  flat = 14;

				for( int j = 0; j < 256; j++ )
			   {

				  if( temp[j] == 0 ) 
				   {
						pe1[j].peBlue = pe1[j].peFlags = pe1[j].peGreen = pe1[j].peRed = 204;
				   }
			   }
		break;
		}
	default:
		return 0;
	}
	for ( int k = 0; k < 256; k++ )
	{
		if( pe1[k].peFlags != 204 )
		{
			arraype.push_back( RGB( pe1[k].peRed, pe1[k].peGreen, pe1[k].peBlue ));
		}
	}
	unsigned long* parray = new unsigned long[ arraype .size()+1];
	int lens = arraype .size()+1;
	parray[0] = lens - 1;
	for ( int t = 1; t < lens; t++ )
	{
		parray[t] = arraype[ t-1 ]; 
	}
	DeleteObject(m_hPalette);
	return parray;
	//(( void * )parray,0,"Error: Pointer to PALENTRY is invalid")
}




HPALETTE Display::CBitmapOperation::CreateIdentifyPalette(HPALETTE hPalSrc)
{
	
		BOOL bResult = FALSE;
	int i, iSysColors, iPalEntries;
	HPALETTE hPalette, hpalOld;

	if (! hPalSrc)
	{
		//OTLOG(eLog,"Error:Handle to Palette is invalid");
		return NULL;
	}

	hPalette = CopyPalette(hPalSrc);

	HDC hdcScreen = GetDC(NULL);
	
	if (!(GetDeviceCaps(hdcScreen, RASTERCAPS) & RC_PALETTE)) 
	{
		goto abort;
	}

	iSysColors = GetDeviceCaps(hdcScreen, NUMCOLORS);
	iPalEntries = GetDeviceCaps(hdcScreen, SIZEPALETTE);

	if (iSysColors > 256) goto abort;

	SetSystemPaletteUse(hdcScreen, SYSPAL_NOSTATIC);
	SetSystemPaletteUse(hdcScreen, SYSPAL_STATIC);

	hpalOld = ::SelectPalette(hdcScreen,
		hPalette,
		FALSE);
	::RealizePalette(hdcScreen);

	::SelectPalette(hdcScreen, hpalOld, FALSE);


	PALETTEENTRY pe[256];
	GetSystemPaletteEntries(hdcScreen, 
		0,
		iPalEntries,
		pe);


	for (i = 0; i < iSysColors/2; i++) {
		pe[i].peFlags = 0;
	}
	for (; i < iPalEntries-iSysColors/2; i++) {
		pe[i].peFlags = PC_NOCOLLAPSE;
	}
	for (; i < iPalEntries; i++) {
		pe[i].peFlags = 0;
	}


	ResizePalette(hPalette, iPalEntries);


	SetPaletteEntries(hPalette, 0, iPalEntries, pe);
	bResult = TRUE;

abort:
	::ReleaseDC(NULL, hdcScreen);

	return hPalette;
}
HPALETTE Display::CBitmapOperation::CopyPalette(HPALETTE hPalSrc)
{
	
		PLOGPALETTE     plogPal;
	int             iNumEntries=0;
	HPALETTE        hPal;
	HANDLE			h;

	iNumEntries = GetPaletteEntries(hPalSrc, 0, iNumEntries, NULL);
	if (iNumEntries == 0) 
	{
		//OTTRACE("Error:Bits is invalid");
		return NULL;
	}

	h = (HANDLE)malloc( sizeof(DWORD) + sizeof(PALETTEENTRY)*iNumEntries);
	if (! h)
	{
		free(h);
		//OTTRACE("Error:Handle  is invalid");
		return NULL;
	}
	plogPal = (PLOGPALETTE)h;
	if (! plogPal) 
	{
		free(h);
		//OTTRACE("Error:Handle to Palette is invalid");
		return NULL;
	}

	plogPal->palVersion = 0x300;
	plogPal->palNumEntries = (WORD) iNumEntries;
	GetPaletteEntries(hPalSrc, 0, iNumEntries, plogPal->palPalEntry);
	hPal = CreatePalette(plogPal);

	free(h);

	//(hPal;,0,"Error: Handle to Palette is invalid")
	return hPal;
}

void * Display::CBitmapOperation::LoadIMG(std::string strFile, bool & bPng ,HBITMAP & bitmap ,int & Lens)
{
	
	void * bitmapData = NULL ;
	if( strFile.c_str() == NULL )
	{
		//OTLOG(eLog,"Error: CString is invalid");
		return NULL;
	}
	CImage pLoadImg;

	pLoadImg.Load( strFile.c_str() );
	if( pLoadImg.IsNull() )
	{
		 //OTLOG(eLog,"Handle to Palette is invalid");
		 return NULL;
	}
	LPBYTE lp;
	int  nbitCount = pLoadImg.GetBPP();
	bitmap = pLoadImg.Detach();
	lp = ( LPBYTE )SaveToBuffer( bitmap, Lens);
	DeleteObject( bitmap );
    bitmap = DIBToDIBSection( lp );
	
	 if( nbitCount == 32 )
	 {
		 bPng = true;	
	 }
	 else if( nbitCount == 24 )
	 {
		 //不在将24位的位图转换成256色

		/*lp = ( LPBYTE )ConvertColor( bitmap ,8 ,lp);
		LPBITMAPINFO bitmap_info = ( LPBITMAPINFO )lp;
		Lens = sizeof(BITMAPINFOHEADER) + (DIBNumColors( lp ) * sizeof(RGBQUAD))+ bitmap_info->bmiHeader.biSizeImage;*/
	 }
	 else
	 {
		 bitmapData = false;
	 }
	 return lp;
	//(lp,NULL,"Error: Handle to bitmapData is invalid")
}
HBITMAP Display::CBitmapOperation::LoadIMG( void * lPBITMAPINFO)
{	
	
		if( lPBITMAPINFO == NULL )
		{
			//OTLOG(eLog,"Error: lPBITMAPINFO is invalid" );
			return NULL;
		}
		
		LPBYTE lp;
		lp = ( LPBYTE )lPBITMAPINFO; 
		HBITMAP pbitmap = DIBToDIBSection( lp );
	return pbitmap;
	//( pbitmap, 0, "Error: Handle to BITMAPINFO is invalid" )
}
void * Display::CBitmapOperation::ConvertColor( HBITMAP& bitmap, int Bits ,void * bitmapData)
 {
	 
		 if( bitmap == NULL )
		 {
			 //OTLOG(eLog,"Error: HBITMAP is invalid" );
			 return false;
		 }
		 if( Bits == -1 )
		 {
			 //OTLOG(eLog,"Error: Bits is invalid" );
			 return false;
		 }

		HANDLE  hImgt;
		hImgt = ConvertDIBFormat( ( LPBYTE )bitmapData, Bits, NULL );
		bitmap = DIBToDIBSection( ( LPBYTE )hImgt );
		free( bitmapData );

		return hImgt;
	//( hImgt, NULL, "Error: Handle to BITMAPINFO is invalid" )
 }
void* Display::CBitmapOperation::SaveToBuffer( HBITMAP bitmap, int & nLens )
 {
	 

		 if( bitmap == NULL )
		 {
			  //OTLOG(eLog, "Error: HBITMAP is invalid");
			  return NULL;
		 }
		 LPBYTE m_lp;
		 HANDLE hImg;
		 hImg = DIBSectionToDIB( bitmap );

		 if(hImg == NULL)
			return NULL;

		 m_lp = ( LPBYTE )hImg ;
		 LPBITMAPINFO bitmap_info = ( LPBITMAPINFO )m_lp;
		 int wBitCount = bitmap_info->bmiHeader.biBitCount;
		 if( wBitCount > 8 )
		 {
			 wBitCount = 0;
		 }
		 nLens = sizeof(BITMAPINFOHEADER) + (DIBNumColors( hImg ) * sizeof(RGBQUAD))+ bitmap_info->bmiHeader.biSizeImage;

		 if( bitmap_info->bmiHeader.biBitCount == 32 )
		 {
			 int DataLens =  bitmap_info->bmiHeader.biSizeImage /4;
			 for(int i = 0 ; i < DataLens; i++ )
			 {
				 if(bitmap_info->bmiColors[i].rgbReserved == 0 )
				 {
					 bitmap_info->bmiColors[i].rgbBlue = bitmap_info->bmiColors[i].rgbGreen =  bitmap_info->bmiColors[i].rgbRed = 0;
				 }
			 }
		 }

		return m_lp;
	// ((void *) m_lp, NULL , "Error: Handle to BITMAPINFO is invalid" )
 }
 void Display::CBitmapOperation::GetImageInfo( IMAGE_INFO & Image_Info ,void * BitmapData )
 {
	 

		 if( BitmapData == NULL )
		 {
			 //OTLOG(eLog,"Error: HBITMAP is invalid" );
			 return;
		 }
		 LPBITMAPINFO bitmap_info = ( LPBITMAPINFO )BitmapData;
		 Image_Info.lHeight = bitmap_info->bmiHeader.biHeight;
		 Image_Info.lWidth = bitmap_info->bmiHeader.biWidth;
		 Image_Info.lBitCount = bitmap_info->bmiHeader.biBitCount;

     
 }