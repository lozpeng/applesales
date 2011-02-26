//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2010.12
// ������  ������
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
	//����������
	virtual bool Create(const char *title,ProgressMode mode,long ltotal);

	//�رս�����
	virtual void Close();

	//���½���
	virtual void UpdateProgress(const char *message);

	virtual void UpdateProgress(const char *message,double percent);

private:
	
	void *m_pBar;
};

}


#endif