#pragma once

template <class T>
class CProxy_IGeoMapEvents : public IConnectionPointImpl<T, &__uuidof( _IGeoMapEvents ), CComDynamicUnkArray>
{
	//警告此类将由向导重新生成。
public: 

	//触发图元删除事件
    HRESULT Fire_ElementDeleted(IElement* element)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
        CComVariant* pvars = new CComVariant[1];

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			//将连接点接口转换成IDispatch
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				VariantClear(&varResult);
				pvars[0] = reinterpret_cast<IUnknown*>(element);
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
		}
		delete[] pvars;
		return varResult.scode;
	}
};
