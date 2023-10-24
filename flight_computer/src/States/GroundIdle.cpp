//
// Created by TDKua on 2023/10/22.
//
#include "Utils/MemoryPool.h"

bool GroundIdle::Run(SensorData& Data)
{
    return false;
}

State* GroundIdle::Transition()
{
	// will break SM you create random obj
    return new PoweredFlight;
}
