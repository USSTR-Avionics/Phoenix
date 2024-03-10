#include "States.h"

State* MainChute::Run(const SensorData& SD, StateMemPool& MemPool)
{
    digitalWrite(18, HIGH);
    delay(2000);
    digitalWrite(18, LOW);
    if(true)
    {
        // transition to new state, will break SM if you create random obj
	    return static_cast<State*>(&MemPool.emplace<Unarmed>());
    }
	return static_cast<State*>(this);
}

FlightState MainChute::GetState()
{
	return FlightState::eMainChute;
}
