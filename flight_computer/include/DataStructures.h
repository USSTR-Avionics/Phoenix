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
// | acceleration x axis  | 02 bytes  | float16   |
// | acceleration y axis  | 02 bytes  | float16   |
// | acceleration z axis  | 02 bytes  | float16   |
// | gyroscope x axis     | 02 bytes  | float16   |
// | gyroscope y axis     | 02 bytes  | float16   |
// | gyroscope z axis     | 02 bytes  | float16   |
// | relative altitude    | 02 bytes  | float16   |
// | pressure (barometer) | 04 bytes  | float32   |
// | thermocouple temp    | 02 bytes  | float16   |
// | timestamp            | 04 bytes  | uint32_t  |
// | rocket state         | 01 byte   | uint8_t   |
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

	struct BMP280
	{
		float RelativeAltitude;
		float Barometer;
	} m_Bmp{};

    // MAX31855
    float m_Temperature{};

    uint32_t m_TimeStamp{};

    FlightState m_State {};

    [[nodiscard]] std::array<std::byte, 41> GetBytes() const;
    [[nodiscard]] std::array<std::byte, 25> GetBytesCompressed() const;
};

struct SensorChunk : SensorData
{
	bool m_SuccessfulRead{false};
	/**
	 * Create SensorChunk from bytes
	 * @param Data ptr to 41 bytes of data
	 * @return populated SensorChunk
	 */
	static SensorChunk DecodeBytes(const std::byte Data[]);

	/**
	 * Create SensorChunk from compressed bytes
	 * @param Data ptr to 25 bytes of data
	 * @return populated SensorChunk
	 */
	static SensorChunk DecodeBytesCompressed(const std::byte Data[]);


private:
	static float ReadF16(const std::byte* Location);
	static float ReadF32(const std::byte* Location);
};

#endif //FLIGHT_COMPUTER_DATASTRUCTURES_H
