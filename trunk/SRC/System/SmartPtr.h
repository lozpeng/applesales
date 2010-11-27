#ifndef _SYSTEM_SMART_PTR_H
#define _SYSTEM_SMART_PTR_H

#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace SYSTEM
{

	template <class T>
	class CSmartPtr : public boost::shared_ptr<T>
	{
	public:
		CSmartPtr() {};
		CSmartPtr( T* p ) : shared_ptr(p) {};
		template <class Y> 
		CSmartPtr(CSmartPtr<Y> const & other) : shared_ptr(other, boost::detail::dynamic_cast_tag()) {};
		template <class Y>
		CSmartPtr(boost::shared_ptr<Y> const & other) : shared_ptr(other, boost::detail::dynamic_cast_tag()) {};
	};

}


#endif