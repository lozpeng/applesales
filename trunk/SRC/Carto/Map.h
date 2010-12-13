

#ifndef _Map_h
#define _Map_h

#include "IDisplay.h"
#include "LayerArray.h"
//#include "IEditor.h"
//#include "IEagleEyeView.h"
#include "GraphicLayer.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
#include "ISerialization.h"
//#include "AoiManager.h"
//#include "CrossLine.h"
//#include "ElementOperationStack.h"


namespace Carto
{

	/*
	* CMap�ǵ�ͼ����
	*/
	class CARTO_DLL CMap : public SYSTEM::ISerialization
	{
	public:
		CMap();
		virtual ~CMap();

	public:

		/**
		* ��ȡDisplay
		* @return IDisplayָ��
		*/
		Display::IDisplayPtr GetDisplay();

		/**
		* ����Display
		* @param pNewDisplay Displayָ��
		*/
		Display::IDisplayPtr SetDisplay(Display::IDisplayPtr pNewDisplay);

		/**
		* ����
		*/
		virtual void Draw(long content);

		/**
		* ���ƺ�
		*/
		virtual void OnAfterDraw(long content);

		/**
		* ����ǰ
		*/
		virtual void OnBeforeDraw(long content);

		/**
		* ���л�
		* @param ar �ĵ���
		*serializationEx1 ֻ���л�ELEMENT, serializationEx2ֻ���л�ELMENT����
		*/
		virtual void serialization(SYSTEM::IArchive &ar);
		void serializationEx1(SYSTEM::IArchive &ar);
		void serializationEx2(SYSTEM::IArchive &ar);

		/**
		* ����
		* @return CMapPtr
		*/
		SYSTEM::CSmartPtr<CMap> Clone();

		/**
		* ���õ�ͼ��mapctrl�е����к�
		* @return 
		*/
		void SetID(long id);

		/**
		*  ��õ�ͼ��mapctrl�е����к�
		* @return ��ͼ��ͼ���
		*/
		long GetID();

		/**
		* ��õ�ͼ��ͼ����
		* @return ��ͼ��ͼ����
		*/
		std::string GetName();

		/**
		* ���õ�ͼ��ͼ����
		* @param Name ��ͼ��ͼ����
		*/
		void SetName(std::string Name);

		/**
		* ��õ�ͼ�ĵ�λ
		* @return ��ͼ�ĵ�λ
		*/
		SYSTEM::SYS_UNIT_TYPE GetUnit(){return m_unit;};

		/**
		* �����µ�ͼ�㲢��ӵ�map��
		* @param pDataObject ����
		* @return ����ӳɹ�Ϊtrue������Ϊfalse
		*/
		BOOL AddNewLayer(Geodatabase::IGeodataObjectPtr pDataObject);
		/**
		* Ϊ��ͼ��ͼ���һ��ͼ��
		* @return ����ӳɹ�Ϊtrue������Ϊfalse
		*/
		BOOL AddLayer(ILayerPtr pLayer);

		/**
		* ɾ��ͼ��
		* @param iIndex ����
		* @return ��ɾ���ɹ�Ϊtrue������Ϊfalse
		*/
		BOOL DeleteLayer(int iIndex);

		/**
		* ɾ��ָ��ͼ��
		* @param ptrLayer ָ��ͼ��
		* @return ��ɾ���ɹ�Ϊtrue������Ϊfalse
		*/
		BOOL DeleteLayer(ILayerPtr ptrLayer);

		/**
		* ��ͼ������
		* @param ptrLayer ָ��ͼ��
		*/
		void MoveLayerUp(ILayerPtr ptrLayer);

		/**
		* ��ͼ������
		* @param ptrLayer ָ��ͼ��
		*/
		void MoveLayerDown(ILayerPtr ptrLayer);

		/**
		* ��ͼ���Ƶ�����
		* @param ptrLayer ָ��ͼ��
		* @return 
		*/
		void MoveLayerToTop(ILayerPtr ptrLayer);

		/**
		* ��ͼ���Ƶ��ײ�
		* @param ptrLayer ָ��ͼ��
		*/
		void MoveLayerToBottom(ILayerPtr ptrLayer);

		/**
		* �����ͼ��ͼ��ͼ��
		* @return 
		*/
		void Clear();

		// ǳcopy��ͼ�㼶����Ϊ���ù�ϵ
		//SYSTEM::CSmartPtr<CMap> Clone();

		/**
		* ���µ�ͼͶӰ
		* @retrun ָ��ͼ��
		*/
		BOOL	UpdateMapProjection(ILayerPtr pLayer);

		/**
		* ��ȡ��ͼͶӰ
		* @retrun ��ͼ��ǰͶӰ
		*/
		std::string GetMapProjection();

		/**
		* ��ͼ���Ƶ��ײ�
		* @param ptrLayer ָ��ͼ��
		*/
		void	UpdateMapExtent();

		/**
		* ���ͼ����
		* @return ͼ����
		*/
		CLayerArray& GetLayers();


		/**���õ�ǰ����ͼ��
		*
		* @param ILayerPtr ptrLayer
		* @return 
		*/
		void SetActiveLayer(ILayerPtr ptrLayer);

		/**
		* �õ���ǰ����ͼ��
		*/

		ILayerPtr GetActiveLayer();

		/**
		* ��ñ༭��
		*/
		//IEditorPtr GetEditor() {return m_pEditor;};

		/**
		* ���ñ༭��
		*/
		//void SetEditor(IEditorPtr pEditor){m_pEditor =pEditor;}

		/** 
		* ���ӥ�ۻ��ƶ���
		*/
		//IEagleEyeViewPtr GetEagleViewDrawer() {return m_pEagleEyeViewPtr;};

		/** 
		* ����ӥ�ۻ��ƶ���
		*/
		//void SetEagleViewDrawer(IEagleEyeViewPtr pView) {m_pEagleEyeViewPtr = pView;};

		CGraphicLayerPtr GetGraphicLayer();

		void ResetGraphicLayer();

		//Element::CElementOperationStackPtr GetElementOperationStack(){return m_pElementOperStack;};

		/** 
		* ���AOI������
		*/
		//CAoiManagerPtr GetAOIManager() {return m_pAoiManager;};

		/** 
		* ���ʮ��˿����
		*/
		//CCrossLine* GetCrossLiner() {return m_pCrossLine;};

		/** 
		* ����ʮ��˿����
		*/
		//void SetCrossLiner(CCrossLine* pCrossLiner) {m_pCrossLine = pCrossLiner;};



		/** ��������	:	RegisterDeleteLayer(boost::function fun)
		*����			:	ע��ɾ��ͼ��Ļص�����
		* ����			:	boost::function fun ��������
		��������		:	boost::signals::connection �ź����Ӷ���*/
		static boost::signals::connection RegisterDeleteLayer(boost::function<void (ILayerPtr)> fun);

		/** ��������	:	RegisterActiveLayer(boost::function fun)
		*����			:	ע�ἤ��ͼ��Ļص�����
		* ����			:	boost::function fun ��������
		��������		:	boost::signals::connection �ź����Ӷ���*/
		static boost::signals::connection RegisterActiveLayer(boost::function<void (ILayerPtr)> fun);

		/** ��������	:	RegisterChangeMapExtent(boost::function fun)
		*����			:	ע�����MAP����Χ�Ļص���������MAP��Χ�仯ʱ��һЩ��Ҫ������Ӧ
		* ����			:	boost::function fun ��������
		��������		:	boost::signals::connection �ź����Ӷ���*/
		static boost::signals::connection RegisterChangeMapExtent(boost::function<void (CMap*)> fun);

		/** ��������	:	RegisterChangeMapExtentMode(boost::function fun)
		*����			:	ע�����MAP����Χ�Ļص���������MAP��Χģʽ�仯ʱ��һЩ��Ҫ������Ӧ
		* ����			:	boost::function fun ��������
		��������		:	boost::signals::connection �ź����Ӷ���*/
		static boost::signals::connection CMap::RegisterChangeMapExtentMode(boost::function<void (CMap*)> fun);

		/** ��������	:	RegisterChangeMapProj(boost::function fun)
		*����			:	ע�����MAPͶӰ�Ļص���������MAPͶӰ�仯ʱ��һЩ��Ҫ������Ӧ
		* ����			:	boost::function fun ��������
		��������		:	boost::signals::connection �ź����Ӷ���*/
		static boost::signals::connection CMap::RegisterChangeMapProj(boost::function<void (CMap*)> fun);
		/** ��������	:	RegisterChangeMapProj(boost::function fun)
		*����			:	ע�����MAPͶӰ�Ļص���������MAPͶӰ�仯ʱ��һЩ��Ҫ������Ӧ
		* ����			:	boost::function fun ��������
		��������		:	boost::signals::connection �ź����Ӷ���*/
		static boost::signals::connection CMap::RegisterMapReDrawed(boost::function<void (CMap*)> fun);

		/** ��������	:	RegisterLayerColorAdjust(boost::function fun)
		*����			:	ע��ɾ��ͼ��Ļص�����
		* ����			:	boost::function fun ��������
		��������		:	boost::signals::connection �ź����Ӷ���*/
		static boost::signals::connection RegisterLayerColorAdjust(boost::function<void (ILayerPtr)> fun);


		////view //////////////////////////////////////////////////////////////////////
		void SetViewBound(DIS_BOUND bound);

		DIS_BOUND GetViewBound();

		void SetViewEnvelope(GEOMETRY::geom::Envelope env){m_viewEnvelope = env;};

		GEOMETRY::geom::Envelope GetViewEnvelope();

		void SetExtentMode(MAP_EXTENT_MODE extMode){m_ExtentMode = extMode;};

		MAP_EXTENT_MODE GetExtentMode();

		void SetReferenceScale(double refScale); 
		double GetReferenceScale();

		void SetFramed(BOOL bFramed);

		void SetFramePageScale(double pageScale,double maptoPageScale);

		virtual const GEOMETRY::geom::Envelope& GetExtent(){return m_Envelope;};

		double GetMapToPageScale(){return m_dbMapToPageScale;};

		void SetDrawBound(DIS_BOUND bound, BOOL bCacheBuffer = FALSE);


	protected:

		long m_lID;

		//��ͼ��
		std::string m_strMapName;

		//map project
		std::string m_strWkt;

		//ͼ������
		CLayerArray	m_Layers;	

		//elementͼ��
		CGraphicLayerPtr	m_pGraphicLayer;

		MAP_EXTENT_MODE m_ExtentMode;			//��Χģʽ

		GEOMETRY::geom::Envelope	m_viewEnvelope;

		GEOMETRY::geom::Envelope	m_drawEnvelope;

		double	m_dbReferenceScale;

		//////////////////////////////////////////////////////////////////////////
		//Element::CElementOperationStackPtr m_pElementOperStack;	//ͼԪ��������ջ


		//////////////////////////////////////

		//��ʶ��ͼ�Ƿ��Ѿ�����ͶӰ
		BOOL m_bSetPrj;

		//map extent
		GEOMETRY::geom::Envelope m_Envelope;


		//Display device
		Display::IDisplayPtr m_pDisplay;


		//��ͼ�ĵ�λ
		SYSTEM::SYS_UNIT_TYPE m_unit;

		//��ǰ����ͼ��
		//ILayerPtr m_activeLayer;

		//�༭��
		//IEditorPtr m_pEditor;

		//���浱ǰ��ͼλ�õ���ʱ����
		//IEagleEyeViewPtr m_pEagleEyeViewPtr;

		BOOL m_bFramed;

		double m_dbFramePageScale;

		double m_dbMapToPageScale;



		//ʮ��˿
		//CCrossLine* m_pCrossLine;

		//����AOI
		//CAoiManagerPtr     m_pAoiManager;

		//����ͼ����ͼ�������е�����
		long m_lActiveLayerId;

	public:
		double m_dbMapFixScale;

	};
	typedef SYSTEM::CSmartPtr<CMap> CMapPtr;

}

#endif