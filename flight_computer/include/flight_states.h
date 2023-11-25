#pragma once

#include <cstdint>

enum class FlightStates : uint8_t
{
    UNARMED,
    GROUND_IDLE,
    POWERED_FLIGHT,
    UNPOWERED_FLIGHT,
    BALISTIC_DECENT,
    MAIN_CHUTE,
    LAND_SAFE
};