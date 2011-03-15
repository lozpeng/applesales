//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/28
// ������  �������
//////////////////////////////////////////////////////////////////////


#ifndef _GraphicLayer_h
#define _GraphicLayer_h
#include "GraphicsContainer.h"
#include "GraphicsContainerSelect.h"
#include "SpatialQuery.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
#include "ILayer.h"

namespace Carto
{

class CARTO_DLL CGraphicLayer : public ILayer, public Element::CGraphicsContainer
								, public Element::CGraphicsContainerSelect
{
public:
	CGraphicLayer();
	CGraphicLayer(const GEOMETRY::geom::Envelope& envelope);
	virtual ~CGraphicLayer();

	/**
	* ���л�����
	* @param SYSTEM::IArchive &ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	/**
	* ѡ��ͼ����ĳ�����ϣ�������������ѡ��
	* @param query ��ѯ����
	* @return 
	*/
	void Select(Geodatabase::CSimpleQuery* query, SELECT_OPTION selectOption = SELECT_REPLACE);

	void ClearSelectionSet();

	void Draw(Display::IDisplayPtr pDisplay,DRAW_CONTENT content);

	void SelectAllElements();

	GEOMETRY::geom::Envelope GetEnvelope();

	void AddElement(Element::IElementPtr pElement);

	void RemoveElement(Element::IElementPtr pElement);
	
	void BringForward(Element::IElementPtr pElement);

	void SendBackward(Element::IElementPtr pElement);

	void BringToFront(Element::IElementPtr pElement);

	void SendToBack(Element::IElementPtr pElement);

	void BringForward(Element::CElementCollection pElements);

	void SendBackward(Element::CElementCollection pElements);

	void BringToFront(Element::CElementCollection pElements);

	void SendToBack(Element::CElementCollection pElements);

	//��Element����Ϊshp ��ǰѡ�����ȫ��
	void SaveElementAsShp(std::string filename,bool bSlected=false);

	/*
	*����			:	ע��ɾ��ͼԪ�Ļص�����
	* ����			:	boost::function fun ��������
	*��������		:	boost::signals::connection �ź����Ӷ���*/
	static boost::signals::connection RegisterDeleteElement(boost::function<void (Element::IElementPtr pElement)> fun);

protected:
	void SpatialSelect(Geodatabase::CSpatialQuery* query, SELECT_OPTION selectOption = SELECT_REPLACE);

	void SetMapFrame();

protected:
	GEOMETRY::geom::Envelope m_envelope;
};
typedef SYSTEM::CSmartPtr<CGraphicLayer> CGraphicLayerPtr;

};

#endif