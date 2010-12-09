#ifndef ISHADOW_H
#define ISHADOW_H
#include "ISelectionTracker.h"

namespace Element{

	enum Shadow_Type
	{
		ST_SIMPLE_SHADOW
	};

class CARTO_DLL IShadow : public SYSTEM::ISerialization
{
public:
	IShadow(void);
	IShadow(const GEOMETRY::geom::Geometry& geometry);
	virtual~IShadow(void);

	void serialization(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<IShadow> CreateShadowFromStream(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<IShadow> CreateShadow(Shadow_Type type);


	virtual void Draw(Display::IDisplayPtr pDisplay)=0;
	virtual void SetGeometry(const GEOMETRY::geom::Geometry& geometry);
	virtual const GEOMETRY::geom::Geometry* GetGeometry();
	virtual void GetGap(float &fXGap, float &fYGap);
	virtual void SetGap(float fXGap, float fYGap);
protected:
	virtual void UpdateDrawGeometry();

protected:

	Shadow_Type m_type;

	float m_fXGap;
	float m_fYGap;

	//基础形状
	GEOMETRY::geom::Geometry* m_pGeometry;
	//经Gap等修饰后的用于绘制的形状
	GEOMETRY::geom::Geometry* m_pDrawGeometry;


};

typedef SYSTEM::CSmartPtr<IShadow> IShadowPtr;
}
#endif
