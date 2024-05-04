#ifndef SENSOR_FRAM_H
#define SENSOR_FRAM_H

#include "fp16.h"
#include "Sensor_t.h"

#include <Adafruit_FRAM_I2C.h>

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

class FRAM_t
{
public:
	FRAM_t(uint32_t MinAddr, uint32_t MaxAddr)
	: m_MaxAddr{MaxAddr}, m_MinAddr{MinAddr}, m_FramWriteCursor{MinAddr}{};

	/**
	 * Is the fram ready
	 * @param I2C_Addr the I^2C address to use
	 * @return true if ready
	 */
	bool Init(uint8_t I2C_Addr);

	/**
	 * @brief    stores sensor info to FRAM_t
	 * @param    SD struct of SensorData to store
	 * @return   success or failure
	 */
	bool StoreData(SensorData SC);

	/**
	 * @brief    Reads SensorData chunk from FRAM_t
	 * @param    Item the i-th item to read
	 * @return   the data chunk read from FRAM_t
	 */
	SensorChunk ReadData(uint16_t Item);

private:
	bool Write(std::byte Data, uint32_t Location);
	std::byte Read(uint16_t Location);

	// The last addr that will be used
	const uint32_t m_MaxAddr;
	// Starting Addr
	const uint32_t m_MinAddr;

	// max addr is uint16_t, attempt to write past max addr will fail, prevents overflow
	uint32_t m_FramWriteCursor;

	Adafruit_FRAM_I2C m_FRAM;

};

#endif