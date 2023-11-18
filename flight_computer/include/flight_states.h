#pragma once
enum class FlightStates : unint8_t 
{
    eUnarmed,
    GROUND_IDLE,
    POWERED_FLIGHT,
    UNPOWERED_FLIGHT,
    BALISTIC_DECENT,
    MAIN_CHUTE,
    LAND_SAFE
};