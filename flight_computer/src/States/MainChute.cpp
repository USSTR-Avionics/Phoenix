//
// Created by TDKua on 2023/10/22.
//
#include "StateMachine.h"
#include "States/MainChute.h"


State* MainChute::Run(SensorData& SD, StateMemPool& MemPool)
{
    digitalWrite(18, HIGH);
    delay(2000);
    digitalWrite(18, LOW);
    if(true)
    {
        // transition to new state, will break SM if you create random obj
	    return dynamic_cast<State*>(&MemPool.emplace<Land>());
    }
	return dynamic_cast<State*>(&std::get<MainChute>(MemPool));
}

FlightState MainChute::GetState()
{
	return FlightState::eMainChute;
}
