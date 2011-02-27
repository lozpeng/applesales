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

//Macros.h

/*****************************************************************
 *	作者名字: 
 *	创建日期: 2000-08-21
 *	文件描述: 基本宏定义
 *****************************************************************/

#ifndef _MACROS_H_
#define _MACROS_H_

#ifndef max
#define max(a,b)	(((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)	(((a) < (b)) ? (a) : (b))
#endif
#ifndef sqr
#define sqr(a)		((a)*(a))
#endif
#ifndef PI
#define PI			3.1415926535897932
#endif

#define TOLERANCE				(1e-9)
#define DEGTORAD		0.0174532925199433			//角度转弧度转换因子
#define RADTODEG		57.29577951308232			//弧度转角度转换因子

#define EQ( dblX, dblY )		( ( dblX - dblY ) <= TOLERANCE && ( dblX - dblY ) >= -TOLERANCE )
#define NE( dblX, dblY )		( ( dblX - dblY ) > TOLERANCE || ( dblX - dblY ) < -TOLERANCE )
#define LT( dblX, dblY )		( dblX + TOLERANCE < dblY )
#define GT( dblX, dblY )        ( dblX - TOLERANCE > dblY )
#define LE( dblX, dblY )		( dblX <= dblY + TOLERANCE )
#define GE( dblX, dblY )        ( dblX >= dblY - TOLERANCE )

#endif //_MACROS_H_
//Empty line