//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_MAINCHUTE_H
#define FLIGHT_COMPUTER_MAINCHUTE_H

#include "Land.h"

class MainChute : public State
{
public:
    // main
    virtual bool Run(SensorData&) override;
    // return next state
    virtual State* Transition() override;

    ~MainChute() override = default;
};
#endif //FLIGHT_COMPUTER_MAINCHUTE_H
