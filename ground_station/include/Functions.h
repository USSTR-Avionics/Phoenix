//
// Created by TDKua on 2023/10/23.
//

#ifndef FLIGHT_COMPUTER_FUNCTIONS_H
#define FLIGHT_COMPUTER_FUNCTIONS_H

#include <algorithm>
#include <cstdint>
#include <string>
#include "DataStructures.h"

namespace RA
{
	enum FlightState : uint8_t
	{
		eUnarmed,
		eGroundIdle,
		eInFlight,
		eMainChute
	};

	std::string to_string(FlightState S)
	{
		switch (S)
		{
			case FlightState::eUnarmed:
				return "Unarmed";

			case FlightState::eGroundIdle:
				return "GroundIdle";

			case FlightState::eInFlight:
				return "Inflight";

			case FlightState::eMainChute:
				return "MainChute";

			default:
				return "Invalid flight state";
		}
	}

	std::string to_string(SensorChunk S)
	{
		if(!S.m_SuccessfulRead) { return "Read Failed!\n"; }

		std::string Str = "Accel X Y Z: " + std::to_string(S.m_AccelerometerData.xData) + std::to_string(S.m_AccelerometerData.yData) + std::to_string(S.m_AccelerometerData.zData);
		Str += "\n Gyro X Y Z : " + std::to_string(S.m_Gyro.x) + std::to_string(S.m_Gyro.y) + std::to_string(S.m_Gyro.z);
		Str += "\n Bmp Relative Altitude Barometer : " + std::to_string(S.m_Bmp.RelativeAltitude) + std::to_string(S.m_Bmp.Barometer);
		Str += "\n Temp : " + std::to_string(S.m_Temperature);
		Str += "\n Time Stamp : " + std::to_string(S.m_TimeStamp);
		Str += "\n State : " + to_string(static_cast<FlightState>(S.m_State));

		return Str;
	}

#endif //FLIGHT_COMPUTER_FUNCTIONS_H
}