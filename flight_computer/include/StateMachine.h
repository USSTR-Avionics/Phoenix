#pragma once

#include "Utils/MemoryPool.h"
#include "DataQueue.h"

class StateMachine
{
public:
    explicit StateMachine(State* State = StateMemory.Allocate<Unarmed>());
    void Run(SensorData&);

    StateMachine(StateMachine&) = delete;
    StateMachine& operator=(StateMachine&) = delete;
private:
    SensorData sensor_data;
    State* m_CurrentState{nullptr};
};
