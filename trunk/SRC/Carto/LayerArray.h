//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/11/25
// 描述：  数据层layer的集合
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


		inline int Add(Carto::ILayerPtr ptrLayer) {
			push_back(ptrLayer);
			return (int)(size() - 1);
		};

		inline void RemoveAt(int nIndex, int nCount = 1) {
			_ASSERT(nIndex >= 0 && nIndex < (int)size() && nIndex + nCount <= (int)size());

			int i;
			std::vector < ILayerPtr >::iterator pos = begin();
			for (i = 0; i < nIndex; i++, pos++);

			if (nCount == 1) erase(begin() + nIndex);
			else {
				erase(begin() + nIndex, begin() + nIndex + nCount);
			}
		};
		inline void InsertAt(int nIndex, Carto::ILayerPtr ptrLayer, int nCount = 1) 
		{
			_ASSERT(nIndex >= 0);
			if (nIndex > (int)size()) 
				insert(end(), nCount, ptrLayer);
			else 
				insert(begin() + nIndex, nCount, ptrLayer);
		};

		CLayerArray& operator =(const CLayerArray& la);

		inline ILayerPtr GetAt(int nIndex) const {
			_ASSERT(nIndex < (int)size());
			return (*this)[nIndex];
		};


		inline void RemoveAll() {
			clear();
		};
	public:
		inline int GetSize() const { return (int)size(); };
	};

}
#endif //LAYERARRAY_H
