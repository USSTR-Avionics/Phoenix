#pragma once

#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include <BMI088.h>
#include <SparkFun_KX13X.h> // Click here to get the library: http://librarymanager/All#SparkFun_KX13X
//#include <SparkFun_Qwiic_KX13X.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MAX31855.h>

#include <array>
#include <algorithm>

#include "DataStructures.h"

namespace RA
{
class Sensor_t
{
public:
	/**
	 * Construct sensors
	 * @param ThermocouplePin SCLK, CS, MISO
	 * @param BmiPin Accel addr, Gyo addr
	 * @param KxAccelPin KxAccelPin
	 */
	Sensor_t(std::array<int8_t, 3> ThermocouplePin, std::array<uint8_t, 2> BmiPin, uint8_t KxAccelPin) :
		m_Thermocouple{ThermocouplePin[0], ThermocouplePin[1], ThermocouplePin[2]},
		m_Bmi{Wire, BmiPin[0], BmiPin[1]},
		m_KxAccelPin{KxAccelPin}{};

	/**
	 * Computes weighted average of 2 values
	 * @tparam T the type of data
	 * @condition type satisfy T + T -> T, T * float -> convertible_to<T>
	 * @param New New value
	 * @param Old Previous value
	 * @param NewPercentage The weight of new value, 0.0 - 1.0
	 * @return The weighted average
	 */
	template<typename T>
	requires requires (T a, T b, float c)
	{
		// T + T -> T
		a + b;
		// T * float -> convertible_to<T>
		{ a * c } -> std::convertible_to<T>;
	}
	static T Average(T New, T Old, float NewPercentage)
	{
		NewPercentage = std::clamp(NewPercentage, 0.f, 1.f);
		return NewPercentage * New + (1.f - NewPercentage) * Old;
	}

	void Setup();

	void ReadAcceleration();

	void ReadBarometer();

	void ReadThermocouple();

	SensorData&  RecordSensorData(FlightState CurrentState);

	SensorData GetData();

	void SetSensorData(const SensorData& SD) { m_SD = SD; }
private:
	Adafruit_MAX31855 m_Thermocouple;
	Bmi088 m_Bmi;
	//QwDevKX134 m_KxAccel;
	//QwiicKX134 m_KxAccel;
	SparkFun_KX134 m_KxAccel;
	// SparkFun_KX134 kxAccel; // For the KX134, uncomment this and comment line above

	// I2C
	Adafruit_BMP280 m_Bmp;

	SensorData m_SD;

    uint32_t m_PrevTime{}, m_CurrentTime{};

	const uint8_t m_KxAccelPin;
};
}
