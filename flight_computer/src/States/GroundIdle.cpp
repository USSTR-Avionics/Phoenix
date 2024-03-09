//
// Created by TDKua on 2023/10/22.
//
#include "StateMachine.h"
#include "States/GroundIdle.h"


State* GroundIdle::Run(SensorData& SD, StateMemPool& MemPool)
{
    digitalWrite(19, HIGH);
    delay(2000);
    digitalWrite(19, LOW);
    if(true)
    {
        // transition to new state, will break SM if you create random obj
	    return dynamic_cast<State*>(&MemPool.emplace<InFlight>());
    }
	return dynamic_cast<State*>(&std::get<GroundIdle>(MemPool));
}

FlightState GroundIdle::GetState()
{
	return FlightState::eGroundIdle;
}
