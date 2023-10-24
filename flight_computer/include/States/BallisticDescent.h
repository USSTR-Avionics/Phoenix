//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_BALLISTICDECENT_H
#define FLIGHT_COMPUTER_BALLISTICDECENT_H

#include "MainChute.h"

class BallisticDescent : public State
{
public:
    // main
    virtual bool Run(SensorData&) override;
    // return next state
    virtual State* Transition() override;

	BallisticDescent() = default;
    ~BallisticDescent() override = default;
};
#endif //FLIGHT_COMPUTER_BALLISTICDECENT_H
