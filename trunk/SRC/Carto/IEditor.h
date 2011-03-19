#ifndef  _IEDITOR_H_
#define  _IEDITOR_H_

#include "IDisplay.h"

namespace Carto
{

	class CMap;

	/************************************************************************************
	* IEditor��ʸ���༭����Ľӿ�,���ṩ�˿�ʼ������������༭�ķ���
	*
	***********************************************************************************/
	class  CARTO_DLL IEditor
	{
	public:
		IEditor();
		virtual ~IEditor();
	public:


		/**
		* ��ʼ�༭
		*/
		virtual void StartEdit() =0;

		/**
		* �����༭
		* @param bSave �Ƿ񱣴��޸�
		*/
		virtual void StopEdit(bool bSave) =0;

		/**
		* ����༭
		*/
		virtual void SaveEdit() =0;

		/**
		* �Ƿ��ڱ༭
		*/
		virtual bool IsEditing() =0;

		/**
		* ��������
		*/
		virtual void Undo() =0;

		/**
		* ��������
		*/
		virtual void Redo() =0;

		/**
		* �Ƿ���Գ���
		*/
		virtual bool CanUndo() =0;

		/**
		* �Ƿ��������
		*/
		virtual bool CanRedo() =0;

		/**
		* ���Ʊ༭���������ڴ�����ͼ�Σ��༭��ͼ�ε�
		*/
		virtual void DrawEdit(Display::IDisplayPtr pDisplay) =0;
		/**
		* ���ñ༭�ĵ�ͼ
		* @param pMap ��ͼָ��
		*/
		void SetMap(CMap *pMap){m_pGeoMap =pMap;}

		/**
		* �õ��༭�ĵ�ͼָ��
		*/
		CMap* GetMap() {return m_pGeoMap;}

	protected:

		//�༭�������ĵ�ͼ
		CMap *m_pGeoMap;
	};

	typedef SYSTEM::CSmartPtr<IEditor> IEditorPtr;

}


#endif