#include "States.h"

#include <Arduino.h>

FlightState Unarmed::Run(const SensorData& SD, FlightStateMemPool& MemPool)
{
    digitalWrite(20, HIGH);
    delay(2000);
    digitalWrite(20, LOW);

    if(true)
    {
        // transition to new state, will break SM if you create random obj
	   return MemPool.emplace<GroundIdle>().GetState();
    }
	return GetState();
}

FlightState inline Unarmed::GetState() const
{
	return eUnarmed;
}