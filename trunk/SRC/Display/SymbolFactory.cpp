#include "stdafx.h"
#include "SimpleMarkerSymbol.h"
#include "CharMarkerSymbol.h"
//#include "ArrowMarkerSymbol.h"
//#include "PicMarkerSymbol.h"
//#include "ComplexMarkerSymbol.h"
#include "SimpleLineSymbol.h"
//#include "AdvLineSymbol.h"
//#include "MarkerLineSymbol.h"
//#include "HashLineSymbol.h"

//#include "ComplexLineSymbol.h"
#include "SimpleFillSymbol.h"
#include "SimpleFillSymbol.h"
//#include "MarkerFillSymbol.h"
//#include "LineFillSymbol.h"
//#include "PicFillSymbol.h"
//#include "GradientFillSymbol.h"
//#include "ComplexFillSymbol.h"
#include "TextSymbol.h"
#include "SymbolFactory.h"

#include <sstream>
#include <boost/filesystem.hpp>
#include "IArchive.h"
using namespace std;

Display::CSymbolFactory g_SymbolFactory;

//SYSTEM::XMLConfigurationPtr ptrSymbolRender = NULL;

//static std::map< std::string , Display::IExtSymbolInterFacePtr >::iterator curItem;

//SYSTEM::XMLConfigurationPtr Display::GetSymbolRenderConfig()
//{
//	if(ptrSymbolRender == NULL)
//	{
//		ptrSymbolRender = new otSystem::CXMLConfiguration;
//		try
//		{
//			boost::filesystem::path path = otSystem::CSystemPath::GetCoreSystemPath();
//			path /= "ctColor.dll";
//			ptrSymbolRender->Open(path.native_file_string());
//		}
//		catch(std::exception&)
//		{
//			ErrorLog("open ctColor.tbl file failed.");
//			return NULL;
//		}
//	}
//
//	return ptrSymbolRender;
//
//}
//
//void Display::ReleaseSymbolRenderConfig()
//{
//	ptrSymbolRender.reset();
//}

Display::CSymbolFactory::CSymbolFactory(void)//:SYSTEM::CLibraryMgr("GetExtSymbol", "", "ExtSymbol")
{
//	Init();
}
Display::CSymbolFactory::~CSymbolFactory(void)
{
//	Uninit();
}

//BOOL Display::CSymbolFactory::RegisterExtLib(FARPROC lpfnDLLProc)
//{
//	// 调用初始化函数
//	GETSYMBOLINTERFACE initFunc = (GETSYMBOLINTERFACE)lpfnDLLProc;
//	return initFunc();
//}
//
//BOOL Display::CSymbolFactory::RegisterExtSymbolInterfaceObject(std::string name, Display::IExtSymbolInterFacePtr pExtSymbolInterface )
//{
//	if( g_SymbolFactory.m_mapExtSymbolInterFace.find( name ) != g_SymbolFactory.m_mapExtSymbolInterFace.end() )
//		OTFALSERETURN1(FALSE,"The Same Name Of Ext Symbol Object Is Already Exist!(%s)",(char*)name.c_str() );
//
//	g_SymbolFactory.m_mapExtSymbolInterFace[ name ] = pExtSymbolInterface;
//
//	return TRUE;
//}
//
//Display::ISymbolPtr Display::CSymbolFactory::CreateExtSymbol(std::string name)
//{
//	std::map< std::string , Display::IExtSymbolInterFacePtr >::iterator item;
//	item = g_SymbolFactory.m_mapExtSymbolInterFace.find( name );
//	if( item == g_SymbolFactory.m_mapExtSymbolInterFace.end() )
//		OTFALSERETURN1(NULL, "No Find Ext Symbol:(%s)" , (char*)name.c_str() );
//
//	return item->second->CreateSymbol();
//}
//
//BOOL Display::CSymbolFactory::GetFirstExtSymbolName(std::string &Name, std::string &Desc)
//{
//	if( g_SymbolFactory.m_mapExtSymbolInterFace.size() == 0 )
//		return FALSE;
//
//	curItem = g_SymbolFactory.m_mapExtSymbolInterFace.begin();
//
//	Name = curItem->first;
//	Desc = curItem->second->GetDescription();
//
//	return TRUE;
//}
//
//BOOL Display::CSymbolFactory::GetNextExtSymbolName(std::string &Name, std::string &Desc)
//{
//	curItem++;
//	if ( curItem != g_SymbolFactory.m_mapExtSymbolInterFace.end() )
//	{
//		Name = curItem->first;
//		Desc = curItem->second->GetDescription();
//		return TRUE;
//	}
//	else
//		return FALSE;
//}
//////////////////////////////////////////////////////////////////////////

// 函数名称   : Display::CSymbolFactory::CreateSymbolFromStream
// 描述       : 根据一个数据流创建一个符号对象
// 返回值     : Display::ISymbolPtr 
// 参数       : System::IArchive &ar

Display::ISymbolPtr Display::CSymbolFactory::CreateSymbolFromStream(SYSTEM::IArchive &ar)
{
	ar.SetReadState();

	ISymbolPtr pSym;
	//long lType;
	//ar & lType;
	//ar.GetCurrentPos() -= 4; // 先预读4个字节的类型信息，再回退
	//pSym = CreateSymbol( (SYMBOL_TYPE)lType );
	//if( pSym != NULL )
	//	pSym->serialization( ar );
	unsigned long startIndex = ar.GetCurrentPos();
	long lType;
	ar & lType;
	if (lType & EXT_SYMBOL)
	{
		long lID;
		std::string strLabel;
		try
		{		
			COLORREF lColor;	
			int enumUnit;	
			std::string extSymbolName; 

			ar & lID;
			ar & strLabel;
			ar & lColor;
			ar & enumUnit;
			ar & extSymbolName;
			
			ar.GetCurrentPos() = startIndex; 
			//pSym = CreateExtSymbol(extSymbolName);
		}
		catch (...)
		{
			//FALSERETURN2(NULL , "Error:Symobl Create False!\nSymbol Name : %s , Symbol ID : %d " , strLabel , lID)
		}
	}
	else
	{
		ar.GetCurrentPos() = startIndex; 
		pSym = CreateSymbol( (SYMBOL_TYPE)lType );
	}
	if( pSym != NULL )
		pSym->serialization( ar );

	return pSym;
}


// 函数名称   : Display::CSymbolFactory::CreateSymbol
// 描述       : 通过指定类型，返回一个初始化状态的符号对象
// 返回值     : Display::ISymbolPtr 
// 参数       : SYMBOL_TYPE SymboType

Display::ISymbolPtr Display::CSymbolFactory::CreateSymbol(SYMBOL_TYPE SymboType)
{
	switch(SymboType)
	{
	case SIMPLE_MARKER_SYMBOL:
		{
			return CSimpleMarkerSymbolPtr(new CSimpleMarkerSymbol());
		}
	case CHAR_MARKER_SYMBOL: 
		{
			return CCharMarkerSymbolPtr(new CCharMarkerSymbol());
		}
	case ARROW_MARKER_SYMBOL: 
		{
			//return CArrowMarkerSymbolPtr(new CArrowMarkerSymbol());
		}
	case PIC_MARKER_SYMBOL:   
		{
			//return CPicMarkerSymbolPtr(new CPicMarkerSymbol());
		}
	case COMPLEX_MARKER_SYMBOL:
		{
			//return CComplexMarkerSymbolPtr(new CComplexMarkerSymbol());
		}
	case SIMPLE_LINE_SYMBOL:
		{
			return CSimpleLineSymbolPtr(new CSimpleLineSymbol());
		}
	case ADV_LINE_SYMBOL:	  
		{
			//return IAdvLineSymbolPtr(new CAdvLineSymbol());
		}
	case MARKER_LINE_SYMBOL:	  
		{
			//return IMarkerLineSymbolPtr(new CMarkerLineSymbol());
		}
	case HASH_LINE_SYMBOL:  
		{
			//return IHashLineSymbolPtr(new CHashLineSymbol());
		}
	case COMPLEX_LINE_SYMBOL:
		{
			//return IComplexLineSymbolPtr(new CComplexLineSymbol());
		}
	case SIMPLE_FILL_SYMBOL: 
		{
			return CSimpleFillSymbolPtr(new CSimpleFillSymbol());
		}
	case MARKER_FILL_SYMBOL:	  
		{
			//return IMarkerFillSymbolPtr(new CMarkerFillSymbol());
		}
	case LINE_FILL_SYMBOL:   
		{
			//return ILineFillSymbolPtr(new CLineFillSymbol());
		}
	case PIC_FILL_SYMBOL:   
		{
			//return IPicFillSymbolPtr(new CPicFillSymbol());
		}
	case GRADIENT_FILL_SYMBOL:   
		{
			//return CGradientFillSymbolPtr(new CGradientFillSymbol());
		}
	case COMPLEX_FILL_SYMBOL:
		{
			//return IComplexFillSymbolPtr(new CComplexFillSymbol());
		}
	case TEXT_SYMBOL:
		{
			return CTextSymbolPtr(new CTextSymbol());
		}
	}
	return NULL;
}

Display::CSymbolFactory& Display::CSymbolFactory::GetSymbolFactoryLibMgr()
{
	return g_SymbolFactory;
}

void Display::CSymbolFactory::Uninit()
{
	//m_mapExtSymbolInterFace.clear();
	//SYSTEM::CLibraryMgr::Uninit();
}