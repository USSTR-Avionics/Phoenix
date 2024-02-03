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
    virtual State* Run(SensorData&, StateMemPool&) override;
	virtual FlightState GetState() override;

    ~MainChute() override = default;
};
#endif //FLIGHT_COMPUTER_MAINCHUTE_H
