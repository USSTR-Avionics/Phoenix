//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_STATES_H
#define FLIGHT_COMPUTER_STATES_H

#include "SensorData.h"

struct State
{
    // true if transition condition met
    virtual bool Run(SensorData&) = 0;
    virtual State* Transition() = 0;
    virtual ~State() = default;
};

#endif //FLIGHT_COMPUTER_STATES_H
