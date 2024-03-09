//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_GROUNDIDLE_H
#define FLIGHT_COMPUTER_GROUNDIDLE_H

#include "InFlight.h"

#include "GlobalVariables.h"
#include "States.h"

class GroundIdle : public State
{
public:
    // main
    virtual State* Run(SensorData&, StateMemPool&) override;
	virtual FlightState GetState() override;

    ~GroundIdle() override = default;
};
#endif //FLIGHT_COMPUTER_GROUNDIDLE_H
