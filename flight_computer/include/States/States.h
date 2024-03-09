//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_STATES_H
#define FLIGHT_COMPUTER_STATES_H
#include <variant>
#include <cstdint>

#include "GlobalVariables.h"


struct State
{
    // true if transition condition met
    virtual State* Run(class SensorData&, StateMemPool&) = 0;

	// track state for logging purpose
	virtual FlightState GetState() = 0;

    virtual ~State() = default;
};

#endif //FLIGHT_COMPUTER_STATES_H
