#include "States.h"

State* InFlight::Run(const SensorData& SD, StateMemPool& MemPool)
{
    if(SD.m_AccelerometerData.zData < -9.81)
	{
        return static_cast<State*>(&MemPool.emplace<MainChute>());
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
    return static_cast<State*>(this);
}

FlightState InFlight::GetState()
{
	return FlightState::eInFlight;
}
