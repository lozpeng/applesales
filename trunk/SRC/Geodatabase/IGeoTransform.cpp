#include "stdafx.h"
#include "IGeoTransform.h"

namespace Geodatabase{

IGeoTransform::IGeoTransform()
{

}

IGeoTransform::~IGeoTransform()
{

}

CSpatialReferencePtr IGeoTransform::GetSourceCS() const
{
	return m_pSrcCS;
}

CSpatialReferencePtr IGeoTransform::GetTargetCS() const
{
	return m_pTargetCS;
}

} //namespace Geodatabase