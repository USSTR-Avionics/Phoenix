//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_POWEREDFLIGHT_H
#define FLIGHT_COMPUTER_POWEREDFLIGHT_H

#include "UnpoweredFlight.h"

class PoweredFlight : public State
{
public:
    // main
    virtual bool Run(SensorData&) override;
    // return next state
    virtual State* Transition() override;

    ~PoweredFlight() override = default;
};
#endif //FLIGHT_COMPUTER_POWEREDFLIGHT_H
