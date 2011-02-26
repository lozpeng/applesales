//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  champion
// 时间：  2010.12
// 描述：  进度条
//////////////////////////////////////////////////////////////////////
#ifndef _PROGRESS_BAR_H
#define _PROGRESS_BAR_H

#include "IProgress.h"

namespace Control
{

class CONTROL_DLL CProgressBar: public SYSTEM::IProgress
{
public:
	CProgressBar(void);
	virtual ~CProgressBar(void);

public:
	//创建进度条
	virtual bool Create(const char *title,ProgressMode mode,long ltotal);

	//关闭进度条
	virtual void Close();

	//更新进度
	virtual void UpdateProgress(const char *message);

	virtual void UpdateProgress(const char *message,double percent);

private:
	
	void *m_pBar;
};

}


#endif