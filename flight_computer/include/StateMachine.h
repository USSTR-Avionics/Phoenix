#pragma once

#include "States/Unarmed.h"
#include "DataQueue.h"

class StateMachine
{
public:
    StateMachine(State* State = new Unarmed());
    void Run(SensorData&);

private:
    SensorData sensor_data;
    State* m_CurrentState{nullptr};
};
