#ifndef TRACKABLE_H
#define TRACKABLE_H

#include <cstddef>

class Trackable
{
	public:
		void* operator new(std::size_t size);
		void operator delete(void* ptr);
		void* operator new[](std::size_t size);
		void operator delete[](void* ptr);
};

#endif