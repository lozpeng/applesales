#pragma once


class CCursorMgr
{
public:
	CCursorMgr(HMODULE hResource);
	~CCursorMgr(void);
public:
	static HCURSOR GetCursor(long type);

protected:
	std::vector<HCURSOR> m_cursors;

};
