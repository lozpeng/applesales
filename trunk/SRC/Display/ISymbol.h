#ifndef _ISymbol_h
#define _ISymbol_h

#include "ISerialization.h"
#include "SmartPtr.h"
#include "SystemUnit.h"

namespace Display
{
	class CDC;
	class DISPLAY_DLL ISymbol: public SYSTEM::ISerialization
	{

	public:
		ISymbol();
		ISymbol(const ISymbol& Symbol);
		virtual ~ISymbol();
	public:
	/**
	* ���ݱ������з�������
	* @param rate ���ű���
	*/
	virtual void Zoom(float rate);

	/**
	* ���ƣ����󷽷���������ʵ��
	* @param pObject 
	*/
	virtual void Draw(void* pObject) = 0;

	/**
	* ��ø��ַ�������
	* @return �������򷵻ط�������
	*/
	virtual SYMBOL_TYPE GetType() = 0;

	/**
	* װ�仭��,ͨ��������ʼ������
	* @param pDC ����
	*/
	virtual void SelectDC(Display::CDC *pDC)=0;

	/**
	* ��selectDC��������Ļ��ƾ��װ�뵱ǰ��������ɻ���ǰ��׼������
	*/
	virtual void SetReadyDraw()=0;

	/**
	* �������
	*/
	virtual void ClearDC();

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
	virtual void DrawLegend( DIS_RECT *rect , int nFlag )=0;

	/**
	* �õ�ID�� 
	* @return ����ID��
	*/
	long GetID();

	/**
	* ����ID��
	* @param lID ���ű�ʶ
	*/
	void SetID(long lID);

	/**
	* �õ����ž��
	* @return ��÷��ž��
	*/
	std::string GetLabel();

	/**
	* ���÷��ž��
	* @param strLabel ���ž��
	*/
	void SetLabel(const char* strLabel);

	/** 
	* ����һ������
	* @return �����Ƴɹ��򷵻�һ������
	*/
	SYSTEM::CSmartPtr<ISymbol> Clone();

	/**
	* �����ɫֵ
	* @return ������ɫֵ
	*/
	COLORREF GetColor();

	/**
	* ������ɫֵ
	* @param color ��ɫֵ
	*/
	void SetColor( COLORREF color );

	/**
	* ��÷��ŵ�λ
	* @return ���ط��ŵ�λ
	*/
	SYSTEM::SYS_UNIT_TYPE GetUnit();

	/**
	* ���÷��ŵ�λ
	* @param SYS_UNIT_TYPE ���ŵ�λ
	*/
	void SetUnit(SYSTEM::SYS_UNIT_TYPE  unitType);

	/**
	* �ⲿ���ã�����һ��ԭʼֵ�����Ŀ�굥λ��Ӧ��ֵ
	* @param valUnit
	* @param aimUnit
	* @param float val
	*/
	float UnitChangeTo(SYSTEM::SYS_UNIT_TYPE valUnit , SYSTEM::SYS_UNIT_TYPE aimUnit , float val);

	/**
	* ��SelectDC�е��ã���floatֵת��Ϊlong��ֵ
	* @param Unit ��λ
	* @param Val
	*/
	long UnitChange( SYSTEM::SYS_UNIT_TYPE Unit , float Val );

	/**
	* ���л�����
	* @param ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar)=0;

	CDC* GetDC(){return m_pDC;};

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

	/**
	* ������غͺ���֮��ı���
	* @return �������غͺ���֮��ı���
	*/
	float GetRateOfPixelAndMM();
	protected:
		Display::CDC*	m_pDC;

		long m_lID;

		std::string m_strLabel;

		COLORREF m_lColor;

		SYSTEM::SYS_UNIT_TYPE m_enumUnit;	

	};
	typedef SYSTEM::CSmartPtr<ISymbol> ISymbolPtr;
}
#endif