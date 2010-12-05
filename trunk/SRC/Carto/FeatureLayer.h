//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/29
// ������  ʸ�����ݲ�
//////////////////////////////////////////////////////////////////////

#ifndef _FeatureLayer_h
#define _FeatureLayer_h

#include "IRender.h"
#include "ISelectionSet.h"
#include "LabelRender.h"


namespace Carto
{
	class IRender;
	class CARTO_DLL CFeatureLayer : public ILayer
	{
	public:
		CFeatureLayer();
		~CFeatureLayer();


	public:
		/**
		* ���л�����
		* @param otSystem::IArchive &ar �ĵ���
		*/
		virtual void serialization(SYSTEM::IArchive &ar);

		static SYSTEM::CSmartPtr<CFeatureLayer> CreateFeatureLayer(Geodatabase::IGeodataObjectPtr  pDataObject);

		virtual bool SetData(Geodatabase::IGeodataObjectPtr pDataObject);

		virtual long GetFeatureType();

		virtual void SetDrawDynamicLabel( bool bDraw = false ) { m_bDrawDynamicLabel = bDraw; }

		virtual bool GetDrawDynamicLabel() { return m_bDrawDynamicLabel; }

		virtual void SetFeatureRender(IRenderPtr pRender);

		virtual SYSTEM::CSmartPtr<IRender> GetFeatureRender() { return m_pRender; }

		virtual void Draw(Display::IDisplayPtr pDisplay,DRAW_CONTENT content);

		virtual void ClearSelectionSet();

		/**
		* ѡ��ͼ����ĳ�����ϣ�������������ѡ��
		* @param query ��ѯ����
		* @return 
		*/
		void Select(Geodatabase::CSimpleQuery* query, SELECT_OPTION selectOption = SELECT_REPLACE);

		Geodatabase::ISelctionSetPtr GetSelection(){return m_pSelectionset;};

		//����ѡ��Ҫ�صķ���
		void SetSelectionSymbol(Display::ISymbolPtr pSymbol);

		//�õ�ѡ��Ҫ�صķ���
		Display::ISymbolPtr GetSelectionSymbol();

		//����ѡ��
		void SetSelection(Geodatabase::ISelctionSetPtr pSelection);

		std::map<Display::ISymbolPtr, std::string>& GetLabels();

		std::map<Display::ISymbolPtr, std::string>& GetDecriptions();

		virtual CLegendInfoPtr GetLegendInfo();

		//���ñ�ע(Label)Render
		void SetLabelRender( Carto::CLabelRenderPtr pLabelRender ) { m_pLabelRender = pLabelRender; }
		Carto::CLabelRenderPtr GetLabelRender( void ) { return m_pLabelRender; }

	private:


	private:

		//
		bool m_bDrawDynamicLabel;

		//
		IRenderPtr m_pRender;

		//
		Geodatabase::ISelctionSetPtr m_pSelectionset;

		Display::ISymbolPtr m_pSelSymbol;

		Carto::CLabelRenderPtr m_pLabelRender;

	};

	typedef SYSTEM::CSmartPtr<CFeatureLayer> IFeatureLayerPtr;

}

#endif