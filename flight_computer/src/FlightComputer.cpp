#include "GlobalVariables.h"
#include "StateMachine.h"
#include "Sensor.h"
#include "FlightComputer.h"

bool FlightComputer::start_health_check()
{
    return true;
}

bool FlightComputer::mid_flight_health_check()
{
	return true;
}


void FlightComputer::retrieve_data()
{
    //get data through canbus and set it to sensor_data
}

//Main
void FlightComputer::main_loop(){

    while (able_to_fly)
    {
        retrieve_data();
        mid_flight_health_check();
        // flight_function.set_variables();
        // flight_function.call_function(&sensor_data);
    }
}

void FlightComputer::init(){
    retrieve_data();
    if(start_health_check()){
        main_loop();
    }
}

/*
FlightComputer::FlightComputer()
{
        able_to_fly = true;
        // flight_function = StateMachine(<#initializer#>);
        sensor_data = DataQueue();
        Flight_Data = &sensor_data;
}
*/
