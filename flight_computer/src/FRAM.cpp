#include "FRAM_t.h"

#include <bit>

/**
 * Is the FRAM_t ready
 * @param I2C_Addr the I^2C address to use
 * @return true if ready
 */
bool FRAM_t::Init(uint8_t I2C_Addr)
{
	return m_FRAM.begin(I2C_Addr);
}

/**
 * @brief    stores sensor info to fram
 * 	// compressed data chunk format
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
 * @param    SD struct of SensorData to store
 * @return   success or failure
 */
bool FRAM_t::StoreData(SensorData SD)
{
	uint32_t Cursor{m_FramWriteCursor};

	for(const std::byte& Byte : SD.GetBytesCompressed())
	{
		if(!Write(Byte, Cursor++)) { return false; }
	}

	m_FramWriteCursor = Cursor;
	return true;
}

/**
 * @brief Reads SensorData chunck from FRAM_t
 * 	// compressed data chunk format
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
 * @param    Location the address to read from
 * @return   the data chunk read from FRAM_t
 */
SensorChunk FRAM_t::ReadData(uint16_t Item)
{
	// check if valid location
	if(static_cast<uint32_t>((Item + 1) * 25) > m_MaxAddr) { return {{}, false}; }

	uint32_t Location{static_cast<uint32_t>(Item * 25)};
	std::byte Buffer[25];

	for(auto& Element : Buffer)
	{
		Element = Read(Location);
		Location++;
	}

	return SensorChunk::DecodeBytesCompressed(Buffer);
}

/**
 * @brief    direct lib API wrapper for writing to FRAM_t
 * @param    Data    the data to write
 * @param    Location   the address to write to
 */
bool FRAM_t::Write(std::byte Data, uint32_t Location)
{
	if(Location > m_MaxAddr) { return false; }

	return m_FRAM.write(Location, static_cast<uint8_t>(Data));
}

/**
 * @brief    direct lib API wrapper for reading from FRAM_t
 * @param    Location the address to read from
 * @return   the data read from FRAM_t
 */
std::byte FRAM_t::Read(uint16_t Location)
{
	return static_cast<std::byte>(m_FRAM.read(Location));
}