#include <iostream>
#include "util/stabi/adapter/stlMap2stabiMap.h"
#include <assert.h>

using namespace std;
int main()
{
	util::stabi::adapter::stlMap2stabiMapAdapter<int, int> stabiMap;
	assert(stabiMap.Initialize());
	assert(!stabiMap.Add(1));
	assert(stabiMap.Size() == 0);
	assert(!stabiMap.Contains(1));
	assert(!stabiMap.ContainsKey(1));
	assert(stabiMap.Put(1,10));
	assert(stabiMap.Put(2,20));
	assert(stabiMap.Put(3,30));
	assert(stabiMap.Size() == 3);
	assert(stabiMap.Contains(20));
	assert(stabiMap.ContainsKey(3));
	assert(stabiMap.EraseKey(3));
	assert(stabiMap.Erase(20));
	int data;
	assert(stabiMap.Remove(1, data));
	assert(stabiMap.Size() == 0);
	for (int i = 0; i < 10; ++i)
	{
		assert(stabiMap.Put(i, i));
	}

	int *pData;
	assert((pData = stabiMap.Get(1)) != NULL);
	assert(*pData == 1);
	assert(stabiMap.Put(1, 2));
	assert((pData = stabiMap.Get(1)) != NULL);
	assert(*pData == 2);
	stabiMap.Clear();
	assert(stabiMap.Size() == 0);

	return 0;
}