#include "memoryTracker.h"

#include <assert.h>

int MemoryTracker::msPointerNum = 0;
MemoryTracker gMemoryTracker;

MemoryTracker::MemoryTracker()
{
}

MemoryTracker::~MemoryTracker()
{
}

void MemoryTracker::add(void* ptr, size_t size)
{
	std::map<void*, PointerRecord>::iterator iter = mPointers.find(ptr);

	if (iter != mPointers.end())
	{
		std::cout << "TRIED TO INIT POINTER, BUT IT ALREADY EXISTS!!!!!\n";
		assert(false);
	}
	else
	{
		PointerRecord record(msPointerNum, size);
		std::pair<void*, PointerRecord> pair(ptr, record);
		mPointers.insert(pair);
		msPointerNum++;
	}
}

void MemoryTracker::remove(void* ptr)
{
	std::map<void*, PointerRecord>::iterator iter = mPointers.find(ptr);
	if (iter == mPointers.end())
	{
		std::cout << "TRIED TO DELETE POINTER, BUT NO RECORD EXISTS!!!!\n";
		assert(false);
	}
	else
	{
		mPointers.erase(ptr);
	}
}

void MemoryTracker::reportPointers(std::ostream& stream)
{
	stream << "Current memory allocations:\n";

	std::map<void*, PointerRecord>::iterator iter;
	for (iter = mPointers.begin(); iter != mPointers.end(); iter++)
	{
		stream << "address:" << iter->first << " size:" << iter->second.size << " num:" << iter->second.num << '\n';
	}
}