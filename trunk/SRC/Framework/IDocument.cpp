#include "stdafx.h"
#include "IDocument.h"
#include "IMapCtrl.h"
#include <boost/function.hpp>

namespace Framework
{


IDocument::IDocument()
{
	m_linkMapCtrl =NULL;

	m_index =0;
}

IDocument::~IDocument()
{

}

long IDocument::GetMapCount() const
{
	return (long)m_pMaps.size();
}

void IDocument::SetActiveMap(Carto::CMapPtr pMap)
{
	m_pActiveMap =pMap;
	if(m_linkMapCtrl)
	{
	   //����ͼ�����ؼ�
       m_linkMapCtrl->SetMap(pMap);
	}
}

Carto::CMapPtr IDocument::GetActiveMap()
{
	return m_pActiveMap;
}

Carto::CMapPtr IDocument::GetMap(long index)
{
	if(index<0 || index>=m_pMaps.size())
	{
		return NULL;
	}
	return m_pMaps[index];
}

long IDocument::AddNewMap()
{
	//�½�һ����ͼ
	Carto::CMapPtr ptrMap = new Carto::CMap();

	CString strName;

	m_index++;
	strName.Format("��ͼ - %d",m_index);
	
	ptrMap->SetName(std::string(strName));

	
	AddMap(ptrMap);

	return long(m_pMaps.size()) - 1;
}

void IDocument::AddMap(Carto::CMapPtr pMap)
{
	m_pMaps.push_back(pMap);
}


void IDocument::DeleteMap(long index)
{
	if(index<0 || index>=m_pMaps.size())
	{
		return ;
	}
	m_pMaps.erase(m_pMaps.begin()+index);
}

void IDocument::SetLinkMapCtrl(Framework::IMapCtrl *pMapCtrl)
{
	m_linkMapCtrl =pMapCtrl;
}



}