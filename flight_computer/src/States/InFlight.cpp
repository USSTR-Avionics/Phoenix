#include "States.h"

FlightState InFlight::Run(const SensorData& SD, FlightStateMemPool& MemPool)
{
    //apogee check ( if moving downwards, apogee is hit)
    if(prevHeight - SD.m_RelativeAltitude < 0)
	{
        //Deploy drougue chute
		return MemPool.emplace<MainChute>().GetState();
    }
    prevHeight = SD.m_RelativeAltitude;
	return GetState();
}

FlightState inline InFlight::GetState() const
{
	return eInFlight;
}