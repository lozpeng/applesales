#ifndef IEXTSYMBOL_H
#define IEXTSYMBOL_H
#include "ISymbol.h"
#include "alm.h"
#include "DisplayCache.h"
#include "ICursor.h"
#include "PropRecordIndexGroup.h"
namespace Display{
	/**��չ����
	*/
class DISPLAY_DLL IExtSymbol : public Display::ISymbol
{
public:
	IExtSymbol(void);
	virtual ~IExtSymbol(void);

	IExtSymbol(const IExtSymbol& extSymbol);

	IExtSymbol& operator = (const IExtSymbol& extSymbol);

   /**
    * ��֤����������Ч��
	* @param recordset ��¼��
	* @param &exchangInfo
	* @return ����������Ч�򷵻�True
	*/
	virtual bool ValidatePropValueAndGetInfo(Geodatabase::ICursorPtr pCursor , CPropRecordIndexGroup &exchangInfo) = 0;

   /**
    * ���������������������
	* @param propValueStream ������
	*/
	//virtual b SetPropValue(void *propValueStream) = 0;ȡ��ʹ�ã��ɾ�����չ�������д�������װ�룬��Ϊdraw �������޷�Լ���Ƿ�ʹ�ô˷���

   /**
    * �õ���չ���ŵ�����
	* @return ������չ���ŵ�����
	*/
	virtual const std::string GetDescription();

   /**
    * ��÷�������
	* @return ���ط��ŵ�����
	*/
	virtual const std::string GetSymbolName();

   /**
    * װ�仭��,ͨ��������ʼ������
	* @param pDC ����ͼ�εĻ��� 
	*/
	virtual void SelectDC(Display::CDC *pDC);

   /**
    * �������
	*/
	virtual void ClearDC();

   /**
    * ���л�����
	* @param ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive & ar);

   /**
    * ��������
	* @param PropertyName ��������
	* @param PropertyValue ����ֵ
	*/
	virtual void SetProperties(const char* PropertyName , const _variant_t& PropertyValue);
	/**
	* �����������ƻ������ֵ
	* @param PropertyName ��������
	* @return ��������ֵ
	*/
	virtual _variant_t GetProperties(const char* PropertyName);	

   /**
    * ���ݱ������з�������
	* @param rate ����
	*/
	virtual void Zoom(float rate);
protected:

   /**
    * ʵ���¾ɵ�λ֮���ת��
	* @param oldUnit �µ�λ
	* @param newUnit �ɵ�λ
	*/
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);

   /**
    * ��SelectDC�е��ã��ı���ŵ�λ����floatֵת��Ϊlong��ֵ������������ת����Ļ��������
	*/
	virtual void OnChangingInSelectDC();
protected:
	/** 
	 * ��������
	 */
	std::string m_sDescription;
	/** 
	 * ��������
	 */
	std::string m_sSymbolName;	
};

typedef SYSTEM::CSmartPtr<IExtSymbol> IExtSymbolPtr;
}
#endif