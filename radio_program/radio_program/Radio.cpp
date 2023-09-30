#include "Radio.h"

Radio::Radio(/* args */)
{
}

bool Radio::listen_for_signal(){
    return true;
}

void Radio::main(){
    if(listen_for_signal()){
        send_data_to_flight_computer();
    }
    if(recieve_canbus_data()){
        send_data_to_ground_station();
    }
    main();
}