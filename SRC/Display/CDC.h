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
		* 克隆DC
		* @return 若克隆成功则返回DC
		*/
		Display::CDC* CloneDC();

		/**
		* 释放克隆DC
		* @param destDC 释放克隆的DC
		*/
		static void ReleaseCloneDC(Display::CDC *destDC);

		/**
		* 设置画布
		* @param hDC 画布句柄
		* @param lWidth 画布宽度
		* @param lHeight 画布高度
		*/
		void SetDC( long hDC, long lWidth , long lHeight );

		/**
		* @alias 删除对象
		*/
		void DelObj();

		/**
		* @alias 得到DC的宽度
		*/
		long GetDCWidth();				 

		/**
		* @alias 得到DC的高度
		*/
		long GetDCHeight();		

		/**
		* 选择对象
		* @param handle 显示句柄
		*/
		DISPLAY_HANDLE SelectObject(DISPLAY_HANDLE handle);

		/**
		* 选择RGN
		* @param handle 显示句柄
		*/
		DISPLAY_HANDLE SelectRGN(DISPLAY_HANDLE handle);

		/**
		* 删除RGN
		* @param handle 显示句柄
		*/
		void DeleteRGN(DISPLAY_HANDLE handle);

		/**
		* 移除句柄
		* @param handle 句柄
		*/
		void RemoveHandle( void* handle);

		/**
		* 获得HDC句柄
		* @return 若成功则返回句柄
		*/
		long GetSafeHdc();

		/*
		* 获得Bitmap
		* @return 若成功则返回bitmap
		*/
		HBITMAP& GetBitmap(DRAW_CONTENT drawcontent = drawAll);

		/**
		* 开始显示
		*/
		void BeginDisplay();

		/**
		* 结束显示
		*/
		void EndDisplay();

		/**
		* 创建画布
		* @param lHeight 画布高度
		* @param lWidth 画布宽度
		*/
		void CreateExDC( long lHeight, long lWidth );

		/**
		* 
		* @param pDC 画布
		*/
		void CreateCompatibleDC( Display::CDC *pDC);

		void CreateCompatibleBitmap( Display::CDC *pDC,long lWidth, long lHeight);


		//位图函数
	public:
		/**
		* 栅格透明拷贝运算
		* @param dcDest 目标CtoDC
		* @param PointDest 目标点结构
		* @param wDest 目标高度 
		* @param wDest 目标高度
		* @param PointSrc 源点结构
		* @param wSrc 源宽度
		* @param hSrc 源高度
		* @param UINT uTransparentColor 透明颜色
		*/
		void TransparentBlt( CDC * dcDest,  INT_POINT PointDest,int wDest, int hDest,
			DIS_POINT PointSrc,  int wSrc,int hSrc,unsigned long Color );

		/**
		* 选择位图 
		*/
		void SelectBitmap(DRAW_CONTENT drawcontent = drawAll);

		void CacheBitmap(long lWidth, long lHeight);

		void AttachBitmap(DISPLAY_HANDLE bitmapHandle , long lWidth , long lHeight );

		/**
		* 从文件读取位图
		* @param strFile 文件名
		* @param bPNG 若为true则为32位位图
		* @param nLens
		*/
		void * LoadImageFromFile( std::string strFile, bool & bPNG ,int & nLens);

		/**
		* 从数据块中读取位图
		* @param pBitmapInfo 位图信息
		*/
		void  LoadImageFromBuffer( void * pBitmapInfo ); 

		/**
		* 把位图数据存到内存中
		* @param pBITMAPINFO 位图信息
		* @param nLens
		*/
		void* SaveFromBuffer( void* pBITMAPINFO , int & nLens );

		/**
		* 二值图片的背景色(r=红，g=绿，b=蓝)
		* @param r 红
		* @param g 绿
		* @param b 蓝
		* @return 若设置成功则返回为true
		*/
		bool SetBGColor(BYTE r,BYTE g,BYTE b);

		/**
		* 二值图片的前景色(r=红，g=绿，b=蓝)
		* @param r 红
		* @param g 绿
		* @param b 蓝
		* @return 若设置成功则返回为true
		*/
		bool SetFGColor(BYTE r,BYTE g,BYTE b);


		/**
		* 透明显示
		*/
		void AlphaBlend( CDC * dcDest,  DIS_POINT PointDest,int wDest, int hDest,
			DIS_POINT PointSrc,  int wSrc,int hSrc, unsigned char AlphaVal = 255,unsigned char AlphaFormat = 1);

		/**
		* 清除位图
		*/
		void Destroy();	

		/**
		* 二值图片的前景色(r=红，g=绿，b=蓝)
		* @param dcDest 目标CtoDC
		* @param PointDest 目标点结构
		* @param nWidthDest 目标宽度
		* @param nHeightDest 目标高度
		* @param PointSrc 源点结构
		* @param nWidthSrc 源宽度
		* @param nHeightSrc 源高度
		* @param uSrcColor 原始颜色,COLORREF类型
		* @param uDestColor 目标颜色,COLORREF类型
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
		* 生成透明区域为白色，其它区域为黑色的掩码位图
		* @param dcDest 目标CtoDC
		* @param PointSrc 目标结构
		* @param cx 点X坐标
		* @param cy 点Y坐标
		* @param PointSrc 源点结构
		* @param unsigned long rop 栅格运算方式
		*/
		void BitBlt( CDC *dcDest,  DIS_POINT PointDest,  int cx,  int cy, 
			DIS_POINT PointSrc,unsigned long rop = SRCCOPY );

		/**
		* 栅格拉伸拷贝运算
		* @param dcDest 目标CtoDC
		* @param PointDest 目标点结构
		* @param wDest 目标高度 
		* @param wDest 目标高度
		* @param PointSrc 源点结构
		* @param wSrc 源宽度
		* @param hSrc 源高度
		* @param unsigned long rop 栅格运算方式
		*/
		void StretchBlt( CDC *dcDest,  DIS_POINT PointDest, int wDest, int hDest, 
			DIS_POINT PointSrc,  int wSrc,  int hSrc,unsigned long rop = SRCCOPY);


		/**
		* 透明色贴图
		* @param dcDest 目标CtoDC
		* @param x 目标DC的起始点X
        * @param y 目标DC的起始点Y
		* @param wDest 目标高度 
		* @param wDest 目标高度
		* @param x1 源DC的起始点X
		* @param y1 源DC的起始点Y
		* @param wSrc 源宽度
		* @param hSrc 源高度
		* @param backColor 透明色
		*/
		void TransparentBlt( CDC *dcDest,  int x, int y,int wDest, int hDest,
			int x1, int y1, int wSrc,int hSrc,unsigned long backColor );


		/**
		* 得到位图信息
		* @param Image_Info 图像信息
		* @param void * BitmapData 位图数据
		*/
		void GetImageInfo( IMAGE_INFO & Image_Info ,void * BitmapData ); 

		/**
		* 释放位图数据块
		* @param pBitmapInfo 位图信息
		*/
		void FreeImageBuffer( void * pBitmapInfo );				

		/**
		* 分配位图数据块
		* @param BufferSize 缓冲长度
		*/
		void * NewImageBuffer( int BufferSize );	


		/**
		* 得到当前图片的颜色表
		* @param Bitmapdata 位图数据
		*/
		void * GetBitmapColor( void * Bitmapdata );		 

		/**
		* 锁住缓冲区
		* @param PixelBitCount 像素位数
		*/
		void* LockBuffer(short &PixelBitCount);

		/**
		* 解锁
		* @param data 数据
		*/
		void UnlockBuffer(void * data);

//图形绘制函数
	public:

		/**
		* 设置显示字体
		* @param font
		*/
		DISPLAY_HANDLE CreateFont(const DIS_FONT &font);

		/**
		* 绘制多边形组
		* @param points 点组
		* @param count 多边形个数
		*/
		void DrawPolyLines(long &points,long count);

		/**
		* 绘制多边形
		* @param count 个数
		* @param points 点组
		*/
		void DrawPolygon(long lCount,long &dPoints);			//重载

		/**
		* @alias 设置画刷 
		*/
		DISPLAY_HANDLE CreateBrush(const BRUSH_STYLE &style);

		/**
		* @alias 设置画笔
		*/
		DISPLAY_HANDLE CreatePen(const LINE_STYLE &style);

		/**
		* @alias 设置裁减多边形 
		*/
		DISPLAY_HANDLE CreateClipPolygon(const DIS_POLYGON &polygon);

		/**
		* @alias 设置裁减多边形 
		*/
		DISPLAY_HANDLE CreateClipArcPolygon(const DIS_ARCPOLYGON *pArcPolygon);
		/**
		* @alias 创建裁减椭圆或圆 
		*/
		DISPLAY_HANDLE CreateClipEllipse(const DIS_RECT &rect);

		/**
		* @alias 创建裁减矩形 
		*/
		DISPLAY_HANDLE CreateClipRect(const DIS_RECT& rect);

		/**
		* @alias 设置裁减矩形 
		*/
		DISPLAY_HANDLE CreateExtRegion(DISPLAY_HANDLE handle , XFORM form);
		/**
		* @alias 创建多边形裁减体 
		*/
		DISPLAY_HANDLE CreatePolygonRgn(CONST DIS_POINT *lppt, int cPoints, int fnPolyFillMode );
		/**
		* @alias 创建刷子 
		*/
		DISPLAY_HANDLE CreateSolidBrush(unsigned long color);
		/**
		* @alias 保存画布原设置
		*/
		void SaveOldObj();

		/**
		* @alias 还原画布原设置并删除垃圾句柄
		*/
		void LoadOldObj();

		/**
		* 移动到当前点
		* @param point 当前点
		*/
		void MoveTo(INT_POINT &point);

		/**
		* 移动到一点
		* @param x 点的X坐标
		* @param y 点的Y坐标
		*/
		void MoveTo(int x , int y);

		/**
		* 画线到当前点
		* @param x 点的X坐标
		* @param y 点的Y坐标
		*/
		void LineTo(int x ,int y);

		/** 
		* @alias 绘Bezier曲线
		*/
		void PolyBezierTo(DIS_POINT* points , unsigned long cCount);

		/** 
		* @alias 设置前景色
		*/
		void SetFGColor(unsigned long lColor);

		/** 
		* @alias 设置背景色
		*/
		void SetBGColor(unsigned long lColor);

		/** 
		* @alias 得到前景色
		*/
		unsigned long  GetFGColor();

		/** 
		* @alias 得到背景色
		*/
		unsigned long  GetBGColor();

		/** 
		* @alias 设置先前的前景色
		*/
		void SetOldFGColor();

		/** 
		* @alias 设置先前的背景色
		*/
		void SetOldBGColor();

		/**
		* 得到裁剪体的矩形区域，目的为了进行裁剪体的内部填充
		* @param rect 矩形区域
		* @param DISPLAY_HANDLE handle
		*/
		DIS_RECT& GetClipRegionBox(DIS_RECT& rect,DISPLAY_HANDLE handle);

		/**
		* 设置世界坐标系
		* @param float angle 角度
		* @param float scalex 
		* @param float scaley
		* @param const long OffsetX 偏移X坐标
		* @param const long OffsetY 偏移Y坐标
		*/
		XFORM SetWorldTransform(float angle, float scalex, float scaley, const long OffsetX, const long OffsetY);

		/**
		* 还原世界坐标系
		* @param flag
		*/
		void SetWorldTransformBack(XFORM flag);

		/** 
		* 获得字体高度和宽度
		*/
		void GetFontInfo(long &lWidth,long &lHeight,LPCTSTR wChar,int num);

		/**
		* 设置背景模式度
		* @param bkMode 透明或不透明
		*/
		void SetBGMode(BK_MODE bkMode);


		/************************************************************************/
		/*绘制点																*/
		/************************************************************************/
		/**
		* 绘制点
		* @param point 点
		* @param lColor 颜色值
		*/
		void DrawPoint(DIS_POINT &point,unsigned long lColor);

		void DrawCharPoint(DIS_POINT& point,const wchar_t &wChar,int num);

		/**
		* 绘制点的外围轮廓
		* @param pOffSet 偏移
		* @param wStr 
		*/
		void DrawCharMask(DIS_POINT pOffSet,LPCTSTR wStr);	

		/**
		* 绘制点的高级外围轮廓
		* @param DIS_POLYGON polygon 多边形
		* @param LPCSTR wStr
		*/
		void DrawCharExtMask(DIS_POLYGON polygon,LPCSTR wStr);		

		/************************************************************************/
		/*绘制线																*/
		/************************************************************************/
		/**
		* 绘制线段
		* @param from 起点
		* @param to 终点
		*/
		void DrawLine(DIS_POINT &from,DIS_POINT &to);					

		/**
		* 绘制折线 
		* @param line 线
		*/
		void DrawPolyLines(const DIS_LINE &line);					

		/**
		* 绘制弧
		* @param rect 矩形区域
		* @param arc 弧
		*/
		void DrawArc(DIS_RECT &rect,DisEndPoint &arc);				

		/**
		* 绘制Bezier曲线
		* @param line 线
		*/
		void DrawPolyBezier(DIS_BEZIER &line);	

		/**
		* 绘制Bezier曲线
		* @param line 线
		*/
		void DrawPolyBezier(long &points,long count);

		/**
		* 绘制多边形
		* @param polygon 多边形
		*/
		void DrawPolygon(DIS_POLYGON &polygon);

		/**
		* 绘制带弧段多边形的边界
		* @param pArcPolygon 多边形
		*/
		void DrawArcPolygon(DIS_ARCPOLYGON *pArcPolygon);

		/************************************************************************/
		/*绘制多边形                                                            */
		/************************************************************************/
		/**
		* 绘制矩形边框
		* @param rect 矩形区域
		*/
		void DrawRect(DIS_RECT &rect);	


		/**
		* 绘制圆角矩形边框
		* @param rect 矩形区域
		*/
		void DrawRoundRect(DIS_RECT &rect,DIS_ELLIPSE &ellipse);


		/**
		* ？？？？
		* @param rect
		* @param pie
		*/
		void DrawPie(DIS_RECT &rect,DisEndPoint &pie);

		/**
		* 画椭圆,只绘制椭圆边界
		* @param rect 矩形区域
		*/
		void DrawEllipse(DIS_RECT &rect);

		/**
		* 画圆,只绘制圆边界
		* @param circle 圆
		*/
		void DrawCircle(DIS_CIRCLE &circle);

		/**
		* @alias 填充裁减区域 
		*/
		void FillRgn(DISPLAY_HANDLE hRgn , DISPLAY_HANDLE hBrush );

		/**
		* @alias 填充矩形 
		*/
		void FillRect(DIS_RECT &rect);	

		/**
		* @alias 填充矩形 
		*/
		void FillPie(DIS_RECT &rect,DisEndPoint &pie);	

		/**
		* @alias 填充椭圆形 
		*/
		void FillEllipse(DIS_RECT &rect);				

		/**
		* @alias 填充圆形 
		*/
		void FillCircle(DIS_CIRCLE &circle);			

		/**
		* @alias 填充圆角矩形 
		*/
		void FillRoundRect(DIS_RECT &rect,DIS_ELLIPSE &ellipse);	

		void FillArcPolygon(DIS_ARCPOLYGON *pArcPolygon);

		/************************************************************************/
		/*填充并绘制图形                                                        */
		/************************************************************************/
		void Circle(const DIS_RECT &circle);

		/**
		* 画圆角矩形
		* @param rect 矩形区域
		* @param ellipse 椭圆
		*/
		void DrawAndFillRoundRect(DIS_RECT &rect,DIS_ELLIPSE &ellipse);

		/**
		* @alias 绘制并填充矩形区域 
		*/
		void DrawAndFillRect(DIS_RECT &rect);

		/**
		* @alias 绘制并填充？？？区域 
		*/
		void DrawAndFillPie(DIS_RECT &rect,DisEndPoint &pie);

		/**
		* @alias 绘制并填充椭圆区域 
		*/
		void DrawAndFillEllipse(DIS_RECT &rect);

		/**
		* @alias 绘制并填充圆区域 
		*/
		void DrawAndFillRounDIS_RECT(DIS_RECT &rect,DIS_ELLIPSE &ellipse);

		/**
		* @alias 绘制并填充菱形区域 
		*/
		void DrawAndFillDiamond(DIS_POINT *points);	

		/************************************************************************/
		/*文本                                                                  */
		/************************************************************************/
		/**
		* 绘制在矩形区域中的多行文本
		* @param rect 矩形区域
		* @param wStr 
		* @param dwDTFormat
		*/
		void DrawMultiText(DIS_RECT &rect,LPTSTR wStr,unsigned int dwDTFormat);	//

		void DrawText(DIS_RECT &rect,LPTSTR cStr,unsigned int dwDTFormat);

		/**
		* 判断点是否在制定区域中
		* @param point 点
		* @param  handle
		*/
		BOOL IsPTInRegion(DIS_POINT &point,DISPLAY_HANDLE handle);	//

		BOOL IsPTInRect(DIS_RECT &rect,DIS_POINT &point);

		//转变字符集类型

		/**
		* @alias 用于双字节码向unicode码转换
		*/
		void ConverChar(LPCWSTR wStr,char *pStore);	

		/**
		* @alias 用于判断矩形是否在矩形区域内
		*/
		BOOL IsPTInRect(DIS_RECT &rect,INT_POINT &point);	

		/**
		* @alias 根据当前CDC中的dc得到毫米与像素的比例
		*/
		void GetCurrentDCsRateOfPixelAndMillimeter();		

		/**
		* @alias 创建屏幕dc得到毫米与像素的比例
		*/
		static float GetCreateDCsRateOfPixelAndMillimeter();		

		/**
		* @alias 获得像素和毫米之间的比例
		*/
		float GetRateValueOfPixelAndMillimeter();

		/**
		* @alias 设置像素和毫米之间的比例
		*/
		void SetRateValueOfPixelAndMillimeter(float rate);

	public:
		/**
		* 内部bitmap之间的拷贝
		*/
		void BitBlt( DRAW_CONTENT BmpDest,  int x, int y,  int cx,  int cy, 
			DRAW_CONTENT BmpSrc, int x1, int y1, unsigned long rop = SRCCOPY );

    
		/**
		* 内部bitmap之间的透明叠加
		*/
		void AlphaBlend( DRAW_CONTENT BmpDest,  DIS_POINT PointDest,  int cx,  int cy, 
			DRAW_CONTENT BmpSrc, DIS_POINT PointSrc,  int x1,  int y1, unsigned char AlphaVal = 255,unsigned char AlphaFormat = 1);

		/**
		* 内部bitmap之间的透明拷贝运算
		* @param DRAW_CONTENT 目标bitmap类型
		* @param PointDest 目标点结构
		* @param wDest 目标高度 
		* @param wDest 目标高度
		* @param BmpSrc 源bitmap类型
		* @param PointSrc 源点结构
		* @param wSrc 源宽度
		* @param hSrc 源高度
		* @param UINT uTransparentColor 透明颜色
		*/
		void TransparentBlt( DRAW_CONTENT BmpDest,  int x, int y,int wDest, int hDest,
			DRAW_CONTENT BmpSrc,  int x1, int y1, int wSrc,int hSrc,unsigned long backColor );


		/*
		*m_geoBmp,m_geoSelBmp,m_elemBmp,m_dynaBmp刷新m_hBitmap
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

		//绘制缓冲区
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
