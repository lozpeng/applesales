#ifndef _IMGPROFUNCTION_H_
#define _IMGPROFUNCTION_H_

#include "RasterRGBRender.h"
#include <list>
using std::list;




namespace Carto{

//定义处理功能的类型
#define CARTO_IMGPRO_ADJUST_HUE						1001	//色调调整
#define CARTO_IMGPRO_ADJUST_SATURATION				1002	//饱和度调整
#define CARTO_IMGPRO_ADJUST_LUT                     1003    //记录LUT表变化
#define CARTO_IMGPRO_ADJUST_LUM                     1004    //明度调整

#define UNDEFINED		(-1.0)
#define BOUND(value, min, max) (value<min ? min : (value>max ? max : value))
#define ROTATE(value) (value<0 ? (value+360) : (value>=360 ? (value-360) : value))

void HLStoRGB(double h, double l, double s, BYTE* r, BYTE* g, BYTE* b);
void RGBtoHLS(BYTE r, BYTE g, BYTE b, double* h, double* l, double* s);

class CARTO_DLL IProgressReporter
{
public:
	virtual void StartProgress() = 0;
	virtual void EndProgress() = 0;
	virtual void SetStepCount(long lCount) = 0;
	virtual void SetTipMessage(LPCSTR psTip) = 0;
	virtual void ShowProgress(BOOL bShow) = 0;
	virtual void StepIt() = 0;
	virtual BOOL IsCanceled() = 0;
};


class CARTO_DLL CImageProFunction
{
protected:
	CImageProFunction(long lType);
	IProgressReporter* m_pReporter;
	CImageProFunction* m_pIncorporate;
	BOOL m_bAbled;
	long mg_lType;			//标志对象类型的变量
	//它在派生类的构造函数中设置，其他地方不允许改变

public:
	virtual ~CImageProFunction();

public:
	//设定进度报告
	void SetProgressReporter(IProgressReporter* pReporter);

	long GetType() { return mg_lType; };

	//进行处理
	virtual BOOL operator()(long lBufLen,unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3);
	virtual BOOL operator()(long lBufLen, unsigned char* pChannel);
	//判断是否冲突
	virtual BOOL ConflictWith(CImageProFunction* pOther) = 0;
	//判断是否可以合并（默认实现是只要mg_lType相同就可以合并）
	virtual BOOL CanIncorporate(CImageProFunction* pOther);
	//合并
	virtual BOOL Incorporate(CImageProFunction* pOther) = 0;
	//回退
	virtual BOOL Backward();

	void SetAbled(BOOL b) {m_bAbled = b;};

	BOOL GetAbled() {return m_bAbled;};

	void SetColorType(COLORTYPE color) {m_clrType = color;};

public:
	CRasterRGBRenderPtr m_pRasRender;

	COLORTYPE m_clrType;

	//标识调整的次数,处在不同次调整的两个同类函数不能合并
    static int gAdjustCount;

	UINT m_AdjustCount;
};

class CARTO_DLL CImagePro_AdjustHue : public CImageProFunction
{

	static const std::string m_szDesc;
	double m_dDelta;

	double m_dAlbes;
	BOOL   IsToExact;


public:
	CImagePro_AdjustHue();
	BOOL operator()(long lBufLen,unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3);

	BOOL ConflictWith(CImageProFunction* pOther);
	BOOL Incorporate(CImageProFunction* pOther);
	void SetHueDelta(double dDelta) { m_dDelta = dDelta; };
	double GetHueDelta() { return m_dDelta; };
	BOOL Backward();

	void SetHue(double dAlbes) { m_dAlbes = dAlbes; IsToExact=TRUE;};
};

//调整饱和度
class CARTO_DLL CImagePro_AdjustSaturation : public CImageProFunction
{
	static const std::string m_szDesc;
	double m_dDelta;

	double m_dAlbes;
	BOOL   IsToExact;
public:
	CImagePro_AdjustSaturation();
	BOOL operator()(long lBufLen,unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3);
	BOOL ConflictWith(CImageProFunction* pOther);
	BOOL Incorporate(CImageProFunction* pOther);
	void SetSaturationDelta(double dDelta) { m_dDelta = dDelta; };
	double GetSaturationDelta() { return m_dDelta; };
	BOOL Backward();

	void SetSaturation(double dAlbes) { m_dAlbes = dAlbes; IsToExact=TRUE;};
};

//调整明度
class CARTO_DLL CImagePro_AdjustLum : public CImageProFunction
{
	static const std::string m_szDesc;
	double m_dDelta;

	double m_dAlbes;
	BOOL   IsToExact;
public:
	CImagePro_AdjustLum();
	BOOL operator()(long lBufLen,unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3);
	BOOL ConflictWith(CImageProFunction* pOther);
	BOOL Incorporate(CImageProFunction* pOther);
	void SetLumDelta(double dDelta) { m_dDelta = dDelta; };
	double GetLumDelta() { return m_dDelta; };
	BOOL Backward();

	void SetLum(double dAlbes) { m_dAlbes = dAlbes; IsToExact=TRUE;};
};

//调整LUT
class CARTO_DLL CImagePro_LutRollback : public CImageProFunction
{
	BYTE  m_LutHistory[3][256];    //变换后的LUT表
public:
	CImagePro_LutRollback();
	BOOL ConflictWith(CImageProFunction* pOther);
	BOOL Incorporate(CImageProFunction* pOther);
	BOOL AddLUTHistroy();
	BOOL Backward();

};

}

#endif