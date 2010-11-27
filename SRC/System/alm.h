#ifndef _ALM_H_
#define _ALM_H_
#pragma once
#pragma warning(disable:4786)

#include <list>
#include <vector>
#include <map>

#include <crtdbg.h>

#ifndef ASSERT
#define ASSERT
#endif

#ifndef __AFX_H__
struct __POSITION { };


typedef __POSITION * POSITION;

#endif

#ifdef __ATLBASE_H__
#define ASSERT ATLASSERT
#endif
namespace System{
    template < class TYPE, class ARG_TYPE = TYPE >
    class CArray {
    public:
        // Construction
        CArray();

        // Attributes
        inline int GetSize() const { return (int)array.size(); };

        inline int GetUpperBound() const { return (int)(array.size() - 1); };

        inline void SetSize(int nNewSize, int nGrowBy = -1) {
            if (nNewSize != 0) array.resize(nNewSize);
            if (nGrowBy != -1) array.reserve(nNewSize + nGrowBy);
        };

        // Operations
        // Clean up
        inline void FreeExtra() {
            array.reserve(array.size());
        };

        inline void RemoveAll() {
            array.clear();
        };

        // Accessing elements
        inline TYPE GetAt(int nIndex) const {
            _ASSERT(nIndex < (int)array.size());
            return array[nIndex];
        };

        inline void SetAt(int nIndex, ARG_TYPE newElement) {
            _ASSERT(nIndex >= 0 && nIndex < (int)array.size());
            array[nIndex] = newElement;
        };

        inline TYPE & ElementAt(int nIndex) {
            _ASSERT(nIndex >= 0 && (nIndex < (int)array.size()));
            return array[nIndex];
        };

        // Direct Access to the element data (may return NULL)
        inline const TYPE * GetData() const {
            return & (* array.begin());
        };

        inline TYPE * GetData() {
            return & (* array.begin());
        };

        // Potentially growing the array
        inline void SetAtGrow(int nIndex, ARG_TYPE newElement) {
            _ASSERT(nIndex >= 0);
            if (nIndex >= (int)array.size()) array.push_back(newElement);
            else array[nIndex] = newElement;
        };

        inline int Add(ARG_TYPE newElement) {
            array.push_back(newElement);
            return (int)(array.size() - 1);
        };

        inline int Append(const CArray & src) {
            array.insert(array.end(), src.array.begin(), src.array.end());
            return (int)array.size();
        };

        inline void Copy(const CArray & src) {
            array.clear();
            array.insert(array.end(), src.array.begin(), src.array.end());
        };

        // overloaded operator helpers
        inline TYPE operator[] (int nIndex) const {
            _ASSERT(nIndex >= 0 && nIndex < (int)array.size());
            return array[nIndex];
        };

        inline TYPE & operator[] (int nIndex) {
            _ASSERT(nIndex >= 0 && nIndex < (int)array.size());
            return array[nIndex];
        };

        // Operations that move elements around
        inline void InsertAt(int nIndex, ARG_TYPE newElement, int nCount = 1) {
            _ASSERT(nIndex >= 0);
            if (nIndex > (int)array.size()) array.insert(array.end(), nCount, newElement);
            else {
                array.insert(array.begin() + nIndex, nCount, newElement);
            }
        };

        inline void RemoveAt(int nIndex, int nCount = 1) {
            _ASSERT(nIndex >= 0 && nIndex < (int)array.size() && nIndex + nCount <= (int)array.size());

            int i;
            std::vector < TYPE >::iterator pos = array.begin();
            for (i = 0; i < nIndex; i++, pos++);

            if (nCount == 1) array.erase(array.begin() + nIndex);
            else {
                array.erase(array.begin() + nIndex, array.begin() + nIndex + nCount);
            }
        };

        inline void InsertAt(int nStartIndex, CArray * pNewArray) {
            _ASSERT(nStartIndex >= 0);
            if (nStartIndex >= (int)array.size()) array.insert(array.end(), pNewArray->array.begin(), pNewArray->array.end());
            else {
                //int i;
                //std::vector<TYPE>::iterator pos = array.begin();
                //for(i = 0 ; i < nIndex ; i++,pos++) ;
                array.insert(array.begin() + nStartIndex, pNewArray->array.begin(), pNewArray->array.end());
            }
        };

        // Implementation
    protected:
        std::vector < TYPE > array;
    public:
        ~CArray();
    };

}


namespace System{
    template < class TYPE, class ARG_TYPE >
    class CList {
    public:
        // Construction
        CList();

        // Attributes (head and tail)
        // count of elements
        inline int GetCount() { return (int)list.size(); };

        inline bool IsEmpty() { return list.size() == 0; };

        // peek at head or tail
        inline TYPE & GetHead() {
            ASSERT(list.size() != 0);
            return * list.begin();
        };

        inline TYPE & GetTail() {
            ASSERT(list.size() != 0);
            return * (--list.end());
        };

        // Operations
        // get head or tail (and remove it) - don't call on empty list !
        inline TYPE RemoveHead() {
            TYPE t = * list.begin();
            list.pop_front();
            return t;
        };

        inline TYPE RemoveTail() {
            TYPE t = * list.end();
            list.pop_back();
            return t;
        };

        // add before head or after tail
        inline POSITION AddHead(ARG_TYPE newElement) {
            list.push_front(newElement);
            return (POSITION)list.begin()._Mynode();
        };

        inline POSITION AddTail(ARG_TYPE newElement) {
            list.push_back(newElement);
            return (POSITION)(--list.end())._Mynode();
        };

        // add another list of elements before head or after tail
        inline void AddHead(CList * pNewList) {
            _ASSERT(pNewList != NULL);

            // add a list of same elements to head (maintain order)
            POSITION pos = --pNewList->list.end();
            POSITION posBegin = pNewList->list.begin();
            while (pos != posBegin) list.push_front(* pos--);
            list.push_front(* pos);
        };

        inline void AddTail(CList * pNewList) {
            _ASSERT(pNewList != NULL);

            // add a list of same elements
            POSITION pos = pNewList->list.begin();
            POSITION posend = pNewList->list.end();
            while (pos != posend) list.push_back(* pos++);
        };

        // remove all elements
        inline void RemoveAll() { list.clear(); };

        // iteration
        inline POSITION GetHeadPosition() {
            return (POSITION)list.begin()._Mynode();
        };

        inline POSITION GetHeadPosition() const { return (POSITION)list.begin()._Mynode(); };

        inline POSITION GetTailPosition() {
            return (POSITION)(--list.end())._Mynode();
        };

        inline POSITION GetTailPosition() const {
            return (POSITION)(--list.end())._Mynode();
        };

        inline TYPE & GetNext(POSITION & rPosition) // return *Position++
        {
            _ASSERT(rPosition != NULL);
            std::list < TYPE >::iterator it((std::list < TYPE >::_Nodeptr) rPosition), it2;
            it2 = it++;
            if (it == list.end()) rPosition = NULL;
            else rPosition = (POSITION)it._Mynode();
            return * it2;
        };

        inline TYPE GetNext(POSITION & rPosition) const // return *Position++
        {
            _ASSERT(rPosition != NULL);
            std::list < TYPE >::const_iterator it((std::list < TYPE >::_Nodeptr) rPosition), it2;
            it2 = it++;
            if (it == list.end()) rPosition = NULL;
            else rPosition = (POSITION)it._Mynode();
            return * it2;
        };

        inline TYPE & GetPrev(POSITION & rPosition) // return *Position--
        {
            _ASSERT(rPosition != NULL);
            std::list < TYPE >::iterator it((_Nodeptr)rPosition), it2;
            it2 = it--;
            if (it == list.begin()) rPosition = NULL;
            else rPosition = (POSITION)it._Mynode();
            return * it2;
        }

        // getting/modifying an element at a given position
        inline TYPE & GetAt(POSITION position) {
            return * std::list < TYPE >::iterator((std::list < TYPE >::_Nodeptr) position);
        };

        inline void SetAt(POSITION pos, ARG_TYPE newElement) {
            * std::list < TYPE >::iterator((std::list < TYPE >::_Nodeptr) position) = newElement;
        };

        inline void RemoveAt(POSITION position) {
            std::list < TYPE >::iterator pos((std::list < TYPE >::_Nodeptr) position);
            list.erase(pos);
        };

        // inserting before or after a given position
        inline POSITION InsertBefore(POSITION position, ARG_TYPE newElement) {
            std::list < TYPE >::iterator pos((std::list < TYPE >::_Nodeptr) position);
            if (pos == list.begin()) return AddHead(newElement); // insert before nothing -> head of the list

            // Insert it before position
            return (POSITION)list.insert(pos, newElement)._Mynode();
        };

        inline POSITION InsertAfter(POSITION position, ARG_TYPE newElement) {
            std::list < TYPE >::iterator pos((std::list < TYPE >::_Nodeptr) position);

            if (pos == list.end()) return AddTail(newElement); // insert after nothing -> tail of the list
            pos++;

            if (pos == list.begin()) return AddHead(newElement); // insert before nothing -> head of the list

            // Insert it before position
            return (POSITION)list.insert(pos, newElement)._Mynode();
        };

        // helper functions (note: O(n) speed)
        inline POSITION Find(ARG_TYPE searchValue, POSITION startAfter) {
            std::list < TYPE >::iterator pos, posStart;
            if (startAfter == NULL) posStart = list.begin();
            else posStart = std::list < TYPE >::iterator((std::list < TYPE >::_Nodeptr) position);
            for (pos = posStart; pos != list.end(); pos++) {
                if (* pos == searchValue) {
                    pos++;
                    return (POSITION)pos._Mynode();
                }
            }
            return NULL;
        };

        // defaults to starting at the HEAD, return NULL if not found
        inline POSITION FindIndex(int nIndex) {
            std::list < TYPE >::iterator pos = list.begin();
            while (nIndex--) {
                pos++;
            }
            return (POSITION)pos._Mynode();
        };

        // get the 'nIndex'th element (may return NULL)

        // Implementation
    protected:
        std::list < TYPE > list;
    public:
        ~CList();
    };

}


namespace System{
    template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE >
    class CMap {
    public:
        // Construction
        CMap();

        // Attributes
        // number of elements
        int GetCount() const { return map.size(); };

        bool IsEmpty() const { return map.empty(); };

        // Lookup
        bool Lookup(ARG_KEY key, VALUE & rValue) const {
            std::map < KEY, VALUE >::const_iterator item = map.find(key);
            if (item._Mynode() == map.end()._Mynode()) return FALSE;
            rValue = (* item).second;
            return TRUE;
        };

        // Operations
        // Lookup and add if not there
        VALUE & operator[] (ARG_KEY key) { return map[key]; };

        // add a new (key, value) pair
        void SetAt(ARG_KEY key, ARG_VALUE newValue) { map.insert(std::map < KEY, VALUE >::value_type(key, newValue)); };

        // removing existing (key, ?) pair
        bool RemoveKey(ARG_KEY key) {
            map.erase(key);
            return true;
        };

        void RemoveAll() { map.clear(); };

        // iterating all (key, value) pairs
        POSITION GetStartPosition() const { return (POSITION)map.begin()._Mynode(); };

        void GetNextAssoc(POSITION & rNextPosition, KEY & rKey, VALUE & rValue) const {
			std::map < KEY, VALUE >::iterator it((std::map < KEY, VALUE >::_Nodeptr) rNextPosition);
            rKey = (* it).first;
            rValue = (* it).second;
            it++;
            if (it._Mynode() == map.end()._Mynode()) rNextPosition = NULL;
            else rNextPosition = (POSITION)it._Mynode();
        };

    protected:
        std::map < KEY, VALUE > map;
    public:
        ~CMap();
    };

}


/////////////////////////////////////////////////////////////////////
// CArray
/////////////////////////////////////////////////////////////////////

template < class TYPE, class ARG_TYPE >
System::CArray<TYPE, ARG_TYPE>::CArray() {
}

template < class TYPE, class ARG_TYPE >
System::CArray<TYPE, ARG_TYPE>::~CArray() {
    array.clear();
}

/////////////////////////////////////////////////////////////////////
// CList
/////////////////////////////////////////////////////////////////////



template < class TYPE, class ARG_TYPE >
System::CList<TYPE, ARG_TYPE>::CList() {
}


template < class TYPE, class ARG_TYPE >
System::CList<TYPE, ARG_TYPE>::~CList() {
    RemoveAll();
    ASSERT(list.size() == 0);
}

////////////////////////////////////////////////////////////////
//
// CMap
//
////////////////////////////////////////////////////////////////

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE >
System::CMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::CMap() {
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE >
System::CMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::~CMap() {
    map.clear();
}

#endif//_ALM_H_