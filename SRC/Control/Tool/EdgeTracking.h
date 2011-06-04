
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
	GEOMETRY::geom::Coordinate SeedPoint,CurPoint;//种子点和当前点的世界坐标
	
	long GetPixelInEdge(const POINT& point);
	
public:
	void ReleaseMemory();
	void ResampleToPixel(CPoint *point);
	void PixelToResample(CPoint *point);
	
	float GetGradientValue(POINT point);
	//初始化数据，将图层加入
	void InitRasData(Geodatabase::IRasterDataset* pDataset,long lChannel,GEOMETRY::geom::Envelope stDrawWorldExtent, RECT rect);
	//设置出发点
	void SetSeedPoint(GEOMETRY::geom::Coordinate point);
	//设置当前目标点
	void SetCurPoint(GEOMETRY::geom::Coordinate point);
	
	//通过连续的3个点计算这3个点连线的夹角
	float GetAngleFromThreePoint(const CPoint& pt1, const CPoint& pt2, const CPoint& pt3);

	//计算从出发点到目标点的最短路径
	void GetOptimalPath(long *lCount,POINT **pPathPixel);
	float GetLocalCost(const POINT& PreversePoint, const POINT& NextPoint);
	float GetLocalCost(long PreversePointLoc, long NextPointLoc);	
};

}

#endif 