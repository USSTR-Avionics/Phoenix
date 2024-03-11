#pragma once
#include <Arduino.h>

#include "States.h"

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

    void Run(const SensorData&);

	/**
	 * Checks if memory pool is initialized
	 * @return true if ready
	 */
	bool Ready();

    StateMachine(StateMachine&) = delete;
    StateMachine& operator=(StateMachine&) = delete;

private:
	StateMemPool m_MemPool;
    State* m_CurrentState { nullptr };
};
