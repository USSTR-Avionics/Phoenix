#include "States.h"
#include "Global.h"

FlightState MainChute::Run(FlightStateMemPool& MemPool)
{
    //if height is less than accepted minimum height activate chute
    if(SD.m_RelativeAltitude < AcceptedMainChuteHeight)
    {
        // TODO: send signal to activate main chute
    }

	auto& NewVal = RA::Global::IO::Sensor.RecordSensorData(GetState());
	// TODO Change the if condition
    if(NewVal - PrevBarVal < 0.1f)
    {
        // transition to new state, will break SM if you create random obj
	    return MemPool.emplace<Unarmed>().GetState();
    }

	// collect data
	RA::Global::IO::FRam.StoreData(RA::Global::IO::Sensor.GetData());

	return GetState();
}

FlightState inline MainChute::GetState() const
{
	return eMainChute;
}