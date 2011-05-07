#include "stdafx.h"
#include "IRasterDataset.h"
#include "IWorkspace.h"
#include "IRasterCatalog.h"

namespace Geodatabase{


IRasterDataset::IRasterDataset(IWorkspace *pWorkspace,IRasterCatalog *pRasterCatalog):IGeodataObject(pWorkspace)
{
	m_objType =GDT_RASTERDATASET;
	m_pRasterCatalog =pRasterCatalog;

	//图块大小
	m_blockXSize=512; 
	m_blockYSize=512;
	

}

IRasterDataset::~IRasterDataset()
{

}



bool IRasterDataset::IsWritable()
{
	return false;
}


long IRasterDataset::GetBandCount()
{
	return 0;
}

bool IRasterDataset::GetSize(long *plWidth, long *plHeight)
{
	return false;
}

bool IRasterDataset::GetCellSize (double *pdblSizeX, double *pdblSizeY)
{
	return false;
}

BANDDATATYPE IRasterDataset::GetBandDataType(long lChannelIndex)
{
	return BDT_UNKNOWN;
}


bool IRasterDataset::GetBandMinMaxValue(long lChannelIndex, double *pvMaxValue, double *pvMinValue)
{
	return false;
}



/*@*****************************坐标转换，投影相关接口*****************************************@*/


bool IRasterDataset::SetCoordinateExtent(const GEOMETRY::geom::Envelope &extent)
{
	return false;
}


bool IRasterDataset::WorldToPixel (double dblX, double dblY, long *plCol,long *plRow)
{
	return false;
}


bool IRasterDataset::PixelToWorld ( long lCol,long lRow, double *pdblX, double *pdblY)
{
	return false;

}


std::string IRasterDataset::GetProjection()
{
	return "";
}


bool IRasterDataset::SetProjection(const char *pszWKT)
{
	return false;
}


/*@*****************************数据读取相关接口********************************************@*/

bool    IRasterDataset::GetPixel(long lChannelIndex,long lCol, long lRow,  void *pvValue)
{
	return false;
}

bool	IRasterDataset::SetPixel(long lChannelIndex,long lCol,  long lRow, void *pvValue)
{
	return false;
}

bool IRasterDataset::DataReadBandNormalize(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer,double& minValue,double& maxValue)
{
	return false;
}

bool IRasterDataset::DataReadBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, void *pvBuffer)
{
	return false;
}

bool IRasterDataset::DataWriteBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, void *pvBuffer)
{
	return false;
}


/*@*****************************获得调色板、LUT等信息的接口*********************************@*/

bool    IRasterDataset::GetChannelPalette(long lChannelIndex, BYTE *pbRed, BYTE *pbGreen, BYTE *pbBlue)
{
	return false;
}

bool	IRasterDataset::SetChannelPalette(long lChannelIndex, BYTE *pbRed, BYTE *pbGreen, BYTE *pbBlue)
{
	return false;
}

bool	IRasterDataset::GetChannelLUT(long lChannelIndex, BYTE *&pbLUT, long *plNodesCount , GEOMETRY::geom::Coordinate* pstPts )
{
	for(int i=0; i<256; ++i)
		pbLUT[i] = BYTE(i);
	return true;
}

bool	IRasterDataset::SetChannelLUT(long lChannelIndex, BYTE *pbLUT, long lNodesCount , GEOMETRY::geom::Coordinate* pstPts )
{
	return false;
}

/*@*****************************金字塔操作相关接口********************************************@*/

bool	IRasterDataset::HasPyramid()
{
	return false;
}

//建立金字塔
bool IRasterDataset::BuildPyramid(double dResample,SYSTEM::IProgress*)
{
	return false;
}

bool IRasterDataset::DataReadPyramidBand(long lLevel, long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight,long lBuffSizeX, long lBuffSizeY, void *pvBuffer)
{
	return false;
}


bool IRasterDataset::GetPyramidSize( long lLevel, long *lWidth, long *lHeight)
{
	return false;
}

bool IRasterDataset::GetPyramidCellSize(long lLevel, double *pdCellX, double *pdCellY)
{
	return false;
}

bool IRasterDataset::GetPyramidLevelNum(long *lLevelNum)
{
	return false;
}

bool IRasterDataset::ReadPyramidNormal(long lLevel,long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer)
{
	return false;
}

bool IRasterDataset::CreateBuffer()
{
	static int nDataNum =50;
	long lBandCount;
	BANDDATATYPE lDataType;
	long lwidth,lheight;

	GetSize(&lwidth, &lheight);
	lBandCount =GetBandCount();
	lDataType =GetBandDataType(1);

	//获取格层金字塔分辨率与分块数
	m_blockXCount=(lwidth-1)/m_blockXSize+1;
	m_blockYCount=(lheight-1)/m_blockYSize+1;

	//创建索引表
	long lBlockCount = lBandCount*m_blockYCount*m_blockXCount;
	m_indexTable = new BDlist<CBlockData*>::pointer[lBlockCount];

	for(int k=0; k<lBlockCount; k++)
		m_indexTable[k] = NULL;


	//创建位图队列
	for(int i=0;i<nDataNum;i++)
	{
		CBlockData *tempData=new CBlockData();
		tempData->Create(m_blockXSize,m_blockYSize,lDataType);
		m_DataQueue.push_back(tempData);
	}

	m_qIndex=m_DataQueue.Loc(1);//定位到链表的第一个元素

	return true;
}

bool IRasterDataset::FlushBuffer()
{
	long lWidth,lHeight;
	GetSize(&lWidth, &lHeight);
	long lSCol,lSRow;

	BDlist<CBlockData*>::pointer p=m_DataQueue.head;
	for(long i=0;i<m_DataQueue.length;i++)
	{
		if(p->data->m_bDirty)
		{
			lSCol = (p->data->m_Pos.lBlockX-1)*m_blockXSize + 1;
			lSRow = (p->data->m_Pos.lBlockY-1)*m_blockYSize + 1;

			lWidth = ((lWidth-lSCol+1)<m_blockXSize) ? (lWidth-lSCol+1) : m_blockXSize;
			lHeight = ((lHeight-lSRow+1)<m_blockYSize) ? (lHeight-lSRow+1) : m_blockYSize;

			if(p->data->m_bDirty)
				DataWriteBand(p->data->m_Pos.lBand, lSCol, lSRow, lWidth, lHeight,p->data->m_pBuffer);

		}
		p=p->next;
	}
	return true;
}

bool IRasterDataset::DeleteBuffer()
{
	FlushBuffer();
	BDlist<CBlockData*>::pointer p=m_DataQueue.head;

	for(long i=0;i<m_DataQueue.length;i++)
	{
		delete p->data;
		p=p->next;
	}
	m_DataQueue.Clear();
	delete []m_indexTable;

	return true;
}

bool IRasterDataset::PixelIO(long lBandIndex, long lCol, long lRow, void *pvValue, bool bRead )
{
    long lwidth,lheight;
	GetSize(&lwidth,&lheight);

	if(lCol<1 || lCol>lwidth || lRow<1 || lRow>lheight)
	{
		return false;
	}

	long lBlockIndex;
	STBlockPos pos;
	pos.lBand = lBandIndex;
	pos.lBlockX = (lCol-1)/m_blockXSize + 1;
	pos.lBlockY = (lRow-1)/m_blockYSize + 1;

	lBlockIndex = (pos.lBand-1)*m_blockXCount*m_blockYCount + (pos.lBlockY-1)*m_blockXCount + (pos.lBlockX-1);

	long lWidth,lHeight;
	long lSCol,lSRow;

	if(m_indexTable[lBlockIndex] == 0)
	{
		//空闲块内容如果dirty,存盘
		lSCol = (m_qIndex->data->m_Pos.lBlockX-1)*m_blockXSize + 1;
		lSRow = (m_qIndex->data->m_Pos.lBlockY-1)*m_blockYSize + 1;

		lWidth = ((lwidth-lSCol+1)<m_blockXSize) ? (lwidth-lSCol+1) : m_blockXSize;
		lHeight = ((lheight-lSRow+1)<m_blockYSize) ? (lheight-lSRow+1) : m_blockYSize;

		if(m_qIndex->data->m_bDirty)
			DataWriteBand(m_qIndex->data->m_Pos.lBand, lSCol, lSRow, lWidth, lHeight,m_qIndex->data->m_pBuffer);

		//
		long lOldBlockIndex;
		lOldBlockIndex = (m_qIndex->data->m_Pos.lBand-1)*m_blockXCount*m_blockYCount + (m_qIndex->data->m_Pos.lBlockY-1)*m_blockXCount + (m_qIndex->data->m_Pos.lBlockX-1);
		if(lOldBlockIndex>=0)
			m_indexTable[lOldBlockIndex]=0; 
		m_indexTable[lBlockIndex]=m_qIndex; 
		m_qIndex->data->m_Pos=pos;
		m_qIndex->data->m_bDirty=false;

		//
		lSCol = (m_qIndex->data->m_Pos.lBlockX-1)*m_blockXSize + 1;
		lSRow = (m_qIndex->data->m_Pos.lBlockY-1)*m_blockYSize + 1;

		lWidth = ((lwidth-lSCol+1)<m_blockXSize) ? (lwidth-lSCol+1) : m_blockXSize;
		lHeight = ((lheight-lSRow+1)<m_blockYSize) ? (lheight-lSRow+1) : m_blockYSize;
		m_qIndex->data->SetBlockSize(lWidth,lHeight);

		DataReadBand(m_qIndex->data->m_Pos.lBand, lSCol, lSRow, lWidth, lHeight, lWidth, lHeight,m_qIndex->data->m_pBuffer);

		//
		m_qIndex=m_qIndex->next;
	}

	//将当前访问的位图移动到链表头
	else
	{
		if(m_indexTable[lBlockIndex]==m_qIndex)
		{
			m_qIndex=m_qIndex->next;
		}
		else if(m_indexTable[lBlockIndex] == m_qIndex->prior)
		{

		}
		else
		{
			BDlist<CBlockData*>::pointer p=m_indexTable[lBlockIndex];
			p->prior->next=p->next;
			p->next->prior=p->prior;

			m_qIndex->prior->next=p;
			p->prior=m_qIndex->prior;
			p->next=m_qIndex;
			m_qIndex->prior=p;	
		}
	}

	lSCol = (m_indexTable[lBlockIndex]->data->m_Pos.lBlockX-1)*m_blockXSize + 1;
	lSRow = (m_indexTable[lBlockIndex]->data->m_Pos.lBlockY-1)*m_blockYSize + 1;


	if(bRead)
	{
		//long lCol2=lCol-lSCol+1;
		//long lRow2=lRow-lSRow+1;
		//GET_PIXEL(lCol2,lRow2,pvValue,m_indexTable[lBlockIndex]->data);
		m_indexTable[lBlockIndex]->data->GetPixel(lCol-lSCol+1, lRow-lSRow+1,pvValue);
	}
	else
	{
		//long lCol2=lCol-lSCol+1;
		//long lRow2=lRow-lSRow+1;
		//SET_PIXEL(lCol2,lRow2,pvValue,m_indexTable[lBlockIndex]->data);
		m_indexTable[lBlockIndex]->data->SetPixel(lCol-lSCol+1, lRow-lSRow+1, pvValue);
	}


	return true;
}


} //namespace Geodatabase