#include "StdAfx.h"
#include "SafeResource.h"

CSafeResource::CSafeResource(void)
{
	SetRes();
}
CSafeResource::~CSafeResource(void)
{
	ReleaseRes();
}
void CSafeResource::SetRes()
{
	hInstOld = AfxGetResourceHandle();
	AfxSetResourceHandle(hStyleResource);
}
void CSafeResource::ReleaseRes()
{
	AfxSetResourceHandle(hInstOld);
}
