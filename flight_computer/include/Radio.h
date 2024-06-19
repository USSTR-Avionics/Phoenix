#pragma once

#include <RH_RF95.h>
#include <string>
#include <variant>

#include "DataStructures.h"

namespace RA
{
	struct RadioMessage
	{
		enum class Type : uint8_t
		{
			UnDefined,
			SensorChunk,
			string
		} MessageType = Type::UnDefined;

		std::variant<SensorChunk, std::string> Message;
	};

	class Radio
	{
	public:
		/**
		 * Create RF95 radio
		 * @param CS cs pin, slave pin
		 * @param Int interrupt pin
		 */
		explicit Radio(uint8_t CS, uint8_t Interrupt);

		/**
		 * Send string message
		 * @param Data message to send
		 * @param Timeout length to wait before aborting
		 * @return send successful is true
		 */
		bool UDP_Send(std::string Data, uint16_t Timeout);

		/**
		 * Send SensorData
		 * @param Data SensorData
		 * @param Timeout length to wait before aborting
		 * @return send successful is true
		 */
		bool UDP_Send(const SensorData& Data, uint16_t Timeout);

		/**
		 * Execute command
		 * @param Cmd : Cmd[0] - Cmd type, Cmd[1:] - rest of cmd
		 * ----------------
		 * Cmd Type
		 * ----------------
		 * '0' | change frequency
		 * ----------------
		 */
		void ParseCmd(std::string_view Cmd);

		/**
		 * Receive Data
		 */
		RadioMessage UDP_Receive();

		static const uint32_t m_Max_message_length{RH_RF95_MAX_MESSAGE_LEN};
	private:
		RH_RF95 m_Radio;
	};
}
