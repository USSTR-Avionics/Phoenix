//
// Created by TDKua on 2023/10/22.
//
#include "Utils/MemoryPool.h"

State* Unarmed::Run(SensorData &)
{
    if(false)
    {
        // transition to new state, will break SM if you create random obj
        return StateMemory.ReplaceAllocate<MainChute, decltype(this)>();
    }
    return this;
}
