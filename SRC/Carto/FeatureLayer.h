//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/11/29
// 描述：  矢量数据层
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
		* 序列化操作
		* @param otSystem::IArchive &ar 文档流
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
		* 选择图层中某个集合，根据条件产生选择集
		* @param query 查询条件
		* @return 
		*/
		void Select(Geodatabase::CSimpleQuery* query, SELECT_OPTION selectOption = SELECT_REPLACE);

		Geodatabase::ISelctionSetPtr GetSelection(){return m_pSelectionset;};

		//设置选中要素的符号
		void SetSelectionSymbol(Display::ISymbolPtr pSymbol);

		//得到选中要素的符号
		Display::ISymbolPtr GetSelectionSymbol();

		//设置选择集
		void SetSelection(Geodatabase::ISelctionSetPtr pSelection);

		std::map<Display::ISymbolPtr, std::string>& GetLabels();

		std::map<Display::ISymbolPtr, std::string>& GetDecriptions();

		virtual CLegendInfoPtr GetLegendInfo();

		//设置标注(Label)Render
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