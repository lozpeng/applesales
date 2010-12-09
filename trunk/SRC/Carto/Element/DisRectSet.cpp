#include "StdAfx.h"
#include "DisRectSet.h"
namespace Element{

CDisRectSet::CDisRectSet(void)
{
	m_bound.left = m_bound.right = m_bound.top = m_bound.bottom = 0;
}

CDisRectSet::~CDisRectSet(void)
{
}

DIS_RECT CDisRectSet::GetBound()
{
	return m_bound;
}
void CDisRectSet::AddRect(DIS_RECT rect)
{
	m_rectSet.push_back(rect);
	RectExpandToInclude(m_bound, rect);
}
DIS_RECT CDisRectSet::GetRect(int nIndex)
{
	return m_rectSet[nIndex];
}

void CDisRectSet::Offset(double x, double y )
{
	m_bound.top += y;
	m_bound.bottom += y;
	m_bound.left += x;
	m_bound.right += x;
	for(int i=0; i<m_rectSet.size(); i++)
	{
		DIS_RECT* pRect = &m_rectSet[i];
		pRect->top += y;
		pRect->bottom += y;
		pRect->left += x;
		pRect->right += x;
	}
}

void CDisRectSet::MoveTo(double left, double bottom)
{
	float x = left - m_bound.left;
	float y = bottom - m_bound.bottom;
	Offset(x,y);
}

void CDisRectSet::SetBound(DIS_RECT bound)
{
	m_bound = bound;
}

}