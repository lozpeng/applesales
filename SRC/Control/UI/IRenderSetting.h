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

	//加载数字型的字段
	void LoadNumericFields(CWnd *pCmbBox, Geodatabase::IFeatureClass *pFeatureClass);

	//将带有字段类型描述的字符转换成字段名，ID(NUMBER) =ID
	void TrimField(CString &csValue);

	//产生一个和数据源类型相同的默认符号
	Display::ISymbolPtr CreateDefaultSymbol(Geodatabase::IFeatureClass *pFeatureClass);

	//得到一个字段的最大最小值
	void GetMinMaxValue(Geodatabase::IFeatureClass *pFeatureClass, CString csFieldName, double *pMax, double *pMin);

protected:
	//当前图层的指针
	Carto::ILayer *m_pLayer;


};
