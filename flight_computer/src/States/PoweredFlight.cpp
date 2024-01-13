//
// Created by TDKua on 2023/10/22.
//
#include "StateMachine.h"
#include "States/PoweredFlight.h"


State* PoweredFlight::Run(SensorData& SD, StateMemPool& MemPool)
{
    if(SD.m_AccelerometerData.zData > -9.8){
        // transition to new state, will break SM if you create random obj
	    return dynamic_cast<State*>(&MemPool.emplace<UnpoweredFlight>());
    }
    // digitalWrite(18, HIGH);
    // delay(2000);
    // digitalWrite(18, LOW);
    // if(true)
    // {
    //     // transition to new state, will break SM if you create random obj
	//     return dynamic_cast<State*>(&MemPool.emplace<UnpoweredFlight>());
    // }
	return dynamic_cast<State*>(&std::get<PoweredFlight>(MemPool));
}

FlightState PoweredFlight::GetState()
{
	return FlightState::ePoweredFlight;
}
