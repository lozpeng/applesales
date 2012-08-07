#ifndef  _IMAGE_CLIP_H_
#define  _IMAGE_CLIP_H_

#include "IRasterDataset.h"
#include <vector>

namespace ImageProcess
{

	 IMP_DLL bool ImgClip(const char* pszInFile, 
		const char* pszOutFile, 
		GEOMETRY::geom::Envelope& aoiExtent,
		double dblCellX,
		double dblCellY);

	 IMP_DLL bool TargetClip(const char* pszInImage,
		 const char* pszTargetFile,
		 long lWidth,
		 long lHeight,
		 const char* pszOutPath);

	 //相关系数图
	IMP_DLL bool RelativeMap(const char* strSrc, const char* strDest, const char *strResult, int nsize, SYSTEM::IProgress *pProgress);

    IMP_DLL double CalCorrelation(float* pBase, float* pSamp, int nBlockLen);
}

#endif