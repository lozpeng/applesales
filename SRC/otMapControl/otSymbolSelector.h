

#pragma once


// CotSymbolSelector ÃüÁîÄ¿±ê

class CotSymbolSelector : public CCmdTarget
{
	DECLARE_DYNCREATE(CotSymbolSelector)

public:
	CotSymbolSelector();
	virtual ~CotSymbolSelector();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CotSymbolSelector)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	

	enum 
	{
		dispidSelectSymbol = 1L
	};
public:

	IotSymbol* SelectSymbol(IotSymbol* symbol);

};


