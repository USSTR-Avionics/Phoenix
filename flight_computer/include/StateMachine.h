#pragma once

#include "States/Unarmed.h"
#include "States/GroundIdle.h"
#include "States/PoweredFlight.h"
#include "States/UnpoweredFlight.h"
#include "States/BallisticDescent.h"
#include "States/MainChute.h"

#include "Sensor.h"

#include <Arduino.h>

class StateMachine
{
public:
    explicit StateMachine();
    void Run(SensorData&);

    StateMachine(StateMachine&) = delete;
    StateMachine& operator=(StateMachine&) = delete;

	bool Ready();
private:
	StateMemPool m_MemPool;
    State* m_CurrentState { nullptr };

	FlightState m_eCurrentState;
};
