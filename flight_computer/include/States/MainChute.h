//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_MAINCHUTE_H
#define FLIGHT_COMPUTER_MAINCHUTE_H

#include "State.h"

class MainChute : public State
{
public:
    // main
    State* Run(const SensorData&, StateMemPool&) override;
	FlightState GetState() override;

    ~MainChute() override = default;
};
#endif //FLIGHT_COMPUTER_MAINCHUTE_H
