#include "stdafx.h"
#include "ProjTransform.h"
#include "ogr_spatialref.h"

namespace Geodatabase{

CProjTransform::CProjTransform()
{
    m_handle =NULL;
}

CProjTransform::CProjTransform(CSpatialReferencePtr pSrcCS,CSpatialReferencePtr pTargetCS)
{
   m_handle =NULL;
   
   Init(pSrcCS,pTargetCS);
}

CProjTransform::~CProjTransform()
{
   Clear();
}

void CProjTransform::Clear()
{
    if(m_handle)
	{
        OGRCoordinateTransformation* pCT =(OGRCoordinateTransformation*)m_handle;
		delete pCT;
		m_handle=NULL;
	}
	m_pSrcCS.reset();
	m_pTargetCS.reset();
}

void CProjTransform::Init(Geodatabase::CSpatialReferencePtr pSrcCS, Geodatabase::CSpatialReferencePtr pTargetCS)
{
	Clear();
	if(!pSrcCS || !pTargetCS)
	{
		return;
	}

	m_pSrcCS =pSrcCS;

	m_pTargetCS=pTargetCS;


    OGRSpatialReference *pSrc= (OGRSpatialReference*)pSrcCS->GetHandle();

	OGRSpatialReference *pTarget= (OGRSpatialReference*)pTargetCS->GetHandle();

	m_handle =OGRCreateCoordinateTransformation(pSrc,pTarget);


}

bool CProjTransform::Transform(int nCount, double *x, double *y, double *z)
{
	if(!m_handle)
	{
		return false;
	}

    OGRCoordinateTransformation* pCT =(OGRCoordinateTransformation*)m_handle;

	return pCT->Transform(nCount,x,y,z);

}


} //namespace Geodatabase