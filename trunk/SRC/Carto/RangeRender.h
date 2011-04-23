
#ifndef _RANGE_RENDER_H_
#define _RANGE_RENDER_H_

#include <vector>
#include <utility>
#include "ISymbol.h"

namespace Carto
{
/****************************************************************************
* ��Χ��Ⱦר��
*****************************************************************************/

class CARTO_DLL CRangeRender : public Carto::IRender 
{
	//����һ���ֶ��������
	struct BreakClass
	{
		BreakClass():dvalue(0.0)
		{

		}
		Display::ISymbolPtr pSymbol;
		double  dvalue;
		std::string strLable;
	};

public:

	CRangeRender();

	~CRangeRender();

public:
	virtual void Draw( Display::IDisplayPtr pDisplay,  Geodatabase::ICursorPtr pCursor );

    virtual void HighLightDraw(Display::IDisplayPtr pDisplay,  Geodatabase::ISelctionSet* pSelections);

	virtual std::string GetRendFieldsStr();

	/**
	* ���÷�����ֶ�
	* @param strField �ֶ�����
	*/
	void SetClassField(std::string strField);


	/**
	* �õ�ĳ���ֶε�����ֵ
	* @param index ���
	*/
	double GetBreakValue(long index);

	/**
	* ����ĳ���ֶε�����ֵ
	* @param index ���
	* @param value ���õ�ֵ
	*/
	void SetBreakValue(long index,double value);

	/**
	* �õ���С������ֵ��Ҳ���ǵ�һ���ֶε�����
	*/
	double GetminBreakValue();

	/**
	* ������С������ֵ��Ҳ���ǵ�һ���ֶε�����
	* @param value ���õ�ֵ
	*/
	void SetminBreakValue(double value);

	/**
	* �õ�ĳ��ֵ��ʹ�õķ���
	* @param Value ����ֵ
	*/
	Display::ISymbolPtr GetSymbolByValue(double Value );

	/**
	* �õ�ĳ���ֶ�ʹ�õķ���
	* @param index ���
	*/
	Display::ISymbolPtr GetSymbol(long index);

	/**
	* ����ĳ���ֶεķ���
	* @param index ���
	* @param value ���õ�ֵ
	*/
	void SetSymbol(long index,Display::ISymbolPtr pSymbol);

	/**
	* �õ��������Ŀ
	*/
	long GetCount();

	/**
	* ���÷������Ŀ
	*/
	void SetClassCount(long num);

	/**
	* ����ĳ�����ı�ע
	* @param index ������ţ���0��ʼ
	* @param strLabel ��ע
	*/
	void SetLabel(long index,std::string strLabel);

	/**
	* �õ�ĳ�����ı�ע
	* @param index ������ţ���0��ʼ
	* @return std::string ��ע
	*/
	std::string GetLabel(long index);

	/**
	* ����ͼ����ͷ����
	* @param strLable ��ע
	*/
	void SetHeading(std::string strHeading);

	/**
	* �õ�ͼ����ͷ����
	* @return std::string ��ע
	*/
	std::string GetHeading();

    void clear(void);

	virtual void serialization(SYSTEM::IArchive &ar);

	virtual CLegendInfoPtr GetLegendInfo();

private:

	long GetIndex(double Value);

protected:
	std::string m_RendFieldsStr;
	std::string m_strHeading;
	std::string m_DefaultLabel; //Ĭ�Ϸ��ŵı�ע

	double m_dminValue; //��Сֵ

	std::vector<BreakClass> m_Classes; 
	
	Display::ISymbolPtr m_pDefaultSymbol;



	
};

typedef SYSTEM::CSmartPtr<CRangeRender> IRangeRenderPtr;

}
#endif 
