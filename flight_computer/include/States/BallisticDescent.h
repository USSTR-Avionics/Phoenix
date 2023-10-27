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
    virtual State* Run(SensorData&, StateMemPool&) override;

	BallisticDescent() = default;
    ~BallisticDescent() override = default;
};
#endif //FLIGHT_COMPUTER_BALLISTICDECENT_H
