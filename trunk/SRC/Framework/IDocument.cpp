#include "stdafx.h"
#include "IDocument.h"
#include "IMapCtrl.h"
#include "ILayoutCtrl.h"
#include "ShapefileWorkspaceFactory.h"
#include "ShapefileWorkspace.h"
#include "ShapefileFeatureClass.h"
#include "FeatureLayer.h"
#include "RasterLayer.h"
#include "RasterWSFactory.h"
#include <boost/function.hpp>

namespace Framework
{


	IDocument::IDocument()
	{
		m_linkMapCtrl =NULL;

		m_pLinkMapTree =NULL;

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

	void IDocument::SetLinkLayoutCtrl(ILayoutCtrl *pLayoutCtrl)
	{
		m_linkLayoutCtrl = pLayoutCtrl;
	}

	ILayoutCtrl* IDocument::GetLinkLayoutCtrl()
	{
		return m_linkLayoutCtrl;
	}

	void IDocument::SetLinkMapTree(IMaptreeCtrl* pMapTree)
	{
		m_pLinkMapTree =pMapTree;
	}
    
	IMaptreeCtrl* IDocument::GetLinkMapTree()
	{
		return m_pLinkMapTree;
	}

	void IDocument::LoadImageFile(const char *fileName,bool buildPyd,SYSTEM::IProgress *pProgress)
	{
		CString csDataSourceTmp=fileName;

		CString csThemeName = csDataSourceTmp.Mid (csDataSourceTmp.ReverseFind ('\\') + 1);
		csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));
		

		Geodatabase::IWorkspace* pWorkspace = CRasterWSFactory::GetInstance()->OpenFromFile(fileName);
		Geodatabase::IRasterDatasetPtr pRasterDataset = pWorkspace->OpenRasterDataset(fileName);
		
		if (NULL == pRasterDataset)
			return;

		if(buildPyd)
		{
			//��������
			pRasterDataset->BuildPyramid(0.5,pProgress);
		}

		Carto::ILayerPtr pLayer = Carto::ILayerPtr(new Carto::CRasterLayer());
		pLayer = Carto::ILayer::CreateLayer(pRasterDataset);

		//����ͼ����
		pLayer->SetName(std::string(csThemeName));
		m_pActiveMap->AddLayer(pLayer);

		if(m_pLinkMapTree)
		{
			m_pLinkMapTree->AddLayer(pLayer);
		}
	}

	void IDocument::LoadShpFile(const char *fileName)
	{
		CString csDataSourceTmp=fileName;

		CString csThemeName = csDataSourceTmp.Mid (csDataSourceTmp.ReverseFind ('\\') + 1);
		csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));

		Geodatabase::IWorkspace* ipWorkspace = CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(fileName);
		Geodatabase::IFeatureClassPtr ipFeatureCls = ipWorkspace->OpenFeatureClass(fileName);


		Carto::ILayerPtr pLayer = Carto::ILayerPtr(new Carto::CFeatureLayer());
		pLayer = Carto::ILayer::CreateLayer(ipFeatureCls);
		//����ͼ����
		pLayer->SetName(std::string(csThemeName));
		m_pActiveMap->AddLayer(pLayer);

		if(m_pLinkMapTree)
		{
			m_pLinkMapTree->AddLayer(pLayer);
		}
	}


}