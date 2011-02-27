#include "stdafx.h"
#include "ImgProFunction.h"
#include "IGPI_Types.h"
#include "Macros.h"

namespace Carto{

const std::string CImagePro_AdjustHue::m_szDesc = "Adjust Hue";
const std::string CImagePro_AdjustSaturation::m_szDesc = "Adjust Saturation";
const std::string CImagePro_AdjustLum::m_szDesc = "Adjust Luminance";

//加入这个类仅仅为了保证CImageProFunction的m_pReporter指针总是有效
class _reporter : public IProgressReporter
{
public:
	void StartProgress(){};
	void EndProgress(){};
	void SetStepCount(long lCount){};
	void SetTipMessage(LPCSTR psTip){};
	void ShowProgress(BOOL bShow){};
	void StepIt(){};
	BOOL IsCanceled(){return FALSE;};
};

static _reporter g_PlaceHolder_Reporter;

///////////////////////////////////////////////////////////////////////////
//全局函数
static double Value(double n1, double n2, double hue)
{
	if(hue > 360.0)
		hue -= 360.0;
	else if(hue < 0.0)
		hue += 360.0;

	if(hue < 60.0)
		return (n1+(n2-n1)*hue/60.0);
	else if(hue < 180.0)
		return n2;
	else if(hue < 240.0)
		return (n1+(n2-n1)*(240.0-hue)/60.0);
	else
		return n1;
}

////////////////////////////////////////////////////////////////////
//change HLS color to RGB color
void HLStoRGB(double h, double l, double s, BYTE* r, BYTE* g, BYTE* b)
{
	double m1, m2;
	double R, G, B;

	if(l<=0.5)
		m2 = l*(1.0+s);
	else
		m2 = l+s-l*s;

	m1 = 2.0*l - m2;
	if(s == 0)
	{
		if(h == UNDEFINED)
			R = G = B = l;
		else
			R = G = B = 0.0;
	}
	else
	{
		R = Value(m1, m2, h+120.0);
		G = Value(m1, m2, h);
		B = Value(m1, m2, h-120.0);
	}
	int iR = (int)(R*255.0);
	int iG = (int)(G*255.0);
	int iB = (int)(B*255.0);
	*r = (BYTE)BOUND(iR, 0, 255);
	*g = (BYTE)BOUND(iG, 0, 255);
	*b = (BYTE)BOUND(iB, 0, 255);
}

////////////////////////////////////////////////////////////////////
//change RGB color to HLS color
void RGBtoHLS(BYTE r, BYTE g, BYTE b, double* h, double* l, double* s)
{
	double mx, mn, delta;
	double R, G, B;
	R = (double)r/255.0;
	G = (double)g/255.0;
	B = (double)b/255.0;
	mx = max(R, max(G, B));
	mn = min(R, min(G, B));
	*l = (mx+mn)/2.0;
	if(mx == mn)
	{
		*s = 0.0;
		*h = UNDEFINED;
	}
	else
	{
		delta = mx-mn;
		if(*l < 0.5)
			*s = delta/(mx+mn);
		else
			*s = delta/(2.0-mx-mn);
		if(R == mx)
			*h = (G-B)/delta;
		else if(G== mx)
			*h = 2.0+(B-R)/delta;
		else if(B == mx)
			*h = 4.0+(R-G)/delta;

		*h *= 60.0;
		if(*h < 0.0)
			*h += 360.0;
		else if(*h > 360.0)
			*h -= 360.0;
	}

}

void RGB2HSB(BYTE r,BYTE g,BYTE b,double* hue,double* sat,double* bri)
{
	BYTE minval = min(r,min(g,b));
	BYTE maxval = max(r,max(g,b));

	//bri
	*bri = (double)(maxval)/255;

	//sat
	if (maxval == minval)
	{
		*sat = 0.0f;
	}
	else
	{
		*sat = (double)(maxval - minval)/maxval;
	}

	//hue
	if (maxval == minval)
	{
		*hue = UNDEFINED;
	}
	else
	{
		double diff = (double)(maxval - minval);
		double rnorm = (maxval - r)/diff;
		double gnorm = (maxval - g)/diff;
		double bnorm = (maxval - b)/diff;

		*hue = 0.0f;

		if (r == maxval)
		{
			*hue = 60.0f*(6.0f + bnorm - gnorm);
		}

		if (g == maxval)
		{
			*hue = 60.0f*(2.0f + rnorm - bnorm);
		}

		if (b == maxval)
		{
			*hue = 60.0f*(4.0f + gnorm - rnorm);
		}

		if (*hue > 360.0f)
		{
			*hue = *hue - 360.0f;
		}
	}

}


void HSB2RGB(double hue,double sat,double bri,BYTE* r,BYTE* g,BYTE* b)
{
	if (sat == 0.0)
	{
		BYTE byValue(BYTE(bri * 255.0 + 0.5));
		*r = (BYTE)BOUND(byValue, 0, 255);
		*g = (BYTE)BOUND(byValue, 0, 255);
		*b = (BYTE)BOUND(byValue, 0, 255);
	}
	double dMode(hue / 60.0);
	switch((int)dMode)
	{
	case 0:
		{
			double dTemp(bri * (1.0 - sat));
			*r = BYTE(bri*255.0+0.5);
			*g = BYTE((dTemp+(bri - dTemp)*dMode)*255.0 + 0.5);
			*b = BYTE(dTemp*255.0 + 0.5);
		}
	case 1:
		{
			double dTemp(bri * (1.0 - sat));
			*r = BYTE((bri - (bri - dTemp)*(dMode-1.0))*255.0 +0.5);
			*g = BYTE(bri*255.0 + 0.5);
			*b = BYTE(dTemp*255.0 + 0.5);
		}
	case 2:
		{
			double dTemp(bri * (1.0 - sat));
			*r = BYTE(dTemp*255.0 + 0.5);
			*g = BYTE(bri *255.0 +0.5);
			*b = BYTE((dTemp + (bri-dTemp)*(dMode-2.0))*255.0 + 0.5);
		}
	case 3:
		{
			double dTemp(bri * (1.0 - sat));
			*r = BYTE(dTemp*255.0 + 0.5);
			*g = BYTE((bri - (bri-dTemp)*(dMode-3.0))*255.0 + 0.5);
			*b = BYTE(bri*255.0 + 0.5);
		}
	case 4:
		{
			double dTemp(bri * (1.0 - sat));
			*r = BYTE((dTemp + (bri-dTemp)*(dMode-4.0))*255.0 + 0.5);
			*g = BYTE(dTemp*255.0 + 0.5);
			*b = BYTE(bri *255.0 +0.5);
		}
	default:
		{
			double dTemp(bri * (1.0 - sat));
			*r = BYTE(bri *255.0 +0.5);
			*g = BYTE(dTemp*255.0 + 0.5);
			*b = BYTE((bri - (bri - dTemp)*(dMode-5.0))*255.0 +0.5);

		}
	}
}

int CImageProFunction::gAdjustCount = 0;

CImageProFunction::CImageProFunction(long lType)
{
	mg_lType = lType;
	m_pReporter = &g_PlaceHolder_Reporter;
	m_pIncorporate = NULL;
	m_clrType = COLNONE;
	m_bAbled = TRUE;
	m_AdjustCount = gAdjustCount;
}

CImageProFunction::~CImageProFunction()
{
}

void CImageProFunction::SetProgressReporter(IProgressReporter* pReporter)
{
	//ASSERT(pReporter != NULL);
	m_pReporter = pReporter;
}

BOOL CImageProFunction::CanIncorporate(CImageProFunction* pOther)
{
	return pOther->GetType() == GetType()  && pOther->m_clrType == m_clrType && pOther->m_pIncorporate == NULL && pOther->m_AdjustCount == m_AdjustCount;
}

BOOL CImageProFunction::operator()(long lBufLen, unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3)
{
	return TRUE;
}

BOOL CImageProFunction::operator()(long lBufLen, unsigned char* pChannel)
{
	return TRUE;
}

BOOL CImageProFunction::Backward()
{
	return TRUE;
}

CImagePro_AdjustHue::CImagePro_AdjustHue() : CImageProFunction(CARTO_IMGPRO_ADJUST_HUE)
{
	m_dDelta = 24.0;
	IsToExact = FALSE;
}

BOOL CImagePro_AdjustHue::operator()(long lBufLen, unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3)
{
	if(m_pIncorporate != NULL)		//本身已经被合并入其它同类对象实例
		return TRUE;
	if(!m_bAbled)
		return TRUE;
	if(EQ(m_dDelta,0.0))
		return TRUE;


	double h, l, s;
	m_pReporter->StartProgress();
	m_pReporter->SetTipMessage(m_szDesc.c_str());
	m_pReporter->ShowProgress(TRUE);
	m_pReporter->SetStepCount(lBufLen);

	float fLMin,fLMax,fRMin,fRMax;

	{
		if(IsToExact == TRUE)
		{
			for(long i=0; i<lBufLen; i++)
			{
				RGBtoHLS(*pChannel1, *pChannel2, *pChannel3, &h, &l, &s);

				if(h != UNDEFINED)
				{
					h = BOUND(m_dAlbes, 0.0, 360.0);
				}
				HLStoRGB(h, l, s, pChannel1, pChannel2, pChannel3);
				pChannel1++;
				pChannel2++;
				pChannel3++;
				m_pReporter->StepIt();
			}
			m_pReporter->EndProgress();
			IsToExact = FALSE;
			return TRUE;
		}

		for(long i=0; i<lBufLen; i++)
		{
	
			RGBtoHLS(*pChannel1, *pChannel2, *pChannel3, &h, &l, &s);

			if(h != UNDEFINED)
			{
				switch(m_clrType)
				{
				case FULL://全图
					{
                        h = BOUND(h+m_dDelta, 0.0, 360.0);
					}
					break;
				case RED://红
					{
						fLMin = 315;
						fLMax = 345;
						fRMin = 15;
						fRMax = 45;
						if (h>=fLMin && h<=fLMax)
							h = ROTATE((h+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)));
						else if (h>=fRMin&&h<=fRMax)
							h = ROTATE((h-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)));
						else if ((h>fLMax&&h<=360) || (h>=0&&h<fRMin))
							h = ROTATE(h+m_dDelta, 0.0, 360.0);
						
					}
					break;
				case GREEN://绿
					{
						fLMin = 75;
						fLMax = 105;
						fRMin = 135;
						fRMax = 165;
						if (h>=fLMin && h<=fLMax)
							h = ROTATE((h+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)));
						else if (h>=fRMin&&h<=fRMax)
							h = ROTATE((h-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)));
						else if (h>fLMax && h<fRMin)
							h = ROTATE(h+m_dDelta, 0.0, 360.0);

					}
				    break;
				case BLUE://蓝
					{
						fLMin = 195;
						fLMax = 225;
						fRMin = 255;
						fRMax = 285;
						if (h>=fLMin && h<=fLMax)
							h = ROTATE((h+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)));
						else if (h>=fRMin&&h<=fRMax)
							h = ROTATE((h-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)));
						else if (h>fLMax && h<fRMin)
							h = ROTATE(h+m_dDelta, 0.0, 360.0);

					}
				    break;
				case YELLOW://黄
					{
						fLMin = 15;
						fLMax = 45;
						fRMin = 75;
						fRMax = 105;
						if (h>=fLMin && h<=fLMax)
							h = ROTATE((h+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)));
						else if (h>=fRMin&&h<=fRMax)
							h = ROTATE((h-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)));
						else if (h>fLMax && h<fRMin)
							h = ROTATE(h+m_dDelta, 0.0, 360.0);

					}
					break;
				case CYAN://青
					{
						fLMin = 135;
						fLMax = 165;
						fRMin = 195;
						fRMax = 225;
						if (h>=fLMin && h<=fLMax)
							h = ROTATE((h+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)));
						else if (h>=fRMin&&h<=fRMax)
							h = ROTATE((h-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)));
						else if (h>fLMax && h<fRMin)
							h = ROTATE(h+m_dDelta, 0.0, 360.0);

					}
					break;
				case MAGENTA://洋红
					{
						fLMin = 255;
						fLMax = 285;
						fRMin = 315;
						fRMax = 345;
						if (h>=fLMin && h<=fLMax)
							h = ROTATE((h+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)));
						else if (h>=fRMin&&h<=fRMax)
							h = ROTATE((h-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)));
						else if (h>fLMax && h<fRMin)
							h = ROTATE(h+m_dDelta, 0.0, 360.0);

					}
				    break;
				default:
				    break;
				}

			}
			HLStoRGB(h, l, s, pChannel1, pChannel2, pChannel3);

			pChannel1++;
			pChannel2++;
			pChannel3++;
			m_pReporter->StepIt();
		}

	}

	m_pReporter->EndProgress();

	return TRUE;
}

BOOL CImagePro_AdjustHue::ConflictWith(CImageProFunction* pOther)
{
	return FALSE;
}

BOOL CImagePro_AdjustHue::Incorporate(CImageProFunction* pOther)
{
	if(pOther->GetType() == GetType() && pOther->m_clrType == m_clrType && pOther->GetAbled())
	{
		CImagePro_AdjustHue* pAH = (CImagePro_AdjustHue*)pOther;
		//pAH->m_dDelta += m_dDelta;
		pAH->m_dDelta = m_dDelta;
		m_pIncorporate = pOther;
		return TRUE;
	}
	return FALSE;
}

BOOL CImagePro_AdjustHue::Backward()
{
	if(m_pIncorporate != NULL)
	{
		((CImagePro_AdjustHue*)m_pIncorporate)->m_dDelta -= m_dDelta;
	}
	m_bAbled = TRUE;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
CImagePro_AdjustSaturation::CImagePro_AdjustSaturation() : CImageProFunction(CARTO_IMGPRO_ADJUST_SATURATION)
{
	m_dDelta = 0.1;
}

BOOL CImagePro_AdjustSaturation::operator()(long lBufLen, unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3)
{
	if(m_pIncorporate != NULL)		//本身已经被合并入其它同类对象实例
		return TRUE;
	if(EQ(m_dDelta,0.0))
		return TRUE;

	double h, l, s;
	m_pReporter->StartProgress();
	m_pReporter->SetTipMessage(m_szDesc.c_str());
	m_pReporter->ShowProgress(TRUE);
	m_pReporter->SetStepCount(lBufLen);

	float fLMin,fLMax,fRMin,fRMax;

	{
		if(IsToExact == TRUE)
		{
			for(long i=0; i<lBufLen; i++)
			{	

				RGBtoHLS(*pChannel1, *pChannel2, *pChannel3, &h, &l, &s);
				s = BOUND(m_dAlbes, 0.0, 1.0);		 
				HLStoRGB(h, l, s, pChannel1, pChannel2, pChannel3);

				pChannel1++;
				pChannel2++;
				pChannel3++;
				m_pReporter->StepIt();
			}
			m_pReporter->EndProgress();
			IsToExact=FALSE;
			return TRUE;
		}

		if(GT(m_dDelta,0.0))
		{
			for(long i=0; i<lBufLen; i++)
			{

				RGBtoHLS(*pChannel1, *pChannel2, *pChannel3, &h, &l, &s);

				switch(m_clrType)
				{
				case FULL://全图
					{
						s = BOUND(s+m_dDelta, 0.0, 1.0);
					}
					break;
				case RED://红
					{
						fLMin = 315;
						fLMax = 345;
						fRMin = 15;
						fRMax = 45;
						if (h>=fLMin && h<=fLMax)
						{
							s = BOUND((s+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)),0.0,1.0);

						}
						else if (h>=fRMin&&h<=fRMax)
						{
						    s = BOUND((s-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)),0.0,1.0);
						}
						else if ((h>fLMax&&h<=360) || (h>=0&&h<fRMin))
							s = BOUND(s+m_dDelta, 0.0, 1.0);

					}
					break;
				case GREEN://绿
					{
						fLMin = 75;
						fLMax = 105;
						fRMin = 135;
						fRMax = 165;
						if (h>=fLMin && h<=fLMax)
						{
                            s = BOUND((s+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)),0.0,1.0);
						}
						else if (h>=fRMin&&h<=fRMax)
						{
                            s = BOUND((s-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)),0.0,1.0);
						}
						else if (h>fLMax && h<fRMin)
							s = BOUND(s+m_dDelta, 0.0, 1.0);

					}
					break;
				case BLUE://蓝
					{
						fLMin = 195;
						fLMax = 225;
						fRMin = 255;
						fRMax = 285;
						if (h>=fLMin && h<=fLMax)
						{
                            s = BOUND((s+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)),0.0,1.0);
						}
						else if (h>=fRMin&&h<=fRMax)
						{
                            s = BOUND((s-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)),0.0,1.0);
						}
						else if (h>fLMax && h<fRMin)
							s = BOUND(s+m_dDelta, 0.0, 1.0);

					}
					break;
				case YELLOW://黄
					{
						fLMin = 15;
						fLMax = 45;
						fRMin = 75;
						fRMax = 105;
						if (h>=fLMin && h<=fLMax)
						{
                            s = BOUND((s+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)),0.0,1.0);
						}
						else if (h>=fRMin&&h<=fRMax)
						{
                            s = BOUND((s-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)),0.0,1.0);
						}
						else if (h>fLMax && h<fRMin)
							s = BOUND(s+m_dDelta, 0.0, 1.0);

					}
					break;
				case CYAN://青
					{
						fLMin = 135;
						fLMax = 165;
						fRMin = 195;
						fRMax = 225;
						if (h>=fLMin && h<=fLMax)
						{
                            s = BOUND((s+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)),0.0,1.0);
						}
						else if (h>=fRMin&&h<=fRMax)
						{
                            s = BOUND((s-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)),0.0,1.0);
						}
						else if (h>fLMax && h<fRMin)
							s = BOUND(s+m_dDelta, 0.0, 1.0);

					}
					break;
				case MAGENTA://洋红
					{
						fLMin = 255;
						fLMax = 285;
						fRMin = 315;
						fRMax = 345;
						if (h>=fLMin && h<=fLMax)
						{
                            s = BOUND((s+h*m_dDelta/(fLMax-fLMin)-fLMin*m_dDelta/(fLMax-fLMin)),0.0,1.0);
						}
						else if (h>=fRMin&&h<=fRMax)
						{
                            s = BOUND((s-h*m_dDelta/(fRMax-fRMin)+fRMax*m_dDelta/(fRMax-fRMin)),0.0,1.0);
						}
						else if (h>fLMax && h<fRMin)
							s = BOUND(s+m_dDelta, 0.0, 1.0);

					}
					break;
				default:
					break;
				}

				//
				HLStoRGB(h, l, s, pChannel1, pChannel2, pChannel3);
				pChannel1++;
				pChannel2++;
				pChannel3++;
				m_pReporter->StepIt();
			}
		}
		else
		{
			double dMean;
			bool bAdjust = false;
			for(long i=0; i<lBufLen; i++)
			{
				bAdjust = false;

				RGBtoHLS(*pChannel1, *pChannel2, *pChannel3, &h, &l, &s);

				if(h != UNDEFINED)
				{
					////////////////
					switch(m_clrType)
					{
					case FULL://全图
						{
							 bAdjust = true;
						}
						break;
					case RED://红
						{
							fLMin = 315;
							fLMax = 345;
							fRMin = 15;
							fRMax = 45;
							if (h>=fLMin && h<=fLMax)
							{
							   bAdjust = true;	
							}
							else if (h>=fRMin&&h<=fRMax)
							{
							   bAdjust = true;	
							}
							else if ((h>fLMax&&h<=360) || (h>=0&&h<fRMin))
							   bAdjust = true;

						}
						break;
					case GREEN://绿
						{
							fLMin = 75;
							fLMax = 105;
							fRMin = 135;
							fRMax = 165;
							if (h>=fLMin && h<=fLMax)
							{
								bAdjust = true;
							}
							else if (h>=fRMin&&h<=fRMax)
							{
								bAdjust = true;
							}
							else if (h>fLMax && h<fRMin)
								bAdjust = true;

						}
						break;
					case BLUE://蓝
						{
							fLMin = 195;
							fLMax = 225;
							fRMin = 255;
							fRMax = 285;
							if (h>=fLMin && h<=fLMax)
							{
								bAdjust = true;
							}
							else if (h>=fRMin&&h<=fRMax)
							{
								bAdjust = true;
							}
							else if (h>fLMax && h<fRMin)
								bAdjust = true;

						}
						break;
					case YELLOW://黄
						{
							fLMin = 15;
							fLMax = 45;
							fRMin = 75;
							fRMax = 105;
							if (h>=fLMin && h<=fLMax)
							{
								bAdjust = true;
							}
							else if (h>=fRMin&&h<=fRMax)
							{
								bAdjust = true;
							}
							else if (h>fLMax && h<fRMin)
								bAdjust = true;

						}
						break;
					case CYAN://青
						{
							fLMin = 135;
							fLMax = 165;
							fRMin = 195;
							fRMax = 225;
							if (h>=fLMin && h<=fLMax)
							{
							    bAdjust = true;
							}
							else if (h>=fRMin&&h<=fRMax)
							{
								bAdjust = true;
							}
							else if (h>fLMax && h<fRMin)
							    bAdjust = true;
						}
						break;
					case MAGENTA://洋红
						{
							fLMin = 255;
							fLMax = 285;
							fRMin = 315;
							fRMax = 345;
							if (h>=fLMin && h<=fLMax)
							{
								bAdjust = true;
							}
							else if (h>=fRMin&&h<=fRMax)
							{
								bAdjust = true;
							}
							else if (h>fLMax && h<fRMin)
								
                                bAdjust = true;
						}
						break;
					default:
						break;
					}

					if (bAdjust)
					{
						dMean = l*255;
						*pChannel1 += (*pChannel1-dMean)*m_dDelta;
						*pChannel2 += (*pChannel2-dMean)*m_dDelta;
						*pChannel3 += (*pChannel3-dMean)*m_dDelta;
						*pChannel1 = (BYTE)BOUND(*pChannel1, 0, 255);
						*pChannel2 = (BYTE)BOUND(*pChannel2, 0, 255);
						*pChannel3 = (BYTE)BOUND(*pChannel3, 0, 255);
					}

				}
				pChannel1++;
				pChannel2++;
				pChannel3++;
				m_pReporter->StepIt();
			}
		}

	}

	m_pReporter->EndProgress();
	return TRUE;
}

BOOL CImagePro_AdjustSaturation::ConflictWith(CImageProFunction* pOther)
{
	return FALSE;
}

BOOL CImagePro_AdjustSaturation::Incorporate(CImageProFunction* pOther)
{
	if(pOther->GetType() == GetType() && pOther->m_clrType == m_clrType && pOther->GetAbled())
	{
		CImagePro_AdjustSaturation* pAH = (CImagePro_AdjustSaturation*)pOther;
		pAH->m_dDelta = BOUND(/*pAH->m_dDelta+*/m_dDelta, -1.0, 1.0);
		m_pIncorporate = pOther;
		return TRUE;
	}
	return FALSE;
}

BOOL CImagePro_AdjustSaturation::Backward()
{
	if(m_pIncorporate != NULL)
	{
		((CImagePro_AdjustSaturation*)m_pIncorporate)->m_dDelta -= m_dDelta;
	}
	m_bAbled = TRUE;
	return TRUE;
}

CImagePro_LutRollback::CImagePro_LutRollback() : CImageProFunction(CARTO_IMGPRO_ADJUST_LUT)
{
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<256;++j)
		{
			m_LutHistory[i][j]=j;
		}
	}
}

BOOL CImagePro_LutRollback::AddLUTHistroy()
{
	BOOL m_ColorFlag=m_pRasRender->GetRGBMode();
	BYTE* m_CurLut=new BYTE[256];
	if(m_ColorFlag)
	{
		/*try
		{*/
		for(int i=0;i<3;++i)
		{
			m_pRasRender->GetBandLUT(i+1,m_CurLut);
			memcpy(m_LutHistory[i],m_CurLut,sizeof(BYTE)*256);
		}
		/*	
		}
		catch(exception e)
		{
		delete m_CurLut;
		return FALSE;
		}	*/
	}
	else
	{
		/*try
		{*/
		m_pRasRender->GetBandLUT(1,m_CurLut);
		memcpy(m_LutHistory[0],m_CurLut,sizeof(BYTE)*256);
		/*}
		catch(exception e)
		{
		delete m_CurLut;
		return FALSE;
		}*/		
	}
	delete m_CurLut;
	return TRUE;
}

BOOL CImagePro_LutRollback::Backward()
{
	BOOL m_ColorFlag=m_pRasRender->GetRGBMode();
	BYTE* m_CurLut=new BYTE[256];
	if(m_ColorFlag)
	{
		/*try
		{*/
		for(int i=0;i<3;++i)
		{
			memcpy(m_CurLut,m_LutHistory[i],sizeof(BYTE)*256);
			m_pRasRender->SetBandLUT(i+1,m_CurLut);
		}			
		/*}
		catch(exception e)
		{
		delete m_CurLut;
		return FALSE;
		}	*/
	}
	else
	{
		/*try
		{*/
		memcpy(m_CurLut,m_LutHistory[0],sizeof(BYTE)*256);
		m_pRasRender->SetBandLUT(1,m_CurLut);
		/*}
		catch(exception e)
		{
		delete m_CurLut;
		return FALSE;
		}	*/	
	}
	delete m_CurLut;
	m_pRasRender->ApplyEnhanceDraw(FUNC_Cancel);
	return TRUE;
}

BOOL CImagePro_LutRollback::ConflictWith(CImageProFunction* pOther)
{
	return FALSE;
}

BOOL CImagePro_LutRollback::Incorporate(CImageProFunction* pOther)
{
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
CImagePro_AdjustLum::CImagePro_AdjustLum() : CImageProFunction(CARTO_IMGPRO_ADJUST_LUM)
{
	m_dDelta = 0.1;
}

BOOL CImagePro_AdjustLum::operator()(long lBufLen,unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3)
{
	if(m_pIncorporate != NULL)		//本身已经被合并入其它同类对象实例
		return TRUE;
	if(EQ(m_dDelta,0.0))
		return TRUE;

	double h, l, s;
	m_pReporter->StartProgress();
	m_pReporter->SetTipMessage(m_szDesc.c_str());
	m_pReporter->ShowProgress(TRUE);
	m_pReporter->SetStepCount(lBufLen);

	float fLMin,fLMax,fRMin,fRMax;

	{
		if(IsToExact == TRUE)
		{
			for(long i=0; i<lBufLen; i++)
			{	

				RGBtoHLS(*pChannel1, *pChannel2, *pChannel3, &h, &l, &s);
				l = BOUND(m_dAlbes, 0.0, 1.0);		 
				HLStoRGB(h, l, s, pChannel1, pChannel2, pChannel3);

				pChannel1++;
				pChannel2++;
				pChannel3++;
				m_pReporter->StepIt();
			}
			m_pReporter->EndProgress();
			IsToExact=FALSE;
			return TRUE;
		}

		//

		double dMean;
		bool bAdjust = false;
		for(long i=0; i<lBufLen; i++)
		{
			bAdjust = false;

			RGBtoHLS(*pChannel1, *pChannel2, *pChannel3, &h, &l, &s);

			if(h != UNDEFINED)
			{
				switch(m_clrType)
				{
				case FULL://全图
					{
						bAdjust = true;
					}
					break;
				case RED://红
					{
						fLMin = 315;
						fLMax = 345;
						fRMin = 15;
						fRMax = 45;
						if (h>=fLMin && h<=fLMax)
						{
							bAdjust = true;	
						}
						else if (h>=fRMin&&h<=fRMax)
						{
							bAdjust = true;	
						}
						else if ((h>fLMax&&h<=360) || (h>=0&&h<fRMin))
							bAdjust = true;

					}
					break;
				case GREEN://绿
					{
						fLMin = 75;
						fLMax = 105;
						fRMin = 135;
						fRMax = 165;
						if (h>=fLMin && h<=fLMax)
						{
							bAdjust = true;
						}
						else if (h>=fRMin&&h<=fRMax)
						{
							bAdjust = true;
						}
						else if (h>fLMax && h<fRMin)
							bAdjust = true;

					}
					break;
				case BLUE://蓝
					{
						fLMin = 195;
						fLMax = 225;
						fRMin = 255;
						fRMax = 285;
						if (h>=fLMin && h<=fLMax)
						{
							bAdjust = true;
						}
						else if (h>=fRMin&&h<=fRMax)
						{
							bAdjust = true;
						}
						else if (h>fLMax && h<fRMin)
							bAdjust = true;

					}
					break;
				case YELLOW://黄
					{
						fLMin = 15;
						fLMax = 45;
						fRMin = 75;
						fRMax = 105;
						if (h>=fLMin && h<=fLMax)
						{
							bAdjust = true;
						}
						else if (h>=fRMin&&h<=fRMax)
						{
							bAdjust = true;
						}
						else if (h>fLMax && h<fRMin)
							bAdjust = true;

					}
					break;
				case CYAN://青
					{
						fLMin = 135;
						fLMax = 165;
						fRMin = 195;
						fRMax = 225;
						if (h>=fLMin && h<=fLMax)
						{
							bAdjust = true;
						}
						else if (h>=fRMin&&h<=fRMax)
						{
							bAdjust = true;
						}
						else if (h>fLMax && h<fRMin)
							bAdjust = true;
					}
					break;
				case MAGENTA://洋红
					{
						fLMin = 255;
						fLMax = 285;
						fRMin = 315;
						fRMax = 345;
						if (h>=fLMin && h<=fLMax)
						{
							bAdjust = true;
						}
						else if (h>=fRMin&&h<=fRMax)
						{
							bAdjust = true;
						}
						else if (h>fLMax && h<fRMin)

							bAdjust = true;
					}
					break;
				default:
					break;
				}

				if (bAdjust)
				{
					if (GT(m_dDelta,0.0))
					{
						*pChannel1 += (255-*pChannel1)*m_dDelta;
						*pChannel2 += (255-*pChannel2)*m_dDelta;
						*pChannel3 += (255-*pChannel3)*m_dDelta;
					}
					else
					{
						*pChannel1 += (*pChannel1)*m_dDelta;
						*pChannel2 += (*pChannel2)*m_dDelta;
						*pChannel3 += (*pChannel3)*m_dDelta;
					}

					*pChannel1 = (BYTE)BOUND(*pChannel1, 0, 255);
					*pChannel2 = (BYTE)BOUND(*pChannel2, 0, 255);
					*pChannel3 = (BYTE)BOUND(*pChannel3, 0, 255);

				}

			}
			else //黑 白
			{
				if (GT(m_dDelta,0.0))
				{
					*pChannel1 += (255-*pChannel1)*m_dDelta;
					*pChannel2 += (255-*pChannel2)*m_dDelta;
					*pChannel3 += (255-*pChannel3)*m_dDelta;
				}
				else
				{
					*pChannel1 += (*pChannel1)*m_dDelta;
					*pChannel2 += (*pChannel2)*m_dDelta;
					*pChannel3 += (*pChannel3)*m_dDelta;
				}

				*pChannel1 = (BYTE)BOUND(*pChannel1, 0, 255);
				*pChannel2 = (BYTE)BOUND(*pChannel2, 0, 255);
				*pChannel3 = (BYTE)BOUND(*pChannel3, 0, 255);

            }
			pChannel1++;
			pChannel2++;
			pChannel3++;
			m_pReporter->StepIt();
		}
	}

	m_pReporter->EndProgress();
	return TRUE;
}

BOOL CImagePro_AdjustLum::ConflictWith(CImageProFunction* pOther)
{
	return FALSE;
}

BOOL CImagePro_AdjustLum::Incorporate(CImageProFunction* pOther)
{
	if(pOther->GetType() == GetType() && pOther->m_clrType == m_clrType && pOther->GetAbled())
	{
		CImagePro_AdjustLum* pAH = (CImagePro_AdjustLum*)pOther;
		pAH->m_dDelta = BOUND(/*pAH->m_dDelta+*/m_dDelta, -1.0, 1.0);
		m_pIncorporate = pOther;
		return TRUE;
	}
	return FALSE;
}

BOOL CImagePro_AdjustLum::Backward()
{
	if(m_pIncorporate != NULL)
	{
		((CImagePro_AdjustLum*)m_pIncorporate)->m_dDelta -= m_dDelta;
	}
	m_bAbled = TRUE;
	return TRUE;
}


}