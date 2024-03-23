// // the setup function runs once when you press reset or power the board
// void setup() {
//   // initialize digital pin LED_BUILTIN as an output.
//   pinMode(LED_BUILTIN, OUTPUT);
// }

// // the loop function runs over and over again forever
// void loop() {
//   digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//   delay(1000);                      // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//   delay(1000);                      // wait for a second
// }
#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>

#include "StateMachine.h"
#include "Watchdog_t4.h"
#include "FRAM.h"

//Adafruit_BMP280 bmp; // use I2C interface
//Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
//Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

// CHANGE THESE VALUES
RA::Sensor Sensor({18, 18, 18}, {18, 18}, 18);
FRAM FRam(0, 32000);

// StateMachine StateMachine;
// WDT_T4<WDT2> WatchDog;

uint64_t PrevTime = 0, CurrentTime;

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
    //     Serial.println("State machine could not allocate memory pool");
    // }
    Sensor.Setup();

	// CHANGE THIS NUMBER
	if(!FRam.Init(0x50))
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
    //Serial.println("Reading Data:");
	// WatchDog.feed();
    //Sensor.ReadSensorData();

	/*
	CurrentTime = millis();
	// must add, millis() can overflow
	if(PrevTime + 5000 <= CurrentTime)
	{
		FRam.StoreData(Sensor.GetData(), CurrentTime);
		PrevTime = CurrentTime;
	}
	*/

//#ifdef TEENSY_OPT_DEBUG
    //Serial.println("DebugMacroWorks");
//#endif
	//StateMachine.Run(Sensor);
}