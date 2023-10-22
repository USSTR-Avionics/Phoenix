//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_UNPOWERFLIGHT_H
#define FLIGHT_COMPUTER_UNPOWERFLIGHT_H

#include "BallisticDescent.h"

class UnpoweredFlight : public State
{
public:
    // main
    virtual bool Run(SensorData&) override;
    // return next state
    virtual State* Transition() override;

    ~UnpoweredFlight() override = default;
};
#endif //FLIGHT_COMPUTER_UNPOWERFLIGHT_H
