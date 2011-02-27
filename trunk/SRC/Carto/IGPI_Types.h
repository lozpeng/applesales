/*****************************************************************
 *  Copyright (c) 2000  Beijing Office of Apollo TG.
 *  All Rights Reserved.
 *  Copyright   protection   claimed   includes   all   forms  and
 *  matters of copyrightable  material and information now allowed
 *  by statutory or judicial law or hereinafter granted, including	
 *  without  limitation,  material  generated  from  the  software	
 *  programs  which  are  displayed  on the  screen such as icons,	
 *  screen display looks, etc.	
 *****************************************************************/


#ifndef __IGPI_TYPES_H__
#define __IGPI_TYPES_H__

#define IGPI_API __declspec(dllexport)
#define TRUE  1
#define FALSE 0

struct DirectionP
{
	long lFirstPointLoc;
	long lNextPointLoc;
}typedef *PDirectionP;

typedef unsigned char BYTE;
typedef int			BOOL; 

typedef unsigned char CHANNEL;   //整型 图象通道值
typedef float         R_CHANNEL;  //实型 图象通道值

#define FUNC_NoneEnhance					1000    //无增强
#define FUNC_LineStrechEnhance				1001    //线性拉伸
#define FUNC_HistgramNormalizeEnhance		1002	//直方图正态化
#define FUNC_HistgramEqulizeEnhance			1003	//直方图均匀化
#define FUNC_LogEnhance						1004	//对数增强
#define FUNC_ExpEnhance						1005	//指数增强
#define FUNC_ReverseImage					1006	//反转
#define FUNC_EdgeEnhance					1007	//边缘增强	
#define FUNC_StandardDeviation				1008	//Standard Deviation	
#define FUNC_Cancel                         1009    //撤销


#endif //__IGPI_TYPES_H__