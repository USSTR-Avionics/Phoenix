#include "States.h"

#include <Arduino.h>

State* Unarmed::Run(const SensorData& SD, StateMemPool& MemPool)
{
    //swichs states if recieved arming signal
    //TODO: be able to recieve arming signal
    if(true)
    {
        // transition to new state, will break SM if you create random obj
	    return static_cast<State*>(&MemPool.emplace<GroundIdle>());
    }
	return static_cast<State*>(this);
}

FlightState Unarmed::GetState()
{
	return FlightState::eUnarmed;
}
