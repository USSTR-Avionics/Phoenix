#ifndef FLIGHT_COMPUTER_FUNCTIONS_H
#define FLIGHT_COMPUTER_FUNCTIONS_H

#include "States.h"

namespace UA
{
/* =============================================================
 * 						FIND MAX CONSTEXPR
 * ============================================================= */

template <typename... T, typename U>
size_t constexpr Max(T... Args)
{
    return std::max({U(Args)...});
}

template <typename... T>
size_t constexpr MaxAlignof()
{
    return std::max({alignof(T)...});
}

template <typename... T>
size_t constexpr MaxSizeof()
{
    return std::max({sizeof(T)...});
}

// =============================================================
} // namespace UA

const char* to_string(FlightState S)
{
    switch (S)
    {
        case FlightState::eUnarmed:
            return "Unarmed";

        case FlightState::eGroundIdle:
            return "GroundIdle";

        case FlightState::eInFlight:
            return "Inflight";

        case FlightState::eMainChute:
            return "MainChute";

        default:
            return "Invalid flight state";
    }
}
#endif // FLIGHT_COMPUTER_FUNCTIONS_H
