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

#ifndef __UTIL_STABI_INTERFACE_MAP_H
#define __UTIL_STABI_INTERFACE_MAP_H

#include "util/stabi/interface/collection.h"
#include "util/stabi/interface/keyAccessible.h"
#include "util/stabi/interface/iterable.h"

namespace util
{
namespace stabi
{
namespace interface
{

template<
        typename _DataType
        >
class Vector : 
	public Collection<_DataType>, 
	public KeyAccessible<size_t, _DataType>,
	public Iterable<_DataType>
{
public:
    typedef _DataType DataType;
};

}   // namespace interface
}   // namespace stabi
}   // namespace util

#endif // __UTIL_STABI_INTERFACE_MAP_H
