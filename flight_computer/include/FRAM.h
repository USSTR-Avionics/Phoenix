#ifndef SENSOR_FRAM_H
#define SENSOR_FRAM_H

#include <Adafruit_FRAM_I2C.h>
#include <FP16.h>

#include "FlightComputer.h"
#include "Sensor.h"

// data chunk format
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

struct SensorChunk : SensorData
{
	uint32_t m_TimeStamp;
	bool m_SuccessfulRead;
};

class FRAM
{
public:
	FRAM(uint32_t MinAddr, uint32_t MaxAddr, uint32_t InitAddr) :
	m_MaxAddr(MaxAddr), m_MinAddr(MinAddr), m_FramCursor(InitAddr){}

	bool Init(uint8_t I2C_Addr);

	bool StoreData(SensorData SC, uint32_t TimeStamp);

	SensorChunk ReadData(uint32_t Location);

private:
	bool Write(uint8_t Data, uint32_t Location);
	uint8_t Read(uint16_t Location);

	float ReadF16(uint32_t Location);
	float ReadF32(uint32_t Location);

	const uint32_t m_MaxAddr;
	const uint32_t m_MinAddr;

	// max addr is uint16_t, attempt to write past max addr will fail, prevents overflow
	uint16_t m_FramCursor;

	Adafruit_FRAM_I2C m_FRAM;
};
// actual funcs
int init_fram();

// ! These should not be used directly, use the package_fram.h API instead
int write_to_fram(uint8_t, uint16_t);
int read_from_fram(int);

#endif // SENSOR_FRAM_H
