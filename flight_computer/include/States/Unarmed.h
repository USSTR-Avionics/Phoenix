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
    virtual State* Run(SensorData&, StateMemPool&) override;

    ~Unarmed() override= default;
};

#endif //FLIGHT_COMPUTER_UNARMED_H
