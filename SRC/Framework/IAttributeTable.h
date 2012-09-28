#ifndef _IATTRIBUTE_TABLE_H_
#define _IATTRIBUTE_TABLE_H_


#include "IUIObject.h"
#include "ILayer.h"
#include "ISelectionSet.h"

namespace Framework
{

/********************************************************************************
* IAttributeTable��ʸ�����Ա�Ļ���
* 
*********************************************************************************/

class FRAMEWORK_DLL IAttributeTable :public IUIObject
{
public:
	IAttributeTable();
	virtual ~IAttributeTable();
public:

	/**
	* �ر����ݱ�
	*/
	virtual void CloseTable();

	/**
	* �ر����ݱ�
	*/
	virtual void RefreshTable(){};

	/**
	* �������Ա�Ĺ���ͼ��
	*/
	virtual void SetLayer(Carto::ILayerPtr pLayer);


	/**
	* �ж����ݱ��Ƿ��Ѿ���
	*/
	virtual bool TableIsOpen();


	/**
	* ����ͼ���ѡ��
	*/
	virtual void UpdateLayerSelction();

	/**
	* ���ݱ��Ƿ���Ա༭
	*/
	virtual bool CanEdit( );


	/**
	* ѡ��ȫ��
	*/
	void SelectAll();

	/**
	* ȡ��ѡ��
	*/
	void SelectNone();

	/**
	* �õ���¼����
	*/
	long GetRecordCount(){return m_totalRecord;}

	/**
	* �õ�ѡ�е���Ŀ
	*/
	long GetSelectCount(){return m_selRecord;}

	/**
	* ����ѡ��
	*/
   virtual void SetSelction(Geodatabase::ISelctionSetPtr pSel);

	/**
	* �õ����Ա��Ӧ��ͼ��
	*/
	virtual Carto::ILayerPtr GetCurSelectLayer();

	static IAttributeTable* GetActiveAttributeTable();

protected:
	Carto::ILayerPtr m_pLayer; //���Ա������ͼ��

	//�ܼ�¼��
	long m_totalRecord;

	//ѡ�м�¼��
	long m_selRecord;

};

}


#endif