//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2008/11/18
  // ������  �߷��Žӿ���
//////////////////////////////////////////////////////////////////////

#ifndef ILINESYMBOL_H
#define ILINESYMBOL_H

#include "ISymbol.h"

namespace Display{

/** @interface */
/** 
 *�߷��Žӿ�
 */
class DISPLAY_DLL ILineSymbol : virtual public ISymbol 
{
public:
	ILineSymbol();

	virtual ~ILineSymbol();

	ILineSymbol(const ILineSymbol& toLineSymbol);

	ILineSymbol& operator = (const ILineSymbol& toLineSymbol);

	/**
	* ��������
	* @param PropertyName ��������
	* @param PropertyValue ����ֵ
	*/
	virtual void SetProperties( const char* PropertyName , const _variant_t& PropertyValue);

	/**
	* �������ֵ
	* @param PropertyName ��������
	*/
	virtual _variant_t GetProperties(const char* PropertyName);			
 
	/**
	* ��ø��ַ�������
	* @return �������򷵻ط�������
	*/
	virtual SYMBOL_TYPE GetType();									

	/**
	* ���ݱ������з�������
	* @param rate ���ű���
	*/
	virtual void Zoom(float rate);									

   /**
    * �����߿�
	* @param nWidth �߿�
	* @return 
	*/
	virtual void SetLineWidth(float nWidth);				

   /**
    * �õ��߿�
	* @return �����߿� 
	*/
	virtual float GetLineWidth();							

   /**
    * �����߷�����ɫ
	* @param lColor �߷��ŵ���ɫֵ
	*/
	virtual void SetLineColor(unsigned long lColor);				

   /**
    * �õ��߷�����ɫ
	* @return �����߷�����ɫֵ
	*/
	virtual unsigned long GetLineColor();							

   /**
    * �����߷��ŵ�ƫ����
	* @param float x
	* @param float y
	* @return 
	*/
	virtual void SetOffset(float x , float y);							

   /**
    * �õ��߷��ŵ�xƫ����
	* @return �����߷��ŵ�xƫ���� 
	*/
	virtual float GetOffsetX();										

   /**
    * �õ��߷��ŵ�yƫ����
	* @return �����߷��ŵ�yƫ����
	*/
	virtual float GetOffsetY();										

	/**
	* ����ͼ��
	* @param rect ��������
	* @param nFlag �жϱ�ʶ
	*/
	virtual void DrawLegend( DIS_RECT * rect,int nFlag );				

   /**
    * ����
	* @param pObject ���Ŷ���
	* @return 
	*/
	virtual void Draw(void* pObject);

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
protected:////������̳����ԣ�����ֱ��ʹ��

	unsigned long  m_lLineWidth;									/**< �߿�*/

	long m_lOffsetX;

	long m_lOffsetY;
	
	float m_fLineWidth;
	float m_fOffsetX;
	float m_fOffsetY;
public:

   /**
    * ���л�����
	* @param ar �����ļ���
	*/
	virtual void serialization(SYSTEM::IArchive & ar);
};

typedef SYSTEM::CSmartPtr<ILineSymbol> ILineSymbolPtr;

}

#endif //ILINESYMBOL_H
