#pragma once
#include "DisplayHeader.h"
#include "IFillSymbol.h"
#include "CDC.h"
#include "IArchive.h"


namespace Display{
class DISPLAY_DLL CPicFillSymbol :public IFillSymbol
{
public:
	CPicFillSymbol();

	CPicFillSymbol(const CPicFillSymbol& toPicFillSymbol);

	CPicFillSymbol& operator = (const CPicFillSymbol& toPicFillSymbol);

	~CPicFillSymbol();

	SYMBOL_TYPE GetType();	//�õ���������	

	

	void SetReverseColor(bool bReverseColor);//��ת��ɫ//��ֵʱ��ʹ��

	bool GetReverseColor();

	virtual void Draw(void* pObject);//���ƺ���

	void SetBGColor(unsigned long nBGcolor);//���ñ���ɫ

	void SetTransparecyColor(unsigned long nTransparecyColor);//�����ڸ�ɫ
	
	unsigned long GetBGColor();//�õ�����ɫ

	unsigned long GetTransparecyColor();//�õ��ڸ�ɫ
	
	void SetWidthScale (float Scale);		//���÷��ź������

	float GetWidthScale ();		//�õ����ź������

	void SetFileName(std::string cFilename);

	//�õ�λͼ·��
	std::string GetFileName() const {return m_cPicPath;}

	void SetHeightScale(float Scale);//�����������
	
	float GetHeightScale();//�õ��������
	
	void SetOffsetXY( float OffsetX , float OffsetY);//����ƫ��
	
	void SetSeparationXY(float SeparationX , float SeparationY);//���ü��
	
	float GetOffsetX() ;

	float GetOffsetY() ;//�õ�ƫ��
	
	float GetSeparationX();  

	float GetSeparationY();//�õ����
	
	void SetAngle(float Angle);

	float GetAngle();

	virtual void Zoom(float rate);

	virtual void ClearDC();

public:

	virtual void SelectDC(Display::CDC * pDC);

	virtual void SetReadyDraw();

	virtual void SetProperties(const char* PropertyName , const _variant_t& PropertyValue);

	virtual _variant_t GetProperties(const char* PropertyName);			//�õ���ǰ���ŵ���������
protected:

	void DrawPic(DIS_POINT & Destpoint, long destW, long destH);

protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();

private:
	unsigned long m_lBackGroundColor,m_lTransparecyColor;//����ɫ��͸��ɫ
	long m_nSrcW;											//ͼ��ԭʼ���
	long m_nSrcH;											//ͼ��ԭʼ�߶�  
	bool m_bReverseColor;									//�Ƿ�ת��ɫ
	bool m_bPng;											//��png��
	Display::CDC  m_MemDC;										//�ڴ�DC
	float m_fScaleX,m_fScaleY,m_fAngle;						//����X,Y�������,�Ƕ�
    long m_lDestW,m_lDestH;									//Ŀ���ȣ��߶�
	long m_OffsetX,m_OffsetY;								//X,Yƫ����
	long m_SeparationX,m_SeparationY;						//λͼ���
	float m_fOffsetX , m_fOffsetY;							
	float m_fSeparationX , m_fSeparationY;
	float m_fZoom;
	void * m_bitmapData;									//ͼ������
	int m_bitmapDataLens;									//ͼ�����ݳ���
	int m_bpp;                                              //ͼ��λ���
	bool m_bSetFileName;									//�Ƿ��ȡ��
	std::string m_cPicPath;							//����ͼƬ·��
public:

    virtual void serialization(SYSTEM::IArchive & ar);

};

typedef SYSTEM::CSmartPtr<CPicFillSymbol> IPicFillSymbolPtr;
}

