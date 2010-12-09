#pragma once

namespace Element{

class CARTO_DLL CDisRectSet
{
public:
	CDisRectSet(void);
	~CDisRectSet(void);
	DIS_RECT GetBound();
	void AddRect(DIS_RECT rect);
	DIS_RECT GetRect(int nIndex);

	void SetBound(DIS_RECT bound);
	void Offset(double x, double y );
	void MoveTo(double left, double bottom);

private:
	DIS_RECT m_bound;
	std::vector<DIS_RECT> m_rectSet;
};
}
