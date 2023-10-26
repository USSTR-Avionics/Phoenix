//
// Created by TDKua on 2023/10/23.
//

#ifndef FLIGHT_COMPUTER_MEMORYPOOL_H
#define FLIGHT_COMPUTER_MEMORYPOOL_H

#include <new>

#include "Utils/Functions.h"

namespace UA
{
// currently only allocates for 1 thing at a time
// ...T are the list of the TYPES of objects that this memory pool needs to allocate for.
template<typename ...T>
class MemoryPool
{
public:
	// Replace the current allocation with a new one
	template<typename New_T, typename Old>
	New_T* ReplaceAllocate()
	{
		if (!bCanAllocate)
		{ Deallocate<Old>(); }

		// placement new
		new((void*) m_pCurrent) New_T;
		bCanAllocate = false;

		// return allocated mem
		return (New_T*) m_pCurrent;
	}

	// allocate a given type
	template<typename U>
	U* Allocate()
	{
		if (!bCanAllocate)
		{ return nullptr; }

		// placement new
		new((void*) m_pCurrent) U;
		bCanAllocate = false;

		// return allocated mem
		return (U*) m_pCurrent;
	}

	// deallocate type
	template<typename U>
	void Deallocate()
	{
		// call destructor
		((U*) m_pCurrent)->~U();
		bCanAllocate = true;
	}

	MemoryPool() = default;

	MemoryPool(MemoryPool&) = delete;

	MemoryPool& operator =(MemoryPool&) = delete;

private:
	bool bCanAllocate{true};

	// consider std::byte
	// don't care what is in it, will only waste resources setting them to 0
	alignas(MaxAlignof<T...>()) unsigned char Pool[MaxSizeof<T...>()];
	// redundant ptr technically
	unsigned char* m_pCurrent = Pool;
};
}

#endif //FLIGHT_COMPUTER_MEMORYPOOL_H
