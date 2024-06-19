#include "Radio.h"

namespace RA
{

Radio::Radio(uint8_t CS, uint8_t Interrupt) : m_Radio{CS, Interrupt}
{
    m_Radio.init();
}

bool Radio::UDP_Send(std::string Data, uint16_t Timeout)
{
    if(m_Max_message_length < Data.size() || !m_Radio.waitPacketSent(Timeout)) { return false; }

	// prepend '2' for str type
	Data = '2' + Data;

    return m_Radio.send(reinterpret_cast<const uint8_t*>(Data.data()), Data.size());
}

bool Radio::UDP_Send(const SensorData& Data, uint16_t Timeout)
{
	if(!m_Radio.waitPacketSent(Timeout)) { return false; }

	const auto& Bytes{Data.GetBytes()};

    // reinterpret_cast<uint8_t*>(Bytes.data()) is UB
    uint8_t Message[SensorData::m_Size + 1];
	// '1' for SensorData
	Message[0] = '1';

	return m_Radio.send(static_cast<const uint8_t *>(memcpy(Message + 1, Bytes.data(), Bytes.size())),
                        Bytes.size() + 1
                        );
}
void Radio::ParseCmd(std::string_view Cmd)
{
	switch(Cmd[0])
	{
		case '0':
		{
			auto Freq = stof(std::string(Cmd.data() + 1));
			m_Radio.setFrequency(Freq);
			UDP_Send("changing frequency to " + std::to_string(Freq), 500);
		}
			break;
		default:
			break;
	}
}

RadioMessage Radio::UDP_Receive()
{
	RadioMessage Message {.MessageType = RadioMessage::Type::UnDefined, .Message = {}};

	// message available
	if(!m_Radio.available()) { return Message; }

	// get message
	uint8_t Buffer[m_Max_message_length];
	uint8_t BufferLength{sizeof(Buffer)};

	m_Radio.recv(Buffer, &BufferLength);

	switch(Buffer[0])
	{
		case '1':
			Message.MessageType = RadioMessage::Type::SensorChunk;
			// char, unsigned char, std::byte are allowed under strict aliasing rules
			Message.Message.emplace<SensorChunk>(SensorChunk::DecodeBytes(reinterpret_cast<std::byte*>(Buffer + 1)));
			break;
		case '2':
			Message.MessageType = RadioMessage::Type::string;
			Message.Message.emplace<std::string>(reinterpret_cast<char*>(Buffer + 1));
			break;
		default:
			break;
	}

	return Message;
}
}
