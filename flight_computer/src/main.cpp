


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
#include <Adafruit_BMP280.h>
#include <Arduino.h>

#include "SensorData.h"
#include "StateMachine.h"
#include "Watchdog_t4.h"

//Adafruit_BMP280 bmp; // use I2C interface
//Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
//Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

static SensorData SensorData;

static StateMachine State_Machine;
static WDT_T4<WDT2> WatchDog;

void WatchDogInterrupt()
{

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

	while (BMI.begin() < 0)
	{
		Serial.println("IMU Initialization Error");
	}

    // check StateMachine
    if (!State_Machine.Ready())
    {
        Serial.println("State machine could not allocate memory pool");
    }
    SensorData.Setup();
}

void loop()
{
    Serial.println("Reading Data:");
	WatchDog.feed();
    SensorData.ReadSensorData();
	//StateMachine.Run(SensorData);
}