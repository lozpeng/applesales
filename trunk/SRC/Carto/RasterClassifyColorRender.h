#ifndef _RASTER_CLASSIFY_COLOR_RENDER_H_
#define _RASTER_CLASSIFY_COLOR_RENDER_H_
#include "IRasterRender.h"
#include "CartoHeader.h"
#include "IRasterDataset.h"
#include "IColorRamp.h"
#include <list>
using std::list;


namespace Carto
{

class CARTO_DLL CRasterClassifyColorRender : public IRasterRender
{
public:
	CRasterClassifyColorRender();
	virtual ~CRasterClassifyColorRender();
public:

	virtual void Draw( Display::IDisplayPtr pDisplay,Geodatabase::IRasterDataset* pRaster);

	/**
	* �Ե�ǰר��������л�����
	* @param ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	int getBreak(){return m_nBreak;}

	void setBreak(int nbreak){m_nBreak=nbreak;}

	Display::IColorRampPtr getColorRamp(){return m_pColorRamp;}

	void setColorRamp(Display::IColorRampPtr pColorRamp);

private:

	template<class DataType>
	void ReadDrawData(GEOMETRY::geom::Envelope dataDrawExtent/*,DataType nulldata*/);

	bool DibDraw();


private:
	//�ֶ���Ŀ
	int m_nBreak;
	Display::IColorRampPtr m_pColorRamp;

	std::vector<Display::RGBColor> m_colorgroup;

	Display::IDisplayPtr m_pDisplay;

	//��Ļ���Ʒ�Χ
	RECT			m_destRect;
	//������ʾ�ĵ���Χ
	GEOMETRY::geom::Envelope m_DrawDataEnv;

	//���ڶ�ȡ��ʾ��ͼ�������
	long			mp_lResampleWidth;

	//���ڶ�ȡ��ʾ��ͼ�������
	long			mp_lResampleHeight;

	//��ǰ������
	double			mp_dblResampleRatio;

	//�������ݳߴ�
	long			mp_lResampleBufferSize;

	unsigned char	*mp_pucBufSrc[3];

};


}

#endif