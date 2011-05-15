#ifndef IEXTSYMBOLINTERFACE_H
#define IEXTSYMBOLINTERFACE_H
#include "ISymbol.h"
namespace Display{
class DISPLAY_DLL IExtSymbolInterFace// :
	/**扩展符号接口
	 */
//	public SYSTEM::CRef 
{
public:
	IExtSymbolInterFace(void);
	virtual ~IExtSymbolInterFace(void);

   /**
    * 获得扩展符号名称
	* @return 返回符号名称
	*/
	virtual std::string GetSymbolName();

   /**
    * 创建扩展符号
	* @return 若创建成功返回一个扩展符号
	*/
	virtual Display::ISymbolPtr CreateSymbol() = 0;

   /**
    * 获得扩展符号的描述
	* @return 获得扩展符号的描述
	*/
	virtual std::string GetDescription();
};
typedef SYSTEM::CSmartPtr<IExtSymbolInterFace> IExtSymbolInterFacePtr;
}
#endif