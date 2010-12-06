//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2008/11/18
  // ������  ����Žӿ���
//////////////////////////////////////////////////////////////////////

#ifndef IMARKER_SYMBOL_H
#define IMARKER_SYMBOL_H

#include "ISymbol.h"
#include "IArchive.h"

namespace Display{
class  CSymbolMask;
class  CComplexMarkerSymbol;

/** @interface */
/** 
 * ����Žӿ�
 */
class DISPLAY_DLL IMarkerSymbol: virtual public ISymbol
{

friend class CSymbolMask;
friend class CComplexMarkerSymbol;

public:

	IMarkerSymbol();

	virtual ~IMarkerSymbol();

	IMarkerSymbol(const IMarkerSymbol& MarkSymbol);

	IMarkerSymbol& operator = (const IMarkerSymbol& MarkSymbol);

	/**
	* ��������
	* @param PropertyName ��������
	* @param PropertyValue ����ֵ
	*/
	virtual void SetProperties(const char* PropertyName , const _variant_t& PropertyValue);
	
	/**
	* �������ֵ
	* @param PropertyName ��������
	*/
	virtual _variant_t GetProperties(const char* PropertyName);			

	/**
	* ����ͼ��
	* @param rect ��������
	* @param nFlag �жϱ�ʶ
	*/
	virtual void DrawLegend(DIS_RECT *rect,int nFlag);

	/**
	* ���ݱ������з�������
	* @param rate ���ű���
	*/
	virtual void Zoom(float rate);				

	/**
	* ��ø��ַ�������
	* @return �������򷵻ط�������
	*/
	SYMBOL_TYPE GetType();						

   /**
    * ���õ���ŵ�ƫ����
	* @param x xƫ����
	* @param y yƫ����
	*/
	virtual void SetOffSet(float x , float y);				

   /**
    *�õ�����ŵ�xƫ����
	* @return ���ص���ŵ�xƫ����
	*/
	virtual float GetOffsetX();							

   /**
    * �õ�����ŵ�yƫ����
	* @return ���ص���ŵ�xƫ����
	*/
	virtual float GetOffsetY();			

   /**
    * ���õ���ŵĻ���
	* @param fAngle ����ŵĻ���
	*/
	virtual void SetAngle(float fAngle);				

   /**
    * �õ�����ŵĻ���
	* @return ���ص���ŵĻ���
	*/
	virtual float GetAngle();							

   /**
    * ���÷��ŵĳߴ�
	* @param marksize ���ŵĳߴ�
	*/
	virtual void SetMarkerSize(float marksize);	

   /**
    * �õ����ŵĳߴ�
	* @return ���ط��ŵĳߴ�
	*/
	virtual float GetMarkerSize();				

   /**
    * �����Ƿ������Χ����
	* @param bMask �ж��Ƿ������Χ����
	*/
	virtual void SetMaskDrawable(bool bMask);			

   /**
    * �õ��Ƿ������Χ����������
	* @return ������true���������Χ���������ã�����Ϊfalse
	*/
	virtual bool GetMaskDrawable();						

   /**
    * װ����Χ����ָ��
	* @param pSymbolMask ��Χ����ָ��
	*/
	virtual void SetMask(ISymbolPtr pSymbolMask);		

   /**
    * �õ���Χ����ָ��
	* @return �����ڣ��򷵻���Χ����ָ�룬���򷵻�ΪNULL
	*/
	virtual ISymbolPtr GetMask();						

   /**
    * ���õ������ɫ
	* @param lColor �������ɫ
	*/
	virtual void SetMarkerColor(unsigned long lColor);	

   /**
    * �õ��������ɫ
	* @return ���ص���ŵ���ɫֵ 
	*/
	virtual unsigned long GetMarkColor();				

   /**
    * ����
	* @param pObject ���Ŷ���
	*/
	virtual void Draw(void* pObject);

   /**
    * ���л�����
	* @param ar �����ļ���
	*/
	virtual void serialization(SYSTEM::IArchive & ar);
	
	/**
	* ���DC
	*/
	virtual void ClearDC();

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
	
	long m_lOffsetX;							/**< ���ŵ�ƫ������Ĭ��Ϊ0*/

	long m_lOffsetY;

	float m_fAngle;								/**< ���ŵĽǶȣ�Ĭ��Ϊ0,��λ�Ƕ���*/

	unsigned long m_lMarkerSize;					/**< ���Ŵ�С��Ĭ��ֵ����СֵΪ1*/

	bool m_bMask;								/**< �ж��Ƿ������Χ������Ĭ��false*/

	ISymbolPtr m_pSymbolMask;					/**< ��Χ�����Ķ���ָ��*/

	float m_fMarkerSize;							/**< �ڲ�������ųߴ�,��Ҫ���л�*/
	float m_fOffsetX;
	float m_fOffsetY;
};

typedef SYSTEM::CSmartPtr<IMarkerSymbol> IMarkerSymbolPtr;
}
#endif //IMarkerSymbol_H
