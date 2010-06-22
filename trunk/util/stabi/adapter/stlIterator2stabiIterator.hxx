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

#include <assert.h>
#include "algorithm/iterator.h"

namespace util
{
namespace stabi
{
namespace adapter
{

template<typename CollectionType>
stlIterator2stabiIterator<CollectionType>::stlIterator2stabiIterator(iteratorImplType &iteratorImpl, CollectionType *pCollectionImpl) throw () :
m_iteratorImpl(iteratorImpl),
m_pCollectionImpl(pCollectionImpl)
{
}

template<typename CollectionType>
stlIterator2stabiIterator<CollectionType>::~stlIterator2stabiIterator() throw ()
{
}

template<typename CollectionType>
void stlIterator2stabiIterator<CollectionType>::Destroy() throw ()
{
    delete this;
}

// Collection
template<typename CollectionType>
bool stlIterator2stabiIterator<CollectionType>::HasNext() const throw ()
{
	assert(m_pCollectionImpl != NULL);
	if (m_pCollectionImpl == NULL)
	{
		return false;
	}

	if (m_iteratorImpl ==  m_pCollectionImpl->end())
	{
		return false;
	}

	iteratorImplType iteratorTest = m_iteratorImpl;
	return ++iteratorTest != m_pCollectionImpl->end();
}

template<typename CollectionType>
bool stlIterator2stabiIterator<CollectionType>::HasPrevious() const throw ()
{
	assert(m_pCollectionImpl != NULL);
	if (m_pCollectionImpl == NULL)
	{
		return false;
	}

	return m_iteratorImpl != m_pCollectionImpl->begin();
}

template<typename CollectionType>
typename stlIterator2stabiIterator<CollectionType>::DataType * stlIterator2stabiIterator<CollectionType>::Get() throw ()
{
	return const_cast<DataType *>(const_cast<const stlIterator2stabiIterator<CollectionType> *>(this)->Get());
}

template<typename CollectionType>
const typename stlIterator2stabiIterator<CollectionType>::DataType * stlIterator2stabiIterator<CollectionType>::Get() const throw ()
{
	assert(m_pCollectionImpl != NULL);
	if (m_pCollectionImpl == NULL)
	{
		return NULL;
	}

	if (m_iteratorImpl == m_pCollectionImpl->end())
	{
		return NULL;
	}
	return &(*m_iteratorImpl);
}


template<typename CollectionType>
ptrdiff_t stlIterator2stabiIterator<CollectionType>::Move(ptrdiff_t offSet) throw ()
{
	assert(m_pCollectionImpl != NULL);
	if (m_pCollectionImpl == NULL)
	{
		return NULL;
	}

	return algorithm::checkedAdvance(m_iteratorImpl, offSet, m_pCollectionImpl->begin(), m_pCollectionImpl->end());
}

template<typename CollectionType>
bool stlIterator2stabiIterator<CollectionType>::Erase() throw ()
{
    assert(m_pCollectionImpl != NULL);
    if (m_pCollectionImpl == NULL)
    {
        return false;
    }

	if (m_iteratorImpl == m_pCollectionImpl->end())
	{
		return false;
	}
	m_iteratorImpl = m_pCollectionImpl->erase(m_iteratorImpl);
    return true;
}

}   // namespace adapter
}   // namespace stabi
}   // namespace util