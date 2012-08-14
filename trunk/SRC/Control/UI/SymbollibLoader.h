/* Generated by Together */


//注意:必须在使用该类前调用AfxOleInit()函数,否则无法打开数据库.
#ifndef _SYMBOLLIBLOADER_H_
#define _SYMBOLLIBLOADER_H_

#include <vector>
using namespace std;

#import "c:\\Program Files\\Common Files\\System\\ado\\MSADO15.DLL" rename("EOF","adoEOF")
#import "c:\\Program Files\\Common Files\\System\\ADO\\msadox.dll" rename_namespace("ADOX")\
	rename("_Collection","_CollectionX")\
	rename("_DynaCollection","_DynaCollectionX")\
	rename("DataTypeEnum","DataTypeEnumX")\
	rename("Properties","PropertiesX")\
	rename("Property","PropertyX")   

#include "ISymbol.h"

//用来访问符号库,目前符号库用mdb来保存

class __declspec(dllexport) CSymbolLibLoader 
{
public:
	CSymbolLibLoader();

	~CSymbolLibLoader();
public:
	// 添加符号
	bool AddSymbol(Display::ISymbolPtr pSymbol);

	bool OpenDatabase(const char *FileName);

	// 更新符号
	bool UpdateSymbol(Display::ISymbolPtr pSymbol);

	// 删除符号
	bool DelSymbol(const char* queryName, long type);

	// 查询符号
	vector<Display::ISymbolPtr> QuerySymbols(const char* queryName, long type);

	bool IsConnection();

	bool CreateDataBase(const char *FileName);
private:
	bool CreateTable();
	void CloseDatabase();
private:
	CString m_strFilePathName;
	ADODB::_ConnectionPtr m_pConnection;

	_variant_t SerializeSymbol(Display::ISymbolPtr pSymbol);
	Display::ISymbolPtr UnSerializeSymbol(_variant_t &vt);
public:
	CString GetName(void);
	BOOL bVisible;
};

#endif //CSYMBOLLIBACCESS_H
