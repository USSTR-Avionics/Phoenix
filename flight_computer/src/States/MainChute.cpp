//
// Created by TDKua on 2023/10/22.
//
#include "GlobalVariables.h"

State* MainChute::Run(SensorData&)
{
    if(false)
    {
        // transition to new state, will break SM if you create random obj
        return StatePool.ReplaceAllocate<MainChute, decltype(this)>();
    }
    return this;
}
