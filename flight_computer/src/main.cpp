#include "Global.h"

#include "StateMachine.h"
#include <Watchdog_t4.h>

namespace RA::Global::IO
{
	// RA::Sensors RA::Global::IO::Sensors{};
	RA::Sensors Sensor{{18, 18, 18}, {18, 18}, 18};
	FRAM FRam{0, 0};
	RA::Radio Radio{0, 0};
}

StateMachine StateMachine;
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

    // check StateMachine
    // if (!StateMachine.Ready())
    // {
    //     Serial.println("BaseState machine could not allocate memory pool");
    // }
    RA::Global::IO::Sensor.Setup();

	// CHANGE THIS NUMBER
	if(!RA::Global::IO::FRam.Init(0x50))
	{
		Serial.println("Failed to init FRam at addr");
	}

    //auto tim = millis();
}

void loop()
{
	StateMachine.Run();
	// WatchDog.feed();

    //determines whether to log data

    //everything after this point should be to log data

	/*
	CurrentTime = millis();
	// must add, millis() can overflow
	if(PrevTime + 5000 <= CurrentTime)
	{
		FRam.StoreData(Sensors.GetData(), CurrentTime);
		PrevTime = CurrentTime;
	}
	*/

//#ifdef TEENSY_OPT_DEBUG
    //Serial.println("DebugMacroWorks");
//#endif
	//StateMachine.Run(Sensors);
}
