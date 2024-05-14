#ifndef FLIGHT_COMPUTER_INFLIGHT_H
#define FLIGHT_COMPUTER_INFLIGHT_H
#include "BaseState.h"
#include <limits>

class InFlight : BaseState
{
public:
	float PrevAltitude{std::numeric_limits<float>::max()};

    // main
    FlightState Run(FlightStateMemPool&) override;

	/**
	 * Finds the State of the current State
	 * @return The state currently at
	 */
	[[nodiscard]]
	FlightState GetState() const override;

    ~InFlight() override = default;
};
#endif //FLIGHT_COMPUTER_GROUNDIDLE_H
