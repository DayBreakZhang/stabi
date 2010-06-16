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

#ifndef __UTIL_STABI_ADAPTER_STL_VECTOR_2_STABI_VECTOR_H
#define __UTIL_STABI_ADAPTER_STL_VECTOR_2_STABI_VECTOR_H

#include "util/stabi/interface/vector.h"
#include <vector>

namespace util
{
namespace stabi
{
namespace adapter
{

template<
        typename DataType, 
        typename AllocatorType = ::std::allocator<DataType> 
        >
class stlVector2stabiVectorAdapter : public interface::Vector<DataType>
{
public:
	typedef ::std::vector<DataType, AllocatorType> vectorImplType;
public:
    stlVector2stabiVectorAdapter() throw ();
    virtual ~stlVector2stabiVectorAdapter() throw ();

    // creates an instance of the vectorImplType with the AllocatorType
    bool Initialize() throw ();
    void Attach(vectorImplType *pMapImpl) throw ();
    vectorImplType *Detach() throw ();

public:	// Collection
	// modifier
	virtual bool Add(const DataType &inData) throw ();
	virtual bool Erase(const DataType &inData) throw ();

	// operation
	virtual bool Contains(const DataType &inData) const throw ();

	// capcacity
	virtual size_t Size() const throw ();

	// bulk
	virtual void Clear() throw ();

public: // KeyAccessible functions
    // modifier
    bool Put(const KeyType &key, const DataType &data) throw ();
    bool EraseKey(const KeyType &key) throw ();
    bool Remove(const KeyType &key, DataType &outData) throw ();

    // operation
	virtual DataType *Get(const KeyType &key) throw ();
	virtual const DataType *Get(const KeyType &key) const throw ();
	virtual bool ContainsKey(const KeyType &key) const throw ();

public: // Iterable functions
	virtual IteratorType GetIterator() const throw ();
	virtual IteratorType GetReverseIterator() const throw ();

private:
    vectorImplType *m_pVectorImpl;
};

}   // namespace adapter
}   // namespace stabi
}   // namespace util

// implementation file
#include "stlVector2stabiVector.hxx"

#endif // __UTIL_STABI_ADAPTER_STL_VECTOR_2_STABI_VECTOR_H
