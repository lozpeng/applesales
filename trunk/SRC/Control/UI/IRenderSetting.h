#pragma once

#include "IRender.h"
#include "ILayer.h"
#include "IFeatureClass.h"
#include "IRasterRender.h"
class IRenderSetting
{
public:
	IRenderSetting(void);
	virtual ~IRenderSetting(void);
public:

	virtual long GetRenderType()=0;

	void SetLayer(Carto::ILayer* pLayer);

	virtual Carto::IRenderPtr GetRender() =0;

	virtual Carto::IRasterRenderPtr GetRasterRender(){return NULL;}

	virtual bool CreateDlg(CWnd *pParent) =0;

protected:

	void LoadFields(CWnd *pCmbBox, Geodatabase::IFeatureClass *pFeatureClass);

	//���������͵��ֶ�
	void LoadNumericFields(CWnd *pCmbBox, Geodatabase::IFeatureClass *pFeatureClass);

	//�������ֶ������������ַ�ת�����ֶ�����ID(NUMBER) =ID
	void TrimField(CString &csValue);

	//����һ��������Դ������ͬ��Ĭ�Ϸ���
	Display::ISymbolPtr CreateDefaultSymbol(Geodatabase::IFeatureClass *pFeatureClass);

	//�õ�һ���ֶε������Сֵ
	void GetMinMaxValue(Geodatabase::IFeatureClass *pFeatureClass, CString csFieldName, double *pMax, double *pMin);

protected:
	//��ǰͼ���ָ��
	Carto::ILayer *m_pLayer;


};
