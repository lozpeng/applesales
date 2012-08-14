#ifndef  _CONTROL_ATTRIBUTE_TABLE_H_
#define  _CONTROL_ATTRIBUTE_TABLE_H_

#include "IAttributeTable.h"
#include "IFeatureClass.h"
#include "SelectionSet.h"
#include "CommonData.h"

class CReFormatItem : public CBCGPGridItem
{
public:
	CReFormatItem();
	~CReFormatItem();
};

//֪ͨ������ѡ����Ŀ�����ı�
#define WM_UPDATESELECTNUM WM_USER+100
#define WM_MESSAGE_FLASH WM_USER+101


namespace Control
{

class CONTROL_DLL CAttributeTable : public CBCGPGridCtrl, public Framework::IAttributeTable
{
public:
	CAttributeTable();
	virtual ~CAttributeTable();

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL CreateControl( std::string Name, void *pParent , long nID );

	/**
	* ��ʸ������Դ�����Ա�
	* @ ����pFeatureClass������Դ��ָ�� 
	* @ ����bIsSelDispField���Ƿ�Ҫѡ����ʾ�ֶ�
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	*/
	bool OpenTable(Geodatabase::IFeatureClassPtr pFeatureClass,bool bIsSelDispField=true);

	/**
	* �ж����ݱ��Ƿ��Ѿ���
	*/
	virtual bool TableIsOpen();

	/**
	* �ر����ݱ�
	*/
	virtual void CloseTable();

	/**
	* ���ݱ��Ƿ���Ա༭
	*/
	virtual bool CanEdit( );

	/**
	* ˢ����ʾ
	*/
	virtual void RefreshTable();

	//��ѯ
	void TableQuery();

	/**
	* ����ѡ��
	*/
	void SetSelction(Geodatabase::ISelctionSetPtr pSel);

	/**
	* �����Ƿ�༭
	*/
	void SetEditMode(bool bedit =true);

	bool IsEditMode() const;

	//ѡ��ȫ��
	bool SelectAll( );

	//ȡ��ѡ��ȫ��
	bool SelectNone( );

	//����ȫ���ֶοɼ�
	bool ShowAllFields();

	//����ֶ� 
	bool AddField();

	//�����滻
	void FindReplace();

	//���ñ����ʾ����
	void SetTableProperty();
	
	//��������Txt�ļ�
	void OutputToTxt( LPCTSTR lpszFileName );

	//������Exel
	void OutputToDbf( LPCTSTR lpszFileName );

	//��õ�ǰѡ��FeatureClass
	Geodatabase::IFeatureClassPtr GetFeatureClass(){ return m_pFeatureClass;}
	
	//ͨ��listItem��ֵ�޸�Feature��ֵ 
	void ChangeFeatureFromListItem( CBCGPGridItem* pItem, int nRow, int nColumn );

	//���ѡ�е���
	void GetSelectRows( std::vector<long> &vSelRows, ROWTYPE type );

	//������е���
	void GetAllRows( std::vector<long> &vAllRows, ROWTYPE type );

	//�������
	int GetRowCount();

protected:
	/***********����CBCGPGridCtrl�ĺ���****************************/

	virtual CBCGPGridRow* OnCreateVirtualRow (BCGPGRID_DISPINFO* pdi);

	virtual CBCGPGridItem* OnCreateVirtualItem (BCGPGRID_DISPINFO* pdi);

	virtual void OnItemChanged (CBCGPGridItem* pItem, int nRow, int nColumn);

	//���������ʱ
	virtual void ToggleSortColumn (int nColumn);

	//ѡ�����ı�ʱ
	virtual void OnSelChanged (const CBCGPGridRange &range, BOOL bSelect);

	virtual CBCGPGridRow* CreateVirtualRow (int nRowIndex);

private:
	/**
	* ��������ֵ�Ĵ�С��������
	*/
	BOOL SortByFieldValue(int nColumn,bool bAscending);

	//����ѡ��
	void UpdateSelection();

	/**
	* ����ͼ���ѡ��
	*/
	void UpdateLayerSelction();


	//�򸸴��ڷ���Ϣ
	void SendMessage2Parent(UINT message,WPARAM wParam = 0,LPARAM lParam = 0 );

	//���²˵�״̬
	void UpdateMenuStatus(CMenu *pMenu, UINT nMenuID);

	//����е�ͳ��
	void AddColumnForStatics( int icol, std::vector<LP_CAL_FIELDVALUE>  &vCalFieldsVals );

	void ResetItemValue(CBCGPGridItem* pItem,int nColumn, Geodatabase::CFeaturePtr pFeature);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	
	//Operate Rows
	afx_msg void OnFlash();
	afx_msg void OnPanto();
	afx_msg void OnZoomto();
	afx_msg void OnSelUnsel();
	afx_msg void OnSelReverse();
	afx_msg void OnCopyRow();
	afx_msg void OnPasteRow();
	afx_msg void OnDelRow();

	//Operate Columns
	afx_msg void OnSortAsd();
	afx_msg void OnSortDes();
	afx_msg void OnCalStastic();
	afx_msg void OnFieldCal();
	afx_msg void OnGeometryCal();
	afx_msg void OnHideField();
	afx_msg void OnDelField();
	afx_msg void OnFreezeUnfreeze();
	afx_msg void OnSetFieldPro();
	
private:
	Geodatabase::IFeatureClassPtr m_pFeatureClass;

	//��ʾ���ֶ��б�
	CStringArray m_cDisplayFieldArray;

	long m_CurRow;     //��ǰ�к�

	long m_CurColumn;  //��ǰ�к�

	std::vector<long> m_sortlist; //�������б�

	//��������ֶ�����
	std::vector<Geodatabase::CFieldPtr> m_allFields;

	std::vector<long> m_indexes;

	Geodatabase::CFeaturePtr m_curFeature;
	
	std::vector<Geodatabase::CFeaturePtr> m_vecCopyFeatures;

	//��ʽ�����
	std::vector<FIELD_DISPLAY_FORMAT> m_vecFieldFormat;

	bool   m_bEditMode;

	Geodatabase::ISelctionSetPtr m_pSelection;

	bool m_bLockSelection;

	//�Ҽ�����������ݲ˵�ʱ��������
	int m_nHitColumn;

	//�Ƿ����ȫ���� falseֻ���ѡ�е���
	bool m_bIsOupputAll;

	long m_nDecimalNum;
}; // Class CAttributeTable

} // namespace Control

#endif // _CONTROL_ATTRIBUTE_TABLE_H_