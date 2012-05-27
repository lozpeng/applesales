#ifndef _HSL_GrdintClrComboBox_H_
#define _HSL_GrdintClrComboBox_H_

#include "ColorDefine.h"

// CGrdintClrComboBox

class CHSLGrdintClrComboBox : public CComboBox
{
	//DECLARE_DYNAMIC(CHSLGrdintClrComboBox)

public:
	CHSLGrdintClrComboBox();
	virtual ~CHSLGrdintClrComboBox();

protected:
	//DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	virtual void PreSubclassWindow();
	Display::HSLColor get_curStartColor();
	Display::HSLColor get_curEndColor();

};

#endif //_GrdintClrComboBox_H_
