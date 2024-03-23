#include "States.h"

#include <Arduino.h>

State* GroundIdle::Run(const SensorData& SD, StateMemPool& MemPool)
{
    
    if(true)
    {
        // transition to new state, will break SM if you create random obj
	    return static_cast<State*>(&MemPool.emplace<InFlight>());
    }
	return static_cast<State*>(this);
}

FlightState GroundIdle::GetState()
{
	return FlightState::eGroundIdle;
}
