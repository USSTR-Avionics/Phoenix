//
// Created by TDKua on 2023/10/22.
//
#include "Utils/MemoryPool.h"

bool Unarmed::Run(SensorData &)
{
    return false;
}

State* Unarmed::Transition()
{
	// will break SM you create random obj
    return new GroundIdle;
}
