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
	//构造函数 pGeometry形状，内部释放
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

	//X方向扩展宽度
	float m_fXGap;
	//Y方向扩展宽度
	float m_fYGap;
	//基础形状
	GEOMETRY::geom::Geometry* m_pGeometry;
	//经Gap等修饰后的用于绘制的形状
	GEOMETRY::geom::Geometry* m_pDrawGeometry;
	//地理范围
	GEOMETRY::geom::Envelope m_Envelope;
	

};

typedef SYSTEM::CSmartPtr<IBorder> IBorderPtr;

}
#endif
