#include "StdAfx.h"
#include "IProgress.h"

namespace SYSTEM {

IProgress::IProgress(void)
{
}

IProgress::~IProgress(void)
{
}

bool IProgress::Create(const char *title,ProgressMode mode, long ltotal)
{
	return false;
}

void IProgress::UpdateProgress(const char *message)
{

}

void IProgress::UpdateProgress(const char *message,double percent)
{

}

void IProgress::Close()
{

}

}
