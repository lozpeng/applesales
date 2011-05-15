/************************************************************************/
/*���ߣ���ά
���������Ϸ��Žӿ�
�汾�ţ�1.0
�������ڣ�2007-6-14 ����06:16:45                                                                      */
/************************************************************************/

#pragma once

#include "IArchive.h"
#include "alm.h"
#include "ISerialization.h"
#include "SymbolArray.h"
#include "ISymbol.h"
namespace Display{
	class DISPLAY_DLL IComplexSymbol : virtual public ISymbol/*public SYSTEM::CRef , public SYSTEM::ISerialization */
{
public:
	IComplexSymbol(void);

	~IComplexSymbol(void);

	IComplexSymbol(const IComplexSymbol& ComplexSymbol);

	IComplexSymbol& operator = (const IComplexSymbol& ComplexSymbol);	

   /**
    * ��ӷ��ż���
	* @param Symbol ����ָ��
	* @return ����ӳɹ��򷵻�true������Ϊfalse
	*/
	virtual bool Add(ISymbolPtr Symbol) = 0;							

   /**
    * ���÷����Ƿ�ɼ�
	* @param index ��������
	* @param visible �Ƿ�ɼ�
	*/
	virtual void SetSymbolVisible( int index , bool visible );			

   /**
    * �ж��Ƿ�ɼ�
	* @param index ��������
	* @return 
	*/
	virtual bool IsVisible(int index);									

   /**
    * ɾ������ķ���,����������
	* @param index ���ŵ�����
	*/
	virtual void RemoveSymbol(int index);								

   /**
    * ���������������Ƿ����
	* @param index ������
	* @param bool bLock = false ����	�Ƿ������Ĭ��falseΪ������
	* @return 
	*/
	virtual void LockSymbol( int index , bool bLock = false);			

   /**
    * ���������õ�����ָ��
	* @param index ������
	* @return �����ڣ��򷵻�
	*/
	virtual ISymbolPtr GetAt(int index);								

   /**
    * ���������ŵõ������Ƿ������
	* @param index ������
	* @return �������򷵻�Ϊtrue������Ϊfalse
	*/
	virtual bool IsLocked(int index);										

   /**
    * �õ�����ķ��Ÿ���
	* @return ���ؼ�����ŵĸ��� 
	*/
	virtual int GetSize();													

   /**
    * �ӵ�indexλ�ÿ�ʼ����һ������
	* @param index ������
	* @param symbol ����
	* @param bVisible �����Ƿ�ɼ�
	* @return 
	*/
	virtual bool Insert( int index , ISymbolPtr symbol , bool bVisible ) = 0; 

   /**
    * ��������˳��
	* @param posX X����
	* @param posY Y����
	* @return 
	*/
	virtual bool ExchangeOrder( int posX , int posY );					

   /**
    * �޸������Ŷ�Ӧ�ķ���
	* @param index ������
	* @param symbol ����ָ�룬ָ�����
	* @return �����óɹ��򷵻�true������Ϊfalse
	*/
	virtual bool SetSymbol( int index , ISymbolPtr symbol ) = 0;

	/**
	* ����ͼ��
	* @param rect ��������
	* @param nFlag �жϱ�ʶ
	*/
	virtual void DrawLegend( DIS_RECT * rect , int nFlag );

	/**
	* ���DC
	*/
	virtual void ClearDC();


	void SetReadyDraw(){};

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

public:

	virtual void serialization(SYSTEM::IArchive &ar);
protected:

	ISymbolArrayPtr  m_arrayGroup;					//��ʼһ��CArray����,���ڴ�����ŵ�ָ��
	SYSTEM::CArray<bool>	m_arrayLock;						//��ʼһ����������Ƿ������ɫ����
	SYSTEM::CArray<bool>	m_arrayView;						//��ʼ�����ſɼ����ɼ�
};
typedef SYSTEM::CSmartPtr<IComplexSymbol> IComplexSymbolPtr;
}