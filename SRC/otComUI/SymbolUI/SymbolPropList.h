#pragma once


//enum UNITS{OT_UNITS_PELS=0,OT_UNITS_CM=1,OT_UNITS_MM=2};//�������Ѷ���

#define DISPLAYNODE "Display"
#define SYMBOLCFG  "SymbolConfig"
#include "ISymbolPropListInterface.h"
#include "DashArray.h"

//////////////////////////////////////////////////////////////////////////
class CBCGPFontSelectProp : public CBCGPProp
{
public:
	CBCGPFontSelectProp(const CString& strGroupName, DWORD dwData = 0,
		BOOL bIsValueList = FALSE);

	CBCGPFontSelectProp(const CString& strName, const _variant_t& varValue, 
		LPCTSTR lpszDescr = NULL, DWORD dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
		LPCTSTR lpszValidChars = NULL);
	virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);
};

//////////////////////////////////////////////////////////////////////////
class CBCGPFilePropEx : public CBCGPFileProp
{
public:
	CBCGPFilePropEx(const CString& strName, const CString& strFolderName, DWORD dwData = 0, LPCTSTR lpszDescr = NULL);
	CBCGPFilePropEx(const CString& strName, BOOL bOpenFileDialog, const CString& strFileName, 
		LPCTSTR lpszDefExt = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		LPCTSTR lpszFilter = NULL,
		LPCTSTR lpszDescr = NULL, DWORD dwData = 0);
	virtual ~CBCGPFilePropEx();
public:
	virtual void OnClickButton (CPoint point);
};
//////////////////////////////////////////////////////////////////////////
class CCustomEdit : public CEdit
{
public:
	CCustomEdit( CBCGPProp *prop , CBCGPPropList *propList );
public:	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	CBCGPProp *m_pProp;
	CBCGPPropList *m_pPropList;
};
//////////////////////////////////////////////////////////////////////////
class CBCGPPropEx : public CBCGPProp
{
public:
	CBCGPPropEx(const CString& strGroupName, DWORD dwData = 0,
		BOOL bIsValueList = FALSE);

	// Simple property
	CBCGPPropEx(const CString& strName, const _variant_t& varValue, 
		LPCTSTR lpszDescr = NULL, DWORD dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
		LPCTSTR lpszValidChars = NULL);
	virtual ~CBCGPPropEx();

	int GetMaxValue();
	int GetMinValue();
	void EnableSpinControl (BOOL bEnable = TRUE, int nMin = 0, int nMax = 0);
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual BOOL OnClickValue (UINT uiMsg, CPoint point);
	virtual CSpinButtonCtrl* CreateSpinControl (CRect rectSpin);
	void Update();
};

//////////////////////////////////////////////////////////////////////////
class CCustomDlgProp : public CBCGPProp
{
public:
	CCustomDlgProp(
		const CString& strName,
		const _variant_t& varValue , LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
		);

protected:
	virtual BOOL HasButton () const	{	return TRUE;	}
	virtual void OnClickButton (CPoint point);
};
//////////////////////////////////////////////////////////////////////////
class CCharSymbolSelectProp : public CCustomDlgProp
{
public:
	CCharSymbolSelectProp(CSymbolPropList* propList,
		const CString& strName,
		const _variant_t& varValue , LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
		);
	int GetMaxValue();
	int GetMinValue();
	virtual void OnClickButton (CPoint point);
private:
	CSymbolPropList* m_pPropList;
};
//////////////////////////////////////////////////////////////////////////
class CSymbolProp : public CBCGPProp
{
public:
	CSymbolProp(CWnd *pWnd ,
		const CString& strName,
		_variant_t &value,
		LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
		);

	virtual void OnDrawValue (CDC* pDC, CRect rect);

	virtual CString FormatProperty ();

	void SetSymbol( _variant_t &vt );
	Display::ISymbolPtr GetSymbol();

	virtual BOOL HasButton () const	{	return TRUE;	}
	virtual void OnClickButton (CPoint point);

	Display::ISymbolPtr m_pSymbol;
	CWnd *m_pParentWnd;
	_variant_t m_symbolData;
};

//////////////////////////////////////////////////////////////////////////
class CDashArrayExProp : public CBCGPProp
{
public:
	CDashArrayExProp(
		const CString& strName,
		Display::CDashArray *dashArray,
		LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
		);
	~CDashArrayExProp();
	void SetDashArray(Display::CDashArray *dashArray);
	void SetSymbolType(SYMBOL_TYPE type);
protected:
	virtual BOOL HasButton () const	{	return TRUE;	}
	virtual void OnClickButton (CPoint point);
private:
	Display::CDashArray *m_dashArray;
	SYMBOL_TYPE m_enumSymbolType;
};
//////////////////////////////////////////////////////////////////////////
class CBCGPColorPropEx : public CBCGPColorProp
{
public:
	CBCGPColorPropEx(const CString& strName, const COLORREF& color, 
		CPalette* pPalette = NULL, LPCTSTR lpszDescr = NULL, DWORD dwData = 0);
	virtual ~CBCGPColorPropEx();

	void ReSetPalette(IMAGE_COLOR * imagePalette = NULL);
	virtual void OnClickButton (CPoint point);
protected:
	static void InitColors (IMAGE_COLOR * imagePalette , CArray<COLORREF, COLORREF>& arColors);
};
//////////////////////////////////////////////////////////////////////////
// CSymbolPropList

class CSymbolPropList : public CBCGPPropList
{
	friend class CCharSymbolSelectProp;
	DECLARE_DYNAMIC(CSymbolPropList)

public:
	CSymbolPropList();
	~CSymbolPropList();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// ͨ��һ���������ͳ�ʼ������
	virtual bool InitSymbolPropList(int SymbolType);
	// ����һ������
	virtual bool SetSymbol(Display::ISymbolPtr pSymbol);
	// ���Create���������д����ͳ�ʼ������
	virtual bool InitWindow(CRect& rectPropList, CWnd* pWnd, UINT nID);

	virtual void SetUnit( SYSTEM::SYS_UNIT_TYPE newUnit);									//�����µĳ��ȵ�λ
protected:
	ISymbolPropListInterface *m_propListInterface;
	SYSTEM::IConfigItemPtr m_pSymCfg;
	CArray< SYSTEM::IConfigItemPtr > m_pSymCfgItems;
	Display::ISymbolPtr m_pSymbol;
	int m_SymbolType;
	SYSTEM::SYS_UNIT_TYPE m_enumUnit;									//��ǰ�ĵ�λ
	float m_fPelsToMmRate;									//����ת���ױ���
	float m_fMmToPelsRate;									//����ת����
	float m_fPelsToCmRate;									//����ת����
	float m_fCmToPelsRate;									//����ת����
	float m_fDmToPelsRate;									//����ת����
	float m_fPelsToDmRate;									//����ת����
	float m_fPointToMmRate;									//��ת����
	float m_fMmToPointRate;									//����ת��


	float m_lWide , m_lWideNegative;
	float m_ulWide;
	float m_angleWide;


	//CStringArray m_PropNames,m_EnablePropNames;
	// ͨ�����ͻ�����ýڵ�
	SYSTEM::IConfigItemPtr GetSymbolConfigItem(int type);
	// ͨ��һ�����ýڵ㣬����һ������������
	CBCGPProp* GetSymbolItem(SYSTEM::IConfigItemPtr pItemCfg);
	//��ʱ������
public:
	bool m_bCurrentForce;									//��ǰ�Ƿ���н���
public:

	void SetSymbolPropListInterface( ISymbolPropListInterface * propListInterface);

	virtual void OnPropertyChanged (CBCGPProp* pProp) const;		//��Ӧ���Կ�������
	// ���·��ŵ���Ӧ����
	bool UpDataSymbol();
	void SetSymbolValueToPropList(Display::ISymbolPtr pSymbol, CBCGPProp* pGroup);
	void SetPropListToSymbolValue(CBCGPProp* pGroup) const;

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	//static BOOL CALLBACK AFX_EXPORT EnumFamScreenCallBackEx(
	//	ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* /*lpntm*/, 
	//	int FontType, LPVOID pThis);
};


