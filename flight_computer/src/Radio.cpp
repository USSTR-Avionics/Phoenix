#include "Radio.h"

Radio::Radio(uint8_t CS, uint8_t Interrupt) : m_Radio{CS, Interrupt}
{
    m_Radio.init();
    m_Max_message_length = m_Radio.maxMessageLength();
}

bool Radio::UDP_Send(std::string_view Data, uint16_t Timeout)
{
    if(!m_Radio.waitPacketSent(Timeout)) { return false; }

    return m_Radio.send(reinterpret_cast<const uint8_t*>(Data.cbegin()), Data.size());
}

bool Radio::UDP_Send(const SensorData& Data, uint16_t Timeout)
{
	if(!m_Radio.waitPacketSent(Timeout)) { return false; }

	const auto& Bytes{Data.GetBytes()};

	return m_Radio.send(reinterpret_cast<const uint8_t*>(Bytes.cbegin()), Bytes.size());
}

SensorChunk Radio::UDP_Receive()
{
	// message available
	if(!m_Radio.available()) { return {{}, false}; }

	// get message
	union
	{
		uint8_t uint_Buffer[SensorData::m_Size];
		std::byte ByteBuffer[SensorData::m_Size];
	} Buffer{};
	uint8_t BufferLength{SensorData::m_Size};

	m_Radio.recv(Buffer.uint_Buffer, &BufferLength);

	// is message exactly 41 bytes long
	if(BufferLength != SensorData::m_Size) { return {{}, false}; }

	return SensorChunk::DecodeBytes(Buffer.ByteBuffer);
}
