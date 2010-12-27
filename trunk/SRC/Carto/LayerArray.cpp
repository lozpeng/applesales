/* Generated by Together */
#include "stdafx.h"
#include "LayerArray.h"
//#include "ILayer.h"
namespace Carto{
	Carto::CLayerArray::CLayerArray(){}
	Carto::CLayerArray::~CLayerArray(){}

	int Carto::CLayerArray::ChangeOrder(int From, int To)
	{
		if(From ==To)
		{
			return TRUE;
		}
		long lsize =this->size();
		if(From<0 || From>=lsize)
		{
			return FALSE;
		}
		if(To<0 || To>=lsize)
		{
			return FALSE;
		}

		Carto::ILayerPtr pLayer =(*this)[From];

		RemoveAt(From);        
		insert(begin() + To, 1, pLayer);

		return TRUE;
	}

	int Carto::CLayerArray::MoveToTop(int FromPos)
	{
		return 0;
	}

	void Carto::CLayerArray::serialization(SYSTEM::IArchive &ar)
	{
		if( ar.IsRead() )
		{
			long Size;
			ar & Size;
			for (long i = 0 ; i < Size ; i++ )
			{
				ILayerPtr player = ILayer::CreateLayerFromStream( ar );
				if( player != NULL )
					push_back( player );
			}
		}
		else
		{
			long Size = size();
			ar & Size;
			for (long i = 0 ; i < Size ; i++ )
			{
				ILayerPtr player = (*this)[i];
				player->serialization( ar );
			}

		}
	}


	long Carto::CLayerArray::FindIndex(Carto::ILayerPtr ptrLayer)
	{
		if (ptrLayer == NULL )
		{
			return -1; //ERROR
		}
		long lSize =size();
		for (long i = 0; i < lSize; i++)
		{
			Carto::ILayerPtr tempLayer = (*this)[i];
			if (tempLayer == ptrLayer)
			{
				return i;
			}
		}
		return -1;
	}

	Carto::CLayerArray& Carto::CLayerArray::operator =(const CLayerArray& la)
	{
		clear();
		insert(end(), la.begin(), la.end());
		return *this;
	}
	int Carto::CLayerArray::GetSize()
	{
		return (int)(this->size());
	}
}