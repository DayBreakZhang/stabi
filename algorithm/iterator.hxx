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
#include <iterator>
namespace algorithm
{
namespace 
{

template<
		class iteratorType,
		class diffType
		> 
inline diffType _checkedAdvance(iteratorType& itr, diffType offset, const iteratorType &, const iteratorType &itrEnd, std::forward_iterator_tag)
{
	if (itr == itrEnd)
	{
		return 0;
	}

	diffType i;
	for (i = 0; i < offset; ++i)
	{
		iteratorType itrNext = itr+1;
		if (itrNext == itrEnd)
		{
			break;
		}
		++itr;
	}
	return i;
}

template<
		class iteratorType,
		class diffType
		> 
inline diffType _checkedAdvance(iteratorType& itr, diffType offset, const iteratorType &itrBegin, const iteratorType &itrEnd, std::bidirectional_iterator_tag)
{
	if (offset > 0 && itr == itrEnd)
	{
		return 0;
	}

	diffType i = 0;
	for (; i < offset; ++i)
	{
		++itr;

		// if we went too far, then take a step back
		if (itr == itrEnd)
		{
			--itr;
			break;
		}
	}
	for (; i > offset; --i)
	{	
		if (itr == itrBegin)
		{
			break;
		}
		--itr;
	}
	return i;
}

template<
		class iteratorType,
		class diffType
		>
inline diffType _checkedAdvance(iteratorType& itr, diffType offset, const iteratorType &itrBegin, const iteratorType &itrEnd, std::random_access_iterator_tag)
{
	diffType checkedOffset;
	if (offset > 0)
	{
		if (itr == itrEnd)
		{
			return 0;
		}
		checkedOffset = min(offset, itrEnd -1 - itr);
	}
	else if (offset < 0)
	{
		checkedOffset = max(offset, itrBegin - itr);
	}
	else
	{
		return 0;
	}
	itr += checkedOffset;
	return checkedOffset;
}
}	// namespace

template<
		class iteratorType,
		class diffType
		> 
 inline diffType checkedAdvance(iteratorType& itr, diffType offset, const iteratorType &itrBegin, const iteratorType &itrEnd) throw ()
{	
	iteratorType::iterator_category catTypeDummyParam;
	return _checkedAdvance(itr, offset, itrBegin, itrEnd, catTypeDummyParam);
}

}	// namespace algorithm

