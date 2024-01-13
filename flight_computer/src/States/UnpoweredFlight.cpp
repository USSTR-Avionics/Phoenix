//
// Created by TDKua on 2023/10/22.
//
#include "StateMachine.h"
#include "States/UnpoweredFlight.h"


State* UnpoweredFlight::Run(SensorData& SD, StateMemPool& MemPool)
{
    if(SD.m_AccelerometerData.zData < -9.81){
        return dynamic_cast<State*>(&MemPool.emplace<BallisticDescent>());
    }
    // digitalWrite(19, HIGH);
    // delay(2000);
    // digitalWrite(19, LOW);
    // if(true)
    // {
    //     // transition to new state, will break SM if you create random obj
	// 	// same as &MemPool.emplace<MainChute>(), doesn't seem to affect binary size
    //     return dynamic_cast<State*>(&MemPool.emplace<BallisticDescent>());
    // }
    return dynamic_cast<State*>(&std::get<UnpoweredFlight>(MemPool));
}

FlightState UnpoweredFlight::GetState()
{
	return FlightState::eUnpoweredFlight;
}
