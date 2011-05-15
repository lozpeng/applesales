#pragma once

//破折号数组对话框的属性列表控件
class CDashArrayPropListEx :
	public CBCGPPropList
{
public:
	CDashArrayPropListEx(void);
	virtual void OnPropertyChanged (CBCGPProp* pProp) const;
public:
	~CDashArrayPropListEx(void);
public:
	bool m_setFocus;								//判断当前破折号列表属性控件的焦点（当鼠标移出控件，使控件失去焦点）
public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
