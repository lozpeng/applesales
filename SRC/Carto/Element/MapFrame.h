//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/14
// ������  ��ͼҪ�ء�����ͼ��
//////////////////////////////////////////////////////////////////////

#ifndef CMAP_FRAME_H
#define CMAP_FRAME_H
#include "IFrameElementBase.h"
#include "MapGrids.h"
#include "IMapSurround.h"
#include "Map.h"
#include "GraphicsContainer.h"

#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>

typedef boost::signals::connection  connection_t;

namespace Element{

class CARTO_DLL CMapFrame :public IFrameElementBase
{
public:
	CMapFrame();
	CMapFrame(const GEOMETRY::geom::Geometry& geometry, Carto::CMapPtr pGeoMap);
	~CMapFrame(void);

	virtual void serialization(SYSTEM::IArchive &ar);

	//��������ͼԪ
	IMapSurroundPtr CreateMapSurroundElement(ELEMENT_TYPE enumElementType);
	
	//��ȡ����
	CMapGrids&	GetMapGrids();

	//������frame�����ĵ�ͼ
	void SetMap(Carto::CMapPtr pMap);

	//��ȡ��frame�����ĵ�ͼ
	Carto::CMapPtr GetMap();

	void SetMapToPageScale(double scale);
	
	//���Ա༭
	//��ͼ/ҳ�����
	double	GetMapToPageScale();

	//��ͼ��ʾ��Χģʽ
	void SetViewExtAutoMode();

	void SetViewExtFixScaleMode(double dbMapScale, GEOMETRY::geom::Coordinate coordLeftBottom);

	void SetViewExtFixExtentMode(GEOMETRY::geom::Envelope viewExtent);

	GEOMETRY::geom::Envelope GetViewEnvelope();

	long GetMapID();

	void SetMapFrameID(long id){m_MapFrameID = id;};

	long GetMapFrameID(){return m_MapFrameID;}; 

	/** ��������	:	RegisterDeleteLayer(boost::function fun)
	*����			:	ע��ɾ��ͼ��Ļص�����
	* ����			:	boost::function fun ��������
	��������		:	boost::signals::connection �ź����Ӷ���*/
	static boost::signals::connection RegisterMapFrameProperChanged(boost::function<void (CMapFrame*)> fun);

	/** ��������	:	RegisterDeleteLayer(boost::function fun)
	*����			:	ע��ɾ��ͼ��Ļص�����
	* ����			:	boost::function fun ��������
	��������		:	boost::signals::connection �ź����Ӷ���*/
	static boost::signals::connection RegisterMapFrameMapSetted(boost::function<void (CMapFrame*)> fun);


protected:
	void UpdateMapFrame(Display::IDisplayPtr pDisplay);
	
	void DrawNormal(Display::IDisplayPtr pDisplay);

	void DrawMap(Display::IDisplayPtr pDisplay);

	void DrawGrids(Display::IDisplayPtr pDisplay);

	void ReDrawMap(Display::IDisplayPtr pDisplay);

	void ReCalcGrid();

	void ReCalcMapToPageScale(Display::IDisplayPtr pDisplay);

	void SetMapFrameDirty(BOOL bDirty);

	void GeometryChangedEvents();

	void SetStandardMappingState( BOOL bIsStdMap = TRUE );

	BOOL GetStandardMappingState( void );

protected:
	connection_t m_ConnectionMapExtentModeChange;

	connection_t m_ConnectionMapRedrawed;

	connection_t m_ConnectionViewChange;

	void CallbackMapRedrawedFun(Carto::CMap* pMap);

	void CallbackMapExtentModeChangedFun(Carto::CMap* pMap);

	void CallbackViewPosChange(Display::VIEW_POSITION viewPosition);


protected:

	int					m_mapID;				//ֻ�����л�readʱ����ʱ����mapid�����ã�

	Carto::CMapPtr m_pGeoMap;				//��Frame������Map

	BOOL				m_bStandardMap;			//��־�Ƿ�Ϊ��׼��ͼ״̬

	long				m_MapFrameID;			//Ψһ��ʶmapframe��ID�ţ���GraphicLayer��������mapsurroundElementѰ����ص�Mapframe

	BOOL				m_bMapProperChanged;	//��ʶmapframe�����Ƿ����

	//�̶�����������
	double				m_dbMapScale;			//Map���layout�ı�����

	BOOL				m_bNewMapScale;			//��־�̶��������Ƿ����

	GEOMETRY::geom::Coordinate	m_coordLeftBottom;	//�̶�������ʱ���½ǵ�λ�� 

	//�̶���Χ
	BOOL		m_bNewFixViewExtent;			//��־�̶���Χ�Ƿ����

	CMapGrids	m_Grids;						//����


	DIS_BOUND	m_drawBound;

};

typedef SYSTEM::CSmartPtr<CMapFrame> CMapFramePtr;

}
#endif
