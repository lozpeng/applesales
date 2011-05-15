#pragma once
#include "DisplayHeader.h"
#include "IFillSymbol.h"
#include "CDC.h"
#include "IArchive.h"


namespace Display{
class DISPLAY_DLL CPicFillSymbol :public IFillSymbol
{
public:
	CPicFillSymbol();

	CPicFillSymbol(const CPicFillSymbol& toPicFillSymbol);

	CPicFillSymbol& operator = (const CPicFillSymbol& toPicFillSymbol);

	~CPicFillSymbol();

	SYMBOL_TYPE GetType();	//得到符号类型	

	

	void SetReverseColor(bool bReverseColor);//反转颜色//二值时可使用

	bool GetReverseColor();

	virtual void Draw(void* pObject);//绘制函数

	void SetBGColor(unsigned long nBGcolor);//设置背景色

	void SetTransparecyColor(unsigned long nTransparecyColor);//设置掩盖色
	
	unsigned long GetBGColor();//得到背景色

	unsigned long GetTransparecyColor();//得到掩盖色
	
	void SetWidthScale (float Scale);		//设置符号横向比例

	float GetWidthScale ();		//得到符号横向比例

	void SetFileName(std::string cFilename);

	//得到位图路径
	std::string GetFileName() const {return m_cPicPath;}

	void SetHeightScale(float Scale);//设置竖向比例
	
	float GetHeightScale();//得到竖向比例
	
	void SetOffsetXY( float OffsetX , float OffsetY);//设置偏移
	
	void SetSeparationXY(float SeparationX , float SeparationY);//设置间隔
	
	float GetOffsetX() ;

	float GetOffsetY() ;//得到偏移
	
	float GetSeparationX();  

	float GetSeparationY();//得到间隔
	
	void SetAngle(float Angle);

	float GetAngle();

	virtual void Zoom(float rate);

	virtual void ClearDC();

public:

	virtual void SelectDC(Display::CDC * pDC);

	virtual void SetReadyDraw();

	virtual void SetProperties(const char* PropertyName , const _variant_t& PropertyValue);

	virtual _variant_t GetProperties(const char* PropertyName);			//得到当前符号的属性配置
protected:

	void DrawPic(DIS_POINT & Destpoint, long destW, long destH);

protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();

private:
	unsigned long m_lBackGroundColor,m_lTransparecyColor;//背景色，透明色
	long m_nSrcW;											//图像原始宽度
	long m_nSrcH;											//图像原始高度  
	bool m_bReverseColor;									//是否反转颜色
	bool m_bPng;											//是png吗
	Display::CDC  m_MemDC;										//内存DC
	float m_fScaleX,m_fScaleY,m_fAngle;						//储存X,Y长宽比例,角度
    long m_lDestW,m_lDestH;									//目标宽度，高度
	long m_OffsetX,m_OffsetY;								//X,Y偏移量
	long m_SeparationX,m_SeparationY;						//位图间距
	float m_fOffsetX , m_fOffsetY;							
	float m_fSeparationX , m_fSeparationY;
	float m_fZoom;
	void * m_bitmapData;									//图像数据
	int m_bitmapDataLens;									//图像数据长度
	int m_bpp;                                              //图像位深度
	bool m_bSetFileName;									//是否读取过
	std::string m_cPicPath;							//储存图片路径
public:

    virtual void serialization(SYSTEM::IArchive & ar);

};

typedef SYSTEM::CSmartPtr<CPicFillSymbol> IPicFillSymbolPtr;
}

