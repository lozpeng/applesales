//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/18
// ������  ���ݲ����Ⱦ���壬�����������ݲ㣨դ��ʸ���Ȳ㣩����������
//////////////////////////////////////////////////////////////////////


#ifndef _TEXTSYMBOL_H
#define _TEXTSYMBOL_H
#include "ISymbol.h"
#include "CDC.h"
//#include "DisplayCache.h"

namespace Display{
	class DISPLAY_DLL CTextSymbol : public ISymbol 
	{
	public:

		CTextSymbol();

		virtual ~CTextSymbol();

		CTextSymbol(const CTextSymbol& toTextSymbol);

		CTextSymbol& operator = (const CTextSymbol& toTextSymbol);

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
		// ��������   : SelectDC(CDC *pDC)
		// ����       : ���ñʣ�ˢ�������
		// ��������   : virtual void 
		// ����       : CDC *pDC   ���ƾ�� 
		virtual void SelectDC(Display::CDC * pDC);

		// ��������   : SetReadyDraw()
		// ����       : ��selectDC��������Ļ��ƾ��װ�뵱ǰ��������ɻ���ǰ��׼������
		// ��������   : virtual void 
		virtual void SetReadyDraw();


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
		* �������ַ��ŵ���б��
		* @param fAngle ���ֵ���б��
		*/
		virtual void SetAngle(float fAngle);				

		/**
		* �õ����ַ��ŵ���б��
		* @return �������ַ��ŵ���б��
		*/
		virtual float GetAngle();							

		/**
		* ���÷��ŵĳߴ�
		* @param textsize ���ŵĳߴ�
		*/
		virtual void SetTextSize(float textsize);	

		/**
		* �õ����ŵĳߴ�
		* @return ���ط��ŵĳߴ�
		*/
		virtual float GetTextSize();				

		/**
		* �������ַ�����ɫ
		* @param lColor ���ַ�����ɫ
		*/
		virtual void SetTextColor(unsigned long lColor);	

		/**
		* �õ����ַ�����ɫ
		* @return �������ַ��ŵ���ɫֵ 
		*/
		virtual unsigned long GetTextColor();		

		/**
		* �������ַ�����ɫ
		* @param font ���ַ�����ɫ
		*/
		virtual void SetTextFont(DIS_FONT font);	

		/**
		* �õ����ַ�����ɫ
		* @return �������ַ��ŵ���ɫֵ 
		*/
		virtual DIS_FONT GetTextFont();	

		/**
		* �������ֻ��Ƹ�ʽ��Ϣ
		* @return 
		*/
		void SetDrawFormat(unsigned int dwDTFormat);

		/**
		* ���������Ķ�˳��
		* @param bRightToLeft �����Ķ�˳��
		*/
		virtual void SetReadDirection(BOOL bRightToLeft);	

		/**
		* �õ������Ķ�˳��
		* @return ���������Ķ�˳�� 
		*/
		virtual BOOL GetReadDirection();

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

		/**
		* ����ͼ��
		* @param rect ��������
		* @param nFlag �жϱ�ʶ
		*/
		virtual void DrawLegend( DIS_RECT *rect , int nFlag );

		void SetTextPosType(TEXT_POS_TYPE eType);

		TEXT_POS_TYPE GetTextPosType();


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


		virtual void SetFont();



	protected:////������̳����ԣ�����ֱ��ʹ��

		//////////////////////////////////////////////////////////////////////////
		//DISPLAY_HANDLE_NODE* m_hFontHandle;								//�洢���建��
		//////////////////////////////////////////////////////////////////////////

		long m_lOffsetX;							/**< ���ŵ�ƫ������Ĭ��Ϊ0*/

		long m_lOffsetY;

		float m_fAngle;								/**< ���ŵĽǶȣ�Ĭ��Ϊ0,��λ�Ƕ���*/

		float m_fTextHeight;					/**< ���Ŵ�С��Ĭ��ֵ����СֵΪ1*/

		unsigned int m_dwDTFormat;					/**<������Ϣ,Ĭ��ֵΪDT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP*/

		DIS_FONT m_font;							/**< ������Ϣ*/

		BOOL m_bRightToLeft;						/**< ��־�Ķ�˳���Ƿ��������Ĭ��ΪFALSE*/

		bool m_bMask;								/**< �ж��Ƿ������Χ������Ĭ��false*/

		TEXT_POS_TYPE m_enumTextPosType;

		ISymbolPtr m_pSymbolMask;					/**< ��Χ�����Ķ���ָ��*/

		float m_fTextSize;							/**< �ڲ�������ųߴ�,��Ҫ���л�*/
		float m_fOffsetX;
		float m_fOffsetY;
	
	};
	typedef SYSTEM::CSmartPtr<CTextSymbol> CTextSymbolPtr;
}
#endif

