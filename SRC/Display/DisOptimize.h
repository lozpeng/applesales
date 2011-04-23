#ifndef _CTO_DISPLAY_OPTIMIZE
#define _CTO_DISPLAY_OPTIMIZE


#define TOLER 1
#define _PI		3.1415926535
#define PI	_PI
#define _PI2	1.5707963268
#define _3PI2	4.7123889803
#define _2PI	6.283185307
#define CALLBACK __stdcall
//////////////////////////////////////////////////////////////////////////
//返回值　

//异常
#define DP_ERROR					(-1)	
#define DP_FUNC_UNDEAL_ERROR		(-2)	//函数中不应该走到的地方
#define DP_ARRAY_NULL_ERROR			(-3)	//偏移线的结构为空
#define DP_MARKLINE_ERROR			(-4)	//Mark线的数据有误
#define DP_MARKCOUNT_ERROR			(-5)	//Mark线的count有误
#define DP_STEP_LENGTH_ERROR		(-6)	//StepLength有误


//正常
#define DP_NOX_LENGTH_SHORT         (-101)

struct dbPoint 
{
	double x, y;
	dbPoint()
	{
		x = 0.0;
		y = 0.0;
	}
};

struct dbLine
{
	long Count;
	dbPoint ps[2];
	dbLine()
	{
		Count=0;
	}
};


//////////////////////////////////////////////////////////////////////////

namespace Display{
class DISPLAY_DLL CDisOptimize
{
public:
	CDisOptimize(void);
public:
	/*virtual*/ ~CDisOptimize(void);

	//释放“底层库函数”
	static void free_Object(unsigned char ** ppObject);

	static void free_Group(long ** ppGroup);
	static void free_Group(double ** ppGroup);
	//功能：将点集进行抽稀处理
	//参数：输入参数 iPointNum, 源点集中的点个数
	//      		 pPoints　源点集
	//				 length  点与线段最短距离的阀值（容差）
	//      输出参数 ppRetPoints 抽稀后的点数据（点集）GetPtInLineByDistance
	//返回值：
	//		抽稀后的点个数
	/*static*/ long DilutePoints(long iPointNum, const long * pPoints, long length, long ** ppRetPoints);
	long DiluteDoublePoints(long iPointNum, const double * pPoints, double length, double ** ppRetPoints);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//点符号

	//函数说明：
	//功能：得到拟和曲线的拟和点个数和拟和点数据
	//参数：输入参数 iPointNum, 控制点个数
	//      		 pControlPoint, 控制点数据
	//				 stepLength 离散化后的点的步长（默认为2）
	//				 curveRate 为曲线的弯曲(平滑)程度(0--1) ，默认为0.25
	//      输出参数 ppCurvePoint, 拟和点数据
	//返回值：拟和点点个数
	static long  GetCurvePoint(long iPointNum,const  long * pControlPoint, long ** ppCurvePoint,long stepLength=15,double curveRate=0.25);

	static void  GetArcBox(const long *  pArcPoint, bool bClockwise, long& minxRet, long& minyRet,long& maxxRet,  long& maxyRet);


	//功能：得到任意弧段的精确的在弧上的起点和终点
	//参数：输入参数	iPointNum, 点个数
	//	   				pArcPoint, 弧段点数据
	//      输出参数	ppRetPoint, 返回的弧段点数据
	//返回值：
	//		返回的点个数

	static long  GetArcAccurateBeingEndPoint(const long* pArcPoint, long  pRetPoint[4]);


	// 功能：得到任意弧段的打散的点
	//参数：输入参数 iPointNum, 点个数
	//				bClockwise (T：顺时针　F：逆时针)
	//	   			pPoint, 弧段点数据
	//      输出参数 ppDestPoint, 返回的打散的点数据
	//返回值：返回的打散的点个数
	static long  TransArcToPoints(const long pArcPoint[8],bool bClockwise, long ** ppRetPoint, long StepLength = 15);


	//功能：得到带旋转角度的矢量点符号的外接矩形
	//参数：输入参数 pData, 矢量绘制结构原始值
	//				objType 对象的类型
	//	   			Angle, 旋转角度
	//      输出参数 minx,maxX,minY,maxY, 旋转以后的外接矩形
	//返回值：
	static void GetObjectBoxByRotate(long PointCount,const long * pObjData, unsigned char objType, double Angle , long&  minx,  long& maxx, long& miny, long& maxy );

	//函数扩展：以rotX,rotY为旋转中心进行旋转
	static void GetObjectBoxByRotateEx(long PointCount,const long * pObjData, unsigned char objType, long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy );


	//功能：带两种旋转角度的矢量点符号的外接矩形
	//参数：输入参数 pData, 矢量绘制结构原始值
	//				objType 对象的类型
	//				rotXSelf, rotYSelf 自旋中心
	//	   			AngleSelf,	自旋角度
	//				rotX, rotY	外旋中心
	//	   			Angle,		外旋角度
	//      输出参数 minx,maxX,minY,maxY, 旋转以后的外接矩形
	//返回值：
	static void GetObjectBoxByTwoRotate(long PointCount,const long * pObjData, unsigned char objType, long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy );

	//////////////////////////////////////////////////////////////////////////
	//线符号

	//功能：实线得到偏移后的线数据
	//参数：输入参数	pSourLine:原线的点集
	//					nOX:水平偏移
	//					nOY:垂直偏移
	//					JoinsStyle:拐角样式	
	//      输出参数
	//					ppRetLine: 新线的点集
	//返回值：
	//		ppRetLine中点的个数
	static long OffsetLine(long PointCount, const long * pSourLine , long nOX,long nOY, unsigned char JoinsStyle, long ** ppRetLine);


	//功能：标记线符号计算偏移后的线
	//参数：输入参数	pSourLine:原线的点集
	//					nOX:水平偏移
	//					nOY:垂直偏移
	//					JoinsStyle:拐角样式	
	//					MarkCount: 样式单元中标记数
	//					pMarkSpace:样式单元中每个标记的间隔
	//      输出参数
	//					ppRetLine: 返回的绘制标记符号的位置集(点集)
	//					pRetAngle:返回位置处线的角度（弧度）
	//返回值：
	//		ppRetLine中点的个数
	static long OffsetLineByMarkLine(long PointCount,const  long * pSourLine , long nOX, long nOY,unsigned char JoinsStyle, long MarkCount, long * pMarkSpace, long ** ppRetLine, double ** ppRetAngle);


	//功能：虚线符号计算偏移后的线
	//参数：输入参数	pSourLine:原线的点集
	//					nOX:水平偏移
	//					nOY:垂直偏移
	//					JoinsStyle:拐角样式	
	//					MarkCount虚线样式单元中部分数
	//					pMarkSpace每部分的长度集
	//      输出参数
	//					ppRetLine: 返回的绘制虚线符号的位置集(点集)
	//返回值：
	//		ppRetLine中点的个数
	static long OffsetLineByDasheDIS_LINE(long PointCount,const long* pSourLine, long nOX, long nOY, unsigned char  JoinsStyle, long MarkCount, long * pMarkSpace, long **ppRetLine,double **ppRetAngle);


	//功能：得到距离线的首点或尾点一定长度的位置和角度(用于修饰属性)
	//参数：输入参数	pSourLine:原线的点集
	//					nOY:垂直偏移
	//					JoinsStyle:拐角样式	
	//					nDistance:距离值
	//					nDirect:方向 =0 指到首点距离  =1到尾点距离
	//      输出参数
	//					pRetPoint:返回的位置(点)
	//					pRetAngle:返回位置处线的角度（弧度）
	//返回值：
	//		false：　	长度大于线的长度，没有处理而返回
	//					nDirect 不为0 或 1
	//					nDistance < 0
	//需求变更(2005.4.28)：只要点不在第一段或最后一段上，返回F。
	static bool GetPtInLineByDistance(long PointCount,const long * pSourLine, long nOY, unsigned char JointStyle, long nDistance , long nDirect , long * pRetPoint , double* pRetAngle );


	//得到线角度
	static double GetAngleOfLine(long *pStartPoint , long* pEndPoint );

	//功能：取到线上各个节点一定距离的位置集和各位置的角度集（逆时针角度为正）
	//参数：输入参数	pSourLine:原线的点集
	//					nOY:垂直偏移
	//					JoinsStyle:拐角样式	
	//					nDistance:到节点的距离 大于0为线的前向  小于0为线的反向
	//      输出参数
	//					ppRetPoints: 返回的各位置集合
	//					ppRetAngles: 返回的各位置处线的角度集合
	//返回值：
	//		ppRetPoints中点的个数
	static long GetPtsInLineByNodeDistance(long PointCount,const  long * pSourLine, long nOY, unsigned char  JoinsStyle,long nDistance , long ** ppRetPoints, double** ppRetAngles );


	//功能：取线中各子线段的中心位置，返回各位置和该位置线的角度（逆时针角度为正）
	//参数：输入参数	pSourLine:原线的点集
	//					nOY:垂直偏移
	//					JoinsStyle:拐角样式	
	//      输出参数
	//					ppRetPoints: 返回的各位置集合
	//					ppRetAngles: 返回的各位置处线的角度集合
	//返回值：
	//		ppRetPoints中点的个数
	static long GetPtsInSubLineByCenter(long PointCount,const  long * pSourLine, long nOY, unsigned char  JoinsStyle, long ** ppRetPoints, double** ppRetAngles);




	//功能：用给定间隔长度平均分割线，返回各分割点位置和该点处线的角度（逆时针角度为正）
	//参数：输入参数	pSourLine:原线的点集
	//					nOY:垂直偏移
	//					JoinsStyle:拐角样式	
	//					nLength::线分割的间隔长度
	//      输出参数
	//					ppRetPoints: 返回的各位置集合
	//					ppRetAngles: 返回的各位置处线的角度集合
	//返回值：
	//		ppRetPoints中点的个数
	//说明：如果有偏移，定位以原线为准
	static long GetPtsInLineByAvgInterval(long PointCount,const  long * pSourLine, long nOY, unsigned char  JoinsStyle, long nLength , long ** ppRetPoints, double** ppRetAngles);


	//功能：用给定段数(中间点数+1)平均分割线，返回各分割点位置和该点处线的角度（逆时针角度为正）
	//		要求：首尾点去除
	//参数：输入参数	pSourLine:原线的点集
	//					nOY:垂直偏移
	//					JointStyle:拐角样式	
	//					nCount::中间的点个数
	//      输出参数
	//					ppRetPoints: 返回的各位置集合
	//					ppRetAngles: 返回的各位置处线的角度集合
	//返回值：
	//		ppRetPoints中点的个数
	//说明：如果有偏移，定位以原线为准
	static long GetPtsInLineByAvgCount(long PointCount,const  long * pSourLine, long nOY, unsigned char JoinsStyle, long nCount, long ** ppRetPoints, double** ppRetAngles);



	//////////////////////////////////////////////////////////////////////////
	//面符号

	//函数功能：平行线与面矩形的求交，返回一系列平行线
	//输入参数：minx, maxx, miny, maxy 为矩形框
	//			bAbsolutedPos  
	//				T:   OrgX、Y以原点为参照的绝对坐标
	//				F：　OrgX、Y以矩形的（minx,miny）点为参照的相对坐标
	//			OrgX 、OrgY平行线上的点坐标
	//			nOffset线之间偏移量
	//	   		dAngle线的斜角
	//输出参数：ppRetHorizonLine一系列平行线（点对的集合）
	//返回值：	ppRetHorizonLine的线段条数
	static long GetIntersection(long minx, long miny, long maxx, long maxy, bool bAbsolutedPos,long OrgX, long OrgY, double dAngle, long nOffset, long ** ppRetHorizonLine);


	//函数功能：求点集没有旋转前的外接矩形
	//输入参数： 
	//			PointCount 点个数
	//			pSourPolygon 点集数据
	//			dAngle	旋转角度
	//输出参数  minxRet，maxxRet，minyRet，maxyRet, 点集的外接矩形值
	static void GetUnRotateRect(long PointCount,const long* pSourPolygon,double dAngle,long& minxRet, long& minyRet,long& maxxRet,long& maxyRet);



	//////////////////////////////////////////////////////////////////////////
	//参数化对象的四类偏移函数


	//函数功能：(对象的结构偏移) 
	//			将参数化对象偏移，形成新的参数化对象结构
	//输入参数：pObject　参数化对象（纯数据）结构
	//			bType 　参数化对象类型
	//	   		nOffset　偏移量（右正，负左）
	//输出参数：ppRetObject参数化对象（纯数据）结构
	//返回值：	
	//注意事项：
	//			参数化对象经过偏移后，产生一个新的参数化对象。
	static bool  OffsetObjectToStruct(long * pPoints, unsigned char objType, long nOffset, long * pRetObject );




	//函数功能：(对象的离散化偏移)
	//			将参数化对象偏移，形成离散化后的点集
	//输入参数：pObject参数化对象（纯数据）结构
	//			bType 参数化对象类型
	//	   		nOffset　偏移量（右正，负左）
	//			JoinsStyle　拐角样式
	//输出参数：ppRetObject离散化后的点集
	//返回值：	结果点集中点的个数
	//注意事项：
	//			参数化对象经过偏移后，产生离散后的点集
	static long  OffsetObject(const  long * pObjPoints, unsigned char objType, long nOffset, unsigned char JoinsStyle ,long ** ppRetObject );




	////函数功能：(对象的点符号位置偏移)
	////			将参数化对象偏移，形成"标记点符号位置"的点集
	////输入参数：pObject参数化对象（纯数据）结构
	////			bType 参数化对象类型
	////	   		nOffset　偏移量（右正，负左）
	////			JoinsStyle　拐角样式
	////			MarkCount: 样式单元中标记数
	////			PerMarkSpace:样式单元中每个标记的间隔
	////输出参数：	ppRetObject离散化后的点集
	////返回值：	结果点集中点的个数
	////注意事项：
	////			参数化对象经过偏移后，产生一个系列的点集，标记点符号的位置。
	//static long  OffsetObjectByMarkLine (const  long * pObjPoints, unsigned char objType, long nOffset, long MarkCount,unsigned char JoinsStyle, long * PerMarkSpace, long** ppRetObject,  double ** ppRetAngle );


	//函数功能：(对象的"虚线结构"位置偏移)
	//			将参数化对象偏移，形成"间隔标记虚实线的位置"的点集
	//输入参数：pObject参数化对象（纯数据）结构
	//			bType 参数化对象类型
	//	   		nOffset　偏移量（右正，负左）
	//			JoinsStyle　拐角样式
	//			MarkCount: 样式单元中标记数
	//			PerMarkSpace:样式单元中每个标记的间隔
	//输出参数：	ppRetObject离散化后的点集
	//返回值：	结果点集中点的个数
	//注意事项：
	//			参数化对象经过偏移后，产生一系列的点集，间隔标记虚实线的位置。
	static long  OffsetObjectByDasheDIS_LINE(const  long * pObjPoints, unsigned char objType, long nOffset, long MarkCount, unsigned char JoinsStyle, long * PerMarkSpace, long** ppRetObject);


	//////////////////////////////////////////////////////////////////////////
	//2005-5 线文字算法需求

	//功能:返回中点 及其它信息
	//输入参数: 
	//			PointCount 点个数
	//			pSourLine 点的数据
	//返回值: T是原线上的顶点(点在pIndex段尾)
	//			pIndex为第几段(1-n),中点所在的线段号
	//			pMidx,pMidy 中点的XY坐标
	//			pdtLeft,pdtRight(当返回为F时有效,为中点距本线段两端点的距离)
	static bool GetMidPointInfo(long PointCount,const  long * pSourLine,long * pIndex,double * pMidx, double * pMidy,double * pdtLeft, double * pdtRight);


	//功能: 给定间隔长度，计算个分布点位置和角度(扩展)
	//
	//参数：输入参数	PointCount:	原线的点数
	//					pSourLine:	原线的点集
	//					nOY:		垂直偏移
	//					JointStyle:	拐角样式	
	//					nCount:		间隔数(返回的点个数为:nCount+1)
	//					nLength:	线分割的间隔长度
	//					AlignType :	点集在线上的排列方式（左，右，中）
	//      输出参数
	//					ppRetPoints: 返回的各位置集合
	//					ppRetAngles: 返回的各位置处线的角度集合
	//返回值：
	//			ppRetPoints中点的个数
	//说明：
	//		如果有偏移，定位以原线为准
	//		左排列从线的起点开始沿线分布（考虑延长线）
	//		右排列从线的尾点开始沿线分布（考虑延长线）
	//		中排列从线的中间往两侧沿线分布（考虑延长线）
	static long GetPtsInLineByCount_Interval(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nLength ,unsigned char AlignType, long ** ppRetPoints, double** ppRetAngles);

	//功能: 给定间隔数，计算各个分布点位置和角度（在线上平均分散）(扩展)
	//参数：输入参数	PointCount:	原线的点数
	//					pSourLine:	原线的点集
	//					nOY:		垂直偏移
	//					JointStyle:	拐角样式	
	//					nCount:		间隔数(返回的点个数为:nCount+1)
	//					nMinLength:	点间的最小间隔长度
	//      输出参数
	//					ppRetPoints: 返回的各位置集合
	//					ppRetAngles: 返回的各位置处线的角度集合
	//返回值：
	//			ppRetPoints中点的个数
	//说明：
	//			如果线的长度不够，根据左排列方式进行延长。
	static long GetPtsInLineByAvgCountEx(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nMinLength , long ** ppRetPoints, double** ppRetAngles);

	//功能:	线的截取 重组 , 计算截取下来的线数据
	//参数：输入参数	PointCount:	原线的点数
	//					pSourLine:	原线的点集
	//					nRebulidLength:给定长度（可以超过线的长度，超过则加上延长线）
	//					AlignType :	点集在线上的排列方式（左，右，中）
	//      输出参数
	//					ppRetPoints: 返回的各位置集合
	//				
	//返回值：
	//			ppRetPoints中点的个数
	static long ReBuliDIS_LINE(long PointCount,const  long * pSourLine, long nRebulidLength, unsigned char AlignType,long ** ppRetPoints);
};

}



#endif //endif _CTO_DISPLAY_OPTIMIZE