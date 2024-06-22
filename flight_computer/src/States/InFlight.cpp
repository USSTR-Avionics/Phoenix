#include "States.h"
#include "Global.h"

FlightState InFlight::Run(FlightStateMemPool& MemPool)
{
    // TODO : recauluate this entire thing
    /*
    * don't know which way the rocket will be falling(x,y,z?) (gyroscope?)
    * don't know when appogee
    * maybe get velocity with gyroscope and trig
    * velocity calc might be imprcise because polling rate differs(not polling fast enough for acctuate calc)
    */
	auto& NewVal{RA::Global::IO::Sensor.RecordSensorData(GetState())};
   Serial.print("prev altitude before");
    Serial.println(PrevAltitude);
	// apogee
    if(NewVal.m_Bmp.RelativeAltitude - PrevAltitude < 0.0f)
	{
        //Deploy drougue chute


		return MemPool.emplace<MainChute>().GetState();
    }

	PrevAltitude = NewVal.m_Bmp.RelativeAltitude;
    Serial.print("prev altitude after");
    Serial.println(PrevAltitude);

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