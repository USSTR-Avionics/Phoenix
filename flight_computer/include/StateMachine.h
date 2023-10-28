#pragma once

#include "States/Unarmed.h"
#include "States/GroundIdle.h"
#include "States/PoweredFlight.h"
#include "States/UnpoweredFlight.h"
#include "States/BallisticDescent.h"
#include "States/MainChute.h"

#include "EEPROM.h"
#include "Watchdog_t4.h"
#include "DataQueue.h"

class StateMachine
{
public:
    explicit StateMachine(WDT_timings_t);
    void Run(SensorData&);

    StateMachine(StateMachine&) = delete;
    StateMachine& operator=(StateMachine&) = delete;

	bool Ready();
private:
	static void WD_CallBack();
	StateMemPool m_MemPool;
    State* m_CurrentState { nullptr };
	WDT_T4<WDT2> m_WatchDog;
};
