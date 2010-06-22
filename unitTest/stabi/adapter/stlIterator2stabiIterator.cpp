#include <iostream>
#include "util/stabi/adapter/stlIterator2stabiIterator.h"
#include <vector>
#include <list>
#include <assert.h>

template <class collectionType> 
void forwardTest()
{
	collectionType stdCollection;

	for (int i = 0; i < 10; ++i)
	{
		stdCollection.push_back(i);
	}

	util::stabi::adapter::stlIterator2stabiIterator<collectionType> siBegin(stdCollection.begin(), &stdCollection);
	assert(!siBegin.HasPrevious());
	assert(siBegin.Move(-1) == 0);
	assert(siBegin.Move(0) == 0);
	for (int i = 0; i < 10; ++i)
	{
		int *p = siBegin.Get();
		assert(p != NULL);
		assert(*p == i);
		if (i == 0)
		{
			assert(!siBegin.HasPrevious());
		}
		else
		{
			assert(siBegin.HasPrevious());
		}

		if (i == 9)
		{
			assert(!siBegin.HasNext());
			assert(siBegin.Move(1) == 0);
		}
		else
		{
			assert(siBegin.HasNext());
			assert(siBegin.Move(1) == 1);
		}

	}

	util::stabi::adapter::stlIterator2stabiIterator<collectionType> siBegin2(stdCollection.begin(), &stdCollection);
	assert(siBegin2.Move(20) == 9);
}

template <class collectionType>
void reverseTest()
{
	collectionType stdCollection;

	for (int i = 0; i < 10; ++i)
	{
		stdCollection.push_back(i);
	}

	util::stabi::adapter::stlIterator2stabiIterator<collectionType> siEnd(stdCollection.end(), &stdCollection);
	assert(siEnd.Get() == NULL);
	assert(!siEnd.HasNext());
	assert(siEnd.Move(1) == 0);
	assert(siEnd.Move(-1) == -1);

	assert(!siEnd.HasNext());
	assert(siEnd.Move(1) == 0);
	for (int i = 9; i > 0; --i)
	{
		assert(siEnd.Get() != NULL);
		assert(*siEnd.Get() == i);

		assert(siEnd.HasPrevious());
		if (i == 9)
		{
			assert(!siEnd.HasNext());
		}
		else
		{
			assert(siEnd.HasNext());
		}
		assert(siEnd.Move(-1) == -1);
	}
	assert(siEnd.Get() != NULL);
	assert(*siEnd.Get() == 0);
	assert(!siEnd.HasPrevious());
	assert(siEnd.Move(-1) == 0);

	util::stabi::adapter::stlIterator2stabiIterator<collectionType> siEnd2(--stdCollection.end(), &stdCollection);
	assert(siEnd2.Move(-20) == -9);
}
using namespace std;
int main()
{
	// random access iterator
	forwardTest<std::vector<int> >();
	reverseTest<std::vector<int> >();
	
	// bidirectional iterator
	forwardTest<std::list<int> >();
	reverseTest<std::list<int> >();

	// forward iterator
	// skipping this test since there's no stl::container that uses forward iterators

	return 0;
}