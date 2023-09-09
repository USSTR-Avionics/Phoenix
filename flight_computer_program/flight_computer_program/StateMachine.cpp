#include "SensorData.h"
#include "StateMachine.h"
#include "flight_states.h"

void StateMachine::set_variables(){
    
}

void StateMachine::unarmed(){
    //check arming signal from canbus
}

void StateMachine::ground_idle(){
    //swich state on acceleration
}

void StateMachine::powered_flight(){
    //swich state on deceleration
}

void StateMachine::unopowered_flight(){
    //swich state on apoge
}

void StateMachine::balistic_decent(){
    //switch state on proper altitude
}

void StateMachine::main_chute(){
    //switch state if on ground
}

void StateMachine::land_safe(){
    
}

void StateMachine::call_function(){
    switch (flight_state)
    {
    case FlightStates::UNARMED:
        unarmed();
        break;
    case FlightStates::GROUND_IDLE:
        ground_idle();
        break;
    case FlightStates::POWERED_FLIGHT:
        powered_flight();
        break;
    case FlightStates::UNPOWERED_FLIGHT:
        unopowered_flight();
        break;
    case FlightStates::BALISTIC_DECENT:
        balistic_decent();
        break;
    case FlightStates::MAIN_CHUTE:
        main_chute();
        break;
    case FlightStates::LAND_SAFE:
        land_safe();
        break;
    default:
        //add Emergency Function
        break;
    }
}

StateMachine::StateMachine(){
    flight_state = FlightStates::UNARMED;
}
