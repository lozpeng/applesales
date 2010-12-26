//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  矢量选择工具基类
//////////////////////////////////////////////////////////////////////
#ifndef _ISelectFeatureTool_H
#define _ISelectFeatureTool_H

#include "ITool.h"
#include "IMapCtrl.h"
#include "SimpleQuery.h"
namespace Control
{

class  ISelectFeatureTool: public Framework::ITool
{
public:
	ISelectFeatureTool(const char* name);
	~ISelectFeatureTool();

public:

	//选择模式
	static void SetSelMode(long lSelMode){m_lSelMode = lSelMode;};
	static long GetSelMode(){return m_lSelMode;};

	//容差
	static void SetSnapTol(int nSnapTol){m_SnapTol = nSnapTol;};
	static int GetSnapTol(){return m_SnapTol;};

protected:

	void Select(Geodatabase::CSimpleQuery *pQuery);

protected:

	Framework::IMapCtrl *m_pMapCtrl;


	//选择的模式，为Cato::SELECT_OPTION类型
	static long m_lSelMode;

	static int  m_SnapTol;

};

}


#endif