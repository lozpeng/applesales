//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2010/11/18
  // ������  ���ݲ�Ľӿڶ��壬�����������ݲ㣨դ��ʸ���Ȳ㣩����������
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

	typedef SYSTEM::CSmartPtr<ILayer> ILayerPtr; //layer����ָ��

}
#endif