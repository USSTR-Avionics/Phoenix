//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_GROUNDIDLE_H
#define FLIGHT_COMPUTER_GROUNDIDLE_H

#include "PoweredFlight.h"

class GroundIdle : public State
{
public:
    // main
    virtual State* Run(SensorData&, StateMemPool&) override;

    ~GroundIdle() override = default;
};
#endif //FLIGHT_COMPUTER_GROUNDIDLE_H
