#pragma once

#include <RH_RF95.h>
#include <string_view>

#include "DataStructures.h"

class Radio
{
public:
	explicit Radio(uint8_t CS, uint8_t Int);

	/**
	 * Send string message
	 * @param Data message to send
	 * @param Timeout length to wait before aborting
	 * @return send successful is true
	 */
	bool UDP_Send(std::string_view Data, uint16_t Timeout);
	/**
	 * Send SensorData
	 * @param Data SensorData
	 * @param Timeout length to wait before aborting
	 * @return send successful is true
	 */
	bool UDP_Send(const SensorData& Data, uint16_t Timeout);

	/**
	 * Receive SensorChunk
	 * @return Populated SensorChunk
	 */
	SensorChunk UDP_Receive();
private:
	RH_RF95 m_Radio;
	uint32_t m_Max_message_length;
};
