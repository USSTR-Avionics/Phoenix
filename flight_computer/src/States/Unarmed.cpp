//
// Created by TDKua on 2023/10/22.
//
#include "StateMachine.h"
#include "States/Unarmed.h"


State* Unarmed::Run(SensorData& SD, StateMemPool& MemPool)
{
    digitalWrite(20, HIGH);
    delay(2000);
    digitalWrite(20, LOW);

    if(true)
    {
        // transition to new state, will break SM if you create random obj
	    return dynamic_cast<State*>(&MemPool.emplace<GroundIdle>());
    }
	return dynamic_cast<State*>(&std::get<Unarmed>(MemPool));
}

FlightState Unarmed::GetState()
{
	return FlightState::eUnarmed;
}
