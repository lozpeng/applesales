
//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/18
// ������  ���ݲ����Ⱦ���壬�����������ݲ㣨դ��ʸ���Ȳ㣩����������
//////////////////////////////////////////////////////////////////////

#ifndef _IRender_h
#define _IRender_h
#include "ICursor.h"
#include "ISelectionSet.h"
#include "IDisplay.h"
#include "LegendInfo.h"

namespace Geodatabase
{
	class ICursor;
	class ISelctionSet;
}

namespace Carto
{

class  CARTO_DLL IRender : public SYSTEM::ISerialization
{
public:
	IRender();
	virtual ~IRender();

public:
	/**
	* ��ѡ�еļ�¼�����л���
	* @param pDisplay ����ָ�룬ָ����ʾ�ӿ�
	* @param pdatarecordset ����ָ�룬ָ���¼��
	*/
	virtual void Draw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor ) = 0;

	/**
	* ��ѡ�еļ�¼�����и�������
	* @param pDisplay ����ָ�룬ָ����ʾ�ӿ�
	* @param pdatarecordset ����ָ�룬ָ���¼��
	*/
	virtual void HighLightDraw( Display::IDisplayPtr pDisplay,  Geodatabase::ICursorPtr pCursor  );

	/**
	* ��ѡ�еļ�¼�����и�������
	* @param pDisplay ����ָ�룬ָ����ʾ�ӿ�
	* @param pSelections ָ���¼����ָ��
	*/
	virtual void HighLightDraw(Display::IDisplayPtr pDisplay,  Geodatabase::ISelctionSet* pSelections);

	/**

	/**
	* ���ר����ֶ���
	* @return ����ר����ֶ���
	*/
	virtual std::string GetRendFieldsStr() = 0;

	/**
	* ����ר��
	* @return ����ר��
	*/
	virtual SYSTEM::CSmartPtr<IRender> CopyNewRender();

	/**
	* ���ר������
	* @return ����ר������
	*/
	RENDER_TYPE GetRenderType();

	/**
	* ����Renderͼ��
	* @return
	*/
	void SetAffineTransform(CAffineTransformPtr pAffineTransform) { m_pAffineTransform = pAffineTransform; }

	/**
	* ��ø�����ʾ����ɫ
	* @return ��ɫֵ
	*/
	COLORREF GetHighLightColor();

	/**
	* ���ø�����ʾ����ɫ
	* @param color ��ɫֵ
	*/
	void SetHighLightColor(COLORREF color);

	/**
	* ���ø�����ʾ�ķ���
	* @param pSymbol ����
	*/
	void SetHighLightSymbol(Display::ISymbolPtr pSymbol);

	/**
	* ����ר��ʸ������
	* @param type ʸ������
	*/
	virtual void SetRenderFeatureType(long type);

	/**
	* ���ר��ʸ������
	* @return ����ʸ������
	*/
	long GetRenderFeatureType();

	/*
	* �õ�ͼ������Ϣ
	*/
	virtual CLegendInfoPtr GetLegendInfo();

	/**
	* �Ե�ǰר��������л�����
	* @param ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar) = 0;

	/**
	* ����������ר��
	* @param ar �ĵ���
	* @return ����ר��
	*/
	static SYSTEM::CSmartPtr<IRender> CreateRenderFromStream(SYSTEM::IArchive &ar);

	/**
	* ����ר��
	* @param type ר������
	* @param RenderExtName ��չר����
	* @return ����ר��
	*/
	static SYSTEM::CSmartPtr<IRender> CreateRender( RENDER_TYPE type , std::string RenderExtName = "" );

protected:

	COLORREF m_HighLightColor;
	RENDER_TYPE m_type;
	long m_lFeaturetype;

	Display::ISymbolPtr m_pHighLightSymbol;
	Carto::CAffineTransformPtr m_pAffineTransform;

};

typedef SYSTEM::CSmartPtr<IRender> IRenderPtr;



}

#endif