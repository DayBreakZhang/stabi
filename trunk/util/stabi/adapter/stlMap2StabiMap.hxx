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
STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::STLMap2StabiMapAdapter() throw () : m_pMapImpl(NULL)
{
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::~STLMap2StabiMapAdapter() throw ()
{
    m_pMapImpl->~mapImplType();
    AllocatorType::rebind<mapImplType>::other().deallocate(m_pMapImpl, 1);
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Initialize() throw ()
{
    if (m_pMapImpl != NULL)
    {
        m_pMapImpl->~mapImplType();
        AllocatorType::rebind<mapImplType>::other().deallocate(m_pMapImpl, 1);
    }

    m_pMapImpl = AllocatorType::rebind<mapImplType>::other().allocate(1);
    if (m_pMapImpl == NULL)
    {
        return false;
    }
    ::new(m_pMapImpl) mapImplType;
    return true;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
void STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Attach(mapImplType *pMapImpl) throw ()
{
    if (m_pMapImpl != NULL)
    {
        m_pMapImpl->~mapImplType();
        AllocatorType::rebind<mapImplType>::other().deallocate(m_pMapImpl, 1);
    }
    m_pMapImpl = pMapImpl;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
typename STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::mapImplType *STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Detach() throw ()
{
    mapImplType *pMapImpl = m_pMapImpl;
    m_pMapImpl = NULL;
    return pMapImpl;
}

// Collection
template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Add(const DataType &inData) const throw ()
{
	assert(m_pMapImpl != NULL);
	return false;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Erase(const DataType &data) const throw ()
{
	assert(m_pMapImpl != NULL);
	if (m_pMapImpl == NULL)
	{
		return false;
	}

	for (mapImplType::iterator it= m_pMapImpl->begin() ; it != m_pMapImpl->end(); ++it)
	{
		if (data == it->second)
		{
			m_pMapImpl->Erase(it);
			return true;
		}
	}
	return false;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Contains(const DataType &data) const throw ()
{
	assert(m_pMapImpl != NULL);
	if (m_pMapImpl == NULL)
	{
		return false;
	}

	for (mapImplType::iterator it= m_pMapImpl->begin() ; it != m_pMapImpl->end(); ++it)
	{
		if (data == it->second)
		{
			return true;
		}
	}
	return false;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
size_t STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Size() const throw ()
{
	assert(m_pMapImpl != NULL);
	if (m_pMapImpl == NULL)
	{
		return 0;
	}

	return m_pMapImpl->size();
}


template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
void STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Clear() throw ()
{
	assert(m_pMapImpl != NULL);
	if (m_pMapImpl == NULL)
	{
		return;
	}

	return m_pMapImpl->clear();
}
// KeyAccessable
template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Put(const KeyType &key, const DataType &data) throw ()
{
    assert(m_pMapImpl != NULL);
    if (m_pMapImpl == NULL)
    {
        return false;
    }

    mapReturnType retVal;

    // note: data copy should not throw any unexpected types
    try
    {
        retVal = m_pMapImpl->insert(valueType(key, data));

        // if key already existed, then replace it
        if (!retVal.second)
        {
            retVal.first->second = data;
        }
    }
    catch (std::bad_alloc*)
    {
    	return false;
    }
    assert(retVal.second);
    return retVal.second;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
void STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Erase(const KeyType &key) throw ()
{
    assert(m_pMapImpl != NULL);
    if (m_pMapImpl == NULL)
    {
        return;
    }

    mapImplType::iterator retVal;
    retVal = m_pMapImpl->find(key);
    if (retVal == m_pMapImpl->end())
    {
        return;
    }

    m_pMapImpl->erase(retVal);
    return;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Remove(const KeyType &key, DataType &outData) throw ()
{
    assert(m_pMapImpl != NULL);
    if (m_pMapImpl == NULL)
    {
        return false;
    }

    mapImplType::iterator retVal;
    retVal = m_pMapImpl->find(key);
    if (retVal == m_pMapImpl->end())
    {
        return false;
    }

    try
    {
        outData = retVal->second; 
    }
    catch (std::bad_alloc*)
    {
        return false;    	
    }

    m_pMapImpl->erase(retVal);
    return true;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
DataType * STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Get(const KeyType &key) throw ()
{
	return const_cast<DataType *>(const_cast<const STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType> *>(this)->Get(key));
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
const DataType * STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::Get(const KeyType &key) const throw ()
{
	assert(m_pMapImpl != NULL);
	if (m_pMapImpl == NULL)
	{
		return NULL;
	}

	mapImplType::iterator retVal;
	retVal = m_pMapImpl->find(key);
	if (retVal == m_pMapImpl->end())
	{
		return NULL;
	}

	return &retVal->second;
}

template<typename KeyType, typename DataType, typename CompareFunctor, typename AllocatorType>
bool STLMap2StabiMapAdapter<KeyType, DataType, CompareFunctor, AllocatorType>::ContainsKey(const KeyType &key) const throw ()
{
    assert(m_pMapImpl != NULL);
    if (m_pMapImpl == NULL)
    {
        return false;
    }

    mapImplType::iterator retVal;
    retVal = m_pMapImpl->find(key);
    return (retVal != m_pMapImpl->end());
}

}   // namespace adapter
}   // namespace stabi
}   // namespace util