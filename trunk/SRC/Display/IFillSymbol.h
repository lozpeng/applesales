//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2008/11/19
  // ������  ����Žӿ���
//////////////////////////////////////////////////////////////////////

#ifndef IFILLSYMBOL_H
#define IFILLSYMBOL_H
#include "ISymbol.h"
#include "ILineSymbol.h"


namespace Display{

/** @interface */
/** 
*����Žӿ�
*/
class DISPLAY_DLL IFillSymbol : virtual public ISymbol 
{
public:
	IFillSymbol();

	virtual ~IFillSymbol();

	IFillSymbol(const IFillSymbol& FillSymbol);

	IFillSymbol& operator = (const IFillSymbol& FillSymbol);

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
    * ���ñ߽��ߵ���ɫ
	* @param lColor �߽�����ɫֵ
	*/
	virtual void SetOutLineColor(unsigned long lColor);									//�����ߵ���ɫ

   /**
    * ��ñ߽��ߵ���ɫ
	* @return ���ر߽�����ɫֵ
	*/
	virtual unsigned long GetOutLineColor();											//�õ��ߵ���ɫ

   /**
    * ���������ɫ
	* @param lColor ��ɫֵ
	*/
	virtual void SetFillColor(unsigned long lColor);									//���������ɫ

   /**
    * �õ������ɫ
	* @return �������ɫ
	*/
	virtual unsigned long GetFillColor();												//�õ������ɫ
	
	/**
	* �����Ƿ���������
	* @param bFill �ж��Ƿ���������
	*/
	virtual void SetDrawFill(bool bFill);												

	/**
	* �õ��Ƿ���������
	* @return ������������򷵻�true�����򷵻�false
	*/
	virtual bool GetDrawFill();	
   /**
    * ���ñ߽��ߵĿ��
	* @param size �߽��ߵĿ��
	*/
	virtual void SetOutLineWidth(float size);											//�����ߵĿ��

   /**
    * �õ��ߵĿ��
	* @return �����ߵĿ��
	*/
	virtual float  GetOutLineWidth();													//�õ��ߵĿ��

   /**
    * ���ñ߽���ָ��
	* @param mOutLine �߽��߷���ָ��
	*/
	virtual void SetOutLineSymbol(ILineSymbolPtr mOutLine);								    //������ָ��

   /**
    * ��ñ߽��ߵ�ָ��
	* @return ���ر߽��߷���ָ��
	*/
	ILineSymbolPtr GetOutLineSymbol();

   /**
    * �����Ƿ���Ʊ߽���
	* @param bline �ж��Ƿ���Ʊ߽���
	*/
	virtual void SetDrawOutLine(bool bline);												

   /**
    * �õ��Ƿ������
	* @return ���������򷵻�true�����򷵻�false
	*/
	virtual bool GetDrawOutLine();	

	
	
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
	* ����ͼ��
	* @param rect ��������
	* @param nFlag �жϱ�ʶ
	*/
	virtual void DrawLegend( DIS_RECT * rect , int nFlag );						

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
protected:

	bool m_bOutLine;															/**< �Ƿ���Ʊ߽���*/

	unsigned long m_lRgnID;														/**< Rgn ID ������*/

	ILineSymbolPtr m_OutLineSymbol;													/**< �߶���ָ��*/

protected:

	void DrawOutLine(DIS_POLYGON *pDIS_POLYGON);									    /**< ����*/

	void DrawOutLine(DIS_RECT *pDIS_RECT);

	void DrawOutLine(DIS_CIRCLE *pCircle);

	void DrawOutLine(DIS_ELLIPSE *pEllipse);

	void DrawOutLine(DIS_ARCPOLYGON *pPolygon);

	int GetSquare(DIS_RECT * rc );													/**< �õ����������*/
public:

	/**
	* ���л�����
	* @param ar �����ļ���
	*/
    virtual void serialization(SYSTEM::IArchive & ar);
};

typedef SYSTEM::CSmartPtr<IFillSymbol> IFillSymbolPtr;
}
#endif //IFILLSYMBOL_H
