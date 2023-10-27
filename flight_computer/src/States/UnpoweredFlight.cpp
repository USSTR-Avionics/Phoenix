//
// Created by TDKua on 2023/10/22.
//
#include "StateMachine.h"

State* UnpoweredFlight::Run(SensorData& SD, StateMemPool& MemPool)
{
    if(false)
    {
        // transition to new state, will break SM if you create random obj
		// same as &MemPool.emplace<MainChute>(), doesn't seem to affect binary size
        return dynamic_cast<State*>(&MemPool.emplace<MainChute>());
    }
    return dynamic_cast<State*>(&std::get<UnpoweredFlight>(MemPool));
}