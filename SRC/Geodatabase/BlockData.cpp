#include "stdafx.h"
#include "BlockData.h"
#include <memory.h>

namespace Geodatabase
{

CBlockData::CBlockData()
{
	m_pBuffer=0;
	m_lWidth=0;
	m_lHeight=0;
	m_lBufferWidth=0;
	m_lBufferHeight=0;
	m_Pos.lBand=0;
	m_Pos.lBlockX=0;
	m_Pos.lBlockY=0;
	m_bDirty = false;

}

CBlockData::~CBlockData()
{
	Free();
}

void  CBlockData::Free()
{
	if(m_pBuffer)
		delete m_pBuffer;

	m_pBuffer=0;
}

//初始化缓存的大小
void CBlockData::Create(long lBufferWidth,long lBufferHeight,BANDDATATYPE lDataType)
{
	m_lBufferWidth=lBufferWidth;
	m_lBufferHeight=lBufferHeight;
	m_lDataType=lDataType;

	switch (m_lDataType)
	{
	case BDT_BYTE:
		{
			m_pBuffer=new unsigned char[lBufferWidth*lBufferHeight];
			memset(m_pBuffer,0,lBufferWidth*lBufferHeight);
		}
		break;
	case BDT_SHORT:
		{
			m_pBuffer=new unsigned char[lBufferWidth*lBufferHeight*2];
			memset(m_pBuffer,0,lBufferWidth*lBufferHeight*2);
		}
		break;
	case BDT_USHORT:
		{
			m_pBuffer=new unsigned char[lBufferWidth*lBufferHeight*2];
			memset(m_pBuffer,0,lBufferWidth*lBufferHeight*2);
		}
		break;
	case BDT_LONG:
	case BDT_FLOAT:
		{
			m_pBuffer=new unsigned char[lBufferWidth*lBufferHeight*4];
			memset(m_pBuffer,0,lBufferWidth*lBufferHeight*4);
		}
		break;
	default:
		break;
	}

}

void CBlockData::SetBlockSize(long lWidth, long lHeight)
{
	m_lWidth = lWidth;
	m_lHeight = lHeight;
}

inline void  CBlockData::GetPixel(long lCol, long lRow, void *pVal)
{
	unsigned char* pucVal, *pucVal2;
	unsigned short* pusVal, *pusVal2;
	short *psVal, *psVal2;
	float *pfVal,*pfVal2;

	switch (m_lDataType)
	{
	case 0:
		{
			pucVal = (unsigned char*)m_pBuffer;
			pucVal2 = (unsigned char*)pVal;
			*pucVal2 = *(pucVal+m_lWidth*(lRow-1)+lCol-1);
		}
		break;
	case 1:
		{
			pusVal = (unsigned short*)m_pBuffer;
			pusVal2 = (unsigned short*)pVal;
			*pusVal2 = *(pusVal+m_lWidth*(lRow-1)+lCol-1);
		}
		break;
	case 2:
		{
			psVal = (short *)m_pBuffer;
			psVal2 = (short *)pVal;
			*psVal2 = *(psVal+m_lWidth*(lRow-1)+lCol-1);
		}
		break;
	case 3:
		{
			pfVal = (float *)m_pBuffer;
			pfVal2 = (float *)pVal;
			*pfVal2 =  *(pfVal+m_lWidth*(lRow-1)+lCol-1);
		}
		break;
	default:
		break;
	}


}

inline void CBlockData::SetPixel(long lCol, long lRow, void *pVal)
{
	unsigned char* pucVal, *pucVal2;
	unsigned short* pusVal, *pusVal2;
	short *psVal, *psVal2;
	float *pfVal,*pfVal2;

	switch (m_lDataType)
	{
	case 0:
		{
			pucVal = (unsigned char*)m_pBuffer;
			pucVal2 = (unsigned char*)pVal;
			*(pucVal+m_lWidth*(lRow-1)+lCol-1) =  *pucVal2 ;
		}
		break;
	case 1:
		{
			pusVal = (unsigned short*)m_pBuffer;
			pusVal2 = (unsigned short*)pVal;
			*(pusVal+m_lWidth*(lRow-1)+lCol-1) = *pusVal2 ;
		}
		break;
	case 2:
		{
			psVal = (short *)m_pBuffer;
			psVal2 = (short *)pVal;
			*(psVal+m_lWidth*(lRow-1)+lCol-1) = *psVal2 ;
		}
		break;
	case 3:
		{
			pfVal = (float *)m_pBuffer;
			pfVal2 = (float *)pVal;
			*(pfVal+m_lWidth*(lRow-1)+lCol-1) =  *pfVal2;
		}
		break;
	default:
		break;
	}

	m_bDirty = true;
}

}