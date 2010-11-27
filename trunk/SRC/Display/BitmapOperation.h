//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  9527
// 时间：  2008/11/27
// 描述：  GDI库相关
//////////////////////////////////////////////////////////////////////

#ifndef CBITMAPOPERATION_H
#define CBITMAPOPERATION_H

#include "DisplayHeader.h"
#include <atlimage.h>

#define GetDattSizePerLine(biWidth ,bitcount) (biWidth * bitcount + 31 )/8;

namespace Display
{
	class DISPLAY_DLL CBitmapOperation
	{
	public:

		CBitmapOperation(void);

		~CBitmapOperation(void);

		static bool SetBGColor( HBITMAP& bitmap, BYTE r, BYTE g, BYTE b );//二值图片的背景色(r=红，g=绿，b=蓝)

		static bool SetFGColor( HBITMAP& bitmap, BYTE r, BYTE g, BYTE b );//二值图片的前景色(r=红，g=绿，b=蓝)

		static HBITMAP LoadIMG( void * lPBITMAPINFO );//从内存读取图片

		static void * LoadIMG( std::string strFile, bool & bPng ,HBITMAP & bitmap, int & Lens); //从文件读取图像

		static void * ConvertColor( HBITMAP& bitmap, int Bits ,void * bitmapData);//转换位深度

		static void * SaveToBuffer( HBITMAP bitmap, int & nLens );//把图片存到内存中

		static void GetImageInfo( IMAGE_INFO & Image_Info ,void * BitmapData ); //获位图的位深度、宽度、高度、调色板、调色板数据长度

		static void * GetBitmapColor( void * Bitmapdata );		  //得到当前图片的颜色表

	private:

		static HPALETTE BuildOctreePalette(HANDLE hImage, UINT nMaxColors, UINT nColorBits);//建立8叉树调色板

		static void AddColor (NODE**, BYTE, BYTE, BYTE, UINT, UINT, UINT*, NODE**);//添加颜色

		static NODE* CreateNode (UINT, UINT, UINT*, NODE**);//创建节点

		static void ReduceTree (UINT, UINT*, NODE**);

		static void DeleteTree (NODE**);

		static void GetPaletteColors (NODE*, PALETTEENTRY*, UINT*);

		static int GetRightShiftCount (DWORD);

		static int GetLeftShiftCount (DWORD);

		static HPALETTE CreateOctreePalette(LPBYTE lpDIB, UINT nMaxColors, UINT nColorBits);

		static HBITMAP DIBToDIBSection(LPBYTE lpDIB);

		static DWORD BytesPerLine(LPBYTE lpDIB);

		static LPBYTE FindDIBBits(LPBYTE lpDIB) ;

		static WORD PaletteSize(LPBYTE lpDIB);

		static WORD DIBNumColors(LPBYTE lpDIB) ;

		static HANDLE ConvertDIBFormat(HANDLE hDIB, UINT nbpp, HPALETTE hPalSrc);

		static bool CopyColorTable( LPBITMAPINFO lpTarget, LPBITMAPINFO lpSource, HPALETTE hPalSrc );

		static WORD DIBNumColors(HANDLE hDIB) ;

		static HANDLE DIBSectionToDIB(HBITMAP hBitmap);

		static HBITMAP DIBToBitmap(HANDLE hDIB, HPALETTE hPal);

		static HPALETTE CreateIdentifyPalette(HPALETTE hPalSrc);

		static HPALETTE CopyPalette(HPALETTE hPalSrc);

		static HPALETTE CreateDIBPalette(LPBYTE lpbi);

	};
}
#endif