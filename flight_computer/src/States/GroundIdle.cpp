#include "States.h"

#include <Arduino.h>

FlightState GroundIdle::Run(const SensorData& SD, FlightStateMemPool& MemPool)
{
    digitalWrite(19, HIGH);
    delay(2000);
    digitalWrite(19, LOW);
    if(true)
    {
        // transition to new state, will break SM if you create random obj
	    return MemPool.emplace<InFlight>().GetState();
    }
	return GetState();
}

FlightState inline GroundIdle::GetState() const
{
	return eGroundIdle;
}