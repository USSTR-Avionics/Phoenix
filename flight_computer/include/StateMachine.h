#pragma once
#include "flight_states.h"
#include "SensorData.h"
#include "DataQueue.h"

class StateMachine{
private:
    SensorData sensor_data;

    void unarmed();

    void ground_idle();

    void powered_flight();

    void unopowered_flight();

    void balistic_decent();

    void main_chute();

    void land_safe();
public:
    FlightStates flight_state;
    void set_variables();

    void call_function(DataQueue *data);

    StateMachine();
};
