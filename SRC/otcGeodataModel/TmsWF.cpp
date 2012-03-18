// TmsWF.cpp : CTmsWF 的实现

#include "stdafx.h"
#include "TmsWF.h"


// CTmsWF
CTmsWF::CTmsWF()
{
	//m_pFactory =CTmsWorkspaceFactory::GetInstance();
}

STDMETHODIMP CTmsWF::OpenFromFile(BSTR filename, IotWorkspace **workspace)
{
	//if(!m_pFactory)
	//{
	//	*workspace =NULL;
	//	return E_FAIL;
	//}

	//_bstr_t filepath =filename;
	//Geodatabase::IWorkspace *pws =m_pFactory->OpenFromFile((const char*)filepath);

	//if(!pws)
	//{
	//	*workspace =NULL;
	//	return E_FAIL;
	//}

	//IOriginDataPtr pData;
	//CoCreateInstance(CLSID_otWorkspace,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	////塞入IWorkspace的指针
	//pData->put_OriginData((long)pws);

	//IotWorkspace *pWorkspace;
	//pData->QueryInterface(__uuidof(IotWorkspace),(void**)&pWorkspace);

	//*workspace =pWorkspace;


	return S_OK;
}

STDMETHODIMP CTmsWF::OpenFolder(BSTR name, IotWorkspace** retWorkspace)
{
	//if(!m_pFactory)
	//{
	//	*retWorkspace =NULL;
	//	return E_FAIL;
	//}

	//_bstr_t filepath =name;
	//Geodatabase::IWorkspace *pws =m_pFactory->OpenFolder((const char*)filepath);

	//if(!pws)
	//{
	//	*retWorkspace =NULL;
	//	return E_FAIL;
	//}

	//IOriginDataPtr pData;
	//CoCreateInstance(CLSID_otWorkspace,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	////塞入IWorkspace的指针
	//pData->put_OriginData((long)pws);

	//IotWorkspace *pWorkspace;
	//pData->QueryInterface(__uuidof(IotWorkspace),(void**)&pWorkspace);

	//*retWorkspace =pWorkspace;

	return S_OK;
}
