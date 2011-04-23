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
//����ֵ��

//�쳣
#define DP_ERROR					(-1)	
#define DP_FUNC_UNDEAL_ERROR		(-2)	//�����в�Ӧ���ߵ��ĵط�
#define DP_ARRAY_NULL_ERROR			(-3)	//ƫ���ߵĽṹΪ��
#define DP_MARKLINE_ERROR			(-4)	//Mark�ߵ���������
#define DP_MARKCOUNT_ERROR			(-5)	//Mark�ߵ�count����
#define DP_STEP_LENGTH_ERROR		(-6)	//StepLength����


//����
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

	//�ͷš��ײ�⺯����
	static void free_Object(unsigned char ** ppObject);

	static void free_Group(long ** ppGroup);
	static void free_Group(double ** ppGroup);
	//���ܣ����㼯���г�ϡ����
	//������������� iPointNum, Դ�㼯�еĵ����
	//      		 pPoints��Դ�㼯
	//				 length  �����߶���̾���ķ�ֵ���ݲ
	//      ������� ppRetPoints ��ϡ��ĵ����ݣ��㼯��GetPtInLineByDistance
	//����ֵ��
	//		��ϡ��ĵ����
	/*static*/ long DilutePoints(long iPointNum, const long * pPoints, long length, long ** ppRetPoints);
	long DiluteDoublePoints(long iPointNum, const double * pPoints, double length, double ** ppRetPoints);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//�����

	//����˵����
	//���ܣ��õ�������ߵ���͵��������͵�����
	//������������� iPointNum, ���Ƶ����
	//      		 pControlPoint, ���Ƶ�����
	//				 stepLength ��ɢ����ĵ�Ĳ�����Ĭ��Ϊ2��
	//				 curveRate Ϊ���ߵ�����(ƽ��)�̶�(0--1) ��Ĭ��Ϊ0.25
	//      ������� ppCurvePoint, ��͵�����
	//����ֵ����͵�����
	static long  GetCurvePoint(long iPointNum,const  long * pControlPoint, long ** ppCurvePoint,long stepLength=15,double curveRate=0.25);

	static void  GetArcBox(const long *  pArcPoint, bool bClockwise, long& minxRet, long& minyRet,long& maxxRet,  long& maxyRet);


	//���ܣ��õ����⻡�εľ�ȷ���ڻ��ϵ������յ�
	//�������������	iPointNum, �����
	//	   				pArcPoint, ���ε�����
	//      �������	ppRetPoint, ���صĻ��ε�����
	//����ֵ��
	//		���صĵ����

	static long  GetArcAccurateBeingEndPoint(const long* pArcPoint, long  pRetPoint[4]);


	// ���ܣ��õ����⻡�εĴ�ɢ�ĵ�
	//������������� iPointNum, �����
	//				bClockwise (T��˳ʱ�롡F����ʱ��)
	//	   			pPoint, ���ε�����
	//      ������� ppDestPoint, ���صĴ�ɢ�ĵ�����
	//����ֵ�����صĴ�ɢ�ĵ����
	static long  TransArcToPoints(const long pArcPoint[8],bool bClockwise, long ** ppRetPoint, long StepLength = 15);


	//���ܣ��õ�����ת�Ƕȵ�ʸ������ŵ���Ӿ���
	//������������� pData, ʸ�����ƽṹԭʼֵ
	//				objType ���������
	//	   			Angle, ��ת�Ƕ�
	//      ������� minx,maxX,minY,maxY, ��ת�Ժ����Ӿ���
	//����ֵ��
	static void GetObjectBoxByRotate(long PointCount,const long * pObjData, unsigned char objType, double Angle , long&  minx,  long& maxx, long& miny, long& maxy );

	//������չ����rotX,rotYΪ��ת���Ľ�����ת
	static void GetObjectBoxByRotateEx(long PointCount,const long * pObjData, unsigned char objType, long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy );


	//���ܣ���������ת�Ƕȵ�ʸ������ŵ���Ӿ���
	//������������� pData, ʸ�����ƽṹԭʼֵ
	//				objType ���������
	//				rotXSelf, rotYSelf ��������
	//	   			AngleSelf,	�����Ƕ�
	//				rotX, rotY	��������
	//	   			Angle,		�����Ƕ�
	//      ������� minx,maxX,minY,maxY, ��ת�Ժ����Ӿ���
	//����ֵ��
	static void GetObjectBoxByTwoRotate(long PointCount,const long * pObjData, unsigned char objType, long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy );

	//////////////////////////////////////////////////////////////////////////
	//�߷���

	//���ܣ�ʵ�ߵõ�ƫ�ƺ��������
	//�������������	pSourLine:ԭ�ߵĵ㼯
	//					nOX:ˮƽƫ��
	//					nOY:��ֱƫ��
	//					JoinsStyle:�ս���ʽ	
	//      �������
	//					ppRetLine: ���ߵĵ㼯
	//����ֵ��
	//		ppRetLine�е�ĸ���
	static long OffsetLine(long PointCount, const long * pSourLine , long nOX,long nOY, unsigned char JoinsStyle, long ** ppRetLine);


	//���ܣ�����߷��ż���ƫ�ƺ����
	//�������������	pSourLine:ԭ�ߵĵ㼯
	//					nOX:ˮƽƫ��
	//					nOY:��ֱƫ��
	//					JoinsStyle:�ս���ʽ	
	//					MarkCount: ��ʽ��Ԫ�б����
	//					pMarkSpace:��ʽ��Ԫ��ÿ����ǵļ��
	//      �������
	//					ppRetLine: ���صĻ��Ʊ�Ƿ��ŵ�λ�ü�(�㼯)
	//					pRetAngle:����λ�ô��ߵĽǶȣ����ȣ�
	//����ֵ��
	//		ppRetLine�е�ĸ���
	static long OffsetLineByMarkLine(long PointCount,const  long * pSourLine , long nOX, long nOY,unsigned char JoinsStyle, long MarkCount, long * pMarkSpace, long ** ppRetLine, double ** ppRetAngle);


	//���ܣ����߷��ż���ƫ�ƺ����
	//�������������	pSourLine:ԭ�ߵĵ㼯
	//					nOX:ˮƽƫ��
	//					nOY:��ֱƫ��
	//					JoinsStyle:�ս���ʽ	
	//					MarkCount������ʽ��Ԫ�в�����
	//					pMarkSpaceÿ���ֵĳ��ȼ�
	//      �������
	//					ppRetLine: ���صĻ������߷��ŵ�λ�ü�(�㼯)
	//����ֵ��
	//		ppRetLine�е�ĸ���
	static long OffsetLineByDasheDIS_LINE(long PointCount,const long* pSourLine, long nOX, long nOY, unsigned char  JoinsStyle, long MarkCount, long * pMarkSpace, long **ppRetLine,double **ppRetAngle);


	//���ܣ��õ������ߵ��׵��β��һ�����ȵ�λ�úͽǶ�(������������)
	//�������������	pSourLine:ԭ�ߵĵ㼯
	//					nOY:��ֱƫ��
	//					JoinsStyle:�ս���ʽ	
	//					nDistance:����ֵ
	//					nDirect:���� =0 ָ���׵����  =1��β�����
	//      �������
	//					pRetPoint:���ص�λ��(��)
	//					pRetAngle:����λ�ô��ߵĽǶȣ����ȣ�
	//����ֵ��
	//		false����	���ȴ����ߵĳ��ȣ�û�д��������
	//					nDirect ��Ϊ0 �� 1
	//					nDistance < 0
	//������(2005.4.28)��ֻҪ�㲻�ڵ�һ�λ����һ���ϣ�����F��
	static bool GetPtInLineByDistance(long PointCount,const long * pSourLine, long nOY, unsigned char JointStyle, long nDistance , long nDirect , long * pRetPoint , double* pRetAngle );


	//�õ��߽Ƕ�
	static double GetAngleOfLine(long *pStartPoint , long* pEndPoint );

	//���ܣ�ȡ�����ϸ����ڵ�һ�������λ�ü��͸�λ�õĽǶȼ�����ʱ��Ƕ�Ϊ����
	//�������������	pSourLine:ԭ�ߵĵ㼯
	//					nOY:��ֱƫ��
	//					JoinsStyle:�ս���ʽ	
	//					nDistance:���ڵ�ľ��� ����0Ϊ�ߵ�ǰ��  С��0Ϊ�ߵķ���
	//      �������
	//					ppRetPoints: ���صĸ�λ�ü���
	//					ppRetAngles: ���صĸ�λ�ô��ߵĽǶȼ���
	//����ֵ��
	//		ppRetPoints�е�ĸ���
	static long GetPtsInLineByNodeDistance(long PointCount,const  long * pSourLine, long nOY, unsigned char  JoinsStyle,long nDistance , long ** ppRetPoints, double** ppRetAngles );


	//���ܣ�ȡ���и����߶ε�����λ�ã����ظ�λ�ú͸�λ���ߵĽǶȣ���ʱ��Ƕ�Ϊ����
	//�������������	pSourLine:ԭ�ߵĵ㼯
	//					nOY:��ֱƫ��
	//					JoinsStyle:�ս���ʽ	
	//      �������
	//					ppRetPoints: ���صĸ�λ�ü���
	//					ppRetAngles: ���صĸ�λ�ô��ߵĽǶȼ���
	//����ֵ��
	//		ppRetPoints�е�ĸ���
	static long GetPtsInSubLineByCenter(long PointCount,const  long * pSourLine, long nOY, unsigned char  JoinsStyle, long ** ppRetPoints, double** ppRetAngles);




	//���ܣ��ø����������ƽ���ָ��ߣ����ظ��ָ��λ�ú͸õ㴦�ߵĽǶȣ���ʱ��Ƕ�Ϊ����
	//�������������	pSourLine:ԭ�ߵĵ㼯
	//					nOY:��ֱƫ��
	//					JoinsStyle:�ս���ʽ	
	//					nLength::�߷ָ�ļ������
	//      �������
	//					ppRetPoints: ���صĸ�λ�ü���
	//					ppRetAngles: ���صĸ�λ�ô��ߵĽǶȼ���
	//����ֵ��
	//		ppRetPoints�е�ĸ���
	//˵���������ƫ�ƣ���λ��ԭ��Ϊ׼
	static long GetPtsInLineByAvgInterval(long PointCount,const  long * pSourLine, long nOY, unsigned char  JoinsStyle, long nLength , long ** ppRetPoints, double** ppRetAngles);


	//���ܣ��ø�������(�м����+1)ƽ���ָ��ߣ����ظ��ָ��λ�ú͸õ㴦�ߵĽǶȣ���ʱ��Ƕ�Ϊ����
	//		Ҫ����β��ȥ��
	//�������������	pSourLine:ԭ�ߵĵ㼯
	//					nOY:��ֱƫ��
	//					JointStyle:�ս���ʽ	
	//					nCount::�м�ĵ����
	//      �������
	//					ppRetPoints: ���صĸ�λ�ü���
	//					ppRetAngles: ���صĸ�λ�ô��ߵĽǶȼ���
	//����ֵ��
	//		ppRetPoints�е�ĸ���
	//˵���������ƫ�ƣ���λ��ԭ��Ϊ׼
	static long GetPtsInLineByAvgCount(long PointCount,const  long * pSourLine, long nOY, unsigned char JoinsStyle, long nCount, long ** ppRetPoints, double** ppRetAngles);



	//////////////////////////////////////////////////////////////////////////
	//�����

	//�������ܣ�ƽ����������ε��󽻣�����һϵ��ƽ����
	//���������minx, maxx, miny, maxy Ϊ���ο�
	//			bAbsolutedPos  
	//				T:   OrgX��Y��ԭ��Ϊ���յľ�������
	//				F����OrgX��Y�Ծ��εģ�minx,miny����Ϊ���յ��������
	//			OrgX ��OrgYƽ�����ϵĵ�����
	//			nOffset��֮��ƫ����
	//	   		dAngle�ߵ�б��
	//���������ppRetHorizonLineһϵ��ƽ���ߣ���Եļ��ϣ�
	//����ֵ��	ppRetHorizonLine���߶�����
	static long GetIntersection(long minx, long miny, long maxx, long maxy, bool bAbsolutedPos,long OrgX, long OrgY, double dAngle, long nOffset, long ** ppRetHorizonLine);


	//�������ܣ���㼯û����תǰ����Ӿ���
	//��������� 
	//			PointCount �����
	//			pSourPolygon �㼯����
	//			dAngle	��ת�Ƕ�
	//�������  minxRet��maxxRet��minyRet��maxyRet, �㼯����Ӿ���ֵ
	static void GetUnRotateRect(long PointCount,const long* pSourPolygon,double dAngle,long& minxRet, long& minyRet,long& maxxRet,long& maxyRet);



	//////////////////////////////////////////////////////////////////////////
	//���������������ƫ�ƺ���


	//�������ܣ�(����Ľṹƫ��) 
	//			������������ƫ�ƣ��γ��µĲ���������ṹ
	//���������pObject�����������󣨴����ݣ��ṹ
	//			bType ����������������
	//	   		nOffset��ƫ����������������
	//���������ppRetObject���������󣨴����ݣ��ṹ
	//����ֵ��	
	//ע�����
	//			���������󾭹�ƫ�ƺ󣬲���һ���µĲ���������
	static bool  OffsetObjectToStruct(long * pPoints, unsigned char objType, long nOffset, long * pRetObject );




	//�������ܣ�(�������ɢ��ƫ��)
	//			������������ƫ�ƣ��γ���ɢ����ĵ㼯
	//���������pObject���������󣨴����ݣ��ṹ
	//			bType ��������������
	//	   		nOffset��ƫ����������������
	//			JoinsStyle���ս���ʽ
	//���������ppRetObject��ɢ����ĵ㼯
	//����ֵ��	����㼯�е�ĸ���
	//ע�����
	//			���������󾭹�ƫ�ƺ󣬲�����ɢ��ĵ㼯
	static long  OffsetObject(const  long * pObjPoints, unsigned char objType, long nOffset, unsigned char JoinsStyle ,long ** ppRetObject );




	////�������ܣ�(����ĵ����λ��ƫ��)
	////			������������ƫ�ƣ��γ�"��ǵ����λ��"�ĵ㼯
	////���������pObject���������󣨴����ݣ��ṹ
	////			bType ��������������
	////	   		nOffset��ƫ����������������
	////			JoinsStyle���ս���ʽ
	////			MarkCount: ��ʽ��Ԫ�б����
	////			PerMarkSpace:��ʽ��Ԫ��ÿ����ǵļ��
	////���������	ppRetObject��ɢ����ĵ㼯
	////����ֵ��	����㼯�е�ĸ���
	////ע�����
	////			���������󾭹�ƫ�ƺ󣬲���һ��ϵ�еĵ㼯����ǵ���ŵ�λ�á�
	//static long  OffsetObjectByMarkLine (const  long * pObjPoints, unsigned char objType, long nOffset, long MarkCount,unsigned char JoinsStyle, long * PerMarkSpace, long** ppRetObject,  double ** ppRetAngle );


	//�������ܣ�(�����"���߽ṹ"λ��ƫ��)
	//			������������ƫ�ƣ��γ�"��������ʵ�ߵ�λ��"�ĵ㼯
	//���������pObject���������󣨴����ݣ��ṹ
	//			bType ��������������
	//	   		nOffset��ƫ����������������
	//			JoinsStyle���ս���ʽ
	//			MarkCount: ��ʽ��Ԫ�б����
	//			PerMarkSpace:��ʽ��Ԫ��ÿ����ǵļ��
	//���������	ppRetObject��ɢ����ĵ㼯
	//����ֵ��	����㼯�е�ĸ���
	//ע�����
	//			���������󾭹�ƫ�ƺ󣬲���һϵ�еĵ㼯����������ʵ�ߵ�λ�á�
	static long  OffsetObjectByDasheDIS_LINE(const  long * pObjPoints, unsigned char objType, long nOffset, long MarkCount, unsigned char JoinsStyle, long * PerMarkSpace, long** ppRetObject);


	//////////////////////////////////////////////////////////////////////////
	//2005-5 �������㷨����

	//����:�����е� ��������Ϣ
	//�������: 
	//			PointCount �����
	//			pSourLine �������
	//����ֵ: T��ԭ���ϵĶ���(����pIndex��β)
	//			pIndexΪ�ڼ���(1-n),�е����ڵ��߶κ�
	//			pMidx,pMidy �е��XY����
	//			pdtLeft,pdtRight(������ΪFʱ��Ч,Ϊ�е�౾�߶����˵�ľ���)
	static bool GetMidPointInfo(long PointCount,const  long * pSourLine,long * pIndex,double * pMidx, double * pMidy,double * pdtLeft, double * pdtRight);


	//����: ����������ȣ�������ֲ���λ�úͽǶ�(��չ)
	//
	//�������������	PointCount:	ԭ�ߵĵ���
	//					pSourLine:	ԭ�ߵĵ㼯
	//					nOY:		��ֱƫ��
	//					JointStyle:	�ս���ʽ	
	//					nCount:		�����(���صĵ����Ϊ:nCount+1)
	//					nLength:	�߷ָ�ļ������
	//					AlignType :	�㼯�����ϵ����з�ʽ�����ң��У�
	//      �������
	//					ppRetPoints: ���صĸ�λ�ü���
	//					ppRetAngles: ���صĸ�λ�ô��ߵĽǶȼ���
	//����ֵ��
	//			ppRetPoints�е�ĸ���
	//˵����
	//		�����ƫ�ƣ���λ��ԭ��Ϊ׼
	//		�����д��ߵ���㿪ʼ���߷ֲ��������ӳ��ߣ�
	//		�����д��ߵ�β�㿪ʼ���߷ֲ��������ӳ��ߣ�
	//		�����д��ߵ��м����������߷ֲ��������ӳ��ߣ�
	static long GetPtsInLineByCount_Interval(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nLength ,unsigned char AlignType, long ** ppRetPoints, double** ppRetAngles);

	//����: �������������������ֲ���λ�úͽǶȣ�������ƽ����ɢ��(��չ)
	//�������������	PointCount:	ԭ�ߵĵ���
	//					pSourLine:	ԭ�ߵĵ㼯
	//					nOY:		��ֱƫ��
	//					JointStyle:	�ս���ʽ	
	//					nCount:		�����(���صĵ����Ϊ:nCount+1)
	//					nMinLength:	������С�������
	//      �������
	//					ppRetPoints: ���صĸ�λ�ü���
	//					ppRetAngles: ���صĸ�λ�ô��ߵĽǶȼ���
	//����ֵ��
	//			ppRetPoints�е�ĸ���
	//˵����
	//			����ߵĳ��Ȳ��������������з�ʽ�����ӳ���
	static long GetPtsInLineByAvgCountEx(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nMinLength , long ** ppRetPoints, double** ppRetAngles);

	//����:	�ߵĽ�ȡ ���� , �����ȡ������������
	//�������������	PointCount:	ԭ�ߵĵ���
	//					pSourLine:	ԭ�ߵĵ㼯
	//					nRebulidLength:�������ȣ����Գ����ߵĳ��ȣ�����������ӳ��ߣ�
	//					AlignType :	�㼯�����ϵ����з�ʽ�����ң��У�
	//      �������
	//					ppRetPoints: ���صĸ�λ�ü���
	//				
	//����ֵ��
	//			ppRetPoints�е�ĸ���
	static long ReBuliDIS_LINE(long PointCount,const  long * pSourLine, long nRebulidLength, unsigned char AlignType,long ** ppRetPoints);
};

}



#endif //endif _CTO_DISPLAY_OPTIMIZE