#ifndef _DIB_h
#define _DIB_h


namespace Display
{
/********************************************************************************
* CDIB封装了设备无关位图的结构，用于栅格数据的绘制
*********************************************************************************/
class DISPLAY_DLL CDIB
{
public:
	CDIB(void);
	virtual ~CDIB(void);

public:
	/**
	* 创建DIB的结构
	* @param lWidth 位图的宽
	* @param lHeight 位图的高
    * @param lColors 位图的颜色属性，0为RGB,256为灰度图像
	*/
	bool Create(long lWidth, long lHeight, long lColors);
    
	/**
	* 释放位图的内存
	* 
	*/
	void Free();

	/**
	* 填充位图数据
	* @param lChannelNum 波段号，R 1,G 2,B 3
	* @param lRow 起始行号,从1开始
	* @param lCol 起始列号,从1开始
	* @param lWidth 数据宽
	* @param lHeight 数据高
	* @param pData 要填充的栅格数据
	*/
	void SetImgDataBW(long lChannelNum, long lRow, long lCol, long lWidth, long lHeight, unsigned char *pData);

	/**
	* 将位图绘制到DC上
	* @param hDC 目标DC
	* @param lRow 起始行号,从1开始
	* @param lCol 起始列号,从1开始
	* @param lWidth 数据宽
	* @param lHeight 数据高
	* @param rctDest 绘制到目标DC的矩形区域
	*/
	bool Draw( long hDC, long lRow, long lCol, long lWidth, long lHeight, RECT rctDest);

	/**
    * 返回位图颜色数
	*/
	bool GetColors(long *plColors);


	/**
    * 设置位图调色板
	*/
	bool SetPalette(unsigned char *pucRed, unsigned char *pucGreen, unsigned char *pucBlue);

	/**
	* 获得位图调色板
    */
	bool GetPalette(unsigned char *pucRed, unsigned char *pucGreen, unsigned char *pucBlue);

	long GetWidth() const{return m_lwidth;}

	long GetHeight() const {return m_lheight;}

	/**
	* 从位图句柄创建DIB的结构
	* @param hbitmap 位图
	*/
    bool CreateFromBitmap(HBITMAP hbitmap);

    bool GetImgDataBW(long lChannelNum, long lRow, long lCol, long lWidth, long lHeight, unsigned char *pData);

private:
	long m_lwidth;
	long m_lheight;
	long m_lColors;
	//DIB的头结构
	void *m_pHeader;

};

}

#endif
