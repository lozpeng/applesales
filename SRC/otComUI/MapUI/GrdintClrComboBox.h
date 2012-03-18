#ifndef _GrdintClrComboBox_H_
#define _GrdintClrComboBox_H_

#pragma once

struct GradientColor
{
	COLORREF m_startColor;
	COLORREF m_endColor;
};
// CGrdintClrComboBox

class CGrdintClrComboBox : public CComboBox
{
	//DECLARE_DYNAMIC(CGrdintClrComboBox)

public:
	CGrdintClrComboBox();
	virtual ~CGrdintClrComboBox();

protected:
	//DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	virtual void PreSubclassWindow();
	COLORREF get_curStartColor();
	COLORREF get_curEndColor();

};

#endif //_GrdintClrComboBox_H_
