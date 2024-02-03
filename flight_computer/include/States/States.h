//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_STATES_H
#define FLIGHT_COMPUTER_STATES_H
#include <variant>
#include <cstdint>

enum FlightState : uint8_t
{
	eUnarmed,
	eGroundIdle,
	ePoweredFlight,
	eUnpoweredFlight,
	eBallisticDescent,
	eMainChute,
	eLand
};

typedef std::variant<
	class Unarmed,
	class GroundIdle,
	class PoweredFlight,
	class UnpoweredFlight,
	class BallisticDescent,
	class MainChute,
	class Land> StateMemPool;

struct State
{
    // true if transition condition met
    virtual State* Run(class SensorData&, StateMemPool&) = 0;

	// track state for logging purpose
	virtual FlightState GetState() = 0;

    virtual ~State() = default;
};

#endif //FLIGHT_COMPUTER_STATES_H
