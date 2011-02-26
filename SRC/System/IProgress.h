//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2010.10
// ������  IProgress�ṩ���������ȵĻ���
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
		Percent, //�ٷֱ�
		Count    //����
	};

	//����������
	virtual bool Create(const char *title,ProgressMode mode,long ltotal);

	//�رս�����
	virtual void Close();

	//���½���
	virtual void UpdateProgress(const char *message);

	virtual void UpdateProgress(const char *message,double percent);

};


}


#endif