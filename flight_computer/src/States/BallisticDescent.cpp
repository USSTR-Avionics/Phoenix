//
// Created by TDKua on 2023/10/22.
//
#include "States/BallisticDescent.h"

bool BallisticDescent::Run(SensorData &)
{
    return false;
}

State* BallisticDescent::Transition()
{
	// will break SM you create random obj
    return new MainChute;
}
