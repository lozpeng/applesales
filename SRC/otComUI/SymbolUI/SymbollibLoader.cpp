#include "stdafx.h"
#include "SymbollibLoader.h"
#include "SymbolFactory.h"

CSymbolLibLoader::CSymbolLibLoader()
{
	m_pConnection = NULL;
}

CSymbolLibLoader::~CSymbolLibLoader()
{
	CloseDatabase();
}

bool CSymbolLibLoader::AddSymbol(Display::ISymbolPtr pSymbol)
{
	
	_variant_t vt;
	vt.Attach( SerializeSymbol( pSymbol ) );

	m_pConnection->BeginTrans();
	ADODB::_RecordsetPtr pRec;
	long iID;
	try {
		pRec.CreateInstance(__uuidof(ADODB::Recordset));
		pRec->CacheSize = 10000;
		pRec->CursorLocation = ADODB::adUseClient;
		HRESULT hr = pRec->Open(_variant_t("OTSYMBOL"), 
			_variant_t((IDispatch *) m_pConnection, true),
			ADODB::adOpenKeyset,
			ADODB::adLockPessimistic,
			ADODB::adCmdTable);
		if( FAILED(hr) ) 
		{
//			WarningLog("Open OTSYMBOL Failed！");
			m_pConnection->RollbackTrans();
			return false;
		}
		if( pRec->adoEOF == VARIANT_TRUE )
			iID = 1;
		else
		{
			pRec->MoveLast();
			iID = pRec->GetRecordCount() + 1;
		}
		pSymbol->SetID( iID );

		pRec->AddNew();

		pRec->Fields->GetItem(_variant_t("ID"))->Value = pSymbol->GetID();
		pRec->Fields->GetItem(_variant_t("Name"))->Value = pSymbol->GetLabel().c_str();
		pRec->Fields->GetItem(_variant_t("TYPE"))->Value = (long)(pSymbol->GetType()&0xF0);
		pRec->Fields->GetItem(_variant_t("DATA"))->Value = vt;

		pRec->Update();
		pRec->Close();
		pRec = NULL;
		m_pConnection->CommitTrans();

	}
	catch(_com_error e)
	{
		//WarningLog("Open OTSYMBOL Failed！-- %s", (char*)e.Description() );

		pRec = NULL;
		m_pConnection->RollbackTrans();

		return false;
	}

	return true;
}
bool CSymbolLibLoader::CreateDataBase(const char *FileName)
{
	try
	{
		ADOX::_CatalogPtr pCat; 
		CString strSource("Provider=Microsoft.JET.OLEDB.4.0;Data source =");
		strSource += FileName;
		pCat.CreateInstance(__uuidof(ADOX::Catalog));   
		pCat->Create(_bstr_t(strSource));
	}
	catch(_com_error e)
	{
//		OTWARNING((char*)e.Description());
		return false;
	}
	return true;
}
bool CSymbolLibLoader::CreateTable()
{
	try
	{
		char BufSQL[1024];
		_variant_t vt;
		sprintf(BufSQL,"create table OTSYMBOL(ID long NOT NULL  , TYPE int, Name TEXT(50), DATA image)");
		m_pConnection->Execute(BufSQL,&vt,-1);
		sprintf(BufSQL,"alter table OTSYMBOL ADD CONSTRAINT MK primary key (TYPE, NAME )");
		m_pConnection->Execute(BufSQL,&vt,-1);
	}
	catch(_com_error e)
	{
//		OTWARNING((char*)e.Description());
		return FALSE;
	}
	return TRUE;
}

_variant_t CSymbolLibLoader::SerializeSymbol(Display::ISymbolPtr pSymbol)
{
	SYSTEM::CBinArchive bin;

	pSymbol->serialization( bin );

	return bin.ExportToVariant();
}

Display::ISymbolPtr CSymbolLibLoader::UnSerializeSymbol(_variant_t &vt)
{
	SYSTEM::CBinArchive bin( vt.parray->pvData , vt.parray->rgsabound[0].cElements );

	Display::ISymbolPtr pSymbol = Display::CSymbolFactory::CreateSymbolFromStream( bin );

	return pSymbol;

}

bool CSymbolLibLoader::UpdateSymbol(Display::ISymbolPtr pSymbol)
{
	
	_variant_t vt;
	vt = SerializeSymbol( pSymbol );

	m_pConnection->BeginTrans();
	ADODB::_RecordsetPtr pRec;

	char cSql[1024];
	sprintf(cSql, "SELECT * FROM OTSYMBOL WHERE Name='%s'",pSymbol->GetLabel() );
	try
	{
		pRec.CreateInstance(__uuidof(ADODB::Recordset));
		pRec->CacheSize = 10000;
		pRec->CursorLocation = ADODB::adUseClient;
		pRec->Open(_variant_t(cSql), 
			m_pConnection.GetInterfacePtr(),
			ADODB::adOpenKeyset,
			ADODB::adLockPessimistic,
			ADODB::adCmdText);
		if( pRec->adoEOF == VARIANT_TRUE )
		{
//			WarningLog("Open OTSYMBOL Failed！");
			m_pConnection->RollbackTrans();
			return false;
		}

		pRec->Fields->GetItem(_variant_t("ID"))->Value = pSymbol->GetID();
		pRec->Fields->GetItem(_variant_t("Name"))->Value = pSymbol->GetLabel().c_str();
		pRec->Fields->GetItem(_variant_t("TYPE"))->Value = (long)pSymbol->GetType();
		pRec->Fields->GetItem(_variant_t("DATA"))->Value = vt;

		pRec->Update();
		pRec->Close();
		pRec = NULL;
		m_pConnection->CommitTrans();
	}
	catch(_com_error e)
	{
		//OTLOG(eError , (char*)e.Description());
	}


	return true;
}

bool CSymbolLibLoader::OpenDatabase(const char *FileName)
{
	
	try
	{
		m_pConnection.CreateInstance(__uuidof(ADODB::Connection));
		CString strSource("Provider=Microsoft.Jet.OLEDB.4.0;Persist Security Info=False;Data Source=");
		strSource += FileName;
		HRESULT hr=m_pConnection->Open(_bstr_t(strSource),"","",ADODB::adModeUnknown);
		if(FAILED( hr ))
		{
			::MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd , "文件读取错误,可能不是Access文件" , "警告", MB_OK );
			return false;
		}
		CreateTable();

		bVisible = true;
	}
	catch(_com_error e)
	{
		m_pConnection = NULL;
//		OTLOG(eError , (char*)e.Description());
		return false;
	}
	return true;
}

void CSymbolLibLoader::CloseDatabase()
{
	
		if( m_pConnection != NULL )
			m_pConnection->Close();
	
}

bool CSymbolLibLoader::DelSymbol(char* queryName, long type)
{
	
	ADODB::_RecordsetPtr pRec;
	char cSql[1024];
	sprintf(cSql, "SELECT DATA FROM OTSYMBOL WHERE Name='%s' AND TYPE = %ld",queryName , type );
	try
	{
		pRec.CreateInstance(__uuidof(ADODB::Recordset));
		pRec->CacheSize = 10000;
		pRec->CursorLocation = ADODB::adUseClient;
		pRec->Open(_variant_t(cSql), 
			m_pConnection.GetInterfacePtr(),
			ADODB::adOpenKeyset,
			ADODB::adLockPessimistic,
			ADODB::adCmdText);

		if( pRec->adoEOF == VARIANT_TRUE )
			return false;

		pRec->Delete(ADODB::adAffectAll);
		pRec->Update();
		pRec->Close();
	}
	catch(_com_error e)
	{
//		OTLOG(eError , (char*)e.Description());
	}
	pRec = NULL;
	return true;
}


Display::ISymbolPtr CSymbolLibLoader::QuerySymbol(const char *queryName)
{
	ADODB::_RecordsetPtr pRec;
	char cSql[1024];
	if( strlen( queryName ) == 0 )
	{
		return NULL;
	}
	else
		sprintf(cSql, "SELECT DATA FROM OTSYMBOL WHERE Name LIKE '%s'",queryName);

	pRec.CreateInstance(__uuidof(ADODB::Recordset));
	pRec->CacheSize = 10000;
	pRec->CursorLocation = ADODB::adUseClient;
	try
	{
		pRec->Open(_variant_t(cSql), 
			m_pConnection.GetInterfacePtr(),
			ADODB::adOpenStatic,
			ADODB::adLockOptimistic,
			ADODB::adCmdText );

	}
	catch (_com_error e)
	{
//		OTLOG(eError , (char*)e.Description());
	}

	Display::ISymbolPtr pSymbol;

	for( ; pRec->adoEOF == VARIANT_FALSE ; pRec->MoveNext() )
	{
		pSymbol= UnSerializeSymbol( pRec->Fields->GetItem(_variant_t("DATA"))->Value );
	}
	pRec->Close();
	pRec = NULL;
	return pSymbol;
}
// 查询符号
Display::ISymbolArrayPtr CSymbolLibLoader::QuerySymbols(const char* queryName, long type)
{
	
	type = type&0xF0;
	Display::ISymbolArrayPtr pSymbolArray(new Display::CSymbolArray());

	ADODB::_RecordsetPtr pRec;
	char cSql[1024];
	if( strlen( queryName ) == 0 )
		sprintf(cSql, "SELECT DATA FROM OTSYMBOL WHERE TYPE = %ld", type );
	else
		sprintf(cSql, "SELECT DATA FROM OTSYMBOL WHERE Name LIKE '%s%s' AND TYPE = %ld",queryName ,"%", type );

	pRec.CreateInstance(__uuidof(ADODB::Recordset));
	pRec->CacheSize = 10000;
	pRec->CursorLocation = ADODB::adUseClient;
	try
	{
		pRec->Open(_variant_t(cSql), 
			m_pConnection.GetInterfacePtr(),
			ADODB::adOpenStatic,
			ADODB::adLockOptimistic,
			ADODB::adCmdText );

	}
	catch (_com_error e)
	{
//		OTLOG(eError , (char*)e.Description());
	}

	for( ; pRec->adoEOF == VARIANT_FALSE ; pRec->MoveNext() )
	{
		pSymbolArray->Add( UnSerializeSymbol( pRec->Fields->GetItem(_variant_t("DATA"))->Value ) );
	}
	pRec->Close();
	pRec = NULL;
	return pSymbolArray;
}

CString CSymbolLibLoader::GetName(void)
{
	return m_strFilePathName;
}
bool CSymbolLibLoader::IsConnection()
{
	return m_pConnection == NULL ? true : false;
}