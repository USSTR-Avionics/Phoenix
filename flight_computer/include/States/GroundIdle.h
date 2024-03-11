#ifndef FLIGHT_COMPUTER_GROUNDIDLE_H
#define FLIGHT_COMPUTER_GROUNDIDLE_H

#include "State.h"

class GroundIdle : public State
{
public:
    // main
    State* Run(const SensorData&, StateMemPool&) override;
	FlightState GetState() override;

    ~GroundIdle() override = default;
};
#endif //FLIGHT_COMPUTER_GROUNDIDLE_H
