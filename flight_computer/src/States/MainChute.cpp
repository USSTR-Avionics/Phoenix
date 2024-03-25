#include "States.h"
#include "Global.h"

FlightState MainChute::Run(FlightStateMemPool& MemPool)
{
    digitalWrite(18, HIGH);
    delay(2000);
    digitalWrite(18, LOW);

	// TODO Change the if condition
    if(RA::Global::Sensor.RecordSensorData(GetState()).m_State)
    {
        // transition to new state, will break SM if you create random obj
	    return MemPool.emplace<Unarmed>().GetState();
    }

	RA::Global::FRam.StoreData(RA::Global::Sensor.GetData());

	return GetState();
}

FlightState inline MainChute::GetState() const
{
	return eMainChute;
}