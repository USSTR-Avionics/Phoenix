#pragma once
#include "flight_states.h"
#include "BMI088.h"
#include <algorithm>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Arduino.h>

#include "SensorData.h"
#include "StateMachine.h"
#include "Watchdog_t4.h"

#include <SparkFun_KX13X.h> // Click here to get the library: http://librarymanager/All#SparkFun_KX13X

#define BMP_SCK  (16)

#include "Adafruit_MAX31855.h"


struct SensorData
{
	/*
	* lets assume everything is a float for now
	*/
	float m_AccelX;
	float m_AccelY;
	float m_AccelZ;

	float m_BarometerVal;
	float m_Temperature;

	// Struct for the accelerometer's data
	outputData AccelerometerData;

	FlightStates m_State;


	/* SensorData - needs to store data from the following sensors:
	 - accelerometer -kx134 - 8bit, 16bit https://www.mouser.ca/ProductDetail/Kionix/KX134-1211?qs=BJlw7L4Cy79%2FET%2FI6G7icQ%3D%3D

	 - scrapped - gyroscope 6axis includes accelerometer -bmi088
	 - magnetometer -NA
	 - find one which does all 3 of above sensors
	 - barometer -bmp280 8bit https://www.bosch-sensortec.com/products/environmental-sensors/pressure-sensors/bmp280/#software
	 - thermocouple - MAX31855 https://learn.adafruit.com/thermocouple/downloads
	 - fram - adafruit i2c fram

	 - flight state
	*/

	/*
	bmp280 :   Struct BMP280_data { float Temperature , float  Pressure, float Altitude}

	fram: returns an 8-bit integer when reading a memory address

	MAX31855: float for the temperature

	kx134: Struct accelerometer_data {float X, float Y, float Z}
	*/

};

constexpr int8_t MAXDO = 3;
constexpr int8_t MAXCS = 4;
constexpr int8_t MAXCLK = 5;

class Sensor
{
public:
	template<typename T> requires std::is_arithmetic_v<T>
	static T Average(T New, T Old, float NewPercentage)
	{
		NewPercentage = std::clamp(NewPercentage, 0.f, 1.f);
		return NewPercentage * New + (1.f - NewPercentage) * Old;
	}

	void Setup();

	void ReadAcceleration();

	void ReadBarometer();

	void ReadThermocouple();

	void ReadSensorData();

	SensorData GetData();

	void CreatThermocouple(int8_t MaxClk, int8_t MaxCS, int8_t MaxDO);

	void CreateBMI(uint8_t AccelAddr, uint8_t GyroAddr);

private:

	SensorData SD;

	Adafruit_MAX31855 Thermocouple;

	SparkFun_KX132 kxAccel;
	// SparkFun_KX134 kxAccel; // For the KX134, uncomment this and comment line above

	// I2C
	Adafruit_BMP280 Bmp;

	Bmi088 Bmi;
};





