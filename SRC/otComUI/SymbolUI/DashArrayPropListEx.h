#pragma once

//���ۺ�����Ի���������б�ؼ�
class CDashArrayPropListEx :
	public CBCGPPropList
{
public:
	CDashArrayPropListEx(void);
	virtual void OnPropertyChanged (CBCGPProp* pProp) const;
public:
	~CDashArrayPropListEx(void);
public:
	bool m_setFocus;								//�жϵ�ǰ���ۺ��б����Կؼ��Ľ��㣨������Ƴ��ؼ���ʹ�ؼ�ʧȥ���㣩
public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
