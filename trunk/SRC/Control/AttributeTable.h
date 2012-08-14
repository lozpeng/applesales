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

//通知父窗口选择数目发生改变
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
	* 打开矢量数据源的属性表
	* @ 参数pFeatureClass，数据源的指针 
	* @ 参数bIsSelDispField，是否要选择显示字段
	* @return 成功返回TRUE,失败返回FALSE
	*/
	bool OpenTable(Geodatabase::IFeatureClassPtr pFeatureClass,bool bIsSelDispField=true);

	/**
	* 判断数据表是否已经打开
	*/
	virtual bool TableIsOpen();

	/**
	* 关闭数据表
	*/
	virtual void CloseTable();

	/**
	* 数据表是否可以编辑
	*/
	virtual bool CanEdit( );

	/**
	* 刷新显示
	*/
	virtual void RefreshTable();

	//查询
	void TableQuery();

	/**
	* 设置选择集
	*/
	void SetSelction(Geodatabase::ISelctionSetPtr pSel);

	/**
	* 设置是否编辑
	*/
	void SetEditMode(bool bedit =true);

	bool IsEditMode() const;

	//选择全部
	bool SelectAll( );

	//取消选择全部
	bool SelectNone( );

	//设置全部字段可见
	bool ShowAllFields();

	//添加字段 
	bool AddField();

	//查找替换
	void FindReplace();

	//设置表格显示属性
	void SetTableProperty();
	
	//输出到表格到Txt文件
	void OutputToTxt( LPCTSTR lpszFileName );

	//输出表格到Exel
	void OutputToDbf( LPCTSTR lpszFileName );

	//获得当前选择FeatureClass
	Geodatabase::IFeatureClassPtr GetFeatureClass(){ return m_pFeatureClass;}
	
	//通过listItem的值修改Feature的值 
	void ChangeFeatureFromListItem( CBCGPGridItem* pItem, int nRow, int nColumn );

	//获得选中的行
	void GetSelectRows( std::vector<long> &vSelRows, ROWTYPE type );

	//获得所有的行
	void GetAllRows( std::vector<long> &vAllRows, ROWTYPE type );

	//获得行数
	int GetRowCount();

protected:
	/***********重载CBCGPGridCtrl的函数****************************/

	virtual CBCGPGridRow* OnCreateVirtualRow (BCGPGRID_DISPINFO* pdi);

	virtual CBCGPGridItem* OnCreateVirtualItem (BCGPGRID_DISPINFO* pdi);

	virtual void OnItemChanged (CBCGPGridItem* pItem, int nRow, int nColumn);

	//当点击排序时
	virtual void ToggleSortColumn (int nColumn);

	//选择发生改变时
	virtual void OnSelChanged (const CBCGPGridRange &range, BOOL bSelect);

	virtual CBCGPGridRow* CreateVirtualRow (int nRowIndex);

private:
	/**
	* 按照属性值的大小进行排序
	*/
	BOOL SortByFieldValue(int nColumn,bool bAscending);

	//更新选择集
	void UpdateSelection();

	/**
	* 更新图层的选择集
	*/
	void UpdateLayerSelction();


	//向父窗口发消息
	void SendMessage2Parent(UINT message,WPARAM wParam = 0,LPARAM lParam = 0 );

	//更新菜单状态
	void UpdateMenuStatus(CMenu *pMenu, UINT nMenuID);

	//添加列到统计
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

	//显示的字段列表
	CStringArray m_cDisplayFieldArray;

	long m_CurRow;     //当前行号

	long m_CurColumn;  //当前列号

	std::vector<long> m_sortlist; //排序后的列表

	//表里面的字段描述
	std::vector<Geodatabase::CFieldPtr> m_allFields;

	std::vector<long> m_indexes;

	Geodatabase::CFeaturePtr m_curFeature;
	
	std::vector<Geodatabase::CFeaturePtr> m_vecCopyFeatures;

	//格式化输出
	std::vector<FIELD_DISPLAY_FORMAT> m_vecFieldFormat;

	bool   m_bEditMode;

	Geodatabase::ISelctionSetPtr m_pSelection;

	bool m_bLockSelection;

	//右键单击弹出快捷菜单时操作的列
	int m_nHitColumn;

	//是否输出全部行 false只输出选中的列
	bool m_bIsOupputAll;

	long m_nDecimalNum;
}; // Class CAttributeTable

} // namespace Control

#endif // _CONTROL_ATTRIBUTE_TABLE_H_