//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2010/11/18
  // 描述：  数据层的接口定义，其它地理数据层（栅格、矢量等层）均由其派生
//////////////////////////////////////////////////////////////////////


#ifndef ILayer_H
#define Ilayer_H

#include "ISerialization.h"
namespace Carto 
{
	class CARTO_DLL ILayer : public SYSTEM::ISerialization
	{
	public:
		ILayer(void);
		virtual ~ILayer(void);

	};

	typedef SYSTEM::CSmartPtr<ILayer> ILayerPtr; //layer智能指针

}
#endif