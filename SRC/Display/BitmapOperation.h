//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  9527
// ʱ�䣺  2008/11/27
// ������  GDI�����
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

		static bool SetBGColor( HBITMAP& bitmap, BYTE r, BYTE g, BYTE b );//��ֵͼƬ�ı���ɫ(r=�죬g=�̣�b=��)

		static bool SetFGColor( HBITMAP& bitmap, BYTE r, BYTE g, BYTE b );//��ֵͼƬ��ǰ��ɫ(r=�죬g=�̣�b=��)

		static HBITMAP LoadIMG( void * lPBITMAPINFO );//���ڴ��ȡͼƬ

		static void * LoadIMG( std::string strFile, bool & bPng ,HBITMAP & bitmap, int & Lens); //���ļ���ȡͼ��

		static void * ConvertColor( HBITMAP& bitmap, int Bits ,void * bitmapData);//ת��λ���

		static void * SaveToBuffer( HBITMAP bitmap, int & nLens );//��ͼƬ�浽�ڴ���

		static void GetImageInfo( IMAGE_INFO & Image_Info ,void * BitmapData ); //��λͼ��λ��ȡ���ȡ��߶ȡ���ɫ�塢��ɫ�����ݳ���

		static void * GetBitmapColor( void * Bitmapdata );		  //�õ���ǰͼƬ����ɫ��

	private:

		static HPALETTE BuildOctreePalette(HANDLE hImage, UINT nMaxColors, UINT nColorBits);//����8������ɫ��

		static void AddColor (NODE**, BYTE, BYTE, BYTE, UINT, UINT, UINT*, NODE**);//�����ɫ

		static NODE* CreateNode (UINT, UINT, UINT*, NODE**);//�����ڵ�

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