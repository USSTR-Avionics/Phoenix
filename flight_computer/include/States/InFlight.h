
//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_INFLIGHT_H
#define FLIGHT_COMPUTER_INFLIGHT_H
#include "MainChute.h"

class InFlight : public State
{
public:
    // main
    virtual State* Run(SensorData&, StateMemPool&) override;
	virtual FlightState GetState() override;

    ~InFlight() override = default;
};
#endif //FLIGHT_COMPUTER_GROUNDIDLE_H
