#ifndef _CDC_h
#define _CDC_h

#define MAX_COUNT 5000

namespace Display
{

	class DISPLAY_DLL CDC
	{
	public:

		CDC();

		CDC(const CDC& DC);

		CDC& operator = (const CDC& toDC);

		virtual ~CDC();

	public:
		/**
		* ��¡DC
		* @return ����¡�ɹ��򷵻�DC
		*/
		Display::CDC* CloneDC();

		/**
		* �ͷſ�¡DC
		* @param destDC �ͷſ�¡��DC
		*/
		static void ReleaseCloneDC(Display::CDC *destDC);

		/**
		* ���û���
		* @param hDC �������
		* @param lWidth �������
		* @param lHeight �����߶�
		*/
		void SetDC( long hDC, long lWidth , long lHeight );

		/**
		* @alias ɾ������
		*/
		void DelObj();

		/**
		* @alias �õ�DC�Ŀ��
		*/
		long GetDCWidth();				 

		/**
		* @alias �õ�DC�ĸ߶�
		*/
		long GetDCHeight();		

		/**
		* ѡ�����
		* @param handle ��ʾ���
		*/
		DISPLAY_HANDLE SelectObject(DISPLAY_HANDLE handle);

		/**
		* ѡ��RGN
		* @param handle ��ʾ���
		*/
		DISPLAY_HANDLE SelectRGN(DISPLAY_HANDLE handle);

		/**
		* ɾ��RGN
		* @param handle ��ʾ���
		*/
		void DeleteRGN(DISPLAY_HANDLE handle);

		/**
		* �Ƴ����
		* @param handle ���
		*/
		void RemoveHandle( void* handle);

		/**
		* ���HDC���
		* @return ���ɹ��򷵻ؾ��
		*/
		long GetSafeHdc();

		/*
		* ���Bitmap
		* @return ���ɹ��򷵻�bitmap
		*/
		HBITMAP& GetBitmap(DRAW_CONTENT drawcontent = drawAll);

		/**
		* ��ʼ��ʾ
		*/
		void BeginDisplay();

		/**
		* ������ʾ
		*/
		void EndDisplay();

		/**
		* ��������
		* @param lHeight �����߶�
		* @param lWidth �������
		*/
		void CreateExDC( long lHeight, long lWidth );

		/**
		* 
		* @param pDC ����
		*/
		void CreateCompatibleDC( Display::CDC *pDC);

		void CreateCompatibleBitmap( Display::CDC *pDC,long lWidth, long lHeight);


		//λͼ����
	public:
		/**
		* դ��͸����������
		* @param dcDest Ŀ��CtoDC
		* @param PointDest Ŀ���ṹ
		* @param wDest Ŀ��߶� 
		* @param wDest Ŀ��߶�
		* @param PointSrc Դ��ṹ
		* @param wSrc Դ���
		* @param hSrc Դ�߶�
		* @param UINT uTransparentColor ͸����ɫ
		*/
		void TransparentBlt( CDC * dcDest,  INT_POINT PointDest,int wDest, int hDest,
			DIS_POINT PointSrc,  int wSrc,int hSrc,unsigned long Color );

		/**
		* ѡ��λͼ 
		*/
		void SelectBitmap(DRAW_CONTENT drawcontent = drawAll);

		void CacheBitmap(long lWidth, long lHeight);

		void AttachBitmap(DISPLAY_HANDLE bitmapHandle , long lWidth , long lHeight );

		/**
		* ���ļ���ȡλͼ
		* @param strFile �ļ���
		* @param bPNG ��Ϊtrue��Ϊ32λλͼ
		* @param nLens
		*/
		void * LoadImageFromFile( std::string strFile, bool & bPNG ,int & nLens);

		/**
		* �����ݿ��ж�ȡλͼ
		* @param pBitmapInfo λͼ��Ϣ
		*/
		void  LoadImageFromBuffer( void * pBitmapInfo ); 

		/**
		* ��λͼ���ݴ浽�ڴ���
		* @param pBITMAPINFO λͼ��Ϣ
		* @param nLens
		*/
		void* SaveFromBuffer( void* pBITMAPINFO , int & nLens );

		/**
		* ��ֵͼƬ�ı���ɫ(r=�죬g=�̣�b=��)
		* @param r ��
		* @param g ��
		* @param b ��
		* @return �����óɹ��򷵻�Ϊtrue
		*/
		bool SetBGColor(BYTE r,BYTE g,BYTE b);

		/**
		* ��ֵͼƬ��ǰ��ɫ(r=�죬g=�̣�b=��)
		* @param r ��
		* @param g ��
		* @param b ��
		* @return �����óɹ��򷵻�Ϊtrue
		*/
		bool SetFGColor(BYTE r,BYTE g,BYTE b);


		/**
		* ͸����ʾ
		*/
		void AlphaBlend( CDC * dcDest,  DIS_POINT PointDest,int wDest, int hDest,
			DIS_POINT PointSrc,  int wSrc,int hSrc, unsigned char AlphaVal = 255,unsigned char AlphaFormat = 1);

		/**
		* ���λͼ
		*/
		void Destroy();	

		/**
		* ��ֵͼƬ��ǰ��ɫ(r=�죬g=�̣�b=��)
		* @param dcDest Ŀ��CtoDC
		* @param PointDest Ŀ���ṹ
		* @param nWidthDest Ŀ����
		* @param nHeightDest Ŀ��߶�
		* @param PointSrc Դ��ṹ
		* @param nWidthSrc Դ���
		* @param nHeightSrc Դ�߶�
		* @param uSrcColor ԭʼ��ɫ,COLORREF����
		* @param uDestColor Ŀ����ɫ,COLORREF����
		*/
		void ConvertColorBlt( CDC  *dcDest,   
			DIS_POINT PointDest,	
			int nWidthDest,     
			int nHeightDest,    
			DIS_POINT PointSrc,	
			int nWidthSrc,      
			int nHeightSrc,     
			UINT uSrcColor,		
			UINT uDestColor		
			);

		/** 
		* ����͸������Ϊ��ɫ����������Ϊ��ɫ������λͼ
		* @param dcDest Ŀ��CtoDC
		* @param PointSrc Ŀ��ṹ
		* @param cx ��X����
		* @param cy ��Y����
		* @param PointSrc Դ��ṹ
		* @param unsigned long rop դ�����㷽ʽ
		*/
		void BitBlt( CDC *dcDest,  DIS_POINT PointDest,  int cx,  int cy, 
			DIS_POINT PointSrc,unsigned long rop = SRCCOPY );

		/**
		* դ�����쿽������
		* @param dcDest Ŀ��CtoDC
		* @param PointDest Ŀ���ṹ
		* @param wDest Ŀ��߶� 
		* @param wDest Ŀ��߶�
		* @param PointSrc Դ��ṹ
		* @param wSrc Դ���
		* @param hSrc Դ�߶�
		* @param unsigned long rop դ�����㷽ʽ
		*/
		void StretchBlt( CDC *dcDest,  DIS_POINT PointDest, int wDest, int hDest, 
			DIS_POINT PointSrc,  int wSrc,  int hSrc,unsigned long rop = SRCCOPY);


		/**
		* ͸��ɫ��ͼ
		* @param dcDest Ŀ��CtoDC
		* @param x Ŀ��DC����ʼ��X
        * @param y Ŀ��DC����ʼ��Y
		* @param wDest Ŀ��߶� 
		* @param wDest Ŀ��߶�
		* @param x1 ԴDC����ʼ��X
		* @param y1 ԴDC����ʼ��Y
		* @param wSrc Դ���
		* @param hSrc Դ�߶�
		* @param backColor ͸��ɫ
		*/
		void TransparentBlt( CDC *dcDest,  int x, int y,int wDest, int hDest,
			int x1, int y1, int wSrc,int hSrc,unsigned long backColor );


		/**
		* �õ�λͼ��Ϣ
		* @param Image_Info ͼ����Ϣ
		* @param void * BitmapData λͼ����
		*/
		void GetImageInfo( IMAGE_INFO & Image_Info ,void * BitmapData ); 

		/**
		* �ͷ�λͼ���ݿ�
		* @param pBitmapInfo λͼ��Ϣ
		*/
		void FreeImageBuffer( void * pBitmapInfo );				

		/**
		* ����λͼ���ݿ�
		* @param BufferSize ���峤��
		*/
		void * NewImageBuffer( int BufferSize );	


		/**
		* �õ���ǰͼƬ����ɫ��
		* @param Bitmapdata λͼ����
		*/
		void * GetBitmapColor( void * Bitmapdata );		 

		/**
		* ��ס������
		* @param PixelBitCount ����λ��
		*/
		void* LockBuffer(short &PixelBitCount);

		/**
		* ����
		* @param data ����
		*/
		void UnlockBuffer(void * data);

//ͼ�λ��ƺ���
	public:

		/**
		* ������ʾ����
		* @param font
		*/
		DISPLAY_HANDLE CreateFont(const DIS_FONT &font);

		/**
		* ���ƶ������
		* @param points ����
		* @param count ����θ���
		*/
		void DrawPolyLines(long &points,long count);

		/**
		* ���ƶ����
		* @param count ����
		* @param points ����
		*/
		void DrawPolygon(long lCount,long &dPoints);			//����

		/**
		* @alias ���û�ˢ 
		*/
		DISPLAY_HANDLE CreateBrush(const BRUSH_STYLE &style);

		/**
		* @alias ���û���
		*/
		DISPLAY_HANDLE CreatePen(const LINE_STYLE &style);

		/**
		* @alias ���òü������ 
		*/
		DISPLAY_HANDLE CreateClipPolygon(const DIS_POLYGON &polygon);

		/**
		* @alias ���òü������ 
		*/
		DISPLAY_HANDLE CreateClipArcPolygon(const DIS_ARCPOLYGON *pArcPolygon);
		/**
		* @alias �����ü���Բ��Բ 
		*/
		DISPLAY_HANDLE CreateClipEllipse(const DIS_RECT &rect);

		/**
		* @alias �����ü����� 
		*/
		DISPLAY_HANDLE CreateClipRect(const DIS_RECT& rect);

		/**
		* @alias ���òü����� 
		*/
		DISPLAY_HANDLE CreateExtRegion(DISPLAY_HANDLE handle , XFORM form);
		/**
		* @alias ��������βü��� 
		*/
		DISPLAY_HANDLE CreatePolygonRgn(CONST DIS_POINT *lppt, int cPoints, int fnPolyFillMode );
		/**
		* @alias ����ˢ�� 
		*/
		DISPLAY_HANDLE CreateSolidBrush(unsigned long color);
		/**
		* @alias ���滭��ԭ����
		*/
		void SaveOldObj();

		/**
		* @alias ��ԭ����ԭ���ò�ɾ���������
		*/
		void LoadOldObj();

		/**
		* �ƶ�����ǰ��
		* @param point ��ǰ��
		*/
		void MoveTo(INT_POINT &point);

		/**
		* �ƶ���һ��
		* @param x ���X����
		* @param y ���Y����
		*/
		void MoveTo(int x , int y);

		/**
		* ���ߵ���ǰ��
		* @param x ���X����
		* @param y ���Y����
		*/
		void LineTo(int x ,int y);

		/** 
		* @alias ��Bezier����
		*/
		void PolyBezierTo(DIS_POINT* points , unsigned long cCount);

		/** 
		* @alias ����ǰ��ɫ
		*/
		void SetFGColor(unsigned long lColor);

		/** 
		* @alias ���ñ���ɫ
		*/
		void SetBGColor(unsigned long lColor);

		/** 
		* @alias �õ�ǰ��ɫ
		*/
		unsigned long  GetFGColor();

		/** 
		* @alias �õ�����ɫ
		*/
		unsigned long  GetBGColor();

		/** 
		* @alias ������ǰ��ǰ��ɫ
		*/
		void SetOldFGColor();

		/** 
		* @alias ������ǰ�ı���ɫ
		*/
		void SetOldBGColor();

		/**
		* �õ��ü���ľ�������Ŀ��Ϊ�˽��вü�����ڲ����
		* @param rect ��������
		* @param DISPLAY_HANDLE handle
		*/
		DIS_RECT& GetClipRegionBox(DIS_RECT& rect,DISPLAY_HANDLE handle);

		/**
		* ������������ϵ
		* @param float angle �Ƕ�
		* @param float scalex 
		* @param float scaley
		* @param const long OffsetX ƫ��X����
		* @param const long OffsetY ƫ��Y����
		*/
		XFORM SetWorldTransform(float angle, float scalex, float scaley, const long OffsetX, const long OffsetY);

		/**
		* ��ԭ��������ϵ
		* @param flag
		*/
		void SetWorldTransformBack(XFORM flag);

		/** 
		* �������߶ȺͿ��
		*/
		void GetFontInfo(long &lWidth,long &lHeight,LPCTSTR wChar,int num);

		/**
		* ���ñ���ģʽ��
		* @param bkMode ͸����͸��
		*/
		void SetBGMode(BK_MODE bkMode);


		/************************************************************************/
		/*���Ƶ�																*/
		/************************************************************************/
		/**
		* ���Ƶ�
		* @param point ��
		* @param lColor ��ɫֵ
		*/
		void DrawPoint(DIS_POINT &point,unsigned long lColor);

		void DrawCharPoint(DIS_POINT& point,const wchar_t &wChar,int num);

		/**
		* ���Ƶ����Χ����
		* @param pOffSet ƫ��
		* @param wStr 
		*/
		void DrawCharMask(DIS_POINT pOffSet,LPCTSTR wStr);	

		/**
		* ���Ƶ�ĸ߼���Χ����
		* @param DIS_POLYGON polygon �����
		* @param LPCSTR wStr
		*/
		void DrawCharExtMask(DIS_POLYGON polygon,LPCSTR wStr);		

		/************************************************************************/
		/*������																*/
		/************************************************************************/
		/**
		* �����߶�
		* @param from ���
		* @param to �յ�
		*/
		void DrawLine(DIS_POINT &from,DIS_POINT &to);					

		/**
		* �������� 
		* @param line ��
		*/
		void DrawPolyLines(const DIS_LINE &line);					

		/**
		* ���ƻ�
		* @param rect ��������
		* @param arc ��
		*/
		void DrawArc(DIS_RECT &rect,DisEndPoint &arc);				

		/**
		* ����Bezier����
		* @param line ��
		*/
		void DrawPolyBezier(DIS_BEZIER &line);	

		/**
		* ����Bezier����
		* @param line ��
		*/
		void DrawPolyBezier(long &points,long count);

		/**
		* ���ƶ����
		* @param polygon �����
		*/
		void DrawPolygon(DIS_POLYGON &polygon);

		/**
		* ���ƴ����ζ���εı߽�
		* @param pArcPolygon �����
		*/
		void DrawArcPolygon(DIS_ARCPOLYGON *pArcPolygon);

		/************************************************************************/
		/*���ƶ����                                                            */
		/************************************************************************/
		/**
		* ���ƾ��α߿�
		* @param rect ��������
		*/
		void DrawRect(DIS_RECT &rect);	


		/**
		* ����Բ�Ǿ��α߿�
		* @param rect ��������
		*/
		void DrawRoundRect(DIS_RECT &rect,DIS_ELLIPSE &ellipse);


		/**
		* ��������
		* @param rect
		* @param pie
		*/
		void DrawPie(DIS_RECT &rect,DisEndPoint &pie);

		/**
		* ����Բ,ֻ������Բ�߽�
		* @param rect ��������
		*/
		void DrawEllipse(DIS_RECT &rect);

		/**
		* ��Բ,ֻ����Բ�߽�
		* @param circle Բ
		*/
		void DrawCircle(DIS_CIRCLE &circle);

		/**
		* @alias ���ü����� 
		*/
		void FillRgn(DISPLAY_HANDLE hRgn , DISPLAY_HANDLE hBrush );

		/**
		* @alias ������ 
		*/
		void FillRect(DIS_RECT &rect);	

		/**
		* @alias ������ 
		*/
		void FillPie(DIS_RECT &rect,DisEndPoint &pie);	

		/**
		* @alias �����Բ�� 
		*/
		void FillEllipse(DIS_RECT &rect);				

		/**
		* @alias ���Բ�� 
		*/
		void FillCircle(DIS_CIRCLE &circle);			

		/**
		* @alias ���Բ�Ǿ��� 
		*/
		void FillRoundRect(DIS_RECT &rect,DIS_ELLIPSE &ellipse);	

		void FillArcPolygon(DIS_ARCPOLYGON *pArcPolygon);

		/************************************************************************/
		/*��䲢����ͼ��                                                        */
		/************************************************************************/
		void Circle(const DIS_RECT &circle);

		/**
		* ��Բ�Ǿ���
		* @param rect ��������
		* @param ellipse ��Բ
		*/
		void DrawAndFillRoundRect(DIS_RECT &rect,DIS_ELLIPSE &ellipse);

		/**
		* @alias ���Ʋ����������� 
		*/
		void DrawAndFillRect(DIS_RECT &rect);

		/**
		* @alias ���Ʋ���䣿�������� 
		*/
		void DrawAndFillPie(DIS_RECT &rect,DisEndPoint &pie);

		/**
		* @alias ���Ʋ������Բ���� 
		*/
		void DrawAndFillEllipse(DIS_RECT &rect);

		/**
		* @alias ���Ʋ����Բ���� 
		*/
		void DrawAndFillRounDIS_RECT(DIS_RECT &rect,DIS_ELLIPSE &ellipse);

		/**
		* @alias ���Ʋ������������ 
		*/
		void DrawAndFillDiamond(DIS_POINT *points);	

		/************************************************************************/
		/*�ı�                                                                  */
		/************************************************************************/
		/**
		* �����ھ��������еĶ����ı�
		* @param rect ��������
		* @param wStr 
		* @param dwDTFormat
		*/
		void DrawMultiText(DIS_RECT &rect,LPTSTR wStr,unsigned int dwDTFormat);	//

		void DrawText(DIS_RECT &rect,LPTSTR cStr,unsigned int dwDTFormat);

		/**
		* �жϵ��Ƿ����ƶ�������
		* @param point ��
		* @param  handle
		*/
		BOOL IsPTInRegion(DIS_POINT &point,DISPLAY_HANDLE handle);	//

		BOOL IsPTInRect(DIS_RECT &rect,DIS_POINT &point);

		//ת���ַ�������

		/**
		* @alias ����˫�ֽ�����unicode��ת��
		*/
		void ConverChar(LPCWSTR wStr,char *pStore);	

		/**
		* @alias �����жϾ����Ƿ��ھ���������
		*/
		BOOL IsPTInRect(DIS_RECT &rect,INT_POINT &point);	

		/**
		* @alias ���ݵ�ǰCDC�е�dc�õ����������صı���
		*/
		void GetCurrentDCsRateOfPixelAndMillimeter();		

		/**
		* @alias ������Ļdc�õ����������صı���
		*/
		static float GetCreateDCsRateOfPixelAndMillimeter();		

		/**
		* @alias ������غͺ���֮��ı���
		*/
		float GetRateValueOfPixelAndMillimeter();

		/**
		* @alias �������غͺ���֮��ı���
		*/
		void SetRateValueOfPixelAndMillimeter(float rate);

	public:
		/**
		* �ڲ�bitmap֮��Ŀ���
		*/
		void BitBlt( DRAW_CONTENT BmpDest,  int x, int y,  int cx,  int cy, 
			DRAW_CONTENT BmpSrc, int x1, int y1, unsigned long rop = SRCCOPY );

    
		/**
		* �ڲ�bitmap֮���͸������
		*/
		void AlphaBlend( DRAW_CONTENT BmpDest,  DIS_POINT PointDest,  int cx,  int cy, 
			DRAW_CONTENT BmpSrc, DIS_POINT PointSrc,  int x1,  int y1, unsigned char AlphaVal = 255,unsigned char AlphaFormat = 1);

		/**
		* �ڲ�bitmap֮���͸����������
		* @param DRAW_CONTENT Ŀ��bitmap����
		* @param PointDest Ŀ���ṹ
		* @param wDest Ŀ��߶� 
		* @param wDest Ŀ��߶�
		* @param BmpSrc Դbitmap����
		* @param PointSrc Դ��ṹ
		* @param wSrc Դ���
		* @param hSrc Դ�߶�
		* @param UINT uTransparentColor ͸����ɫ
		*/
		void TransparentBlt( DRAW_CONTENT BmpDest,  int x, int y,int wDest, int hDest,
			DRAW_CONTENT BmpSrc,  int x1, int y1, int wSrc,int hSrc,unsigned long backColor );


		/*
		*m_geoBmp,m_geoSelBmp,m_elemBmp,m_dynaBmpˢ��m_hBitmap
		*/
		void BuildBitmap(long content);


		void SelectPrintClipRgn(DIS_RECT* disrect);

		HRGN GetPrintRgn();

	private:

		bool m_bSelfDC;
		bool m_bPNG;
		IMAGE_INFO m_Image_Info;
		long m_lDCWidth, m_lDCHeight;
		float m_fRateOfPixelAndMillimeter;

		HPEN m_hOldPen;
		HBRUSH m_hOldBrush;
		HFONT m_hOlDIS_FONT;
		DISPLAY_HANDLE m_OldRgn;
		unsigned long m_bkOldColor,m_bkColor;
		unsigned long m_fgOldColor,m_fgColor;

		DISPLAY_HANDLE m_PrintRgn;

		//���ƻ�����
		HDC m_hDC;
		HBITMAP m_geoBmp;
		HBITMAP m_geoSelBmp;
		HBITMAP m_elemBmp;
		HBITMAP m_editBmp;
		HBITMAP m_hBitmap;
		HBITMAP m_tempBmp;

		HBITMAP m_hOldBitmap;
		HBITMAP m_hLockBitmap;


	};

}
#endif
