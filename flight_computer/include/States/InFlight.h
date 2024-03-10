#ifndef FLIGHT_COMPUTER_INFLIGHT_H
#define FLIGHT_COMPUTER_INFLIGHT_H
#include "State.h"

class InFlight : public State
{
public:
    // main
    State* Run(const SensorData&, StateMemPool&) override;
	FlightState GetState() override;

    ~InFlight() override = default;
};
#endif //FLIGHT_COMPUTER_GROUNDIDLE_H
