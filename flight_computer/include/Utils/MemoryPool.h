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
template<typename ...T>
class MemoryPool
{
public:
	template<typename New_T, typename Old>
	New_T* ReplaceAllocate()
	{
		if(!bCanAllocate)
        {
            // deallocate
            Deallocate<Old>();
        }

		// placement new
		new((void*)m_pCurrent) New_T;
		bCanAllocate = false;

		// return allocated mem
		return (New_T*)m_pCurrent;
	}

    template<typename U>
    U* Allocate()
    {
        if(!bCanAllocate) { return nullptr; }

        // placement new
        new((void*)m_pCurrent) U;
        bCanAllocate = false;

        // return allocated mem
        return (U*)m_pCurrent;
    }

	template<typename U>
	void Deallocate()
	{
		// call destructor
		((U*)m_pCurrent)->~U();
		bCanAllocate = true;
	}

    MemoryPool() = default;
	MemoryPool(MemoryPool&) = delete;
	MemoryPool& operator=(MemoryPool&) = delete;

private:
	bool bCanAllocate{true};

	// don't care what is in it, will only waste resources setting them to 0
	alignas(MaxAlignof<T...>()) unsigned char Pool[MaxSizeof<T...>()];
	unsigned char* m_pCurrent = Pool;
};

static MemoryPool<Unarmed, GroundIdle, PoweredFlight, UnpoweredFlight, BallisticDescent, MainChute, Land> StateMemory;


#endif //FLIGHT_COMPUTER_MEMORYPOOL_H
