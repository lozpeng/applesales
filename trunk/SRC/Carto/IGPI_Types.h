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

typedef unsigned char CHANNEL;   //���� ͼ��ͨ��ֵ
typedef float         R_CHANNEL;  //ʵ�� ͼ��ͨ��ֵ

#define FUNC_NoneEnhance					1000    //����ǿ
#define FUNC_LineStrechEnhance				1001    //��������
#define FUNC_HistgramNormalizeEnhance		1002	//ֱ��ͼ��̬��
#define FUNC_HistgramEqulizeEnhance			1003	//ֱ��ͼ���Ȼ�
#define FUNC_LogEnhance						1004	//������ǿ
#define FUNC_ExpEnhance						1005	//ָ����ǿ
#define FUNC_ReverseImage					1006	//��ת
#define FUNC_EdgeEnhance					1007	//��Ե��ǿ	
#define FUNC_StandardDeviation				1008	//Standard Deviation	
#define FUNC_Cancel                         1009    //����


#endif //__IGPI_TYPES_H__