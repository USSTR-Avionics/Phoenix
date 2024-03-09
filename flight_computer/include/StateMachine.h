#pragma once

#include "States/Unarmed.h"
#include "States/GroundIdle.h"
#include "States/InFlight.h"
#include "States/MainChute.h"

#include "Sensor.h"

#include <Arduino.h>

typedef std::variant<
	Unarmed,
	GroundIdle,
    InFlight,
	MainChute
    > StateMemPool;

enum FlightState : uint8_t
{
    eUnarmed,
    eGroundIdle,
    eInFlight,
    eMainChute
};

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
