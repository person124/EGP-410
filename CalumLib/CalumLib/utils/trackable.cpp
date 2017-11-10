#include "trackable.h"

#include "utils/memoryTracker.h"

#include <stdlib.h>

void* Trackable::operator new(std::size_t size)
{
	void* ptr = malloc(size);
	gMemoryTracker.add(ptr, size);
	return ptr;
}

void Trackable::operator delete(void* ptr)
{
	gMemoryTracker.remove(ptr);
	free(ptr);
}

void* Trackable::operator new[](std::size_t size)
{
	void* ptr = malloc(size);
	gMemoryTracker.add(ptr, size);
	return ptr;
}

void Trackable::operator delete[](void* ptr)
{
	gMemoryTracker.remove(ptr);
	free(ptr);
}