#include "Global.h"

#include "StateMachine_t.h"
#include <Watchdog_t4.h>

namespace RA::Global::IO
{
	// RA::Sensor_t RA::Global::IO::Sensor_t{};
	RA::Sensor_t Sensor{{18, 18, 18}, {18, 18}, 18};
	FRAM_t FRam{0, 0};
	Radio_t Radio_t{0, 0};
}

StateMachine_t StateMachine;
WDT_T4<WDT2> WatchDog;

void WatchDogInterrupt()
{
	// WatchDog.feed();
}

void setup()
{

    pinMode(20, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(18, OUTPUT);

    // watch dog
  /*  WatchDog.begin({
                           .trigger = 10.0,
                           .timeout = 20.0,
                           .pin = 13,
                           .callback = WatchDogInterrupt
                   });*/
    // ==============

    Serial.begin(9600);
    while (!Serial) delay(100);   // wait for native usb

    // check StateMachine_t
    // if (!StateMachine_t.Ready())
    // {
    //     Serial.println("BaseState machine could not allocate memory pool");
    // }
    RA::Global::IO::Sensor.Setup();

	// CHANGE THIS NUMBER
	if(!RA::Global::IO::FRam.Init(0x50))
	{
		Serial.println("Failed to init FRam at addr");
	}


    SensorData SD{};

    SD.m_Gyro.x = 1.2f;

    //auto tim = millis();
    for(int i = 0; i < 1290; i++)
    {
        if(!FRam.StoreData(SD, i)){
            Serial.println("Failed to store");
        }
    }
    for(int i = 1200; i < 1290; i++)
    {
        Serial.println(FRam.ReadData(i*25).m_TimeStamp);
        Serial.println(FRam.ReadData(i*25).m_SuccessfulRead);
    }

}

void loop()
{
	// WatchDog.feed();
    Sensor.ReadSensorData();

    //used to ensure the data
    FlightState CurrentState{StateMachine.Run(Sensor.GetData())};

    //determines whether to log data
    if(CurrentState != FlightState::eInFlight && CurrentState != FlightState::eMainChute)
    {
        //dont log data
        return;
    }
    //everything after this point should be to log data

	/*
	CurrentTime = millis();
	// must add, millis() can overflow
	if(PrevTime + 5000 <= CurrentTime)
	{
		FRam.StoreData(Sensor_t.GetData(), CurrentTime);
		PrevTime = CurrentTime;
	}
	*/

//#ifdef TEENSY_OPT_DEBUG
    //Serial.println("DebugMacroWorks");
//#endif
	//StateMachine_t.Run(Sensor_t);
}
