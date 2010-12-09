#ifndef IBORDER_H
#define IBORDER_H
#include "IElement.h"
#include "ISelectionTracker.h"

namespace Element{

	enum Border_Type
	{
		ST_SIMPLE_BORDER
	};

class CARTO_DLL IBorder : public SYSTEM::ISerialization
{
public:
	IBorder(void);
	//���캯�� pGeometry��״���ڲ��ͷ�
	IBorder(const GEOMETRY::geom::Geometry& geometry);
	virtual~IBorder(void);

	void serialization(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<IBorder> CreateBorderFromStream(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<IBorder> CreateBorder(Border_Type type);

	virtual  void Draw(Display::IDisplayPtr pDisplay)=0;
	virtual void SetGeometry(const GEOMETRY::geom::Geometry& geometry);
	virtual const GEOMETRY::geom::Geometry* GetGeometry();
	virtual const GEOMETRY::geom::Geometry* GetDrawGeometry();
	virtual void SetEnvelope(GEOMETRY::geom::Envelope& envelope);
	virtual const GEOMETRY::geom::Envelope& GetEnvelope();
	virtual void GetGap(float &fXGap, float &fYGap);
	virtual void SetGap(float fXGap, float fYGap);



protected:
	virtual void UpdateDrawGeometry();

protected:
	Border_Type m_type;

	//X������չ���
	float m_fXGap;
	//Y������չ���
	float m_fYGap;
	//������״
	GEOMETRY::geom::Geometry* m_pGeometry;
	//��Gap�����κ�����ڻ��Ƶ���״
	GEOMETRY::geom::Geometry* m_pDrawGeometry;
	//����Χ
	GEOMETRY::geom::Envelope m_Envelope;
	

};

typedef SYSTEM::CSmartPtr<IBorder> IBorderPtr;

}
#endif
