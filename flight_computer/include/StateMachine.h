#pragma once

#include "GlobalVariables.h"
#include "DataQueue.h"

class StateMachine
{
public:
    explicit StateMachine(State* State = StatePool.Allocate<Unarmed>());
    void Run(SensorData&);

    StateMachine(StateMachine&) = delete;
    StateMachine& operator=(StateMachine&) = delete;
private:
    SensorData sensor_data;
    State* m_CurrentState{nullptr};
};
