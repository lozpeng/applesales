#pragma once
/******************************************************************************
 * $Id: SafeResource.h  2009-09-16 11:13:00 $
 *
 * Project:  SafeResource 　安全资源调度类　
 * Purpose:  提供外部程序调用本工程时，声明该类对象可安全使用工程资源
 * Author:    黄鸿志
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
