#ifndef _RASTERLUTALGORITHM_H_
#define _RASTERLUTALGORITHM_H_

//#include "RasterRegionRender.h"

namespace Carto{

	/** 
	* 函数功能： 对输入数据块按照LUT映射得到输出数据块
	*/
	static BOOL ApplyLut(BYTE *pbLUT,unsigned char* pchSrcBuffer,unsigned char *pchBuffer,long lBufferSize)
	{
		if( NULL == pchSrcBuffer || NULL == pchBuffer )
			return FALSE;

		for( int i = 0;i < lBufferSize;i++ )
			pchBuffer[i]= pbLUT[pchSrcBuffer[i]];

		return TRUE;
	}

	static BOOL AdjustLutByContrast(BYTE *pbLUT,long lContrast)
	{
		//对LUT表做对比度与亮度增强
		//第一步:找到LUT表最大最小值
		long lMin = 0;
		long lMax = 255;

		long lMinValue = 255;
		long lMaxValue = 0;
		long i = 0;
		for(; i < 256; i++)
		{
			if(pbLUT[i] <= lMinValue)
			{
				lMinValue = pbLUT[i];
				lMin = i;
			}
		}

		for(long j = 255; j >= 0; j--)
		{
			if(pbLUT[j] >= lMaxValue )
			{
				lMaxValue = pbLUT[j]; 
				lMax = j;
			}
		}

		long lMean = (lMax + lMin) /2;
		long lMeanValue = (lMaxValue + lMinValue) /2;

		//第二步:变化对比度
		long lValue;
		for(i = 0 ; i< 256 ;i++)
		{
			if(lContrast == 45)
				break;

			if(pbLUT[i] < lMeanValue)
			{
				lValue = lMeanValue - (lMeanValue - pbLUT[i]) * tan(((double)lContrast) / 180 * 3.14159);
				if(lValue < lMinValue)
					pbLUT[i] = lMinValue;
				else
					pbLUT[i] = lValue;
			}
			else if(pbLUT[i] > lMeanValue)
			{
				lValue = (pbLUT[i] - lMeanValue ) * tan(((double)lContrast) / 180 * 3.14159) + lMeanValue;
				if(lValue > lMaxValue)
					pbLUT[i] = lMaxValue;
				else
					pbLUT[i] = lValue;
			}
		}

		return TRUE;
	}

	static BOOL AdjustLutByBrightness(BYTE *pbLUT,long lBrightness)
	{
		long lValue;
		//变化亮度
		for( int i = 0; i< 256; i++)
		{
			if(lBrightness == 50)
				break;
			lValue = pbLUT[i] + (lBrightness - 50); 
			if(lValue > 255)
				pbLUT[i] = 255;
			else if(lValue < 0)
				pbLUT[i] = 0;
			else
				pbLUT[i] = lValue;
		}

		return TRUE;
	}




}



#endif