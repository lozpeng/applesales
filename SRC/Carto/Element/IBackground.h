#ifndef IBACKGROUND_H
#define IBACKGROUND_H
#include "ISelectionTracker.h"

namespace Element{

	enum Background_Type
	{
		BT_SIMPLE_BG
	};
class CARTO_DLL IBackground : public SYSTEM::ISerialization
{
public:
	IBackground(void);
	IBackground(const GEOMETRY::geom::Geometry& geometry);

	virtual~IBackground(void);

	void serialization(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<IBackground> CreateBackgroundFromStream(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<IBackground> CreateBackground(Background_Type type);

	virtual void Draw(Display::IDisplayPtr pDisplay)=0;
	virtual void SetGeometry(const GEOMETRY::geom::Geometry& geometry);
	virtual const GEOMETRY::geom::Geometry* GetDrawGeometry();
	virtual const GEOMETRY::geom::Geometry* GetGeometry();
	virtual void GetGap(float &fXGap, float &fYGap);
	virtual void SetGap(float fXGap, float fYGap);


protected:
	virtual void UpdateDrawGeometry();

protected:
	Background_Type m_type;
	//X方向扩展宽度
	float m_fXGap;
	//Y方向扩展宽度
	float m_fYGap;
	//基础形状
	GEOMETRY::geom::Geometry* m_pGeometry;
	//经Gap等修饰后的用于绘制的形状
	GEOMETRY::geom::Geometry* m_pDrawGeometry;

};

typedef SYSTEM::CSmartPtr<IBackground> IBackgroundPtr;
}
#endif