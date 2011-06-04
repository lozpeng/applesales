
#ifndef _EDGETRACKING_H_
#define _EDGETRACKING_H_

#include "RasterLayer.h"
#include "IRasterDataset.h"

namespace Control
{
	struct DirectionP
	{
		long lFirstPointLoc;
		long lNextPointLoc;
	};

class CEdgeTracking  
{
public:
	CEdgeTracking();
	virtual ~CEdgeTracking();

protected:
	void GetActiveMaxGradient(RECT rect);
	void ReadThemeData(const GEOMETRY::geom::Envelope& stDrawWorldExtent, const RECT& rect);
	long lSelectLastPointer;
	long lSelectFirstPointer;
	long* plSelectLocation;
	BOOL *pbPointHaveSelected;
	BOOL *pbPointHaveExpanded;
	float *pfTotalCost;
	DirectionP *pDirection;

	float GetMinPoint(const float *pfTotalCost,long *lLocaotion,const BOOL *pbHaveSearch);
	float mg_fMaxGradient;
	float * mg_pfGradient;
	float * mg_pfGradientX;
	float * mg_pfGradientY;
	float GetMaxGradient();
	long mg_lChannelIndex;
	long mg_ChannelType;
	float GetLaplacian(long lRow,long lCol);
	float GetDirection(long lFirstLocation, long lNextLocation);
	
	Geodatabase::IRasterDataset* m_pDataset;
	unsigned char *mp_pucBufSrc;
	
	long lAreaWidth,lAreaHeight;
	double mp_dblResampleRatio;
	long mp_lSrcWidth,mp_lSrcHeight;
	long mp_lRow1,mp_lRow2,mp_lCol1,mp_lCol2;

	GEOMETRY::geom::Envelope stScreenWorldExtent;
	RECT ScreenRect;

	long mp_lResampleWidth;
	long mp_lResampleHeight;
	long mp_lBufferSize;

	long lArrayLength;
	GEOMETRY::geom::Coordinate SeedPoint,CurPoint;//���ӵ�͵�ǰ�����������
	
	long GetPixelInEdge(const POINT& point);
	
public:
	void ReleaseMemory();
	void ResampleToPixel(CPoint *point);
	void PixelToResample(CPoint *point);
	
	float GetGradientValue(POINT point);
	//��ʼ�����ݣ���ͼ�����
	void InitRasData(Geodatabase::IRasterDataset* pDataset,long lChannel,GEOMETRY::geom::Envelope stDrawWorldExtent, RECT rect);
	//���ó�����
	void SetSeedPoint(GEOMETRY::geom::Coordinate point);
	//���õ�ǰĿ���
	void SetCurPoint(GEOMETRY::geom::Coordinate point);
	
	//ͨ��������3���������3�������ߵļн�
	float GetAngleFromThreePoint(const CPoint& pt1, const CPoint& pt2, const CPoint& pt3);

	//����ӳ����㵽Ŀ�������·��
	void GetOptimalPath(long *lCount,POINT **pPathPixel);
	float GetLocalCost(const POINT& PreversePoint, const POINT& NextPoint);
	float GetLocalCost(long PreversePointLoc, long NextPointLoc);	
};

}

#endif 