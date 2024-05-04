#pragma once
#include "States.h"
#include "Sensor_t.h"
#include "FRAM_t.h"

/**
 * Manages States
 */
class StateMachine_t
{
public:
	/**
	 * Initialize and enter into Unarmed state
	 */
	explicit StateMachine_t();

	/**
	 * Performs state action
	 * @return The current state
	 */
	FlightState Run();

	FlightState GetState() const;

	StateMachine_t(StateMachine_t&) = delete;

	StateMachine_t& operator =(StateMachine_t&) = delete;

private:
	FlightStateMemPool m_MemPool{};
};