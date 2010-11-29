//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/25
// ������  ���ݲ�layer�ļ���
//////////////////////////////////////////////////////////////////////

#ifndef LAYERARRAY_H
#define LAYERARRAY_H


#include "alm.h"
#include "ILayer.h"

namespace Carto{

class CARTO_DLL CLayerArray : public SYSTEM::CArray<ILayerPtr> , public SYSTEM::ISerialization 
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
};

}
#endif //LAYERARRAY_H
