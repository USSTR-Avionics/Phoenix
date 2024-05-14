#ifndef FLIGHT_COMPUTER_MAINCHUTE_H
#define FLIGHT_COMPUTER_MAINCHUTE_H

#include "BaseState.h"

class MainChute : BaseState
{
public:
	// height to deploy main chute
	float AcceptedMainChuteHeight = 400.f;

	// preveous barometer value used to determine on ground
	float PrevBarVal{};

    // main
    FlightState Run(FlightStateMemPool&) override;

	/**
	 * Finds the State of the current State
	 * @return The state currently at
	 */
	[[nodiscard]]
	FlightState GetState() const override;

    ~MainChute() override = default;
};
#endif //FLIGHT_COMPUTER_MAINCHUTE_H
