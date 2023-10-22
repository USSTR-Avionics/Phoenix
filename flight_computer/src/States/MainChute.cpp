//
// Created by TDKua on 2023/10/22.
//
#include "States/MainChute.h"

bool MainChute::Run(SensorData &)
{
    return false;
}

State* MainChute::Transition()
{
	// will break SM you create random obj
    return new Land;
}
