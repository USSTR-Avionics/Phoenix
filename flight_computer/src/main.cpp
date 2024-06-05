#include "Global.h"

#include "StateMachine.h"
#include <Watchdog_t4.h>

#include "Utils/Functions.h"

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
	Serial.println("WatchDog bit you!!");
	StateMachine.GoState<InFlight>();
	WatchDog.feed();
}

void setup()
{
    pinMode(20, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(18, OUTPUT);

    // watch dog
    WatchDog.begin(
{
			// jump to callback
           .trigger = 10.0,
		   // board shutdown
           .timeout = 20.0,
           .pin = 13,
           .callback = WatchDogInterrupt
       });
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

    SensorData d = SensorData();

    for (size_t i = 0; i < 10; i++)
    {
        d.m_AccelerometerData.xData = 1*i;
        d.m_AccelerometerData.xData = 2*i;
        d.m_AccelerometerData.xData = 3*i;

        d.m_TimeStamp = i;

        RA::Global::IO::Radio.UDP_Send(d,1);
    }
    for (size_t i = 0; i < 10; i++)
    {
        RA::Global::IO::Radio.UDP_Send("Hello World! "+i,1);
    }
    


    //auto tim = millis();
}

void loop()
{
	Serial.println(to_string(StateMachine.Run()).c_str());
	WatchDog.feed();

//#ifdef TEENSY_OPT_DEBUG
    //Serial.println("DebugMacroWorks");
//#endif
	//StateMachine.Run(Sensors);
}
