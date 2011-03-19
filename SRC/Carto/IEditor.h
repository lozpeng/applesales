#ifndef  _IEDITOR_H_
#define  _IEDITOR_H_

#include "IDisplay.h"

namespace Carto
{

	class CMap;

	/************************************************************************************
	* IEditor是矢量编辑对象的接口,它提供了开始，结束、保存编辑的方法
	*
	***********************************************************************************/
	class  CARTO_DLL IEditor
	{
	public:
		IEditor();
		virtual ~IEditor();
	public:


		/**
		* 开始编辑
		*/
		virtual void StartEdit() =0;

		/**
		* 结束编辑
		* @param bSave 是否保存修改
		*/
		virtual void StopEdit(bool bSave) =0;

		/**
		* 保存编辑
		*/
		virtual void SaveEdit() =0;

		/**
		* 是否在编辑
		*/
		virtual bool IsEditing() =0;

		/**
		* 撤销操作
		*/
		virtual void Undo() =0;

		/**
		* 重做操作
		*/
		virtual void Redo() =0;

		/**
		* 是否可以撤销
		*/
		virtual bool CanUndo() =0;

		/**
		* 是否可以重做
		*/
		virtual bool CanRedo() =0;

		/**
		* 绘制编辑对象，如正在创建的图形，编辑的图形等
		*/
		virtual void DrawEdit(Display::IDisplayPtr pDisplay) =0;
		/**
		* 设置编辑的地图
		* @param pMap 地图指针
		*/
		void SetMap(CMap *pMap){m_pGeoMap =pMap;}

		/**
		* 得到编辑的地图指针
		*/
		CMap* GetMap() {return m_pGeoMap;}

	protected:

		//编辑器关联的地图
		CMap *m_pGeoMap;
	};

	typedef SYSTEM::CSmartPtr<IEditor> IEditorPtr;

}


#endif