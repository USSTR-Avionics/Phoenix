#ifndef FLIGHT_COMPUTER_DATASTRUCTURES_H
#define FLIGHT_COMPUTER_DATASTRUCTURES_H

#include <SparkFun_KX13X.h>
#include <array>

// BaseState
enum FlightState : uint8_t;

// compressed data chunk format
// |----------------------|-----------|-----------|
// |      data            |   size    | data type |
// |----------------------|-----------|-----------|
// | timestamp            | 04 bytes  | u32       |
// | rocket state         | 01 byte   | u8        |
// | acceleration x axis  | 02 bytes  | float16   |
// | acceleration y axis  | 02 bytes  | float16   |
// | acceleration z axis  | 02 bytes  | float16   |
// | gyroscope x axis     | 02 bytes  | float16   |
// | gyroscope y axis     | 02 bytes  | float16   |
// | gyroscope z axis     | 02 bytes  | float16   |
// | relative altitude    | 02 bytes  | float16   |
// | pressure             | 04 bytes  | float32   |
// | thermocouple temp    | 02 bytes  | float16   |
// |----------------------|-----------|-----------|
// | total                | 25 bytes  |           |
// |----------------------|-----------|-----------|

struct SensorData
{
    // kx134, 3 floats
    outputData m_AccelerometerData{};

    struct Gyro
    {
        float x;
        float y;
        float z;
    } m_Gyro{};

    // bmp280
    float m_RelativeAltitude{};
    // bmp280, pressure
    float m_BarometerVal{};

    // MAX31855
    float m_Temperature{};

    uint32_t m_TimeStamp{};

    FlightState m_State {};

    std::array<std::byte, 25> GetBytes() const;
    std::array<std::byte, 41> GetBytesCompressed() const;



};

#endif //FLIGHT_COMPUTER_DATASTRUCTURES_H
