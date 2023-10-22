//
// Created by TDKua on 2023/10/22.
//

#include "States/PoweredFlight.h"

bool PoweredFlight::Run(SensorData &)
{
    return false;
}

State* PoweredFlight::Transition()
{
	// will break SM you create random obj
    return new UnpoweredFlight;
}
