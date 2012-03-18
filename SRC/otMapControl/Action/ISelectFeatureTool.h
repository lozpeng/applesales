#ifndef _ISELECTFEATURE_TOOL_H_
#define _ISELECTFEATURE_TOOL_H_

#include "IAction.h"
#include "SimpleQuery.h"

class  ISelectFeatureTool : public IAction
{
public:
	ISelectFeatureTool(long id);
	virtual ~ISelectFeatureTool();

public:


	static void SetSelMode(long lSelMode){m_lSelMode = lSelMode;};
	static long GetSelMode(){return m_lSelMode;};

	static void SetSnapTol(int nSnapTol){m_SnapTol = nSnapTol;};
	static int GetSnapTol(){return m_SnapTol;};

	virtual void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
	
protected:

	void Select(Geodatabase::CSimpleQuery *pQuery);

	//选择Selectionset在属性表中对应的行
	void SelecRowsInAttributeTable();


protected:
	//选择的模式，为otCato::SELECT_OPTION类型
	static long m_lSelMode;

	static int  m_SnapTol;
};




#endif