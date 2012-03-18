#include "stdafx.h"
#include "EnviColorMap.h"

CString GetAppPathName()
{
	TCHAR	szProgPath[MAX_PATH*2];
	::GetModuleFileName(NULL, szProgPath, sizeof(szProgPath)/sizeof(TCHAR));    
	CString PathName = szProgPath;
	CString FileName = PathName;
	int    SplashPos = PathName.ReverseFind('\\');
	if(SplashPos>=2 && SplashPos<=PathName.GetLength()-4)
		FileName=PathName.Left(SplashPos);
	return FileName;
}

CEnviColorMap::CEnviColorMap()
{
	/*if(!m_objFile.Open(strFilePath,CFile::modeRead))
	{
		m_bSuccessOpen = false;
		::MessageBox(NULL,"打开颜色文件失败，唯一值渲染功能不可用","提示",MB_OK);
		return;
	}
	else
	{
		m_bSuccessOpen = true;
	}
	BYTE ucColorNum;
	memset(&ucColorNum, 0, sizeof(BYTE));
	m_objFile.Read(&ucColorNum, sizeof(BYTE));
    m_iColorMapCount = ucColorNum;*/
}

CEnviColorMap::~CEnviColorMap(void)
{
	/*if(m_bSuccessOpen)
	{
		m_objFile.Close();
	}*/
}

void CEnviColorMap::GetColorMap(int iIndex,COLOR_MAP& struColorMap)
{
	if(!m_objFile.Open(GetAppPathName() + "\\colors.tbl",CFile::modeRead))
	{
		m_bSuccessOpen = false;
		::MessageBox(NULL,"打开颜色文件失败，唯一值渲染功能不可用","提示",MB_OK);
		return;
	}
	else
	{
		m_bSuccessOpen = true;
	}
	BYTE ucColorNum;
	memset(&ucColorNum, 0, sizeof(BYTE));
	m_objFile.Read(&ucColorNum, sizeof(BYTE));
    m_iColorMapCount = ucColorNum;

	memset(&struColorMap,'\0',sizeof(struColorMap));
	if(iIndex < 0 || iIndex > m_iColorMapCount - 1 || !m_bSuccessOpen)
	{
		return;
	}

	//分别存储颜色表里所有的RGB值
	m_objFile.Seek((1 + 256 * 3 * iIndex)*sizeof(BYTE),m_objFile.begin);
	m_objFile.Read(struColorMap.ucR,256*sizeof(BYTE));
	m_objFile.Read(struColorMap.ucG,256*sizeof(BYTE));
	m_objFile.Read(struColorMap.ucB,256*sizeof(BYTE));
    //读取相应的颜色表的名称
	m_objFile.Seek((1 + 256 * 3 * m_iColorMapCount + iIndex * 32)*sizeof(BYTE),m_objFile.begin);
	m_objFile.Read(struColorMap.szName,32*sizeof(BYTE));
	if(m_bSuccessOpen)
	{
		m_objFile.Close();
	}
}

void CEnviColorMap::GetColorMapCount(int& iColorMapCount)
{
	iColorMapCount = m_iColorMapCount;
}
 bool CEnviColorMap::GetOpenResult()
 {
	 return m_bSuccessOpen;
 }
