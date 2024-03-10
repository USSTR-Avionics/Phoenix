#include "States.h"

#include <Arduino.h>

State* Unarmed::Run(const SensorData& SD, StateMemPool& MemPool)
{
    digitalWrite(20, HIGH);
    delay(2000);
    digitalWrite(20, LOW);

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
