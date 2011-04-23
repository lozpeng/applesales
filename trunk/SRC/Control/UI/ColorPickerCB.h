
#if !defined(AFX_COLORPICKERCB_H__C74333B7_A13A_11D1_ADB6_C04D0BC10000__INCLUDED_)
#define AFX_COLORPICKERCB_H__C74333B7_A13A_11D1_ADB6_C04D0BC10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "EnviColorMap.h"
               
class CColorPickerCB : public CComboBox
{
// Construction
public:
	CColorPickerCB();

// Implementation
public:
	virtual	~CColorPickerCB();
private:
    CEnviColorMap* m_pEnviColorMap;
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
protected:
	virtual void PreSubclassWindow();
public:
	///<summary>
	///获得当强选择颜色的颜色值
	///</summary>
	///<param neme ="iIndex">当前下拉框的选择元素</param>
	///<param name="struColorMap">读取的颜色表的信息</param>
	///<returns>返回当前文件夹所在的路径</returns>
	void   GetColorMap(int iIndex,COLOR_MAP& struColorMap);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPICKERCB_H__C74333B7_A13A_11D1_ADB6_C04D0BC10000__INCLUDED_)
