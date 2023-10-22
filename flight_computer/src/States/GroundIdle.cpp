//
// Created by TDKua on 2023/10/22.
//
#include "States/GroundIdle.h"

bool GroundIdle::Run(SensorData &)
{
    return false;
}

State* GroundIdle::Transition()
{
	// will break SM you create random obj
    return new PoweredFlight;
}
