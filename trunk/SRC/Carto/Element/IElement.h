//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/12
// ������  ���Ҫ�صĽӿ�  ���б��Ҫ����������
//////////////////////////////////////////////////////////////////////


#ifndef IELEMENT_H
#define IELEMENT_H

#include "ElementDefine.h"
#include "IDisplay.h"
//#include "AdvLineSymbol.h"
#include "SimpleMarkerSymbol.h"
#include "ISerialization.h"
#include "ISelectionTracker.h"
#include "SimpleFillSymbol.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"

namespace Element{
/** @interface */
/**
*�๦�ܸ�����Element����
*/

class CElementCollection;

class CARTO_DLL IElement : public SYSTEM::ISerialization  {
public:
	IElement();

	IElement(const GEOMETRY::geom::Geometry& geometry);
	
	virtual ~IElement();

	/**
	* �������������л�����
	* @param SYSTEM::IArchive &ar �����ļ���
	* @return  void
	*/
	virtual void serialization(SYSTEM::IArchive &ar);   
	
	/**
	* ��������:��¡����
	* @return _ptr_t<IElement> Element����ָ��
	*/
	virtual SYSTEM::CSmartPtr<IElement> Clone();


	/**
	* ��������:������������ͼԪ
	* @param SYSTEM::IArchive &ar ������
	* @return _ptr_t<IElement> Element����ָ��
	*/
	static SYSTEM::CSmartPtr<IElement> CreateElementFromStream(SYSTEM::IArchive &ar);

	/**
	* ��������:�½�ͼԪ
	* @param ELEMENT_TYPE type ͼԪ����
	* @return _ptr_t<IElement> Element����ָ��
	*/
	static SYSTEM::CSmartPtr<IElement> CreateElement( ELEMENT_TYPE type);
   
	/**
    * ��������������Element����
	*/
	void Activate( Display::IDisplayPtr pDisplay);

	/**
	* ��������������Element������
	*/
	void Deactivate(Display::IDisplayPtr pDisplay );
  
	/**
    * �����������Ƿ񼤻�
	* @return bool
	*/
	bool IsActive(Display::IDisplayPtr pDisplay);
	
	/**
	* �������������������element�����������Ƿ���read only
	* @param BOOL bLock ��־����������TRUE���������FALSE������
	*/
	void Lock();

	/**
	* �������������������element�����������Ƿ���read only
	* @param BOOL bLock ��־����������TRUE���������FALSE������
	*/
	void UnLock();
	
	/**
	* ������������������״̬
	* @return BOOL
	*/
	BOOL IsLocked();

	/**
	* ��������������Element����
	* @param std::string ����
	* @return 
	*/
	void SetName(std::string strName);

	/**
	* ��������������Element����
	*  @return std::string ����
	*/
	std::string GetName();
   
	/**
    * ��������������Element����
	* @return ELEMENT_TYPE
	*/
	ELEMENT_TYPE GetType();

	/**
	* ��������������ͼ��
	* @param GEOMETRY::geom::Geometry& geometry ͼ��,�ⲿ����ͼ��
	* @return void
	*/
	virtual void SetGeometry(GEOMETRY::geom::Geometry& geometry);

	/**
	* ��������������ͼ��
	* @param GEOMETRY::geom::Geometry& geometry ͼ�Σ��ڲ�����ͼ��ָ��
	* @return void
	*/
	virtual void SetGeometry(GEOMETRY::geom::Geometry* geometry);
	/**
	* ��������������Element��״
	* @return GEOMETRY::geom::Geometry ͼԪͼ��
	*/
	virtual GEOMETRY::geom::Geometry* GetGeometry();

	/**
	* ��������������Element����Χ
	* @return GEOMETRY::geom::Envelope&
	*/
	virtual  GEOMETRY::geom::Envelope GetEnvelope();

	/**
	* �������������÷���
	* @param Display::ISymbolPtr ͼԪ����
	*/
	void SetSymbol(Display::ISymbolPtr pSymbol);

	/**
	* ������������ȡ����
	* @return Display::ISymbolPtr ͼԪ����
	*/
	Display::ISymbolPtr GetSymbol();

	/**
	* ��������������ͼԪ��λ��
	* @return ELEMENT_ANCHOR_POS ͼԪ��λ��
	*/
	virtual void SetAnchorPos(ELEMENT_ANCHOR_POS anchorpos){m_AnchorPos = anchorpos;};

	/**
	* ������������ȡͼԪ��λ��
	* @return ELEMENT_ANCHOR_POS ͼԪ��λ��
	*/
	virtual ELEMENT_ANCHOR_POS GetAnchorPos(){return m_AnchorPos;};

	//////////////////////////////////////////////////////////////////////////
	/**
	* �������������ñ༭ģʽ
	* @param ELEMENT_EDIT_MODE editMode �༭ģʽ
	*/
	virtual void SetEditMode(ELEMENT_EDIT_MODE editMode);
	
	/**
	* ������������ȡ�༭ģʽ
	* @return ELEMENT_EDIT_MODE �༭ģʽ
	*/
	ELEMENT_EDIT_MODE GetEditMode();

	/**
	* �������������û���ģʽ
	* @param ELEMENT_DRAW_MODE editMode ����ģʽ
	*/
	virtual void SetDrawMode(ELEMENT_DRAW_MODE drawMode);

	/**
	* ������������ȡ����ģʽ
	* @return ELEMENT_DRAW_MODE  ����ģʽ
	*/
	ELEMENT_DRAW_MODE GetDrawMode();

	/**
	* ���������������Ƿ���Ա༭�����
	* @return BOOL 
	*/
	virtual void SetWHRatioMode(ELEMENT_WIDTH_HEIGHT_RATIO eWHRatio);

	/**
	* ������������ȡ�Ƿ���Ա༭�����
	* @return BOOL 
	*/
	virtual BOOL CanSetWHRMode();

	/**
	* ������������ȡ�����ģʽ
	* @return BOOL 
	*/
	ELEMENT_WIDTH_HEIGHT_RATIO GetWHRatioMode();

	//////////////////////////////////////////////////////////////////////////

	/**
	* �������������ݿռ�ѡ������������ͼԪѡ����
	* @param GEOMETRY::geom::Geometry* pSelectGeometry ѡ��Χ
	* @param long lSpatialRelation �ռ�ѡ������
	* @param CElementCollection& selectedSubElements �����������ѡ�е�ͼԪ�ĸ���ͼԪ����
	* @return BOOL ��־ͼԪ�����Ƿ�ѡ��
	*/
	virtual BOOL Select(GEOMETRY::geom::Geometry* pSelectGeometry, long lSpatialRelation, CElementCollection& selectedSubElements,double dbTolerance=0.0);

	/**
	* ���������������ж�
	* @param GEOMETRY::geom::Coordinate coord �����������
	* @param bool dbTolerance ���̾���
	* @BOOL bTestSelectionHandle �Ƿ��жϻ���handle
	* @return void
	*/
	virtual HIT_TEST_RES HitTest ( GEOMETRY::geom::Coordinate coord, double dbTolerance=0, HIT_MODE nHitMode = HH_HIT_GEOMETRY); 
	
	/**
	* �����������ƶ�Handle
	* @param HIT_HANDLE nHandle �ƶ���handle
	* @param GEOMETRY::geom::Coordinate coord handle�����ƶ�����λ��
	* @return void
	*/
	virtual void MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord);

	/**
	* �����������ƶ��ڵ�
	* @param long lIndex �ƶ��Ľڵ����
	* @param GEOMETRY::geom::Coordinate coord �ڵ㽫���ƶ�����λ��
	* @return void
	*/
	virtual void MoveVertixTo(long lIndex,GEOMETRY::geom::Coordinate coord);

	/**
	* ��������������
	* @param DIS_POINT pPoint ���ŵ�
	* @param double sx x�᷽������ű���
	* @param double sy y�᷽������ű���
	* @return void
	*/
	virtual void Scale(DIS_POINT pPoint, double sx, double sy);

	/**
	* ����������ƽ��
	* @param double dx x�᷽���ƽ�ƾ���
	* @param double dy y�᷽���ƽ�ƾ���
	* @return void
	*/
	virtual void Move(double dx, double dy);

	/**
	* ������������ת
	* @param DIS_POINT pPoint ��ת���ĵ�
	* @param double rotationAngle ��ת�Ƕȣ�PIΪ��λ��
	* @return void
	*/
	virtual void Rotate(DIS_POINT pPoint, double rotationAngle);

	/**
	* �����������ı�ͼ�ε���Χ
	* @param newEnvelope �µĵ���Χ
	* @return void
	*/
	virtual void ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope);


	ISelectionTrackerPtr GetSelectionTracker(){return m_pSelectionHandle;};

	//////////////////////////////////////////////////////////////////////////
	
	/**
	* ��������������
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @param bool bPrint �Ƿ��ӡ
	* @return void
	*/
	virtual void Draw( Display::IDisplayPtr pDisplay/* , ELEMENT_EDIT_MODE editMode = EEM_NO_EDIT*/);

	/**
	* �������������Ƶ���Χ
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @param bool bPrint �Ƿ��ӡ
	* @return void
	*/
	virtual void DrawEnvelope(Display::IDisplayPtr pDisplay);

	
protected:

	/**
	* ��������:ͼԪgeometry�ı����¼���Ӧ
	* @return void
	*/
	virtual void GeometryChangedEvents();

	/**
	* ��������:�ı�ͼԪgeometry�ķ�Χ
	* @return void
	*/
	/**
	* ��������������ͼԪ
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawNoEditMode(Display::IDisplayPtr pDisplay);
	/**
	* ����������ѡ��ͼԪ����
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawSelectMode(Display::IDisplayPtr pDisplay);
	/**
	* �����������༭ͼԪ�ڵ����
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawEditVertixMode(Display::IDisplayPtr pDisplay);
	/**
	* �����������������ڻ���ͼԪ
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawOnDrawMode(Display::IDisplayPtr pDisplay);
	/**
	* �����������ƶ�ͼԪ����
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawMoveMode(Display::IDisplayPtr pDisplay);
	/**
	* ����������ͼԪ��������
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawNormal(Display::IDisplayPtr pDisplay)=0;
	/**
	* ����������ͼԪ�ݸ����
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawDraft(Display::IDisplayPtr pDisplay);
	/**
	* ������������ӡͼԪ����
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawPrint(Display::IDisplayPtr pDisplay);

	/**
	* ��������������ѡ���
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawSelectionTracker(Display::IDisplayPtr pDisplay);

	/**
	* �������������Ʊ༭�ڵ�
	* @param Display::IDisplayPtr pDisplay ����ָ��IDisplay
	* @return void
	*/
	virtual void DrawVertixTracker(Display::IDisplayPtr pDisplay);
	
protected:
	BOOL m_bLocked;								//�Ƿ�ֻ��

	BOOL m_bActive;								//�ڵ�ǰdisplay���Ƿ���ʾ

	ELEMENT_TYPE m_enumElementType;				//ͼԪ����

	std::string m_strName;						//ͼԪ����

	//ͼ�Ρ�λ�á��༭�����Ʒ���
	GEOMETRY::geom::Geometry* m_pGeometry;	//ͼԪ������״

	Display::ISymbolPtr	m_pSymbol;			//ͼԪ���Ʒ���

	ELEMENT_ANCHOR_POS m_AnchorPos;				//��λ��

	ELEMENT_WIDTH_HEIGHT_RATIO	m_eWHRatio;		//��߱�������ģʽ

	BOOL	m_bCanSetWHRMode;					//�û��Ƿ������ÿ�߱�ģʽ

	//���ơ��༭ģʽ
	ELEMENT_DRAW_MODE m_DrawMode;				//��־����ģʽ

	ELEMENT_EDIT_MODE m_EditMode;				//��־�༭ģʽ

	//ѡ�񡢱༭���Ʒ���
	ISelectionTrackerPtr m_pSelectionHandle;		//ѡ���

	Display::CSimpleMarkerSymbolPtr m_pVertixMarkerSymbol;

	Display::CSimpleMarkerSymbolPtr m_pControlPtMarkerSymbol;

	Display::CSimpleLineSymbolPtr m_pTrakerLineSymbol;

	Display::CSimpleFillSymbolPtr m_pEnvelopeSymbol; //�߽���Ʒ���

};
typedef SYSTEM::CSmartPtr<IElement> IElementPtr;
}
#endif //IELEMENT_H
