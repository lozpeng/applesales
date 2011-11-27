/*
*
*  author:wsm(wangshuming@gmail.com) 
*  date  :2008-2-22 15:00:09
*  desc  : copy from  Delta3D (Copyright (C) 2005, BMH Associates, Inc)
*/
#pragma once

namespace owUtil
{

	/**
	* @namespace gvUtil::Bits
	*
	* Contains bit-wise operation functionality which makes using bits
	* a little "bit" easier.
	*/
	namespace Bits
	{

		/**
		* See if the "bits" are in "number".
		* @code
		* unsigned int accum = 3;
		* Bits::Has( accum, 1 ); //true
		* Bits::Has( accum, 7 ); //false
		* @endcode
		*/
		template < class N, class B > inline bool Has ( N number, B bits )
		{
			return ( ( number & bits ) == ( static_cast<N>(bits) ) );
		}

		/**
		* Add the "bits" to "number".
		*/
		template < class N, class B > inline N Add ( N number, B bits )
		{
			return ( number | bits );
		}

		//
		//  Remove the "bits" from "number".
		//
		template < class N, class B > inline N Remove ( N number, B bits )
		{
			return ( ( number & bits ) ? ( number ^ bits ) : number );
		}

		/**
		* Toggle the "bits" in "number".
		* @code
		* unsigned int accum = 3;
		* unsigned int newBits;
		* newBits = Bits::Toggle(accum, 1); //newBits = 2
		* newBits = Bits::Toggle(accum, 1); //newBits = 3
		* @endcode
		*/
		template < class N, class B > inline N Toggle ( N number, B bits )
		{
			return ( number ^ bits );
		}

	} //namespace Bits
}//namespace gvUtil
