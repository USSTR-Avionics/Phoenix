#pragma once
#include <Arduino.h>

#include "States.h"
#include "Sensor.h"
#include "FRAM.h"

/**
 * Manages States
 */
class StateMachine
{
public:
	/**
	 * Initialize and enter into Unarmed state
	 */
	explicit StateMachine(RA::Sensor&& Sensor, FRAM&& Fram);

	/**
	 * Performs state action
	 * @return The current state
	 */
	FlightState Run();

	FlightState GetState() const;

	StateMachine(StateMachine&) = delete;

	StateMachine& operator =(StateMachine&) = delete;

private:
	FlightStateMemPool m_MemPool{};

    // shared resources between states
    RA::Sensor m_Sensor;
    FRAM m_Fram;
    SensorData m_SensorData;
    FlightState m_CurrentState;
};