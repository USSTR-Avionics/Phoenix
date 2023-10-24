//
// Created by TDKua on 2023/10/23.
//

#ifndef FLIGHT_COMPUTER_MEMORYPOOL_H
#define FLIGHT_COMPUTER_MEMORYPOOL_H

#include <new>

#include "States/Unarmed.h"
#include "States/GroundIdle.h"
#include "States/PoweredFlight.h"
#include "States/UnpoweredFlight.h"
#include "States/BallisticDescent.h"
#include "States/MainChute.h"
#include "States/Land.h"

#include "Utils/Functions.h"

// calculate everything on creation with varadic templates
// currently only allocates for 1 state at a time, only for the statemachine
class MemoryPool
{
public:
	template<typename T>
	T* Allocate()
	{
		if(!bCanAllocate) { return nullptr; }

		// placement new
		new((T*)m_pCurrent) T;
		bCanAllocate = false;

		// return allocated mem
		return reinterpret_cast<T*>(m_pCurrent);
	};

	template<typename T>
	void Deallocate()
	{
		// call destructor
		((T*)m_pCurrent)->~T();
		bCanAllocate = true;
	};

	static MemoryPool& Instance()
	{
		static MemoryPool MemPool;
		return MemPool;
	};

	MemoryPool(MemoryPool&) = delete;
	MemoryPool& operator=(MemoryPool&) = delete;

private:
	MemoryPool() = default;
	bool bCanAllocate{true};

	static constexpr int Alignment{ Max(alignof(Unarmed), alignof(GroundIdle), alignof(PoweredFlight), alignof(UnpoweredFlight), alignof(BallisticDescent), alignof(MainChute), alignof(Land)) };
	static constexpr int PoolSize{ Max(sizeof(Unarmed), sizeof(GroundIdle), sizeof(PoweredFlight), sizeof(UnpoweredFlight), sizeof(BallisticDescent), sizeof(MainChute), sizeof(Land)) };

	// don't care what is in it, will only waste resources setting them to 0
	alignas(Alignment) unsigned char Pool[PoolSize];
	unsigned char* m_pCurrent = Pool;
};


#endif //FLIGHT_COMPUTER_MEMORYPOOL_H
