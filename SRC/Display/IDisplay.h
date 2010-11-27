#ifndef _IDisplay_h
#define _IDisplay_h
//
#include "DisplayTransformation.h"
#include "CDC.h"
#include "ISymbol.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>


namespace Display
{

	

class ISymbol;

class DISPLAY_DLL IDisplay// : public SYSTEM::CRef 
{
public:
	IDisplay();
	virtual ~IDisplay();

public:

	SYSTEM::CSmartPtr<IDisplay> Clone();

	//�����Ƿ�����ͼdisplay
	void SetLayoutDisplay(BOOL bLayoutDis);

	BOOL GetBeLayoutDisplay();
	/**
	* ���û���
	* @param hDC �������
	* @param lWidth �������
	* @param lHeight �����߶�
	*/
	virtual	void SetDC(long hDC, long lWidth, long lHeight );

	/**
	* ���÷���
	* @param pSymbol ����ָ�룬ָ�����
	* @return �����óɹ��򷵻�True
	*/
	virtual BOOL SetSymbol(ISymbol* pSymbol);

	/**
	* ����
	* @param pGeometry ������
	*/
	virtual void Draw(const GEOMETRY::geom::Geometry* pGeometry);
	/**
	* ����
	* @param pEnvelope ����
	*/
	virtual void Draw(const GEOMETRY::geom::Envelope* pEnvelope);
	/**
	* ��������
	* @param pEnvelope ���ֵ�λ��
	* @param strText ����
	*/
	virtual DIS_RECT Draw(const GEOMETRY::geom::Envelope* pEnvelope,  const std::string strText, BOOL bScaleWithMap , unsigned int dwDTFormat= DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);
	DIS_RECT Draw(const DIS_RECT* rect,  const std::string strText, BOOL bScaleWithMap, unsigned int dwDTFormat);

	void Draw(void* pObject);
	/**
	* ��ʼ����
	* @return 
	*/
	virtual BOOL Begin();

	/**
	* �ڿ�ʼ����ǰ���Ȼ���һЩ����
	* @param hDC �������
	*/
	virtual void OnBeginDraw( long hDC );

	/**
	* �������� 
	*/
	virtual void End();

	/**
	* �ڽ�������֮ǰ���Ȼ���һЩ����
	* @param hDC �������
	*/
	virtual void OnEndDraw( long hDC );

	/**
	* ������������õ�ջ��
	* @param ISymbolPtr pSymbol
	*/
	int SetSymbolInStack(ISymbol* pSymbol);

	/**
	* �ڻ����У�Begin-End���л�ջ�з���
	* @param index ��������
	*/
	virtual BOOL SelectStackSymbol(int index);

	/**
	* �����ʾת��
	* @return ����óɹ��򷵻���ʾת��
	*/
	CDisplayTransformation& GetDisplayTransformation();

	/**
	* ����ͼ��
	* @param pSymbol ����
	* @param rect ��������
	* @param nFlag �ж���ʾ��ʽ��ֱ�߻����ߣ�
	*/
	void DrawLegend(ISymbol* pSymbol, DIS_RECT * rect, int nFlag = 0);

	/**
	* ����ͼ��
	* @param pSymbol ����
	* @param lPosx ����������ʼλ��x
	* @param lPosy ����������ʼλ��y
	* @param lWidth ����������
	* @param lHeight ��������߶�
	* @param nFlag �ж���ʾ��ʽ��ֱ�߻����ߣ�
	*/
	void DrawLegend(ISymbol* pSymbol,long lPosx,long lPosy,long lWidth,long lHeight, int nFlag = 0);

	/**
	* ƫ����Ļ����
	* @param offset_x ƫ��λ��X
	* @param offset_y ƫ��λ��Y
	*/
	void OffsetScreen(long offset_x,long offset_y);

	/**
	* ���ñ���ɫ
	* @param color ��ɫֵ
	*/
	void SetBgColor( COLORREF color);

	/**
	* �����ɫֵ
	* @return ������ɫֵ
	*/
	COLORREF GetBgColor();

	/**
	* ���Ʊ���
	*/
	void DrawBackgroud();

	/**
	* ��û���DC
	* @return ����óɹ�����CDC
	*/
	CDC* GetDrawDC();

	//���û��ƻ�����
	void SetDrawBuffer(DRAW_CONTENT content);

	//ˢ����ʾ�ڴ�
	void RefreshDisplay(long content);

	//����������ʾ�����С
	void CacheBuffer(long lWidth, long lHeight);

	//�����Ƿ����ڴ�ӡ
	void SetPrinting(BOOL bPrint);

	BOOL GetPrinting(){return m_bPrint;};

	//ˢ�µ���Ҫ����ͼ
	void UpdateGeography();

	boost::signals::connection RegisterUpdateGeography(boost::function<void ()> fun);

protected:
	
	//
	bool bDraw;
	COLORREF m_BgColor;

	//
	CDisplayTransformation m_cDisplayTransformation;
	Display::CDC* m_pDC;	

	//
	ISymbol* m_pSymbol;
	std::vector<ISymbol*> m_stackpSymbol;

	BOOL m_bLayoutDis;

	BOOL m_bPrint;

	
	
};

typedef SYSTEM::CSmartPtr<IDisplay> IDisplayPtr;

}

#endif