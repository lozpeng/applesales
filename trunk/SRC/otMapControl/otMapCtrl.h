#pragma once

#include "IAction.h"
#include <Map.h>
#include <IDisplay.h>

namespace Carto
{
	class CMap;
}

enum SERIEALIZE_TYPE
{
	SERIEALIZE_NONE = 0x00, //
	SERIEALIZE_MAP = 0x01,  //����ELEMENT��MAP
	SERIEALIZE_LAYOUT= 0x02,//��ͼ����Ԫ�� 
	SERIEALIZE_MAPELEMENT= 0x03,//��ͼELEMNT
	SERIEALIZE_ALL = 0x04		//ȫ�����
};

class CotMapCtrl : public COleControl
{
	DECLARE_DYNCREATE(CotMapCtrl)

// ���캯��
public:
	CotMapCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CotMapCtrl();

	DECLARE_OLECREATE_EX(CotMapCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CotMapCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CotMapCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CotMapCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()



// ���Ⱥ��¼� ID
public:
	enum {
		dispidStopFlashLayer = 27L,
		dispidFlashLayer = 26L,
		dispidSaveElement = 25L,
		dispidRemoveElement = 24L,
		dispidLoadElementFile = 23L,
		dispidOutputMapToFile = 22L,
		dispidOutputMap = 21L,
		dispidMoveCenterTo = 20L,
		dispidPixelToMap = 19L,
		dispidMapToPixel = 18L,
		dispidMouseIcon = 17,
		dispidMouseType = 16,
		dispidLoadGWF = 15L,
		dispidRefreshScreen = 14L,
		dispidScreenCanvas = 13,
		dispidUpdateContent = 12L,
		dispidAddShpFile = 11L,
		eventidOnMouseMove = 4L,
		eventidOnMouseUp = 3L,
		eventidOnMouseDown = 2L,
		eventidOnDoubleClick = 1L,
		dispidFullExtent = 10,
		dispidViewExtent = 9,
		dispidObject =8,
		dispidMap = 7,
		dispidMoveMap = 6L,
		dispidAddImageFile = 5L,
		dispidAddTmsFile = 4L,
		dispidAction = 3,
		dispidAddFeatureLayer =1L,
		dispidRefresh         =2L,
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    
public:

	otActionType GetAction(void);

	void SetAction(otActionType newVal);

	//���ʸ��ͼ��
	afx_msg void AddFeatureLayer(BSTR filename);

	//��TMS�ļ�������ӵ�Map��
	afx_msg void AddTmsFile(BSTR filename);

	//��Ӱ���ļ�������ӵ�Map��
	VARIANT_BOOL AddImageFile(BSTR filename);

	//ˢ�µ�ͼ����������
	afx_msg void Refresh();

	//�ƶ���ͼ
	void MoveMap(DOUBLE dx, DOUBLE dy);

	afx_msg IGeoMap* GetMap(void);

	//�õ��ؼ��ڲ��Ľӿ�
	afx_msg IDispatch* GetObject();


	//�õ���������ͼ���ĵ���Χ
	IotEnvelope* GetViewExtent(void);
	void SetViewExtent(IotEnvelope* pVal);


	/**
	* �õ�������ͼ�ķ�Χ
	*/
	IotEnvelope* GetFullExtent(void);

    //��shp�ļ�������ӵ�Map��
	void AddShpFile(LPCTSTR filename);

	//���µ�ͼ������
	void UpdateContent(otDrawContent content);

	//�õ���ĻDisplay
	IotCanvas* GetScreenCanvas(void);

	void RefreshScreen();

	//���ع����ļ�
	void LoadGWF(LPCTSTR filename);

	//�������������
	otMouseType GetMouseType(void);
	void SetMouseType(otMouseType newVal);

	void SetMouseIcon(LPCTSTR newVal);

	void MapToPixel(DOUBLE mapX, DOUBLE mapY, LONG* X, LONG* Y);

	IotPoint* PixelToMap(LONG x, LONG y);
	void MoveCenterTo(IotPoint* point);

	//������Ļ���ݵ�ָ��DC��
	void OutputMap(LONG hDC);

	//������Ļ���ݵ��ļ�
	VARIANT_BOOL OutputMapToFile(LPCTSTR filename, otOutputFileType filetype);

	//����ͼԪ�ļ�
	void LoadElementFile(LPCTSTR filename);

	//ɾ��ͼԪ
	void RemoveElement(void);

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

public:

	

	//�ƶ���ͼ����
	 void OffsetClient(long offset_x, long offset_y);

	 //���ù��
	 void SetCursorType(long lCursorType) { m_lCursorType=lCursorType;}	

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
protected:
	

private:
	//
	IGeoMapPtr m_potGeoMap;
	//�ڲ��洢�ĵ�ͼ����
	Carto::CMapPtr m_pGeomap;

	//Ψһ��otGeomapָ��
	IGeoMap *m_pMapInterface;

	//�ͻ���DC
	HDC m_hClientDC;
	//���Ƶ��ڴ�DC
	HDC m_hMemDC;

	//��ǰ�Ķ���
	IAction *m_pCurAction;

	otActionType m_ActionType;

	//�ؼ��ı���ɫ
	COLORREF m_BgColor;

	//�ؼ����ڴ�С
	long m_lSizeX;
	long m_lSizeY;

	long m_lCursorType;

	//�߿�Ĵ�С
	int m_nBorderSize;

	//��ĻDisplay
	Display::IDisplayPtr m_pScreenDisplay;

	double m_dblScale;
	bool m_bTimer;
	GEOMETRY::geom::Envelope m_srcEnvelop; //��¼�ڴ�DC�ĵ���Χ
	double   m_srcScale;
	bool m_bMouseWheel;

    //���������
    otMouseType   m_mouseType;

	//�Զ��������
	HCURSOR       m_CustomCursor;
    

	int m_FlashLayerId;
    
protected:


	/**
	* �������˫���¼�
	* @param button ��ʾ���µ�������ĸ���,0����û�а�����1���������2�����Ҽ�,3�������
	* @param flag ���ֵ������,���ڼ�¼����һЩ����������
	* @param X �����X���꣬�ͻ�������ϵ
	* @param Y �����Y���꣬�ͻ�������ϵ
	* @param MapX �����X���꣬��ͼ����ϵ
	* @param MapY �����Y���꣬��ͼ����ϵ
	* 
	*/
	void FireDoubleClick(LONG button, LONG flag, LONG X, LONG Y, DOUBLE MapX, DOUBLE MapY);

	
	/**
	* ������굥���¼�
	* @param button ��ʾ���µ�������ĸ���,1���������2�����Ҽ�,3�������
	* @param flag ���ֵ������,���ڼ�¼����һЩ����������
	* @param X �����X���꣬�ͻ�������ϵ
	* @param Y �����Y���꣬�ͻ�������ϵ
	* @param MapX �����X���꣬��ͼ����ϵ
	* @param MapY �����Y���꣬��ͼ����ϵ
	* 
	*/
	void FireMouseDown(LONG button, LONG flag, LONG x, LONG y, DOUBLE mapX, DOUBLE mapY);
	
	/**
	* �������̧���¼�
	* @param button ��ʾ���µ�������ĸ���,1���������2�����Ҽ�,3�������
	* @param flag ���ֵ������,���ڼ�¼����һЩ����������
	* @param X �����X���꣬�ͻ�������ϵ
	* @param Y �����Y���꣬�ͻ�������ϵ
	* @param MapX �����X���꣬��ͼ����ϵ
	* @param MapY �����Y���꣬��ͼ����ϵ
	* 
	*/
	void FireMouseUp(LONG button, LONG flag, LONG x, LONG y, DOUBLE mapX, DOUBLE mapY);


	void FireMouseMove(LONG button, LONG flag, LONG x, LONG y, DOUBLE mapX, DOUBLE mapY);

private:
	void serialization(SYSTEM::IArchive &ar,SERIEALIZE_TYPE sType);
	
	//����Ҫ����ͼ��memDC�ϵ�λ��
	void CalSrcRect(GEOMETRY::geom::Envelope extent,CRect &rect);
	//������ͼ��view�е�λ��
	void CalDestRect(GEOMETRY::geom::Envelope srcExtent,GEOMETRY::geom::Envelope destExtent,CRect &rect);

protected:
	void SaveElement(LPCTSTR filename);
	public:
	void FlashLayer(LONG layerID, LONG millisecond);
	void StopFlashLayer(void);
};

