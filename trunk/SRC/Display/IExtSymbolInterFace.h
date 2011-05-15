#ifndef IEXTSYMBOLINTERFACE_H
#define IEXTSYMBOLINTERFACE_H
#include "ISymbol.h"
namespace Display{
class DISPLAY_DLL IExtSymbolInterFace// :
	/**��չ���Žӿ�
	 */
//	public SYSTEM::CRef 
{
public:
	IExtSymbolInterFace(void);
	virtual ~IExtSymbolInterFace(void);

   /**
    * �����չ��������
	* @return ���ط�������
	*/
	virtual std::string GetSymbolName();

   /**
    * ������չ����
	* @return �������ɹ�����һ����չ����
	*/
	virtual Display::ISymbolPtr CreateSymbol() = 0;

   /**
    * �����չ���ŵ�����
	* @return �����չ���ŵ�����
	*/
	virtual std::string GetDescription();
};
typedef SYSTEM::CSmartPtr<IExtSymbolInterFace> IExtSymbolInterFacePtr;
}
#endif