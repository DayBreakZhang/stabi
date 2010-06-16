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
namespace util
{
namespace stabi
{
namespace adapter
{

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::stlVector2stabiVectorAdapter() throw () : m_pVectorImpl(NULL)
{
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::~stlVector2stabiVectorAdapter() throw ()
{
    m_pVectorImpl->~vectorImplType();
    AllocatorType::rebind<vectorImplType>::other().deallocate(m_pVectorImpl, 1);
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Initialize() throw ()
{
    if (m_pVectorImpl != NULL)
    {
        m_pVectorImpl->~vectorImplType();
        AllocatorType::rebind<vectorImplType>::other().deallocate(m_pVectorImpl, 1);
    }

    m_pVectorImpl = AllocatorType::rebind<vectorImplType>::other().allocate(1);
    if (m_pVectorImpl == NULL)
    {
        return false;
    }
    ::new(m_pVectorImpl) vectorImplType;
    return true;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
void stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Attach(vectorImplType *pMapImpl) throw ()
{
    if (m_pVectorImpl != NULL)
    {
        m_pVectorImpl->~vectorImplType();
        AllocatorType::rebind<vectorImplType>::other().deallocate(m_pVectorImpl, 1);
    }
    m_pVectorImpl = pMapImpl;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
typename stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::vectorImplType *stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Detach() throw ()
{
    vectorImplType *pMapImpl = m_pVectorImpl;
    m_pVectorImpl = NULL;
    return pMapImpl;
}

// Collection
template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Add(const DataType &inData) throw ()
{
	assert(m_pVectorImpl != NULL);
	if (m_pVectorImpl == NULL)
	{
		return false;
	}

	try
	{
		m_pVectorImpl->push_back(inData);
	}
	catch (std::bad_alloc *)
	{
		return false;
	}
	return true;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Erase(const DataType &data) throw ()
{
	assert(m_pVectorImpl != NULL);
	if (m_pVectorImpl == NULL)
	{
		return false;
	}

	for (vectorImplType::iterator it= m_pVectorImpl->begin() ; it != m_pVectorImpl->end(); ++it)
	{
		if (data == *it)
		{
			m_pVectorImpl->erase(it);
			return true;
		}
	}
	return false;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Contains(const DataType &data) const throw ()
{
	assert(m_pVectorImpl != NULL);
	if (m_pVectorImpl == NULL)
	{
		return false;
	}

	for (vectorImplType::iterator it= m_pVectorImpl->begin() ; it != m_pVectorImpl->end(); ++it)
	{
		if (data == *it)
		{
			return true;
		}
	}
	return false;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
size_t stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Size() const throw ()
{
	assert(m_pVectorImpl != NULL);
	if (m_pVectorImpl == NULL)
	{
		return 0;
	}

	return m_pVectorImpl->size();
}


template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
void stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Clear() throw ()
{
	assert(m_pVectorImpl != NULL);
	if (m_pVectorImpl == NULL)
	{
		return;
	}

	return m_pVectorImpl->clear();
}
// KeyAccessible
template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Put(const KeyType &key, const DataType &data) throw ()
{
    assert(m_pVectorImpl != NULL);
	assert(key < m_pVectorImpl->size());
    if (m_pVectorImpl == NULL || key >= m_pVectorImpl->size())
    {
        return false;
    }

	try
    {
        (*m_pVectorImpl)[key] = data;	    // note: data copy should not throw any unexpected types
    }
    catch (std::bad_alloc *)
    {
    	return false;
    }
    return true;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::EraseKey(const KeyType &key) throw ()
{
	assert(m_pVectorImpl != NULL);
	assert(key < m_pVectorImpl->size());
	if (m_pVectorImpl == NULL || key >= m_pVectorImpl->size())
	{
		return false;
	}

	m_pVectorImpl->erase(m_pVectorImpl->begin() + key);
    return true;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Remove(const KeyType &key, DataType &outData) throw ()
{
	assert(m_pVectorImpl != NULL);
	assert(key < m_pVectorImpl->size());
	if (m_pVectorImpl == NULL || key >= m_pVectorImpl->size())
	{
		return false;
	}

    try
    {
        outData = (*m_pVectorImpl)[key];
    }
    catch (std::bad_alloc*)
    {
        return false;    	
    }

	m_pVectorImpl->erase(m_pVectorImpl->begin() + key);
	return true;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
DataType * stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Get(const KeyType &key) throw ()
{
	return const_cast<DataType *>(const_cast<const stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType> *>(this)->Get(key));
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
const DataType * stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Get(const KeyType &key) const throw ()
{
	assert(m_pVectorImpl != NULL);
	assert(key < m_pVectorImpl->size());
	if (m_pVectorImpl == NULL || key >= m_pVectorImpl->size())
	{
		return false;
	}

	return &(*m_pVectorImpl)[key];
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::ContainsKey(const KeyType &key) const throw ()
{
	assert(m_pVectorImpl != NULL);
	assert(key < m_pVectorImpl->size());
	if (m_pVectorImpl == NULL || key >= m_pVectorImpl->size())
	{
		return false;
	}
	return true;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
const DataType * stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::GetIterator() const throw ()
{
	assert(m_pVectorImpl != NULL);
	assert(key < m_pVectorImpl->size());
	if (m_pVectorImpl == NULL)
	{
		return NULL;
	}

	return m_pVectorImpl->begin();
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool stlVector2stabiVectorAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::GetReverseIterator() const throw ()
{
	assert(m_pVectorImpl != NULL);
	assert(key < m_pVectorImpl->size());
	if (m_pVectorImpl == NULL)
	{
		return NULL;
	}
	return --m_pVectorImpl->end();
}

}   // namespace adapter
}   // namespace stabi
}   // namespace util