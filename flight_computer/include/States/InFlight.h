#ifndef FLIGHT_COMPUTER_INFLIGHT_H
#define FLIGHT_COMPUTER_INFLIGHT_H
#include "BaseState.h"

class InFlight : BaseState
{
public:
	//preveous height value, used to check if moving downwards
	float prevHeight;
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
