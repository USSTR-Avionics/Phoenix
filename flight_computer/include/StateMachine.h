#pragma once
#include "States.h"
#include "Sensors.h"
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
	explicit StateMachine();

	/**
	 * Performs state action
	 * @return The current state
	 */
	FlightState Run();

	FlightState GetState() const;

	template<typename State>
	void GoState()
	{
		m_MemPool.emplace<State>();
	}

	StateMachine(StateMachine&) = delete;

	StateMachine& operator =(StateMachine&) = delete;

private:
	FlightStateMemPool m_MemPool{};
};