#include "States.h"
#include "Global.h"

FlightState InFlight::Run(FlightStateMemPool& MemPool)
{
	auto& NewVal{RA::Global::IO::Sensor.RecordSensorData(GetState())};
    if(prevHeight - NewVal.m_Bmp.RelativeAltitude < 0.f)
	{
        //Deploy drougue chute
		return MemPool.emplace<MainChute>().GetState();
    }

	prevHeight = NewVal.m_Bmp.RelativeAltitude;
	// collect data
	RA::Global::IO::FRam.StoreData(NewVal);

    // digitalWrite(19, HIGH);
    // delay(2000);
    // digitalWrite(19, LOW);
    // if(true)
    // {
    //     // transition to new state, will break SM if you create random obj
	// 	// same as &MemPool.emplace<MainChute>(), doesn't seem to affect binary size
    //     return dynamic_cast<State*>(&MemPool.emplace<BallisticDescent>());
    // }
	return GetState();
}

FlightState inline InFlight::GetState() const
{
	return eInFlight;
}