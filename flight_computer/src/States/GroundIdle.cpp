#include "States.h"

#include "Global.h"

FlightState GroundIdle::Run(FlightStateMemPool& MemPool)
{
    //TODO: change acceleration axis and value to be respective to sensor
    if(RA::Global::IO::Sensor.GetData().m_AccelerometerData.zData > 2.0f)
    {
        // transition to new state, will break SM if you create random obj
	    return MemPool.emplace<InFlight>().GetState();
    }
	return GetState();
}

FlightState inline GroundIdle::GetState() const
{
	return eGroundIdle;
}