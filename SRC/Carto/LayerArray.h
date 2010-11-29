//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/25
// ������  ���ݲ�layer�ļ���
//////////////////////////////////////////////////////////////////////

#ifndef LAYERARRAY_H
#define LAYERARRAY_H


#include "ILayer.h"
#include <vector>

namespace Carto{

class CARTO_DLL CLayerArray : public std::vector<ILayerPtr> , public SYSTEM::ISerialization 
{
public:

    ~CLayerArray();

    CLayerArray();

public:
	
	virtual void serialization(SYSTEM::IArchive &ar);

	int ChangeOrder(int From, int To);

	int MoveToTop(int FromPos);

	long FindIndex(Carto::ILayerPtr ptrLayer);

	CLayerArray& operator =(const CLayerArray& la);

	inline ILayerPtr GetAt(int nIndex) const {
		_ASSERT(nIndex < (int)size());
		return (*this)[nIndex];
	};

	inline void RemoveAt(int nIndex) {
		_ASSERT(nIndex >= 0 && nIndex < (int)size());

	    erase(begin() + nIndex);
		
	};
};

}
#endif //LAYERARRAY_H
