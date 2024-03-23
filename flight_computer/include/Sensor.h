#pragma once

#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include <array>
#include <algorithm>

#include <BMI088.h>
#include <SparkFun_KX13X.h> // Click here to get the library: http://librarymanager/All#SparkFun_KX13X
//#include <SparkFun_Qwiic_KX13X.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MAX31855.h>

#include "DataStructures.h"

namespace RA
{
class Sensor
{
public:
	/**
	 * Construct sensors
	 * @param ThermocouplePin SCLK, CS, MISO
	 * @param BmiPin Accel addr, Gyo addr
	 * @param KxAccelPin KxAccelPin
	 */
	Sensor(std::array<int8_t, 3> ThermocouplePin, std::array<uint8_t, 2> BmiPin, uint8_t KxAccelPin) :
		m_Thermocouple(Adafruit_MAX31855(ThermocouplePin[0], ThermocouplePin[1], ThermocouplePin[2])),
		m_Bmi(Bmi088(Wire, BmiPin[0], BmiPin[1])),
		m_KxAccelPin(KxAccelPin){};

	/**
	 * Computes weighted average of 2 values
	 * @tparam T the type of data
	 * @param New New value
	 * @param Old Previous value
	 * @param NewPercentage The weight of new value, 0.0 - 1.0
	 * @return The weighted average
	 */
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

private:

	SensorData m_SD;

	Adafruit_MAX31855 m_Thermocouple;
	Bmi088 m_Bmi;
	//QwDevKX134 m_KxAccel;
	//QwiicKX134 m_KxAccel;
	SparkFun_KX134 m_KxAccel;
	// SparkFun_KX134 kxAccel; // For the KX134, uncomment this and comment line above

	// I2C
	Adafruit_BMP280 m_Bmp;

	const uint8_t m_KxAccelPin;

};
}
