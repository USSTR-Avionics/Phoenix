#pragma once

#include "States/Unarmed.h"
#include "States/GroundIdle.h"
#include "States/PoweredFlight.h"
#include "States/UnpoweredFlight.h"
#include "States/BallisticDescent.h"
#include "States/MainChute.h"
#include "States/Land.h"

#include "DataQueue.h"
#include "SensorData.h"

class StateMachine
{
public:
    explicit StateMachine();
    void Run(SensorData&);

    StateMachine(StateMachine&) = delete;
    StateMachine& operator=(StateMachine&) = delete;
private:
    SensorData sensor_data;
	StateMemPool MemPool;
    State* m_CurrentState { nullptr };
};
