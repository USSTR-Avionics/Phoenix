//
// Created by TDKua on 2023/10/23.
//

#ifndef FLIGHT_COMPUTER_FUNCTIONS_H
#define FLIGHT_COMPUTER_FUNCTIONS_H

#include <algorithm>
#include <cstdint>

namespace UA
{
/* =============================================================
 * 						FIND MAX CONSTEXPR
 * ============================================================= */

template<typename... T, typename U>
size_t constexpr Max(T ...Args)
{ return std::max({U(Args)...}); }

template<typename... T>
size_t constexpr MaxAlignof()
{ return std::max({alignof(T)...}); }

template<typename... T>
size_t constexpr MaxSizeof()
{ return std::max({sizeof(T)...}); }

// =============================================================
}
#endif //FLIGHT_COMPUTER_FUNCTIONS_H
