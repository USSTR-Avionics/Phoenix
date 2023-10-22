//
// Created by TDKua on 2023/10/22.
//
#include "States/Land.h"

bool Land::Run(SensorData &)
{
    return false;
}

State* Land::Transition()
{
	// will break SM you create random obj
    return nullptr;
}
