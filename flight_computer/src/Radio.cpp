#include "Radio_t.h"

Radio_t::Radio_t(uint8_t CS, uint8_t Interrupt) : m_Radio{CS, Interrupt}
{
    m_Radio.init();
    m_Max_message_length = m_Radio.maxMessageLength();
}

bool Radio_t::UDP_Send(std::string_view Data, uint16_t Timeout)
{
    if(!m_Radio.waitPacketSent(Timeout)) { return false; }

    return m_Radio.send(reinterpret_cast<const uint8_t*>(Data.cbegin()), Data.size());
}

bool Radio_t::UDP_Send(const SensorData& Data, uint16_t Timeout)
{
	if(!m_Radio.waitPacketSent(Timeout)) { return false; }

	const auto& Bytes{Data.GetBytes()};

    // reinterpret_cast<uint8_t*>(Bytes.data()) is UB
    uint8_t Message[SensorData::m_Size];
	return m_Radio.send(static_cast<const uint8_t *>(memcpy(Message, Bytes.data(), Bytes.size())),
                        Bytes.size()
                        );
}

SensorChunk Radio_t::UDP_Receive()
{
	// message available
	if(!m_Radio.available()) { return {{}, false}; }

	// get message
	uint8_t Buffer[SensorData::m_Size];
	uint8_t BufferLength;

	m_Radio.recv(Buffer, &BufferLength);

	// is message exactly 41 bytes long
	if(BufferLength != SensorData::m_Size) { return {{}, false}; }

    // char, unsigned char, std::byte are allowed under strict aliasing rules
	return SensorChunk::DecodeBytes(reinterpret_cast<const std::byte*>(Buffer));
}
