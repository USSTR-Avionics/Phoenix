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
    virtual State* Run(SensorData&, StateMemPool&) override;

    ~Land() override = default;
};
#endif //FLIGHT_COMPUTER_LAND_H
