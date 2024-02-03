//
// Created by TDKua on 2023/10/22.
//
#include "StateMachine.h"
#include "States/BallisticDescent.h"


State* BallisticDescent::Run(SensorData& SD, StateMemPool& MemPool)
{
    if (SD.m_BarometerVal > 2000)
    {
        return dynamic_cast<State*>(&std::get<MainChute>(MemPool));
    }
    
    // digitalWrite(20, HIGH);
    // delay(2000);
    // digitalWrite(20, LOW);
    // if(true)
    // {
    //     // transition to new state, will break SM if you create random obj
	//     return dynamic_cast<State*>(&MemPool.emplace<MainChute>());
    // }
	return dynamic_cast<State*>(&std::get<BallisticDescent>(MemPool));
}

FlightState BallisticDescent::GetState()
{
	return FlightState::eBallisticDescent;
}
