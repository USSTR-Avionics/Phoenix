#pragma once
#include "flight_states.h"
#include <algorithm>

class SensorData
{
    /*
    * lets assume everything is a float for now
    */
    public:
    float m_AccelX;
    float m_AccelY;
    float m_AccelZ;
 
    float m_BarometerVal;
    float m_Temperature;

    FlightStates m_State;

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