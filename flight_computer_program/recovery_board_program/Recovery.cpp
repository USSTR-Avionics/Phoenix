#include "Recovery.h"

Recovery::Recovery(/* args */)
{
}

bool Recovery::calculate_apoge(){
    return false;
}

bool Recovery::check_for_flight_computer_signal(){
    return false;
}

void Recovery::main(){
    if ((calculate_apoge || check_for_flight_computer_signal()) && !chute_is_deployed)
    {
        send_chute_signal();
        chute_is_deployed = true;
    }else{
        main();
    }
    
}