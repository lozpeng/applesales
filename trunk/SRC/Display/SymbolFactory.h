//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/10/18
// ������  ���Ź���  �������з��ŵĹ���
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
 * ���Ź��� 
 */
class DISPLAY_DLL CSymbolFactory //: public SYSTEM::CLibraryMgr
{

public:
	CSymbolFactory(void);
	/**
	 * ������չ���ļ���������չ����ע�ᵽϵͳ��
	 * @param FARPROC lpfnDLLProc
	 * @return ��ע��ɹ�����true������Ϊfalse
	 */
	//virtual BOOL RegisterExtLib(FARPROC lpfnDLLProc);

   /**
    * ���ݷ������ʹ����򵥷���
	* @param SymboType �򵥷�������
	* @return �������ɹ��򷵻ط��ţ����򷵻�ΪNULL
	*/
	static ISymbolPtr CreateSymbol(SYMBOL_TYPE SymboType);

	/**
	* �����ļ�������չ����
	* @param ar ���ļ�
	* @return �������ɹ��򷵻ط��ţ����򷵻�ΪNULL
	*/
	static ISymbolPtr CreateSymbolFromStream(SYSTEM::IArchive &ar);
//	ISymbolPtr  CreateSymbolFromIXSerializeString(SYMBOL_TYPE SymboType,string  &strData);
//	void GetOXSerializeStringFromSymbol(ISymbolPtr pSymbol, Char& strData);

   /**
    * ��չ����ģ��ͨ�����øú���ע���Լ��ķ��Žӿڶ���
	* @param name ��չ������
	* @param pExtSymbolInterface ��չ���Žӿڶ���
    * @return ��ע��ɹ�����true������Ϊfalse
	*/
//	static BOOL RegisterExtSymbolInterfaceObject(std::string name, Display::IExtSymbolInterFacePtr pExtSymbolInterface );

   /**
    * ͨ�����ֵõ���ʾ��չ���Ŷ���
	* @param name ��չ��������
	*/
//	static ISymbolPtr CreateExtSymbol(std::string name);

   /**
    * ö�ٵ�һ�����Ŷ��������
	* @param Name ��һ����չ���ŵ�����
	* @param Desc ��һ����չ���ŵ�����
	* @return ���ɹ���÷���true������Ϊfalse
	*/
//	static BOOL GetFirstExtSymbolName(std::string &Name, std::string &Desc);

	/**
	 * �����һ�����Ŷ��������
	 * @param Name ��һ����չ���ŵ�����
	 * @param Desc ��һ����չ���ŵ�����
	 * @return ���ɹ���÷���true������Ϊfalse
	 */
//	static BOOL GetNextExtSymbolName(std::string &Name, std::string &Desc);
	/**
	* ��÷��Ź�������
	* @return ���ط��Ź�������
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