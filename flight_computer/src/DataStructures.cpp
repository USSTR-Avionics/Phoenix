#include "DataStructures.h"

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


std::array<std::byte, 41> SensorData::GetBytesCompressed() const
{
    std::array<std::byte, 41> Data;
    uint32_t Cursor{m_FramCursor};
    std::byte* BytePtr;

    // Time Stamp
    BytePtr = reinterpret_cast<std::byte*>(&m_TimeStamp);
    for(int i = 0; i < 4; i++)
    {
        if(!Write(BytePtr[i], Cursor)) { return false; }
        Cursor++;
    }

    // Rocket BaseState
    Write(static_cast<std::byte>(SD.m_State), Cursor);
    Cursor++;

    // Accel
    {
        uint16_t AccelXYZ[]
                {
                        fp16_ieee_from_fp32_value(SD.m_AccelerometerData.xData),
                        fp16_ieee_from_fp32_value(SD.m_AccelerometerData.yData),
                        fp16_ieee_from_fp32_value(SD.m_AccelerometerData.zData)
                };

        for(auto& i : AccelXYZ)
        {
            BytePtr = reinterpret_cast<std::byte*>(&i);
            for(int j = 0; j < 2; j++)
            {
                if(!Write(BytePtr[j], Cursor)) { return false; }

                Cursor++;
            }
        }
    }

    // Gyro
    {
        uint16_t GyroXYZ[]
                {
                        fp16_ieee_from_fp32_value(SD.m_Gyro.x),
                        fp16_ieee_from_fp32_value( SD.m_Gyro.y),
                        fp16_ieee_from_fp32_value( SD.m_Gyro.z),
                };

        for(auto& i : GyroXYZ)
        {
            BytePtr = reinterpret_cast<std::byte*>(&i);
            for(int j = 0; j < 2; j++)
            {
                if(!Write(BytePtr[j], Cursor)) { return false; }

                Cursor++;
            }
        }
    }

    // relative altitude
    auto RelativeAltitude = fp16_ieee_from_fp32_value(SD.m_RelativeAltitude);
    BytePtr = reinterpret_cast<std::byte*>(&RelativeAltitude);
    for(int i = 0; i < 2; i++)
    {
        if(!Write(BytePtr[i], Cursor)) { return false; }

        Cursor++;
    }

    // pressure
    BytePtr = reinterpret_cast<std::byte*>(&SD.m_BarometerVal);
    for(int i = 0; i < 4; i++)
    {
        if(!Write(BytePtr[i], Cursor)) { return false; }
        Cursor++;
    }

    // Thermocouple
    auto Thermocouple = fp16_ieee_from_fp32_value(SD.m_Temperature);
    BytePtr = reinterpret_cast<std::byte*>(&Thermocouple);
    for(int i = 0; i < 2; i++)
    {
        if(!Write(BytePtr[i], Cursor)) { return false; }

        Cursor++;
    }

    m_FramCursor = Cursor;

}

std::array<std::byte, 25> SensorData::GetBytes() const
{
    return std::array<std::byte, 25>();
}