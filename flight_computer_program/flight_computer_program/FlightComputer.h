#pragma once
#include "StaticVariables.h"
#include "StateMachine.h"
#include "SensorData.h"
#include "DataQueue.h"

class FlightComputer{
private:
    bool able_to_fly;

    StateMachine flight_function;

    DataQueue sensor_data;


    //HealthCheck
    bool start_health_check();

    bool mid_flight_health_check();

    void retrieve_data();

    void main_loop();
    
    FlightComputer();
public:
    void init();
};
