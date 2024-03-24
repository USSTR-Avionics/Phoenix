#include <bit>
#include "DataStructures.h"
#include "fp16.h"

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

std::array<std::byte, 25> SensorData::GetBytesCompressed() const
{
	std::array<std::byte, 25> Data{};
	const std::byte* BytePtr;
	uint32_t Cursor{0};

	// Accel, 2 x 3
	{
		const uint16_t AccelXYZ[]
		{
			fp16_ieee_from_fp32_value(m_AccelerometerData.xData),
			fp16_ieee_from_fp32_value(m_AccelerometerData.yData),
			fp16_ieee_from_fp32_value(m_AccelerometerData.zData)
		};

		for(const auto& i : AccelXYZ)
		{
			BytePtr = reinterpret_cast<const std::byte*>(&i);
			for(int j = 0; j < 2; j++, Cursor++)
			{
				Data[Cursor] = BytePtr[j];
			}
		}
	}

	// Gyro, 2 x 3
	{
		const uint16_t GyroXYZ[]
		{
			fp16_ieee_from_fp32_value(m_Gyro.x),
			fp16_ieee_from_fp32_value(m_Gyro.y),
			fp16_ieee_from_fp32_value(m_Gyro.z)
		};

		for(const auto& i : GyroXYZ)
		{
			BytePtr = reinterpret_cast<const std::byte*>(&i);
			for(int j = 0; j < 2; j++, Cursor++)
			{
				Data[Cursor] = BytePtr[j];
			}
		}
	}

	// BMP280, 6
	{
		// relative altitude, 2
		const auto RelativeAltitude{fp16_ieee_from_fp32_value(m_Bmp.RelativeAltitude)};
		BytePtr = reinterpret_cast<const std::byte*>(&RelativeAltitude);
		for(int i = 0; i < 2; i++, Cursor++)
		{
			Data[Cursor] = BytePtr[i];
		}

		// pressure, 4
		BytePtr = reinterpret_cast<const std::byte*>(&m_Bmp.Barometer);
		for(int i = 0; i < 4; i++, Cursor++)
		{
			Data[Cursor] = BytePtr[i];
		}
	}

	// Thermocouple, 4
	BytePtr = reinterpret_cast<const std::byte*>(&m_Temperature);
	for(int i = 0; i < 4; i++, Cursor++)
	{
		Data[Cursor] = BytePtr[i];
	}

	// Time Stamp, 4
	BytePtr = reinterpret_cast<const std::byte*>(&m_TimeStamp);
	for(int i = 0; i < 4; Cursor++, i++)
	{
		Data[Cursor] = BytePtr[i];
	}

	// Rocket State, 1
	Data[Cursor] = static_cast<std::byte>(m_State);

	return Data;
}


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
SensorChunk SensorChunk::DecodeBytesCompressed(const std::byte* Data)
{
	if(Data == nullptr) { return {.m_SuccessfulRead = false}; }

	return
	{
		// Sensor chunk
		{
			.m_AccelerometerData =
			{
				.xData = ReadF16(Data),
				.yData = ReadF16((Data += 2)),  // last read 2 bytes
				.zData = ReadF16((Data += 2))
			},

			.m_Gyro =
			{
				.x = ReadF16((Data += 2)),
				.y = ReadF16((Data += 2)),
				.z = ReadF16((Data += 2))
			},

			// Bmp
			.m_Bmp =
			{
				.RelativeAltitude = ReadF16((Data += 2)),
				.Barometer = ReadF32((Data += 2))
			},

			// Temperature
			.m_Temperature = ReadF16((Data += 4)),  // last read 4 bytes

			// Time stamp
			.m_TimeStamp = std::bit_cast<uint32_t>(ReadF32((Data += 2))),

			// State
			.m_State = static_cast<FlightState>(Data[4]),  // last read 4 bytes
		},
		true
	};
}


// compressed data chunk format
// |----------------------|-----------|-----------|
// |      data            |   size    | data type |
// |----------------------|-----------|-----------|
// | acceleration x axis  | 04 bytes  | float32   |
// | acceleration y axis  | 04 bytes  | float32   |
// | acceleration z axis  | 04 bytes  | float32   |
// | gyroscope x axis     | 04 bytes  | float32   |
// | gyroscope y axis     | 04 bytes  | float32   |
// | gyroscope z axis     | 04 bytes  | float32   |
// | relative altitude    | 04 bytes  | float32   |
// | pressure (barometer) | 04 bytes  | float32   |
// | thermocouple temp    | 04 bytes  | float32   |
// | timestamp            | 04 bytes  | uint32_t  |
// | rocket state         | 01 byte   | uint8_t   |
// |----------------------|-----------|-----------|
// | total                | 41 bytes  |           |
// |----------------------|-----------|-----------|

std::array<std::byte, 41> SensorData::GetBytes() const
{
	std::array<std::byte, 41> Data{};
	const std::byte* BytePtr;
	uint32_t Cursor{0};

	const float Values[]
	{
		m_AccelerometerData.xData,
		m_AccelerometerData.yData,
		m_AccelerometerData.zData,
		m_Gyro.x,
		m_Gyro.y,
		m_Gyro.z,
		m_Bmp.RelativeAltitude,
		m_Bmp.Barometer,
		m_Temperature
	};

	for(const float& i : Values)
	{
		BytePtr = reinterpret_cast<const std::byte*>(&i);
		for(uint8_t j = 0; j < 4; Cursor++, j++)
		{
			Data[Cursor] = BytePtr[j];
		}
	}

	// Time Stamp
	BytePtr = reinterpret_cast<const std::byte*>(&m_TimeStamp);
	for(int i = 0; i < 4; Cursor++, i++)
	{
		Data[Cursor] = BytePtr[i];
	}

	// Rocket State
	Data[Cursor] = static_cast<std::byte>(m_State);

	return Data;
}

// compressed data chunk format
// |----------------------|-----------|-----------|
// |      data            |   size    | data type |
// |----------------------|-----------|-----------|
// | acceleration x axis  | 04 bytes  | float32   |
// | acceleration y axis  | 04 bytes  | float32   |
// | acceleration z axis  | 04 bytes  | float32   |
// | gyroscope x axis     | 04 bytes  | float32   |
// | gyroscope y axis     | 04 bytes  | float32   |
// | gyroscope z axis     | 04 bytes  | float32   |
// | relative altitude    | 04 bytes  | float32   |
// | pressure (barometer) | 04 bytes  | float32   |
// | thermocouple temp    | 04 bytes  | float32   |
// | timestamp            | 04 bytes  | uint32_t  |
// | rocket state         | 01 byte   | uint8_t   |
// |----------------------|-----------|-----------|
// | total                | 41 bytes  |           |
// |----------------------|-----------|-----------|
SensorChunk SensorChunk::DecodeBytes(const std::byte* Data)
{
	if(Data == nullptr) { return {.m_SuccessfulRead = false}; }

	return
	{
		// Sensor chunk
		{
			.m_AccelerometerData =
			{
				.xData = ReadF32(Data),
				.yData = ReadF32((Data += 4)),
				.zData = ReadF32((Data += 4))
			},

			.m_Gyro =
			{
				.x = ReadF32((Data += 4)),
				.y = ReadF32((Data += 4)),
				.z = ReadF32((Data += 4))
			},

			// Bmp
			.m_Bmp =
			{
				.RelativeAltitude = ReadF32((Data += 4)),
				.Barometer = ReadF32((Data += 4))
			},

			// Temperature
			.m_Temperature = ReadF32((Data += 4)),

			// Time stamp
			.m_TimeStamp = std::bit_cast<uint32_t>(ReadF32((Data += 4))),

			// State
			.m_State = static_cast<FlightState>(Data[4]),
		},
		true
	};
}

float SensorChunk::ReadF16(const std::byte* Location)
{
	std::byte Buffer[2]{Location[0], Location[1]};
	return fp16_ieee_to_fp32_value(std::bit_cast<uint16_t>(Buffer));
}

float SensorChunk::ReadF32(const std::byte* Location)
{
	std::byte Buffer[4]{Location[0], Location[1], Location[2], Location[3]};
	return std::bit_cast<float>(Buffer);
}

