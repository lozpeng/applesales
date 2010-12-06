//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/10/18
// 描述：  符号工厂  负责所有符号的管理
//////////////////////////////////////////////////////////////////////

#ifndef _CSYMBOLFACTORY_H
#define _CSYMBOLFACTORY_H


#include "ISymbol.h"
//#include "IExtSymbolInterFace.h"
namespace Display{

typedef bool (CALLBACK *GETSYMBOLINTERFACE)();

//DISPLAY_DLL SYSTEM::XMLConfigurationPtr GetSymbolRenderConfig();
//
//DISPLAY_DLL void ReleaseSymbolRenderConfig();

/** 
 * 符号工厂 
 */
class DISPLAY_DLL CSymbolFactory //: public SYSTEM::CLibraryMgr
{

public:
	CSymbolFactory(void);
	/**
	 * 引入扩展库文件，并将扩展对象注册到系统中
	 * @param FARPROC lpfnDLLProc
	 * @return 若注册成功返回true，否则为false
	 */
	//virtual BOOL RegisterExtLib(FARPROC lpfnDLLProc);

   /**
    * 根据符号类型创建简单符号
	* @param SymboType 简单符号类型
	* @return 若创建成功则返回符号，否则返回为NULL
	*/
	static ISymbolPtr CreateSymbol(SYMBOL_TYPE SymboType);

	/**
	* 从流文件创建扩展符号
	* @param ar 流文件
	* @return 若创建成功则返回符号，否则返回为NULL
	*/
	static ISymbolPtr CreateSymbolFromStream(SYSTEM::IArchive &ar);
//	ISymbolPtr  CreateSymbolFromIXSerializeString(SYMBOL_TYPE SymboType,string  &strData);
//	void GetOXSerializeStringFromSymbol(ISymbolPtr pSymbol, Char& strData);

   /**
    * 扩展符号模块通过调用该函数注册自己的符号接口对象
	* @param name 扩展符号名
	* @param pExtSymbolInterface 扩展符号接口对象
    * @return 若注册成功返回true，否则为false
	*/
//	static BOOL RegisterExtSymbolInterfaceObject(std::string name, Display::IExtSymbolInterFacePtr pExtSymbolInterface );

   /**
    * 通过名字得到显示扩展符号对象
	* @param name 扩展符号名称
	*/
//	static ISymbolPtr CreateExtSymbol(std::string name);

   /**
    * 枚举第一个符号对象的名字
	* @param Name 第一个扩展符号的名称
	* @param Desc 第一个扩展符号的描述
	* @return 若成功获得返回true，否则为false
	*/
//	static BOOL GetFirstExtSymbolName(std::string &Name, std::string &Desc);

	/**
	 * 获得下一个符号对象的名字
	 * @param Name 下一个扩展符号的名称
	 * @param Desc 下一个扩展符号的描述
	 * @return 若成功获得返回true，否则为false
	 */
//	static BOOL GetNextExtSymbolName(std::string &Name, std::string &Desc);
	/**
	* 获得符号工厂对象
	* @return 返回符号工厂对象
	*/
	static Display::CSymbolFactory& GetSymbolFactoryLibMgr();

	virtual void Uninit();
public:
	~CSymbolFactory(void);
protected:
//	std::map< std::string , Display::IExtSymbolInterFacePtr > m_mapExtSymbolInterFace;
};

}

#endif