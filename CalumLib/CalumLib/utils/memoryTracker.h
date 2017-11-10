#ifndef MEMORY_TRACKER_H
#define MEMORY_TRACKER_H

#include <iostream>
#include <map>

struct PointerRecord
{
	PointerRecord(int theNum, std::size_t theSize)
	{
		num = theNum;
		size = theSize;
	}
	int num;
	std::size_t size;
};

class MemoryTracker
{
	public:
		MemoryTracker();
		~MemoryTracker();

		void add(void* ptr, std::size_t size);
		void remove(void* ptr);

		void reportPointers(std::ostream& stream);
	private:
		MemoryTracker(const MemoryTracker&);
		MemoryTracker& operator=(const MemoryTracker&);

		std::map<void*, PointerRecord> mPointers;

		static int msPointerNum;
};

extern MemoryTracker gMemoryTracker;

#endif