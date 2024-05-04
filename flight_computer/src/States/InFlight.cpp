#include "States.h"
#include "Global.h"

FlightState InFlight::Run(FlightStateMemPool& MemPool)
{
    if(RA::Global::IO::Sensor.RecordSensorData(GetState()).m_AccelerometerData.zData < -9.81f)
	{
        //Deploy drougue chute
		return MemPool.emplace<MainChute>().GetState();
    }

	prevHeight = RA::Global::IO::Sensor.GetData();
	// collect data
	RA::Global::IO::FRam.StoreData(prevHeight);

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