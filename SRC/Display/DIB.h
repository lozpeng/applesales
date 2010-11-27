#ifndef _DIB_h
#define _DIB_h


namespace Display
{
/********************************************************************************
* CDIB��װ���豸�޹�λͼ�Ľṹ������դ�����ݵĻ���
*********************************************************************************/
class DISPLAY_DLL CDIB
{
public:
	CDIB(void);
	virtual ~CDIB(void);

public:
	/**
	* ����DIB�Ľṹ
	* @param lWidth λͼ�Ŀ�
	* @param lHeight λͼ�ĸ�
    * @param lColors λͼ����ɫ���ԣ�0ΪRGB,256Ϊ�Ҷ�ͼ��
	*/
	bool Create(long lWidth, long lHeight, long lColors);
    
	/**
	* �ͷ�λͼ���ڴ�
	* 
	*/
	void Free();

	/**
	* ���λͼ����
	* @param lChannelNum ���κţ�R 1,G 2,B 3
	* @param lRow ��ʼ�к�,��1��ʼ
	* @param lCol ��ʼ�к�,��1��ʼ
	* @param lWidth ���ݿ�
	* @param lHeight ���ݸ�
	* @param pData Ҫ����դ������
	*/
	void SetImgDataBW(long lChannelNum, long lRow, long lCol, long lWidth, long lHeight, unsigned char *pData);

	/**
	* ��λͼ���Ƶ�DC��
	* @param hDC Ŀ��DC
	* @param lRow ��ʼ�к�,��1��ʼ
	* @param lCol ��ʼ�к�,��1��ʼ
	* @param lWidth ���ݿ�
	* @param lHeight ���ݸ�
	* @param rctDest ���Ƶ�Ŀ��DC�ľ�������
	*/
	bool Draw( long hDC, long lRow, long lCol, long lWidth, long lHeight, RECT rctDest);

	/**
    * ����λͼ��ɫ��
	*/
	bool GetColors(long *plColors);


	/**
    * ����λͼ��ɫ��
	*/
	bool SetPalette(unsigned char *pucRed, unsigned char *pucGreen, unsigned char *pucBlue);

	/**
	* ���λͼ��ɫ��
    */
	bool GetPalette(unsigned char *pucRed, unsigned char *pucGreen, unsigned char *pucBlue);

	long GetWidth() const{return m_lwidth;}

	long GetHeight() const {return m_lheight;}

	/**
	* ��λͼ�������DIB�Ľṹ
	* @param hbitmap λͼ
	*/
    bool CreateFromBitmap(HBITMAP hbitmap);

    bool GetImgDataBW(long lChannelNum, long lRow, long lCol, long lWidth, long lHeight, unsigned char *pData);

private:
	long m_lwidth;
	long m_lheight;
	long m_lColors;
	//DIB��ͷ�ṹ
	void *m_pHeader;

};

}

#endif
