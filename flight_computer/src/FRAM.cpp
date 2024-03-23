#include "FRAM.h"

#include <bit>

/**
 * Is the fram ready
 * @param I2C_Addr the I^2C address to use
 * @return true if ready
 */
bool FRAM::Init(uint8_t I2C_Addr)
{
	return m_FRAM.begin(I2C_Addr);
}

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

/**
 * @brief    stores sensor info to fram
 * @param    SD struct of SensorData to store
 * @return   success or failure
 */
bool FRAM::StoreData(SensorData SD, uint32_t TimeStamp)
{
	uint32_t Cursor{m_FramCursor};
	std::byte* BytePtr;

	// Time Stamp
	BytePtr = reinterpret_cast<std::byte*>(&TimeStamp);
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
	return true;
}



/**
 * @brief    Reads SensorData chunck from FRAM
 * @param    Location the address to read from
 * @return   the data chunk read from FRAM
 */
SensorChunk FRAM::ReadData(uint32_t Location)
{
	SensorChunk SC;
	// check
	if(Location + 25 > m_MaxAddr) { SC.m_SuccessfulRead = false; return SC; }

	// time stamp
	std::byte Buff[4];
	for(auto& i : Buff)
	{
		i = Read(Location);
		Location++;
	}
    // reinterpret_cast is UB
	SC.m_TimeStamp = std::bit_cast<uint32_t>(Buff);

	// Rocket state
	SC.m_State = static_cast<FlightState>(Read(Location));
	Location++;

	// Accel
	SC.m_AccelerometerData.xData = ReadF16(Location);
	Location += 2;
	SC.m_AccelerometerData.yData = ReadF16(Location);
	Location += 2;
	SC.m_AccelerometerData.zData = ReadF16(Location);
	Location += 2;

	// Gyro
	SC.m_Gyro.x = ReadF16(Location);
	Location += 2;
	SC.m_Gyro.y = ReadF16(Location);
	Location += 2;
	SC.m_Gyro.z = ReadF16(Location);
	Location += 2;

	// relative altitude
	SC.m_RelativeAltitude = ReadF16(Location);
	Location += 2;

	// pressure
	SC.m_BarometerVal = ReadF32(Location);
	Location += 4;

	SC.m_Temperature = ReadF16(Location);

	SC.m_SuccessfulRead = true;

	return SC;
}

/**
 * @brief    direct lib API wrapper for writing to FRAM
 * @param    Data    the data to write
 * @param    Location   the address to write to
 */
bool FRAM::Write(std::byte Data, uint32_t Location)
{
	if(Location > m_MaxAddr) { return false; }

	return m_FRAM.write(Location, static_cast<uint8_t>(Data));
}

/**
 * @brief    direct lib API wrapper for reading from FRAM
 * @param    Location the address to read from
 * @return   the data read from FRAM
 */
std::byte FRAM::Read(uint16_t Location)
{
	return static_cast<std::byte>(m_FRAM.read(Location));
}

/**
 * @brief    Read f16 from FRAM
 * @param    Location the address to read from
 * @return   the data read from FRAM
 */
float FRAM::ReadF16(uint32_t Location)
{
	std::byte Buff[2];
	for(int i = 0; i < 2; i++)
	{
		Buff[i] = Read(Location + i);
	}
	// *reinterpret_cast<T*>(Var) is UB
	return fp16_ieee_to_fp32_value(std::bit_cast<uint16_t>(Buff));
}

/**
 * @brief    Read f32 from FRAM
 * @param    Location the address to read from
 * @return   the data read from FRAM
 */
float FRAM::ReadF32(uint32_t Location)
{
	std::byte Buff[4];
	for(int i = 0; i < 4; i++)
	{
		Buff[i] = Read(Location + i);
	}
	// *reinterpret_cast<T*>(Var) is UB
	return std::bit_cast<float>(Buff);
}