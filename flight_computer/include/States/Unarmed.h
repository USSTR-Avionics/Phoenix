//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_UNARMED_H
#define FLIGHT_COMPUTER_UNARMED_H

#include "GroundIdle.h"

class Unarmed : public State
{
public:
    // main
    virtual bool Run(SensorData&) override;
    // return next state
    virtual State* Transition() override;

    ~Unarmed() override= default;
};

#endif //FLIGHT_COMPUTER_UNARMED_H
