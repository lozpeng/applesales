// otLayerProperty.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "otMapControl.h"
#include "otLayerProperty.h"
#include "otLayerProp.h"
#include "FeatureLayer.h"
#include "RasterLayer.h"
#include "otMapCtrl.h"
// CotLayerProperty

IMPLEMENT_DYNCREATE(CotLayerProperty, CCmdTarget)


CotLayerProperty::CotLayerProperty()
{
	EnableAutomation();

	AfxOleLockApp();
}

CotLayerProperty::~CotLayerProperty()
{
	AfxOleUnlockApp();
}


void CotLayerProperty::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CotLayerProperty, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CotLayerProperty, CCmdTarget)
	DISP_FUNCTION_ID(CotLayerProperty, "ShowLayerProperty", dispidShowLayerProperty, ShowLayerProperty, VT_EMPTY, VTS_UNKNOWN VTS_DISPATCH)
END_DISPATCH_MAP()

// ע��: ������� IID_IotLayerProperty ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {63E2AB56-8483-4405-AB79-40B81AEF1CCC}
static const IID IID_IotLayerProperty =
{ 0x63E2AB56, 0x8483, 0x4405, { 0xAB, 0x79, 0x40, 0xB8, 0x1A, 0xEF, 0x1C, 0xCC } };

BEGIN_INTERFACE_MAP(CotLayerProperty, CCmdTarget)
	INTERFACE_PART(CotLayerProperty, IID_IotLayerProperty, Dispatch)
END_INTERFACE_MAP()


// {798B7203-4A4B-48a9-B802-FB4C66246040}
IMPLEMENT_OLECREATE(CotLayerProperty, "otMapControl.otLayerProperty", 0x798b7203, 0x4a4b, 0x48a9, 0xb8, 0x2, 0xfb, 0x4c, 0x66, 0x24, 0x60, 0x40)






// CotLayerProperty ��Ϣ�������

class CLayerCallback : public otComUI::ILayerPropCallback
{
public:
	CLayerCallback(void){m_pMapControl =NULL;}

public:
	void SetMapCtrl(CotMapCtrl *pMapControl) {m_pMapControl =pMapControl;}

	virtual void UpdateMapCtrl()
	{
		if(m_pMapControl)
		{
			m_pMapControl->Refresh();
		}
	}
private:

	CotMapCtrl *m_pMapControl; 

};

void CotLayerProperty::ShowLayerProperty(IotLayer* layer,IDispatch *MapControl)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
	CotMapCtrl *pMapCtrl =(CotMapCtrl*)CotMapCtrl::FromIDispatch(MapControl);
    CLayerCallback callback;
	callback.SetMapCtrl(pMapCtrl);

	Carto::ILayerPtr pLayer =ConvertILayer(layer);

	if(!pLayer)
	{
		return;
	}

	//����ͼ������ԶԻ���
	if(otComUI::CotLayerProp::ShowLayerProp(pLayer,&callback)==IDOK)
	{
		pMapCtrl->Refresh();
		
	}
	
}


Carto::ILayerPtr CotLayerProperty::ConvertILayer(IotLayer *layer)
{
	if(!layer)
	{
		return NULL;
	}
	IOriginDataPtr pData;
	layer->QueryInterface(__uuidof(IOriginData),(void**)&pData);
	long ldata;
	pData->get_OriginData(&ldata);

	otLayerType type;
	layer->get_LayerType(&type);

	Carto::ILayerPtr retLayer;

	switch(type)
	{
	case OT_FeatureLayer:
		{
			retLayer =*((Carto::IFeatureLayerPtr*)ldata);
			break;
		}
	case OT_RasterLayer:
		{
			retLayer =*((Carto::CRasterLayerPtr*)ldata);
			break;
		}
	case OT_GraphicLayer:
		{

			retLayer =*((Carto::CGraphicLayerPtr*)ldata);
			break;
		}
	default:
		break;
	}

	return retLayer;
}