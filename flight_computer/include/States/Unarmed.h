//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_UNARMED_H
#define FLIGHT_COMPUTER_UNARMED_H

#include "State.h"

class Unarmed : public State
{
public:
    // main
	State* Run(const SensorData&, StateMemPool&) override;
	FlightState GetState() override;

    ~Unarmed() override= default;
};

#endif //FLIGHT_COMPUTER_UNARMED_H
