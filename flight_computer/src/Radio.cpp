#include "Radio.h"

Radio::Radio(uint8_t CS, uint8_t Interrupt) : m_Radio{CS, Interrupt}
{
    m_Radio.init();
    m_Max_message_length = m_Radio.maxMessageLength();
}

bool Radio::UDP_Send(std::string_view Data, uint16_t Timeout)
{
    if(Data.size() + 1 > m_Max_message_length) { return false; }
    if(!m_Radio.waitPacketSent(Timeout)) { return false; }
    m_Radio.send(reinterpret_cast<const uint8_t*>(Data.cbegin()), Data.size() + 1);

    return true;
}
