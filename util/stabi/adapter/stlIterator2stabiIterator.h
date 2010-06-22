// Copyright (c) 2010 Yu-Li Lin
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef __UTIL_STABI_ADAPTER_STL_ITERATOR_2_STABI_ITERATOR_H
#define __UTIL_STABI_ADAPTER_STL_ITERATOR_2_STABI_ITERATOR_H

#include "util/stabi/interface/iterator.h"

namespace util
{
namespace stabi
{
namespace adapter
{

template<
        typename CollectionType
        >
class stlIterator2stabiIterator : public interface::Iterator<typename CollectionType::value_type>
{
public:
	typedef typename CollectionType::iterator iteratorImplType;
	typedef typename CollectionType::value_type DataType;
public:
    stlIterator2stabiIterator(iteratorImplType &iteratorImpl, CollectionType *pCollectionImpl) throw ();
    virtual ~stlIterator2stabiIterator() throw ();

public:	// Destructible functions
	virtual void Destroy() throw ();

public: // Iterator functions
	virtual bool HasNext() const throw ();
	virtual bool HasPrevious() const throw();

	virtual DataType *Get() throw();
	virtual const DataType *Get() const throw();

	virtual ptrdiff_t Move(ptrdiff_t offSet) throw();
	virtual bool Erase() throw();

private:
    iteratorImplType m_iteratorImpl;
	CollectionType *m_pCollectionImpl;
};

}   // namespace adapter
}   // namespace stabi
}   // namespace util

// implementation file
#include "stlIterator2stabiIterator.hxx"

#endif // __UTIL_STABI_ADAPTER_STL_ITERATOR_2_STABI_ITERATOR_H
