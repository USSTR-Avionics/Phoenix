#include "States.h"
#include "Global.h"

FlightState MainChute::Run(FlightStateMemPool& MemPool)
{
	auto& NewVal{ RA::Global::IO::Sensor.RecordSensorData(GetState()) };

    //if height is less than accepted minimum height activate chute
    if(NewVal.m_Bmp.RelativeAltitude < AcceptedMainChuteHeight)
    {
        // TODO: send signal to activate main chute
    }

	// TODO Change the if condition
    if(abs(NewVal.m_Bmp.Barometer - PrevBarVal) < 1.0f)
    {
        // transition to new state, will break SM if you create random obj
	    return MemPool.emplace<Unarmed>().GetState();
    }

	PrevBarVal = NewVal.m_Temperature;

	// collect data
	// RA::Global::IO::FRam.StoreData(RA::Global::IO::Sensor.GetData());

	return GetState();
}

FlightState inline MainChute::GetState() const
{
	return eMainChute;
}