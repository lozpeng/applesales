#pragma once
#include "Field.h"
#include "afxwin.h"
#include "resource.h"

// CDlgFieldProperty 对话框

class CDlgFieldProperty : public CDialog
{
	DECLARE_DYNAMIC(CDlgFieldProperty)

public:
	CDlgFieldProperty(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFieldProperty();

// 对话框数据
	enum { IDD = IDD_FIELD_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void	 SetName( const char* szName );
	void	 SetType( Geodatabase::FIELD_TYPE szType );
	void	 SetLength( long nLength );
	void	 SetPrecision( long nPrecision );

	void SetVisible( bool bVisible );
	bool GetVisible( void );
	
	void SetDecimalNum( long nNum );
	long GetDecimalNum( void );

protected:
	CString m_strName;
	CString m_strType;
	long	m_nLength;
	long	m_nPrecise;

	BOOL	m_bInVisible;
	long	m_nNumDecimal;
	CEdit m_edtDec;

public:
	virtual BOOL OnInitDialog();

	
};
