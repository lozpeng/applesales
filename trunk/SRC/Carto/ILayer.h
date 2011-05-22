//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2010/11/15
  // ������  ���ݲ�Ľӿڶ��壬�����������ݲ㣨դ��ʸ���Ȳ㣩����������
//////////////////////////////////////////////////////////////////////


#ifndef _ILayer_H
#define _ILayer_H

#include <Geometry/geom/Envelope.h>
#include "IGeoDataObject.h"
#include "IDisplay.h"
#include "SimpleQuery.h"
#include "AffineTransform.h"
#include "LegendInfo.h"

namespace GEOMETRY
{
	namespace geom
	{
		class Geometry;
		class Envelope;
	}
}

namespace Carto 
{
	class CARTO_DLL ILayer : public SYSTEM::ISerialization
	{
	public:
public:
	ILayer();
	virtual ~ILayer();

public:
	/**
	* ����߼�ͼ������
	* @return �����߼�ͼ������
	*/
	LAYER_TYPE GetLayerType() { return m_layerType; }

	/**
	* ��������ͼ�����߼�ͼ��
	* @param pDataObject ���ݶ���
	* @return �����سɹ��򷵻�true������Ϊfalse
	*/
	virtual bool SetData(Geodatabase::IGeodataObjectPtr pDataObject);

	/**
	* ����
	* @param pDisplay ��ʾ
	* @param content = eDCGeometry Ĭ��Ϊ������
	* @return 
	*/
	virtual void Draw(Display::IDisplayPtr pDisplay,DRAW_CONTENT content = drawAll);

	/**
	* ���ͼ����
	* @return ����ͼ����
	*/
	std::string GetName() { return m_Name; }

	/**
	* ����ͼ����
	* @param Name ͼ����
	*/
	void SetName(std::string Name) { m_Name = Name;}

	/**
	* ���ͼ����Ϣ
	* @return ����ͼ��������Ϣ
	*/
	std::string GetLayerDesciption() { return m_csDescription; }

	/**
	* ����ͼ����Ϣ
	* @param csDescription ͼ����Ϣ
	*/
	virtual void SetLayerDescription(std::string csDescription) { m_csDescription = csDescription;}

	/**
	* ��õ���Χ
	* @return ����Χ
	*/
	virtual GEOMETRY::geom::Envelope GetEnvelope();

	/**
	* ���л�����
	* @param System::IArchive &ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	/**
	* ѡ��ͼ����ĳ�����ϣ�������������ѡ��
	* @param query ��ѯ����
	* @return 
	*/
	virtual void Select(Geodatabase::CSimpleQuery* query, SELECT_OPTION selectOption = SELECT_REPLACE);

	virtual void ClearSelectionSet()=0;

	/**
	* ��������ͼ��
	* @param ar �ĵ���
	* @return �������ɹ���Ϊͼ�㣬ʧ��ΪNULL
	*/
	static SYSTEM::CSmartPtr<ILayer> CreateLayerFromStream( SYSTEM::IArchive &ar );

	/**
	* ����ͼ��
	* @param pDataObject ���ݶ���
	* @return �������ɹ���Ϊͼ�㣬ʧ��ΪNULL
	*/
	static SYSTEM::CSmartPtr<ILayer> CreateLayer(Geodatabase::IGeodataObjectPtr pDataObject);

	/**
	* �����ʾ״̬
	* @return ��Ϊtrue��Ϊ��ʾ��falseΪ����
	*/
	BOOL GetVisible() { return m_bVisible; }

	/**
	* ������ʾ״̬
	* @param bVisible true��Ϊ��ʾ��falseΪ����
	*/
	void SetVisible(bool bVisible) { m_bVisible = bVisible; }

	/**
	* �������ͼ��
	* @return ����ȡ�ɹ�Ϊ����ͼ�㣬����ΪNULL
	*/
	Geodatabase::IGeodataObjectPtr GetDataObject(void) 
	{ 
		return m_pDataObject;
	}

	/**
	* ���͸��ֵ 
	* @return ����͸��ֵ
	*/
	unsigned short GetTransparentValue() { return m_TransparentAlphaValue; }

	/**
	* ����͸��ֵ
	* @param TransparentValue ͸��ֵ
	*/
	void SetTransparent(unsigned short TransparentValue) { m_TransparentAlphaValue=TransparentValue; }

	/**
	* �����ܷ���б����߷�Χ������
	* @param bFlag ��Ϊtrue��������ã�falseΪ����������
	*/
	void SetEnableScaleRange(bool bFlag) { m_bScaleRange=bFlag;}

	/**
	* ��ñ����߷�Χ���õ�״̬
	* @return true��������ã�falseΪ����������
	*/
	bool GetEnableScaleRange() { return m_bScaleRange; }

	/**
	* ���ñ��������Χ
	* @param double dScaleMax
	* @return 
	*/
	void SetScaleRangeMax(double dScaleMax) { m_dScaleMax = dScaleMax;}

	/**
	* ���ñ�������С��Χ
	* @param double dScaleMin
	* @return 
	*/
	void SetScaleRangeMin(double dScaleMin) { m_dScaleMin = dScaleMin;}

	/**
	* ��ñ��������Χ
	* @return 
	*/
	double GetScaleRangeMax() { return m_dScaleMax; }

	/**
	* ��ñ�������С��Χ
	* @return 
	*/
	double GetScaleRangeMin() { return m_dScaleMin; }

	/**
	* ����֮ǰ���Ĵ���
	* @return 
	*/
	virtual void BeforeDraw(SYSTEM::CSmartPtr<Display::IDisplay> pDisplay);

	/**
	* ����֮�����Ĵ���
	* @return 
	*/
	virtual void AfterDraw(SYSTEM::CSmartPtr<Display::IDisplay> pDisplay);

	/*
	����ͼ����ʾ˳��
	*/
	void SetLayerPosition(LAYER_POSITION pos);

	LAYER_POSITION GetLayerPostion();

	//auxiliary Layer
	void AddAuxiliaryLayer(SYSTEM::CSmartPtr<ILayer> ptrLayer);

	bool RemoveAuxiliaryLayer(SYSTEM::CSmartPtr<ILayer> ptrLayer);

	bool IsAuxiliaryLayerExist(SYSTEM::CSmartPtr<ILayer> ptrLayer);

	SYSTEM::CSmartPtr<ILayer> GetAuxiliaryLayer(long index);

	long GetAuxiliaryLayerCount();

	CAffineTransformPtr GetAffineTransPtr(){return m_pAffineTransform;}

	/*
	* �õ�ͼ������Ϣ
	*/
	virtual CLegendInfoPtr GetLegendInfo();

public:
	
	//��ȡ/����ͼ���Ƿ�ӵ���Լ���������ʾ����
	virtual void		get_Cached(bool& bCached);
	virtual void		set_Cached(bool bCached);
	//��ȡ/����ͼ�㻺��ID
	virtual void		get_CacheId(short& sId);
	virtual void		set_CacheId(short sId);


protected:

	//layer name
	std::string m_Name;

	//is visible
	bool m_bVisible;

	//layer description
	std::string m_csDescription;

	//layer's data object
	Geodatabase::IGeodataObjectPtr m_pDataObject;

	//layer type
	LAYER_TYPE m_layerType;

	//transparent 
	unsigned short m_TransparentAlphaValue; // ͸����0~100

	//layer visible range
	bool m_bScaleRange;
	double m_dScaleMax,m_dScaleMin;

	//layer position
	LAYER_POSITION m_Position;

	//auxiliary layers
	std::vector<SYSTEM::CSmartPtr<ILayer>> m_auxiliaryLayers;

	//����任
	CAffineTransformPtr m_pAffineTransform;
protected:
	short				m_sCachedId;			//����ID
	bool				m_bCached;				//ͼ���Ƿ�ӵ�л���

	};

	typedef SYSTEM::CSmartPtr<ILayer> ILayerPtr; //layer����ָ��

}
#endif