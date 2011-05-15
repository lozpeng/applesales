#include "StdAfx.h"
#include "DashArrayPropListEx.h"

CDashArrayPropListEx::CDashArrayPropListEx(void)
{
	m_setFocus = false;
}

CDashArrayPropListEx::~CDashArrayPropListEx(void)
{
}
BEGIN_MESSAGE_MAP(CDashArrayPropListEx, CBCGPPropList)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void CDashArrayPropListEx::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CBCGPPropList::OnMouseMove(nFlags, point);
	m_setFocus = true;
}
void CDashArrayPropListEx::OnPropertyChanged (CBCGPProp* pProp) const
{
		_variant_t tmpData=pProp->GetValue();
		if( (float)tmpData > 200.000000f )
		{
			tmpData = 200.000000f;
			pProp->SetValue(tmpData);
		}
		else if( (float)tmpData < 0.000001f )
		{
			tmpData = 0.000001f;
			pProp->SetValue(tmpData);
		}

		CBCGPPropList::OnPropertyChanged(pProp);
}
