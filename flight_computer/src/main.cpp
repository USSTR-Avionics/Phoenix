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


}

void loop()
{
    //Serial.println("Reading Data:");
	// WatchDog.feed();
    //Sensor_t.ReadSensorData();

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
