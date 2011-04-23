
#ifndef _RANGE_RENDER_H_
#define _RANGE_RENDER_H_

#include <vector>
#include <utility>
#include "ISymbol.h"

namespace Carto
{
/****************************************************************************
* 范围渲染专题
*****************************************************************************/

class CARTO_DLL CRangeRender : public Carto::IRender 
{
	//对于一个分段类的描述
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
	* 设置分类的字段
	* @param strField 字段名称
	*/
	void SetClassField(std::string strField);


	/**
	* 得到某个分段的上限值
	* @param index 序号
	*/
	double GetBreakValue(long index);

	/**
	* 设置某个分段的上限值
	* @param index 序号
	* @param value 设置的值
	*/
	void SetBreakValue(long index,double value);

	/**
	* 得到最小的属性值，也就是第一个分段的下限
	*/
	double GetminBreakValue();

	/**
	* 设置最小的属性值，也就是第一个分段的下限
	* @param value 设置的值
	*/
	void SetminBreakValue(double value);

	/**
	* 得到某个值所使用的符号
	* @param Value 属性值
	*/
	Display::ISymbolPtr GetSymbolByValue(double Value );

	/**
	* 得到某个分段使用的符号
	* @param index 序号
	*/
	Display::ISymbolPtr GetSymbol(long index);

	/**
	* 设置某个分段的符号
	* @param index 序号
	* @param value 设置的值
	*/
	void SetSymbol(long index,Display::ISymbolPtr pSymbol);

	/**
	* 得到分类的数目
	*/
	long GetCount();

	/**
	* 设置分类的数目
	*/
	void SetClassCount(long num);

	/**
	* 设置某个类别的标注
	* @param index 类别的序号，从0开始
	* @param strLabel 标注
	*/
	void SetLabel(long index,std::string strLabel);

	/**
	* 得到某个类别的标注
	* @param index 类别的序号，从0开始
	* @return std::string 标注
	*/
	std::string GetLabel(long index);

	/**
	* 设置图例的头文字
	* @param strLable 标注
	*/
	void SetHeading(std::string strHeading);

	/**
	* 得到图例的头文字
	* @return std::string 标注
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
	std::string m_DefaultLabel; //默认符号的标注

	double m_dminValue; //最小值

	std::vector<BreakClass> m_Classes; 
	
	Display::ISymbolPtr m_pDefaultSymbol;



	
};

typedef SYSTEM::CSmartPtr<CRangeRender> IRangeRenderPtr;

}
#endif 
