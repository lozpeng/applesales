#pragma once
/******************************************************************************
 * $Id: SafeResource.h  2009-09-16 11:13:00 $
 *
 * Project:  SafeResource ����ȫ��Դ�����ࡡ
 * Purpose:  �ṩ�ⲿ������ñ�����ʱ�������������ɰ�ȫʹ�ù�����Դ
 * Author:    �ƺ�־
 * Version:   1.0
 ******************************************************************************/

class CSafeResource
{
public:
	CSafeResource(void);
public:
	~CSafeResource(void);
private:
	void SetRes();
	void ReleaseRes();
private:
	HINSTANCE	hInstOld;
};
