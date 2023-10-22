//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_LAND_H
#define FLIGHT_COMPUTER_LAND_H

#include "States.h"
#include "Unarmed.h"

class Land : public State
{
public:
    // main
    virtual bool Run(SensorData&) override;
    // return next state
    virtual State* Transition() override;

    ~Land() override = default;
};
#endif //FLIGHT_COMPUTER_LAND_H
