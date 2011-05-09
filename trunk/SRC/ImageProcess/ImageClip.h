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


}

#endif