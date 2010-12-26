//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  ʸ��ѡ�񹤾߻���
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

	//ѡ��ģʽ
	static void SetSelMode(long lSelMode){m_lSelMode = lSelMode;};
	static long GetSelMode(){return m_lSelMode;};

	//�ݲ�
	static void SetSnapTol(int nSnapTol){m_SnapTol = nSnapTol;};
	static int GetSnapTol(){return m_SnapTol;};

protected:

	void Select(Geodatabase::CSimpleQuery *pQuery);

protected:

	Framework::IMapCtrl *m_pMapCtrl;


	//ѡ���ģʽ��ΪCato::SELECT_OPTION����
	static long m_lSelMode;

	static int  m_SnapTol;

};

}


#endif