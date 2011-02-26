//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2010.10
// 描述：  IProgress提供了描述进度的基类
//////////////////////////////////////////////////////////////////////

#ifndef _SYSTEM_IPROGRESS_H
#define _SYSTEM_IPROGRESS_H

namespace SYSTEM {

class SYSTEM_DLL IProgress
{
public:
	IProgress(void);
	virtual ~IProgress(void);

public:
	enum ProgressMode
	{
		Percent, //百分比
		Count    //次数
	};

	//创建进度条
	virtual bool Create(const char *title,ProgressMode mode,long ltotal);

	//关闭进度条
	virtual void Close();

	//更新进度
	virtual void UpdateProgress(const char *message);

	virtual void UpdateProgress(const char *message,double percent);

};


}


#endif