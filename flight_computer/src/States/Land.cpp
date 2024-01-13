//
// Created by TDKua on 2023/10/22.
//
#include "StateMachine.h"
#include "States/Land.h"


State* Land::Run(SensorData& SD, StateMemPool& MemPool)
{
	// Are you sure its y?
    if(SD.m_AccelerometerData.yData < -9.8)
	// always return self, no transition
    // delay(1000);
    // digitalWrite(19, HIGH);
    // delay(1000);
    // digitalWrite(19, LOW);
	return dynamic_cast<State*>(&std::get<Land>(MemPool)); // equivalent : return this;
}

FlightState Land::GetState()
{
	return FlightState::eLand;
}
