#ifndef CFRAME_PROPERTY_H
#define CFRAME_PROPERTY_H

#include "SimpleBackground.h"
#include "SimpleBorder.h"
#include "SimpleShadow.h"
#include "ISerialization.h"
namespace Element{

	class CARTO_DLL IFrameProperty : public SYSTEM::ISerialization
{
public:
	IFrameProperty();
	IFrameProperty(const GEOMETRY::geom::Geometry& geometry);
	~IFrameProperty(void);

	virtual void serialization(SYSTEM::IArchive &ar);

	virtual CSimpleBackgroundPtr GetBackground();
	virtual void SetBackground(CSimpleBackgroundPtr pBackground);
	virtual CSimpleBorderPtr GetBorder();
	virtual void SetBorder(CSimpleBorderPtr pBorder);
	virtual CSimpleShadowPtr GetShadow( );
	virtual void SetShadow(CSimpleShadowPtr pShadow);
	


protected:
	//�߿�
	CSimpleBorderPtr m_pBorder;
	//����
	CSimpleBackgroundPtr m_pBackground;
	//��Ӱ
	CSimpleShadowPtr m_pShadow;
};

typedef SYSTEM::CSmartPtr<IFrameProperty> IFramePropertyPtr;
}
#endif
