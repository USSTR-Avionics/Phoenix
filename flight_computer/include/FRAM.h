#ifndef SENSOR_FRAM_H
#define SENSOR_FRAM_H

#include "fp16.h"
#include "Sensor.h"

#include <Adafruit_FRAM_I2C.h>

// Sensor data chunk format
// |----------------------|-----------|-----------|
// |      data            |   size    | data type |
// |----------------------|-----------|-----------|
// | timestamp            | 04 bytes  | uint32    |
// | rocket state         | 01 byte   | uint8     |
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

struct SensorChunk : SensorData
{
	uint32_t m_TimeStamp{};
	bool m_SuccessfulRead{false};
};

class FRAM
{
public:
	FRAM(uint32_t MinAddr, uint32_t MaxAddr)
	: m_MaxAddr{MaxAddr}, m_MinAddr{MinAddr}, m_FramCursor{MinAddr}{};

	/**
	 * Is the fram ready
	 * @param I2C_Addr the I^2C address to use
	 * @return true if ready
	 */
	bool Init(uint8_t I2C_Addr);

	/**
	 * @brief    stores sensor info to FRAM
	 * @param    SD struct of SensorData to store
	 * @return   success or failure
	 */
	bool StoreData(SensorData SC, uint32_t TimeStamp);

	/**
	 * @brief    Reads SensorData chunk from FRAM
	 * @param    Location the address to read from
	 * @return   the data chunk read from FRAM
	 */
	SensorChunk ReadData(uint32_t Location);

private:
	bool Write(uint8_t Data, uint32_t Location);
	uint8_t Read(uint16_t Location);

	float ReadF16(uint32_t Location);
	float ReadF32(uint32_t Location);

	// The last addr that will be used
	const uint32_t m_MaxAddr;
	// Starting Addr
	const uint32_t m_MinAddr;

	// max addr is uint16_t, attempt to write past max addr will fail, prevents overflow
	uint32_t m_FramCursor;

	Adafruit_FRAM_I2C m_FRAM;
};

#endif // SENSOR_FRAM_H
