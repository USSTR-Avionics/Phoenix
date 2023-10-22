//
// Created by TDKua on 2023/10/22.
//
#include "States/UnpoweredFlight.h"

bool UnpoweredFlight::Run(SensorData &)
{
    return false;
}

State* UnpoweredFlight::Transition()
{
	// will break SM you create random obj
    return new BallisticDescent;
}
