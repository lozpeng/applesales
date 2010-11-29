#ifndef  _LEGEND_INFO_H_
#define  _LEGEND_INFO_H_

#include "ISymbol.h"
#include <vector>

namespace Carto
{

struct LegendItem
{
	Display::ISymbolPtr pSymbol; //ͼ������ķ���
	std::string strLabel; //ͼ������ı�ע
	std::string strDes;  //ͼ���������������ѡ��������Label�ĺ���
};

/******************************************************************************
*  CLegendGroup��ʾһ��ͼ������ļ��ϣ������˶��LegendItem
*
*******************************************************************************/
class CARTO_DLL CLegendGroup
{
public:
	/**
	* ���ͼ���������Ŀ
	*/
	long GetItemCount();

	/**
	* ���ָ��λ�õ�ͼ������
	* @param index ���,��0��ʼ
	*/
    LegendItem GetItem(long index);

	/**
	* ���һ��ͼ������
	* @param item ͼ������
	*/
	void AddItem(const LegendItem &item);

	/**
	* ���ͷ����
	*/
	std::string GetHeading();

	/**
	* ����ͷ����
	*/
	void SetHeading(std::string strHeading);

	/**
	* ɾ�����е�ͼ������
	*/
	void Clear();

protected:
	std::vector<LegendItem> m_Items;
	std::string m_strHeading;
};

typedef SYSTEM::CSmartPtr<CLegendGroup> CLegendGroupPtr;

/******************************************************************************
* CLegendInfo������ͼ������Ϣ
*
*******************************************************************************/

class CARTO_DLL CLegendInfo
{
public:
	CLegendInfo();
	virtual ~CLegendInfo();
public:
    
	/**
	* ���ͼ�������Ŀ
	*/
	long LegendGroupCount();

	/**
	* ���ָ��λ�õ�ͼ����
	* @param index ���,��0��ʼ
	*/
	CLegendGroupPtr GetLegendGroup(long index);

	/**
	* ���һ��ͼ����
	*/
	void AddGroup( CLegendGroupPtr pLegendGroup);

public:
	std::vector<CLegendGroupPtr> m_Groups;

};

typedef SYSTEM::CSmartPtr<CLegendInfo> CLegendInfoPtr;



}




#endif