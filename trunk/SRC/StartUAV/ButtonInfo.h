#pragma once
#include <vector>
#include <string>
struct stProduct
{
	std::string strIdentity;
	std::string strExeName;
	std::string strTitle;
	std::string strToolTip;
	std::string strURL;
	std::string strIsWeb;
	CRect rect;
};

struct stButIDandName 
{
	UINT m_ButtonID;
	std::string strExeName;
	std::string strURL;
	bool bIsWebURL;
	std::string strTitle;
};