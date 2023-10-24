//
// Created by TDKua on 2023/10/22.
//
#include "Utils/MemoryPool.h"

bool UnpoweredFlight::Run(SensorData &)
{
    return false;
}

State* UnpoweredFlight::Transition()
{
	MemoryPool& Pool = MemoryPool::Instance();
	Pool.Deallocate<State>();
	// will break SM you create random obj, see diagram for which state to transition to
    return Pool.Allocate<BallisticDescent>();
}