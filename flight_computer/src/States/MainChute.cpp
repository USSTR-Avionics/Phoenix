#include "States.h"
#include "Global.h"

FlightState MainChute::Run(FlightStateMemPool& MemPool)
{
    //if height is less than accepted minimum height activate chute
    if(SD.m_RelativeAltitude < AcceptedMainChuteHeight)
    {
        // TODO: send signal to activate main chute
    }

    // if on ground detected, stop data colection
    if(SD.m_BarometerVal - PrevBarVal < 0.1f)
    {//allows for some margin of error in the barometer reading to make sure data collection actually stops

        // TODO: disable data collection
        // transition to new state, will break SM if you create random obj
	    return MemPool.emplace<Unarmed>().GetState();
    }
    PrevBarVal = SD.m_BarometerVal;
	return GetState();
}

FlightState inline MainChute::GetState() const
{
	return eMainChute;
}