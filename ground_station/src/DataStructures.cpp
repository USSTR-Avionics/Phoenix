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

std::array<std::byte, SensorData::m_CompressedSize> SensorData::GetBytesCompressed() const
{
	std::array<std::byte, m_CompressedSize> Data{};
	std::byte* Cursor{Data.data()};

	// Accel, 2 x 3, // Gyro, 2 x 3
	{
		const uint16_t AccelXYZ_GyroXYZ[]
		{
			// Accel
			fp16_ieee_from_fp32_value(m_AccelerometerData.xData),
			fp16_ieee_from_fp32_value(m_AccelerometerData.yData),
			fp16_ieee_from_fp32_value(m_AccelerometerData.zData),

			// Gyro
			fp16_ieee_from_fp32_value(m_Gyro.x),
			fp16_ieee_from_fp32_value(m_Gyro.y),
			fp16_ieee_from_fp32_value(m_Gyro.z)
		};

		for(const auto& i : AccelXYZ_GyroXYZ)
		{
			memcpy(static_cast<void*>(Cursor), &i, 2);
			Cursor += 2;
		}
	}

	// BMP280, 2 + 4
	{
		// relative altitude, 2
		const auto& RelativeAltitude{fp16_ieee_from_fp32_value(m_Bmp.RelativeAltitude)};
		memcpy(static_cast<void*>(Cursor), &RelativeAltitude, 2);
		Cursor += 2;

		// pressure, 4
		memcpy(static_cast<void*>(Cursor), &m_Bmp.Barometer, 4);
		Cursor += 4;
	}

	// Thermocouple, 2
	{
		const auto& Temperature {fp16_ieee_from_fp32_value(m_Temperature)};
		memcpy(static_cast<void*>(Cursor), &Temperature, 2);
		Cursor += 2;
	}


	// Time Stamp, 4
	memcpy(static_cast<void*>(Cursor), &m_TimeStamp, 4);
	Cursor += 4;

	// Rocket State, 1
	*Cursor = static_cast<std::byte>(m_State);

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
SensorChunk SensorChunk::DecodeBytesCompressed(const std::byte Data[25])
{
	if(Data == nullptr) { return {{}, false}; }

	return
	{
		// Sensors chunk
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

std::array<std::byte, SensorData::m_Size> SensorData::GetBytes() const
{
	std::array<std::byte, m_Size> Data{};
	std::byte* Cursor{Data.data()};

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
		memcpy(static_cast<void*>(Cursor), &i, 4);
		Cursor += 4;
	}

	// Time Stamp
	memcpy(static_cast<void*>(Cursor), &m_TimeStamp, 4);
	Cursor += 4;

	// Rocket State
	*Cursor = static_cast<std::byte>(m_State);

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
SensorChunk SensorChunk::DecodeBytes(const std::byte Data[41])
{
	if(Data == nullptr) { return {{}, false}; }

	return
	{
		// Sensors chunk
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

float SensorChunk::ReadF16(const std::byte Location[2])
{
	uint16_t Value;
	memcpy(&Value, Location, 2);
	return fp16_ieee_to_fp32_value(Value);
}

// assuming float is 4 bytes
float SensorChunk::ReadF32(const std::byte Location[4])
{
    float Value;
    memcpy(&Value, Location, 4);
	return Value;
}

