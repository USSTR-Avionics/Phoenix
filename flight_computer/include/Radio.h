#pragma once

#include <RH_RF95.h>
#include <string_view>

#include "DataStructures.h"

class Radio
{
public:
    explicit Radio(uint8_t CS, uint8_t Int);

    bool UDP_Send(std::string_view Data, uint16_t Timeout);
    bool UDP_Sen
    const char* UDP_Receive(const uint16_t& TImeout);
private:
    RH_RF95 m_Radio;
    uint32_t m_Max_message_length;
};
