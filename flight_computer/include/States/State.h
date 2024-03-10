#ifndef FLIGHT_COMPUTER_STATE_H
#define FLIGHT_COMPUTER_STATE_H
#include "Sensor.h"

#include <variant>
#include <cstdint>

typedef std::variant<
		class Unarmed,
		class GroundIdle,
		class InFlight,
		class MainChute
> StateMemPool;

enum FlightState : uint8_t
{
	eUndefined,
	eUnarmed,
	eGroundIdle,
	eInFlight,
	eMainChute
};

struct State
{
    /**
     * Perform task
     * @return The next state
     */
    virtual State* Run(const SensorData&, StateMemPool&) = 0;

	/**
	 * Finds the State of the current State
	 * @return The state currently at
	 */
	virtual FlightState GetState() = 0;

    virtual ~State() = default;
};

#endif //FLIGHT_COMPUTER_STATE_H
